.. _users_and_groups-section:

================
Users and groups
================

.. _account-providers:

Account providers
=================

|product| supports authentication and authorization against either a **local**
or **remote** account provider.

Supported provider types are:

* Local OpenLDAP running on |product| itself
* Remote LDAP server with RFC2307 schema
* Local Samba 4 Active Directory Domain Controller
* Remote Active Directory (both Microsoft and Samba)

Be aware of the following rules about account providers:

1. Once |product| has been bound to an account provider the FQDN cannot be
   changed any more

2. Local account providers cannot be uninstalled

Remote providers
    A clean |product| installation is ready to connect to a **remote** account
    provider of both types (LDAP, AD). The root user can configure the remote
    account provider from the :guilabel:`Accounts provider` page. 
    
    After |product| has been bound to a remote account provider the
    :guilabel:`User and groups` page shows the domain accounts in *read-only*
    mode.

Local providers
    To run a **local** account provider go to :guilabel:`Software center` page
    and install either OpenLDAP **or** Samba 4 account provider from the modules list.

    After installing a local provider (either Samba 4 or OpenLDAP), the administrator
    can create, modify and delete the users and groups.

.. warning::

  Please choose wisely your account provider because **the choice is not
  reversible**. Also the system will forbid any change to the FQDN after the
  account provider has been configured.


Choosing the right account provider
-----------------------------------

Beside choosing to bind a remote provider or install a local one, the
administrator has to decide which backend type suits he needs.

The *File server* module of |product|, which enables the :guilabel:`Shared
folders` page, can authenticate SMB/CIFS clients only if |product| is bound to an
Active Directory domain.  The LDAP providers allow access to :guilabel:`Shared
folders` only in *guest mode*.  See :ref:`shared_folders-section`.

On the other hand, the local OpenLDAP provider is more easy to install and
configure.

In the end, if the SMB file sharing protocol support is not required, an
LDAP provider is the best choice.


OpenLDAP local provider installation
------------------------------------

From the :guilabel:`Software Center` install the module named
*Account provider: OpenLDAP*. At the end of the installation the
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

1. the IP address has to be **free**; it must not be used by any other machine

2. the IP address has to be in the same subnet range of a green network

3. the green network has to be bound to a bridged interface where the Linux
   Container can attach its virtual interface to; the installation procedure can create the
   bridge interface automatically, if it is missing

From the :guilabel:`Software center` page install the module named *Account
provider: Samba Active Directory*.

After the account provider installation, the :guilabel:`Accounts provider` page
shows a configuration panel.  Insert the **additional IP address** as explained
above and press the :guilabel:`Start DC` button. If needed, enable the automatic
bridge interface creation for the green network.

.. tip::

    The Active Directory configuration procedure might require some time to run.
    It creates the Linux Container chroot, by downloading additional packages.

At the end of the Active Directory configuration procedure,  the |product| host
machine is automatically configured to join the Active Directory domain. Go to 
the page :guilabel:`User and groups` to see the default accounts.

.. index::
  pair: active directory; default accounts

After installing Samba Active Directory, the :guilabel:`Users and groups` page
has two default entries; both are disabled: :dfn:`administrator` and
:dfn:`admin`. "Administrator" is the default Active Directory privileged account
and is not required by |product|; it is safe to keep it disabled. "admin" is
defined by |product| as the default system administrative account. It is member
of the AD "domain admins" group. See :ref:`admin-account-section`
section for more details.


Installing on a virtual machine
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Samba Active Directory runs inside a Linux Container which uses a virtual
network interface bridged to the network interface of the system. The virtual
network interface has to be visible inside the physical network, but often
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

Enter the networking configuration section of the virtualization mode and set
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

1. The Kerberos protocol requires the difference between systems clocks in the
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

3. (Only for Microsoft Active Directory) The default machine account cannot perform
   simple LDAP binds due to AD security policies. To be fully operational |product|
   requires an additional account to perform simple LDAP binds.  Create a **dedicated
   user account** in AD, and set a complex *non-expiring* password for it.

After all the prerequisites are fulfilled, proceed with the join from the
:guilabel:`Accounts provider` page:

* Fill :guilabel:`DNS server IP address` field which usually is the
  IP address of an AD domain controller.

* (only for Microsoft Active Directory) specify the **dedicated user account**
  credentials under the :guilabel:`Advanced settings` panel.

* Push the :guilabel:`Submit` button. You will be prompted for an user name and a
  password: provide AD ``administrator`` or any other account
  credentials with permissions to join a new machine to the domain 
  (i.e. ``admin`` on |product|).

.. _bind-remote-ldap-section:

Bind to a remote LDAP server
----------------------------

If the remote server is a |product|, only its IP address is required in
:guilabel:`Accounts provider` page.

