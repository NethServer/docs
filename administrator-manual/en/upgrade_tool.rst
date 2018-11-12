.. _upgrade_tool_section:

===================
Upgrade tool (beta)
===================

The :guilabel:`Upgrade tool` module upgrades |product| from version 6 to version
7 with an automated procedure that acts in three steps:

1. **preparation**: downloads all required packages from the configured software
   repositories

2. **upgrade**: at next reboot runs the packages upgrade transaction, the
   upgrade tasks, then reboots automatically

3. **post-upgrade**: completes by fully re-configuring the system

Each step is described in the sections below. The time estimations depend on the
number of packages, internet connection, CPU and disks speed.

.. warning::

    Read carefully :ref:`upgrade_risks_section`

Preparation step
----------------

Estimated time: 1 hour

The (1) **preparation** step can be started from the :guilabel:`Upgrade tool`
page of the Server Manager.

During the preparation step the system is still operational as usual. The
package download runs in background. It requires some time, depending on the
available network bandwidth.

The available disk space is checked twice, before and after the preparation
step, to ensure the next steps do not run in short of disk space.

At the end of the download the web page asks to abort the procedure or continue
with the system reboot to the upgrade step.

Upgrade step
------------

Estimated time: 30 minutes

The (2) **upgrade** step starts at the next system reboot.  The upgrade
procedure boots the Linux kernel of version 7 by default. If the disk controller
is not compatible with it, the procedure fails at this point.

.. hint::

    It is possible to select the old kernel and boot the system in the previous
    state, actually aborting the upgrade

If the new kernel boots and mounts the disks correctly the system is
**disconnected from the network** and the packages upgrade starts. From this
point there is no way back. During the upgrade the system can be accessed from
the system console.

It takes some time to upgrade all the packages, depending on the system speed
and the number of the packages. At the end of the upgrade step the system is
automatically rebooted.

Post-upgrade step
-----------------

Estimated time: 15 minutes

The (3) **post-upgrade** step starts at the second reboot.

The basic system was completely upgraded by the previous step; the post-upgrade
step renames the network interfaces according to the new NIC naming rules and
re-configures the installed modules.

In this last step a fault can be recovered safely through the system console. At
the end of the post-upgrade step SSH, Server Manager and the other services are
available again.

.. _post-upgrade-checks:

Post-upgrade checklist
----------------------

.. warning::

    1. Some modules, like ownCloud, need to be upgraded or replaced manually.
       Refer to the Upgrade documentation of |product| 7

    2. Once the Server Manager is accessible again remember to refresh the
       browser cache with :kbd:`Ctrl + Shift + R` to fix display issues caused by the
       upgraded style sheets (CSS)

Upgrade completed check
=======================

To ensure the upgrade procedure has finished run ``systemd-analyze``. The output
should begin like ::

    Startup finished

Upgrade errors check
====================

To check if any error occurred, run ::

    grep -B 5 -E '(ERROR|FAILED)' /var/log/messages

Let's Encrypt certificate check
===============================

A Let's Encrypt certificate, if present, must be requested again from the
:guilabel:`Server certificate` page. Then set it as the default system
certificate from the same page. For more information, refer to the "Server
certificate"  manual page of |product| 7.

.. _upgrade_risks_section:

Upgrade risks and how to reduce them
------------------------------------

A major system version upgrade is a risky operation and must be planned
carefully.

- Ensure the system has enough free **disk space**. The procedure checks the
  free disk space, but it is always a good idea to check it early, even before
  installing the :guilabel:`Upgrade tool` module.

- Prepare a complete backup or snapshot of the whole system. A **power outage**
  or an **hardware fault** during the upgrade step, as long as an **unknown
  bug** in this procedure could compromise the system

- Consider the **system downtime** and how it impacts on the end-users

- Make a list of the modules that need to be configured, replaced, **upgraded
  manually** after the automated procedure completes. Refer to the Upgrade
  documentation of |product| 7

- During the upgrade any existing **custom template** is archived into
  ``/root/templates-custom.upgrade/``. It is recommended to check the existing
  customized templates before starting the upgrade procedure and decide if and
  how to restore them

- The system is **disconnected from the network** during the upgrade step and
  until the post-upgrade step completes. If any error occurs during those steps
  a direct **console access** is required.
