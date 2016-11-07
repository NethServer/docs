=========
Nextcloud
=========

`Nextcloud <http://nextcloud.com/>`_ provides universal access to your files via the web,
your computer or your mobile devices wherever you are. It also provides a platform to easily
view and synchronize your contacts, calendars and bookmarks across all your devices and enables
basic editing right on the web.

**Key features:**

* preconfigure :index:`Nextcloud` with MariaDB and default access credential
* integration with |product| system users and groups
* automatic backup data with nethserver-backup-data tool


Installation
============

The installation can be done through the |product| web interface.
After the installation:

* open the url https://your_nethserver_ip/nextcloud
* use **admin/Nethesis,1234** as default credentials
* change the default password

All users configured inside any user provider (see :ref:`users_and_groups-section`) can automatically access the NextCloud installation.
After the installation a new application widget is added to the |product| web interface dashboard.

User list
---------

All users are listed inside the administrator panel of NextCloud using a unique indeitifier containing letters and numenrs.
This is because the system ensures that there are no duplicate internal usernames as reported 
in section `Internal Username` of `Official Netxtcloud documentation <https://docs.nextcloud.com>`_.

Trusted Domains
===============

Trusted domains are a list of domains that users can log into. Default trusted domains are:

* domain name
* ip address

To add a new one use: ::

    config setprop nextcloud TrustedDomains server.domain.com
    signal-event nethserver-nextcloud-update

To add more than one, concatenate the names with a comma.
