=======
Network
=======


NetworksDB
==========

NetworksDB is subclass of esmith::DB. The existing *esmith::NetworksDB* perl module manages 
the *networks* database and has been extended to export some useful methods.

These methods return a list of interfaces filtered by type (names are
auto-explicative):

* interfaces
* ethernets
* bridges
* bonds
* aliases
* ipsec

In a scalar context these methods return an interface with the given
role:

* green: interface on LAN
* orange
* blue
* red: interfaces exposed to external networks when the server is used as a gateway 

For more information use: ::

 perldoc esmith::NetworksDB

Templates
=========

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

DHCP on red interfaces
======================

Enabling DHCP on red interfaces can overwrite ``/etc/resolv.conf`` file.
To avoid this behavior, make sure the *PEERDNS* option is set to *no*.

Example where eth1 is the red interface: ::

 config setprop eth1 peerdns no
