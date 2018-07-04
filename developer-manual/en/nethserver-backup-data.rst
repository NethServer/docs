======================
nethserver-backup-data
======================

This module implements data backup for NethServer using different engines.

Available engines:

- duplicity: execute a full backup once a week, an incremental snapshot all other days of the week. Compression is enabled by default, encryption is not currently supported.
  It supports only storage backend which can be mounted on a local directory.  Used also for the single backup.
- restic: always execute incremental backups using file deduplication. Encryption is always enabled, compression is not implemented.
  It supports local and remote backends.
- rsync: Time Machine-style backup using rsync. Very fast and reliable, the destination contains just regular files which can be easily accessed.


The ``nethserver-backup-data`` package requires ``nethserver-backup-config``.

Single backup
=============

It uses the key ``backup-data`` inside ``configuration`` database.

Properties:

* ``status`` : enable or disable the automatic backup, can be ``enabled`` or ``disabled``. Default is ``enabled``. Regardless of this property, the backup is always executed if started manually
* ``BackupTime``: time of the scheduled backup. Must be in the form ``hh:mm``. Default is ``1:00``
* ``VFSType`` : set the backup medium, can be ``usb``, ``cifs``, ``nfs`` or ``webdav``.
* ``SMBShare``: contains the Samba share name
* ``SMBHost`` : host name of the SMB server
* ``SMBLogin`` : login user for the SMB server
* ``SMBPassword`` : password for the SMB server
* ``USBLabel`` : contains the filesystem label 
* ``NFSHost`` : host name of the NFS server
* ``NFShare`` : contains the NFS share name
* ``Notify``: if set to ``always``, always send a notification with backup status; if set to ``error``, send a notication only on error; if set to ``never``, never send a notification
* ``NotifyFrom``: set a different sender then ``root@localhost``
* ``NotifyTo``: send the notification to given mail address, default is ``root@localhost``
* ``WebDAVUrl`` : contains the WebDAV URL address
* ``WebDAVLogin`` : login user for the WebDAV server
* ``WebDAVPassword`` : password for the WebDAV server
* ``Program`` : program used to perfrom the backup. Backup and restore processes will look for an action called respectively  ``backup-data-<Program>`` and ``restore-data-<Program>``. Default is: duplicity
* ``Type`` : can be ``full`` or ``incremental``. If ``full``, a full backup will be executed every time. If ``incremental``, a full backup will be executed once a week at ``FullDay``, all other backups will be incremental
* ``FullDay`` : number of day of the week when a full backup will be executed. Can be a number from 0 (Sunday) to 6 (Saturday). Defaults is ``0``.
* ``Mount`` : directory where the share (or usb drive) will be mounted. Defaults is ``/mnt/backup``
* ``VolSize`` : size of chunks in MB, if supported by ``Program``. Default is 250
* ``CleanupOlderThan`` : time to retain backups, accept duplicity syntax (eg. 7D, 1M). Default is: never (keep all backups)
* ``IncludeLogs``: if enabled, add ``/var/log`` directory to backup, can be ``enabled`` or ``disabled``. Default is ``disabled``.

Supported VFSType:

* ``cifs`` : save the backup on a remote SMB server. Authentication is mandatory.
* ``nfs`` : save the backup on a remote NFS server. No authentication supported.
* ``usb`` : save the backup on a USB device. The device must have a writable filesystem with a custom label. 
  When the backup is started, the system will search for an USB device with the filesystem label saved in ``USBLabel``.
* ``webdav`` : save the backup on a webDAV server. When using a secure connection make sure the target webDAV server has a valid SSL certificate, otherwise the system will fail mounting the filesystem.

Change single backup engine
---------------------------

As default, duplicity is used for the single backup.
If you whish to change the engine to ``restic`` or ``rsync``, change the ``Program`` peroperty accordingly.

Example for restic: ::

  config setprop backup-data Program restic

Multiple backups
================

Multiple backups can be scheduled in different hours to multiple storage backends.
Some features are still not implemented for multiple backupss:

* configuration backup can't be directly extracted from data backup
* WebDAV storage backend
* disk usage report
* push configuration backup to backup directory
* Web UI for data restore


Every backup record is saved inside the ``backups`` database. Each record can have 3 different types:

* ``duplicity``
* ``restic``
- ``rsync``

The key of the record is referred as the backup ``name``.

Some properties are common to both backends and have the same behavior described under "Single backup" section, the only exception is ``BackupTime``:

* ``status``
* ``BackupTime``: time of the scheduled backup. Must be in the cron-style syntax: Es. ``15 7 * * *``. Runs on 7:15.
* ``SMBShare``
* ``SMBHost``
* ``SMBLogin`` 
* ``SMBPassword``
* ``USBLabel``
* ``NFSHost``
* ``NFShare``
* ``CleanupOlderThan``
* ``VFSType``: each backend can implement its own list of supported storage backends

Each record should contains only the properties relative to the storage backend selected with ``VFSType``.

Duplicity
---------

Properties valid only for duplicity engine (see "Single backup" section):

* ``Type``
* ``FullDay``
* ``VolSize``

Supported ``VFSType`` :

