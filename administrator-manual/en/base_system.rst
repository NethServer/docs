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

The :index:`Dashboard` page is the landing page after a successful login.
The page will display the :index:`status` and configurations of the system.

.. _duc-section:

Disk analyzer
-------------

This tool is used to visualize :index:`disk usage` in a simply and nice graph in which you can interact with click and double click to navigate in the directories tree.

After installation go in :guilabel:`Dashboard` and then :guilabel:`Disk usage` tab and click :guilabel:`Update`
to index the root directory and to display the graph. This process can take several minutes depending on occupied disk space.

Well known folders are:

* Shared folders: :file:`/var/lib/nethserver/ibay`
* User home directories: :file:`/var/lib/nethserver/home`
* Windows roaming profiles: :file:`/var/lib/nethserver/profile`
* Mail: :file:`/var/lib/nethserver/vmail`
* Faxes: :file:`/var/lib/nethserver/fax`
* MySQL databases: :file:`/var/lib/mysql`


.. index::
   single: Network
   pair: interface; role

.. _network-section:

Network
=======

The :guilabel:`Network` page configures how the server is connected to the
local network (LAN) or other ones (i.e. Internet).

If the server has firewall and gateway functionality, it will handle extra networks with special function like 
DMZ (DeMilitarized Zone) and guests network.

|product| supports an unlimited number of network interfaces.
Any network managed by the system must follow these rules:

* networks must be physically separated (multiple networks can't be connected to the same switch/hub)
* networks must be logically separated: each network must have different addresses
* private networks, like LANs, must follow address's convention from RFC1918 document.
  See :ref:`RFC1918-section`

.. index:: zone, role

Every network interface has a specific *role* which determinates its behavior. Roles are identified by colors.
Each role correspond to a well-known *zone* with special network traffic rules:

* *green*: local network. Hosts on this network can access any other configured network
* *blue*: guests network. Hosts on this network can access orange and red network, but can't access to green zone
* *orange*: DMZ network.  Hosts on this network can access red networks, but can't access to blue, orange and green zones
* *red*: public network. Hosts on this network can access only the server itself

See :ref:`policy-section` for more information on roles and firewall rules.

.. note:: The server must have at least one network interface. When the server has only one interface, this interface must have green role.

If the server is installed on a public VPS (Virtual Private Server), it should must be configured with a green interface.
All critical services should be closed using :ref:`network_services-section` panel.

.. _alias_IP-section:

Alias IP
--------

Use alias IP to assign more IP addresses to the same NIC.

The most common use is with a red interface: when the ISP provides a pool of public IP addresses (within the same subnet) you can add some (or all) of them to the same red interface and manage them individually (e.g. in the port forward configuration).

Alias IP section can be found in the dropdown menu of the related network interface.

.. _logical_interfaces-section:

Logical interfaces
------------------

In :guilabel:`Network` page press :guilabel:`New interface` button to
create a logical interface. Supported logical interfaces are:

* :index:`bond`: arrange two or more network interfaces, provides load balancing and fault tolerance
* :index:`bridge`: connect two different networks, it's often used for bridged VPN and virtual machine
* :index:`VLAN` (Virtual Local Area Network): create two or more logically separated networks using a single interface
* :index:`PPPoE` (Point-to-Point Protocol over Ethernet): connect to Internet through a DSL modem

**Bonds** allow you to aggregate bandwidth between two or more network interfaces. The system will use all network interfaces
at the same time, balancing traffic among all active interfaces.
If an error occurs, the faulty card is automatically excluded from the bond.

A **bridge** has the function to connect different network segments, for example by allowing virtual machines, or client connected using a VPN,
to access to the local network (green).

When it is not possible to physically separate two different networks, you can use a tagged **VLAN**. The traffic of the two networks can
be transmitted on the same cable, but it will be handled as if it were sent and received on separate network cards.
The use of VLAN, requires properly configured switches.

.. warning:: The **PPPoE** logical interface must be assigned the red
             role, thus requires the gateway functionality. See
             :ref:`firewall-section` for details.

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

.. index:: trusted networks

.. _trusted_networks-section:

Trusted networks
================

Trusted networks are special networks (local, VPNs or remote)
allowed to access special server's services.

For example, hosts inside trusted networks can access to:

* Server Manager
* Shared folders (SAMBA)

If the remote network is reachable using a router, remember to add a
static route inside :ref:`static_routes-section` page.



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

.. note::
   To avoid problems while importing the certificate in Internet Explorer,
   the Common Name (CN) field should match the server FQDN. 


.. _custom_certificate-section:

Install a custom certificate
----------------------------

:index:`Custom certificates` should be placed inside the following standard directories:

* :file:`/etc/pki/tls/certs`: public key
* :file:`/etc/pki/tls/private`: private key


Set the private key and certificate file paths:

::

    db configuration setprop pki CrtFile '/path/to/cert/pem-formatted.crt'
    db configuration setprop pki KeyFile '/path/to/private/pem-formatted.key'

You can also set a SSL certificate chain file:

::

    db configuration setprop pki ChainFile '/path/to/cert/pem-formatted-chain.crt'

Notify registered daemons about certificate update:

::

    signal-event certificate-update

Custom certificate backup
-------------------------
   
Always remember to add custom certificates to configuration backup.
Just add the paths inside :file:`/etc/backup-config.d/custom.include` file.

For example, if the certificate is :file:`/etc/pki/tls/certs/mycert.crt`, simply execute: ::

 echo "/etc/pki/tls/certs/mycert.crt" >> /etc/backup-config.d/custom.include

.. _user_profile-section:

Change user password
====================

All users can login to Server Manager using their own credentials and access the :index:`user profile`.

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


Inline help
===========

All packages inside the Server Manager contain an :index:`inline help`.
The inline help explains how the module works and all available options.

These help pages are available in all Server Manager's languages.

A list of all available inline help pages can be found at the address: ::

 https://<server>:980/<language>/Help

**Example**

If the server has address ``192.168.1.2``, and you want to see all English help pages, use this address: ::

 https://192.168.1.2:980/en/Help


