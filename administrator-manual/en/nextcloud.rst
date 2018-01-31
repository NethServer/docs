.. _nextcloud-section: 

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

.. note::   Nextcloud update/upgrade procedure disables the apps to avoid incompatibility problems.
            Server logs keep track of which apps were disabled. After a successful update/upgrade procedure
            you can use the Applications page to update and re-enable the apps.

User list
---------

All users are listed inside the administrator panel of NextCloud using a unique identifier containing letters and numbers.
This is because the system ensures that there are no duplicate internal user names as reported 
in section `Internal Username` of `Official NextCloud documentation <https://docs.nextcloud.com>`_.

.. note::       If |product| is bound to a remote Active Directory account provider
                a dedicated user account in AD is required by the module to be fully
                operational! See :ref:`join-existing-ad-section`.

Trusted Domains
===============

Trusted domains are a list of domains that users can log into. Default trusted domains are:

* domain name
* ip address

To add a new one use: ::

    config setprop nextcloud TrustedDomains server.domain.com
    signal-event nethserver-nextcloud-update

To add more than one, concatenate the names with a comma.
