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

User list
---------

All users are listed inside the administrator panel of NextCloud using a unique identifier containing letters and numbers.
This is because the system ensures that there are no duplicate internal user names as reported 
in section `Internal Username` of `Official NextCloud documentation <https://docs.nextcloud.com>`_.

.. note::       If |product| is bound to a remote Active Directory account provider
                a dedicated user account in AD is required by the module to be fully
                operational! See :ref:`join-existing-ad-section`.

Configuration
=============

After installation, the application can be configured from the new Server Manager.

Custom virtual host
-------------------

Sometimes it's better to reserve a full virtual host for accessing Nextcloud like ``nextcloud.nethserver.org``.

Please note that after the configuration of a custom virtual host, Nextcloud will no longer be accessibile from the default URL ``https://your_nethserver_ip/nextcloud``.

If the machine is using :ref:`Let's Encrypt <server_certificate-section>`, remember to add the virtual host domain name to list of valid certificate domains.

Trusted domains
---------------

Trusted domains are a list of domains that users can log into. Default trusted domains are:

* domain name
* ip address

The list of trused domains can be customzized using :guilabel:`Trusted domains` field: add one domain per line.

CalDAV and CardDAV
------------------

Some CalDAV and CardDAV clients may have problems finding the proper sync URL and need automatic service discovery.
Service discovery is enabled by default if a custom virtual host for Nexcloud has been configured.

To enable the service discovery even if Nextcloud is running on the default URL,
check the :guilabel:`Enable CalDAV and CardDAV auto-discovery` field.

.. note:: When enabling DAV auto-discovery, please make sure WebTop or SOGo are *not* already installed.


Collabora Online
----------------

See :ref:`Collabora Online module from NethForge <collabora-section>`.


ONLYOFFICE
----------

Since Nextcloud 18, ONLYOFFICE Community Document Server can be installed directly to the system without further configuration.
To enable built-in ONLYOFFICE integration, access Nextcloud with the ``admin`` user then:

- Go to :guilabel:`Apps` page and access :guilabel:`Office & text` section
- Download and enable the ``ONLYOFFICE`` application
- Download and enable the ``Community Document Server`` application.  Please be patient, download and install will take a while.
- Go to the :guilabel:`Settings` page and access the :guilabel:`ONLYOFFICE` application under :guilabel:`Administration` section
- Verify the :guilabel:`Document Editing Service address` already contains the public address of your Nextcloud server

.. note:: Installation of full ONLYOFFICE server is not supported on |product|.


