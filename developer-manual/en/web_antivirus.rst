.. _squidclamav-section:

=============
Web antivirus
=============

Web antivirus is composed by two components:

* c-icap server: ICAP server for Squid
* squidclamav: ClamAv anti-virus engine for Squid

The nethserver-squidclamav package enables ClamAV inside the c-icap server


Debug
=====

Enable debug to /var/log/c-icap/server.log: ::

  config setprop c-icap DebugLevel 1
  signal-event nethserver-c-icap-update


Database
========

Configuration is kept inside the ``configuration`` database.

Examples: ::

 squidclamav=configuration
    status=enabled

 c-icap=service
    DebugLevel=0
    TemplateDefaultLanguage=en
    status=disabled


The ``TemplateDefaultLanguage`` select the language for ICAP block page, but the block page
is actually implemented in nethserver-squidguard. See :ref:`squidguard-blockpage-section`.

Log files
=========

Blocked page logs:

* Squidclamav: :file:`/var/log/c-icap/server.log`

