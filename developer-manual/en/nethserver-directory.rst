====================
nethserver-directory
====================

The `nethserver-directory` implements user authentication and authorization.
All accounts are saved inside OpenLDAP.

Features:

* RFC2307 schema, user and group account management
* PAM LDAP password storage
* Password strength control
* Service accounts


Schema and base DN
===================

Following schema are always loaded by OpenLDAP: core, cosine, nis, inetorgperson.

The LDAP tree is always accessible with the following base DN: **dc=directory,dc=nh**.
But there is also an :index:`overlay` which maps the domain name to the base DN.
For example, given the domain *mydomain.com*, the corresponding DN will be **dc=mydomain,dc=com**.

Accounts are saved inside following branches:

* Users: ou=People,dc=directory,dc=nh
* Groups: ou=Groups,dc=directory,dc=nh

All users are in the primary group named *locals*.

Examples
--------

List all entries, with root access and automatic bind (unix domain socket): ::

 ldapsearch -Y EXTERNAL

List all entries with libuser bind: ::

 ldapsearch  -D cn=libuser,dc=directory,dc=nh -w `cat /var/lib/nethserver/secrets/libuser` -h 127.0.0.1


User account states
===================

Account management is done via :index:`libuser` which exports some tools (luseradd, luserdel, etc) to create/modify/delete users, groups and set passwords.

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

Service accounts
================

The following service accounts are configured by the ``nethserver-directory-dit-setup`` action:

* ``cn=libuser,dc=directory,dc=nh``. Granted read and write access from 127.0.0.1.

* ``cn=ldapservice,dc=directory,dc=nh``. Granted read only access to
  non-sensitive attributes, from localhost, or from any other IP address with TLS.

The developer can use the ``NethServe::Directory`` Perl module to handle
additional service accounts with ad-hoc permissions, if the existing ``ldapservice``, 
``libuser`` accounts and anonymous binds do not fit his requirements.

A service account is composed by three parts:

* a LDAP user
* a password
* an ACL to access LDAP fields

Perl code snippet to create a service account with read access: ::

  use NethServer::Directory;
  ...
  NethServer::Directory->new()->configServiceAccount('myservice', NethServer::Directory::FIELDS_READ) || die("Failed to register myservice account")

Perl code snippet to use created password: ::

  use NethServer::Password;
  my $pwd = NethServer::Password::store('myservice');
 
User accounts
=============

Authenticated binds are granted to TLS protected connections, or connections
from 127.0.0.1. User DN are in the form: ::

    uid=<username>,ou=People,dc=directory,dc=nh


Anonymous access
================

Some LDAP clients and/or legacy environments may require anonymous bind to the LDAP accounts database.
Currently anonymous access is granted to non-sensitive fields.

Configuration for client:

* Host: ip address of the server
* Port: 389
* Base DN: ``dc=directory,dc=nh``

Administrative access
=====================

An existing DN (i.e. ``administrator``) can be granted full administrative
privileges on the whole ``dc=directory,dc=nh`` tree. By default, the designated
user is defined in config DB, under the ``admins`` key.

```
ldapmodify -Y EXTERNAL <<EOF
dn: olcDatabase={2}hdb,cn=config
changetype: modify
replace: olcRootDN
olcRootDN: uid=administrator,ou=People,dc=directory,dc=nh
EOF
```


Inspect OpenLDAP ACLs
=====================

Service accounts require OpenLDAP ACLs tuning. To inspect the current ACLs type: ::

  ldapsearch -LLL -Y EXTERNAL -b cn=config -s one 'objectClass=olcDatabaseConfig' olcAccess 2>/dev/null

If output appears to be base64-encoded type: ::

  ldapsearch -LLL -Y EXTERNAL -b cn=config -s one 'objectClass=olcDatabaseConfig' olcAccess 2>/dev/null | perl -MMIME::Base64 -MEncode=decode -n -00 -e 's/\n +//g;s/(?<=:: )(\S+)/decode("UTF-8",decode_base64($1))/eg;print'


Upgrade to Active Directory
===========================

If the LDAP database has been restored from a ns6 backup set, it is possible
to upgrade it to a local Active Directory accounts provider.

A ns7 LDAP database cannot be upgraded to Active Directory. It lacks the Samba
LDAP schema extensions required by the Samba *classic upgrade* procedure.

The ``nethserver-directory-ns6upgrade`` event 

- removes the ``nethserver-directory`` RPM
- installs and configures ``nethserver-dc``

Before running the event, assign a free IP address to the ``nsdc`` Linux
container, installed by ``nethserver-dc`` RPM. Ensure it is **a free IP
address** of a **green network**.

::

    config set nsdc service IpAddress A.B.C.D
    signal-event nethserver-directory-ns6upgrade

