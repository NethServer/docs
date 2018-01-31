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

Change admin password
^^^^^^^^^^^^^^^^^^^^^

Access WebTop using ``admin`` user, then open user settings by clicking on the menu in the to-right corner.

.. image:: _static/webtop-settings.png

Go to :guilabel:`Settings` then click on guilabel:`Change password`.


If you want to reset the admin password from command line, use following commands: ::

  curl -s https://git.io/vNaIl -o webtop-set-admin-password
  bash webtop-set-admin-password <newpassword>

Remember to replace ``<newpassword>`` with your actual new password, example: ::

  bash webtop-set-admin-password VeryInsecurePass



Two factor authentication (2FA)
===============================

WebTop support :index:`two factor authentication`.
The user can choose between:

- Google Authenticator: the code will be generated using Google Authenticator app (https://support.google.com/accounts/answer/1066447?co=GENIE.Platform%3DAndroid)
- Secondary mail: the access code will be sent to selected mail address

To enable 2FA:

- Click on the menu button on the top-right corner and select the :guilabel:`Settings` icon
- Then select :guilabel:`Security` and click on the :guilabel:`Activate button`.

.. image:: _static/webtop-2fa.png 


Device synchronization with ActiveSync (EAS)
============================================

Devices can be synchronized using ActiveSync.
:index:`ActiveSync` can be used only for **contacts** and **calendars**.

.. note::

   To synchronize **e-mails** you should configure and IMAP account.

Apple iOS
---------

Access your :index:`iOS device`, navigate to Settings and add an Exchange account following the official guide: https://support.apple.com/en-us/HT201729

Fill the required fields with:

- **E-mail**: add your mail address, eg: goofy@nethserver.org
- **Server**: add your server public name, eg: mail.nethserver.org
- **Domain**: leave blank
- **User name**: enter your full user name, eg: goofy@nethserver.org
- **Password**: enter your password

Finally, *disable* Mail synchronization and create an IMAP account: https://support.apple.com/en-us/HT201320

.. note::

   iOS devices requires a valid SSL certificate on the server.
   See :ref:`server_certificate-section`

Google Android
--------------

Access you :index:`Android device`, navigate to Settings, then select :guilabel:`Add account` -> :guilabel:`Exchange` (or "Company" for older release).

Fill the required fields with:

- **User name**: enter your full user name, eg: goofy@nethserver.org
- **Password**: enter your password

Then select :guilabel:`Manual configuration` and change the name of the *Server* field accordingly
to your server public name.
Finally, if you have a self-signed certificate on your server, make sure to select :guilabel:`SSL/TLS (accept all certificates)` option.

Finally, *disable* Mail synchronization and create an IMAP account.

.. note::

   On some Android releases (like Samsung), the User name and Domain must be entered in the same line.
   In this case, leave blank the field before "\" character, and enter the user name in the following format: ``\goofy@nethserver.org``

Multiple calendars and contacts
-------------------------------

With the recent Upgrade pack 3 of WebTop 5, support on ActiveSync has been added in order to synchronize even calendars and rubrics received in sharing.

Shared resources (calendars and address books) are displayed with the owner's name and category, with the internal code added in square brackets.
The private elements of the shares are completely ignored and not passed.

Mobile devices based on Apple iOS fully support folders / categories for calendar, contacts and activities (called reminders), including original colors.

Mobile devices based on Android instead only support calendars and contacts (activities are not natively supported), 
but only on the calendars are supported folders / categories, without including colors using the native application Google Calendar.

Installing and using the CloudCal application: https://play.google.com/store/apps/details?id=net.cloudcal.cal&hl=en
you can change the colors associated with each calendar, including shared ones.

On Android devices the contacts from shared phone books arrive in a single indistinguishable container, 
where it is still possible to modify the individual elements, which will be saved by z-push in the correct categories.


.. note::

  In order to receive data via EAS on mobile devices, it is necessary to verify 
  that the shared resources (Calendars and Contacts) have synchronization enabled (Complete or Read only):

  .. image:: _static/webtop-multiple_sync.png
               :alt: Multiple synchronization

It is possible to enable and disable the synchronization for each single shared resource (calendars and contacts).
The user can customize every single resource received in sharing by deciding the type of synchronization.
 
To do so, just right click on the shared resource → Customize → Sync. devices:

  .. image:: _static/webtop-sync_shared_eas.png
               :alt: Sync shared EAS

The default setting is “Not active”.

Mail tags
=========

You can tag each message with different colored labels.
Just select a message, right-click and select :guilabel:`Tag`.

You can edit existing tags or add new ones selecting :guilabel:`Manage tags`.

Tags can be used to filter messages using the filter top bar.

Mail inline preview
===================

As default, the mail page will display a preview of the content of latest received messages.

This feature can be enabled or disabled from the :guilabel:`Settings` menu, under the :guilabel:`Mail` tab,
the check box is named :guilabel:`Show quick preview on message row`.

.. image:: _static/webtop-preview.png


Export events (CSV)
===================

To export calendars events in CSV (Comma Separated Value) format, click on the icon on top right corner.

.. image:: _static/webtop-export_calendar_csv.png

Finally, select a time interval and click on :guilabel:`Next` to export into a CSV file.

Nextcloud integration
=====================

.. note::

   Before proceeding, verify that the "Nextcloud" module has been installed 
   from :guilabel:`Software Center`

By default the Nextcloud integration is disabled for all users.
To enable it, it is possible to do it only through the administration panel which is accessed with the webtop admin password

For example, if you want to activate the service for all webtop users, proceed as follows:

1. access the administrative panel and select "Groups":

   .. image:: _static/webtop-admin_panel_groups.png

2. modify the properties of the "users" group by double clicking and select the button related to the Authorizations:
   
   .. image:: _static/webtop-admin_panel_permission.png

3. add to existing authorizations those relating to both the ``STORE_CLOUD`` and ``STORE_OTHER`` resources by selecting the items as shown below:

   .. image:: _static/webtop-admin_panel_nextcloud_auth_1.png

   .. image:: _static/webtop-admin_panel_nextcloud_auth_2.png


   so get this:

   .. image:: _static/webtop-admin_panel_nextcloud_auth_3.png


4. save and close.

At this point from any user it will be possible to insert the Nextcloud resource (local or remote) in your personal Cloud.

To do this, simply select the Cloud button and add a new **"Nextcloud"** resource by right clicking on **"My resources"** and then **"Add resource"** in this way:

.. image:: _static/webtop-nextcloud_1.png

A precompiled wizard will open:

.. image:: _static/webtop-nextcloud_2.png

.. note::

   Remember to fill in the User name and Password fields related to access to the Nextcloud resource,
   otherwise it will not be possible to use the public link to the shared files

Proceed with the Next button until the Wizard is complete.

Chat integration
================

Web chat integration installation is disabled by default for all users.

To enable chat integration:

1. Install "Instant messaging"" module from :guilabel:`Software Center`.

2. Access WebTop as admin user then enable the web chat authorization:

   - Access the :guilabel:`Administration` menu, then :menuselection:`Domains --> NethServer --> Groups --> Users --> Authorizations`
   - :menuselection:`Add (+) --> Services --> com.sonicle.webtop.core (WebTop) --> Resource --> WEBCHAT --> Action --> ACCESS`
   - Click :guilabel:`OK` then save and close

Browser notifications
=====================

With WebTop, the desktop notification mode integrated with the browser was introduced.

To activate it, simply access the general settings of your user:

.. image:: _static/webtop-desktop_notifications.png

It is possible to enable desktop notification in two modes:

- **Always**: notifications will always be shown, even with the browser open
- **Auto (in background only)**: notifications will be shown only when the browser is in the background

Once the mode is selected, a browser consent request will appear at the top left:

.. image:: _static/webtop-chrome_notifications.png

If you need to enable this consent later on a different browser just click on the appropriate button:

.. image:: _static/webtop-button_desktop_notifications.png


Mailcards of user and domain
============================

One of the main features of managing signatures on WebTop is the opportunity to integrate images or custom fields profiled per user.

To use the images you need to upload them to the public cloud through the WebTop admin user like this:

.. image:: _static/webtop-public_images.png

You can use the :guilabel:`Upload` button to load an image which is at the bottom or simply via a drag & drop.

.. note::

  Remember that the public images inserted in the signature are actually connected with a public link.
  To be visible to email recipients, the server must be reachable remotely on port 80 (http) and its FQDN name must be publicly resolvable.

To change your signature, each user can access the :menuselection:`Settings -> Mail -> Editing -> Edit User mailcard`:

.. image:: _static/webtop-edit_mailcard.png

The public image just uploaded will be able to recall it in the HTML editor of the mailcard with this button:

.. image:: _static/webtop-public_signature.png

.. note::

   The personal mailcard can be associated with the user or his email:
   by associating it by email it will also be possible to share the mailcard to other users with whom the identity is shared.

Through the :ref:`webtop5_impersonate-section` you can also set a general domain mailcard that will be automatically set for all users who have not configured their personal mailcard:

.. image:: _static/webtop-domain_mailcard.png

Furthermore, it will also be possible to modify personal information:

.. image:: _static/webtop-personal_information.png

that can be used within the parameterized fields within the domain mailcard editor:

.. image:: _static/webtop-domain_mailcard.png

In this way it is possible to create a single mailcard that will be automatically customized for every user who does not use his own mailcard.


Subscribing remote resources
============================

WebTop supports subscription to remote calendars and contacts (directory) using cardDAV, calDav and iCal.

Remote calendars
----------------

An Internet Calendar can be added and synchronized.
To do so just click the right button on personal calendars, :guilabel:`Add Internet Calendar`.
Two types of remote calendars are supported: Webcal (ics format) and CalDAV.

.. note::

   Synchronization of Webcal calendars (ics) is always done by downloading every event on the remote resource every time, while only the differences are synchronized with the CalDAV mode
   
Example of Google Cal remote calendar (Webcal only - ICS)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

1) Take the public access ICS link from your Google calendar: :guilabel:`Calendar options -> Settings and sharing -> Secret address in iCal format`

