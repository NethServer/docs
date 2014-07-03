.. _users_and_groups-section:

================
Users and groups
================

Users
=====

A system user is required to access many services provided by
|product| (email, shared folders, etc..).

Each user is characterized by a pair of credentials (user and
password). A newly created user account remains locked until it has
set a password. A blocked user can not use the services of
servers that require authentication.

When creating a user, following fields are mandatory:

* Username
* Name
* Surname

Optional fields:

* Company
* Office
* Address
* City
* Phone


Just after creation, the user is disabled. To enable the user, set a password using the :guilabel:`Change password` button.
When a user is enabled, the user can access to the Server Manager and change his/her own password: :ref:`user_profile-section`.

A user can be added to one or more group from the :guilabel:`Users` page or from the :guilabel:`Groups` one. 

Sometimes you need to block user's access to service without deleting the the account. 
This behavior can be achieved using the :guilabel:`Lock` and :guilabel:`Unlock` buttons.


.. note:: When a user is deleted, all user data will be also deleted.

Access to services
------------------

After creation a user can be enabled only to some (or all) services.
This configuration can be done using the :guilabel:`Services` tab page.


Groups
======

A group of user can be used to assign special permissions to some users or to create email distribution lists.

As for the users, a group can be enabled to some (or all) services.



.. _admin-user:

Administrator user
==================

The :guilabel:`Users` module creates the user :dfn:`admin` that allows access to the web interface with the same password for the :dfn:`root` user.
The :index:`admin` user does not have access to the system from the command line.
Despite being two separate users, the password of both coincide and can be changed from the web interface.

On some occasions, it may be useful to differentiate the admin and root password, for example, to allow an inexperienced user
to use the web interface to perform common tasks and inhibiting access to the command line.

Avoid :index:`root` and admin password synchronization by run the following command ::

 config setprop AdminIsNotRoot enabled

Then change the admin password from the panel :guilabel:`Users`. Without password synchronization,
admin will have the new password, and root will keep keep the old one.

If you want to change the root password, it should be done from the command line using :command:`passwd`.

Password management
===================

The system provides the ability to set constraints on password :dfn:`complexity` and :dfn:`expiration`.

Complexity
-----------

The :index:`password` complexity is a set of minimum conditions that password must match to be accepted by the system: 
You can choose between two different management policies about password complexity:

* :dfn:`none`: there is no specific control over the password entered, but minimum length is 7 characters
* :dfn:`strong`

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

The default policy is :dfn:`strong`.

To change the setting to none ::

  config setprop passwordstrength none Users

To change the setting to strong ::

  config setprop passwordstrength Users strong

Check the policy currently in use on the server ::

  config getprop passwordstrength Users

Expiration
----------

The  :index:`password expiration` is enabled by default to 6 months from the time when the password is set.
The system will send an e-mail to inform the users when their password is about to expire.

.. note:: The system will refer to the date of the last password change, 
   whichever is the earlier more than 6 months, the server will send an email to indicate that password has expired. 
   In this case you need to change the user password.
   For example, if the last password change was made in January, and the activation of the deadline in October, 
   the system will assume the password changed in January is expired, and notify the user.

If you wish to bypass the password expiration globally (also allow access for users with expired password) ::

  config setprop passwordstrength PassExpires no
  signal-event password-policy-update

To disable password expiration for a single user (replace username with the user) ::

  db accounts setprop <username> PassExpires no
  signal event password-policy-update


Below are the commands to view enabled policies.

Maximum number of days for which you can keep the same password (default: 180) ::

  config getprop passwordstrength MaxPassAge


Minimum number of days for which you are forced to keep the same password (default 0) ::

  config getprop passwordstrength MinPassAge


Number of days on which the warning is sent by email (default: 7) ::

  config getprop passwordstrength PassWarning


To change the parameters replace the :command:`getprop` command with :command:`setprop`,  
then add the desired value at end of the line. Finally apply new configurations::

  signal-event password-policy-update



For example, to change to 5 "Number of days on which the warning is sent by email" ::

 config setprop passwordstrength PassWarning 5
 signal-event password-policy-update



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