* ``usb``
* ``cifs``
* ``nfs``

Restic
------

See ``nethserver-restic-package``.

Backup
======

The main command is ``/sbin/e-smith/backup-data`` which starts the backup process. The backup is composed of three parts:

* *pre-backup-data* event: prepare the system and mount the destination share
* */etc/e-smith/events/actions/backup-data-<program>* action: execute the backup. This actions must implement full/incremental logic. The backup is directly saved on the mounted share (or usb device).
* *post-backup-data*: umount share and cleanup. Actions in this event can also implement retention policies (currently not implemented).


Logs and wrapper
----------------

Everything is logged to standard output and standard error.

If the backup is executed using ``backup-data-wrapper``,
a new log will be created inside ``/var/log/backup``.

After backup execution, the wrapper will also call
all executable scripts inside ``/etc/backup-data.hooks/`` directory.

Each script is invoked with the following parameters:

- backup name
- log file
- backup exit code


Single backup
-------------

To start the backup, execute: ::

  backup-data


Multiple backups
----------------

Adding a backup
~~~~~~~~~~~~~~~

1. Create a backup record with all required options. Example: create a restic backup named ``t1`` using sFTP backend:

   ::

     db backups set t1 restic VFSType sftp SftpHost 192.168.1.123 SftpUser root SftpPort 22 SftpDirectory /mnt/t1 status enabled BackupTime 3:00 CleanupOlderThan 30D Notify error NotifyFrom '' NotifyTo root@localhost

2. Enable the configuration:

  ::

     echo -e "Nethesis,1234" > /tmp/t1-password; signal-event nethserver-backup-data-save t1  /tmp/t1-password

Start a backup
~~~~~~~~~~~~~~

Start the backup, by passing the name of the backup to ``backup-data`` command. Example:

  ::

    backup-data -b t1

Indexing
========

In the *pre-backup-data* event the disk analyzer (Duc) make an indexing of filesystem, useful to create the graphical tree.

The name of the actions is ``/etc/e-smith/events/actions/nethserver-restore-data-duc-index`` and it compose the JSON file to create
the navigable graphic tree.

The indexing feature is limited to single backup.

Customization
=============

Single backup
-------------

Add custom include/exclude inside following files:

* /etc/backup-data.d/custom.include
* /etc/backup-data.d/custom.exclude

Multiple backups
---------------

The multiple backups read the same configuration of the single backup.
List of saved and excluded files can be customized using two special files (where ``name`` is the name of the backup):

- ``/etc/backup-data/<name>.include``
- ``/etc/backup-data/<name>.exclude``

Both file will override the list on included and excluded files from the single backup.

Retention policy
================

All backups can be deleted after a certain amount of time. Cleanup process takes place in post-backup-data event.
See ``CleanupOlderThan`` property.

Restore
=======

Restore from command line
-------------------------

The main command is ``/sbin/e-smith/restore-data`` which starts the restore process:

* *pre-restore-data* event: used to prepare the system (Eg. mysql stop)
* *restore-data-<program>* action: search for a backup in the configuration database and restore it
* *post-restore-data* event: used to inform programs about new available data (eg. mysql restart)

Single backup
~~~~~~~~~~~~~

To restore all data into the original location, use: ::

  restore-data

To restore a file or directory, use: ::

  restore-file <position> <path>

Example: restore ``/var/lib/nethserver/secrets`` to the orignal position: ::

  restore-file / /var/lib/nethserver/secrets

Example: restore ``/var/lib/nethserver/secrets`` under ``/tmp``: ::

  restore-file /tmp /var/lib/nethserver/secrets

Multiple backups
~~~~~~~~~~~~~~~~

To restore all data into the original location, use: ::

  restore-data -b <name>

To restore a file or directory, use: ::

  restore-file -b <name> <position> <path>


Restore from graphic interface
------------------------------

After the selection of the paths to restore, the main command called is ``/usr/libexec/nethserver/nethserver-restore-data-help`` that
reads the list of paths to restore and creates a executable command to restore the directories. If the second option of restore was selected (Restored file without overwrite the existing files), after the restore in a temp directory, the script moves the restored directories in the correct paths.

List backup contents
====================

The list of file inside the single backup can be obtained using: ::

  /sbin/e-smith/backup-data-list

For multiple backups, use the ``-b`` option to pass the backup name: ::

 /sbin/e-smith/backup-data-list -b t1

Duplicity
=========

The default program used for backup is duplicity using the globbing file list feature. Encryption is disabled and duplicity cache is stored in ``/var/lib/nethserver/backup/duplicity/ directory``.
We plan to support all duplicity features in the near future.

See http://duplicity.nongnu.org/ for more information.


Listing backup sets
-------------------

To list current backup sets:

1. Mount the backup directory
2. Query duplicity status
3. Umount the backup directory

Just execute: ::

  /etc/e-smith/events/actions/mount-`config getprop backup-data VFSType`
  duplicity collection-status --no-encryption --archive-dir /var/lib/nethserver/backup/duplicity/ file:///mnt/backup/`config get SystemName`
  /etc/e-smith/events/actions/umount-`config getprop backup-data VFSType`


