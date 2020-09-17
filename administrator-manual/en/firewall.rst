.. _firewall-section:

=====================
Firewall and gateway
=====================

.. note:: A new Server Manager based on Cockpit is available. See :ref:`firewall_new-section`.

|product| can act as :index:`firewall` and :index:`gateway` inside the network where is installed.
All traffic between computers on the local network and the Internet passes through the server that decides how to 
route packets and what rules to apply.
 
Main features:

* Advanced network configuration (bridge, bonds, alias, etc)
* Multi WAN support (up to 15)
* Firewall rules management
* Traffic shaping (QoS)
* Port forwarding
* Routing rules to divert traffic on a specific WAN
* Intrusion Prevention System (IPS)
* Deep packet inspection (DPI)


Firewall and gateway modes are enabled only if:

* the `nethserver-firewall-base` package is installed
* at least there is one network interface configured with red role

.. _policy-section:

Policy
======

Each interface is identified with a color indicating its role within the system.
See :ref:`network-section`.

When a network packet passes through a firewall zone, the system evaluates a list of rules to decide whether 
traffic should be blocked or allowed. 
:dfn:`Policies` are the default rules to be applied when the network traffic does not match any existing criteria.

The firewall implements two default policies editable from the page :menuselection:`Firewall rules` -> :guilabel:`Configure`:

* :dfn:`Allowed`: all traffic from green to red is allowed
* :dfn:`Blocked`: all traffic from green to red network is blocked. Specific traffic must be allowed with custom rules.

Firewall :index:`policies` allow inter-zone traffic accordingly to this schema: ::

 GREEN -> BLUE -> ORANGE -> RED

Traffic is allowed from left to right, blocked from right to left.

You can create rules between zones to change default policies from :guilabel:`Firewall rules` page.

.. note::  Traffic from local network to the server on SSH port (default 22) and Server Manager port (default 980) is **always** permitted.

.. _firewall-rules-section:

Rules
=====

:index:`Rules` apply to all traffic passing through the firewall.
When a network packet moves from one zone to another, the system looks among configured rules. 
If the packet match a rule, the rule is applied.

.. note:: Rule's order is very important. The system always applies the first rule that matches.

A rule consists of five main parts:

* Action
* Source 
* Destination
* Service
* Time condition


Available actions are:

* :dfn:`ACCEPT`: accept the network traffic
* :dfn:`REJECT`: block the traffic and notify the sender host 
* :dfn:`DROP`: block the traffic, packets are dropped and no notification is sent to the sender host
* :dfn:`ROUTE`: route the traffic to the specified WAN provider. See :ref:`multi-wan-section`.
* :dfn:`Priority`: mark the traffic as high/low priority. See :ref:`traffic-shaping-section`.

.. note:: The firewall will not generate rules for blue and orange zones, if at least a red interface is configured.

REJECT vs DROP
--------------

As a general rule, you should use :index:`REJECT` when you want to inform the source host that the port to which it 
is trying to access is closed. 
Usually the rules on the LAN side can use REJECT. 

For connections from the Internet, it is recommended to use :index:`DROP`, in order to minimize the information disclosure to any 
attackers.

Log
---

When a rule matches the ongoing traffic, it's possible to register the event on a log file by checking the option from the web interface.
:index:`Firewall log` is saved in :file:`/var/log/firewall.log` file.

Deep Packet Inspection (DPI)
----------------------------

