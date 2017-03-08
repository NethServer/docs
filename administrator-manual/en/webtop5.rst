========
WebTop 5
========

WebTop is a full-featured groupware which implements ActiveSync protocol.

Access to web interface is: ``https://<server_name>/webtop``.

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


