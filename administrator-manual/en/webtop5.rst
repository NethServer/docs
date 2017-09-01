========
WebTop 5
========

WebTop is a full-featured groupware which implements ActiveSync protocol.

Access to web interface is: ``https://<server_name>/webtop``.

.. note::       If |product| is bound to a remote Active Directory account provider
                a dedicated user account in AD is required by the module to be fully
                operational! See :ref:`join-existing-ad-section`.


Authentication
==============

Always use the full user name format ``<user>@<domain>`` for login for the
web application and Active Sync.

**Example**

* Server name: mymail.mightydomain.com
* Alternative mail domain: baddomain.net
* User: goofy
* Login: goofy@mightydomain.com

.. note::
   Active Sync protocol is supported only on Android and iOS devices.
   Outlook is not supported.
   Mail synchronization is currently not supported.


.. _webtop5_admin-section:

Admin user
----------

After installation, WebTop will be accessible via the administrator user.
The administrator user can change global settings and login as all other users,
however, it's not a system user and can't access any other services like Mail, Calendar, etc.

Default credentials are:

* User: *admin*
* Password: *admin*

The administrator user's password must be changed from within the WebTop interface.

.. warning::
   **Remember to change the admin password just after installation!**


To check the mail of the system's user admin account use the following login: admin@<domain> where ``<domain>`` is the
domain part of server FQDN.

**Example**

* Server name: mymail.mightydomain.com
* User: admin
* Login: admin@mightydomain.com

Nextcloud integration
=====================

Nextcloud installation is disabled by default for all users.
To enable Nextcloud integration:

1. Install "Nextcloud" module from :guilabel:`Software Center`.

