.. _legacy_server_manager-section:

======================
The old Server Manager
======================

This chapter describes the :dfn:`old Server Manager` web interface. Since |product| 7.9 it must be
installed from the :ref:`software-center-section` page as it is not included in the default
installation procedure.

.. warning::

   New features of |product| are not available in this web interface. Backward compatibility may break
   at any time. It is recommended to use the new Server Manager. See :ref:`access-section`
   and :ref:`base_system-section`.

.. _access_legacy-section:

Getting started
===============

You need a web browser like Mozilla Firefox or Google Chrome to access the old Server Manager web interface using the address (URL)
``https://a.b.c.d:980`` or ``https://server_name:980`` where *a.b.c.d* and *server_name* respectively are the server IP address and name
configured during installation.

If the *Web server* module is installed, you can also access the web interface using the address ``https://server_name/server-manager``.

The Server Manager uses self-signed SSL certificates.
You should explicitly accept them the first time you access the server.
The connection is safe and encrypted.

Login
-----

The login page allows selecting an alternative language among those already
installed on the system. After logging in, additional language packs can
be installed from the :menuselection:`Software center` page under the :guilabel:`Languages` category.

The login page will give you a trusted access to the web interface. Log in
as **root** and type the password chosen during |product| installation.

.. note::

    The *unattended* install procedure sets the root password to the default
    ``Nethesis,1234``.

Change the current password
---------------------------

You can change the root password from the web interface by going to the
:guilabel:`root@host.domain.com` label on the upper right corner of the screen
and clicking on :guilabel:`Profile`.


Logout
------

Terminate the current Server Manager session by going to the
:guilabel:`root@host.domain.com` label on the upper right corner of the screen
and by clicking on :guilabel:`Logout`.

.. _session-timeouts-section:

Session timeouts
----------------

By default (starting from |product| 7.5.1804), a Server Manager session
terminates after **60 minutes of inactivity** (idle timeout) and **expires
8 hours after the login** (session life time).

The following shell command sets 2 hours of idle timeout, and 16 hours of
maximum session life time. Time is expressed in seconds: ::

    config setprop httpd-admin MaxSessionIdleTime 7200 MaxSessionLifeTime 57600

To disable the timeouts ::

    config setprop httpd-admin MaxSessionIdleTime '' MaxSessionLifeTime ''

The new timeout values will affect new sessions. They do not change any active
session.


.. _dashboard_legacy-section:

Dashboard
=========

The :index:`Dashboard` page is the landing page after a successful login.
The page will display the :index:`status` and configuration of the system.

Disk analyzer
-------------

This tool is used to visualize :index:`disk usage` in a simple and nice graph in which you can interact with, click, and double click to navigate in the directories tree.

After installation go to the :guilabel:`Dashboard`, and then :guilabel:`Disk usage` tab, and click :guilabel:`Update` in order
to index the root directory and display the graph. This process can take several minutes depending on the occupied disk space.

Well known folders are:

* Shared folders: :file:`/var/lib/nethserver/ibay`
* User home directories: :file:`/var/lib/nethserver/home`
* Mail: :file:`/var/lib/nethserver/vmail`
* Faxes: :file:`/var/lib/nethserver/fax`
* MySQL databases: :file:`/var/lib/mysql`


.. index::
   single: Network
   pair: interface; role

Network
=======

The :guilabel:`Network` page configures how the server is connected to the
local network (LAN) and/or other networks (i.e. Internet).

If the server has firewall and gateway functionality, it will handle extra networks with special functions like
DMZ (DeMilitarized Zone) and guests network.

|product| supports an unlimited number of network interfaces.
Any network managed by the system must follow these rules:

