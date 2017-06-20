======================
nethserver-backup-data
======================

The`nethserver-backup-data package`` requires ``nethserver-backup-config``. This module implements a traditional incremental/full backup. It uses the key ``backup-data`` inside ``configuration`` database.

Properties:

* ``status`` : enable or disable the automatic backup, can be ``enabled`` or ``disabled``. Default is ``enabled``. Regardless of this property, the backup is always executed if started manually
* ``BackupTime: time of the scheduled backup. Must be in the form ``hh:mm``. Default is ``1:00``
* ``VFSType`` : set the backup medium, can be ``usb``, ``cifs``, ``nfs`` or ``webdav``.
* ``SMBShare``: contains the Samba share name
* ``SMBHost`` : host name of the SMB server
* ``SMBLogin`` : login user for the SMB server
* ``SMBPassword`` : password for the SMB server
* ``USBLabel`` : contains the filesystem label 
* ``NFSHost`` : host name of the NFS server
* ``NFShare`` : contains the NFS share name
* ``WebDAVUrl`` : contains the WebDAV URL address
* ``WebDAVLogin`` : login user for the WebDAV server
* ``WebDAVPassword`` : password for the WebDAV server
* ``Program`` : program used to perfrom the backup. Backup and restore processes will look for an action called respectively  ``backup-data-<Program>`` and ``restore-data-<Program>``. Default is: duplicity
* ``Type`` : can be ``full`` or ``incremental``. If ``full``, a full backup will be executed every time. If ``incremental``, a full backup will be executed once a week at ``FullDay``, all other backups will be incremental
* ``FullDay`` : number of day of the week when a full backup will be executed. Can be a number from 0 (Sunday) to 6 (Saturday). Defaults is ``0``.
* ``Mount`` : directory where the share (or usb drive) will be mounted. Defaults is ``/mnt/backup``
* ``LogFile`` : output of the backup process. Default is ``/var/log/last-backup.log``
* ``VolSize`` : size of chunks in MB, if supported by ``Program``. Default is 250
* ``CleanupOlderThan`` : time to retain backups, accept duplicity syntax (eg. 7D, 1M). Default is: never (keep all backups)

Supported VFSType:

* ``cifs`` : save the backup on a remote SMB server. Authentication is mandatory.
* ``nfs`` : save the backup on a remote NFS server. No authentication supported.
* ``usb`` : save the backup on a USB device. The device must have a writable filesystem with a custom label. 
  When the backup is started, the system will search for an USB device with the filesystem label saved in ``USBLabel``.
* ``webdav`` : save the backup on a webDAV server. When using a secure connection make sure the target webDAV server has a valid SSL certificate, otherwise the system will fail mounting the filesystem.

Backup
------

The main command is ``/sbin/e-smith/backup-data`` which starts the backup process (if enabled). The backup is composed of three parts:

* *pre-backup-data* event: prepare the system and mount the destination share
* */etc/e-smith/events/actions/backup-data-<program>* action: execute the backup. This actions must implement full/incremental logic. The backup is directly saved on the mounted share (or usb device).
* *post-backup-data*: umount share and cleanup. Actions in this event can also implement retention policies (currently not implemented).

Logs:

* /var/log/backup-data.log: parsable log
* /var/log/last-backup.log: backup program output

Indexing
--------

In the *pre-backup-data* event the disk analyzer (Duc) make an indexing of filesystem, useful to create the graphical tree.

The name of the actions is ``/etc/e-smith/events/actions/nethserver-restore-data-duc-index`` and it compose the JSON file to create
the navigable graphic tree.

Customization
-------------

Add custom include/exclude inside following files:

* /etc/backup-data.d/custom.include
* /etc/backup-data.d/custom.exclude

Retention policy
~~~~~~~~~~~~~~~~

All backups can be deleted after a certain amount of time. Cleanup process takes place in post-backup-data event.
See ``CleanupOlderThan`` property.

A log of cleanup action is saved in ``/var/log/last-cleanup.log``.

Duplicity
~~~~~~~~~

The default program used for backup is duplicity using the globbing file list feature. Encryption is disabled and duplicity cache is stored in ``/var/lib/nethserver/backup/duplicity/ directory``.
We plan to support all duplicity features in the near future.

See http://duplicity.nongnu.org/ for more information.


Listing backup sets
^^^^^^^^^^^^^^^^^^^

To list current backup sets:

1. Mount the backup directory
2. Query duplicity status
3. Umount the backup directory

Just execute: ::

  /etc/e-smith/events/actions/mount-`config getprop backup-data VFSType`
  duplicity collection-status --no-encryption --archive-dir /var/lib/nethserver/backup/duplicity/ file:///mnt/backup/`config get SystemName`
  /etc/e-smith/events/actions/umount-`config getprop backup-data VFSType`

Restore command line
--------------------

The main command is ``/sbin/e-smith/restore-data`` which starts the restore process:

* *pre-restore-data* event: used to prepare the system (Eg. mysql stop)
* *restore-data-<program>* action: search for a backup in the configuration database and restore it
* *post-restore-data* event: used to inform programs about new available data (eg. mysql restart)

Restore grahic interface
------------------------

After the selection of the paths to restore, the main command called is ``/usr/libexec/nethserver/nethserver-restore-data-help`` that
reads the list of paths to restore and creates a executable command to restore the directories. If the second option of restore was selected (Restored file without overwrite the existing files), after the restore in a temp directory, the script moves the restored directories in the correct paths.

Logs:

* /var/log/restore-data.log: parsable log
* /var/log/restore.log: process output
