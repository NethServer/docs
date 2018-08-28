========================
nethserver-backup-config
========================

Configuration backup contains only system configuration files (passwd, config databases, etc).
It's scheduled to be executed every night and will create a new archive only if any file is changed in the last 24 hours. 

Backup libraries use conf.d directory behavior (see ``perldoc NethServer::Backup``).
When a backup is started, the system will search for all files in ``/etc/backup-config.d`` directory. 
This directory can contain .include and .exclude files. Each file contain a list of file to include/exclude into/from the backup.

Example file ``/etc/backup-config.d/nethserver-base.include`` ::

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

Configuration backup
====================

The ``nethserver-backup-config`` package implements the backup of configuration and relies on the ``backup-config`` key inside the ``configuration`` database.

Properties:

* ``status`` : enable or disable the automatic backup, can be ``enabled`` or ``disabled``. Default is ``enabled``.

Backup
------

The main command is ``/sbin/e-smith/backup-config`` which starts the backup process (if enabled). The backup process has 3 steps:

* *pre-backup-config* event: used to prepare data, for example a LDAP dump of users
* *backup-config-execute* action: actually execute the backup if any file is changed in the last 24 hours. 
  The backup file is saved in ``/var/lib/nethserver/backup/backup-config.tar.xz`` (see ``perldoc NethServer::BackupConfig``) 
* *post-backup-config* event: used to post-process the backup file, for example to copy the backup to a remote server or encrypting the archive

The configuration backup runs every night and it creates a new backup only if:

* destination file does not exist
* or new files are added or removed to/from the backup set
* or content of any file inside the set is changed

This package does not provide any default action in the pre-backup-config and post-backup-config events.
But you can create a script inside the post-backup-config event to copy the configuration backup to a remote machine
using, for example, the SSH protocol.

The configuration backup is included inside the data backup.

Restore
-------

The main command is ``/sbin/e-smith/restore-config`` which starts the restore process:

* *pre-restore-config* event: used to prepare the system, for example stop a running service
* *restore-config-execute* action: search for a backup file in the well-known directory (see above) and restore it
* *post-restore-config* event: used to apply restored configuration, for example reinstall packages and load the LDAP dump

This package does not provide any action in the pre-restore-config event.

Please note that if no ``/var/lib/nethserver/backup/backup-config.tar.xz`` file is found, the ``restore-config`` command 
will try to access the data backup to retrieve the configuration backup.

The ``restore-config`` options:

* ``--no-reinstall`` : disable package reinstall during restore
* ``--mask-unit=<name>`` : use systemd to mask the specified unit (example: disable httpd-admin restart during restore)

Customization
-------------

Add custom include/exclude inside following files:

* /etc/backup-config.d/custom.include
* /etc/backup-config.d/custom.exclude

