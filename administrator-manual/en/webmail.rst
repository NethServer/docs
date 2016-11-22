=======
Webmail
=======

The default :index:`webmail` client is :index:`Roundcube`.
Roundcube main features are:

* Simple and fast
* Built-in address book integrated with internal LDAP
* Support for HTML messages
* Shared folders support
* Plugins

The webmail is available at the following URLs:

* http://_server_/webmail
* http://_server_/roundcubemail

For example, given a server with IP address *192.168.1.1* and name *mail.mydomain.com*, valid addresses are:

* http://192.168.1.1/webmail
* http://192.168.1.1/roundcubemail
* http://mail.mydomain.com/webmail
* http://mail.mydomain.com/roundcubemail

Plugins
=======

Roundcube supports many plugins already bundled within the installation.

Plugins enabled by default:

* Manage sieve: manage filters for incoming mail
* Mark as junk: mark the selected messages as Junk and move them to the configured Junk folder

Other recommended plugins:

* New mail notifier
* Emoticons
* VCard support


Plugins can be added or removed by editing the comma-separated list inside the ``Plugins`` property.
For example, to enable "mail notification", "mark as junk" and "manage sieve plugins", execute from command line: ::

 config setprop roundcubemail PluginsList managesieve,markasjunk,newmail_notifier
 signal-event nethserver-roundcubemail-update

A list of bundled plugins can be found inside ``/usr/share/roundcubemail/plugins`` directory.
To get the list, just execute: ::

 ls /usr/share/roundcubemail/plugins

Access
======

With default configuration webmail is accessible using HTTPS from any network.

If you want to restrict the access only from green and trusted networks, execute: ::

  config setprop roundcubemail access private
  signal-event nethserver-roundcubemail-update

If you want to open the access from any network: ::

  config setprop roundcubemail access public
  signal-event nethserver-roundcubemail-update
  
Removing
========

You can remove Roundcube to add another webmail type (eg: SOGo, WebTop.…) and you can keep all the mail server RPMs.

To do this only remove Roundcube from the Installed list in the Software Center.

If you want remove Roundcube, remove all the mail server RPMs and no longer have an email system on the server, first remove Roundcube from the Installed list in the Software Center and when it's completed do this step on the server console – either directly or by ssh. ::

   yum autoremove


