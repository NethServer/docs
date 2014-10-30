================
Directory (LDAP)
================

The `nethserver-directory` implements user authentication and authorization.
All accounts are saved inside OpenLDAP.

Features:

* User and group account management
* PAM LDAP password storage
* Password strength control
* Password expiration notifications
* Service accounts


Daemon
======

:index:`OpenLDAP` is a core service and must always be running.
The slapd daemon is controlled by upstart commands and it is
respawn in case of crash.

Start daemon: ::

 start slapd

Stop daemon: ::

 stop slapd


Schema and base DN
===================

Following schema are used inside OpenLDAP:

* always loaded: core, inetorgperson, cosine, corba, nis
* installed by extra packages: samba, qmail

The LDAP tree is always accessible with the following DN: **dc=directory,dc=nh**.
But there is also an :index:`overlay` which maps the domain name to the base DN.
For example, given the domain *mydomain.com*, the corresponding DN will be **dc=mydomain,dc=com**.

Accounts re saved inside following branches:

* Users: ou=People,dc=directory,dc=nh
* Groups: ou=Groups,dc=directory,dc=nh
* Machine accounts: ou=Computers,dc=directory,dc=nh

Examples
--------

List all entries, with root access and automatic bind: ::

 ldapsearch -Y EXTERNAL

List all entries with libuser bind: ::

 ldapsearch  -D cn=libuser,dc=directory,dc=nh -w `cat /var/lib/nethserver/secrets/libuser`


User account states
===================

Account management is done via :index:`libuser` which exports some tools (luseradd, luserdel, etc) to create/modify/delete users and groups.

The process of user/group creations is:

* add new record inside the accounts database
* invoke the create event (eg. user-create) which uses libuser to add the record inside LDAP

The `__state` property keeps of the user status as shown below:

.. figure:: ../../_static/user-account-sm.png
   :alt: User account state machine

Password policy
===============

The system can handle global or per-user policies.
All policies are enforced by PAM and saved under ``passwordstrength`` inside the ``configuration`` database.

Available properties are:

* ``Users``: change strength password for all users, can be:

  * ``strong``: (default) strong passwords must conform to cracklib checks
  * ``none``: no strength check
* ``PassExpires``: can be ``yes`` (default) or ``no``. If set to ``no`` password will not expire, if set to ``yes``,
    following properties apply:

  * ``MaxPassAge``: minimum number of days for which the user is forced to keep the same password (default 0)
  * ``MinPassAge``: maximum number of days for which the user can keep the same password (default: 180)
  * ``PassWarning``: an email will be sent to the user X days before password expiration

Configuration can be applied using the :command:`password-policy-update` event.

DB example: ::

 passwordstrength=configuration
    MaxPassAge=180
    MinPassAge=0
    PassExpires=no
    PassWarning=7
    Users=none


See Administrator manual for more examples.

Logging
=======

OpenLDAP logs only start and stop events inside the :file:`/var/log/messages`.
But its verbosity can be changed at run time by issuing this command: ::

  # ldapmodify -Y EXTERNAL <<EOF
  dn: cn=config
  changetype: modify
  replace: olcLogLevel
  olcLogLevel: 256
  EOF

The command above changes the OpenLDAP `config` DB and set the log verbosity to trace "connections/operations/results" (256). 
Check the debugging levels table from OpenLDAP site for more details: http://www.openldap.org/doc/admin24/slapdconf2.html#olcLogLevel%3A%20%3Clevel%3E.

.. note:: 
   slapd log file can grow quickly. Remember to set `olcLogLevel` to `0` if you do not need it any longer.


Service accounts
================

If a program need to access the LDAP, it should create a special account called :index:`service account`.
A :index:`service account` is composed by three parts:

* a LDAP user
* a password
* an ACL to access LDAP fields

The developer can user the ``NethServe::Directory`` perl module to handle a service account.

Perl code snippet to create a service account with read access: ::

  use NethServer::Directory;
  ...
  NethServer::Directory->new()->configServiceAccount('myservice', NethServer::Directory::FIELDS_READ) || die("Failed to register myservice account")

Perl code snippet to use created password: ::

  use NethServer::Password;
  my $pwd = NethServer::Password::store('myservice');
 

Anonymous access
----------------

Some LDAP clients and/or legacy environments may require anonymous bind to the LDAP accounts database.
Currently only authenticated binds over TLS/SSL are granted access to the LDAP tree.
But you can give access without bind with the following command: ::

 perl -MNethServer::Directory -e '$l = NethServer::Directory->new(); $l->enforceAccessDirective("by anonymous read", "*");'

Please note that password fields are visible only using bind.

.. note:: This command is not easily reversible.

Databases
=========

Accounts
--------

When installed, the package automatically creates the :index:`admin user`, which is disabled by default.

All users have at least the following properties:

* FirstName
* LastName
* PassExpires
* Shell
* Uid

All groups have at least the following properties:

* Members: comma separated list of user
* Uid
* Gid
* Description

These properties are mapped to PAM fields.
A user/group can also have extra parameters about mail and samba configuration.

Example: ::

 gandalf=user
    FirstName=Gandalf
    LastName=TheWhite
    PassExpires=no
    Shell=/bin/bash
    Uid=5042
    __state=active

 hobbits=group
    Description=The Hobbits fellowship
    Gid=5022
    Members=frodo,sam
    Uid=5022


Configuration
-------------

Keys inside configuration database:

* ActiveAccounts: count active user accounts
* nslcd: manage nslcd daemon
* slapd: manage slapd daemon

  * LogLevel: log level, default is 256
  * options: extra options for the daemon

Example: ::

 nslcd=service
    access=private
    status=enabled

 slapd=service
    LogLevel=0
    TCPPorts=389
    access=private
    options=
    status=enabled


Inspect OpenLDAP ACLs
=====================

Service accounts require OpenLDAP ACLs tuning. To inspect the current ACLs type: ::

  ldapsearch -LLL -Y EXTERNAL -b cn=config -s one 'objectClass=olcDatabaseConfig' olcAccess 2>/dev/null

If output appears to be base64-encoded type: ::

  ldapsearch -LLL -Y EXTERNAL -b cn=config -s one 'objectClass=olcDatabaseConfig' olcAccess 2>/dev/null | perl -MMIME::Base64 -MEncode=decode -n -00 -e 's/\n +//g;s/(?<=:: )(\S+)/decode("UTF-8",decode_base64($1))/eg;print'

Tools
=====

There are few tools available inside the :file:`/usr/share/doc/nethserver-directory-<version>` directory:

* :command:`fix_accounts`: synchronize LDAP with users and groups from accounts database; created users must be activated by setting the password
* :command:`import_users`: bulk creation of users from CSV file. See administrator manual for more information
 
