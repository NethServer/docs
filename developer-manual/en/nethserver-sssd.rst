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

System users and groups
-----------------------

SSSD can access all users and groups from an account provider,
but the web interface will always hide system users and groups.

The following users will not be accessible from the web interface:

* all users listed inside `/etc/nethserver/system-users`
* all users with uid < 1000
* all machine accounts from AD

The following groups will not be accessible from the web interface:

* all groups listed inside `/etc/nethserver/system-groups`
* all groups with gid < 1000


NethServer::SSSD
----------------

NethServer::SSSD is the perl library module to retrieve current LDAP configuration. 
It supports both Active Directory and OpenLDAP providers.

Template example: ::

  {
      use NethServer::SSSD;
      my $sssd = new NethServer::SSSD();

      $OUT .= "{ldap_uri, [".$sssd->ldapURI()."]}\n";

      if ($sssd->isAD()) {
          $OUT .= "{ldap_uids, [\"sAMAccountName\"]}.\n";
      }

  }


All functions are documented using perldoc ::

  perldoc NethServer::SSSD