* networks must be physically separated (multiple networks can't be connected to the same switch/hub)
* networks must be logically separated: each network must have different addresses
* private networks, like LANs, must follow address's convention from :ref:`RFC1918 <RFC1918-section>` document

.. index:: zone, role

Every network interface has a specific *role* which determines its behavior. All roles are identified by colors.
Each role corresponds to a well-known *zone* with special network traffic rules:

* *green*: local network (green role/zone). Hosts on this network can access any other configured network
* *blue*: guests network (blue role/zone). Hosts on this network can access orange and red networks, but can't access the green network
* *orange*: DMZ network (orange role/zone).  Hosts on this network can access red network, but can't access to blue and green networks
* *red*: public network (red role/zone). Hosts on this network can access only the server itself

See :ref:`policy-section` for more information on roles and firewall rules.

.. note:: The server must have at least one network interface. When the server has only one interface, this interface must have green role.

If the server is installed on a public VPS (Virtual Private Server), it should must be configured with a green interface.
All critical services should be closed using :ref:`network_services_legacy-section` panel.

Alias IP
--------

Use alias IP to assign more IP addresses to the same NIC.

The most common use is with a red interface: when the ISP provides a pool of public IP addresses (within the same subnet) you can add some (or all) of them to the same red interface and manage them individually (e.g. in the port forward configuration).

Alias IP section can be found in the dropdown menu of the related network interface.

.. note:: Alias IPs on PPPoE interface could not work properly, due to different implementations of the service made by internet providers.


Logical interfaces
------------------

In :guilabel:`Network` page press the :guilabel:`New interface` button to
create a logical interface. Supported logical interfaces are:

* :index:`bond`: arrange two or more network interfaces (provides load balancing and fault tolerance)
* :index:`bridge`: connect two different networks (it's often used for bridged VPN and virtual machine)
* :index:`VLAN` (Virtual Local Area Network): create two or more logically separated networks using a single interface
* :index:`PPPoE` (Point-to-Point Protocol over Ethernet): connect to Internet through a DSL modem

**Bonds** allow you to aggregate bandwidth or tolerate link faults. Bonds can be configured in multiple modes.

Modes providing load balancing and fault tolerance:

* Balance Round Robin (recommended)
* Balance XOR
* 802.3ad (LACP): it requires support at driver level and a switch with IEEE 802.3ad Dynamic link aggregation mode enabled
* Balance TLB: it requires support at driver level
* Balance ALB

Modes providing fault tolerance only:

* Active backup (recommended)
* Broadcast policy

A **bridge** has the function to connect different network segments, for example by allowing virtual machines, or client connected using a VPN,
to access to the local network (green).

When it is not possible to physically separate two different networks, you can use a tagged **VLAN**. The traffic of the two networks can
be transmitted on the same cable, but it will be handled as if it were sent and received on separate network cards.
The use of VLAN, requires properly configured switches.

.. warning:: The **PPPoE** logical interface must be assigned the red
             role, thus requires the gateway functionality. See
             :ref:`firewall-section` for details.


.. _network_services_legacy-section:

Network services
================

A remote system can connect to a :index:`network service`, which is a software
running on |product| itself.

Each service has a list of "open" ports on which it answers to connections.
Connections can be accepted from selected zones. More fine-grained control of
access to network services can be configured from the Firewall rules page.


.. index:: trusted networks

.. _trusted_networks_legacy-section:

Trusted networks
================

Trusted networks are special networks (local, VPNs or remote)
allowed to access special server's services.

For example, hosts inside trusted networks can access to:

* Server Manager
* Shared folders (SAMBA)

If the remote network is reachable using a router, remember to add a
static route inside :ref:`static_routes_legacy-section` page.



.. _static_routes_legacy-section:

Static routes
==============

This page allow to create special :index:`static routes` which will use the specified gateway.
These routes are usually used to connect private network.

Remember to add the network to :ref:`trusted_networks_legacy-section`, if you wish to allow remote hosts to access local services.


.. _organization_contacts_legacy-section:

Organization contacts
=====================

The :guilabel:`Organization contacts` page fields are used as default
values for user accounts.  The organization name and address are also
displayed on the old Server Manager login screen.

.. index::
   pair: Certificate; SSL

Server certificate
==================

The :guilabel:`Server certificate` page shows the currently installed X.509
certificates, and the default one provided by system services for TLS/SSL
encrypted communications.

|product| checks the certificates validity and sends an email to the root user
if a certificate is near to expire.

The :guilabel:`Set as default` button allows choosing the default certificate.
When a new certificate is chosen, all services using TLS/SSL are restarted
and network clients will be required to accept the new certificate.

When |product| is installed a default RSA self-signed certificate is generated.
It should be edited by inserting proper values before configuring the network
clients to use it. When the self-signed certificate is due to expire a new one
is automatically generated from the same RSA key and with the same attributes.

The :guilabel:`Server certificate` page also allows:

* uploading an existing certificate and private RSA/ECC key. Optionally a
  certificate chain file can be specified, too. All files must be PEM-encoded.

* requesting a new *Let's Encrypt* [#Letsencrypt]_ certificate.  This is
  possible if the following requirements are met:

  1. The server must be reachable from outside at port 80. Make sure your port 80
     is open to the public Internet (you can check with sites like [#CSM]_);
    
  2. The domains that you want the certificate for must be public domain names
     associated to server own public IP. Make sure you have public DNS name
     pointing to your server (you can check with sites like [#VDNS]_).

     Wildcard certificates (i.e. ``*.nethserver.org``) are not supported.

  The :guilabel:`Notification email` will be used by Let's Encrypt to send
  notifications about the certificate.

  The Let's Encrypt certificate is automatically renewd 30 days before expiration date.

.. note::
   To avoid problems while importing the certificate in Internet Explorer,
   the Common Name (CN) field should match the server FQDN.

.. [#Letsencrypt] Let's Encrypt website https://letsencrypt.org/
.. [#CSM] Website http://www.canyouseeme.org/
.. [#VDNS] Website http://viewdns.info/

Disable Let's Encrypt
---------------------

Let's Encrypt certificate can be disabled following these steps:

1. Access the :guilabel:`Server certificate` page, set as default the self-signed certificate or an uploaded one
2. Open the shell and execute the following commands:

   ::

     rm -rf /etc/letsencrypt/{accounts,archive,csr,keys,live,renewal}
     config setprop pki LetsEncryptDomains ''

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

.. _date-time_legacy-section:

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
