.. _web-proxy:

=================
Web proxy (Squid)
=================

This package configure the well-known Squid web proxy.

Squid rpms are from: http://www1.ngtech.co.il/rpm/centos/6/x86_64/

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
* *SSLBypass*: comma separated list of domains bypassing the proxy when set in transparent_ssl mode

Database example
----------------

Example: ::

 squid=service
    BlueMode=manual
    DiskCache=disabled
    DiskCacheSize=100
    GreenMode=manual
    KrbPrimaryList=HTTP
    KrbStatus=enabled
    MaxObjSize=4096
    MemCacheSize=256
    MinObjSize=1
    NoCache=
    ParentProxy=
    PortBlock=disabled
    SSLBypass=
    TCPPorts=3128,3129,3130
    access=private
    status=enabled


Transparent mode
================

When the proxy is enabled in transparent mode, all traffic destined to the port 80 is redirect to the Squid (port 3129).
This configuration requires Shorewall.

SSL bump
--------

If the proxy us enabled in transparent SSL mode, also all traffic destined to port 443 is redirected to Squid (port 3130).

Following sites are always excluded from SSL bump:

* images.metaservices.microsoft.com 
* crl.microsoft.com 
* update.microsoft.com 
* www.download.windowsupdate.com 
* windowsupdate.microsoft.com 
* sls.microsoft.com 
* redir.metaservices.microsoft.com 
* wustat.windows.com 
* productactivation.one.microsoft.com 
* download.windowsupdate.com 
* c.microsoft.com 
* .urs.microsoft.com 
* ntservicepack.microsoft.com 
* .download.microsoft.com 


Authenticated mode
==================

Authentication schema depend on system configuration:

* standard authentication for system users is done over LDAP
* if Samba is installed and the server is a Primary Domain Controller, clients can use NTLM authentication
* if Samba is installed and the server is a member of an Active Directory domain, clients can use Kerberos (SPNEGO/GSSAPI)

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

Every records of database can be modified changing the property with ``config setprop squid <property> <value>``.

.. warning:: Be careful to above description of *MaxObjSize*, *MinObjSize* and *MemCacheSize*.


Miscellaneous options
=====================

Following options are always enabled:

* buffered logs
* SNMP support on port 3401
