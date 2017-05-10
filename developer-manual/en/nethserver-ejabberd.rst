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
* *WelcomeSubject*: subject to be shown in the welcome message, default value is empty
* *WelcomeText*: welcome message, default value is empty
* *XMPPAccess*: enable TLS access if value is ``tls``, which is the default value. If empty, TLS is disabled.

When enabled, web-based adminsitration interface listens on 5280 port.
You need a user inside jabberadmins group to login.

Default access to server ports is set to public on following ports: 5280, 5222, 5223.


The jabber server can be accessed using BOSH protocol (https://xmpp.org/extensions/xep-0206.html) at URL ``/http-bind``.

Example:

* server FQDN: mail.nethserver.org
* BOSH URL: https://mail.nethserver.org/http-bind
