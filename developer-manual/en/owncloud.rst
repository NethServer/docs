========
ownCloud
========

Configuration
=============

With clear installation the ``autoconfig.php`` file is used to create an initial default configuration in: ::

 /var/www/html/owncloud/config/config.php

It does the following:

* create ``owncloud`` mysql database
* create default database credentials: user `"ownuser"` and password stored in ``/var/lib/nethserver/secrets/ownuser``
* add trusted domains to use with web access
* create default credentials for web login: user `"admin"` and password `"Nethesis,1234"`
* set english as the default language
* set the user data directory as ``/var/www/html/owncloud/data``

This task is accomplished by the action: ::

 /etc/e-smith/events/actions/nethserver-owncloud-conf

LDAP authentication
===================

It is enabled by default when clear install ownCloud and can be `manually activated <http://nethserver.readthedocs.org/en/latest/owncloud.html#ldap-configuration>`_ in the update scenario.

To do the automatic configuration a patched version of the ``occ`` command line tool has been used. The patch add the ``ldap:create-empty-config`` command as explained `here. <https://github.com/owncloud/core/pull/11347>`_ The patched files are: ::

 /var/www/html/owncloud/apps/user_ldap/command/createemptyconfig.php
 /etc/e-smith/templates/var/www/html/owncloud/apps/user_ldap/appinfo/register_command.php/register_command.php

The configuration is made by the action: ::

 /etc/e-smith/events/actions/nethserver-owncloud-conf-ldap

It does the following:

* first access to ownCloud url using the ``curl`` to initialize all values of the database
* enable the `"user_ldap"` application
* create an empty ldap configuration (using the patch)
* set all the database ldap values

In the update scenario the action only does the upgrade of the database.


Event
=====

The event is: ``nethserver-owncloud-update``. It executes the actions: ::

 /etc/e-smith/events/actions/nethserver-owncloud-conf
 /etc/e-smith/events/actions/nethserver-owncloud-conf-ldap

expand the `ownCloud` and `httpd` templates and restart the `httpd` server.


Backup
======

The ownCloud backup includes the configuration file and all data of the users: ::

 /var/www/html/owncloud/data/
 /var/www/html/owncloud/config/config.php

The database is automatically saved by ``nethserver-mysql``.
