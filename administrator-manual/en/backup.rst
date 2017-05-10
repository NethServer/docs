.. _backup-section:

======
Backup
======

:index:`Backup` is the only way to restore a machine when disasters occur.
The system handles two kinds of backup:

* :index:`configuration backup`
* :index:`data backup`

Configuration backup contains only system configuration files. 
It's scheduled to be executed every night and it will create a new archive, :file:`/var/lib/nethserver/backup/backup-config.tar.xz`, only if any file is changed in the last 24 hours.
The configuration backup also saves a list of installed modules. All modules will be reinstalled during the configuration restore process.
The purpose of this kind of backup is to quickly restore a machine in case of disaster recovery. 
When the machine is functional, a full data restore can be done even if the machine is already in production.

Data backup is enabled installing "backup" module and contains all data like user's home directories and mails. It runs every night and can be full or incremental on a weekly basis. 
This backup also contains the archive of the configuration backup.

Data backup can be saved on different destinations:

* USB: disk connected to a local USB port (See: :ref:`backup_usb_disk-section`)
* CIFS: Windows shared folder, it's available on all NAS (Network Attached Storage)
* NFS: Linux shared folder, it's available on all NAS, usually faster than CIFS
* WebDAV: available on many NAS and remote servers (Use a server with a valid SSL certificate as webDAV target, otherwise the system will fail mounting the filesystem)

The backup status can be notified to the system administrator or to an external mail address.

.. note:: The destination directory is based on the server host name: in case of
   FQDN change, the administrator should take care to copy backup data from
   the old directory to the new one.

Data restore
============

Make sure that backup destination is reachable (for example, USB disk must be connected).

Command line
------------

Listing files
^^^^^^^^^^^^^

It's possible to list all files inside the last backup using this command: ::

 backup-data-list

The command can take some times depending on the backup size.

File and directory
^^^^^^^^^^^^^^^^^^

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

.. note:: When you are using *CIFS* to access the share, and the command doesn't work
          as expected, verify that user and password for the network share are correct.
          If user or password are wrong, you will find NT_STATUS_LOGON_FAILURE errors in
          :file:`/var/log/messages`.
          Also, you can use the :command:`backup-data-list` to check if the backup is accessible.

Graphic interface
-----------------

In the :menuselection:`Restore files` menu section it is possible to search, select and restore
one or more directories from backup, navigating the graphical tree with all paths included in the backup.

By default, last backup tree is shown. If you want to restore a file from a previous backup, select the backup date from *"Backup File"* selector.

There are two options to restore:

* Restore files in the original path, the current files in the filesystem are overwritten by the restored files from backup.
* Restore files in original path but the restored files from backup are moved on a new directory (the files are not overwritten) in this path: ::

  /complete/path/of/file_YYYY-MM-DD (YYYY-MM-DD is the date of restore)

To use the search field, simply insert at least 3 chars and the searching starts automatically, highlighting the matched directories

It is possible to restore the directories by clicking on **Restore** button.

.. note:: Multiple selection can be done with Ctrl key pressed.

.. _disaster-recovery-section:

Disaster recovery
=================

The system is restored in two phases: configuration first, then data. 
Right after configuration restore, the system is ready to be used if proper packages are installed. 
You can install additional packages before or after restore.
For example, if mail-server is installed, the system can send and receive mail.

Other restored configurations:

* Users and groups
* SSL certificates

.. note:: The root/admin password is not restored.

Steps to be executed:

1. Install the new machine with the same host name as the old one
2. Configure a data backup, so the system can retrieve saved data and configuration
3. Restore the configuration backup from page :guilabel:`Backup
   (configuration) > Restore` in Server Manager, or executing:
   :command:`restore-config`
4. If a warning message requires it, reconfigure the network roles assignment. See :ref:`restore-roles-section` below.
5. Verify the system is functional
6. Restore data backup executing: :command:`restore-data`


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

If the missing role is ``green`` an interactive procedure asks to fix
the configuration at boot-time, to ensure a minimal network
connectivity and login again on the Server Manager.

.. _backup_config_rpms:

Restore installed modules
-------------------------

By default the process of configuration restore will also restore all previously installed modules.

To skip the automatic installation, execute the command with the
``--no-reinstall`` argument: ::

    restore-config --no-reinstall

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

Exclusion
---------

If you wish to exclude a file or directory from data backup, add a line to the file :file:`/etc/backup-data.d/custom.exclude`.

For example, to exclude all directories called *Download*, add this line: ::

  **Download**

To exclude a mail directory called *test*, add this line: ::

  /var/lib/nethserver/vmail/test/ 


Same syntax applies to configuration backup. Modification should be done inside the file :file:`/etc/backup-config.d/custom.exclude`.


.. note:: Make sure not to leave empty lines inside edited files.


Configuration backup customization
==================================

In most cases it is not necessary to change the configuration backup. 
But it can be useful, for example, if you have a custom httpd configuration.
In this case you can add the file that contains the customization to the list of files to backup.

Inclusion
---------

If you wish to add a file or directory to configuration backup, add a line to the file :file:`/etc/backup-config.d/custom.include`.

For example, to backup :file:`/etc/httpd/conf.d/mycustom.conf` file , add this line: ::

  /etc/httpd/conf.d/mycustom.conf

Do not add big directories or files to configuration backup.

Exclusion
---------

If you wish to exclude a file or directory from configuration backup, add a line to the file :file:`/etc/backup-config.d/custom.exclude`.

.. note:: 
   Make sure not to leave empty lines inside edited files.
   The syntax of the configuration backup supports only simple file and directory paths.

.. _backup_usb_disk-section:

USB disk configuration
======================

The best filesystem for USB backup disks is EXT3. FAT filesystem is supported but *not recommended*,
while NTFS is **not supported**.

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

* Create the filesystem on *sdc1* partition with a label named *backup*: ::

    mke2fs -v -T largefile4 -j /dev/sdc1 -L backup

* Detach and reconnect the USB disk:

  You can simulate it with the following command: ::

    blockdev --rereadpt /dev/sdc

* Now the *backup* label will be displayed inside the :guilabel:`Backup (data)` page.

