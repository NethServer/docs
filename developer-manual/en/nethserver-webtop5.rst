==================
nethserver-webtop5
==================

WebTop 5 is a full-featured groupware written in Java.

It's composed by three parts:

* Java web application running on Tomcat 7
* PHP implementation of Active Sync protocol
* PHP implementation of CardDAV and CalDAV protocol
* PostgreSQL database

Access to web application is forced in SSL mode.

WebTop 5 has been split in 4 different RPMs:

- webtop5-core: Tomcat webapp, derived from a WAR. It contains all jars developed by Sonicle. This package will be updated at each
  WebTop release
- webtop5-libs: derived from a WAR, it contains all third-party jars. This package will be seldom updated
- webtop5-zpush: ActiveSync implementation for WebTop, it contains PHP code from z-push project (http://z-push.org/)
- webtop5-webdav: CardDAV and CalDAV implementation for WebTop, it contains PHP code from sabre/dav project (http://sabre.io/dav/)
- nethserver-webtop5: NethServer auto-configuration for WebTop

Database
========

Configuration is saved in ``webtop`` key inside ``configuration`` database.

Available properties:

* ``ActiveSync``: if set to ``enabled``, it enables /Microsoft-Server-ActiveSync url.  Default is ``enabled``
* ``ActiveSyncLog``: log level of z-push implementation. As default z-push will log only relevant errors.
* ``Debug``: if set to ``true``, enable debug for the web application. Default is ``false``
* ``DefaultLocale``: default locale for WebTop users. To list available locales execute: ``/etc/e-smith/events/actions/nethserver-webtop5-locale-tz``
* ``DefaultTimezone``: default timezone for WebTop users. To list available timezones: ``JAVA_HOME=/usr/share/webtop/ java ListTimeZones``
* ``MinMemory`` and ``MaxMemory``: minimun and maximum memory of Tomcat instance. Values are expressed in MB.
* ``PublicUrl``: public URL used to publish resources for the cloud. If not set, default is ``http://<FQDN>/webtop``
* ``DavServerUrl``: Dav server URL for CalDAV and CardDAV clients configuration. If not set, default is ``https://<FQDN>/webtop-dav/server.php``
* ``DavServerLog``: log level of webtop-dav implementation. As default webtop-dav will log only relevant errors.
* ``PbxProvider``: PBX provider name
* ``PbxProviderNethvoiceWebrestUrl``: NethVoice base url for API calls, used when ``PbxProvider`` is set to ``nethvoice``

Example: ::

  webtop=configuration
      ActiveSync=enabled
      ActiveSyncLog=LOGLEVEL_ERROR
      Debug=false
      DefaultLocale=en_US
      DefaultTimezone=Etc/UTC
      MaxMemory=1024
      MinMemory=512
      PublicUrl=


Configuration can be applied using the ``nethserver-webtop5-update`` event.

Reset admin password
====================

1. Access the database ::

     su - postgres -c 'psql webtop5'

2. Copy & paste the following query: ::

     UPDATE "core"."local_vault" SET "password_type"='PLAIN', "password"='admin' WHERE ("domain_id"='*') AND ("user_id"='admin');

3. Access the web interface using ``admin`` user with password ``admin``.


Troubleshooting
===============

Please note that nethserver-webtop5 is composed by many parts.
Each part has its own logs and troubleshooting best practices.

Web application
---------------

The web application logs are inside ``/var/log/webtop/webtop.log``.

Tomcat
------

Tomcat instance is managed by systemd unit called ``tomcat@webtop``.
All logs are saved inside ``/var/lib/tomcats/webtop/logs/`` directory.
The logs are rotated daily and deletes after 2 days.

Tomcat output can also be inspected using the following command: ::

  journalctl -u tomcat@webtop

Active Sync
-----------

Active Sync is implemented using a PHP application called z-push.
All logs are inside ``/var/log/z-push/`` directory.

To inspect z-push status use: ::

    php /usr/share/webtop/z-push/z-push-admin.php

It is also possibile to enable z-push debug using these commands: ::

  config setprop webtop ActiveSyncLog LOGLEVEL_DEBUG
  signal-event nethserver-webtop5-update

Instead of ``LOGLEVEL_DEBUG`` you can use any constant supported by z-push implementation.
See ``/usr/share/webtop/z-push/config.php``.

You can test Active Sync using this command (please set user, password and server_name): ::
  
  curl -k -u goofy@local.neth.eu:password https://server_name/Microsoft-Server-ActiveSync

You should see an HTML output containing the string: ::

  GET not supported

CardDAV and CalDAV
------------------
CardDAV and CalDAV are implemented using a PHP application called webtop-dav.
All logs are inside ``/var/log/webtop-dav/`` directory.

It is also possibile to enable webtop-dav debug using these commands: ::

  config setprop webtop DavServerLog DEBUG
  signal-event nethserver-webtop5-update

Instead of ``DEBUG`` you can use any constant supported by ``webtop-dav`` implementation.
See ``/usr/share/webtop/webtop-dav/lib/webtop/Log.php``.

To enable ``browser-plugin`` for directory indexes of the Dav server: ::

  config setprop webtop Debug true
  signal-event nethserver-webtop5-update

Tomcat instance
===============

WebTop uses its own Tomcat instance running on port ``58080``.

The instance is launched with some special Java options,
see content of ``/etc/sysconfig/tomcat@webtop``.

