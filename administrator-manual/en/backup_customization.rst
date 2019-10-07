.. _backup_customization-section:

====================
Backup customization
====================

Basic customization can be done directly from the new Server Manager. See :ref:`backup_basic_customization-section`.

.. _backup_data-section:

Data backup
===========

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
  When using engines without compression support, the destination should always be bigger than
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

Storage backends
----------------

Supported by all engines:

* CIFS: Windows shared folder, it's available on all NAS (Network Attached Storage). Use access credentials like: MyBindUser,domain=mydomain.com
* NFS: Linux shared folder, it's available on all NAS, usually faster than CIFS
* WebDAV: available on many NAS and remote servers (use a server with a valid SSL certificate as WebDAV target, otherwise the system will fail mounting the filesystem)
* USB: disk connected to a local USB/SATA port

Supported by restic and rsync:

* SFTP: SSH File Transfer Protocol

Supported only by restic:

* Amazon S3 (or any compatible server like `Minio <https://www.minio.io/>`_)
* Backblaze `B2 <https://www.backblaze.com/b2/cloud-storage.html>`_

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

.. note:: The destination directory is based on the server host name: in case of
   FQDN change, the administrator should take care of copying/moving the backup data from
   the old directory to the new one.


restic
^^^^^^

:index:`restic` implements a snapshot-based and always-encrypted backup.
It has support for deduplication and can perform backup on cloud services.
Since restic requires only one full backup, all runs after the first should be fast
and could be scheduled multiple times a day.

Supported storage backends:

* CIFS
* NFS
* USB
* WebDAV (only when used as *single backup*)
* SFTP (SSH File Transfer Protocol)
* Amazon S3 (or any compatible server like `Minio <https://www.minio.io/>`_)
* Backblaze `B2 <https://www.backblaze.com/b2/cloud-storage.html>`_
* restic `REST server <https://github.com/restic/rest-server>`_


When configuring a backup using the restic engine and a remote storage backend,
please ensure you have enough bandwidth to complete the first backup within
24 hours. Otherwise restic will create multiple different snapshots.
If you have a slow connection and you still want to use a remote storage
backend, follow this procedure:

- configure the restic backup
- manually execute the backup by clicking on :guilabel:`Run now`
- disable the configured backup, so it will not start at next scheduled execution
- when the backup is over, re-enable it to allow scheduled execution

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

Command line execution
----------------------

To run a backup from command line, use: ::

  backup-data -b <name>

where ``name`` is the name of the backup you want to run.

.. note::
   By default, the name of the *first* data backup configured on |product| is ``backup-data``


.. _backup_advanced_customization-section:

Data backup customization
-------------------------

If additional software is installed, the administrator can edit
the list of files and directories included (or excluded).

Inclusion
^^^^^^^^^

If you wish to add a file or directory to data backup, add a line to the file :file:`/etc/backup-data.d/custom.include`.

For example, to backup a software installed inside :file:`/opt` directory, add this line: ::

  /opt/mysoftware


The same syntax applies to configuration backup. Modifications should be done inside the file :file:`/etc/backup-config.d/custom.include`.


Exclusion
^^^^^^^^^

If you wish to exclude a file or directory from data backup, add a line to the file :file:`/etc/backup-data.d/custom.exclude`.

For example, to exclude all directories called *Download*, add this line: ::

  **Download**

To exclude a mail directory called *test*, add this line: ::

  /var/lib/nethserver/vmail/test/ 


The same syntax applies to configuration backup. Modifications should be done inside the file :file:`/etc/backup-config.d/custom.exclude`.

Override inclusions and exclusions
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

All backups read the same configuration, but the list 
of saved and excluded files can be overridden using two special files:

- ``/etc/backup-data/<name>.include``
- ``/etc/backup-data/<name>.exclude``

Where ``name`` is the name of the backup.

Both files will override the list of included and excluded data set.
The accepted syntax is the same as reported in the paragraph above.

For example, given a backup named ``mybackup1`` create the following files:

- :file:`/etc/backup-data/mybackup1.include`
- :file:`/etc/backup-data/mybackup1.exclude`

Example
~~~~~~~

It's possible to configure a backup which includes only the mail and is scheduled each our.

1. Configure the new ``mymailbackup`` using the UI

2. Create a custom include containing only the mail directory: ::

     echo "/var/lib/nethserver/vmail" > /etc/backup-data/mymailbackup.include

3. Create an empty custom exclude file: ::

     touch /etc/backup-data/mymailbackup.exclude

4. Apply the configuration: ::

     signal-event nethserver-backup-data-save mymailbackup


.. warning:: Make sure not to leave empty lines inside edited files.

.. note:: This type of backup can't be used in case of disaster recovery.

Configuration backup
====================

Configuration backup is an automated task that runs every night at 00.15 and creates a new
archive, :file:`/var/lib/nethserver/backup/backup-config.tar.xz`, if the
configuration has changed during the previous 24 hours.

The list of installed modules is included in the backup archive. The
restore procedure can download and install the listed modules automatically.

In most cases it is not necessary to change the configuration backup. 
But it can be useful, for example, if you have a custom httpd configuration.
In this case you can add the file that contains the customization to the list of files to backup.

Inclusion
---------

If you wish to add a file or directory to configuration backup, add a line to the file :file:`/etc/backup-config.d/custom.include`.

For example, to backup :file:`/etc/httpd/conf.d/mycustom.conf` file, add this line: ::

  /etc/httpd/conf.d/mycustom.conf

Do not add big directories or files to the configuration backup.

Exclusion
---------

If you wish to exclude a file or directory from the configuration backup, add a line to the file :file:`/etc/backup-config.d/custom.exclude`.

.. warning::
   Make sure not to leave empty lines inside edited files.
   The syntax of the configuration backup supports only simple file and directory paths.



.. _data_restore:

Restore from command line
=========================

When the :ref:`selective_restore-section` web interface is not enough,
the restore can be done via command line.

All relevant files are saved under :file:`/var/lib/nethserver/` directory:

* Mails: :file:`/var/lib/nethserver/vmail/<user>`
* Shared folders: :file:`/var/lib/nethserver/ibay/<name>`
* User's home: :file:`/var/lib/nethserver/home/<user>`


To list data inside a backup, use: ::

  backup-data-list -b <name>

To restore all data in the original location, use: ::

  restore-data -b <name>

To restore a file or directory, use: ::

  restore-file -b <name> <position> <path>

Example, restore the version of a file from 15 days ago: ::

  restore-file -b <name> -t 15D /tmp "/var/lib/nethserver/ibay/test/myfile" 

The ``-t`` option allows to specify the number of days (15 in this scenario).
When used with snapshot-based engines, the ``-t`` option requires the name of the snapshot
to restore.


.. note:: When you are using *CIFS* to access the share, and the command doesn't work
          as expected, verify that user and password for the network share are correct.
          If user or password are wrong, you will find NT_STATUS_LOGON_FAILURE errors in
          :file:`/var/log/messages`.
          Also, you can use the :command:`backup-data-list` to check if the backup is accessible.



Formatting a local disk
=======================

Local disks can be formatted directly from the :ref:`web interface <backup_data_settings-section>`.
If something goes wrong, or a custom partitioning is required, please follow the below steps.

The best filesystem for SATA/USB backup disks is EXT3 or EXT4. FAT filesystem is supported but *not recommended*,
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

  sgdisk --zap-all /dev/sdc
  sgdisk --largest-new=1 /dev/sdc

* Create the filesystem on *sdc1* partition with a label named *backup* ::

    mkfs.ext4 -v /dev/sdc1 -L backup -E lazy_itable_init

* Detach and reconnect the USB disk:

  You can simulate it with the following command: ::

    blockdev --rereadpt /dev/sdc

* Now the *backup* label will be displayed inside the :guilabel:`Backup` page.


