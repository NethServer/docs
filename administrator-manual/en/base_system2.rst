.. _base_system-section:

===========
Base system
===========

This chapter describes all available modules at the end of installation. All
modules outside this section can be installed from the :ref:`software-center-section` page.

The default installation includes the following main modules:

- :ref:`system-section`
- :ref:`applications-section`
- :ref:`software-center-section`
- :ref:`Terminal <terminal-section>`
-
  .. only:: nscom

    :ref:`subscription-section`

  .. only:: nsent

    :ref:`registration-section`

While the *root* user can see all configuration pages,
access of each section and application may be also delegated to specific users.
See :ref:`authentication-section`.

.. _system-section:

.. rubric:: System

The :index:`System` page is the landing section after a successful login.
The page will display the :index:`status` and configuration of the system.

From the system dashboard, the administrator can:

* change the machine FQDN and server :ref:`dns_alias-section`
* set upstream :ref:`dns-section` servers
* configure date time and NTP servers
* customize the organization details

The basic system includes also:

* :ref:`network-section`
* :ref:`services-section`
* :ref:`backup-section`
* :ref:`server_certificate-section`
* :ref:`users_and_groups-section`
* :ref:`tlspolicy-section`
* :ref:`dhcp-section`
* :ref:`dns-section`
* :ref:`ssh-section`
* :ref:`storage-section`
* :ref:`trusted_networks-section`
* :ref:`duc-section`
* :ref:`settings-section`
* :ref:`logs-section`

.. _terminal-section:

.. rubric::  Terminal

Execute a standard shell inside a terminal directly accessible from the browser.
The shell and the processes will run with the user privileges.

.. _network-section:

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
All critical services should be closed using :ref:`services-section` panel.

A role can be removed from an existing network interface by clicking on the tree-dots menu :guilabel:`⋮`,
then select :guilabel:`Release role` action.

.. _RFC1918-section:

.. rubric:: Addresses for private networks (RFC1918)

TCP/IP private networks not directly connected to Internet should use special addresses selected by
Internet Assigned Numbers Authority (IANA).

===============   ===========   =============================
Private network   Subnet mask   IP addresses interval
===============   ===========   =============================
10.0.0.0          255.0.0.0     10.0.0.1 - 10.255.255.254
172.16.0.0        255.240.0.0   172.16.0.1 - 172.31.255.254
192.168.0.0       255.255.0.0   192.168.0.1 - 192.168.255.254
===============   ===========   =============================

.. _IP_aliasing-section:

IP aliasing
-----------

Use IP aliasing to assign more IP addresses to the same network interface.

The most common use is with a red interface: when the ISP provides a pool of public IP addresses (within the same subnet) you can add some (or all) of them to the same red interface and manage them individually (e.g. in the port forward configuration).

To add an alias, click the tree-dots menu :guilabel:`⋮` on right corner of the existing network interface, then select :guilabel:`Create alias` item.

.. note:: IP aliases on PPPoE interface could not work properly, due to different implementations of internet providers.

.. _logical_interfaces-section:

Logical interfaces
------------------

Click on the :guilabel:`Add logical interface` button to create a new virtual network device.
As first step, select a role for the network interface. You can also create a logical
interface without a role to use it later with modules like :ref:`dedalo-section`.

Supported logical interfaces are:

* :index:`bond`: arrange two or more network interfaces (provides load balancing and fault tolerance)
* :index:`bridge`: connect two different networks (it's often used for bridged VPN and virtual machine)
* :index:`VLAN` (Virtual Local Area Network): create two or more logically separated networks using a single interface

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


PPPoE
-----

:index:`PPPoE` (Point-to-Point Protocol over Ethernet) connects the server to Internet through a DSL modem.
To create a new PPPoE connection, make sure to have an unassigned Ethernet network interface.

First, click on the :guilabel:`Configure` button on the unassigned network device, than select the :guilabel:`WAN (red)` role and
click :guilabel:`Next`.
Finally select PPPoE as interface type and fill all required
fields like :guilabel:`Username` and :guilabel:`Password`.

.. _static_routes-section:

Static routes
--------------

A static route is a rule that specifies how to route some network traffic that must not go through the default gateway.

To add a static routes, click the tree-dots menu :guilabel:`⋮` on right corner of an existing network interface, then select :guilabel:`Create route` item.
The route must be specified using the CIDR format inside the :guilabel:`Network address` field, like ``10.0.0.0/24``.
Static routes are added below the interface name.

To remove and existing static route, click on the interface name then click on the :guilabel:`Delete` button.

Remember to add the network to :ref:`trusted_networks-section`, if you wish to allow remote hosts to access local services.

.. _diganostic_tools-section:

Diagnostic tools
----------------

Diagnostic tools can be used to troubleshoot network problems.
As starting point, use the :guilabel:`Routing info` button to see current routing rules.

Extra diagnostic tools can be accessed by clicking on the tree-dots menu :guilabel:`⋮` just on right
of the routing information button. Available tools are:

* Ping: send ICMP packets to a specific host
* DNS lookup: perform a DNS query on a custom DNS server
* Traceroute:  print the route packets trace to a target network host

.. _services-section:

Services
========

The page contains a detailed list of all running services.
Each service has the following fields:

- **Name**: systemd service name
- **Description**: optional description of service purpose
- **Enabled**: it indicates if a service is marked to be automatically started by the system, usually at boot
- **Running**: it indicates if the service is actually running, regardless of its enabled/disabled state
- **Details**: inspect all service options by clicking the :guilabel:`View` link

A :index:`network service` is a service which has network access and can list TCP/UDP ports
to accept local or remote connections.
Specific fields for network services are:

- **Access**: it can be one ore more network role (like red, green, etc) or a firewall zone
- **Ports**: list of TCP and/or UDP ports

Existing services can be started and stopped directly from the buttons under the **Action** field.
Extra actions are available by clicking the tree-dots menu :guilabel:`⋮`.

Adding new services
-------------------

All |product| modules automatically configure their own network services.

Access to custom network services is denied by default.
To overcome this limitation, the administrator can create a new network service
by clicking on the :guilabel:`Add network service` button.

.. _server_certificate-section:

Certificates
============

The :guilabel:`Certificates` page shows the currently installed X.509
certificates, and the default one provided by system services for TLS/SSL
encrypted communications.

|product| checks the certificates validity and sends an email to the root user
if a certificate is near to expire and can't be automatically renewed.

The :guilabel:`Set as default` button, available under the the tree-dots menu :guilabel:`⋮`,
allows choosing the default certificate.
When a new certificate is chosen, all services using TLS/SSL are restarted
and network clients will be required to accept the new certificate.

When |product| is installed a default RSA self-signed certificate is generated.
It should be edited by inserting proper values before configuring the network
clients to use it. When the self-signed certificate is due to expire a new one
is automatically generated from the same RSA key and with the same attributes.

The :guilabel:`Server certificate` page also allows:

* uploading an existing certificate and private RSA/ECC key. Optionally a
  certificate chain file can be specified, too. All files must be PEM-encoded.

* requesting a new `Let's Encrypt <https://letsencrypt.org/>`_ certificate.  This is
  possible if the following requirements are met:

  1. The server must be reachable from outside at port 80. Make sure your port 80
     is open to the public Internet (you can check with sites like `CSM <http://www.canyouseeme.org/>`_);
    
  2. The domains that you want the certificate for must be public domain names
     associated to server own public IP. Make sure you have public DNS name
     pointing to your server (you can check with sites like `VDNS <http://viewdns.info/>`_).

     Wild card certificates (i.e. ``*.nethserver.org``) are not supported.

  The :guilabel:`Notification email` will be used by Let's Encrypt to send
  notifications about the certificate.

  The Let's Encrypt certificate is automatically renewed 30 days before expiration date.

.. note::
   To avoid problems while importing the certificate in Internet Explorer,
   the Common Name (CN) field should match the server FQDN.

Delete a certificate
--------------------

Unused certificated can be deleted by clicking the by clicking the :guilabel:`Delete` button
under the tree-dots menu :guilabel:`⋮`.

The builtin certificate can't be deleted.

.. _storage-section:

Storage
=======

The :index:`storage` section configures and monitors disks.
The administrator can mount new local or remote disks, manage RAID arrays and LVM volumes.


.. index:: trusted networks

.. _trusted_networks-section:

Trusted networks
================

Trusted networks are special networks (local, VPNs or remote)
allowed to access special server's services.

For example, hosts inside trusted networks can access to:

* Server Manager
* Shared folders (SAMBA)

New trusted networks can be added using the :guilabel:`Add network` button.

If the remote network is reachable using a router, remember to add a
static route inside :ref:`static_routes-section` page.


.. index: SFTP

.. _ssh-section:

SSH
===

The :menuselection:`System > SSH` page displays the number of current SSH connections. From this
section the administrator can change the OpenSSH listening port and disable weak ciphers, root
login, and password authentication.

By default, SSH and SFTP access is granted to the following groups of administrators:

* ``root``
* ``wheel``

When an account provider is configured, the access is granted to ``domain admins``, too.
See :ref:`admin-account-section` for details.

It is possible to grant access to normal users and groups with the
:guilabel:`Allow SSH/SFTP access` selector.

The administrator can harden SSH by restricting the usage of weak ciphers, algorithms and macs.
After enabling the :guilabel:`Disable weak ciphers` option, the host key will change and clients
will have to accept the new one.
Also, note that big files transfer can be slower with the strong encryption and very old SSH clients
may not be able to connect to the server.

.. note::

    For |product| up to version 7.7:

    The :guilabel:`Allow SSH/SFTP access` selector is available once the :guilabel:`Override the shell of users`
    option has been enabled in :menuselection:`System > Settings > Shell policy`.
    If that option is disabled, only users the with :guilabel:`Shell`
    option can access the Server Manager, and delegation is not required any more.

    See :ref:`relnotes-ns78` for more information.

Access of the ``wheel`` group can be revoked with the following commands: ::

    config setprop sshd AllowLocalGroups ''
    signal-event nethserver-openssh-save

The ``AllowLocalGroups`` property accepts a comma separated list of ``/etc/groups`` names and can be
adjusted according to the actual needs (e.g. ``wheel,srvadmins``).

.. _duc-section:

Disk analyzer
=============

This tool is used to visualize :index:`disk usage` in a simple and nice graph in which you can interact with, click, and double click to navigate in the directories tree.

The chart is updated overnight. Click  the :guilabel:`Update now` in order
to index the file system and update the chart.
Please note that this process can take several minutes depending on the occupied disk space.

Well known folders are:

* Shared folders: :file:`/var/lib/nethserver/ibay`
* User home directories: :file:`/var/lib/nethserver/home`
* Mail: :file:`/var/lib/nethserver/vmail`
* Faxes: :file:`/var/lib/nethserver/fax`
* MySQL databases: :file:`/var/lib/mysql`

.. _settings-section:

Settings
========

The :index:`settings` page allows the configuration of some options which could impact multiple system applications.

.. _smart-host:

Smart host
----------

Many system applications, like cron, can generate mail notification.
If the server can't directly deliver those mails, the administrator can configure
a SMTP relay.
When the smarthost is enabled, all mail messages will be delivered to the configured server.

Email notifications
--------------------

As default, notifications are sent to the local root maildir.
The administrator can change the root forward address adding one or more mail address to the :guilabel:`Destination` field.

It's also a good practice to set a custom :guilabel:`Sender address`: messages from the root user (like cron notifications)
will be sent using the specified address.
A good value could be: ``no-reply@<domain>`` (where ``<domain>`` is the domain of the server).
If not set, messages will be sent using ``root@<fqdn>`` as sender address.

Server Manager
--------------

As default, access to the Server Manager is granted from all firewall zones.
From this section the administrator can restrict the access to the Server Manager only to
a list of trusted IP addresses.

Log files
---------

All log files are managed by :index:`logrotate`. Logrotate is designed to ease administration of a large numbers of log files.
It allows automatic rotation, compression, and removal of log files. Each log file may be handled daily, weekly, monthly.

The administrator can set logrotate defaults from this page. The configuration will apply to all applications.
But please note that some applications can override such configuration to meet specific needs.

Configuration hints
-------------------

Most Server Manager pages can display some configuration hints to help guide the administrator
on a better system configuration.
Hints are just suggestions and can be disabled from this menu.

Password change
---------------

The settings page also includes a panel to let users change their password, including the root user.

Shell policy
------------

This setting was added since |product| 7.8, to select how the user's shell is configured.

If the :guilabel:`Override the shell of users` option is enabled, the old user's :guilabel:`Shell`
setting under the :guilabel:`Users & Groups` page is hidden and it is considered always enabled.

This is required by some features introduced starting from |product| 7.8, like the new Server Manager based
on Cockpit, the :guilabel:`User settings page` and the fine grained SSH and SFTP permissions.
See :ref:`relnotes-ns78` for details.


.. _user_settings-section:

User settings page
------------------

When the :guilabel:`Enable user settings page` options is enabled, users can change their password and other settings on a web page outside
Cockpit (on port 443). The default page is :guilabel:`/user-settings`. This feature can be enabled only if
:guilabel:`Shell Policy` is enabled as well.

The access to the page can be limited only from Trusted Networks.

.. _logs-section:

Logs
====

The system provides an indexed log named journal.
Journal can be browsed from this page: messages can be filtered by service, severity and date.

.. _applications-section:

============
Applications
============

The :guilabel:`Applications` page lists all installed applications.
An :index:`application` is a Server Manager module usually composed by multiple pages
including a dashboard, one or more configuration sections and the access to application logs.
A click on the :guilabel:`Settings` button will open the application.

There are also simpler applications which include only a link to an external web pages.
To access such applications click on the :guilabel:`Open` button.

Shortcuts
=========

The administrator can add shortcuts to applications which are frequently used.
Applications with a shortcut, will be linked to the left menu.

Only *root* user has access to this feature.

.. only:: nscom

  Add to home page
  ----------------

  :index:`Launcher` is an application of the new Server Manager available to all users on HTTPS and HTTP ports.
  The launcher is accessible on the server FQDN (eg. ``https://my.server.com``) and it's enabled if
  there is no home page already configured inside the web server (no index page in :file:`/var/www/html`)

  Installed applications can be added to the launcher by clicking on the :guilabel:`Add to home page` button.
  All users will be able to access the public link of the application.

  Only *root* user has access to this feature.

.. only:: nsent

  Launcher
  ========

  See :ref:`launcher-section`.

Removing applications
=====================

To remove an installed module click :guilabel:`Remove` button on the corresponding application.

.. warning::

   When removing a module other modules could be removed, too! Read carefully
   the list of affected packages to avoid removing required features.

   This feature is not available in |product| Enterprise.

.. _authentication-section:

==============
Authentication
==============

The Server Manager can be always accessed from the following users:
- ``root``
- members of ``domain admins`` groups

.. _delegation-section:

Role delegation
===============

In complex environments, the *root* user can :index:`delegate` the access of some Server Manager
pages to specific groups of users.

The *admin* user and the *domains admins* group are implicitly delegated to all pages.
See also :ref:`admin-account-section` for more information.

Other groups can be delegated to access:

* one or more pages under the :guilabel:`System` section
* one or more installed applications
* the :guilabel:`Subscription` page
* the :guilabel:`Software Center` page

To create a new delegation, go to the :guilabel:`System > User & Groups > List > [Groups]`
section then select the :guilabel:`Delegations` action of an existing group.
Pick one or more items from the :guilabel:`System views` and :guilabel:`Applications` menus.

The following pages are implicitly added to the delegated set:

* :guilabel:`Dashboard`
* :guilabel:`Applications`
* :guilabel:`Terminal`

.. note::

   For |product| up to version 7.7:

   Even if a user has been delegated, it must be explicitly granted the shell access before
   being able to log into the Server Manager.

   See :ref:`relnotes-ns78` for more information.


.. _2fa-section:

Two-factor authentication (2FA)
===============================

Two-factor authentication (2FA) can be used to add an extra layer of security required to access the new Server Manager.
First, users will enter user name and password, then they will be required to provide a temporary verification code
generated by an application running on their smartphone.

2FA is disabled by default. Users can enable it by themselves, accessing the :guilabel:`Two-factor authentication`
section under their :guilabel:`System > Settings` page or by pointing the web browser to the ``/user-settings`` URL
as explained in :ref:`user_settings-section`. Thereafter they have to follow these steps:

1. download and install the preferred 2FA application inside the smartphone
2. scan the QR code with the 2FA application
3. generate a new code and copy it inside :guilabel:`Verification code` field, than click :guilabel:`Check code`
4. if the verification code is correct, click on the :guilabel:`Save` button

Two-factor authentication can be enabled for the following core applications:

- the new Server Manager
- SSH when using username and password (access with public key will never require 2FA)


Recovery codes
--------------

Recovery codes can be used instead of temporary codes if the user cannot access the 2FA application on the smartphone.
Each recovery code is a one-time password and can be used only once.

To generate new recovery codes, disable 2FA, then re-enable it by registering the application again following the above steps.

Smartphone applications
-----------------------

There are several commercial and open source 2FA applications:

Available for both Android and iOS:

- `FreeOTP <https://freeotp.github.io/>`_: available for both Android and iOS
- `Authenticator <https://mattrubin.me/authenticator/>`_: available on iOS only
- `andOTP <https://github.com/andOTP/andOTP>`_: available for both Android and iOS https://github.com/andOTP/andOTP

Emergency recovery
------------------

In case of emergency, 2FA can be disabled accessing the server from a physical console like a keyboard and a monitor,
a serial cable or a VNC-like connection for virtual machines:

1. access the system with user name and password
2. execute: ::

     rm -f ~/.2fa.secret
     sudo /sbin/e-smith/signal-event -j otp-save

Eventually, the root user can retrieve recovery codes for a user.
Use the following command and replace ``<user>`` with the actual user name : ::

  oathtool -w 4 $(cat ~<user>/.2fa.secret)

Example for user ``goofy``: ::

  # oathtool -w 4 $(cat ~goofy/.2fa.secret)
  984147
  754680
  540025
  425645
  016250
