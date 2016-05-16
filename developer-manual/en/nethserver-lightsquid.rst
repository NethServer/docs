============================
LightSquid: Web Proxy report
============================

LightSquid is a lite and fast log analizer for squid proxy.
It parses :file:`/var/log/squid/access.log` log file on daily basis and generate
an HTML report.

LightSquid is enabled by default when the nethserver-lightsquid package is installed.
Web interface can be accessed at ``http://<server>/<hash>``.

The hash is auto-generated (see below).

Database
========

The configuration is saved in the ``lightsquid`` key inside the ``configuration`` database.

Example: ::

 lightsquid=configuration
    alias=44da17a293c2aae17815bb95af98883355520aef

