.. _firewall-section:

========
Firewall
========

|product| can act as :index:`firewall` and :index:`gateway` inside the network where it is installed.
All traffic between computers on the local network and the Internet passes through the server that decides how to 
route packets and what rules to apply.
Firewall mode is enabled only if the system has at least one network interface configured with red role.

The Firewall application can be installed from :ref:`software-center-section` and includes:
 
* Multi WAN support up to 15 connections
* Firewall rules management
* Traffic shaping (QoS)
* Port forwarding
* Routing rules to divert traffic on a specific WAN
* Deep packet inspection (DPI)
* Smart search to quickly find existing rules or objects
* Real time charts

Real time charts display traffic and service statistics collected by `Netdata <https://www.netdata.cloud/>`_.
To avoid performance penalty on slow hardware, Netdata is not part of the firewall application and can be installed from :ref:`software-center-section`.

.. _apply_revert-section:

Apply and revert
================

Every time the firewall configuration has been changed, modifications are not applied immediately but saved in a temporary store.
For the changes to take effect, click on the :guilabel:`Apply` button at the top right corner of the page.

As long as the new rules created have not been applied, you can revert all changes by clicking the :guilabel:`Revert` button at the top right corner of the page.

.. _policy-section:

Policy
======

Each interface is identified with a color indicating its role within the system.
See :ref:`network-section`.

When a network packet passes through a firewall zone, the system evaluates a list of rules to decide whether 
traffic should be blocked or allowed. 
:dfn:`Policies` are the default rules to be applied when the network traffic does not match any existing criteria.

Firewall :index:`policies` allow inter-zone traffic accordingly to this schema: ::

 GREEN -> BLUE -> ORANGE -> RED

Traffic is allowed from left to right, blocked from right to left.

To display the list of active policies click on the :guilabel:`Policies` button inside the :guilabel:`Rules` page.

Policies can be changed from :guilabel:`Rules` page to create specific rules between zones and from :guilabel:`Settings` page (to define the default policy for green zones).

.. _firewall-settings-section:

Settings
======
In this section you can change standard firewall behaviour.

Traffic to Internet (red interface)
-----------------------------------

The default firewall policy allows all traffic from green to red interfaces.
To change the default policy for Internet access, enable or disable the :guilabel:`Traffic to Internet (red interface)` option.
If disabled all traffic from green to red network is blocked. Specific traffic can be allowed creating rules from :guilabel:`Rules` page.

Traffic between OpenVPN roadwarrior, OpenVPN tunnels and IPSec tunnels
----------------------------------------------------------------------

By default traffic between different VPN tunnels is not allowed, but sometimes you would need to allow it (e.g. a RoadWarrior client must reach a remote resource behind an IPsec tunnel).
Just enable this option will allow traffic to pass between VPN tunnels, if you need to allow only specific inter-vpn traffic enable this flag and create specific block rules from the :guilabel:`Rules` page.

Ping from Internet
------------------

Allows NethServer to answer icmp requests from internet.

Port forward - Hairpin NAT
--------------------------

Enable hairpin NAT on active port forwarding so that from local zones you can reach the publicly exposed servers by pointing directly to the public ip and not the private ip.
This functionality requires NethServer to have a public IP address on the red interface.
Whenever possible it is recommended to reach the local servers using their local ip and not the public ip, please use a split dns to correctly resolve the name inside the LAN.

Application Level Gateway Enable SIP-ALG
----------------------------------------

Application-level gateway is a security component that augments a firewall or NAT employed in a computer network.
ALG is enabled by default on NethSecurity for many application protocols (like FTP, SIP and so on), allowing them to operate through NAT.
It inspect and rewrite specific network packets and automatically opens required ports.
Since some PBXs may not work properly in the presence of ALG on SIP and H.323 protocols, if you're experiencing audio and call problems with your PBX or VoIP client try to disable SIP-ALG and H.323-ALG with the specific option.


IP/MAC binding
--------------

The firewall can use the list of DHCP reservations to strictly check all traffic generated from hosts inside local networks.
It's not needed for the dhcp service to be enabled, we just need to create reservations thanks to which an ip address is associated with a MAC address.
When :index:`IP/MAC binding` is enabled, the administrator will choose what policy will be applied to hosts without a DHCP reservation.
The common use is to allow traffic only from known hosts and block all other traffic. 
In this case, hosts without a reservation will not be able to access the firewall nor the external network.

To enable traffic only from well-known hosts, follow these steps:

1. Create a DHCP reservation for a host
2. Go to :menuselection:`Firewall rules` page and select from :guilabel:`Configure` from the button menu
3. Select :guilabel:`MAC validation (IP/MAC binding)`
4. Choose :guilabel:`Block traffic` as the policy to apply to unregistered hosts


