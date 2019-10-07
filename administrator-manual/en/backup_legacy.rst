.. _legacy_backup-section:

=============
Legacy backup
=============

.. note:: A new backup module is available inside the new Server Manager. See :ref:`backup-section`.

|product| handles two kinds of backups: configuration backup and data backup.
See :ref:`backup-section` for more details.

Configuration backup
====================

From page :guilabel:`Backup (configuration)` the system
configuration can be saved, downloaded, uploaded and restored again.

The page allows the creation of a new on-demand backup by clicking on the :guilabel:`Create backup` button.
As default, the system retains the latest three configuration backups. The retention policy can be changed using the :guilabel:`Configure` button.

Data backup
===========

.. note:: 

   The old Server Manager can handle only a single backup.
   Such configuration can be managed also from the new Server Manager by editing the backup named ``backup-data``.


The data backup is performed using Duplicity engine and can be configured from :guilabel:`Backup (data)` page.
:index:`Duplicity` is the well-known default engine for |product|.
It has a good compression algorithm which will reduce storage usage on the destination.
Duplicity requires a full backup once a week, when the data set is very big the process
may take more than 24 hours to complete.
|product| doesn't implement backup encryption when using Duplicity.

Supported storage backends:

* CIFS: Windows shared folder, it's available on all NAS (Network Attached Storage). Use access credentials like: MyBindUser,domain=mydomain.com
* NFS: Linux shared folder, it's available on all NAS, usually faster than CIFS
* WebDAV: available on many NAS and remote servers (use a server with a valid SSL certificate as WebDAV target, otherwise the system will fail mounting the filesystem)
* USB: disk connected to a local USB/SATA port


The selective restore of files can be performed only form the new Server Manager. See :ref:`selective_restore-section`.
