.. _disaster-recovery-section:

Disaster recovery
=================

The system is restored in two phases: configuration first, then data.
Right after configuration restore, the system is ready to be used if the proper packages are installed.
When the machine is functional, a full data restore can performed while the machine is already in production.
You can install additional packages before or after the restore.
For example, if the mail-server is installed, the system can send and receive mails.

Other restored configurations:

* Users and groups
* SSL certificates

.. warning:: Do not restore a configuration backup from an old minor version into a newer version.
   The backup should come from a |product| having the same operating system version of the new 
   installation, i.e., avoid restoring a configuration backup from a 7.4.1708 installation on a new 7.6.1810 system,
   as it may lead to unexpected results.

New Server Manger
-----------------

Please, follow below steps:

1. Install the new machine (refer to :ref:`installation <installation-manual>` section), access the 
   new Server Manager and make sure the machine is able to access the internet and resolve public names correctly 

2. If the machine has an Enterprise entitlement, please follow :ref:`registration-section`,
   if the machine has a Community subscription entitlement, please follow :ref:`subscription-section`.
   Otherwise you can skip this step.

3. Install all the available core updates from the :ref:`software-updates-section`

4. Access the :guilabel:`Backup` page and click on the :guilabel:`Restore` button under
   the **Configuration Backup** section, then upload the configuration backup
   or download it directly from an HTTP/S URL.

   For |product| Enterprise, all cloud backups will be automatically downloaded and ready
   to be restored directly from the :guilabel:`From backup` field.
  
5. Map network interface names from the backup to the running system.
   
6. Click the :guilabel:`Restore` to start the restore process.

   .. note::

      If you're connected to a network interface that will change the IP address during the restore,
      you will be disconnected from the Server Manager and you will need to login again using the
      new IP address.

7. Verify the system is functional and then access the :guilabel:`Backup` page.
   To restore all files, click on :guilabel:`Restore` button under the **Data Backup** section,
   select the name of the backup and click the :guilabel:`Restore` button.

   Please bear in mind that the restore process can last from minutes to hours depending
   on the storage backend speed.


Old Server Manager
------------------

Please, follow below steps:

.. only:: nscom

  1. Install the new machine (refer to :ref:`installation <installation-manual>` section), access the 
     Server Manager and follow the :ref:`first configuration wizard <first-configuration-wizard-section>` 
     procedure to complete the basic server configuration

  2. Ensure that |product| is able to access the internet and resolve public names correctly

  3. Install all the available core updates in the :ref:`Software Center <software-updates-section>`

  4. Restore the configuration backup using the :guilabel:`Backup (configuration)` panel

  5. If a warning message requires it, reconfigure the network roles assignment.
     See :ref:`restore-roles-section` below.

  6. Verify the system is functional

  7. Restore data backup executing on the console ::

      restore-data -b <name>


.. only:: nsent

  1. Install the new machine (refer to :ref:`installation <installation-manual>` section), access the 
     Server Manager and follow the :ref:`first configuration wizard <first-configuration-wizard-section>` 
     procedure to complete the basic server configuration

  2. Ensure that |product| is able to access the internet and resolve public names correctly

  3. Activate |product| following the :ref:`registration <registration-section>` procedure

  4. Install all the available core updates in the :ref:`Software Center <software-updates-section>`

  5. Restore the configuration backup using the :guilabel:`Backup (configuration)` panel which allows
     to use cloud backups or local archives

  6. If a warning message requires it, reconfigure the network roles assignment.
     See :ref:`restore-roles-section` below.

  7. Verify the system is functional

  8. Restore data backup executing on the console ::

      restore-data -b <name>


Please note that the disaster recovery should be always performed from a local media (eg. NFS or USB) to speed up the process.

.. note:: The root/admin password is not restored.

.. _restore-roles-section:
   
Restore network roles 
^^^^^^^^^^^^^^^^^^^^^

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