.. note:: Remember to create at least one DHCP reservation before enabling the IP/MAC binding mode,
   otherwise, no hosts will be able to manage the server using the web interface or SSH.


.. _firewall-rules-section:

Rules
=====

:index:`Rules` apply to all traffic passing through the firewall.
When a network packet moves from one zone to another, the system looks among configured rules. 
If the packet matches a rule, the rule is applied.

.. note:: Rule's order is very important. The system always applies the first rule that matches.

A rule consists of five main parts:

* Action
* Source 
* Destination
* Service (optional)
* Time condition (optional)


Available actions are:

* :dfn:`ACCEPT`: accept the network traffic
* :dfn:`REJECT`: block the traffic and notify the sender host 
* :dfn:`DROP`: block the traffic, packets are dropped and no notification is sent to the sender host

Source and destination fields accept built-in roles, :ref:`firewall_objects-section` and raw IPv4 addresses or CIDR.
Such raw addresses can be later converted to firewall objects using the :guilabel:`Create Host` and
:guilabel:`Create CIDR subnet` actions which will appear next to the address itself.
  
If :ref:`vpn-section` application is installed, there are also two extra zones available:

* *ivpn*: all traffic from IPSec VPNs
* *ovpn*: all traffic from OpenVPN VPNs

The configuration of firewall rules is split into two different pages:

* **Rules**: manage rules applied only to the network traffic traversing the firewall.
* **Local rules**: manage rules applied only to the network traffic generated from the firewall, 
  or directed to the firewall itself.

When creating new rules, only the most common fields are shown. To show other less common parameters click the :guilabel:`Advanced` label.

.. note:: If no red interface has been configured, the firewall will not generate rules for blue and orange zones.

REJECT vs DROP
--------------

As a general rule, you should use :index:`REJECT` when you want to inform the source host that the port which it 
is trying to access is closed. 
Usually, the rules on the LAN side can use REJECT.

For connections from the Internet, it is recommended to use :index:`DROP`, in order to minimize the information disclosed to any 
attacker.

Log
---

When a rule matches the ongoing traffic, it's possible to register the event on a log file by checking the option from the web interface.
:index:`Firewall log` is saved in :file:`/var/log/firewall.log` file.
The log can be inspected from the command line or using the :guilabel:`Logs` page.

Deep Packet Inspection (DPI)
----------------------------

Deep Packet Inspection (`DPI <https://en.wikipedia.org/wiki/Deep_packet_inspection>`_) is an advanced packet filtering technique.

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
  often begins after the connection has been already established, so the routing decision can't be changed

Even if DPI can identify traffic to/from specific web sites such as Facebook,
it is better suited to block or shape protocols like VPN, FTP, etc.
Web site access should be regulated using :ref:`proxy-section`.

Note that some DPI protocols (such as Amazon) can match large `CDNs <https://it.wikipedia.org/wiki/Content_Delivery_Network>`_,
so please do not block such protocols using DPI rules unless you want to prevent access to thousands of sites.

DPI markers are automatically applied also to the traffic
which originates from the firewall itself, like HTTP traffic from the web proxy.

The complete list of DPI protocols, along with counters for matched traffic, is available inside the :guilabel:`DPI` page
under the :menuselection:`Status` category on the left menu.

Rules on existing connections
-----------------------------

When a new rule is created, as default, it is applied only to new connections.
But in some scenarios, the administrator may need to apply the rule also on established connections.

If the option :guilabel:`Apply to existing connections` is enabled, the rule will be applied to all connections including already established ones.


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

.. _wan-section:

WAN
===

The term :dfn:`WAN` (Wide Area Network) refers to a public network outside the server, usually connected to the Internet. 
A :dfn:`provider` is the company that actually manages the :index:`WAN` link.

All WAN network interfaces are labeled with the red role and are listed on the top of the page, just below bandwidth usage charts.
Rules can be created under the :guilabel:`Rules` section on the same page.

If the server has two or more configured red interfaces, it is required to correctly fill, 
:guilabel:`Download bandwidth` and :guilabel:`Upload bandwidth` fields from the :guilabel:`Network` page.
Download and upload bandwidth can be automatically calculated using the :guilabel:`Speedtest` button.

Each provider represents a WAN connection and is associated with a network adapter. 
Each provider defines a :dfn:`weight`: the higher the weight, the higher the priority of the network card associated with the provider. 

The system can use WAN connections in two modes: 

* :dfn:`Balance`: all providers are used simultaneously according to their weight 
* :dfn:`Active backup`: providers are used one at a fly from the one with the highest weight. If the provider you are using loses its connection, all traffic will be diverted to the next provider.

To determine the status of a provider, the system sends an ICMP packet (ping) at regular intervals.
If the number of dropped packets exceeds a certain threshold, the provider is disabled.

