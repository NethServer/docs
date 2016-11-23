.. _users_and_groups-section:

================
Users and groups
================


Account providers
=================

|product| supports authentication and authorization against either a **local**
or **remote** account provider.

Supported provider types are:

* Local OpenLDAP running on |product| itself,
* Remote LDAP server with RFC2307 schema,
* Local Samba 4 Active Directory Domain Controller,
* Remote Active Directory (both Microsoft and Samba).

Two limitations are enforced on the system, once |product| has been bound to an
account provider:

1. the FQDN cannot be changed any more

2. the account provider cannot be changed

Remote providers
    A clean |product| installation is ready to connect a **remote** account provider
    of both types (LDAP, AD). The root user can configure the remote account
    provider from the :guilabel:`User and groups` page.  After |product| has been
    bound to a remote account provider the :guilabel:`User and groups` page shows
    the domain accounts in *read-only* mode.

Local providers
    To run a **local** account provider go to :guilabel:`Software center` page
    and install either OpenLDAP **or** Samba 4 account provider from the modules list.

    After installing a local backend (either Samba 4 or OpenLDAP), the administrator
    can create, modify, delete the users and groups.

.. warning::

  Please, choose wisely your account provider because **the choice is not
  reversible**. Also, the system will forbid any change to the FQDN after the
  account provider has been configured.


Choosing the right account provider
-----------------------------------

Beside choosing to bind a remote provider or install a local one, the
administrator must decide which backend type suits his needs.

The *File server* module of |product|, which enables the :guilabel:`Shared
folders` page, can authenticate SMB/CIFS clients only if |product| is bound to an
Active Directory domain.  The LDAP providers allow access to :guilabel:`Shared
folders` only in *guest mode*.  See :ref:`shared_folders-section`.

On the other hand, the local OpenLDAP provider is more easy to install and
configure.

In the end, if the SMB file sharing protocol support is not required an
LDAP provider is the best choice.


OpenLDAP local provider installation
------------------------------------

From the :guilabel:`Software Center` install the module named
*Account provider: OpenLDAP*. At the end of the installation, the
package is automatically configured and the administrator will be able to manage
users and groups from the :guilabel:`User and groups` page.



Samba Active Directory local provider installation
--------------------------------------------------

When installing Samba Active Directory as local account provider, the system
needs an **additional IP address** and a working internet connection.

The additional IP is assigned to a Linux Container that runs the Active
Directory Domain Controller roles and must be accessible from the LAN (green
network).

Therefore the additional IP address must satisfy three conditions:

1. the IP address must be **free**; it must not be used by any other machine,

2. the IP address must be in the same subnet range of a green network,

3. the green network must be bound to a bridged interface, so that the Linux
   Container can attach its virtual interface to it; the UI procedure can create the
   bridge interface automatically, if it is missing.

From the :guilabel:`Software center` page install the module named *Account
provider: Samba Active Directory*.

After the account provider installation, the :guilabel:`User and groups` page
shows a configuration panel.  Insert the **additional IP address** as explained
above and press the :guilabel:`Start DC` button. If needed, enable the automatic
bridge interface creation for the green network.

.. tip::

    The Active Directory configuration procedure might require some time to run.
    It creates the Linux Container chroot, by downloading additional packages.

At the end of the Active Directory configuration procedure,  the |product| host
machine is automatically configured to join the Active Directory domain, then
the :guilabel:`User and groups` page is reloaded and it shows the default
accounts.

.. index::
  pair: active directory; default accounts

After installing Samba Active Directory, the :guilabel:`Users and groups` page
has one default entry: :dfn:`administrator`. This account is granted special
privileges on some specific services, such as joining a workstation in Samba
Active Directory domain.

Default password for user administrator is: ``Nethesis,1234``

.. warning:: 

    Remember to change the default administrator password by setting a secure one!

Installing on a virtual machine
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Samba Active Directory runs inside a Linux Container which uses a virtual
network interface bridged to the network interface of the system. The virtual
network interface must be visible inside the physical network, but often
virtualization solutions block ARP traffic. As a result, the Samba Active
Directory container is not visible from LAN hosts.

When installing on virtual environment, make sure the virtualization solution
allows traffic in *promiscuous mode*.

VirtualBox
++++++++++

To setup the promiscuous mode policy, select "Allow all" from the drop down list
located in the network settings section.

VMWare
++++++

Enter the networking configuration section of the virtualization node and set
the virtual switch in promiscuous mode.

KVM
+++

Make sure the virtual machine is bridged to a real bridge (like br0) and the
bridge is put in promiscuous mode.

