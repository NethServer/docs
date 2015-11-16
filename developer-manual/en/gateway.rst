.. _firewall_gateway-section:

=====================
Firewall and Gateway 
=====================

NethServer can work into two basic modes:

* server mode: the system will be a standard host inside the network offering services like e-mail or file server.
* gateway mode: the system is the gateway and firewall of the local network

The system has an abstraction layer for firewall base functions, like opening ports for running services.
Actually two implementations are available:

* server mode: standard :command:`lokkit` (default on CentOS)
* gateway mode: advanced Shorewall configuration

The gateway functionality is built around three modules:

* nethserver-base: high-level abstraction of the firewall
* nethserver-firewall-base: Shorewall-based implementation
* nethserver-lsm: link status monitor for multi-wan configurations


.. _section-roles-and-zones:

Roles and zones
===============

Each network interface has a role which maps to a firewall zone.
The firewall has the following built-in zones, ordered from the most to the least privileged:

* *green*: local network, it's considered almost trusted. Hosts in this network can access any other zone. Hosts connected via VPN can be considered in green zone.
* *blue*: guest network.  Hosts in this network can access orange and red zones, can't access green zone
* *orange*: DMZ network. Hosts in this network can access red zone, can't access green and blue zones
* *red*: external/internet networks.  Hosts in this network can access only firewall zone
* a: (not implemented yet) traffic from/to this zone must be explicitly allowed

There is also a special *firewall* zone which represents the firewall itself. The firewall can access any other zone. 

Each network interface with a configured role is a firewall zone. Roles are mapped to Shorewall zone as:

