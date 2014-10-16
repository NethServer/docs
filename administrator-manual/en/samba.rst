===============
Windows network
===============

|Microsoft Windows (TM)| interoperability is provided by Samba
[#SambaOrg]_. To install it, select the :dfn:`File Server` module, or
any other module that requires it.

|product| configures Samba to act in a Windows network according to
its *role*. You can choose the role from the Server Manager, in the
:menuselection:`Windows network` page.  

Currently the following roles are available:

* Workstation
  
* Primary Domain Controller

* Active Directory Member

The differences between these roles concern `where` user database is
stored and `which hosts` can access it.  The user database contains
the list of users of the system, their passwords, group membership and
other informations.

Workstation

    In this role |product| use only its own local user database. Only
    local users can access its resources, by providing the correct user
    name and password credentials.  This is the behaviour of a Windows
    standalone workstation.


Primary Domain Controller

    When acting as `Primary Domain Controller` (PDC), |product|
    emulates a Windows 2000/NT domain controller, by providing access
    to the local user database only from trusted workstations.  People
    can log on any trusted workstation by typing their domain
    credentials, then have access to shared files and printers.


Active Directory member 
   
    In this role |product| becomes a trusted server of an existing
    Active Directory domain.  When accessing a resource from a domain
    workstation, user credentials are checked against a domain
    controller, and the access to the resource is granted.

.. |Microsoft Windows (TM)| unicode:: Microsoft \x20 Windows U+2122

.. _samba_ws:

Workstation
-----------

When acting as a workstation, |product| registers itself as member of
the *Windows workgroup* specified by the :guilabel:`Workgroup
name` field. The default value is ``WORKGROUP``.

From the other hosts of the Windows network, |product| will be listed
in *Network resources*, under the node named after the
:guilabel:`Workgroup name` field value.

As stated before, to access the server resources, clients
must provide the authentication credentials of a valid local account.

.. _samba_pdc:

Primary domain controller
-------------------------

The Primary Domain Controller (PDC) is a centralized place where users
and hosts accounts are stored. To setup a Windows network where
|product| acts in PDC role follow these steps.


1. From the Server Manager, :menuselection:`Windows Network` page,
   select :guilabel:`Primary Domain Controller`, then
   :guilabel:`SUBMIT` the change.
   
   The Domain name by default is assumed to be the second domain part
   of the host name in capital letters (e.g. if the FQDN server host
   name is ``server.example.com`` the default domain name will be
   ``EXAMPLE``. If the default does not fit your needs, choose a
   simple name respecting the rules:

   * length between 1 and 15 characters;

   * begin with a letter, then only letters, numbers, or the minus
     ``-`` char;

   * only capital letters.

   For more informations refer to Microsoft Naming conventions [#MS909264]_.

2. For each workstation of the Windows network, join the new domain.
   This step requires privileged credentials.  In |product|, members
   of the ``domadmins`` group can join workstations to the domain.
   Moreover, ``domadmins`` members are granted administrative
   privileges on domain workstations.  By default, only the ``admin``
   user is member of the ``domadmins`` group.

   Some versions of Windows may require applying a system registry
   patch to join the domain.  From the Server Manager, follow
   :guilabel:`Client registry settings` link to download the
   appropriate ``.reg`` file.  Refer to the official Samba
   documentation [#SambaRegistry]_ for more informations.

.. _samba_ads: 

Active Directory member
-----------------------

The Active Directory member role (ADS) configures |product|
as an Active Directory domain member, delegating authentication to domain
controllers.  When operating in ADS mode, Samba is configured to map
domain accounts into |product|, thus files and directories access can
be shared across the whole domain.  

.. note:: For mail server integration with AD, refer to the
          :ref:`email-section` module documentation.

Joining an Active Directory domain has some pre-requisites:

1. In :menuselection:`DNS and DHCP` page, set the domain controller
   as DNS. If a second DC exists, it can be set as secondary DNS.

2. In :menuselection:`Date and time` page, set the DC as NTP time
   source; the Kerberos protocol requires the difference between
   systems clocks is less than 5 minutes.

After pre-requisites are set, proceed in :menuselection:`Windows
network` page, by selecting the :guilabel:`Active Directory member`
role:

* Fill :guilabel:`Realm` and :guilabel:`Domain` fields with proper
  values. Defaults come from FQDN host name: maybe they do not fit
  your environment so **make sure Realm and Domain fields are set
  correctly**.

* :guilabel:`LDAP accounts branch` must be set to the LDAP branch
  containing your domain accounts if you plan to install the
  :ref:`email-section` module. It is not actually required by Samba.

* :guilabel:`SUBMIT` changes. You will be prompted for an user name and
  password: provide AD ``administrator`` or any other account
  credentials with permissions to join the machine to the domain.

.. rubric:: Footnotes

.. [#SambaOrg] Samba official website http://www.samba.org/
.. [#MS909264] Naming conventions in Active Directory for computers,
               domains, sites, and OUs
               http://support.microsoft.com/kb/909264
.. [#SambaRegistry] Registry changes for NT4-style domains
                    https://wiki.samba.org/index.php/Registry_changes_for_NT4-style_domains