The administrator can configure the sensitivity of the monitoring through the following parameters:

* Percentage of lost packets
* Number of consecutive lost packets
* Interval in seconds between sent packets

To change WAN mode and link monitoring options click on :guilabel:`Configure` button.

The network traffic can be routed to specific WANs by creating rules inside the :guilabel:`Rules` section on this page.
After creating or editing rules, make sure to apply the changes. See :ref:`<apply_revert-section>` for details.


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
For example, if a web server is running inside the LAN, only computers on the local network can access the service in the green zone. 
Any request made by a user outside the local network is blocked. 

To allow any external user access to the web server you must create a :dfn:`port forward`.
A :index:`port forward` is a rule that allows limited access to resources from outside of the LAN. 

When you configure the server, you must choose the listening ports. The traffic from red interfaces will be redirected to selected ports.
In the case of a web server, listening ports are usually port 80 (HTTP) and 443 (HTTPS). 

When you create a port forward, you must specify at least the following parameters: 

* The source port
* The destination port, which can be different from the origin port
* The network protocol like TCP, UDP, TCP & UDP, AH, ESP or GRE
* The address of the internal host to which the traffic should be redirected
* It's possible to specify a port range using a colon as the separator in the source port field (eg: 1000:2000), in this case, the destination port field must be left empty

Port forwards are grouped by destination host and support raw IP addresses along with firewall objects.

By default, all port forwards are available only for hosts inside the WAN.
Check the :guilabel:`Enable hairpin NAT` option under the :guilabel:`Settings` page to make all port forwards available also from local networks.


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

All incoming traffic on the firewall's red interfaces on port 80, will be redirected to port 80 on Server1.

In case you want to make accessible from outside the SSH server on port 2222, you will have to create a port forward like this:

* origin port: 2222
* destination port: 22
* host address: 192.168.1.10

All incoming traffic on the firewall's red interfaces on port 2222, will be redirected to port 22 on Server1.
 
In case you want to make accessible from outside the server on the whole port range between 5000 and 6000, you will have to create a port forward like this:

* origin port: 5000:6000
* destination port: 
* host address: 192.168.1.10

All incoming traffic on the firewall's red interfaces on the port range between 5000 and 6000 will be redirected to the same ports on Server1.

Limiting access
---------------

By default, the field access to port forward is granted to anyone.
You can restrict access to port forward only from some IP addresses or networks by adding entries to :guilabel:`Restrict access to` field.
This configuration is useful when services should be available only from trusted IPs or networks. 

Example of valid entries:

* ``10.2.10.4``: enable port forward for traffic coming from 10.2.10.4 IP
* ``10.2.10.0/24``: enable port forward only for traffic coming from 10.2.10.0/24 network

.. _snat-section:

SNAT 1:1
========

One-to-one :index:`source NAT` (:index:`SNAT`) is a way to make systems behind a firewall and configured with private IP addresses appear to have public IP addresses.
If you have a bunch of public IP addresses and if you want to associate one of these to a specific network host, :index:`NAT 1:1` is the way.
SNAT is available only if there is at least one IP alias configured on red network interfaces.

This feature only applies to network traffic from a host inside the local network to the public Internet.
It does not affect in any way the traffic from the Internet toward the alias IP. If you need to route some specific traffic to the internal host use the port forward as usual.

If you need to route all traffic to the internal host (not recommended!) use a port forward with protocol TCP & UDP and source port 1:65535.


Example
-------

In our network we have a host called ``example_host`` with IP ``192.168.5.122``. We have also associated a public IP address ``89.95.145.226`` as an alias of ``eth0`` interface (``RED``).

We want to map our internal host (``example_host`` - ``192.168.5.122``) with public IP ``89.95.145.226``.

In the :guilabel:`NAT 1:1` panel, we choose for the IP ``89.95.145.226`` (read-only field) the specific host (``example_host``) from the combo-box. We have configured correctly the one-to-one NAT for our host.

.. _traffic-shaping-section:

Traffic shaping
===============

:index:`Traffic shaping` allows applying priority rules on network traffic through the firewall. 
In this way, it is possible to optimize the transmission, control the latency and tune 
the available bandwidth. 

To enable traffic shaping it is necessary to know the exact amount of available download and upload bandwidth.
Access the :guilabel:`Network` page and carefully set bandwidth values.

If download and upload bandwidth are not set for a red interface, traffic shaping rules will not be
enabled for that interface.

.. note::

   Be sure to specify an accurate estimate of the bandwidth on network interfaces.
   To pick an appropriate setting, please do not trust the nominal value,
   but use the :guilabel:`Speedtest` button or online tools to test the real provider speed.

   In case of congestion by the provider, there is nothing to do in order to improve performance.


Traffic shaping classes are used to commit bandwidth for specific network traffic.
Configuration of traffic shaping is composed of 2 steps:

