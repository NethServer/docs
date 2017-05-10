====================
nethserver-nextcloud
====================

This package can be installed before or after any user provider like nethserver-dc
and nethserver-directory.

If nethserver-dc or nethserver-directory are installed, the nethserver-nextcloud-save
event will automatically enable all local users.

The package does the following:

* create ``nextcloud`` mysql database
* create default database credentials: user `nextcloud` and password stored in ``/var/lib/nethserver/secrets/nextcloud``
* add trusted domains to use with web access
* create default credentials for web login: user `"admin"` and password `"Nethesis,1234"`
* set english as the default language
* set the user data directory as ``/var/lib/nethserver/nextcloud``

The configuration is stored inside the ``configuration`` db, under the ``nextcloud`` key.

Properties:

* ``TrustedDomains``: list of trusted domains added to Nextcloud config file


Admin user
==========

After installation the application is accesible using the following credentials:

* User: admin
* Password: Nethesis,1234

Please, remember to change the default password after the first login!

Backup
======

The Nextcloud backup includes the configuration file and all data of the users: ::

 /var/lib/nethserver/nextcloud
 /usr/share/nextcloud/config/config.php

The database is automatically saved by ``nethserver-mysql``.

