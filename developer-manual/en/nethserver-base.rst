===============
nethserver-base
===============

This package implements all core configuration.

Network
=======

Network configuration is saved inside the NetworksDB (:file:`/var/lib/nethserver/db/networks`).

Example of a database containing an interface:

::

 eth0=ethernet
    bootproto=none
    device=eth0
    gateway=192.168.1.254
    ipaddr=192.168.1.1
    netmask=255.255.255.0
    onboot=yes
    role=green


Each entry describes a network interface according to CentOS/RHEL specification for network-scripts files: ::

 <device_name> = type
        role = <role>
        <param> = <value>

The ``type`` variable is the type of interface. Valid values are:

* ethernet
* bond
* bridge
* alias
* ipsec
* xdsl

The ``<device_name>`` variable is the name for the device.

The ``role`` property is a mandatory parameter which describes the interface role. Valid values are:

* green
* orange
* blue
* red

If the role property is empty, the interface is not used by the system.

There are also 3 special roles:

* *bridged*: interface is part of a bridge
* *slave*: interface is part of a bond
* *alias*: interface is an alias of another interface
* *xdsl-disabled*: xdsl disabled interface

See also :ref:`section-roles-and-zones` for the meaning of each color.

All ``<param>/<value>`` are all valid CentOS network parameter for the specified interface. All parameters must be lowercase. Example:

* ippaddr
* dhcp_hostname
* netmask
* slave
* ...

All parameters will be mapped 1-to-1  to the configuration file

**Example**

One green ethernet: ::

 db networks set eth0 ethernet role green ipaddr 192.168.1.4 netmask 255.255.255.0 network 192.168.1.0 onboot yes bootproto static

File content: ::

 green=ethernet|bootproto|static|device|green|ipaddr|192.168.1.4|netmask|255.255.255.0|network|192.168.1.0|onboot|yes|role|green

Bond options
------------

Any property starting with ``BondOpt`` prefix is used as bonding options.

Example: ::

 bond0=bond
    BondOptMode=0
    BondOptMiimon=80
    bootproto=none
    gateway=192.168.1.100
    ipaddr=192.168.1.2
    netmask=255.255.255.0
    role=green



Templates
---------

The network database can be manipulated using the :dfn:`esmith::NetworksDB` perl module.
For more information use: ::

 perldoc esmith::NetworksDB

If you need to access the local IP address within a template, use this code snippet:

.. code-block:: perl

    use esmith::NetworksDB;
    my $ndb = esmith::NetworksDB->open_ro() || return;;
    my $LocalIP = $ndb->green()->prop('ipaddr') || '';


.. note:: Old templates used a variable called *LocalIP* to access the green
   IP address. *This variable is no more available.*

Events
------

All network configurations are applied by ``interface-update`` event.

Database initialization
-----------------------

All interfaces are imported from configuration files to database using
the script: ``/usr/libexec/nethserver/update-networks-db`` .

The *networks* database is updated Whenever an interface is plugged into the system.

Best practices
--------------

DHCP on red interfaces
----------------------

When configuring a red interface in DHCP mode, enable also the above options:

* ``peer_dns`` to avoid resolv.conf overwriting from dhclient
* ``persistent_dhclient`` to enforce dhclient to retry in case of lease request errors

Remember also to remove all gateway IP address from green devices. 
This configuration will create the correct routes and correctly set DHCP options on dnsmasq.

Bridge
------

Create a bridge interface from command line.
The new interface will have green role (eth0 was the previous green interface): ::

 db networks delprop eth0 ipaddr netmask bootproto
 db networks setprop eth0 role bridged bridge br0
 db networks set br0 bridge bootproto static device br0 ipaddr 192.168.1.254 netmask 255.255.255.0 onboot yes role green
 signal-event interface-update

 
.. _reset_network-section:

Reset network configuration
---------------------------

In case of misconfiguration, it's possible to reset network
configuration by following these steps.

1. Delete all logical and physical interfaces from the db

   Display current configuration: ::

     db networks show

   Delete all interfaces: ::

     db networks delete eth0

   Repeat the operation for all interfaces including bridges, bonds
   and vlans.


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

   Network configuration files are inside the
   :file:`/etc/sysconfig/network-scripts/` directory in the form:
   :file:`/etc/sysconfig/network-scripts/ifcfg-<devicename>`. Where
   `devicename` is the name of the interface like `eth0`, `br0`,
   `bond0`.

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


Log retention and rotation
==========================

By default logs are rotated weekly and kept for 4 weeks.
Some packages come with different defaults, but the majority do not specify a custom rotate value.

Logrotate db property:

* ``Rotate``: rotation frequency, can be  ``daily``, ``weekly``, ``monthly``. Default is ``weekly``
* ``Times``: rotate log files ``Times`` number of times (days, weeks or months) before being removes, default is 4
* ``Compression``: can be ``enabled`` or ``disabled``. Defaults is ``disabled``

Example: ::

  logrotate=configuration
    Compression=disabled
    Rotate=weekly
    Times=4