* creation of traffic shaping classes
* assignment of network traffic to a specific class

Classes
-------

Traffic shaping is achieved by controlling how bandwidth is allocated to classes.

Each class can have a reserved rate. A reserved rate is the bandwidth a class will get only when it needs it.
The spare bandwidth is the sum of not committed bandwidth, plus the committed bandwidth of a class but 
not currently used by the class itself.

Each class can have also a maximum rate. If set, the class can exceed its committed rate, up to the maximum rate.
A class will exceed its committed rate only if there is spare bandwidth available.

Traffic shaping classes can be defined under :guilabel:`Traffic shaping` page.
When creating a new class, fill the following fields.

* :guilabel:`Class name`: a representative name
* :guilabel:`Description`: optional description for the class

Limits under :guilabel:`Download bandwidth limits` section:

  * :guilabel:`Min`: minimum reserved download bandwidth, if empty no download reservation will be created
  * :guilabel:`Max`: maximum allowed download bandwidth, if empty no upper limit will be set

Limits under :guilabel:`Upload bandwidth limits` section:

  * :guilabel:`Min`:  minimum reserved upload bandwidth, if empty no upload reservation will be created
  * :guilabel:`Max`: maximum allowed download bandwidth, if empty no upper limit will be created


For each class the bandwidth can be specified using the percentage of available network bandwidth or
with absolutes values expressed in kbps.
As default, a traffic shaping class is applied to all red network interfaces.
Such behavior can be changed by selecting an existing red interfaces under the :guilabel:`Bind to` menu
inside the :guilabel:`Advanced` section.

The system provides two pre-configured classes:

- :guilabel:`high`: generic high priority traffic, can be assigned to something like SSH
- :guilabel:`low`: low priority traffic, can be assigned to something like peer to peer file exchange

The system always tries to prevent traffic starvation under high network load.

Classes will get spare bandwidth proportionally to their committed rate.
So if class A has 1Mbit committed rate and class B has 2Mbit committed rate, class B will get twice the spare bandwidth of class A.
In all cases, all spare bandwidth will be given to them.

Network traffic can be shaped by creating rules under the :guilabel:`Rules` section in this page.
After creating or editing rules, make sure to :ref:`apply <apply_revert-section>` the changes.

For more info, see `FireQOS tutorial <https://github.com/firehol/firehol/wiki/FireQOS-Tutorial>`_.


.. _firewall_objects-section:

Firewall objects
================

:index:`Firewall objects` are representations of network components and are useful to simplify the creation 
of rules. 

There are 6 types of objects, 5 of them represent sources and destinations:

* **Host**: representing local and remote computers. Example: ``web_server``, ``goofy_pc``

* **Groups of hosts**: representing homogeneous groups of computers. Hosts in a host group should always be reachable using the same interface.
  Example: ``servers``, ``router``

* **IP ranges**: a list of IP addresses expressed as a range. Example: ``myrange``, composed by IPs from ``192.168.1.100`` to ``192.168.1.120``

* **CIDR Networks**: you can express a CIDR network in order to simplify firewall rules.
  
  Example 1 : last 14 IP addresses of the network are assigned to servers (``192.168.0.240/28``).
  Example 2 : you have multiple green interfaces but you want to create firewall rules only for one green (``192.168.2.0/24``).

.. index:: zone

* **Zone**: representing networks of hosts, they must be expressed in CIDR notation. Their intended usage is for defining a part of a network with different firewall rules from those of the nominal interface. They are used for very specific needs.

  .. note:: By default, all hosts belonging to a zone are not allowed to do any type of traffic. It's necessary to create all the rules on the firewall in order to obtain the desired behavior.

.. index:: time conditions

* **Time conditions**: can be associated to firewall rules to limit their effectiveness to a given period of time.

  .. note::
    Rules which have time conditions are enforced only for new connections. 
    Example: if you are blocking HTTP connections from 09:00 to 18:00, connections established 
    before 09:00 will be allowed until closed. Any new connection after 09:00 will be dropped.


* **Services**: a service listening on a host with at least one port and protocol. Example: ``ssh``, ``https``

.. index:: mac address

* **MAC addresses**: a host identified by a MAC address. The MAC address must be bound to an existing zone.


When creating rules, you can use the records defined in :ref:`dns-section` and :ref:`dhcp-section` like host objects.
In addition, each network interface with an associated role is automatically listed among the available zones.



.. _firewall_connections-section:

Connections
===========

This page keeps track of all active connections.
Connections can be filter by :guilabel:`Protocol` and :guilabel:`State`.
The list of connections is not refreshed in real time. To list new connections click the :guilabel:`Refresh` button.

The administrator can delete a single connection or flush the whole connection tracking table using :guilabel:`Delete all connections` button.
