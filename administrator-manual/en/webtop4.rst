========
WebTop 4
========

WebTop is a full-featured groupware which implements ActiveSync protocol.

Access to web interface is: ``https://<server_name>/webtop``.

Authentication
==============

Web interface
-------------

The login method to the web application is with a simple user name and password,
regardless of how many mail domains are configured.

**Example**

* Server name: mymail.mightydomain.com
* Alternative mail domain: baddomain.net
* User: goofy
* Login: goofy

Active Sync
-----------

Logging in to the Active Sync account can be accomplished with <username>@<domain> where ``<domain>`` is the 
domain part of server FQDN.

**Example**

* Server name: mymail.mightydomain.com
* Alternative mail domain: baddomain.net
* User: goofy
* Login: goofy@mightydomain.com

When configuring an Active Sync account, make sure to specify the server
address and leave the domain field empty.

.. note::
   Active Sync protocol is supported only on Android and iOS devices.
   Outlook is not supported.
   Mail synchronization is currently not supported.


.. _webtop_admin-section:

Admin user
----------

After installation, WebTop will be accessible via the administrator user.
The administrator user can change global settings and login as all other users,
however, it's not a system user and can't access any other services like Mail, Calendar, etc.

Default credentials are:

* User: admin
* Password: admin

The administrator user's password must be changed from within the WebTop interface.

.. warning::
   **Remember to change the admin password just after installation!**


To check the mail of the system's user admin account use the following login: admin@<domain> where ``<domain>`` is the
domain part of server FQDN.

**Example**

* Server name: mymail.mightydomain.com
* User: admin
* Login: admin@mightydomain.com

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
  signal-event nethserver-webtop4-update


All incoming mail filters configured within SOGo, must be manually recreated inside WebTop interface.
This also applies if the user is switching from WebTop to SOGo.

Active Directory authentication
===============================

After an Active Directory domain has been joined, access WebTop administration page,
then from tree menu on the left, select :guilabel:`Domain` -> :guilabel:`NethServer`.

Edit the following fields:

* Authentication Uri: select ``ldapAD`` mode and insert the full FQDN of the server and port 389.
  Example: w2k8.nethserver.org:389

* Admin LDAP: user name of AD domain administrator

* LDAP Password: user password of AD domain administrator

After saving, the page :guilabel:`Users` will display users from Active Directory.

Importing from SOGo
===================

**Please read all directions before importing any data to ensure import is successful**

Migration of Calendar and Address book data from SOGo to Webop can be accomplished by using the following scripts, and following the steps listed below:

* Calendars: :file:`/usr/share/webtop/doc/sogo2webtop_cal.php`
* Address books: :file:`/usr/share/webtop/doc/sogo2webtop_card.php`

Before using the scripts you need to install this package: ::

  yum install php-mysql -y

When launching the scripts, indicate the user name you want to import from SOGo: ::
 
  php /usr/share/webtop/doc/sogo2webtop_cal.php <user>
  php /usr/share/webtop/doc/sogo2webtop_card.php <user>

Where ``user`` can be a username or ``all``.

**Examples**

To import all address books from SOGo: ::

  php /usr/share/webtop/doc/sogo2webtop_card.php all

To import the calendar of user "foo": ::
 
  php /usr/share/webtop/doc/sogo2webtop_cal.php foo

.. note::
   If the script is executed multiple times, both calendars and address books will be imported multiple times.
   Import of distribution lists and recurring events are not currently supported.

Importing from Outlook PST
==========================

You can import email, calendars and address books from an :index:`Outlook` :index:`PST` archive.

Before using followings scripts, you will need to install *libpst* package: ::

   yum install libpst -y

Mail
----

Initial script to import mail messages: :file:`/usr/share/webtop/doc/pst2webtop.sh`
   
To start the import, run the script specifying the PST file and the system user: ::

   /usr/share/webtop/doc/pst2webtop.sh <filename.pst> <user>

All mail messages will be imported. Contacts and calendars will be saved inside a 
temporary files for later import.
The script will list all created temporary files.

Contacts
--------

Script for contacts import: :file:`/usr/share/webtop/doc/pst2webtop_card.php`.

The script will use files generated from mail import phase: ::

        /usr/share/webtop/doc/pst2webtop_card.php <user> <file_to_import> <phonebook_category>
        
**Example**

Let us assume that the pst2webtop.sh script has generated following output from mail import: ::

   Contacts Folder found: Cartelle personali/Contatti/contacts
    Import to webtop:
   ./pst2webtop_card.php foo '/tmp/tmp.0vPbWYf8Uo/Cartelle personali/Contatti/contacts' <foldername>
   
To import the default address book (WebTop) of *foo* user: ::

   /usr/share/webtop/doc/pst2webtop_card.php foo '/tmp/tmp.0vPbWYf8Uo/Cartelle personali/Contatti/contacts' WebTop
  
Calendars
---------
 
Script for calendars import: :file:`/usr/share/webtop/doc/pst2webtop_cal.php`

The script will use files generated from mail import phase: ::

        /usr/share/webtop/doc/pst2webtop_cal.php <user> <file_to_import> <foldername>
        
**Example**

Let us assume that the pst2webtop.sh script has generated following output from mail import: ::

   Events Folder found: Cartelle personali/Calendario/calendar
    Import to webtop:
   ./pst2webtop_cal.php foo '/tmp/tmp.0vPbWYf8Uo/Cartelle personali/Calendario/calendar' <foldername>

To import the default calendar (WebTop) of *foo* user: ::

        /usr/share/webtop/doc/pst2webtop_cal.php foo '/tmp/tmp.0vPbWYf8Uo/Cartelle personali/Calendario/calendar' WebTop

.. note::
   The script will import all events using the timezone selected by the user inside WebTop, if set.
   Otherwise system timezone will be used.

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

    INSERT INTO settings (idsetting,value) VALUES ('main.googledrive.clientid', '__value__');
    INSERT INTO settings (idsetting,value) VALUES ('main.googledrive.clientsecret', '__value__');

Dropbox API
-----------

* Access https://www.dropbox.com/developers/apps and create a new app
* Insert the new credential key pair (App key e App secret) inside WebTop configuration

  From shell, access webtop database: ::

    su - postgres -c "psql webtop"

  Execute the queries, using the corresponding value in place of ``__value__`` variable: ::

    INSERT INTO settings (idsetting,value) VALUES ('main.googledrive.clientsecret', '__value__');
    INSERT INTO settings (idsetting,value) VALUES ('main.dropbox.appsecret', '__value__');


If you need to raise the user limit, please read the official Dropbox documentation.


.. note::
   The Enterprise version is already integrated with Google and Dropbox.
