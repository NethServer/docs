.. _backup-section:

======
Backup
======

The backup documentation is split the following chapters:

* :ref:`backup_data_settings-section`: general data backup settings
* :ref:`legacy_backup-section`: configuration from the old Server Manager
* :ref:`disaster-recovery-section`: how to recover a failed system
* :ref:`backup_customization-section`: advanced customization, best practices and command line tools

The system handles two kinds of backups:

* :index:`configuration backup`
* :index:`data backup`

.. rubric:: Configuration backup

Configuration backup contains only system configuration files and it's fully automatic. 
The purpose of this kind of backup is to quickly restore a machine in case of
:ref:`disaster recovery <disaster-recovery-section>`.
From page :guilabel:`Backup` the system configuration can be saved, downloaded, uploaded and restored again.
The retention of configuration backup can be changed by clicking on the :guilabel:`Configure` button.
Make sure to regularly download the configuration backup and save it to a secure place.

.. rubric:: Data backup

Data backup contains all data stored in the system (user's home directories, shared folders, emails, etc).
The administrator can schedule multiple data backups.

.. _backup_data_settings-section:

Settings
========

The data backup can be performed using different engines:

* **restic**: very fast, deduplication and encryption enabled by default, best suited for cloud storage
* **rsync**: fast and simple, partial deduplication, perfect for USB and SFTP storage
* **duplicity**: old and reliable, it uses compression and can execute full or incremental backups, no encryption,
  best choice for local network filesystem

Available storage backend:

* network filesystems for LAN: Windows File Share (CIFS), Network File System (NFS)
* remote network filesystems: WebDAV, SSH File Transfer Protocol (SFTP)
* local disk connected to a local USB/SATA port
* cloud providers: Amazon S3 (or any compatible S3 server)
* Backblaze `B2 <https://www.backblaze.com/b2/cloud-storage.html>`_

When using WebDAV as storage backend, make sure the server has a valid SSL certificate,
otherwise the system will fail mounting the filesystem

Scheduling
----------

The administrator can schedule multiple backups using different engines and destinations.
A valid policy could be creating a weekly backup to a local destination using duplicity, while scheduling
a daily backup to a cloud storage using restic.

When configuring backups, please bear in mind two golden rules:

* always use different destinations for each engine
* avoid scheduling concurrent backups, each backup should run when the previous one has been completed

To configure a new backup, access the :guilabel:`Backup` page and click on the :guilabel:`Schedule` button.
The web interface will start a configuration wizard which will automatically suggest the best engine based on the destination type.

.. _backup_basic_customization-section:

Data backup customization
-------------------------

Every time a new |product| module is installed, all directories containing data are added
to the data backup.

The list of paths included inside the backup are visible clicking the :guilabel:`Configure`
button from the :guilabel:`Backup` page.
From the same page, it's also possible to customize what is included or excluded.

When the :guilabel:`Include logs` option is enabled, all logs will be automatically added
to the backup set.

For further customization see :ref:`backup_customization-section`.

Notifications
-------------

At the end of the backup a mail notification can be sent to the system administrator or to
a list of custom email addresses.

Usually notifications are sent in case of backup failure. You can suppress all notifications
or enable them even for successful backup by accessing the :guilabel:`Notify on` field in the
final step of the backup configuration wizard.

Please refer to :ref:`settings-section` chapter if you need to tune global notifications
options such a SMTP rely.

.. _selective_restore-section:

Selective restore of files
==========================

*Restore data* application must be explicitly installed from the Software Center.
Please note that selective restore will be available only for backups executed after the
application installation.

First, make sure the backup destination is reachable (for example, the USB disk must be
connected), then access :guilabel:`Restore data` application.

Access the :guilabel:`Restore data` application, select the name of the backup and the execution date.
Then search a file or directory by entering the name inside the :guilabel:`Field or directory` field.
For better results, select the search mode from the :guilabel:`Choose mode` menu:
the search can be restricted only to mail folders, normal files from applications like Nextcloud.
If the :guilabel:`Advanced` mode is selected, you can use `regular expressions <https://en.wikipedia.org/wiki/Regular_expression>`_ inside the :guilabel:`Pattern` field.

Finally, select the files to restore and click the :guilabel:`Restore` button.

If the :guilabel:`Overwrite` option is checked, the restored files will overwrite the existing ones.
Otherwise the restored files will be created in the same path with date included in the name and ``.restore``, like `.restore-20190729-153318-myfile`.
