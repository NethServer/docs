.. _base_system2-section:

=================
Base system (new)
=================

.. note:: The documentation of the Server Manager is available at :ref:`base_system-section`.

This chapter describes all available modules at the end of installation. All
modules outside this section can be installed from the :ref:`software-center-section` page.

The default installation includes the following main modules:

- :ref:`system-section`
- :ref:`applications-section`
- :ref:`software-center-section`
- :ref:`terminal-section`
-
  .. only:: nscom

    :ref:`subscription-section`

  .. only:: nsent

    :ref:`registration-section`

While the *root* user can see all configuration pages,
access of each section and application may be also delegated to specific users.
See :ref:`delegation-section`.

Many Server Manager applications use netdata to display useful charts.
Since netdata is not installed by default, you can install it from :ref:`software-center-section`.

.. _system-section:

System
======

The :index:`System` page is the landing section after a successful login.
The page will display the :index:`status` and configuration of the system.

From the system dashboard, the administrator can:

* change the machine FQDN and server :ref:`dns_alias-section`
* set upstream :ref:`dns-section` servers
* configure :ref:`date-time-section`
* customize the organization details

The basic system includes also:

* :ref:`network2-section`
* :ref:`services-section`
* :ref:`backup-section`
* :ref:`server_certificate-section`
* :ref:`users_and_groups-section`
* :ref:`tlspolicy-section`
* :ref:`dhcp-section`
* :ref:`dns-section`
* :ref:`ssh-section`
* :ref:`storage-section`
* :ref:`trusted_networks-section`
* :ref:`duc-section`
* :ref:`settings-section`
* :ref:`logs-section`

.. _network2-section:

Network
-------

Besides all features available in the old Server Manager (see :ref:`network-section`),
this page allows to:

- check network status with integrated diagnostic tools like ping, trace route and name lookup
- create a logical network interface without a role: such an interface can be used later in other modules like Dedalo hotspot


.. _services-section:

Services
--------

A remote system can connect to a :index:`network service`, which is a software
running on |product| itself.

Each service can have a list of "open" ports accepting local or remote connections.
To control which zones or hosts can access a network service, see :ref:`firewall-section`.

Existing services can be started and stopped directly from the :guilabel:`Services` page.


.. _storage-section:

Storage
-------

The :index:`storage` section configures and monitors disks.
The administrator can mount new local or remote disks, manage RAID arrays and LVM volumes.


.. _ssh-section:

SSH
---

The :index:`ssh` page displays the number of current SSH connection.
From this section the administrator can change the OpenSSH listening port, disable root login or
password authentication.

.. _settings-section:

Settings
--------

The :index:`settings` page allows the configuration of some options which could impact multiple system applications.

Smart host
^^^^^^^^^^

Many system applications, like cron, can generate mail notification.
If the server can't directly deliver those mails, the administrator can configure
a SMTP relay.
When the smarthost is enabled, all mail messages will be delivered to the configured server.

Email notifications
^^^^^^^^^^^^^^^^^^^

As default, notifications are sent to the local root maildir.
The administrator can change the root forward address adding one or more mail address to the :guilabel:`Destination` field.

It's also a good practice to set a custom :guilabel:`Sender address`: messages from the root user (like cron notifications)
will be sent using the specified address.
A good value could be: ``no-reply@<domain>`` (where ``<domain>`` is the domain of the server).
If not set, messages will be sent using ``root@<fqdn>`` as sender address.

Server Manager
^^^^^^^^^^^^^^

As default, access to the Server Manager is granted from all firewall zones.
From this section the administrator can restrict the access to the Server Manager only to
a list of trusted IP addresses.

Log files
^^^^^^^^^

All log files are managed by :index:`logrotate`. Logrotate is designed to ease administration of a large numbers of log files.
It allows automatic rotation, compression, and removal of log files. Each log file may be handled daily, weekly, monthly.

The administrator can set logrotate defaults from this page. The configuration will apply to all applications.
But please note that some applications can override such configuration to meet specific needs.

Configuration hints
^^^^^^^^^^^^^^^^^^^

Most Server Manager pages can display some configuration hints to help guide the administrator
on a better system configuration.
Hints are just suggestions and can be disabled from this menu.

Password change
^^^^^^^^^^^^^^^

The settings page also includes a panel to let users change their password, including the root user.

.. _logs-section:

Logs
----

The system provides an indexed log named journal.
Journal can be browsed from this page: messages can be filtered by service, severity and date.

.. _applications-section:

Applications
============

The :guilabel:`Applications` page lists all installed applications.
An :index:`application` is a Server Manager module usually composed by multiple pages
including a dashboard, one or more configuration sections and the access to application logs.
A click on the :guilabel:`Settings` button will open the application.

There are also simpler applications which include only a link to an external web pages.
To access such applications click on the :guilabel:`Open` button.

Shortcuts
---------

The administrator can add shortcuts to applications which are frequently used.
Applications with a shortcut, will be linked to the left menu.

Only *root* user has access to this feature.

.. only:: nscom

  Add to home page
  ----------------

  :index:`Launcher` is an application of the new Server Manager available to all users on HTTPS and HTTP ports.
  The launcher is accessible on the server FQDN (eg. ``https://my.server.com``) and it's enabled if
  there is no home page already configured inside the web server (no index page in :file:`/var/www/html`)

  Installed applications can be added to the launcher by clicking on the :guilabel:`Add to home page` button.
  All users will be able to access the public link of the application.

  Only *root* user has access to this feature.

.. only:: nsent

  Launcher
  --------

  See :ref:`launcher-section`.

Removing applications
---------------------

To remove an installed module click :guilabel:`Remove` button on the corresponding application.

.. warning::

   When removing a module other modules could be removed, too! Read carefully
   the list of affected packages to avoid removing required features.

   This feature is not available in |product| Enterprise.


.. _terminal-section:

Terminal
========

Execute a standard shell inside a terminal directly accessible from the browser.
The shell and the processes will run with the user privileges.

.. _delegation-section:

Role delegation
===============

On complex environments, the *root* user can delegate the access of some section
to specific groups of local users.

A local user can be delegated to access:

* one or more pages of the *System* section
* one or more installed applications
* one or more main sections between *Subscription*, *Software Center*

Role delegation is based on local groups, each user belonging to the group will be delegated.
Users inside the *domains admins* are automatically delegated to all panels.

To create a new delegation, access the :guilabel:`User & Groups` page under the group section,
then edit an existing group or create a new one.
Select one or more items from the :guilabel:`System views` and :guilabel:`Applications` menus.

Even if a user has been delegated, it must be explicitly granted the shell access before
being able to log into the Server Manager.

The following pages are always accessible to all users:

* dashboard
* applications
* terminal
