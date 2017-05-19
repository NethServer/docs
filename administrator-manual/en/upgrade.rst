.. index:: upgrade

.. _upgrade-section:

========================
Upgrade from |product| 6
========================

The upgrade from |product| 6 to |product| |version| can be achieved using
the :ref:`disaster-recovery-section` procedure.

.. warning::

    Before running the upgrade procedure, read carefully all the sections of this
    chapter. Please also read :ref:`discontinued-section`.

#. Make sure to have an updated backup of the original installation.

#. Install |product| |version| and complete the initial steps using the first configuration wizard.
   The new machine must have the same hostname of the old one, to access the backup set correctly. 
   Install and configure the backup module.

#. Restore the configuration backup using the web interface. The network configuration is restored, too!
   If any error occurs, check the :file:`/var/log/messages` log file for further information: ::

       grep -E '(FAIL|ERROR)' /var/log/messages

#. If needed, go to :guilabel:`Network` page and fix the network configuration
   accordingly to the new hardware.
   If the machine was joined to an existing Active Directory domain,
   read :ref:`ads-upgrade-section`.

#. Complete the restore procedure with the following command: ::

    restore-data

#. Check the restore logs: ::

    /var/log/restore-data.log
    /var/log/messages

#. Each file under :file:`/etc/e-smith/templates-custom/` must be manually checked for 
   compatibility with version |version|.

.. note::

   During the whole upgrade process, all network services will be inaccessible.

Accounts provider
=================

There are different upgrade scenarios, depending on how the source machine was configured.

* If the source system was a NT Primary Domain Controller (Samba server role was
  :guilabel:`Primary Domain Controller` -- PDC) or a standalone file server
  (role was :guilabel:`Workstation` -- WS), refer to :ref:`pdc-upgrade-section`.

* If the source system was joined to an Active Directory domain (Samba server
  role was :guilabel:`Active Directory member` -- ADS), refer to
  :ref:`ads-upgrade-section`.

* In any other case, the LDAP server is upgraded automatically to *local
  LDAP accounts provider*, preserving existing users, passwords and groups.

.. _pdc-upgrade-section:

Primary Domain Controller and Workstation upgrade
-------------------------------------------------

After the restore procedure, go to :guilabel:`Accounts provider` page and
select the :guilabel:`Upgrade to Active Directory` procedure.
The button will be available only if network configuration has already been
fixed accordingly to the new hardware.

An additional, free, IP address from the *green* network is required by the
Linux container to run the local Active Directory accounts provider.

For instance:

* server IP (green): ``192.168.98.252``
* free additional IP in green network: ``192.168.98.7``

Ensure there is a working Internet connection:

::

    # curl -I http://packages.nethserver.org/nethserver/
    HTTP/1.1 200 OK

For more information about the local Active Directory accounts provider, see
:ref:`ad-local-accounts-provider-section`.

Shared folder connections may require further adjustment.

.. warning::

    Read carefully the :ref:`upgrade-shared-folders` section, because the connection
    credentials may change when upgrading to |product| |version|.

The upgrade procedure preserves user, group and computer accounts.

.. warning::

   Users not enabled for Samba in |product| 6 will be migrated as
   locked users. To enable these locked users, the administrator
   will have to set a new password.

.. _ads-upgrade-section:

Active Directory member upgrade
-------------------------------

After **restoring the configuration**, join the server to the existing Active
Directory domain from the web interface. For more information see
:ref:`join-existing-ad-section`.

At the end, proceed with **data restore**.

.. warning:: Mail aliases from AD server are not imported automatically!

.. _upgrade-shared-folders:

Shared folders
==============

Shared folders have been split into two packages:

- "Shared folders" page configures only Samba SMB shares; it provides data access
  using CIFS/SMB protocol and can be used to share files among Windows and Linux
  workstations

- The "Virtual hosts" panel provides HTTP and FTP access, it has been designed
  to host web sites and web applications

.. _upgrade-smb-access:

SMB access
----------

In |product| |version| the SMB security model is based on Active Directory. As
consequence when upgrading (or migrating) a file server in Primary Domain
Controller (PDC) or Standalone Workstation (WS) role the following rule apply:

  When connecting to a shared folder, the NetBIOS domain name must be either
  prefixed to the user name (i.e. ``MYDOMAIN\username``), or inserted in the
  specific form field.

HTTP access
-----------

Every shared folder with web access configured in |product| 6 can be migrated to
a virtual host directly from the web interface by selecting the action
:guilabel:`Migrate to virtual host`. After the migration, data inside the new
virtual host will be accessible using only FTP and HTTP protocols.

See also :ref:`virtual_hosts-section` for more information about
:guilabel:`Virtual hosts` page.

Mail server
===========

All mailboxes options like SPAM retention and quota, along with ACLs, user shared
mailboxes and subscriptions are preserved.

Mailboxes associated to groups with :guilabel:`Deliver the message into a shared folder` option enabled,
will be converted to public shared mailboxes.
The public shared folder will be automatically subscribed by all group members,
but all messages will be markes as unread.

Let's Encrypt
=============

Let's Encrypt certificates are restored during the process, but will not be
automatically renewed.

After the upgrade process has been completed, access the web interface
and reconfigure Let's Encrypt from the :guilabel:`Server certificate` page.

Owncloud and Nextcloud
======================

In |product| |version|, Owncloud has officially been replaced by Nextcloud.

However Owncloud 7 is still available to avoid service disruption after the upgrade.

.. note::

   In case of :ref:`upgrade from local LDAP to Samba AD <pdc-upgrade-section>`,
   user data inside Owncloud will not be accessible either from the
   web interface or desktop/mobile clients. In such case, install and migrate to
   Nextcloud after the upgrade to Samba Active Directory has been completed.


Migration from Owncloud to Nextcloud is manual and can be arranged according
to user's need.
The migration script will import all files and users from LDAP to Nextcloud,
but shared resources **will not** be migrated.

To migrate users and data, use following command: ::

    /usr/share/doc/$(rpm -q --queryformat "%{NAME}-%{VERSION}" nethserver-nextcloud)/owncloud-migrate

After the migration, please replace Owncloud clients with Nextcloud ones [#DownloadNC]_,
then make sure to set the new application URL: ``https://<your_server_address>/nextcloud``.

.. [#DownloadNC] Nextcloud clients download https://nextcloud.com/install/#install-clients

Phonebook
=========

In |product| |version|, perl library ``NethServer::Directory`` has been replaced
by ``NethServer::Password``.
Please update your custom scripts accordingly.

Example of old code: ::

  use NethServer::Directory;
  NethServer::Directory::getUserPassword('myservice', 0);

New code: ::

  use NethServer::Password;
  my $password = NethServer::Password::store('myservice');

Documentation available via perldoc command: ::

   perldoc NethServer::Password
