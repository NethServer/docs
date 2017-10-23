.. _installation-section:

.. index:: installation

=============
Installation
=============

.. index::
   pair: hardware; requirements

Minimum requirements
====================

Minimum requirements are:

* 64 bit CPU (x86_64)
* 1 GB of RAM
* 10 GB of disk space


.. hint:: We recommend to use at least 2 disks to setup a RAID 1.  The
          RAID software will ensure data integrity in case of a disk
          failure.

.. index::
   pair: hardware; compatibility

Hardware compatibility
----------------------

|product| is compatible with any hardware certified by Red Hat®
Enterprise Linux® (RHEL®), listed on `hardware.redhat.com
<http://hardware.redhat.com/>`__


Installation types
==================

|product| supports two installation modes. In short:

**Installing from ISO**

  * Download the ISO image
  * Prepare a DVD or USB stick
  * Follow the wizard

**Installing from YUM**

  * Install CentOS Minimal
  * Configure the network
  * Install from network

.. index::
   pair: installation; ISO

Installing from ISO
===================

.. warning:: The ISO installation will erase all existing data on
             hard drives!

Media creation
--------------

**Download the ISO file** from official site |download_site|.  The
downloaded ISO file can be used to **create a bootable media** such as
DVD or USB stick.  

USB stick
^^^^^^^^^

On a Linux machine, open the shell and execute: ::

  dd if=NethServer.iso of=/dev/sdc

Where `NethServer.iso` is the file name of the downloaded ISO and `/dev/sdc` is the
destination device corresponding to the USB key and 
not a partition (such as /dev/sdc1).

On a Windows machine, make sure to format the USB drive then unmount it.
Use one of the following tools to write the USB stick:

* `Etcher`_
* `Win32 Disk Imager`_
* `Rawrite32`_
* `dd for Windows`_

.. _`Etcher`: https://etcher.io/ 
.. _`Win32 Disk Imager`: http://sourceforge.net/projects/win32diskimager/ 
.. _`Rawrite32`: http://www.netbsd.org/~martin/rawrite32/ 
.. _`dd for Windows`: http://www.chrysocome.net/dd 

DVD
^^^

The creation of a bootable DVD is different from
writing files into USB stick, and it requires the use of a dedicated
function (e.g. *write* or *burn ISO image*).  Instructions on how to
create a bootable DVD from the ISO are easily available on the
Internet or in the documentation of your operating system.


Install modes
-------------

**Start the machine using the freshly backed media**.  If the machine
will not start from the DVD or USB stick, please refer to the documentation of
the motherboard BIOS. A typical problem is how boot device priority is
configured.  First boot device should be the DVD reader or USB stick.

On start a menu will display different types of installation:

|product| :ref:`interactive installation <installation-interactive>`

    Requires only keyboard and time zone settings. By default, tries to
    configure the network interfaces with DHCP and the first two available
    disks with RAID-1.

Other |product| installation methods

    *   :ref:`Unattended installation <installation-unattended>` --
        A set of default parameters is applied to the system with no human
        intervention.
    
    *   :ref:`Manual installation <installation-manual>` --
        This is the opposite of *unattended*. No defaults are applied: network,
        storage, time zone, keyboard... all settings must be provided
        explicitly.

Standard CentOS installations

    Use the standard CentOS installation procedure. You can then configure 
    |product| by following the :ref:`installation-centos` section.

Tools

    Start the system in *rescue* (recovery) mode, execute a memory
    test or start the hardware detection tool.

Boot from local drive

    Attempts to boot a system that is already installed on the hard
    disk.


At the end of the installation process you will be asked to reboot the
machine. Be sure to remove the installation media before restarting.

Optional boot parameters
^^^^^^^^^^^^^^^^^^^^^^^^

At the boot menu, you can add extra parameters by pressing :kbd:`TAB` and editing 
the kernel command line. This can be useful in *unattended* mode.

To disable raid, just add this option to the command line: ::

    raid=none

If you need to select installation hard drives, use: ::

    disks=sdx,sdy

.. index:: 
    pair: encryption; file system

To enable *file system encryption*, use: ::
    
    fspassword=s3cr3t

When enabling this option, all data written to the disk will be
encrypted using symmetric encryption.  In case of theft, an attacker
will not be able to read the data without the encryption key.

