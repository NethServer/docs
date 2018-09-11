.. _SOGo-section:

====
SOGo
====

.. note::

  This package is not supported in |product| Enterprise 

SOGo is a fully supported and trusted groupware server with a focus on scalability and open standards. SOGo is released under the GNU GPL/LGPL v2 and above.
SOGo provides a rich AJAX-based Web interface and supports multiple native clients through the use of standard protocols such as CalDAV, CardDAV and GroupDAV, as well as Microsoft ActiveSync.
SOGo is the missing component of your infrastructure; it sits in the middle of your servers to offer your users a uniform and complete interface to access their information. It has been deployed in production environments where thousands of users are involved.


.. note::

  SOGo provides EAS (Exchange ActiveSync) support, but not EWS (Exchange Web Service).
  Outlook 2013, 2016 for Windows works well with EAS.
  Mainstream mobile devices (iOS, Android, BlackBerry 10) work well with EAS, they can sync mails, calendars, contacts, tasks.
  Apple Mail.app, and Outlook for Mac support EWS. But not EAS.
  **Clients work very well with POP3/IMAP account, caldav/carddav account**

.. warning::

 ``nethserver-sogo`` doesn't integrate OpenChange and Samba4 for native MAPI support, so SOGo groupware doesn't provide full support for Microsoft Outlook clients, Mac OS X Mail.app and all iOS devices, don't try to add your mail account as an Exchange account in these mail clients. You have to add account as POP3/IMAP account, caldav/carddav account instead.


Installation
============

.. note::

  You need first to set an account provider which can be local (nethserver-directory for openldap or nethserver-dc for Samba AD) or remote (whatever openldap or samba AD choice). You cannot mix your choice by openldap and Samba AD, preferably if you plan to host samba shares with user authentication, you need samba AD (nethserver-dc)


Then install from the Software Center or use the command line: ::

  yum install nethserver-sogo


Official documentation
======================

Please read `official documentation <https://sogo.nu/files/docs/SOGoInstallationGuide.html>`_: your solution is in this book.

Usage
=====

The URL of the groupware is https://yourdomain.com/SOGo. You can use the '``username`` or ``username@domain.com`` for login.

Esmith database
================

You can modify the available properties of SOGo: ::

  sogod=service
    ActiveSync=enabled
    AdminUsers=admin
    BackupTime=30 0
    Certificate=
    Dav=enabled
    DraftsFolder=Drafts
    IMAPLoginFieldName=userPrincipalName
    MailAuxiliaryUserAccountsEnabled=YES
    Notifications=Appointment,EMail              #'Folder'/'ACLs'/'Appointment'
    SOGoInternalSyncInterval=10
    SOGoMaximumPingInterval=10
    SOGoMaximumSyncInterval=30
    SOGoMaximumSyncResponseSize=2048
    SOGoMaximumSyncWindowSize=100
    SentFolder=Sent
    SxVMemLimit=512
    TrashFolder=Trash
    VirtualHost=
    WOWatchDogRequestTimeout=10
    WOWorkersCount=10
    status=enabled


Properties:

