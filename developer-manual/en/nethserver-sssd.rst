===============
nethserver-sssd
===============

This package implements authentication and user management layers.
Supported authentication providers are:

* OpenLDAP with POSIX attributes
* Samba or Windows Active Directory

It includes the following parts:

* SSSD configuration
* events for users and  groups management
* web interface for user management
* password expiration notification (not yet implemented)
* system validators for users and groups
* SSSD perl library to ease the implementation of e-smith templates


The implementation can work in two modes:

* read-and-write: if `nethserver-dc` or `nethserver-directory` are installed, the system will
  provide all user management features like creation, modification and deletion of users and groups
* read-only: if users and groups are read from a remote source, the system will
  be able to consume them only using passwd database

Realm and workgroup
-------------------

When the system is configured to use an Active Directory provider (``Provider=ad``),
make sure to correctly set both ``Realm`` and ``Workgroup`` properties:

- Realm: this is the Kerberos realm and it's case sensitive, but it's usually configured in upper case
  as best practice.
  When the realm is used for DNS queries, it's automatically forced to lower case.

- Workgroup: Samba NetBIOS name, maximum length is 15 characters. It's usually the first part of the Realm in upper case

Events
------

Defined events are:

user-create
^^^^^^^^^^^

The event creates the user record inside the account provider database.

Parameters:

* username: must be unique
* name: full name of the user
* shell: default to `/usr/libexec/openssh/sftp-server`, if set to `/bin/bash` the user will be able to access the server using SSH


user-modify
^^^^^^^^^^^

The event changes the full name inside the account provider databases

Parameters:

* username
* name: full name of the user
* shell: default to `/usr/libexec/openssh/sftp-server`, if set to `/bin/bash` the user will be able to access the server using SSH

Note: shell option can't be changed for AD users

user-delete
^^^^^^^^^^^

The event deleted the user and remove it from all groups.
Also all data inside the user's home will deleted.

Parameters:

* username


user-lock
^^^^^^^^^

The event locks the user preventing the access.
All new users are in locked state.

Parameters:

* username

user-unlock
^^^^^^^^^^^

The event unlocks the user preventing the access.
This event should be called after the invoking `password-modify` event for the user.

Parameters:

* username


group-create
^^^^^^^^^^^^

The event creates the group record inside the account provider database.

Parameters:

* groupname: must be unique
* members: a list of users member of this group


group-modify
^^^^^^^^^^^^

The event changes the members of a group  inside the account provider database.

Parameters:

* groupname: must be unique
* members: a list of users member of this group



group-delete
^^^^^^^^^^^^

This event deletes a group record from the the account provider database.

Parameters:

* groupname


password-policy-update
^^^^^^^^^^^^^^^^^^^^^^

This event configures password expiration of a single user or of all users.

Parameters

* username (optional)
* passexpires: it can be `yes` or `no`. If user is set and value is `yes`, the user password will expires after a 
  predefined number of days (see `passwordstrength{MaxPassAge}`)

  The duration of a password can be  passwordstrength{MaxPassAge}

nethserver-sssd-remove-provider
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

This event removes any installed local account provider and also
wipes the configuration of any remote account provider.

Before resetting the configuration, all accounts are dumped inside the
following files in tsv format:

- /var/lib/nethserver/backup/users.tsv
- /var/lib/nethserver/backup/accounts.tsv

System users and groups
-----------------------

SSSD can access all users and groups from an account provider,
but the Server Manager hides system users and groups.

The following users will not be accessible from the Server Manager:

* all users listed inside `/etc/nethserver/system-users`
* all users in /etc/passwd

The following groups will not be accessible from the web interface:

* all groups listed inside `/etc/nethserver/system-groups`
* all groups in /etc/group

The users and groups lists are retrieved by the following UI helpers:

- ``/usr/libexec/nethserver/list-users``

- ``/usr/libexec/nethserver/list-groups``

The number of entries returned by the server is limited. For instance, AD has a 
1000 entries search results cap.

To retrieve the members of a group and the membership of a specific user:

- ``/usr/libexec/nethserver/list-group-members``

- ``/usr/libexec/nethserver/list-user-membership``

The Dashboard account counters are provided by:

- ``/usr/libexec/nethserver/count-accounts``

All those helpers support the ``-A`` flag, to include hidden entries, 
and the ``-s`` flag to return entries without ``@domain`` suffix.


NethServer::SSSD
----------------

NethServer::SSSD is the Perl library module to retrieve current LDAP configuration. 
It supports both Active Directory and OpenLDAP providers.

Template example: ::

  {
      use NethServer::SSSD;
      my $sssd = NethServer::SSSD->new();

      $OUT .= "{ldap_uri, [".$sssd->ldapURI()."]}\n";

      if ($sssd->isAD()) {
          $OUT .= "{ldap_uids, [\"sAMAccountName\"]}.\n";
      }

  }