For other implementations, change the bind credentials, Base DN and encryption
settings under the :guilabel:`Advanced settings` panel.

Users
=====

A newly created user account remains locked until it has set a password.
Disabled users are denied to access system services.

When creating a user, following fields are mandatory:

* User name
* Full name (name and surname)

A user can be added to one or more group from the :guilabel:`Users` page or from the :guilabel:`Groups` one.

Sometimes you need to block user's access to services without deleting the
account. This can be achieved using the :guilabel:`Lock` and :guilabel:`Unlock`
actions.

.. note:: When a user is deleted, all user data will be also deleted.

.. index:: password

Changing the password
---------------------

If there wasn't given an initial password during user creation, the user account is disabled.
To enable it, set a password using the :guilabel:`Change password` button.

When a user is enabled, the user can access the Server Manager and change
his/her own password by going to the :guilabel:`user@domain.com` label on the
upper right corner of the screen and clicking on :guilabel:`Profile`.

If the system is bound to an Active Directory account provider, users can change
their password also using the Windows tools.  In this case you can not set passwords
shorter than 6 *characters* regardless of the server policies. Windows performs
preliminary checks and sends the password to the server where it is evaluated 
according to the :ref:`configured policies <password-management-section>`.


Credentials for services
------------------------

The user's credentials are the **user name** and his **password**.  Credentials
are required to access the services installed on the system.

The user name can be issued in two forms: *long* (default) and *short*.  The
*long* form is always accepted by services. It depends on the service to accept
also the *short* form.

For instance if the domain is *example.com* and the user is *goofy*:

Long user name form
    *goofy@example.com*

Short user name form
    *goofy*

To access a shared folder, see also :ref:`smb-access-section`.

.. _groups-section:

Groups
======

A group of users can be granted some permission, such as authorize
access over a :ref:`shared folder <shared_folders-section>`. The granted
permission is propagated to all group members.

Two special groups can be created.  Members of these groups are granted access
to the panels of the Server Manager:

* :dfn:`domain admins`: members of this group have the same permissions as the
  *root* user from the Server Manager.

* :dfn:`managers`: members of this group are granted access to the *Management*
  section of the Server Manager.

.. index: admin

.. _admin-account-section:

Admin account
=============

If a **local AD or LDAP provider** is installed, an *admin* user, member of the
*domain admins* group is created automatically. This account allows
access to all configuration pages within the Server Manager.  It is initially
*disabled* and has no access from the console.

.. tip:: To enable the *admin* account set its password.

Where applicable, the *admin* account is granted special privileges on some
specific services, such as joining a workstation to an Active Directory domain.

If |product| is bound to a **remote account provider**, the *admin* user and
*domain admins* group could be created manually, if they do not already exist.

If a user or group with a similar purpose is already present in the remote
account provider database, but it is named differently, |product| can be
configured to rely on it with the following commands: ::

    config setprop admins user customadmin group customadmins
    /etc/e-smith/events/actions/system-adjust custom

.. _password-management-section:

Password management
===================

The system provides the ability to set constraints on password :dfn:`complexity` and :dfn:`expiration`.

Password policies can be changed from web interface.

Complexity
-----------

The :index:`password` complexity is a set of minimum conditions for password to be accepted by the system:
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
   if password is older than 6 months, the server will send an email to indicate that password has expired.
   In this case you need to change the user password.
   For example, if the last password change was made in January and the activation of the deadline in October,
   the system will assume the password changed in January is expired, and notify the user.


.. _effects-of-expired-password:

Effects of expired passwords
----------------------------

After password expiration, the user is still able to read and send email messages.

If |product| has an Active Directory account provider, the user cannot access
shared folders, printers (by Samba) and other domain computers.

.. _import-users_section:

Import users
============

It is possible to create user accounts from a TSV (Tab Separated Values) file with the following format: ::

  username <TAB> fullName <TAB> password <NEWLINE>

Example: ::

  mario <TAB> Mario Rossi <TAB> 112233 <NEWLINE>

then execute: ::

  /usr/share/doc/nethserver-directory-<ver>/import_users <youfilename>

For example, if the user’s file is /root/users.tsv, execute following command: ::

  /usr/share/doc/nethserver-sssd-`rpm --query --qf "%{VERSION}" nethserver-sssd`/scripts/import_users /root/users.tsv

Alternative separator character: ::

  import_users users.tsv ','

Import Emails
-------------

It is possible to create mail aliases from a TSV (Tab Separated Values) file with the following format: ::

  username <TAB> emailaddress <NEWLINE>

Then you can use the ``import_emails`` script. See :ref:`import-users_section` for a sample script invocation.

Import Groups
-------------

Group management is available from the command line through ``group-create`` and ``group-modify`` events ::

  signal-event group-create group1 user1 user2 user3
  signal-event group-modify group1 user1 user3 user4
