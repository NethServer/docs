Ntopng
======

Configure the bandwidth monitor Ntopng daemon, change listen port and
admin password.

After installation, ntopng is disabled by default.  The user must
access the web UI, choose an admin password and enable the
service. Ntopng web interface is then accessible from the port
specified in the web UI (default is 3000 with public access).

Ntopng uses free databases for geolocation. Databases are not part of
nethserver-ntopng package, but a monthly cron script downloads all
compressed packages and unpack them inside ntopng directories.  If you
wish to force database download, just execute: ::

    /etc/cron.monthly/ntop-update-geodb

Events
------

``nethserver-ntopng-update``, standard event triggered on package
installation/update and after modification in web UI.

Templates
---------

* ``/etc/ntopng/ntopng.conf``: daemon configuation
* ``/var/tmp/ntopng-users.conf``: user database

Database Reference
------------------

The admin password is saved in clear text inside the configuration db:
this allows users to easily change the password and retrieve the
current one.

Configuration DB
----------------

::

    ntopng=service
        Password=giacomo
        Interfaces=eth0,eth1
        TCPPort=3001
        access=public
        status=enabled

Links
-----

* Official site: http://www.ntop.org/products/ntop/
* Geoip free databases: http://dev.maxmind.com/geoip/geoip2/geolite2/

