.. _base_system-section:

===========
Base system
===========

This chapter describes all available modules at the end of installation.
All modules outside this section must be installed from :ref:`package_manager-section`, including
backup and users support.

.. _dashboard-section:

Dashboard
=========

The index:`Dashboard` page is the landing page after a successful login.
The page will display the :index:`status` and configurations of the system.

.. _network-section:

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

.. _logical_interfaces-section:

Logical interfaces
------------------

Supported logical interfaces are:

* :index:`alias`: associate more than one IP address to an existing network interface. 
  The alias has the same role of its associated physical interface
* :index:`bond`: arrange two or more network interfaces, provides load balancing and fault tolerance
* :index:`bridge`: connect two different networks, it's often used for bridged VPN and virtual machine
* :index:`vlan` (Virtual Local Area Network): create two or more physically separated networks using a single interface

Aliases are used to configure multiple IPs on a single NIC. For example, if you want to have more public IP on a
red interface.

Bonds allow you to aggregate bandwidth between two or more network interfaces. The system will use all network interfaces
at the same time, balancing traffic among all active interfaces.
If an error occurs, the faulty card is automatically excluded from the bond.

Bridge has the function to connect different network segments, for example by allowing virtual machines, or client connected using a VPN,
to access to the local network (green).

When it is not possible to physically separate two different networks, you can use tagged vlan. The traffic of the two networks can
be transmitted on the same cable, but it will be handled as if it were sent and received on separate network cards.
The use of VLAN, requires properly configured switches.

.. _RFC1918-section:

Address for private networks (RFC1918)
--------------------------------------

TCP/IP private networks not directly connected to Internet should use special addresses selected by
Internet Assigned Numbers Authority (IANA).

===============   ===========   =============================
Private network   Subnet mask   IP addresses interval
===============   ===========   =============================
10.0.0.0          255.0.0.0     10.0.0.1 - 10.255.255.254
172.16.0.0        255.240.0.0   172.16.0.1 - 172.31.255.254
192.168.0.0       255.255.0.0   192.168.0.1 - 192.168.255.254
===============   ===========   =============================

.. _reset_network-section:

Reset network configuration
---------------------------

In case of misconfiguration, it's possible to :index:`reset network configuration` by following these steps.

1. Delete all logical and physical interfaces from the db

   Display current configuration: ::

     db networks show

   Delete all interfaces: ::

     db network delete eth0

   Repeat the operation for all interfaces including bridges, bonds and vlans.


2. Disable interfaces

   Physical interfaces: ::
   
     ifconfig eth0 down

   In case of a bridge: ::

     ifconfig br0 down
     brctl delbr br0 

   In case of a bond (eth0 is enslaved to bond0): ::

     ifenslave -d bond0 eth0
     rmmod bonding

3. Remove configuration files

   Network configuration files are inside the :file:`/etc/sysconfig/network-scripts/` directory
   in the form: :file:`/etc/sysconfig/network-scripts/ifcfg-<devicename>`. Where `devicename` is the
   name of the interface like `eth0`, `br0`, `bond0`.

   Delete the files: ::

     rm -f /etc/sysconfig/network-scripts/ifcfg-eth0

   Repeat the operation for all interfaces including bridges, bonds and vlans.

4. Restart the network

   After restarting the network you should see only the loopback interface: ::

     service network restart

   Use :command:`ifconfig` command to check the network status.

5. Manually reconfigure the network

   Choose an IP to assign to an interface, for example `192.168.1.100`: ::

     ifconfig eth0 192.168.1.100

   Then reconfigure the system: ::

     signal-event system-init

   The interface will have the chosen IP address.

6. Open the web interface and reconfigure accordingly to your needs


.. _network_services-section:

Network services
================

A :index:`network service` is a service running on the firewall itself.

These services are always available to hosts on green network (local network).
Access policies can be modified from :guilabel:`Network services` page.

Available policies are:

* Access only from green networks (private): all hosts from green networks and from VPNs
* Access from green and red networks (public): any host from green networks, VPNs and external networks. But not guests (blue) and DMZ (orange) networks
* Access only from the server itself (none): no host can connect to selected service

Custom access
-------------

If selected policy is private or public, it’s possible to add hosts and networks which are always allowed (or blocked)
using :guilabel:`Allow hosts` and :guilabel:`Deny hosts`.
This rule also apply for blue and orange networks.

Example
^^^^^^^

Given the following configuration:

* Orange network: 192.168.2.0/24
* Access for NTP server set to private

If hosts from DMZ must access NTP server, add 192.168.2.0/24 network inside the :guilabel:`Allow hosts` field.

.. _remote_access-section:

Remote access
=============

Server Manager
--------------

It's possible to grant Server Manager's access to selected networks.
For example, if the server is inside a customer network, you should allow connections from remote management networks.

SSH
---

The :index:`SSH` (Secure Shell) should be always available.
SSH is a protocol to open remote shells over secure connections.

Default configuration allows authentication using password and public/private keys.


.. _trusted_networks-section:


Trusted networks
================

:dfn:`Trusted networks` are special networks (local or remote) allowed to access special server's services.

For example, hosts inside :index:`trusted networks` can access to:

* Server Manager
* Shared folders (SAMBA)

If users connected from VPNs must access system's services, add VPN networks to this page.

If the remote network is reachable using a router, remember to add a static route inside :ref:`static_routes-section` page.



.. _static_routes-section:

Static routes
==============

This page allow to create special :index:`static routes` which will use the specified gateway.
These routes are usually used to connect private network.

Remember to add the network to :ref:`trusted_networks-section`, if you wish to allow remote hosts to access local services.


.. _organization_contacts-section:

Organization contacts
=====================

The :guilabel:`Organization contacts` page fields are used as default
values for user accounts.  The organization name and address are also
displayed on the Server Manager login screen.

.. index::
   pair: Certificate; SSL   

.. _server_certificate-section:

Server certificate
==================

The :guilabel:`Server certificate` page shows the currently installed
SSL certificate that is provided by all system services.

The :guilabel:`Generate certificate` button allows generating a new
self-signed SSL certificate.  When a new certificate is generated, all
SSL services are restarted and network clients will be required to
accept the new certificate.

.. _user_profile-section:

User's profile
==============

All users can login to Server Manager using their own credentials.

After login, a user can :index:`change the password` and information about the account, like:

* Name and surname
* External mail address

The user can also overwrite fields set by the administrator:

* Company
* Office
* Address
* City

Shutdown
========

The machine where |product| is installed can be rebooted or halted from the :menuselection:`Shutdown` page.
Choose an option (reboot or halt) then click on submit button.

Always use this module to avoid bad shutdown which can cause data damages.

Log viewer
==========

All services will save operations inside files called :dfn:`logs`.
The :index:`log` analysis is the main tool to find and resolve problems.
To analyze log files click in :menuselection:`Log viewer`.

This module allows to:

* start search on all server's logs
* display a single log
* follow the content of a log in real time

Date and time
=============

After installation, make sure the server is configured with the correct timezone.
The machine clock can be configured manually or automatically using public NTP servers (preferred).

The machine clock is very important in many protocols. To avoid problems, all hosts in LAN can be configured to use the server as NTP server.

