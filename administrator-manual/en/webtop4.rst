========
WebTop 4
========

WebTop is a full-featured groupware which implements ActiveSync protocol.

Access to web interface is: ``https://<server_name>/webtop``.

Authentication
==============

Web interface
-------------

The login to the web application is always with simple user name and password, 
no matters how many mail domains are configured.

**Example**

* Server name: mymail.mightydomain.com
* Alternative mail domain: baddomain.net
* User: goofy
* Login: goofy

Active Sync
-----------

Login to Active Sync account is with <username>@<domain> where ``<domain>`` is the 
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

After installation, WebTop will be accessible with an administrator user.
The administrator user can change global settings and login as all other users,
but it's not a system users and can't access any other services like Mail, Calendar, etc.

Default credentials are:

* User: admin
* Password: admin

Admin user password must be changed from WebTop interface.

.. warning::
   Remember to change the admin password just after installation.


To check the mail of the system user admin use the following login: admin@<domain> where ``<domain>`` is the
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
The same apply if the user is switching from WebTop to SOGo.

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