Deep Packet Inspection (DPI) [#DPI]_ is an advanced packet filtering technique.

When the :index:`DPI` module is active, new items for the :guilabel:`Service`
field are available in the :guilabel:`Edit rule` form. Those items are
labeled *DPI protocol*, among the usual *network service* and *service object*
items.

The DPI module uses the `nDPI library <https://www.ntop.org/products/deep-packet-inspection/ndpi/>`_
which can identify around 250 types of network traffic split in network protocols
(eg. OpenVPN, DNS) and web applications (eg. Netflix, Spotify).

Firewall rules using DPI services are generated inside the mangle table, for this reason
such rules have some limitations:

- `reject` action is not supported, use `drop` to block traffic
- `any` and `firewall` can't be used as source or destination
- `route to provider X` action is not supported: the identification of the protocol
  often begins after the connection has been already established, so routing decision can't be changed

Even if DPI can identify traffic to/from specific web sites such as Facebook,
it is better suited to block or shape protocols like VPN, FTP, etc.
Web site access should be regulated using :ref:`proxy-section`.

Note that some DPI protocols (such as Amazon) can match large `CDNs <https://it.wikipedia.org/wiki/Content_Delivery_Network>`_,
so please do not block such protocols using DPI rules unless you want to prevent access to thousands of sites.

DPI markers are automatically applied also to the traffic
which originates from the firewall itself, like HTTP traffic from the web proxy.

The complete list of DPI protocols, along with counters for matched traffic, is available inside the :guilabel:`DPI` page
under the :menuselection:`Status` category on the left menu.

.. [#DPI] Deep Packet Inspection https://en.wikipedia.org/wiki/Deep_packet_inspection

Rules on existing connections
-----------------------------

When a new rules is created, as default, it is applied only to new connections.
But in some scenarios the administrator may need to apply the rule also on established connections.

If the option :guilabel:`Apply to existing connections` is enabled, the rule will be applied to all connections including already established ones.

.. note::
   This option is available only inside the new Server Manager. See :ref:`firewall_new-section`.

Examples
--------

Below there are some examples of rules. 

Block all DNS traffic from the LAN to the Internet: 

* Action: REJECT 
* Source: green 
* Destination: red 
* Service: DNS (UDP port 53) 

Allow guest's network to access all the services listening on Server1: 

* Action: ACCEPT 
* Source: blue 
* Destination: Server1 
* Service: -

.. _multi-wan-section:

Multi WAN
=========

The term :dfn:`WAN` (Wide Area Network) refers to a public network outside the server, usually connected to the Internet. 
A :dfn:`provider` is the company who actually manage the :index:`WAN` link.

The system supports up to 15 WAN connections. 
If the server has two or more configured red cards, it is required to correctly fill :guilabel:`Link weight`, 
:guilabel:`Inbound bandwidth` and :guilabel:`Outbound bandwidth` fields from the :guilabel:`Network` page. 

Each provider represents a WAN connection and is associated with a network adapter. 
Each provider defines a :dfn:`weight`: higher the :index:`weight`, higher the priority of the network card associated with the provider. 

The system can use WAN connections in two modes (button  :guilabel:`Configure` on page :menuselection:`Multi WAN`): 

* :dfn:`Balance`: all providers are used simultaneously according to their weight 
* :dfn:`Active backup`: providers are used one at a fly from the one with the highest weight. If the provider you are using loses its connection, all traffic will be diverted to the next provider.

To determine the status of a provider, the system sends an ICMP packet (ping) at regular intervals.
If the number of dropped packets exceeds a certain threshold, the provider is disabled.

The administrator can configure the sensitivity of the monitoring through the following parameters:

* Percentage of lost packets
* Number of consecutive lost packets
* Interval in seconds between sent packets

The :guilabel:`Firewall rules` page allows to route network packets to
a   given   WAN   provider,   if    some   criteria   are   met.   See
:ref:`firewall-rules-section`.


Example
-------

Given two configured providers:

* Provider1: network interface eth1, weight 100
* Provider2: network interface eth0, weight 50

If balanced mode is selected, the server will route a double number of connections on Provider1 over Provider2.

If active backup mode is selected, the server will route all connections on Provider1; only if Provider1 becomes
unavailable the connections will be redirected to Provider2.

.. _port_forward-section:

Port forward
============

The firewall blocks requests from public networks to private ones. 
For example, if web server is running inside the LAN, only computers on the local network can access the service on the green zone. 
Any request made by a user outside the local network is blocked. 

To allow any external user access to the web server you must create a :dfn:`port forward`.
A :index:`port forward` is a rule that allows limited access to resources from outside of the LAN. 

When you configure the server, you must choose the listening ports. The traffic from red interfaces will be redirected to selected ports.
In the case of a web server, listening ports are usually port 80 (HTTP) and 443 (HTTPS). 

When you create a port forward, you must specify at least the following parameters: 

* The source port
* The destination port, which can be different from the origin port
* The address of the internal host to which the traffic should be redirected
* It's possible to specify a port range using a colon as separator in the source port field (eg: 1000:2000), in this case the field destination port must be left void

Example
-------

Given the following scenario:

* Internal server with IP 192.168.1.10, named Server1
* Web server listening on port 80 on Server1
* SSH server listening on port 22 on Server1
* Other services in the port range between 5000 and 6000  on Server1

If you want to make the web server available directly from public networks, you must create a rule like this:

* origin port: 80
* destination port: 80
* host address: 192.168.1.10

All incoming traffic on firewall's red interfaces on port 80, will be redirected to port 80 on Server1.

In case you want to make accessible from outside the SSH server on port 2222, you will have to create a port forward like this:

* origin port: 2222
* destination port: 22
* host address: 192.168.1.10

All incoming traffic on firewall's red interfaces on port 2222, will be redirected to port 22 on Server1.
 
In case you want to make accessible from outside the server on the whole port range between 5000 and 6000, you will have to create a port forward like this:

* origin port: 5000:6000
* destination port: 
* host address: 192.168.1.10

All incoming traffic on firewall's red interfaces on port range between 5000 and 6000 will be redirected to same ports on Server1.

Limiting access
---------------

You can restrict access to port forward only from some IP address or networks using the field :guilabel:`Allow only from`.

This configuration is useful when services should be available only from trusted IP or networks.
Some possible values:

* ``10.2.10.4``: enable port forward for traffic coming from 10.2.10.4 IP
* ``10.2.10.4,10.2.10.5``: enable port forward for traffic coming from 10.2.10.4 and 10.2.10.5 IPs
* ``10.2.10.0/24``: enable port forward only for traffic coming from 10.2.10.0/24 network
* ``!10.2.10.4``: enable port forward  for all IPs except 10.2.10.4
* ``192.168.1.0/24!192.168.1.3,192.168.1.9``: enable port forward for 192.168.1.0/24 network, except for hosts 192.168.1.3 and 192.168.1.9

.. _snat-section:

sNAT 1:1
========

One-to-one NAT is a way to make systems behind a firewall and configured with private IP addresses appear to have public IP addresses.

If you have a bunch of public IP addresses and if you want to associate one of these to a specific network host, :index:`NAT 1:1` is the way.

This feature only applies to traffic from the network specific host to internet.

It doesn't affect in any way the traffic from internet toward the Alias IP, if you need to route some specific traffic to the internal host use the port forward as usual.

If you need to route all traffic to the internal host (not recommended!) use a port forward with protocol TCP & UDP and source port 1:65535.


Example
-------

In our network we have an host called ``example_host`` with IP ``192.168.5.122``. We have also associated a public IP address ``89.95.145.226`` as an alias of ``eth0`` interface (``RED``).

We want to map our internal host (``example_host`` - ``192.168.5.122``) with public IP ``89.95.145.226``.

In the :guilabel:`NAT 1:1` panel, we choose for the IP ``89.95.145.226`` (read-only field) the specific host (``example_host``) from the combo-box. We have configured correctly the one-to-one NAT for our host.

.. _traffic-shaping-section:

Traffic shaping
===============

:index:`Traffic shaping` allows to apply priority rules on network traffic through the firewall. 
In this way it is possible to optimize the transmission, check the latency and tune 
the available bandwidth. 

To enable traffic shaping it is necessary to know the exact amount of available download and upload bandwidth.
Access the :guilabel:`Network` page and carefully set bandwidth values.

If download and upload bandwidth are not set for a red interface, traffic shaping rules will not be
enabled for that interface.

.. note::

   Be sure to specify an accurate estimate of the bandwidth on network interfaces.
   To pick an appropriate setting, please do not trust the nominal value,
   but use online tools to test the real provider speed.

   In case of congestion by the provider, there is nothing to do in order to improve performance.


Configuration of traffic shaping is composed by 2 steps:

- creation of traffic shaping classes
- assignment of network traffic to a specific class

Classes
-------

Traffic shaping is achieved by controlling how bandwidth is allocated to classes.

Each class can have a reserved rate. A reserved rate is the bandwidth a class will get only when it needs it.
The spare bandwidth is the sum of not committed bandwidth, plus the committed bandwidth of a class but 
not currently used by the class itself.

Each class can have also a maximum rate. If set, the class can exceed its committed rate, up to the maximum rate.
A class will exceed its committed rate only if there is spare bandwidth available.

Traffic shaping classes can be defined under :guilabel:`Traffic shaping` page.
When creating a new class, fill the following fields:

* :guilabel:`Class name`: a representative name
* :guilabel:`Min download (%)`: minimum reserved download bandwidth, if empty no download reservation will be created
* :guilabel:`Max download (%)`: maximum allowed download bandwidth, if empty no upper limit will be set
* :guilabel:`Min upload (%)`:  minimum reserved upload bandwidth, if empty no upload reservation will be created
* :guilabel:`Max upload (%)`: maximum allowed download bandwidth, if empty no upper limit will be created
* :guilabel:`Description`: optional description for the class

The system provides two pre-configured classes:

- :guilabel:`high`: generic high priority traffic, can be assigned to something like SSH
- :guilabel:`low`: low priority traffic, can be assigned to something like peer to peer file exchange


The system always tries to prevent traffic starvation under high network load.

Classes will get spare bandwidth proportionally to their committed rate.
So if class A has 1Mbit committed rate and class B has 2Mbit committed rate, class B will get twice the spare bandwidth of class A.
In all cases all spare bandwidth will be given to them.


For more info, see [#]_ .

.. _firewall_objects-section:

Firewall objects
================

:index:`Firewall objects` are representations of network components and are useful to simplify the creation 
of rules. 

There are 6 types of objects, 5 of them represent sources and destinations:

* Host: representing local and remote computers. Example: web_server, pc_boss 
* Groups of hosts: representing homogeneous groups of computers. Hosts in a host group should always be reachable using the same interface.
  Example: servers, pc_segreteria 
* CIDR Networks: You can express a CIDR network in order to simplify firewall rules.
  
  Example 1 : last 14 IP address of the network are assigned to servers (192.168.0.240/28).

  Example 2 : you have multiple green interfaces but you want to create firewall rules only for one green (192.168.2.0/24).

.. index:: zone

* Zone: representing networks of hosts, they must be expressed in CIDR notation. Their usage is for defining a part of a network with different firewall rules from those of the nominal interface. They are used for very specific needs.

.. note:: By default, all hosts belonging to a zone are not allowed to do any type of traffic. It's necessary to create all the rules on the firewall in order to obtain the desired behavior.

.. index:: time conditions

* Time conditions: can be associated to firewall rules to limit their effectiveness to a given period of time.

  .. note::

  Rules which have time conditions are enforced only for new connections. 
  Example: if you are blocking HTTP connections from 09:00 to 18:00, connections established 
  efore 09:00 will be allowed until closed. Any new connection after 09:00 will be dropped.


* Services: a service listening on a host with at least one port and protocol. Example: ssh, https 

.. index:: mac address

* MAC addresses: an host indentified by a MAC address. The MAC address must be bound to an existing zone.

  
When creating rules, you can use the records defined in :ref:`dns-section` and :ref:`dhcp-section` like host objects.
In addition, each network interface with an associated role is automatically listed among the available zones.


IP/MAC binding
==============

When the system is acting as DHCP server, the firewall can use the list of DHCP reservations to strictly check
all traffic generated from hosts inside local networks.
When :index:`IP/MAC binding` is enabled, the administrator will choose what policy will be applied to hosts without a DHCP reservation.
The common use is to allow traffic only from known hosts and block all other traffic. 
In this case, hosts without a reservation will not be able to access the firewall nor the external network.

To enable traffic only from well-known hosts, follow these steps:

1. Create a DHCP reservation for a host
2. Go to :menuselection:`Firewall rules` page and select from :guilabel:`Configure` from the button menu
3. Select :guilabel:`MAC validation (IP/MAC binding)`
4. Choose :guilabel:`Block traffic` as policy to apply to unregistered hosts


.. note:: Remember to create at least one DHCP reservation before enabling the IP/MAC binding mode,
   otherwise no hosts will be able to manage the server using the web interface or SSH.

.. [#]
   FireQOS tutorial:
   https://github.com/firehol/firehol/wiki/FireQOS-Tutorial