It is possible to force a bridge (i.e. ``br0``) in promiscuous mode using this
command: ::

  ifconfig br0 promisc

Hyper-V
+++++++

Configure MAC Address Spoofing for Virtual Network Adapters

https://technet.microsoft.com/en-us/library/ff458341.aspx



Join an existing Active Directory domain
----------------------------------------

Here |product| is bound to a remote Active Directory account provider. It can be
provided by either Samba or Microsoft implementations.  In this scenario
|product| becomes a trusted server of an existing Active Directory domain. When
accessing a |product| resource from a domain workstation, user credentials are
checked against one of the domain controllers, and the access to the resource is
granted.

Joining an Active Directory domain has the following pre-requisites:

1. the Kerberos protocol requires the difference between systems clocks in the
   network is less than 5 minutes. Configure the network clients to align their
   clocks to a common time source.  For |product| go to :guilabel:`Date and time`
   page.

2. The system assumes the default NetBIOS domain name is the
   leftmost label in the DNS domain suffix up to the first 15 characters.

   **Example**

   - FQDN: test.local.nethserver.org
   - Domain: local.nethserver.org
   - Default NetBIOS domain: LOCAL

   If the default NetBIOS domain is not good for your environment,
   you can change it from command line: ::

      config set smb service Workgroup <your_netbios_domain>

After all the pre-requisites are met, proceed with the join from :guilabel:`User
and groups` page:

* Fill :guilabel:`DNS server IP address` field which usually is the
  IP address of an AD domain controller.

* Click the :guilabel:`Bind` button. You will be prompted for an user name and
  password: provide AD ``administrator`` or any other account
  credentials with permissions to join a new machine to the domain.

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

A user can be added to one or more group from the :guilabel:`Users` page or from the :guilabel:`Groups` one.

Sometimes you need to block user's access to service without deleting the account.
This behavior can be achieved using the :guilabel:`Lock` and :guilabel:`Unlock` buttons.

.. note:: When a user is deleted, all user data will be also deleted.

Changing the password
---------------------

If an inital password was not set during creation, the user account is disabled.
To enable it, set a password using the :guilabel:`Change password` button.

When a user is enabled, the user can access the Server Manager and change
his/her own password (see also :ref:`user_profile-section`).

If the system is bound to an Active Directory account provider, users can change
their password using the Windows tools.  In this case you can not set passwords
shorter than 6 *characters* regardless of the server policies. Windows performs
preliminary checks and sends the password to the server where they are then
evaluated according to the :ref:`configured policies <password-management-section>`.


Credentials for services
------------------------

The user's credentials are the **user name** and his **password**.  Credentials
are required to access the services installed on the system.

The user name can be issued in two forms: *long* (default) and *short*.  The
*long* form is always accepted by services. It depends on the service to accept
also the *short* form.

For instance if the domain is *example.com* and the user is *goofy*:

Long user name form
    *goofy@domain.com*

Short user name form
    *goofy*

.. _groups-section:

Groups
======

A group of users can be used to assign special permissions to some users, such
as authorize access over a :ref:`shared folder <shared_folders-section>`.

Two special groups can be created.  The users who belong in one of these groups
are granted access to the panels of the Server Manager:

* :dfn:`administrators`: Users of this group have the same permissions as the
  *root* user from the Server Manager.

* :dfn:`managers`: Users of this group are granted access to the *Management*
  section of the Server Manager.

.. _password-management-section:


.. index: admin

Admin account
=============

If a **local AD or LDAP provider** is installed, an *admin* user, member of  the
*administrators* group is created automatically. This account allows
access to all configuration pages within the Server Manager.  It is initially
*disabled* and has no access from the console.

.. tip:: To enable the *admin* account set its password.

Where applicable, the *admin* account is granted special privileges on some
specific services, such as joining a workstation to an Active Directory domain.

If |product| is bound to a **remote account provider**, the *admin* user and
*administrators* group can be created, if they do not already exist.

If a user or group with a similar purpose is already present in the remote
account provider database, but it is named differently, it can be selected with
a `manual procedure
<http://wiki.nethserver.org/doku.php?id=userguide:set_admin_account>`_.


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
   For example, if the last password change was made in January and the activation of the deadline in October,
   the system will assume the password changed in January is expired, and notify the user.


.. _effects-of-expired-password:

Effects of expired passwords
----------------------------

After password expiration, the user is still able to read and send email messages.

If |product| has an Active Directory account provider, the user cannot access
shared folders, printers (by Samba) and other domain computers.

