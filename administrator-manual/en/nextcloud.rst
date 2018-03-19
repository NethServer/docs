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
* customize https access url (custom virtual host)


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

.. note::   Nextcloud version 13 uses new PHP 7.1 (`nethserver-rh-php71-php-fpm`) while older version uses PHP 5.6 (`nethserver-rh-php56-php-fpm`).
            You can remove php56 version (if there are no dependency problems) with the command "yum remove nethserver-rh-php56-php-fpm".


User list
---------

All users are listed inside the administrator panel of NextCloud using a unique identifier containing letters and numbers.
This is because the system ensures that there are no duplicate internal user names as reported 
in section `Internal Username` of `Official NextCloud documentation <https://docs.nextcloud.com>`_.

.. note::       If |product| is bound to a remote Active Directory account provider
                a dedicated user account in AD is required by the module to be fully
                operational! See :ref:`join-existing-ad-section`.

Custom Virtual Host
===================

To customize the Nextcloud web url: ::

    config setprop nextcloud VirtualHost mynextcloud.domain.com
    config setprop nextcloud TrustedDomains mynextcloud.domain.com
    signal-event nethserver-nextcloud-update

If you use :ref:`let's encrypt <server_certificate-section>` remember to add the domain name to the proper list.


Trusted Domains
===============

Trusted domains are a list of domains that users can log into. Default trusted domains are:

* domain name
* ip address

To add a new one use: ::

    config setprop nextcloud TrustedDomains server.domain.com
    signal-event nethserver-nextcloud-update

To add more than one, concatenate the names with a comma.