* green -> loc
* red -> net
* blue -> blue
* orange -> orang (in Shorewall, a zone name can't be longer than 5 chars)
* firewall -> FW

Custom zone names are directly mapped to Shorewall respecting the limit of 5 chars.

Red interfaces can be configured with static IP address or using DHCP. All other interfaces can be configured only with static IP addresses.


General configuration
=====================

Properties of ``firewall`` key inside ``configuration`` db:

* ``event``: event to call when ``firewall-adjust`` event is fired
* ``tc``: traffic shape mode (see below)
* ``ExternalPing``: if enabled, allow ping responses on external interface
* ``WanMode``: multi-wan mode. Default is ``balance``, can be:

  * ``balance``: traffic is balanced among red interfaces in weighted mode
  * ``backup``: traffic is routed via wan interface with maximum weight, all other interfaces are used as fallback
* ``nfq``: if enabled, traffic from external networks will be passed to NFQ and scanned with Snort. See :ref:`ips`.
* ``Policy``: can be ``permissive`` or ``strict``. See above.
* ``MACValidation``: if enabled, the firewall will check the traffic against a list of known MAC addresses (see: :ref:`ipbinding-section`)
* ``MACValidationPolicy``: can be ``accept`` or ``drop``. Default is ``drop``. See ``man shorewall.conf`` for all valid values
* ``InterfaceRoleList``: list of network interface roles configurable from web interface. Default is: ``green,red,blue,orange``
* ``CheckIP``: comma-separeted list of IP monitored by LSM, to check if a provider is up or down
* ``MaxNumberPacketLoss``: number of maximum consecutive packets lost, over this threshold the provider is considered down
* ``MaxPercentPacketLoss``: percentage of maximum packet lost, over this threshold the provider is considered down
* ``PingInterval``: seconds between ICMP packets sent by LSM, default is ``5``
* ``NotifyWan``: can be ``enabled`` or ``disabled``, if ``enabled`` a mail is sent every time a provider changes its own state
* ``NotifyWanFrom``: sender address for mails sent if NotifyWAN is set to enabled
* ``NotifyWanTo``: recipient address for mails sent if NotifyWAN is set to enabled


Example

::

  firewall=configuration
      event=nethserver-firewall-base-save
      tc=Simple
      nfq=disabled
      WanMode=balance
      Policy=permissive


Events
======

The main event for firewall configuration is *firewall-adjust*. The event contains a single action which fires the event named in the property ``event`` inside the ``firewall`` key into the ``configuration`` database. 

Other events:

* lokkit-save: base firewall implementation using lokkit
* nethserver-firewall-base-save:  firewall implementation using Shorewall 
* wan-uplink-update:  fired when the status of an external interface changes

The ``wan-uplink-event`` event takes at least two parameters:

* provider name: name of the provider involved
* action: can be ``up`` or ``down``, describing the new provider status

Example: ::

  signal-event wan-uplink-update down myisp


Policy
======

For every network packet traveling between firewall zones, the system will evaluate a list of rules to allow/block the specific traffic.
Policies are default firewall rules which will be applied only if no other rule matches the ongoing traffic.

Firewall implements two standard policies:

* :dfn:`Permissive`: will enable all traffic from green (loc) zone to red (net) zone. 
* :dfn:`Strict`: will block all traffic from green (loc) zone to red (net) zone. Permitted traffic should be explicitly allowed.

The firewall configures 4 default zones with built-in policies (see above).
In the schema below, traffic is permitted from left to right and blocked from right to left:

GREEN -> BLUE -> ORANGE -> RED

To override a policy, you should create a firewall rule between zones.

.. _ipbinding-section:

IP/MAC binding
==============

When ``MACValidation`` option is enabled, the firewall analyzes all the traffic based on a well-known list of IPs associated to MAC addresses.
If the host generating the traffic is not inside the list, ``MACValidationPolicy`` will be applied.
The list of IP/MAC association is created from DHCP reservations.

Thus, enabling MACValidation and leaving MACValidationPolicy set to drop, will block all traffic from hosts without a DHCP reservation.


Rules
=====

Firewall rules can allow or deny traffic matching certain conditions.
Rules are saved inside the ``fwrules`` database as records of type ``rule``.

Each rule record has the following fields:

* ``key``: a unique key identifier
* ``Position``: integer sorting key
* ``Src``, ``Dst``: {*literal*|*reference*} where

  * *literal* is an IP or CIDR
  * *reference* has the form ``prefix;value``, where prefix can be a DB type (``host``, ``host-group``,  ``zone``) or the string ``role``, 
    ``value`` is a DB key or an interface role name (``green``, ``red``...)
* ``Action``: can be ``ACCEPT``, ``DROP`` or ``REJECT``

  * ``ACCEPT`` allows the traffic
  * ``REJECT`` denies the traffic, an ICMP port unreachable packet is sent to the source address
  * ``DROP`` discards the traffic without informing the source address (the connection will timeout)
* ``Service``: (optional) can be a service object or a port number. If a port number is used, both TCP and UDP protocols are matched.
* ``Log``: can be ``none`` or ``info``. If value is ``info``, all matched packets will be logged in ``/var/log/firewall.log``. Defaults to ``none``
* ``status``: can be ``enabled`` or ``disabled``. Default is ``enabled``
* ``Description``: (optional)

Example of a rule accepting traffic: ::

  1=rule 
      Src=host;myhost 
      Dst=192.168.1.2 
      Service=service;ssh 
      Action=accept 
      Position=32

Accept all traffic from myhost to myserver for ssh service (port 22): ::

  db fwrules set 1 rule Src "host;myhost" Dst "host;myserver" Service ssh Action ACCEPT Log none status enabled Position 8765

Drop all traffic from 192.168.1.0/24 to 192.168.4.1 on TCP and UDP port 25: ::

  db fwrules set 2 rule Src  192.168.1.0/24 Dst 192.168.4.1 Service 22 Action DROP Log none status enabled Position 5469


Firewall objects
=================

Firewall module uses objects to simplify rules creation. The use of objects is not mandatory but it's strongly encouraged.

Supported objects are:

* Host
* Group of host
* Service
* CIDR
* Ip range
* Zone


A host is an already defined entry inside the ``hosts`` db, or a new key of type ``host``: ::

   name=host
       IpAddress=IP
       Description=



A ``host-group`` is a group of hosts inside the ``hosts`` db. Hosts in a :index:`host-group` should always be reachable using the same interface.
For example: a group of host inside the LAN or on the Internet.
A ``host-group`` db entry can be something like: ::

    name=host-group
        Members=host1,host2

A ``CIDR`` is a group of hosts defined as a CIDR network. It's saved inside the ``hosts`` db: ::

    mycidr=cidr
        Address=192.168.100.0/24
        Description=


A ``IP range`` is a group of hosts defined as a range of IP. It's saved inside the ``hosts`` db: ::

    myrange=iprange
        Description=
        End=192.168.100.20
        Start=192.168.100.10


A zone represents a network zone which can be associated to an interface or a set of IP address. A ``zone`` entry in ``networks`` database can be something like: ::

    name=zone
       Network=CIDR
       Interface=eth0

A configured network interface is automatically a zone.

A service can have a protocol and one or more ports. A ``service`` entry in ``fwservices`` database can be something like: ::

    name=fwservice
       Protocol=TCP/UDP/TCPUDP/ICMP
       Ports=port/port range


Rules based on mac address
--------------------------

It's possible to create rules based on MAC address only using a template-custom.
For example to block internet access to a host on local network using its MAC address: ::

  mkdir -p /etc/e-smith/templates-custom/etc/shorewall/rules
  echo "DROP      loc:~xx-xx-xx-xx-xx-xx          net" > /etc/e-smith/templates-custom/etc/shorewall/rules/90mymac


Where ``xx-xx-xx-xx-xx-xx`` is the MAC address to block.

See :command:`man shorewall-rules` for more information.

Port forwarding
===============

All port-forwards are saved inside the ``portforward`` db.

Each record has:

* ``key``: auto-increment id 
* ``type``: pf
* ``protocol``: tcp/udp  
* ``src``: can be a port number or a range in the form xxxx:yyyy
* ``dst``: can be a port number, if empty the value of ``src`` is used
* ``dstHost``: destination host, can be an IP address or a hos firewall object
* ``allow``: allowed ip address or network, see SOURCE  at http://www.shorewall.net/4.2/manpages/shorewall-rules.html
* ``status``: enabled/disabled
* ``oriDst``: original destination ip, for example alias for a wan interface. If empty, the port forward is valid for all red interface
* ``description``: optional description

NAT 1:1
=======

All NAT one-to-one configurations are stored in ``networks`` db.

Each value is a new attribute for an existing alias key and the name of attribute is ``FwObjectNat`` that contains the reference of an associated host: ::

    eth1:0=alias
        FwObjectNat=host;host_name
        ipaddr=11.11.11.11
        netmask=255.255.255.0
        role=alias

During template-expanding phase, the associated host is mapping with referenced IP and added in shorewall nat configuration. The file is ``/etc/shorewall/nat``. 

More information are available here: http://shorewall.net/NAT.htm


Traffic shaping
================

Traffic shaping is implemented using the Shorewall simple traffic shaping. See: http://www.shorewall.net/simple_traffic_shaping.html

The feature is controlled by ``tc`` property in ``firewall`` key from ``configuration`` db. Possible values are:

* Simple: default
* No: disabled

See TC_ENABLED at http://shorewall.net/manpages/shorewall.conf.html .

All traffic shaping rules are saved inside ``tc`` db.

A record could be of type:

* ``device``: describe an interface
* ``port``: describe a rule for a port
* ``ip``: describe a rule for an ip (or MAC address)
* ``helper``: describe an helper rule (eg. sip)

Device record:

* ``key``: interface name
* ``In``: inbound  bandwidth in kbps
* ``Out``: outbound  bandwidth in kbps
* ``Priority``: traffic priority, default is 2
* ``Description``: optional description

Port record:

* ``key``: port number
* ``Priority``: traffic priority
* ``Proto``: protocol name
* ``Description``: optional description

Ip record:

* ``key``: host object, in the form ``host;<hostname>``
* ``Priority``: traffic priority
* ``Description``: optional description

Helper record:

* ``key``: helper name
* ``Priority``: traffic priority
* ``Description``: optional description

For more information about helpers, see: http://www.shorewall.net/Helpers.html

.. _section-multiwan:

Multi WAN
=========

NethServer firewall can handle 15 red (WAN) interfaces. Implementation uses Shorewall with LSM (Link Status Monitor).
The LSM daemon takes care of monitoring WAN connections (interface) using ICMP traffic and it informs Shorewall about interface up/down events.
Each interface can be checked using multiple IPs (see ``checkip`` property below). At least one IP must be reachable to mark the WAN connection as usable. 
If no IP is specified (recommended option), the system will uses well-known default IPs (Google DNS and OpenDNS).

For each configured provider, LSM will send ping to a configured IP (checkip). 
When a provider status changes, the system will signal a ``wan-uplink-update`` event.

Inside the event, the action ``nethserver-shorewall-wan-update`` invokes:

* shorewall enable <interface> when a red interface is usable
* shorewall disable <interface> then a red interface is not usable

When an interface is disabled, all associated routes will be deleted. 

When a new TCP connection is started, a route is selected and all successive packets will always be routed via same interface. If the used interfaces goes down, the connection is closed.


Actually two behaviors are implemented: balanced and active-backup.

Balanced
---------

All red interfaces are simultaneously used accordingly to the configured weight (see below).

**Example**: 

Given a connection A with weight 2, and connection B with weight 1, the firewall will route a double number of connections via A over B.

Active-backup
-------------

Red interfaces are ordered using the configured weight: higher the weight, higher the route priority.
The interface with maximum weight will be the active connection, all other interfaces will be used if the active one goes down.

**Example**

Given 3 wan connections:

* A with weight 3 
* B with weight 2
* C with weight 1

All traffic is routed via A. On failure of A, all traffic is routed via B. When B goes down, C is used.
Whenever A comes backup, all traffic is again routed through it.

Providers
---------

Providers are an abstraction over red interfaces (see :command:`man shorewall-providers`). 
All providers must have a weight which is used to select the route for packets.

A ``provider`` record inside the ``networks`` database has following properties:

* ``key``: name of provider
* ``interface``: associated red interface, it's mandatory
* ``weight``: weight of connection expressed with an integer number, it's mandatory
* ``Description``: (optional) custom description

Example: ::

  myisp=provider
    interface=eth1
    weight=5
    Description=my fast provider


Multi WAN example
-----------------

1. Configure two interfaces as red, for example eth1 and eth2 

::

  db networks setprop eth1 role red
  db networks setprop eth2 role red
  signal-event interface-update

2. Create two providers: 

::

  db networks set firstisp provider interface eth1 weight 2
  db networks set secondisp provider interface eth2 weight 1

3. Re-configure the firewall: 

::

  signal-event firewall-adjust


See :file:`/var/log/firewall.log` to check for up/down events.

Routes can be checked using: ::

 shorewall show routing

Force traffic to a specific provider
------------------------------------

A mangle rule can route all matched network traffic through a specific provider.
Mangle rules are record of type ``rule`` inside the ``tc`` database.

For example, this rules will route all traffic to port 22 via the provider named myadsl: ::

 1=rule
     Src=192.168.1.0/24
     Dst=0.0.0.0/0
     Service=fwservice;ssh
     Provider=provider;myadsl
     status=enabled
     Position=2
     Description=


Properties:

* ``key``: numeric id
* ``Src``: can be a zone (not interface), host object, ip address or CIDR
* ``Dst``: can be a zone (not interface), host object, ip address or CIDR
* ``Provider``: provider object, in the form of "provider;<name>"
* ``Service``: (optional) can be a service object
* ``status``: can be enabled or disabled. Default is enabled
* ``Position``: integer sorting key
* ``Description``: (optional)

Static routes
=============

Static routes are saved inside the routes database with a record of type static. Example: ::

 8.8.4.4=static
     Description=My route
     Mask=255.255.255.255
     Router=89.97.220.225


Each record has the following properties:

* ``key``: network address
* ``Mask``: network mask
* ``Router``: gateway for the network
* ``Description``: a custom description (optional)

There is also a special type of static route called ``provider-static``.
These routes have the same properties as described above and are used to correctly route traffic for link monitor.
This type of rules should never be manually edited.


