======
Users
======

A system user is required to access many services provided by
NethServer (email, shared folders, etc..).

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

The password must meet the following requirements:

* Must have at least 5 different characters
* Must not be present in the dictionaries of common words
* Must be different from your username
* Can not have repetitions of patterns formed by 3 more characters (for example the password As1.$ AS1. $ is not valid)

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

