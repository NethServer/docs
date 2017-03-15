.. index:: upgrade

.. _upgrade-section:

========================
Upgrade from |product| 6
========================

The upgrade from |product| 6 to |product| 7 can be achieved using
the backup and restore procedure.

.. warning:: 
    
    Before running the migration procedure, read carefully all the sections of this
    chapter.
    Please also read :ref:`discontinued-section`.

#. Make sure to have an updated backup of the original installation.

#. Install |product| 7 and complete the initial steps using the first configuration wizard.
   The new machine must have the same hostname of the old one, while the domain name
   can be changed to fit account provider needs.

#. Restore the configuration backup using the web interface.
   If any error occurs, check the :file:`/var/log/messages` log file for further information: ::

       grep -E '(FAIL|ERROR)' /var/log/messages

#. If needed, change the network configuration accordingly to the new hardware.

#. Restore the data backup using the web interface.

Account provider
================

There are different upgrade scenarios, depending on how the source machine was configured.

* If the source system was joined to an Active Directory domain (Samba server
  role was ADS), the system will keep all settings but you will need to manually migrate 
  mail addresses (see :ref:`ad_mail_upgrade-section`).

* If the source system was a NT Primary Domain Controller (Samba server role was
  PDC), you will need to follow some easy manual steps to install a *local Active Directory*.
  All users, groups and machine accounts will be preserved. See :ref:`samba_promotion-section`.

* In any other case, if the LDAP server (nethserver-directory package) was installed
  in the original system, a *local LDAP* accounts provider will be provided.

.. samba_promotion-section:

Promote to Active Directory
---------------------------

ADS: how to set hostname, fix auth in advanced settings (sogo creds)

Email
=====

.. ad_mail_upgrade-section:

Migrate mail addresses from AD
------------------------------

Shared folders
==============

Shared folders have been split into two packages:

- "Shared folder" page configures only Samba shares, it provides data access using CIFS/SMB protocol and
  can be used to share files among Windows and Linux workstations
- The "Web access" panel provides HTTP and FTP access, it has been designed to host web sites and web applications

Every shared folder with web access configured in |product| 6 can be migrated to a virtual host
directly from the web interface by selecting the button :guilabel:`Migrate to virtual host`.
After the migration, data inside the new virtual host will be accessible using only the FTP and HTTP protocols.


Owncloud and Nextcloud
======================

In |product| 7, Owncloud has officially been replaced by Nextcloud.

But Owncloud 7 is still available to avoid service disruption after the upgrade.
Migration from Owncloud to Nextcloud it's manual and can be arrenged according
to users need.
