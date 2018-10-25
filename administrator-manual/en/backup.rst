.. _backup-section:

======
Backup
======

:index:`Backup` is the only way to restore a machine when disasters occur.
The system handles two kinds of backups:

* :index:`configuration backup`
* :index:`data backup`

**Configuration backup** contains only system configuration files. 
The purpose of this kind of backup is to quickly restore a machine in case of
:ref:`disaster recovery <disaster-recovery-section>`. When the machine is functional, a full data restore can be
done even if the machine is already in production.

**Data backup** is enabled by installing the "Backup" module and, by default, contains all
the data stored in the system (user's home directories, shared folders, emails, etc).
The *single backup* runs once a day and can be full or incremental on a weekly basis.
This backup also contains the archive of the configuration backup.
More backups can be configured to save different data at different intervals.

.. _backup_config_rpms:
.. _backup_config-section:

Configuration backup
====================

From page :guilabel:`Backup (configuration)` the system
configuration can be saved, downloaded, uploaded and restored again.

Furthermore, an automated task runs every night at 00.15 and creates a new
archive, :file:`/var/lib/nethserver/backup/backup-config.tar.xz`, if the
configuration has changed during the previous 24 hours. Under :guilabel:`Backup
(configuration) > Configure` page, specify the number of :guilabel:`Automatic
backups to keep`.

The list of installed modules is included in the backup archive. The
restore procedure can download and install the listed modules automatically.

Configuration backup customization
----------------------------------

In most cases it is not necessary to change the configuration backup. 
But it can be useful, for example, if you have a custom httpd configuration.
In this case you can add the file that contains the customization to the list of files to backup.

**Inclusion**

If you wish to add a file or directory to configuration backup, add a line to the file :file:`/etc/backup-config.d/custom.include`.

For example, to backup :file:`/etc/httpd/conf.d/mycustom.conf` file, add this line: ::

  /etc/httpd/conf.d/mycustom.conf

Do not add big directories or files to the configuration backup.

**Exclusion**

If you wish to exclude a file or directory from the configuration backup, add a line to the file :file:`/etc/backup-config.d/custom.exclude`.

.. warning:: 
   Make sure not to leave empty lines inside edited files.
   The syntax of the configuration backup supports only simple file and directory paths.

.. _backup_usb_disk-section:


.. _backup_data-section:

Data backup
===========

|product| implements 2 types of data backup:

- Single backup (primary, default, backward compatible)
- Multiple backups (multi-backup, multi-engine)

The data backup can be performed using different engines:

* duplicity (default) - http://duplicity.nongnu.org/
* restic - https://restic.net/
* rsync - https://rsync.samba.org/

When selecting an engine, the system administrator should carefully evaluate multiple aspects:

* Compression: data is compressed on the destination, disk usage can vary in function
  of compression efficiency which depends also on the data set
* Deduplication: instead of compressing files, data is split into chunks and only a copy
  of each chunk is kept. Efficiency depends highly on the data set
* Encryption: data saved inside the destination storage is encrypted.
  Usually data is encrypted before transfer
* Size: space used on the destination for each backup, may be smaller or equal than the original data set.
  When using engines without encryption support, the destination should always be bigger than
  the source
* Retention: the policy which sets the amount of time in which a given set of data will remain available for restore
* Integrity: it's the engine ability to check if the performed backup is valid in case of restore
* Type: a backup can be full, incremental or snapshot based (incremental-forever):

  * full: all files are copied to the destination each time
  * incremental: compare the data with last full backup and copy only changed or added items.
    The full backup and all the intermediate incrementals are needed for the restore process.
    A full backup is required on a regular basis.
  * snapshot: create a full backup only the first time, then create differential backups.
    Snapshots can be deleted and consolidated and only one full backup is needed


=============  =========== ============= ========== ========= ==================
Engine         Compression Deduplication Encryption Integrity Type  
=============  =========== ============= ========== ========= ==================
**duplicity**  Yes         No            No         Yes       full / incremental
**restic**     No          Yes           Yes        Yes       snapshot
**rsync**      No          Partial       No         No        snapshot
=============  =========== ============= ========== ========= ==================

Engines
-------

Duplicity
^^^^^^^^^

:index:`Duplicity` is the well-known default engine for |product|.
It has a good compression algorithm which will reduce storage usage on the destination.
Duplicity requires a full backup once a week, when the data set is very big the process
may take more than 24 hours to complete.
|product| doesn't implement backup encryption if the engine is Duplicity.

Supported storage backends:

- CIFS
- NFS
- USB
- WebDAV (only when used as single backup)

Restic
^^^^^^

:index:`Restic` implements a snapshot-based and always-encrypted backup.
It has support for deduplication and can perform backup on cloud services.
Since Restic requires only one full backup, all runs after the first should be fast
and could be scheduled multiple times a day.

Supported storage backends:

* CIFS
* NFS
* USB
* WebDAV (only when used as *single backup*)
* SFTP (SSH File Transfer Protocol)
* Amazon S3 (or any compatible server like `Minio <https://www.minio.io/>`_)
* Backblaze `B2 <https://www.backblaze.com/b2/cloud-storage.html>`_
* Restic `REST server <https://github.com/restic/rest-server>`_


Rsync
^^^^^

:index:`Time machine-style` backup engine using :index:`rsync`.
After the first full backup, it copies only modified or new files using
fast incremental file transfer.
On the destination, partial deduplication is obtained using hard links.
If the backup destination directory is full, the oldest backups are 
automatically deleted to free space.

Supported storage backends:

- CIFS
- NFS
- USB
- WebDAV (only when used as *single backup*)
- SFTP (SSH File Transfer Protocol)

Rsync doesn't support encryption nor compression on the destination.
During data transfer, SFTP assures encryption and data is compressed to minimize bandwidth usage.

.. note::
   When using rsync engine, make sure the storage backend supports symbolic and hard links.
   Please note that |product| doesn't support links on Samba shares due to security implications.
   Also symlinks are not supported on WebDAV.

Single backup
-------------

This is the default system backup which can be configured and restored using the web interface.
It can be scheduled once a day, can include system logs and implements notifications to the system administrator
or to an external mail address.

Storage backends
^^^^^^^^^^^^^^^^

Single backup can be saved on a destination chosen between:

* USB: disk connected to a local USB port (See: :ref:`backup_usb_disk-section`)
* CIFS: Windows shared folder, it's available on all NAS (Network Attached Storage). Use access credentials like: MyBindUser,domain=mydomain.com
* NFS: Linux shared folder, it's available on all NAS, usually faster than CIFS
* WebDAV: available on many NAS and remote servers (use a server with a valid SSL certificate as WebDAV target, otherwise the system will fail mounting the filesystem)

.. note:: The destination directory is based on the server host name: in case of
   FQDN change, the administrator should take care to copy/move the backup data from
   the old directory to the new one.

Change backup engine
^^^^^^^^^^^^^^^^^^^^

Duplicity is the default engine for the *single backup*.
You can change it executing one of the commands below.

To use restic: ::

  config setprop backup-data Program restic

To use rsync: ::

  config setprop backup-data Program rsync

To use duplicity: ::

  config setprop backup-data Program duplicity

The backup will use the selected engine on next run.
When the new engine has completed at least one backup, remember to cleanup the destination by removing
data from the old engine.

Multiple backups
----------------

The administrator can schedule multiple backups using different engines and destinations.
A valid policy could be creating a weekly backup to a local destination using duplicity, while scheduling
a daily backup to a cloud storage using restic.

.. note:: 
   Multiple backups can't be configured using the server-manager web user interface.
   All operations should be performed from command line.

When configuring multiple backups, please bear in mind two golden rules:

* always use different destinations for each engine
* avoid scheduling concurrent backups, each backup should run when the previous one has been completed

Limitation of multiple backups:

* disk usage report is not implemented
* WebDAV can't be used as storage backend

Every backup record is saved inside the ``backups`` database. Each record can have 3 different types:

* ``duplicity``
* ``restic``
* ``rsync``

Common properties:

* ``status`` : enable or disable the backup, can be ``enabled`` or ``disabled``
* ``Notify``: if set to ``always``, always send a notification with backup status; if set to ``error``, send a notification only on error; if set to ``never``, never send a notification
* ``NotifyTo``: send the notification to given mail address, default is ``root@localhost``
* ``VFSType`` : set the storage backend

To list all configured backups: ::

  db backups show

Output example: ::

  mybackup=rsync
    BackupTime=1 7 * * *
    Notify=error
    NotifyTo=root@localhost
    SMBHost=192.168.1.234
    SMBLogin=test
    SMBPassword=test
    SMBShare=test
    VFSType=cifs
    status=enabled
  

Schedule
^^^^^^^^

The backup schedule uses the cron syntax saved inside the ``BackupTime`` property.
Below, some examples.


Every night at 3: ::

  db backups setprop mybackup BackupTime '0 3 * * *'

Every hour, at minute 15: ::

  db backups setprop mybackup BackupTime '15 * * * *'

At 04:05 on every Sunday: ::

  db backups setprop mybackup BackupTime '5 4 * * 0'


For more examples, see:

- https://crontab-generator.org/
- https://crontab.guru

Retention policy
^^^^^^^^^^^^^^^^

Each engine can implement its own retention policy.
The policy can be set using the ``CleanupOlderThan`` property.

The property takes a number followed by D, M or Y (Days, Months, or Years respectively).

Example: cleanup after 30 days: ::

  db backups setprop mybackup CleanupOlderThan 30D

The retention policy is not supported by the rsync backend.

Storage backends
^^^^^^^^^^^^^^^^

Multiple backups support different storage backends.
Some backends are engine-specific.

CIFS
~~~~

Samba or Windows share, ``VFSType`` is ``cifs``.
Supported by all backends.

Properties:

* ``SMBShare``: Samba share name
* ``SMBHost``: Samba server host name or IP address
* ``SMBLogin``: Samba login user
* ``SMBPassword``: Samba password for the given user

USB
~~~

USB-attached disk, ``VFSType`` is ``usb``.
Supported by all backends.

Properties:

* ``USBLabel``

NFS
~~~

Network File System, ``VFSType`` is ``nfs``.
Supported by all backends.

Properties:

* ``NFSHost``: NFS server host name or IP address
* ``NFSShare``: NFS share name

SFTP
~~~~

SSH File Transfer Protocol, ``VFSType`` is ``sftp``.
Supported only by restic and rsync.

Properties:

* ``SftpHost``: SSH host name or IP address
* ``SftpUser``: SSH user
* ``SftpPort``: SSH port
* ``SftpDirectory``: destination directory, must be writable by the SSH user

S3
~~

Amazon S3 (or compatible), ``VFSType`` is ``s3``.
Supported only by restic. 

Properties:

* ``S3AccessKey``: user access key
* ``S3Bucket``: bucket (directory) name
* ``S3Host``: S3 host, use ``s3.amazonaws.com`` for Amazon
* ``S3SecretKey``: secret access key

How to setup Amazon S3 access keys: |restic_link|.

.. |restic_link| raw:: html

   <a href="https://restic.readthedocs.io/en/stable/080_examples.html" target="_blank">documentation</a>

B2
~~

Backblaze B2, ``VFSType`` is ``b2``.
Supported only by restic. 

Properties:

* ``B2AccountId``: B2 account name
* ``B2AccountKey``: B2 account secret key
* ``B2Bucket``: B2 bucket (directory)


Rest
~~~~

Restic REST server, ``VFSType`` is ``rest``.
Supported only by restic.

Properties:

* ``RestDirectory``: destination directory
* ``RestHost``: REST server hostname or IP address
* ``RestPort``: REST sever port (default for server is 8000)
* ``RestProtocol``: REST protocol, can be ``http`` or ``https``
* ``RestUser``: user for authentication (optional)
* ``RestPassword``: password for authentication (optional)

Examples
^^^^^^^^

Rsync backup, every day at 7:15 to a remote server. The SFTP backend requires the password of the remote server to execute SSH key exchange. ::

  db backups set mybackup1 rsync status enabled BackupTime '15 7 * * *' Notify error NotifyTo root@localhost \
  VFSType sftp SftpHost 192.168.1.2 SftpUser root SftpPort 22 SftpDirectory /mnt/mybackup1 
  echo -e "Nethesis,1234" > /tmp/mybackup1-password; signal-event nethserver-backup-data-save mybackup1 /tmp/mybackup1-password

Restic backup every day at 3:00 to Amazon S3, no retention limit: ::

  db backups set mybackup1 restic VFSType s3 BackupTime '0 3 * * *' CleanupOlderThan never Notify error NotifyTo root@localhost status enabled \
  S3AccessKey XXXXXXXXXXXXXXXXXXXX S3Bucket restic-demo S3Host s3.amazonaws.com S3SecretKey xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx Prune 0
  signal-event nethserver-backup-data-save mybackup1

Duplicity backup every day at 22:00 to CIFS, 10 days retention: ::

  db backups set mybackup1 duplicity VFSType cifs BackupTime '0 22 * * *' CleanupOlderThan 10D Notify error NotifyTo root@localhost status enabled \
  SMBHost nas.localnethserver.org SMBLogin myuser SMBPassword mypassword SMBShare mybackup
  signal-event nethserver-backup-data-save mybackup1


To manually start a backup, execute: ::

  backup-data -b <name>

Where ``name`` is the backup name. For the examples above, the name is ``mybackup1``.

.. _backup_customization-section:

Data backup customization
-------------------------

If additional software is installed, the administrator can edit
the list of files and directories included (or excluded).

Single backup
^^^^^^^^^^^^^

**Inclusion**

If you wish to add a file or directory to data backup, add a line to the file :file:`/etc/backup-data.d/custom.include`.

For example, to backup a software installed inside :file:`/opt` directory, add this line: ::

  /opt/mysoftware


The same syntax applies to configuration backup. Modifications should be done inside the file :file:`/etc/backup-config.d/custom.include`.


**Exclusion**

If you wish to exclude a file or directory from data backup, add a line to the file :file:`/etc/backup-data.d/custom.exclude`.

For example, to exclude all directories called *Download*, add this line: ::

  **Download**

To exclude a mail directory called *test*, add this line: ::

  /var/lib/nethserver/vmail/test/ 


The same syntax applies to configuration backup. Modifications should be done inside the file :file:`/etc/backup-config.d/custom.exclude`.

Multiple backups
^^^^^^^^^^^^^^^^

All multiple backups read the same configuration of the single backup, but the list 
of saved and excluded files can be customized using two special files, where ``name`` is the name of the multiple backup:

- ``/etc/backup-data/<name>.include``
- ``/etc/backup-data/<name>.exclude``

Both files will override the list of included and excluded data set from the single backup.
The accepted syntax is the same as the single backup (see paragraph above).

For example, given a backup named ``mybackup1`` create the following files:

- :file:`/etc/backup-data/mybackup1.include`
- :file:`/etc/backup-data/mybackup1.exclude`

Example
~~~~~~~

It's possible to configure the single backup to save all data and create
a multiple backup which includes only the mail and is scheduled each our.

1. Configure the new ``mymailbackup``: ::

     db backups set mymailbackup restic status enabled BackupTime '0 * * * *' Notify error NotifyTo root@localhost \
     VFSType nfs NFSHost nsfs.server.loc NFSShare test CleanupOlderThan 1d Prune 0

2. Create a custom include containing only the mail directory: ::

     echo "/var/lib/nethserver/vmail" > /etc/backup-data/mymailbackup.include

3. Create an empty custom exclude file: ::

     touch /etc/backup-data/mymailbackup.exclude

4. Apply the configuration: ::

     signal-event nethserver-backup-data-save mymailbackup


.. warning:: Make sure not to leave empty lines inside edited files.



.. _data_restore:

Selective restore of files
==========================

Make sure that backup destination is reachable (for example, the USB disk must be
connected).

In the :guilabel:`Restore files` menu section it is possible to search,
select and restore one or more directories from the backup, navigating the graphical
tree with all paths included in the backup.

By default, the latest backup tree is shown. If you want to restore a file from a
previous backup, select the backup date from :guilabel:`Backup File` selector.

There are two options when restoring:

* Restore files in the original path, the current files in the filesystem are
  overwritten by the restored files from backup

* Restore files in original path but the restored files from backup are moved to
  a new directory (the files are not overwritten) in this path: ::

    /complete/path/of/file_YYYY-MM-DD (YYYY-MM-DD is the date of restore)

To use the search field, simply insert at least 3 chars and the searching starts
automatically, highlighting the matched directories.

It is possible to restore the directories by clicking on the **Restore** button.

.. note:: Multiple selection can be done with :kbd:`Ctrl` key pressed.

Command line procedure
----------------------

All relevant files are saved under :file:`/var/lib/nethserver/` directory:

* Mails: :file:`/var/lib/nethserver/vmail/<user>`
* Shared folders: :file:`/var/lib/nethserver/ibay/<name>`
* User's home: :file:`/var/lib/nethserver/home/<user>`

Single backup
^^^^^^^^^^^^^

It is possible to list all files inside the last backup using this command: ::

 backup-data-list

The command can take some time depending on the backup size.

To restore a file/directory, use the command: ::

  restore-file <position> <file>

Example, restore *test* mail account to :file:`/tmp` directory: ::

  restore-file /tmp /var/lib/nethserver/vmail/test

Example, restore *test* mail account to original position: ::

  restore-file / /var/lib/nethserver/vmail/test


The system can restore a previous version of directory (or file).

Example, restore the version of a file from 15 days ago: ::

  restore-file -t 15D /tmp "/var/lib/nethserver/ibay/test/myfile" 

The ``-t`` option allows to specify the number of days (15 in this scenario).
When used with snapshot-based engines, the ``-t`` option requires the name of the snapshot
to restore.

Multiple backups
^^^^^^^^^^^^^^^^

To list data inside a multiple backup, use: ::

  backup-data-list -b <name>

To restore all data in the original location, use: ::

  restore-data -b <name>

To restore a file or directory, use: ::

  restore-file -b <name> <position> <path>

.. note:: When you are using *CIFS* to access the share, and the command doesn't work
          as expected, verify that user and password for the network share are correct.
          If user or password are wrong, you will find NT_STATUS_LOGON_FAILURE errors in
          :file:`/var/log/messages`.
          Also, you can use the :command:`backup-data-list` to check if the backup is accessible.



USB disk configuration
======================

The best filesystem for USB backup disks is EXT3 or EXT4. FAT filesystem is supported but *not recommended*,
while NTFS is **not supported**. EXT3 or EXT4 is mandatory for the rsync engine.

Before formatting the disk, attach it to the server and find the device name: ::

 # dmesg | tail -20

 Apr 15 16:20:43 mynethserver kernel: usb-storage: device found at 4
 Apr 15 16:20:43 mynethserver kernel: usb-storage: waiting for device to settle before scanning
 Apr 15 16:20:48 mynethserver kernel:   Vendor: WDC WD32  Model: 00BEVT-00ZCT0     Rev:
 Apr 15 16:20:48 mynethserver kernel:   Type:   Direct-Access           ANSI SCSI revision: 02
 Apr 15 16:20:49 mynethserver kernel: SCSI device sdc: 625142448 512-byte hdwr sectors (320073 MB)
 Apr 15 16:20:49 mynethserver kernel: sdc: Write Protect is off
 Apr 15 16:20:49 mynethserver kernel: sdc: Mode Sense: 34 00 00 00
 Apr 15 16:20:49 mynethserver kernel: sdc: assuming drive cache: write through
 Apr 15 16:20:49 mynethserver kernel: SCSI device sdc: 625142448 512-byte hdwr sectors (320073 MB)
 Apr 15 16:20:49 mynethserver kernel: sdc: Write Protect is off
 Apr 15 16:20:49 mynethserver kernel: sdc: Mode Sense: 34 00 00 00
 Apr 15 16:20:49 mynethserver kernel: sdc: assuming drive cache: write through
 Apr 15 16:20:49 mynethserver kernel:  sdc: sdc1
 Apr 15 16:20:49 mynethserver kernel: sd 7:0:0:0: Attached scsi disk sdc
 Apr 15 16:20:49 mynethserver kernel: sd 7:0:0:0: Attached scsi generic sg3 type 0
 Apr 15 16:20:49 mynethserver kernel: usb-storage: device scan complete
 
Another good command could be: ::

 lsblk -io KNAME,TYPE,SIZE,MODEL

In this scenario, the disk is accessibile as *sdc* device.

* Create a Linux partition on the whole disk: ::

    echo "0," | sfdisk /dev/sdc

* Create the filesystem on *sdc1* partition with a label named *backup*.
  The filesystem should be tuned on the backup engine used: rsync and restic require a lot of
  inodes, where duplicity performs better on file systems optimized for large files.

  For duplicity use: ::

    mke2fs -v -T largefile4 -j /dev/sdc1 -L backup

  For rsync and restic use: ::

    mkfs.ext4 -v /dev/sdc1 -L backup -E lazy_itable_init

* Detach and reconnect the USB disk:

  You can simulate it with the following command: ::

    blockdev --rereadpt /dev/sdc

* Now the *backup* label will be displayed inside the :guilabel:`Backup (data)` page.


.. _disaster-recovery-section:

Disaster recovery
=================

The system is restored in two phases: configuration first, then data.
Right after configuration restore, the system is ready to be used if the proper packages are installed. 
You can install additional packages before or after the restore.
For example, if the mail-server is installed, the system can send and receive mails.

Other restored configurations:

* Users and groups
* SSL certificates

.. note:: The root/admin password is not restored.

Steps to be executed:

1. Install the new machine. If possible, enable a network connection at
   boot (refer to :ref:`installation-manual` section) to automatically re-install
   the required modules

2. Access the Server Manager and follow the :ref:`first-configuration-wizard-section` procedure

3. At step :guilabel:`Restore configuration`, upload the configuration archive.
   The option :guilabel:`Download modules automatically` should be enabled.

4. If a warning message requires it, reconfigure the network roles assignment.
   See :ref:`restore-roles-section` below.

5. Verify the system is functional

6. Restore data backup executing on the console ::

    restore-data

Please note that the disaster recovery should be always performed from a local media (eg. NFS or USB) to speed up the process.

.. _restore-roles-section:
   
Restore network roles 
---------------------

If a role configuration points to a missing network interface, the
:guilabel:`Dashboard`, :guilabel:`Backup (configuration) > Restore`
and :guilabel:`Network` pages pop up a warning. This happens for
instance in the following cases:

* configuration backup has been restored on a new hardware
* one or more network cards have been substituted
* system disks are moved to a new machine

The warning points to a page that lists the network cards present in
the system, highlighting those not having an assigned :ref:`role
<network-section>`. Such cards have a drop down menu where to select a
role available for restoring.

For instance, if a card with the *orange* role has been replaced, the
drop down menu will list an element ``orange``, near the new
network card.

The same applies if the old card was a component of a logical
interface, such as a bridge or bond.

By picking an element from the drop down menu, the old role is
transferred to the new physical interface.

Click the :guilabel:`Submit` button to apply the changes.

.. warning:: Choose carefully the new interfaces assignment: doing a mistake
             here could lead to a system isolated from the network!

If the missing role is ``green`` an automatic procedure attempts to fix
the configuration at boot-time, to ensure a minimal network
connectivity and login again on the Server Manager.