All functions are documented using perldoc ::

  perldoc NethServer::SSSD

This command prints out the current settings, by querying ``NethServer::SSSD`` 
methods. It requires the package ``openldap-clients`` ::

    /usr/sbin/account-provider-test dump

Check the bind credentials are OK ::

    /usr/sbin/account-provider-test

Join Active Directory
---------------------

The Active Directory join operation is run by *realmd*. After the AD has been
joined sucessfully the system keytab file is initialized as long as individual
service keytabs, as defined on the respective *service* record (see `Service
configuration hooks`_).

Leave and Re-Join Active Directory
----------------------------------

To leave a remote AD go to the :guilabel:`Accounts provider` page. For local AD
provider, this is the **manual leave procedure** ::

    config setprop sssd Realm '' Workgroup '' Provider none
    signal-event nethserver-sssd-leave

If the machine password or system keytab get corrputed, joining again the DC can fix them: ::
    
    realm join -U administrator $(hostname -d)

...at prompt, type the administrator (or admin) password, then: ::

    signal-event nethserver-sssd-save

If you leave and do not want to re-join, disable the sssd service permanently: ::

    config setprop sssd status disabled Provider none
    signal-event nethserver-sssd-save
    signal-event nethserver-sssd-leave
    signal-event nethserver-dnsmasq-save

Change the FQDN
---------------

Once we are bound to an account provider the FQDN cannot be changed any more.
However, this procedure can be useful in early server configuration to fix a
wrong FQDN.  Please note that any existing account setting must be fixed
manually. The procedure to do it is currently undefined.

For local account providers:

1. Execute the leave procedure explained above

2. Go to page :guilabel:`System name` and change the domain suffix in the FQDN field.

3. Re-join as explained above

For remote account providers the procedure is similar. Use the
:guilabel:`Accounts provider` page to leave/join the domain.


Service configuration hooks
^^^^^^^^^^^^^^^^^^^^^^^^^^^

A service (i.e. *dovecot*) record in ``configuration`` DB can be extended with
the following special props, that are read during the join operation, machine
password renewal, and crojob tasks: ::

 dovecot=service
    ...    
    KrbStatus=enabled
    KrbCredentialsCachePath=
    KrbKeytabPath=/var/lib/dovecot/krb5.keytab
    KrbPrimaryList=smtp,imap,pop
    KrbKeytabOwner=
    KrbKeytabPerms=

* ``KrbKeytabPath``
  Keytab file path. If empty, ``/var/lib/misc/nsrv-<service>.keytab`` is assumed
* ``KrbPrimaryList <comma separated words list>``
  Defines the keytab contents. In Kerberos jargon a "primary" is the first part of the `principal string <http://web.mit.edu/kerberos/krb5-1.5/krb5-1.5.4/doc/krb5-user/What-is-a-Kerberos-Principal*003f.html>`_, before the slash (``/``) character. Any primary in this list is exported to the keytab.
* ``KrbKeytabOwner``
  The unix file owner. Default is the ``service`` name. This is applied to both the credentials cache file and the keytab file.
* ``KrbKeytabPerms``
  The unix bit permissions in octal form. Default is ``0400``. This is applied to both the credentials cache file and the keytab file.

The implementation is provided by ``/usr/libexec/nethserver/smbads``.

Individual services can link themselves to ``nethserver-sssd-initkeytabs``
action in the respective ``-update`` event.

The following props are no longer honoured since ns7:

* ``KrbStatus {enabled,disabled}``
  This is the main switch. If set to ``enabled`` a ticket credential cache file is kept valid by the hourly cronjob
* ``KrbCredentialsCachePath``
  The path of the credentials cache. It defaults to ``/tmp/krb5cc*<service*uid>``, if ``service`` is also a system user.


Account import scripts
----------------------

There are some perl scripts under the documentation ``scripts/`` directory. ::
    
    rpm -qd nethserver-sssd

import_users
^^^^^^^^^^^^

It is possible to create user accounts from a TSV (Tab Separated Values) file with the following format: ::

  username <TAB> fullName <TAB> password <NEWLINE>

Sample invocation: ::

  import_users users.tsv

Alternative separator character: ::

  import_users users.csv ','

import_groups
^^^^^^^^^^^^^

It is possible to create groups from a TSV (Tab Separated Values) file with the following format: ::

  groupname <TAB> member1 <TAB> ... <TAB> memberN <NEWLINE>

Sample invocation: ::

  import_users groups.tsv

Alternative separator character: ::

  import_groups groups.csv ','



import_emails
^^^^^^^^^^^^^

It is possible to create mail aliases from a TSV (Tab Separated Values) file with the following format: ::

  username <TAB> emailaddress <NEWLINE>

See ``import_users`` section for a sample script invocation.
