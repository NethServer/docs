.. _disaster-recovery-section:

Disaster recovery
=================

The system is restored in two phases: configuration first, then data.
Right after configuration restore, the system is ready to be used if the proper packages are installed.
When the machine is functional, a full data restore can be performed while the machine is already in production.
You can install additional packages before or after the restore.
For example, if the mail-server is installed, the system can send and receive mails.

Other restored configurations:

* Users and groups
* SSL certificates

.. warning:: Do not restore a configuration backup from an old minor version into a newer version.
   The backup should come from a |product| having the same operating system version of the new 
   installation, i.e., avoid restoring a configuration backup from a 7.4.1708 installation on a new 7.6.1810 system,
   as it may lead to unexpected results.

New Server Manager
------------------

Please, follow below steps:

1. Install the new machine (refer to :ref:`installation <installation-manual>` section), access the 
   new Server Manager and make sure the machine is able to access the internet and resolve public names correctly 

2.

  .. only:: nsent

       Activate NethServer Enterprise following the :ref:`registration <registration-section>` procedure

  .. only:: nscom

       If the machine has a Community subscription entitlement, please follow :ref:`subscription-section`,
       otherwise you can skip this step


3. Install all the available core updates from the :ref:`software-updates-section`

4. Access the :guilabel:`Backup` page and click on the :guilabel:`Restore` button under
   the **Configuration Backup** section, then upload the configuration backup
   or download it directly from an HTTP/S URL.

   For NethServer Enterprise, all cloud backups will be automatically downloaded and ready
   to be restored directly from the :guilabel:`From backup` field.
  
5. Map network interface names from the backup to the running system.
   This step is required only if :guilabel:`Restore network configuration` option is enabled.
   
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

If the :guilabel:`Restore network configuration` was not enabled, further steps
may be required to restore all applications. See :ref:`skip-network-restore-section` for more details.

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

     where ``name`` is the name of the data backup you want to restore from.


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

     where ``name`` is the name of the data backup you want to restore from.


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

The warning message points to a page that lists the network cards present in
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


.. _skip-network-restore-section:

Skip network restore
--------------------

Network configuration is restored by default, but sometimes it is necessary to restore an 
installation on a different hardware without migrating the network configuration.
This is a common scenario when moving a virtual machine from a VPS provider to another.

To disable the network restore, make sure to disable the :guilabel:`Restore network configuration` option from
the new Server Manager.

Since some application configurations depend on network interface names, not everything can be automatically restored.

DHCP
^^^^

DHCP servers on non-existing interfaces will be deleted.
If needed, please reconfigure the DHCP from the Server Manager.
See also :ref:`dhcp-section` for more general information.

Samba Active Directory
^^^^^^^^^^^^^^^^^^^^^^

Samba Active Directory requires a network bridge in the green zone for the local running container.
If the bridge already exists, the container will continue running after the restore.

If the bridge does not exist anymore, Samba Active Directory is stopped.
To enable it again:

- create the bridge, eg. ``br0``
- reconfigure the container from command line: ::

    config setprop nsdc bridge br0 status enabled
    signal-event nethserver-dc-save

More info about :ref:`ad-local-accounts-provider-section`.

Firewall
^^^^^^^^

At the end of restore the firewall will:

- delete all WAN providers
- delete all zones connected to non-existing network interface
- disable all rules using a non-existing zone or a non-existing role

The administrator can access the Server Manager to create missing zones and roles.
Finally, all previously disabled rules can be manually enabled again.

See :ref:`firewall_new-section`.

Web proxy
^^^^^^^^^

Web proxy priority rules using non-existing zones will be disabled.
Before re-enabling such rules, make sure the zones have been created.

More info on priority rules: :ref:`squid_rules-section`.

OpenVPN tunnels
^^^^^^^^^^^^^^^

OpenVPN tunnel servers contain a field named :guilabel:`Public address`.
If such field uses only public DNS names, no action is required.
Otherwise, insert the new public IP address inside the field and update tunnel clients accordingly.

See also OpenVPN :ref:`ovpn_tunnel-section`.

OpenVPN roadwarrior
^^^^^^^^^^^^^^^^^^^

OpenVPN roadwarrior server exposes a field named :guilabel:`Contact this server on public IP / host`.
If such field uses only public DNS names, no action is required.
Otherwise, insert the new public IP address inside the field and update roadwarrior clients accordingly.

See also OpenVPN :ref:`ovpn_roadwarrior-section`.

IPSec tunnels
^^^^^^^^^^^^^

Only IPSec tunnels configured with a dynamic red interface will be disabled.
Access the Server Manager, edit the disabled tunnel by selecting a new red interface and enable it again.

More info at :ref:`ipsec-section`.

Dedalo hotspot
^^^^^^^^^^^^^^

Dedalo hotspot will be disabled if the system doesn't have a network interface configured with the hotspot role.
If the Dedalo is disabled, just reconfigure following :ref:`dedalo-section` chapter.

ntopng
^^^^^^

ntopng must be reconfigured. Access the :guilabel:`Bandwidth monitor` page inside old Server Manager.
Then enable the service and select network interfaces to monitor.

See also :ref:`ntopng-section`.
