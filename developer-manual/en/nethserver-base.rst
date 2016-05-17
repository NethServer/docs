=======
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
=========

The network database can be manipulated using the :dfn:`esmith::NetworksDB` perl module.
For more information use: ::

 perldoc esmith::NetworksDB

If you need to access the local ip address within a template, use this code snippet:

.. code-block:: perl

    use esmith::NetworksDB;
    my $ndb = esmith::NetworksDB->open_ro() || return;;
    my $LocalIP = $ndb->green()->prop('ipaddr') || '';


.. note:: Old templates used a variable called *LocalIP* to access the green
   ipaddress. *This variable is no more available.*

Events
======

All network configurations are applied by ``interface-update`` event.

Database initialization
=======================

All interfaces are imported from configuration files to database using
the script: ``/usr/libexec/nethserver/update-networks-db`` .

The *networks* database is updated Whenever an interface is plugged into the system.

Best practices
==============

DHCP on red interfaces
----------------------

When configuring a red interface in DHCP mode, enable also the above options:

* ``peer_dns`` to avoid resolv.conf overwriting from dhclient
* ``persistent_dhclient`` to enforce dhclient to retry in case of lease request errors

Remember also to remove all gateway ip address from green devices. 
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

     db network delete eth0

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

===============
Password policy
===============

The system can handle global or per-user policies.
All policies are enforced by PAM and saved under ``passwordstrength`` inside the ``configuration`` database.

Available properties are:

* ``Users``: change strength password for all users, can be:

  * ``strong``: (default) strong passwords must conform to cracklib checks
  * ``none``: no strength check
* ``PassExpires``: can be ``yes`` (default) or ``no``. If set to ``no`` password will not expire, if set to ``yes``,
    following properties apply:

  * ``MaxPassAge``: minimum number of days for which the user is forced to keep the same password (default 0)
  * ``MinPassAge``: maximum number of days for which the user can keep the same password (default: 180)
  * ``PassWarning``: an email will be sent to the user X days before password expiration

Configuration can be applied using the :command:`password-policy-update` event.

DB example: ::

 passwordstrength=configuration
    MaxPassAge=180
    MinPassAge=0
    PassExpires=no
    PassWarning=7
    Users=none

