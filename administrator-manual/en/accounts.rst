======
Users
======

A system user is required to access many services provided by
|product| (email, shared folders, etc..).

Each user is characterized by a pair of credentials (user and
password). A newly created user account remains locked until it has
set a password. A blocked user can not use the services of
servers that require authentication.

Create / Modify
===============

Allows you to create or modify user data The username cannot
be changed after creation.

User
------

Basic information about the user. These fields are
 required.

Username
    The *Username* will be used to access the services. It can
    contain only lowercase letters, numbers, dashes, dots, and
    underscore (_) and must start with a lowercase letter. For
    example, "luisa", "jsmith" and "liu-jo" is a valid user name, and
    "4Friends", "Franco Blacks" and "aldo / mistake" are not.
Name
    It is the user's real name. For example, "John"
Surname
    The user's last name
Groups
    Using the search bar, you can select the groups to
    which the user will be added. The user can belong to several groups.

Change Password
---------------

Allows to set an initial password, or change the user's password.

Lock / Unlock
----------------

Allows you to lock or unlock a user. User data 
will not be deleted.

Delete
-------

Delete the user. All user data will be deleted.

Details
--------

This section collects information on the organization to which
the user belongs to and is optional. The default values can be
specify the menu item *Data organization*.

For the following fields, you can specify a custom value,
otherwise it is the setting made by the module "Data
organization, "available only to the system administrator.

* Company
* Office
* Address
* City
* Phone


Service
-------

This section contains the list of services to which the user is
enabled.


Mail
^^^^

Inbox
    Enable the mailbox for the user.

Forwarding messages
    Forward received emails to an alternative address.

Keep a copy on the server
    Forwarded email will still be saved in the user's inbox.

Custom email quota
    Allows you to specify a dimension value other than the default.

Customize retention time of the spam emails.
    The spam emails are deleted at regular intervals. Ticking the 
    box you can set the number of days the user's messages
    classified as spam, will be maintained
    in the system before being deleted.

Email addresses
    List of email addresses associated with the user.

Shared folders (Samba)
^^^^^^^^^^^^^^^^^^^^^^

Samba is the implementation of CIFS protocol, which allows the use of
Windows shared folders.

Shared folders (Samba)
    Grant user permission to access folders shared via Samba.

Remote Shell (SSH)
==================

Remote Shell (SSH)
    Allows the user to access a secure shell on the server.

======
Groups
======

Create, modify or remove groups of users
used to assign user permissions and access to services
or email distribution lists.

Create / Modify
===============

Group
-------------

Create a new group, adding members to the group.


Group Name
    May contain only lowercase letters, numbers,
    hyphens, and underscores and must start with
    a lowercase letter. For example, "sales", "beta3" and "rev_net"
    are valid names, while "3d", "Sales Office" and "q & a" are
    not.
Description
    Enter a brief description of the group.
Membership
    Allows you to search for users on the server. Users
    can be added to the group with the * Add * button. To delete the
    users listed use the button *X*.

Services
--------

Enable services available to the new group.

Email
    Enable the mailbox for the group.
Send a copy of the message to group members
    Enable the standard behavior of the distribution list: each
    e-mail sent to the group will be copied to every user's mailbox.
Deliver the message in a shared folder
    Any email sent to the group will be delivered to an IMAP folder
    shared visible only to group members.
Create pre-defined email addresses
    Automatically create email addresses for the group
    for all domains configured on the server, like
    *Group_name @ domain*. These email addresses can be changed in
    *Management section -> Email Addresses*.

Delete
======

This action removes the defined groups and their
distribution lists. The shared mailboxes associated


.. _admin-user:

Administrator user
==================

The :guilabel:`Users` module creates the user :dfn:`admin` that allows access to the web interface with the same password for the :dfn:`root` user.
The :index:`admin` user does not have access to the system from the command line.
Despite being two separate users, the password of both coincide and can be changed from the web interface.

On some occasions, it may be useful to differentiate the admin and root password, for example, to allow an inexperienced user
to use the web interface to perform common tasks and inhibiting access to the command line.

Avoid :index:`root` and admin password synchronization by run the following command ::

 config September AdminIsNotRoot enabled

Then change the admin password from the panel :guilabel:`Users`. Without password synchronization,
admin will have the new password, and root will keep keep the old one.

If you want to change the root password, it should be done from the command line using :command:`passwd`.

Password management
===================

The system provides the ability to set constraints on password :dfn: `complexity` and: dfn: `expiration`.

Complexity
-----------

The: index `password` complexity is a set of minimum conditions that password must match to be accepted by the system: 
You can choose between two different management policies about password complexity:

* :dfn: `none`: there is no specific control over the password entered, but minimum length is 7 characters
* :dfn: `strong`

The :index:`strong` policy requires that the password must comply with the following rules:

* Minimum length of 7 characters
* Contain at least 1 number
* Contain at least 1 uppercase character 
* Contain at least 1 lowercase character
* Contain at least 1 special character
* At least 5 different characters
* Must be not present in the dictionaries of common words 
* Must be different from the username
* Can not have repetitions of patterns formed by 3 or more characters (for example the password As1.$ AS1. $ is invalid)

The default policy is: dfn: `strong`.

To change the setting to none ::

  config setprop PasswordStrength none Users

To change the setting to strong ::

  config setprop PasswordStrength Users strong

Check the policy currently in use on the server ::

  config GetProp PasswordStrength Users

Expiration
----------

The: index `password expiration` is enabled by default to 6 months from the time when the password is set.
The system will send an e-mail to inform the users when their password is about to expire.

.. note:: The system will refer to the date of the last password change, 
   whichever is the earlier more than 6 months, the server will send an email to indicate that password has expired. 
   In this case you need to change the user password.
   For example, if the last password change was made in January, and the activation of the deadline in October, 
   the system will assume the password changed in January is expired, and notify the user.

If you wish to bypass the password expiration globally (also allow access for users with expired password) ::

  config setprop PasswordStrength PassExpires no
  event signal-password-policy-update

To disable password expiration for a single user (replace username with the user) ::

  db accounts setprop <username> PassExpires no
  event signal-password-policy-update


Below are the commands to view enabled policies.

Maximum number of days for which you can keep the same password (default: 180) ::

  config GetProp PasswordStrength MaxPassAge


Minimum number of days for which you are forced to keep the same password (default 0) ::

  config GetProp PasswordStrength MinPassAge


Number of days on which the warning is sent by email (default: 7) ::

  config GetProp PasswordStrength PassWarning


To change the parameters replace the :command:`getprop` command with :command:`setprop`,  
then add the desired value at end of the line. Finally apply new configurations::

  event signal-password-policy-update



For example, to change to 5 "Number of days on which the warning is sent by email" ::

 config setprop PasswordStrength PassWarning 5
 event signal-password-policy-update



Effects of expired password
^^^^^^^^^^^^^^^^^^^^^^^^^^^

After password expiration, the user will be able to read and send mails but can no longer access the shared folders and printers (Samba) or 
or other computer if the machine is part of the domain. 


Domain password
----------------

If the system is configured as a domain controller,users can change their password using the Windows tools.

In the latter case you can not set passwords shorter than 6 *characters* regardless of the server policies.
Windows performs preliminary checks and sends the password to the server where they are then evaluated 
with enabled policies.
