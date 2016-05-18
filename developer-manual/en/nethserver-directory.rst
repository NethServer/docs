====================
nethserver-directory
====================

The `nethserver-directory` implements user authentication and authorization.
All accounts are saved inside OpenLDAP.

Features:

* User and group account management
* PAM LDAP password storage
* Password strength control
* Service accounts


Schema and base DN
===================

Following schema are used inside OpenLDAP:

* always loaded: core, inetorgperson, cosine, corba

The LDAP tree is always accessible with the following DN: **dc=directory,dc=nh**.
But there is also an :index:`overlay` which maps the domain name to the base DN.
For example, given the domain *mydomain.com*, the corresponding DN will be **dc=mydomain,dc=com**.

Accounts are saved inside following branches:

* Users: ou=People,dc=directory,dc=nh
* Groups: ou=Groups,dc=directory,dc=nh

All users are in the primary group named *locals*.

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

* invoke the create event which uses libuser to add the record inside LDAP
* invoke the group even if the user must be members of additional groups
* invoke the password policy event to change user password expiration
* invoke the password change event to set a password


Logging
=======

OpenLDAP doesn't output any log with standard configuration.
When logging is enabled, all logs are saved inside :file:`/var/log/slapd`.
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

To permanently change LDAP log level: ::

  config setprop slapd LogLevel 256
  signal-event nethserver-directory-update

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
Currently anonymous access is granted to non-sensitive fields.

Configuration for client (eg. Mozilla Thunderbird):

* Host: ip address of the server
* Port: 389
* Base DN: ou=People,dc=example,dc=org
* On Advanced tab, make sue "Login method" is set to "Simple"


Inspect OpenLDAP ACLs
=====================

Service accounts require OpenLDAP ACLs tuning. To inspect the current ACLs type: ::

  ldapsearch -LLL -Y EXTERNAL -b cn=config -s one 'objectClass=olcDatabaseConfig' olcAccess 2>/dev/null

If output appears to be base64-encoded type: ::

  ldapsearch -LLL -Y EXTERNAL -b cn=config -s one 'objectClass=olcDatabaseConfig' olcAccess 2>/dev/null | perl -MMIME::Base64 -MEncode=decode -n -00 -e 's/\n +//g;s/(?<=:: )(\S+)/decode("UTF-8",decode_base64($1))/eg;print'


