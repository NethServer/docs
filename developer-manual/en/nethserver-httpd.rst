nethserver-httpd
================

NethServer extends the upstream configuration for ``httpd`` by adding a specific
configuration file: ``/etc/httpd/conf.d/nethserver.conf``. 

Features
--------

* Shared folders
* Virtual hosts
* Letsencrypt certificates

Configuration database
----------------------

::

 httpd=service
    SSLCipherSuite=DEFAULT:!EXP:!SSLv2:!DES:!IDEA:!SEED:+3DES
    TCPPorts=80,443
    access=public
    status=enabled

Letsencrypt
-----------

::

 /usr/libexec/nethserver/letsencrypt-certs -v
 
See also "Certificate management".

Virtual hosts
-------------

Ongoing discussion http://community.nethserver.org/t/proposal-for-ns7-virtualhost-page/3082

Shared folders
--------------

Events
------

::

 signal-event nethserver-httpd-update