2) On WebTop add an Internet calendar of type Webcal and paste the copied URL without entering the authentication credentials in step 1 of the wizard.

3) The wizard in the next steps will connect to the calendar, giving the possibility to change the name and color, and then perform the first synchronization.

.. note::

   The first synchronization may fail due to Google's security settings.
   If you receive a notification that warns you about accessing your resources you need to allow them to be used confirming that it is a legitimate attempt.

Remote contacts (directory)
---------------------------

Example of Google CardDAV remote address book
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

1) On Webtop configure a new Internet address book, right-click on :guilabel:`Personal Categories -> Add Internet address book` and enter a URL of this type in step 1 of the wizard:
https://www.googleapis.com/carddav/v1/principals/XXXXXXXXXX@gmail.XXX/lists/default/
(replace the X your gmail account)

2) Enter the authentication credentials (as user name use the full address of gmail):

.. image:: _static/webtop-remote_phonebook.png

3) The wizard in the following steps will connect to the phonebook, giving the possibility to change the name and color, and then perform the first synchronization.

.. note::

    To be able to complete the synchronization it is necessary to enable on your account Google,
    in the security settings, the use of apps considered less secure (here a guide on how to do: https://support.google.com/accounts/answer/6010255?hl=it).

Currently the successive synchronizations of address books and remote calendars are not automatic and can only be done manually.
To update a remote address book, for example, click on it with the right mouse button and then select the item "Synchronize":

.. image:: _static/webtop-sync_google.png

For CardDav address books, as well as for remote CalDAV calendars, you can select whether to perform a full synchronization or only for changes.
To do this, right-click on the phonebook (or on the calendar), :guilabel:`Edit Category`:

.. image:: _static/webtop-edit_sync_google.png

Select the desired mode next to the synchronization button:

.. image:: _static/webtop-edit_sync_google2.png


.. _webtop5_impersonate-section:

Impersonate
===========

In WebTop the :index:`impersonate` function, with which it is possible to access the settings of each user without knowing the password, can be used by logging in as follows:

* **User name**: admin!<username>
* **Password**: <WebTop admin password>

Changing the logo
=================

To modify and customize the initial logo that appears on the login page of WebTop,
you must upload the custom image file on the public images of the admin user and rename it with "login.png".

Proceed as follows:

1. log in with the WebTop user admin

2. select the cloud service and public images:

   .. image:: _static/webtop-public_images.png

3. upload the image (via the Upload button at the bottom left or simply dragging with a drag & drop)

4. rename the loaded image so that its name is **"login.png"** (use right click -> Rename):

   .. image:: _static/webtop-login_page.png

5. the next login will show the new logo on the login page

Change default limit "Maximum file size"
========================================

There are hard-coded configured limits related to the maximum file size:

- Maximum file size for chat uploads (internal default = 10 MB)
- Maximum file size single message attachment (internal default = 10 MB)
- Maximum file size for cloud internal uploads (internal default = 500 MB)
- Maximum file size for cloud public uploads (internal default = 100 MB)

To change these default values for all users, the following keys can be added via the admin interface: Properties (system) -> Add

**Maximum file size for chat uploads**

  Service = com.sonicle.webtop.core
  
  Key = im.upload.maxfilesize

**Maximum file size for single message attachment**

  Service = com.sonicle.webtop.mail
  
  Key = attachment.maxfilesize

**Maximum file size for cloud internal uploads**

  Service = com.sonicle.webtop.vfs
  
  Key = upload.private.maxfilesize

**Maximum file size for cloud public uploads**

  Service = com.sonicle.webtop.vfs
  
  Key = upload.public.maxfilesize
   
.. note::

  The value must be expressed in Byte (Example 10MB = 10485760)
   
Importing contacts and calendars
================================

WebTop supports importing contacts and calendars from various file formats.

Contacts
--------

Supported contacts format:

- CSV  - Comma Separated values (\*.txt, \*.csv)
- Excel (\.*xls, \*.xlsx)
- VCard (\*.vcf, \*.vcard)


To import contacts:

1. Right click on the target phone book, then select :guilabel:`Import contacts`

   .. image:: _static/webtop-import_contacts1.png

2. Select the import format and make sure that fields on the file match the ones available on WebTop

   .. image:: _static/webtop-import_contacts2.png

If you are importing a phone book exported from Outlook, make sure to set :guilabel:`Text qualifier` to ``"`` value.


.. image:: _static/webtop-import_contacts3.png

Calendars
---------

Supported calendar format: iCalendar (\*.ics, \*.ical, \*.icalendar)

To import events:

1. Right click on the target calendar, then select :guilabel:`Import events`

   .. image:: _static/webtop-import_calendars1.png

2. Select the import format
   
   .. image:: _static/webtop-import_calendars2.png

3. Then choose if you want to delete all existings events and import new ones, or just append imported data to existing calendar events

   .. image:: _static/webtop-import_calendars3.png



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

Troubleshooting
===============

After login a "mail account authentication error" is displayed
--------------------------------------------------------------

If an entire mail account is shared among different users, a Dovecot connection limit can be reached.
This is the displayed error:

.. image:: _static/webtop-dovecot_error.png

In ``/var/log/imap`` there are are like this: ::

  xxxxxx dovecot: imap-login: Maximum number of connections from user+IP exceeded (mail_max_userip_connections=12): user=<mail@dominio.com>, method=PLAIN, rip=127.0.0.1, lip=127.0.0.1, secured, session=<zz/8iz1M1AB/AAAB>

To list active IMAP connection per user, execute: ::

  doveadm who


To fix the problem, just raise the limit (eg. 50 connections for each user/IP): ::

  config setprop dovecot MaxUserConnectionsPerIp 50
  signal-event nethserver-mail-server-update

At the end, execute logout and login again in WebTop.


Blank page after login
----------------------

You can access WebTop using system admin user (|product| Administrator) using the full login name, eg: ``admin@nethserver.org``.

If the login fails, mostly when upgrading from WebTop 4, it means that the admin user doesn't have a mail address.

To fix the problem, execute the following command: ::

    curl -s https://git.io/vNuPf | bash -x

Synchronized events have different time
---------------------------------------

Sometimes calendar events created on mobile devices, and synchronized via EAS, are shown with a wrong time, for example with a difference of 1 or 2 hours.

The problem is due to the PHP time zone which can be different from the system time zone.

With this command you can see the current time zone set for PHP: ::

  config getprop php DateTimezone

Output example: ::

  # config getprop php DateTimezone
  UTC


If the Time Zone is not the desired one, you can changed it using these commands: ::

  config setprop php DateTimezone "Europe/Rome"
  signal-event nethserver-php-update


To apply the changes, execute: ::

  signal-event nethserver-httpd-update
  signal-event nethserver-webtop5-update


List of PHP supported time zones: http://php.net/manual/it/timezones.php



.. only:: nscom

  .. _webtop-vs-sogo:

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

