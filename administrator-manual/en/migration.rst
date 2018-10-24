.. index:: migration

.. _migration-section:

=====================================
Migration from NethService/SME Server
=====================================

Migration is the process to convert a SME Server/NethService
machine (:dfn:`source`) into a |product| (:dfn:`destination`).
It can be achieved from a :ref:`backup <backup_migration-section>` or :ref:`using rsync <migrate_with_rsync-section>`.

.. note:: No custom template is migrated during the migration process.
   Check the new template files before copying any custom fragment from the old backup.

.. warning:: 
    
    Before running the migration procedure, read carefully all the sections of this
    chapter.

.. _migration_account:

Accounts provider
=================

You should configure an :ref:`accounts provider <account-providers>` before
starting the migration procedure. 

* If the source system was joined to an Active Directory domain (Samba server
  role was ADS), configure a *remote Active Directory* accounts provider.
  
* If the source system was a NT Primary Domain Controller (Samba server role was
  PDC) install a *local Active Directory* accounts provider.

* If access to Shared Folders on the destination system requires user
  authentication, install a *local Active Directory* accounts provider.

* In any other case, install a *local LDAP* accounts provider.

If you choose a *local Active Directory* accounts provider, remember to fully
configure and start the DC before executing the ``migration-import`` event. See
:ref:`account-providers`.

Furthermore, the following accounts are ignored by the migration procedure
because they are already provided by Active Directory:

* ``administrator``
* ``guest``
* ``krbtgt``

.. index::
   pair: migration; email

.. _migration_email:

Email
=====

Before running |product| in production, some considerations about the
network and existing mail client configurations are required: what
ports are in use, if SMTPAUTH and TLS are enabled.  Refer to
:ref:`email_clients` and :ref:`email_policies` sections for more
information.

In a mail server migration, the source mail server could be on
production even after the backup has been done, and email messages
continue to be delivered until it is taken down permanently.

An helper script based on ``rsync`` is provided by package
``nethserver-mail-server``. It
runs on the destination host and synchronizes destination mailboxes
with the source host: ::

    Usage:
        /usr/share/doc/nethserver-mail-server-<VERSION>/sync_maildirs.sh [-h] [-n] [-p] -s IPADDR
            -h          help message
            -n          dry run
            -p PORT     ssh port on source host (default 22)
            -s IPADDR   rsync from source host IPADDR
            -t TYPE     source type: sme8 (default), ns6


The source host at ``IPADDR`` must be accessible by the ``root`` user, through
``ssh`` with public key authentication.

.. _migration-web-server:

Apache
======

The SSL cipher suite configuration is not migrated automatically because the
source system uses a weak cipher suite by default. To migrate it manually,
execute the following commands: ::

    MIGRATION_PATH=/var/lib/migration
    config setprop httpd SSLCipherSuite $(db $MIGRATION_PATH/home/e-smith/db/configuration getprop modSSL CipherSuite)
    signal-event nethserver-httpd-update

.. _migration-ibays:

Ibays
=====

The *ibay* concept has been superseded by :ref:`shared_folders-section`.
Supported protocols for accessing Shared folders are:

- SFTP, provided by the ``sshd`` daemon

- SMB file sharing protocol, typical of Windows networking, implemented by Samba

.. warning::

    Read carefully the :ref:`upgrade-shared-folders` section in the
    :ref:`upgrade-section` chapter, because the connection credentials may change when
    migrating to |product| |version|.

Starting from |product| |version|, Shared folders are not configurable for HTTP
access. After ``migration-import`` event, old ibays could be migrated according 
to the following rules of thumb:

1.  If the ibay was a **virtual host**, install the "Web server" module from the
    :guilabel:`Software center` page. Copy the ibay contents to the virtual host
    root directory. Refer to :ref:`virtual_hosts-section`.

2.  If the ibay access was restricted with a **secret password** (for instance, to
    share contents with a group of people across the internet), the
    :ref:`virtual_hosts-section` page still offers the same feature. Also the
    :ref:`Nextcloud <nextcloud-section>` module could be a good replacement.

3.  If the ibay contents were accessible with an URL like ``http://<IP>/ibayname``
    the easiest procedure to keep it working is moving it to Apache document root: ::
        
        mv -iv /var/lib/nethserver/ibay/ibayname /var/www/html/ibayname
        chmod -c -R o+rX /var/www/html/ibayname
        db accounts delete ibayname
        signal-event nethserver-samba-update


After migration, ibays will retain a backward compatibile profile.
To take advantage of new features, including Samba Audit, the ibay
configuration must be switched to the new profile.
From command line execute: ::

 db accounts setprop ibay_name SmbProfileType default
 signal-event ibay-mody ibay_name

Where ``ibay_name`` is the name of the ibay to configure.

.. _backup_migration-section:

Migration from backup
=====================

#. In the source host, create a full backup archive and move it
   to the destination host.

#. In the destination host, install all packages that cover the same
   features of the source.

#. Explode the full backup archive into some directory; for instance,
   create the directory :file:`/var/lib/migration`.

#. In destination host, signal the event ``migration-import``::

     signal-event migration-import /var/lib/migration

   This step will require some time.

#. Check for any error message in :file:`/var/log/messages`::
 
     grep -E '(FAIL|ERROR)' /var/log/messages



.. _migrate_with_rsync-section:

Migration with rsync
====================

The process is much faster than migrating from a backup.

Before starting make sure to have:

- a running NethService/SME installation, we will call it original server or source server
- a running |product| 7 installation with at least the same disk space of the source server, we will call it destination server
- a working network connection between the two severs

Please also make sure the source server allows root login via SSH key and password.

Sync files
----------

The synchronization script copies all data using rsync over SSH.
Files are saved inside :file:`/var/lib/migration` directory.
If the destination server doesn't have any SSH keys, the script will also create a pair of RSA keys and copy the public key to the source server.
All directories excluded from the backup data will not be synced.

On the target machine, execute the following command: ::

  screen rsync-migrate <source_server_name> [ssh_port]

Where

- ``source_server_name`` is the host name or IP of the original server
- ``ssh_port`` is the SSH port of the original server (default is 22)

Example: ::

    screen rsync-migrate mail.nethserver.org 2222

When asked, insert the root password of the source server, make a coffee and wait patiently.

The script will not perform any action on the source machine and can be invoked multiple times.

Sync and migrate
----------------

If called with ``-m`` option, ``rsync-migrate`` will execute a final synchronization and upgrade
the target machine.

Example: ::

    screen rsync-migrate -m mail.nethserver.org 2222

The script will:

- stop every service on the source machine (except for SSH)
- execute the ``pre-backup`` event on the source machine
- sync all remaining data
- execute the ``migration-import`` event on the destination machine


At the end, check for any error message in :file:`/var/log/messages`::
 
     grep -E '(FAIL|ERROR)' /var/log/messages

