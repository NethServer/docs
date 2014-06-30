.. _network-section:

=======
Network
=======

:index:`Network` configuration tells the system how the server is connected to local network (LAN) or public ones (Internet).

If the server has firewall and gateway functionality, it will handle extra networks with special function like 
DMZ (DeMilitarized Zone) and guests network.

|product| supports an unlimited number of network interfaces.
Any network managed by the system must follow these rules:

* networks must be physically separated (multiple networks can't be connected to the same switch/hub)
* networks must be logically separated: each network must have different addresses
* private networks, like LANs, must follow address's convention from RFC1918 document.
  See :ref:`RFC1918-section`

Every network interface as a specific role which determinates its behavior. Roles are identified by colors.
Each role correspond to a well-known zone with special network traffic rules:

* *green*: local network. Hosts on this network can access any other configured network
* *blue*: guests network. Hosts on this network can access orange and red network, but can't access to green zone
* *orange*: DMZ network.  Hosts on this network can access red networks, but can't access to blue, orange and green zones
* *red*: public network. Hosts on this network can access only the server itself

See :ref:`policy-section` for more information on roles and firewall rules.

.. note:: The server must have at least one network interface. When the server has only one interface, this interface must have green role.

If the server i installed on a public VPS (Virtual Private Server) public, it should must be configured with a green interface.
All critical services should be closed using :ref:`network_services-section` panel.


.. _network_services-section:

Network services
================

A :index:`network service` is a service running on the firewall itself.

These services are always available to hosts on green network (local network).
Access policies can be modified from :guilabel:`Network services` page.

Available policies are:

* Access only from local networks (private): all hosts from green network and from VPNs
* Access from any network (public): any hosts
* Access only from the server itself (none): no host can connect to selected service

If policies private or public are selected, it's possible to add a specific host (or a host list) always allowed (or blocked).


.. _RFC1918-section:

Address for private networks (RFC1918)
========================================

TCP/IP private networks not directly connected to Internet should use special addresses selected by 
Internet Assigned Numbers Authority (IANA).

===============   ===========   =============================
Private network   Subnet mask   IP addresses interval
===============   ===========   =============================
10.0.0.0          255.0.0.0     10.0.0.1 - 10.255.255.254
172.16.0.0        255.240.0.0   172.16.0.1 - 172.31.255.254
192.168.0.0       255.255.0.0   192.168.0.1 - 192.168.255.254
===============   ===========   =============================

