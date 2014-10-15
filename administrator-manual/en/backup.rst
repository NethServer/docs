======
Backup
======

:index:`Backup` is the only way to restore a machine when disasters occur.
The system handles two kind of backup:

* :index:`configuration backup`
* :index:`data backup`

Configuration backup contains only system configuration files. 
It's scheduled to be executed every night and it will create a new archive, :file:`/var/lib/nethserver/backup/backup-config.tar.xz`, only if any file is changed in the last 24 hours. 
The purpose of this kind of backup is to quickly restore a machine in case of disaster recovery. 
When the machine is functional, a full data restore can be done even if the machine is already in production.

Data backup is enabled installing "backup" module and contains all data like user's home directories and mails. It runs every night and can be full or incremental on a weekly basis. 
This backup also contains the archive of the configuration backup.

Data backup can be saved on three different destinations:

* USB: disk connected to an USB port, it's useful but limited by USB bus speed
* CIFS: Windows shared folder, it's available on all NAS
* NFS: Linux shared folder, it's available on all NAS, usually faster than CIFS

The backup status can be notified to the system administrator or to an external mail address.

Data restore
============

Make sure that backup destination is reachable (for example, USB disk must be connected).

.. note:: For now only restore form command line is available.

Listing files
--------------

It's possible to list all file present inside the last backup using this command: ::

 backup-data-list

The command can take some times depending on the backup size.

File and directory
------------------

All relevant files are saved under :file:`/var/lib/nethserver/` directory:

* Mails: :file:`/var/lib/nethserver/vmail/<user>`
* Shared folders: :file:`/var/lib/nethserver/ibay/<name>`
* User's home: :file:`/var/lib/nethserver/home/<user>`

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


Disaster recovery
=================

The system is restored in two phases: first configuration, then data. 
Right after configuration restore, the system is ready to be used if proper packages are installed. 
You can install additional packages before or after restore.
For example, if mail-server is installed, the system can send and receive mail (even sieve filters are already in place).

Other restored configurations:

* Users and groups, including old root/admin password
* SSL certificates


Steps to be executed:

1. Install the new machine with the same host name as the old one
2. Configure a data backup, so the system can retrieve saved data and configuration
3. Install additional packages (optional)
4. Restore configuration backup executing: :command:`restore-config` or using the web interface
5. If the old machine was the network gateway, remember to reinstall firewall module
6. Reconfigure network from web interface
7. Verify the system is functional
8. Restore data backup executing: :command:`restore-data`

.. _backup_customization-section:

Data backup customization
=========================

If additional software is installed, the administrator can edit
the list of files and directories included (or excluded).

Inclusion
---------

If you wish to add a file or directory to data backup, add a line to the file :file:`/etc/backup-data.d/custom.include`.

For example, to backup a software installed inside :file:`/opt` directory, add this line: ::

  /opt/mysoftware

If you wish to add a file or directory to configuration backup, add a line to the :file:`/etc/backup-config.d/custom.include`.
Do not add big directories or files to configuration backup.

Exclusion
---------

If you wish to  exclude a file or directory from data backup, add a line to the file :file:`/etc/backup-data.d/custom.exclude`.

For example, to exclude all directories called *Download*, add this line: ::

  **Download**

To exclude a mail directory called *test*, add this line: ::

  /var/lib/nethserver/vmail/test/ 


Same syntax applies to configuration backup. Modification should be done inside the file :file:`/etc/backup-config.d/custom.exclude`.


.. note:: Make sure to not leave empty lines inside edited files.


Configuration backup customization
==================================

In most cases it is not necessary to change the configuration backup. 
But it can be useful, for example, if you have installed a custom SSL certificate. 
In this case you can add the file that contains the certificate to the list of backuped files.

Inclusion
---------

If you wish to add a file or directory to configuration backup, add a line to the file :file:`/etc/backup-config.d/custom.include`.

For example, to backup :file:`/etc/pki/mycert.pem` file , add this line: ::

  /etc/pki/mycert.pem

Do not add big directories or files to configuration backup.

Exclusion
---------

If you wish to  exclude a file or directory from configuration backup, add a line to the file :file:`/etc/backup-config.d/custom.exclude`.

.. note:: 
   Make sure to not leave empty lines inside edited files.
   The syntax of the configuration backup supports only simple file and directory paths.
