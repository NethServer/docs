.. _firewall-section:

=====================
Firewall and gateway
=====================

|product| can act as :index:`firewall` and :index:`gateway` inside the network where is installed.
All traffic between computers on the local network and the Internet passes through the server that decides how to 
route packets and what rules to apply.
 
Main features:

* Advanced network configuration (bridge, bonds, alias, etc)
* Multi WAN support (up to 15)
* Firewall rules management
* Traffic shaping (QoS)
* Port forwarding
* Routeing rules to divert traffic on a specific WAN
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

A rule consists of four main parts:

* Action: action to take when the rule applies
* Source: 
* Destination: 
* Service: 
* Time condition:


Available actions are:

* :dfn:`ACCEPT`: accept the network traffic
* :dfn:`REJECT`: block the traffic and notify the sender host 
* :dfn:`DROP`: block the traffic, packets are dropped and no notification is sent to the sender host
* :dfn:`ROUTE`: route the traffic to the specified WAN provider. See :ref:`multi-wan-section`.

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

The Deep Packet Inspection (DPI) [#DPI]_ is an advanced packet filtering technique.
On |product| it requires a customised Linux kernel with the additional ``xt_ndpi``
module that can be installed from the :guilabel:`Software Center` page.

.. warning:: Once the module is installed the system must be rebooted. The newly
             installed kernel is selected by default.

If the DPI module is correctly loaded, new items for the :guilabel:`Service`
field are available in the :guilabel:`Edit rule` form. Those items are
labeled *DPI protocol*, among the usual *network service* and *service object*
items.

The complete list of available DPI protocols can be obtained with the following
command: ::

    db NethServer::Database::Ndpi keys

.. [#DPI] Deep Packet Inspection https://en.wikipedia.org/wiki/Deep_packet_inspection

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
If the server has two or more configured red cards, it is required to proceed with :index:`provider` configuration from :guilabel:`Multi WAN` page. 

Each provider represents a  WAN connection and is associated with a network adapter. 
Each provider defines a  :dfn:`weight`: higher the :index:`weight`, higher the priority of the network card associated with the provider. 

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
* It's possibile to specify a port range using a colon as separator in the source port field (eX: 1000:2000), in this case the field destination port must be left void

Example
-------

Given the following scenario:

* Internal server with IP 192.168.1.10, named Server1
* Web server listening on port 80 on Server1
* SSH server listening on port 22 on Server1
* Other services in the port range beetween 5000 and 6000  on Server1

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
 
In case you want to make accessible from outside the server on the whole port range beetween 5000 and 6000, you will have to create a port forward like this:

* origin port: 5000:6000
* destination port: 
* host address: 192.168.1.10

All incoming traffic on firewall's red interfaces on port range beetween 5000 and 6000 will be redirected to same ports on Server1.

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

NAT 1:1
=======

One-to-one NAT is a way to make systems behind a firewall and configured with private IP addresses appear to have public IP addresses.

If you have a bunch of public IP addresses and if you want to associate one of these to a specific network host, :index:`NAT 1:1` is the way.

Example
-------

In our network we have an host called ``example_host`` with IP ``192.168.5.122``. We have also associated a public IP address ``89.95.145.226`` as an alias of ``eth0`` interface (``RED``).

We want to map our internal host (``example_host`` - ``192.168.5.122``) with public IP ``89.95.145.226``.

In the :guilabel:`NAT 1:1` panel, we choose for the IP ``89.95.145.226`` (read-only field) the specific host (``example_host``) from the combo-box. We have configured correctly the one-to-one NAT for our host.


Traffic shaping
===============

:index:`Traffic shaping` allows to apply priority rules on network traffic through the firewall. 
In this way it is possible to optimize the transmission, check the latency and tune 
the available bandwidth. 

To enable traffic shaping it is necessary to know the amount of available bandwidth in both directions 
and fill in the fields indicating the speed of the Internet link. Be aware 
that in case of congestion by the provider there is nothing to do in order to improve performance. 

Traffic shaping can be configured from the page :menuselection:`Traffic shaping` -> :guilabel:`Interface rules`.

The system provides three levels of priority, high, medium and low: as default all traffic has medium priority.
It is possible to assign high or low priority to certain services based on the port used (eg low traffic peer to peer). 

The system works even without specifying  services to high or low priority, 
because, by default, the interactive traffic is automatically run at high priority 
(which means, for example, it is not necessary to specify ports for VoIP traffic or SSH). 
Even the traffic type PING is guaranteed high priority. 


.. note:: Be sure to specify an accurate estimate of the bandwidth on network interfaces.


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

* *Zone*: representing networks of hosts, they must be expressed in CIDR notation. Their usage is for defining a part of a network with different firewall rules from those of the nominal interface. They are used for very specific needs.

.. note:: By default, all hosts belonging to a zone are not allowed to do any type of traffic. It's necessary to create all the rules on the firewall in order to obtain the desired behavior.

.. index:: time conditions

* Time conditions: can be associated to firewall rules to limit their effectiveness to a given period of time.

The last type of object is used to specify the type of traffic:

* Services: a service listening on a host with at least one port and protocol. Example: ssh, https 

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