* AdminUsers: Parameter used to set which usernames require administrative privileges over all the users tables.
* BackupTime: Time to launch the backup, by default ('30 0')each day at 00h30, you can change it if you set a cron compatible value ``* *``
* DraftsFolder: name of draft folder, default is ‘Drafts’
*  IMAPLoginFieldName: adjust the imap login field to your good trusted value in your ldap (see https://community.nethserver.org/t/sogo-and-ad-brainstorming/8024/31)
* SentFolder: name of the sent folder, default is ‘Sent’
* TrashFolder: name of the trash folder, default is ‘Trash’
* WOWorkersCount: The amount of instances of SOGo that will be spawned to handle multiple requests simultaneously
* MailAuxiliaryUserAccountsEnabled: Parameter used to activate the auxiliary IMAP accounts in SOGo. When set to YES, users can add other IMAP accounts that will be visible from the SOGo Webmail interface.
* Notifications: enabled notifications. The value is a comma separated list. Default value is “Appointment, EMail”

**Notes**

Terms highlighted in **bold** are documented in SOGo `installation and configuration guide <https://sogo.nu/files/docs/SOGoInstallationGuide.html#_preferences_hierarchy>`_.

* ``AdminUsers`` comma separated list of accounts allowed to bypass SOGo ACLs. See **SOGoSuperUsernames** key
* Notifications comma separated list of values (no spaces between commas). Known item names are ``ACLs``, ``Folders``, ``Appointments``. See **SOGoSendEMailNotifications**
* ``{Drafts,Sent,Trash}Folder`` See respective **SOGoFolderName** parameters
* ``VirtualHosts`` SOGo is reachable from the default host name plus the host (FQDN) listed here. The host key is generated/removed in ``hosts`` DB, with ``type=self`` automatically.



Access SOGo on an exclusive hostname
====================================

To make SOGo accessible with an exclusive DNS hostname:

* In “DNS and DHCP” UI module (Hosts), create the DNS host name as a server alias (i.e. webmail.example.com)

* Add the host name to sogod/VirtualHost prop list: ::

    config setprop sogod VirtualHost webmail.example.com
    signal-event nethserver-sogo-update

Same rule applies if SOGo must be accessible using server IP address. For example: ::

  config setprop sogod VirtualHost 192.168.1.1
  signal-event nethserver-sogo-update

If the VirtualHost prop is set, requests to the root (i.e. webmail.example.com) are redirected to the (mandatory) /SOGo subfolder (webmail.example.com/SOGo). 

It is also possible to use a custom certificate for this virtualhost: ::

  config setprop sogod Certificate example.crt
  signal-event nethserver-sogo-update


Maximum IMAP command
====================

Maximum IMAP command line length in kilo bytes. Some clients generate very long command lines with huge mailboxes, so you may need to raise this if you get "Too long argument" or "IMAP command line too large" errors often.

Set by default to 2048KB: ::

  config setprop dovecot ImapMaxLineLenght 2048
  signal-event nethserver-sogo-update
  
ActiveSync
==========

According to this :ref:`webtop-vs-sogo`, WebTop and SOGo can be installed on the same machine, although it is discouraged to keep such setup on the long run.

ActiveSync is enabled by default on SOGo and WebTop. At installation of SOGo, Webtop-ActiveSync is disabled and SOGo will take precedence.

SOGo-ActiveSync can be disabled in the server-manager at the SOGo-panel or with: ::

  config setprop sogod ActiveSync disabled
  signal-event nethserver-sogo-update

To enable ActiveSync on WebTop: ::

  config setprop webtop ActiveSync enabled
  signal-event nethserver-webtop5-update

To enable ActiveSync on SOGo again: ::

  config setprop sogod ActiveSync enabled
  signal-event nethserver-sogo-update

Backup
======

Each night (by default) a cron run to backup user data (filter rules, specific settings, events, contacts) and save it to ``/var/lib/sogo/backups``
you can restore the data with a tool ``sogo-restore-user``, for example: ::

  sogo-restore-user /var/lib/sogo/backups/sogo-2017-12-10_0030/ stephane

or for all users ::

  sogo-restore-user /var/lib/sogo/backups/sogo-2017-12-10_0030/ -A

if you want to change the time of your backup for example (in this example, run at 4h01 AM): ::

  config setprop sogod BackupTime '1 4'
  signal-event nethserver-sogo-update

Fine tuning
===========

Adjust Setting
--------------

SOGo `must be tuned <https://sogo.nu/files/docs/SOGoInstallationGuide.html#_microsoft_enterprise_activesync_tuning>`_ following the number of users, some settings can be tested.

.. note:: 

  Keep in mind to set one worker per user for the activesync connection.


100 users, 10 EAS devices: ::

  config setprop sogod WOWorkersCount 15
  config setprop sogod SOGoMaximumPingInterval 3540
  config setprop sogod SOGoMaximumSyncInterval 3540
  config setprop sogod SOGoInternalSyncInterval 30
  signal-event nethserver-sogo-update

100 users, 20 EAS devices: ::

  config setprop sogod WOWorkersCount 25
  config setprop sogod SOGoMaximumPingInterval 3540
  config setprop sogod SOGoMaximumSyncInterval 3540
  config setprop sogod SOGoInternalSyncInterval 40
  signal-event nethserver-sogo-update

1000 users, 100 EAS devices: ::

  config setprop sogod WOWorkersCount 120
  config setprop sogod SOGoMaximumPingInterval 3540
  config setprop sogod SOGoMaximumSyncInterval 3540
  config setprop sogod SOGoInternalSyncInterval 60
  signal-event nethserver-sogo-update

Increase sogod log verbosity
----------------------------

Read the `SOGo FAQ <http://www.sogo.nu/nc/support/faq/article/how-to-enable-more-verbose-logging-in-sogo.html>`_ for other debugging features.

SOGo floods /var/log/messages
-----------------------------

You can see this log noise in ``/var/log/message``:

::

  Dec  4 12:36:01 ns7ad1 systemd: Created slice User Slice of sogo.
  Dec  4 12:36:01 ns7ad1 systemd: Starting User Slice of sogo.
  Dec  4 12:36:01 ns7ad1 systemd: Started Session 163 of user sogo.
  Dec  4 12:36:01 ns7ad1 systemd: Starting Session 163 of user sogo.
  Dec  4 12:36:01 ns7ad1 systemd: Removed slice User Slice of sogo.
  Dec  4 12:36:01 ns7ad1 systemd: Stopping User Slice of sogo.


These messages are normal and expected -- they will be seen any time a user logs in. 
To suppress these log entries in ``/var/log/messages``, create a discard filter with rsyslog, e.g., run the following command: ::

 echo 'if $programname == "systemd" and ($msg contains "Starting Session" or $msg contains "Started Session" or $msg contains "Created slice" or $msg contains "Starting User" or $msg contains "Removed slice User" or $msg contains "Stopping User") then stop' > /etc/rsyslog.d/ignore-systemd-session-slice-sogo.conf

and restart rsyslog ::

  systemctl restart rsyslog

this solution comes from `RedHat solution <https://access.redhat.com/solutions/1564823>`_

Clients
=======

Android
-------

Currently you have 2 ways to integrate your Android device with Sogo.

Integration via Caldav /Cardav/imap
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. note::

  The drawback is that you need to set all settings (Url/Username/Password) in each application.

* Email

Imaps(over ssl) is a good choice, you can use the K9-mail software to retrieve your email or the default email application

* Contacts and calendars

There are various working clients, including `DAVdroid <https://davdroid.bitfire.at>`_ (open-source) and `CalDAV-Sync/CardDav-Sync <http://dmfs.org/>`_.
Advantages Full integration into Android, so that almost all calendar and contacts apps can access synchronized data. 

Integration via ExchangeActiveSync
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. note::

  The advantage is that you set the Url/Username/Password only in one location

Step-by-step configuration
^^^^^^^^^^^^^^^^^^^^^^^^^^

* Open the account menu, choose add an exchange account
* Fill your full email address and password in Account Setup page:
* If it asks you to choose Account Type, please choose Exchange:
* In detailed account setup page, fill up the form with your server address and email account credential

  * Domain\Username: your full email address
  * Password: password of your email account
  * Server: your server name or IP address
  * Port: 443

.. note::

    Please also check Use secure connection (SSL) and Accept all SSL certificates


* In Account Settings page, you can choose Push. it's all up to you.
* Choose a name for your Exchange account.
* Click Next to finish account setup. That's all.


Mozilla Thunderbird and Lightning
---------------------------------

Alternatively, you can access SOGo with a GroupDAV and a CalDAV client. A typical well-integrated setup is to use Mozilla Thunderbird and Mozilla Lightning along with Inverse’s SOGo Connector plug in to synchronize your address books and the Inverse’s SOGo Integrator plug in to provide a complete integration of the features of SOGo into Thunderbird and Lightning. Refer to the documentation of Thunderbird to configure an initial IMAP account pointing to your SOGo server and using the user name and password mentioned above.

With the `SOGo Integrator plug in <https://sogo.nu/download.html#/frontends>`_, your calendars and address books will be automatically discovered when you login in Thunderbird. This plug in can also propagate specific extensions and default user settings among your site. However, be aware that in order to use the SOGo Integrator plug in, you will need to repackage it with specific modifications. Please refer to the `documentation published online <http://sogo.nu/downloads/documentation.html>`_.

If you only use the SOGo Connector plug in, you can still easily access your data.

* To access your personal address book:
* Choose Go > Address Book.
* Choose File > New > Remote Address Book.
* Enter a significant name for your calendar in the Name field.
* Type the following URL in the URL field: http://localhost/SOGo/dav/jdoe/Contacts/personal/
* Click on OK.

To access your personal calendar:

* Choose Go > Calendar.
* Choose Calendar > New Calendar.
* Select On the Network and click on Continue.
* Select CalDAV.
* Type the following URL in the URL field: http://localhost/SOGo/dav/jdoe/Calendar/personal/
* Click on Continue.


Windows Mobile
--------------

The following steps are required to configure Microsoft Exchange ActiveSync on a Windows Phone:

Locate the Settings options from within your application menu.

* Select Email + Accounts.
* Select Add an Account.
* Select the option for Advanced Setup.
* Enter your full email address and password for your account. Then press the sign in button.
* Select Exchange ActiveSync.
* Ensure your email address remains correct.
* Leave the Domain field blank.
* Enter the  address for Server (domain name or IP)
* Select the sign in button.
* You might need to accept all certificats, if you are not able to sync

Once connected, you will see a new icon within your settings menu with the name of your new email account.


Outlook
-------

You can use it with

* IMAP + commercial plugin as `cfos <https://www.cfos.de/en/cfos-outlook-dav/cfos-outlook-dav.htm?__ntrack_pv=1>`_ or `outlookdav <http://www.outlookdav.com/>`_ for calendars/contacts
* ActiveSync since Outlook 2013

There is no support for Openchange/OutlookMAPI.


Nightly build
=============

SOGo is built by the community, if you look to the last version, then you must use the nightly built. 
This version is not considered as stable, but bugs are fixed quicker than in stable version. You are the QA testers :)

|product| 7 - SOGo 3
--------------------

Execute: ::

  sudo rpm --import 'http://pgp.mit.edu/pks/lookup?op=get&search=0xCB2D3A2AA0030E2C'
  sudo rpm -ivh http://dl.fedoraproject.org/pub/epel/epel-release-latest-7.noarch.rpm
  sudo cat >/etc/yum.repos.d/SOGo.repo <<EOF
  [sogo3]
  name=SOGo Repository
  baseurl=https://packages.inverse.ca/SOGo/nightly/3/rhel/7/\$basearch
  gpgcheck=1
  EOF

Then to install: ::

  yum install nethserver-sogo --enablerepo=sogo3

Issues
======

Please raise issues on `community.nethserver.org <http://community.nethserver.org/>`_.

Sources
=======

Source are available https://github.com/NethServer/nethserver-sogo

Developer manual on `github <https://github.com/NethServer/nethserver-sogo/blob/master/README.rst>`_.