2. Access WebTop as admin user then enable the Nextcloud authorization:

   - Access the :guilabel:`Administration` menu, then :menuselection:`Domains --> NethServer --> Groups --> Users --> Authorizations`
   - :menuselection:`Add (+) --> Services --> com.sonicle.webtop.vfs (Cloud) --> Resource --> STORE_CLOUD --> Action --> CREATE`
   - :menuselection:`Add (+) --> Services --> com.sonicle.webtop.vfs (Cloud) --> Resource --> STORE_OTHER --> Action --> CREATE
   - Click :guilabel:`OK` then save and close

Chat integration
================

Web chat integration installation is disabled by default for all users.
To enable chat integration:

1. Install "Instant messaging"" module from :guilabel:`Software Center`.

2. Access WebTop as admin user then enable the web chat authorization:

   - Access the :guilabel:`Administration` menu, then :menuselection:`Domains --> NethServer --> Groups --> Users --> Authorizations`
   - :menuselection:`Add (+) --> Services --> com.sonicle.webtop.core (WebTop) --> Resource --> WEBCHAT --> Action --> ACCESS`
   - Click :guilabel:`OK` then save and close

Importing from Outlook PST
==========================

You can import email, calendars and address books from an :index:`Outlook` :index:`PST` archive.

Before using followings scripts, you will need to install *libpst* package: ::

   yum install libpst -y

Also make sure the PHP timezone corresponds to the server timezone: ::

  config getprop php DateTimezone

PHP time zone can be updated using the following command: ::

  config setprop php DateTimezone Europe/Rome
  signal-event nethserver-php-update


Mail
----

Initial script to import mail messages: :file:`/usr/share/webtop/doc/pst2webtop.sh`

To start the import, run the script specifying the PST file and the system user: ::

   /usr/share/webtop/doc/pst2webtop.sh <filename.pst> <user>

Example: ::

  # /usr/share/webtop/doc/pst2webtop.sh data.pst goofy
  Do you wish to import email? [Y]es/[N]o:

All mail messages will be imported. Contacts and calendars will be saved inside a
temporary and the script will output further commands to import contacts and calendars.

Example: ::

  Events Folder found: Outlook/Calendar/calendar
  pst2webtop_cal.php goody '/tmp/tmp.Szorhi5nUJ/Outlook/Calendar/calendar' <foldername>

  ...

  log created: /tmp/pst2webtop14271.log

All commands are saved also in the reported log.

Contacts
--------

Script for contacts import: :file:`/usr/share/webtop/doc/pst2webtop_card.php`.

The script will use files generated from mail import phase: ::

        /usr/share/webtop/doc/pst2webtop_card.php <user> <file_to_import> <phonebook_category>

**Example**

Let us assume that the pst2webtop.sh script has generated following output from mail import: ::

   Contacts Folder found: Personal folders/Contacts/contacts
    Import to webtop:
   ./pst2webtop_card.php foo '/tmp/tmp.0vPbWYf8Uo/Personal folders/Contacts/contacts' <foldername>

To import the default address book (WebTop) of *foo* user: ::

   /usr/share/webtop/doc/pst2webtop_card.php foo '/tmp/tmp.0vPbWYf8Uo/Personal folders/Contacts/contacts' WebTop

Calendars
---------

Script for calendars import: :file:`/usr/share/webtop/doc/pst2webtop_cal.php`

The script will use files generated from mail import phase: ::

        /usr/share/webtop/doc/pst2webtop_cal.php <user> <file_to_import> <foldername>

**Example**

Let us assume that the pst2webtop.sh script has generated following output from mail import: ::

   Events Folder found: Personal folders/Calendar/calendar
    Import to webtop:
   ./pst2webtop_cal.php foo '/tmp/tmp.0vPbWYf8Uo/Personal folders/Calendar/calendar' <foldername>

To import the default calendar (WebTop) of *foo* user: ::

        /usr/share/webtop/doc/pst2webtop_cal.php foo '/tmp/tmp.0vPbWYf8Uo/Personal folders/Calendar/calendar' WebTop

Known limitations:

* only the first occurrence of recurrent events will be imported
* Outlook reminders will be ignored

.. note::
   The script will import all events using the timezone selected by the user inside WebTop, if set.
   Otherwise system timezone will be used.


.. only:: nscom

  WebTop vs SOGo
  ==============

  WebTop and SOGo can be installed on the same machine.

  ActiveSync is enabled by default on SOGo and WebTop, but if both packages are
  installed, SOGo will take precedence.

  To disable ActiveSync on SOGo: ::

    config setprop sogod ActiveSync disabled
    signal-event nethserver-sogo-update

  To disable ActiveSync on WebTop: ::

    config setprop webtop ActiveSync disabled
    signal-event nethserver-webtop5-update


  All incoming mail filters configured within SOGo, must be manually recreated inside WebTop interface.
  This also applies if the user is switching from WebTop to SOGo.


  Google and Dropbox integration
  ==============================

  Users can add their own Google Drive and Dropbox accounts inside WebTop.
  Before proceeding, the administrator must create a pair of API access credentials.

  Google API
  ----------

  * Access https://console.developers.google.com/project and create a new project
  * Create new credentials by selecting "OAuth 2.0 clientID" type and remember to compile
    "OAuth consent screen" section
  * Insert new credentials (Client ID e Client Secret) inside WebTop configuration

  From shell, access webtop database: ::

    su - postgres -c "psql webtop"

  Execute the queries, using the corresponding value in place of ``__value__`` variable: ::

    UPDATE core.settings SET value = '__value__' WHERE service_id = 'com.sonicle.webtop.core' AND key = 'googledrive.clientid';
    UPDATE core.settings SET value = '__value__' WHERE service_id = 'com.sonicle.webtop.core' AND key = 'googledrive.clientsecret';

  Dropbox API
  -----------

  * Access https://www.dropbox.com/developers/apps and create a new app
  * Insert the new credential key pair (App key e App secret) inside WebTop configuration

  From shell, access webtop database: ::

    su - postgres -c "psql webtop"

  Execute the queries, using the corresponding value in place of ``__value__`` variable: ::

    UPDATE core.settings SET value = '__value__' WHERE service_id = 'com.sonicle.webtop.core' AND key = 'dropbox.appkey';
    UPDATE core.settings SET value = '__value__' WHERE service_id = 'com.sonicle.webtop.core' AND key = 'dropbox.appsecret';


  If you need to raise the user limit, please read the official Dropbox documentation.

