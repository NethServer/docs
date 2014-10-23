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
    hwaddr=xx:yy:18:da:dd:01
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

See also :ref:`section-roles-and-zones` for the meaning of each color.

All ``<param>/<value>`` are all valid CentOS network parameter for the specified interface. All parameters must be lowercase. Example:

* ippaddr
* hwaddr
* dhcp_hostname
* netmask
* slave
* ...

All parameters will be mapped 1-to-1  to the configuration file

**Example**

One green ethernet: ::

 db networks set eth0 ethernet role green hwaddr xx:yy:27:DE:B6:51 ipaddr 192.168.1.4 netmask 255.255.255.0 network 192.168.1.0 onboot yes bootproto static

File content: ::

 green=ethernet|bootproto|static|device|green|hwaddr|xx:yy:27:DE:B6:51|ipaddr|192.168.1.4|netmask|255.255.255.0|network|192.168.1.0|onboot|yes|role|green



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
