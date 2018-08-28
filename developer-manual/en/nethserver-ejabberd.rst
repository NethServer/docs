===================
nethserver-ejabberd
===================

The chat function is implemented using ejabberd jabber server. Enabled features are:

* ldap based roster
* ssl
* admin group

If you want to give admin permissions to an existing user, just add the user to the special group ``jabberadmins``.
The ``jabberadmins`` must be created manually.

When used with AD backend, following limitations apply:

* the shared roster doesn't support groups
* the shared roster displays the list of user names (not full names)

Configuration
=============

Properties:

* *WebAdmin*: enable ejabberd built-in web interfac. Can be ``enabled`` or ``disabled``, default is ``disabled``
* *S2S*: Enable the server-to-server (XMMP federation). can be ``enabled``, default is ``disabled``
* *ModMamStatus*: the new message archive management (mod_mam). can be ``enabled``, default is ``disabled``
* *ModMamPurgeDBStatus*: Purge the Mnesia database of old messages of mod_mam
* *ModMamPurgeDBInterval*: Remove messages older than X days, default is ``30``
* *ShaperFast*: Download speed limit in bytes/second for admin users, default is ``1000000``
* *ShaperNormal*: Download speed limit in bytes/second for users, default is ``500000``


When enabled, web-based administration interface listens on 5280 port.
You need a user inside jabberadmins group to login.

Default access to server ports is set to public on following ports: 5280, 5222, 5223.


The jabber server can be accessed using BOSH protocol (https://xmpp.org/extensions/xep-0206.html) at URL ``/http-bind``.

Example:

* server FQDN: mail.nethserver.org
* BOSH URL: https://mail.nethserver.org/http-bind
