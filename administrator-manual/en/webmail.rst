=======
Webmail
=======

The default :index:`webmail` client is :index:`Roundcube`.
Roundcube's main features are:

* Simple and fast
* Built-in address book integrated with internal LDAP
* Support for HTML messages
* Shared folders support
* Plugins

The webmail is accessible directly from *Applicatons* page, just click on the :guilabel:`Open` button.
It is available at the following URLs:

* http://_server_/webmail
* http://_server_/roundcubemail

For example, given a server with IP address *192.168.1.1* and name *mail.mydomain.com*, valid addresses are:

* http://192.168.1.1/webmail
* http://192.168.1.1/roundcubemail
* http://mail.mydomain.com/webmail
* http://mail.mydomain.com/roundcubemail

.. note::       If |product| is bound to a remote Active Directory account provider
                a dedicated user account in AD is required by the module to be fully
                operational! See :ref:`join-existing-ad-section`.

Plugins
=======

Roundcube supports many plugins that are already bundled within the installation.

The plugins that are enabled by default are:

* Manage sieve: manage filters for incoming mail
* Mark as junk: mark the selected messages as Junk and move them to the configured Junk folder

Recommended plugins:

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

Skins
=====

A list of bundled skins can be found inside ``/usr/share/roundcubemail/skins`` directory.
To get the list, just execute: ::

 ls /usr/share/roundcubemail/skins

The default skin is ``larry``. If you want to set the ``elastic`` skin as the default skin: ::

 config setprop roundcubemail skin elastic
 signal-event nethserver-roundcubemail-update

Please note that each user can override the default skin in the settings > preferences > User Interface of roundcubemail

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

If you want remove Roundcube, run the following command on the server command line. ::

   yum autoremove nethserver-roundcubemail


