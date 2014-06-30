======
Backup
======

NethServer has two kinds of backup:

* configuration backup (nethserver-backup-config)
* data backup (nethserver-backup-data)

Configuration backup contains only system configuration files (passwd, config databases, etc).
It's scheduled to be executed every night and will create a new archive only if any file is changed in the last 24 hours. 


Backup libraries use conf.d directory behavior (see ``perldoc NethServer::Backup``).
When a backup is started, the system will search for all files in ``/etc/backup-config.d`` directory. 
This directory can contain .include and .exclude files. Each file contain a list of file to include/exclude into/from the backup.

Example file :file:`/etc/backup-config.d/nethserver-base.include` ::

  /etc/e-smith/templates-custom
  /etc/e-smith/templates-user-custom
  /etc/ssh
  /etc/sudoers
  /etc/passwd
  /etc/shadow
  /etc/group
  /etc/gshadow

Exclusions are evaluated after all inclusions.

All libraries are inside the ``nethserver-backup-config`` package.

Log format
==========

Backup and restore actions will log all steps in a file using a parsable format. Each log line has the following format: ::

 <DATE_HOUR> - <TAG> - <MESSAGE> - <EXIT_STATUS>

Fields:

* DATE_HOUR: date in ISO 8601 format (%Y-%m-%d) and time in 24 hour notation (%H:%M:%S)
* TAG: can be START, STEP, SUCCESS or ERROR
* MESSAGE: log message
* EXIT_STATUS: (optional) the exit status of the process


Notifications
=============

Both nethserver-backup-config and nethserver-backup-data comes with two property to configure notification:

* ``notify``: enable or disable notification. Possible values:

  * ``always``: send notification regardless of backup exit status
  * ``never``: do not send any notification regardless of backup exit status
  * ``error``: send notification only if an error occurs

* ``notifyTo``: notification mail destination address (default is: admin``localhost)

Configuration backup
====================

The ``nethserver-backup-config`` package implements the backup of configuration and relies on the ``backup-config`` key inside the ``configuration`` database.

Properties:
* ``status`` : enable or disable the automatic backup, can be ``enabled`` or ``disabled``. Default is ``enabled``.

Backup
------

The main command is ``/sbin/e-smith/backup-config`` which starts the backup process (if enabled). The backup process has 3 steps:

* *pre-backup-config* event: used to prepare data, for example a LDAP dump of users
* *backup-config-execute* action: actually execute the backup if any file is changed in the last 24 hours. The backup file is saved in ``/var/lib/nethserver/backup/backup-config.tar.gz`` (see ``perldoc NethServer::BackupConfig``) 
* *post-backup-config* event: used to post-process the backup file, for example to copy the backup to a remote server or encrypting the archive

This package does not provide any default action in the pre-backup-config and post-backup-config events.

Logs:

* /var/log/backup-config.log: parsable log

Restore
-------

The main command is ``/sbin/e-smith/restore-config`` which starts the restore process:

* *pre-restore-config* event: used to prepare the system, for example stop a running service
* *restore-config-execute* action: search for a backup file in the well-known directory (see above) and restore it
* *post-restore-config* event: used to apply restored configuration, for example load the LDAP dump

This package does not provide any action in the pre-restore-config and post-restore-config events.

Logs:

* /var/log/restore-config.log: parsable log

Customization
-------------

Add custom include/exclude inside following files:

* /etc/backup-config.d/custom.include
* /etc/backup-config.d/custom.exclude

Data backup
===========

The`nethserver-backup-data package`` requires ``nethserver-backup-config``. This module implements a traditional incremental/full backup. It uses the key ``backup-data`` inside ``configuration`` database.

Properties:

* ``status`` : enable or disable the automatic backup, can be ``enabled`` or ``disabled``. Default is ``enabled``. Regardless of this property, the backup is always executed if started manually
* ``BackupTime: time of the scheduled backup. Must be in the form ``hh:mm``. Default is ``1:00``
* ``VFSType`` : set the backup medium, can be ``usb``, ``cifs`` or ``nfs``.
* ``SMBShare``: contains the Samba share name
* ``SMBHost`` : host name of the SMB server
* ``SMBLogin`` : login user for the SMB server
* ``SMBPassword`` : password for the SMB server
* ``USBLabel`` : contains the filesystem label 
* ``NFSHost`` : host name of the NFS server
* ``NFShare`` : contains the NFS share name
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
  When the backup is started, the system will search for an USB device with the filesystem label saved in ``SmbShare``.

Backup
------

The main command is ``/sbin/e-smith/backup-data`` which starts the backup process (if enabled). The backup is composed of three parts:

* *pre-backup-data* event: prepare the system and mount the destination share
* */etc/e-smith/events/actions/backup-data-<program>* action: execute the backup. This actions must implement full/incremental logic. The backup is directly saved on the mounted share (or usb device).
* *post-backup-data*: umount share and cleanup. Actions in this event can also implement retention policies (currently not implemented).

Logs:

* /var/log/backup-data.log: parsable log
* /var/log/last-backup.log: backup program output

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

Restore
-------

The main command is ``/sbin/e-smith/restore-data`` which starts the restore process:

* *pre-restore-data* event: used to prepare the system (Eg. mysql stop)
* *restore-data-<program>* action: search for a backup in the configuration database and restore it
* *post-restore-data* event: used to inform programs about new available data (eg. mysql restart)

Logs:

* /var/log/restore-data.log: parsable log
* /var/log/restore.log: process output
