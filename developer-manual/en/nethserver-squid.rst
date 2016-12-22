================
nethserver-squid
================

This package configure the well-known Squid web proxy.

Squid rpms are from upstream.

Configuration
=============

All properties are saved in the ``squid`` key under the ``configuration`` database.

Properties:

* *BlueMode*: change Squid operation mode on blue networks. It has same values and defaults of ``GreenMode``
* *DiskCache*: disabled by default, if enabled it actives the disk caching system for squid
* *DiskCacheSize*: maximum value of squid cache on disk
* *GreenMode*: change Squid operation mode on green networks.
  Can be: ``manual``, ``authenticated``, ``transparent``, ``transparent_ssl``. Default is: ``manual``
* *KrbPrimaryList*: name for Kerberos keytab (used for Active Directory integration)
* *KrbStatus*:  if set to enabled a ticket credential cache file is kept valid by the hourly cron job (used for Active Directory integration)
* *MaxObjSize*: objects larger than this setting will not be saved on disk. If speed is more desirable than saving bandwidth, this should be set to a low value
* *MemCacheSize*: value of squid cache on memory
* *MinObjSize*: can be left at 0 to cache everything, but may be raised if small objects are not desired in the cache.
* *NoCache*: comma separated list of domains which will be not cached
* *ParentProxy*: in the form host:port, if omitted port is default to 3128. Default is empty
* *PortBlock*: if enabled, block port 80 and 443. Default is: ``disabled`` 
* *SafePorts*: comma separated list of ports thath can be accessed through the proxy. Listed ports will be added to the default list of safe and ssl ports

Database example
----------------

Example: ::

 squid=service
    BlueMode=manual
    DiskCache=disabled
    DiskCacheSize=100
    GreenMode=transparent
    KrbPrimaryList=HTTP
    KrbStatus=enabled
    MaxObjSize=4096
    MemCacheSize=256
    MinObjSize=1
    NoCache=www.nethserver.org
    ParentProxy=
    PortBlock=disabled
    TCPPorts=3128,3129,3130
    access=private
    status=enabled


Transparent mode
================

When the proxy is enabled in transparent mode, all traffic destined to the port 80 is redirect to the Squid (port 3129).
This configuration requires Shorewall.

SSL peek and splice
-------------------

If the proxy is enabled in transparent SSL mode, also all traffic destined to port 443 is redirected to Squid (port 3130).
The daemon does not inspect SSL traffic, but visited sites can be processed using the web filter.

Known bugs
^^^^^^^^^^

You could find this kind of errors inside ``/var/log/squid/cache.log`` ::

  2016/12/09 09:44:18 kid1| SECURITY ALERT: on URL: avatars0.githubusercontent.com:443
  2016/12/09 09:44:18 kid1| SECURITY ALERT: Host header forgery detected on local=151.101.60.133:443 remote=192.168.5.22:40950 FD 166 flags=33 (local IP does not match any domain IP)

In this case, when accessing github, the avatars won't be displayed by the browser, and you can find a "Timeout error" for the not loaded images.

This kind of errors can't be fixed. See official documentation for workarounds:

* http://wiki.squid-cache.org/KnowledgeBase/HostHeaderForgery2
* http://lists.squid-cache.org/pipermail/squid-users/2016-September/012344.html

Authenticated mode
==================

Authentication schema depends on system configuration:

* standard authentication for system users is done over LDAP
* if Samba AD is installed, clients can use Kerberos (SPNEGO/GSSAPI)

Bypasses
========

Bypass rules are saved inside the ``fwrules`` databases.
A bypass can be of two types:

* bypass-src: listed origin host are bypassed
* bypass-dst: listed target host are bypassed

Properties:
* *Host*: a host object, like a remote or local host
* *status*: can be ``enabled`` or ``disabled``
* *Description*: optional description


Bypass example: ::

 boss=bypass-src
    Description=Boss without proxy
    Host=host;bosspc
    status=enabled

Cache
=====
There is an *event* called ``nethserver-squid-clear-cache`` that empties the cache.

WPAD
====

WPAD is located at :file:`/var/www/html/wpad.dat`.
The web server is configured to allow the download only from trusted and blue networks,
but be aware that you need to manually open the httpd port for blue networks (see :ref:`network_service_custom_access-section`).

The WPAD returns:

* DIRECT, if squid is disabled or the requesting client is inside a network where the proxy is configured in transparent mode
* IP of corresponding network interface, if the requesting client is inside a network where the proxy is configured in manual or authenticated mode
* proxy.<domain>, if the server is joined to Active Directory and the requesting client is inside a 
  network where the proxy is configured in manual or authenticated mode

Also WPAD file includes all source and destination bypasses.

Miscellaneous options
=====================

The following options are always enabled:

* buffered logs
* SNMP support on port 3401