Keep logs for 6 months, rotate once a week: ::

  config setprop logrotate Rotate weekly
  config setprop logrotate Times 24
  signal-event nethserver-base-update


Transport Layer Security
========================


The ``TLS policy`` page controls how individual services configure the
Transport Layer Security (TLS) protocol, by selecting a *policy identifier*.

Each module implementation decides how to implement a specific policy
identifier, providing a trade off between security and client compatibility.
Newer policies are biased towards security, whilst older ones provide better
compatibility with old clients.

You can enforce the TLS policy (20180330), or choose the legacy one (empty policy property) if your 
clients are not supported/maintained anymore (Windows XP for example).

TLS db property in configuration database: ::
  tls=configuration
    policy=

The event to expand the templates of all rpm which use TLS is ``tls-policy-save``

Repositories
============

Main repositories are:

* ``nethserver-base``: it contains packages and dependencies from core modules. It is updated when a new milestone is released. Enabled by default.
* ``nethserver-updates``: it contains updated packages. If needed, these updates can be applied without requiring manual intervention. Enabled by default.
* ``nethforge``: communty provided modules for NethServer. Enabled by default.
* ``nethserver-testing``: contains packages under QA process. Disabled by default.
* ``base``: base packages from CentOS. Enabled by default.
* ``updates``: updated packages from CentOS. Enabled by default.
* ``centos-sclo-rh`` and ``centos-sclo-sclo``: SCL repositories. Both enabled by default.
* ``extras``: extra RPMs. Enabled by default.

A standard installation should have the following enabled repositories:

* base
* updates
* nethserver-base
* nethserver-updates
* nethforge
* centos-sclo-rh
* centos-sclo-sclo
* extras

Packages published in above repositories should always allow a non-disruptive automatic update.

NS Release Lock
---------------

As default |product| is configured to access latest upstream repositories using the
"Rolling release" approach.

It is possibile to lock repositories to che current minor release using ``NS release lock`` feature: ::

  config setprop sysconfig NsReleaseLock enabled
  signal-event software-repos-save


When NS Release Lock is enabled, the following repositories are available (where ``ce`` stands for CentOS):

- ``ce-base``
- ``ce-updates``
- ``ce-extras``

These repositories point to a fixed CentOS release, the configuration is stored inside :file:`/etc/yum.repos.d/NsReleaseLock.repo`.

Configuration of enabled repositories is stored inside:

- :file:`/etc/nethserver/pkginfo.conf`: list of YUM repositories that have their groups listed
   on the Software Center
- :file:`/etc/nethserver/eorepo.conf`: list of YUM repositories enabled by ``software-repos-save``
  event, every non-listed repository will be disabled

Please note that *NS Release Lock* is mutually exclusive with subscription:
when a subscription is enabled, ``NSReleaseLock`` will be disabled.

Some *third-party repositories* don't support accessing RPMs using a minor release like ``7.5.1804``
but only using a major release like ``7``.
Actually, this limitation is present for:

- ``epel``
- ``centos-sclo-rh``
- ``centos-sclo-sclo``


When ``NsReleaseLock`` is set to ``enabled``:

- installation from the Software Center will enable all upstream repositories otherwise
  YUM will not be able to resolve package dependencies
- updates from the Software Center will disable repositories which doesn't support locking to minor
- updates from the command line will enable all upstream repositories
- ``yum-cron`` has access to a special repository configuration stored inside :file:`/etc/nethserver/yum-update.d/`
  and enabled using ``reposdir`` options inside ``/etc/yum/yum-cron.conf``


Third party repositories
------------------------

It's possible to install third party repositories, using standard CentOS methods.

If such repositories support access using minor release, they can be safely added
to :file:`eorepo.conf` and :file:`pkginfo.conf` using a template-custom.


yum-cron
--------

Since |product| ``7.5.1804``, ``nethserver-yum-cron`` has been merged into ``nethserver-base``.
The cron job runs each night with a random time before to start of 6 hours..
You can decide who receive the notifications (default is root), which updates to do, if you just check, download, or install automatically the updates.

Original author: Stephane de Labrusse (@stephdl)

Database
^^^^^^^^

Properties:

- ``applyUpdate``: can be ``yes`` or ``no``. If set to ``yes``, downloaded updates will be installed
- ``customMail``: comma-separated list of extra mail recipients, as default a mail will be sent to root
- ``download``: can be ``yes`` or ``no``. If set to ``yes``, download new package updates
- ``messages``: can be ``yes`` or ``no``. Whether a message should be emitted when updates are available
- ``randomWait``: random number of minutes to wait before executing the download procedure
  - NS6: 1 to 60 minutes
  - NS7: 1 to 360 minutes, negative and the job start immediately
- ``status``: can be ``enabled`` or ``disabled``. When enabled, a cron script will search for package updates

Database example: ::

 yum-cron=service
    applyUpdate=yes
    customMail=
    download=no
    messages=no
    randomWait=360
    status=enabled