.. note :: You will need to enter the encryption password at every system boot!

Other available options (*unattended* mode only):

* ``keyboard``, keyboard layout, default is ``keyboard=us``
* ``timezone``, default is ``timezone=UTC``

.. _fallback-ip-configuration:

Fallback IP configuration
^^^^^^^^^^^^^^^^^^^^^^^^^

If no IP is assigned by DHCP or by other means, during the first system boot 
the following IP configuration is applied to the **first** network interface

* IP 192.168.1.1
* netmask 255.255.255.0

System administrator password
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

You are strongly advised to choose a secure password for the ``root`` user. 
A good password:

* is at least 8 characters long
* contains uppercase and lowercase letters
* contains symbols and numbers

The default password in *unattended* mode is ``Nethesis,1234``.

System language
^^^^^^^^^^^^^^^

The system language of |product| installations is *English (United States)*.
Additional languages can be installed later. See :ref:`Next steps <installation-next-steps>`.

.. _installation-manual:

.. _installation-interactive:

Interactive and Manual modes
----------------------------

The **interactive** mode allows you to make a few simple choices on the
system configuration.

Required choices are:

* Language
* Keyboard layout
* Root password

All other options are set to a reasonable default accordingly to current
hardware (see the :ref:`installation-unattended` section for details), but you
are free to edit any install configuration available.

On the other hand, the **manual** mode starts the installer with no default
settings at all.  Also the network and storage sections must be configured.

.. warning:: 
    
    Under the :guilabel:`Network > General` section, only the interfaces marked
    as :guilabel:`Automatically connect to this network when it is available`
    are enabled at boot in the installed system. For more info, refer to `RHEL 7
    installation guide`_.

.. _`RHEL 7 installation guide`: https://access.redhat.com/documentation/en-US/Red_Hat_Enterprise_Linux/7/html/Installation_Guide/sect-network-hostname-configuration-x86.html

.. _installation-unattended:

Unattended mode
---------------

The *unattended* mode requires no human intervention. After installation,
the system is rebooted and the following configuration is applied:

* Keyboard layout: ``us``
* Time zone: ``UTC``
* Default ``root`` password: ``Nethesis,1234``
* DHCP enabled on all network interfaces; if no DHCP lease is received the
  :ref:`fallback IP configuration <fallback-ip-configuration>` is applied
* if there are two or more disks, a RAID 1 will be created on
  first two disks and LVM volumes are created on it
* *swap* and *root* partitions are allocated automatically; 1GB is assigned to *boot*


.. index::
   pair: installation; CentOS
   pair: installation; VPS
   pair: installation; USB

.. _installation-centos:

Install on CentOS
=================

It is possible to install |product| on a fresh CentOS minimal installation using
a couple of commands to download the additional software packages. This
installation method is designed for virtual private servers (VPS) where CentOS
comes already installed by the VPS provider.

Enable |product| software repositories with this command: ::

  yum localinstall -y http://mirror.nethserver.org/nethserver/nethserver-release-7.rpm

To install the base system, run: ::

  nethserver-install

.. only:: nscom

    Alternatively, to install base system *and* additional modules, pass
    the name of the module as a parameter to the install script.  Example: ::

      nethserver-install nethserver-mail nethserver-nextcloud

.. only:: nsent

    .. _installation-enterprise:

    Enterprise promotion
    ====================

    To promote to the Enterprise version run the following command: ::
    
        yum localinstall http://update.nethesis.it/nethserver/7/nethserver-register.rpm

    Proceed with :ref:`registration <registration-section>` then run the following command: ::
        
        yum update @nethserver-iso

    If YUM reports problems with RPM dependencies, the system probably has installed RPMs from
    different CentOS release. In this case, please upgade to 7.4 (beta): ::

        yum install http://packages.nethserver.org/nethserver/7.4.1708/base/x86_64/Packages/nethserver-release-7-4.ns7.noarch.rpm
        yum install http://update.nethesis.it/nethserver/7.4.1708/nethserver-register.rpm
        /etc/cron.daily/00fixyumrepos


.. _installation-next-steps:

Next steps
==========

At the end of the installation procedure, :ref:`access the
server-manager <access-section>` to :ref:`install additional software
<package_manager-section>`.
