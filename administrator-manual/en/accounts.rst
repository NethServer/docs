.. _users_and_groups-section:

================
Users and groups
================

|product| supports authentication and authorization on local and remote account providers.

Supported providers are:

* LDAP: OpenLDAP running on |product|
* Active Directory: Samba Active Directory running locally (or remotely) or on an existing Windows AD machine

After the first configuration wizard, the administrator can configure the authentication
source using the :guilabel:`User and groups` page.
If no extra package is installed, the admin user must select a remote account provider.
Users and groups from remote sources are in *read-only* mode and can not be modified.

After installing a local backend (Samba Active Directory or OpenLDAP), the user will be able to 
create/modify/delete local users and groups.

Please, choose wisely your account provider because the choice is not reversible.
Also, the system will forbid any change to the FQDN after the account provider has been configured.

OpenLDAP
========

From the :guilabel:`Software Center` install the package named :guilabel:`Account provider: OpenLDAP`.
At the end of the installation, the package is automatically configured and the administrator
will be able to manage users and groups from the :guilabel:`User and groups` page.


Samba Active Directory
======================

When installing Samba Active Directory, the system needs an additional IP address which will be the address of 
Active Directory controller inside the LAN.
The additional IP address must satisfy three conditions:

* the IP address must be in the same subnet range of a green network
* the green network must be bound to a bridged interface
* the IP address must not be used by any other machine

From the :guilabel:`Software Center` install the package named :guilabel:`Account provider: Samba Active Directory`.
At the end of the installation, access the :guilabel:`User and groups` page to configure Samba for the first time.
Then insert the additional IP address and press the submit button: if needed, 
the system will automatically create a bridge on the green network.

Users and groups can be managed from the :guilabel:`User and groups` page.

Default account
---------------

After installing Samba Active Directory, the :guilabel:`Users and groups` page has one default entry: :dfn:`administrator`. This
account is granted special privileges on some specific services, such as joining a
workstation in Samba Active Directory domain.

Default password for user administrator is: *Nethesis,1234*

.. tip:: Remember to change the administrator password at first login.

Installing on a virtual machine
-------------------------------

Samba Active Directory runs inside a container which uses a virtual network interface bridged to
the network interface of the system.
The virtual network interface must be visible inside the physical network, but often virtualization 
solutions block ARP traffic. As a result, the Samba Active Directory container
isn't visible from hosts inside the LAN.

When installing on virtual environment, make sure the virtualization solution allows traffic in *promiscuous mode*.

VirtualBox
~~~~~~~~~~

To setup the promiscuous mode policy, select "Allow all" from the drop down list located in 
the network settings section.

VMWare
~~~~~~

Enter the networking configuration section of the virtualization node and set the virtual switch
in promiscuous mode.

KVM
~~~

Make sure the virtual machine is bridged to a real bridge (like br0) and the bridge
is put in promiscuous mode.

It's possible to force a bridge (br0) in promiscuous mode using this command: ::

  ifconfig br0 promisc


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
* Full name (name and surname)


Just after creation, the user is disabled. To enable the user, set a password using the :guilabel:`Change password` button.
When a user is enabled, the user can access to the Server Manager and change his/her own password: :ref:`user_profile-section`.

A user can be added to one or more group from the :guilabel:`Users` page or from the :guilabel:`Groups` one. 

Sometimes you need to block user's access to service without deleting the account. 
This behavior can be achieved using the :guilabel:`Lock` and :guilabel:`Unlock` buttons.


.. note:: When a user is deleted, all user data will be also deleted.

.. _users_services-section:

Access to services
------------------

A user can be enabled to access specific (or all) services.
The access must be done using the full user name with the domain: `username@<domain>`.

Example:

* Domain: nethserver.org
* Username: goofy

The full user name for login is: `goofy@nethserver.org`.


.. _groups-section:

Groups
======

A group of user can be used to assign special permissions to some users or to create email distribution lists.

As for the users, a group can be enabled to some (or all) services.

.. tip:: For delegating permissions to the Server Manager, use the groups ``managers`` or ``administrators``.

Two special groups can be created, the users who belong in one of these groups are granted access to the panels of the Server Manager

* :dfn:`administrators`: Users of this group have the same permissions as the root user.
* :dfn:`managers`: Users of this group are granted access to the Management section.


Password management
===================

The system provides the ability to set constraints on password :dfn:`complexity` and :dfn:`expiration`.

Password policies can be changed from web interface.

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
* If Samba Active Directory is installed, also the system will enable password history

The default policy is :dfn:`strong`.

.. warning:: Changing the default policies is highly discouraged. The use of weak passwords often lead
   to compromised servers by external attackers.

Expiration
----------

The  :index:`password expiration` is enabled by default to 6 months from the time when the password is set.
The system will send an e-mail to inform the users when their password is about to expire.

.. note:: The system will refer to the date of the last password change, 
   whichever is the earlier more than 6 months, the server will send an email to indicate that password has expired. 
   In this case you need to change the user password.
   For example, if the last password change was made in January, and the activation of the deadline in October, 
   the system will assume the password changed in January is expired, and notify the user.


Effects of expired password
~~~~~~~~~~~~~~~~~~~~~~~~~~~

After password expiration, the user will be able to read and send mails but can no longer access the shared folders and printers (Samba) or other computer if the machine is part of the domain. 


Domain password
----------------

If the system is configured as a domain controller, users can change their password using the Windows tools.

In the latter case you can not set passwords shorter than 6 *characters* regardless of the server policies.
Windows performs preliminary checks and sends the password to the server where they are then evaluated 
with enabled policies.

Notification language
=====================

Default language for notifications is English.
If you wish to change it, use the following command: ::

  config setprop sysconfig DefaultLanguage <lang>

Example for Italian: ::

  config setprop sysconfig DefaultLanguage it_IT.utf8

