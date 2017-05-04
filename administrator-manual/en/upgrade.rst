.. index:: upgrade

.. _upgrade-section:

========================
Upgrade from |product| 6
========================

The upgrade from |product| 6 to |product| |version| can be achieved using
the **backup and restore** procedure.

.. warning::

    Before running the migration procedure, read carefully all the sections of this
    chapter.

    Please also read :ref:`discontinued-section`.

#. Make sure to have an updated backup of the original installation.

#. Install |product| |version| and complete the initial steps using the first configuration wizard.
   The new machine must have the same hostname of the old one, while the domain name
   can be changed to fit the accounts provider needs.

#. Restore the configuration backup using the web interface.
   If any error occurs, check the :file:`/var/log/messages` log file for further information: ::

       grep -E '(FAIL|ERROR)' /var/log/messages

#. If needed, change the network configuration accordingly to the new hardware.

#. Complete the restore procedure with the following command: ::

    restore-data

#. Check the restore log: ::

    cat /var/log/restore-data.log

#. Each file under file:`/etc/e-smith/templates-custom/` must be manually checked for 
   compatibility with version |version|.


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

After the restore procedure, the following manual steps are required to promote
the LDAP server (nethserver-directory package) to a *local Active Directory*
accounts provider.

An additional, free, IP address from the *green* network is required by the
Linux container to run the local Active Directory accounts provider.

For instance:

* nethserver IP (green): ``192.168.98.252``
* free additional IP in green network: ``192.168.98.7``

Verify it is really a free IP:

::

    # ping 192.168.98.7
    PING 192.168.98.7 (192.168.98.7) 56(84) bytes of data.
    From 192.168.98.252 icmp_seq=1 Destination Host Unreachable

Ensure there is a working Internet connection:

::

    # curl -I http://packages.nethserver.org/nethserver/
    HTTP/1.1 200 OK


Set the IP for nsdc container and run the upgrade event:

::

    config set nsdc service IpAddress 192.168.98.7
    signal-event nethserver-directory-ns6upgrade

For more information about the local Active Directory accounts provider, see
:ref:`ad-local-accounts-provider-section`.

.. _ads-upgrade-section:

Active Directory member upgrade
-------------------------------

The system upgrade procedure tries to reuse the AD machine credentials contained
in the configuration backup.

To upgrade the server correctly:

- the **machine credentials must be still valid**

- the AD domain controller must be reachable

At the end of the restore procedure Users and Groups page could fail to connect
AD. To fix the credentials used by Server Manager to access AD, go to "Accounts
provider > Advanced settings" page. For more information see
:ref:`join-existing-ad-section`.

.. warning:: Mail aliases from AD server are not imported automatically!

Shared folders
==============

Shared folders have been split into two packages:

- "Shared folders" page configures only Samba shares, it provides data access
  using CIFS/SMB protocol and can be used to share files among Windows and Linux
  workstations

- The "Virtual hosts" panel provides HTTP and FTP access, it has been designed
  to host web sites and web applications

Every shared folder with web access configured in |product| 6 can be migrated to
a virtual host directly from the web interface by selecting the action
:guilabel:`Migrate to virtual host`. After the migration, data inside the new
virtual host will be accessible using only FTP and HTTP protocols.


Owncloud and Nextcloud
======================

In |product| |version|, Owncloud has officially been replaced by Nextcloud.

However Owncloud 7 is still available to avoid service disruption after the upgrade.
Migration from Owncloud to Nextcloud is manual and can be arranged according
to user's need.
