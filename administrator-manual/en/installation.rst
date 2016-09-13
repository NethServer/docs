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

* `Rufus`_
* `Fedora LiveUSB Creator`_
* `Win32 Disk Imager`_
* `Rawrite32`_
* `dd for Windows`_

.. _`Rufus`: https://rufus.akeo.ie/
.. _`Fedora LiveUSB Creator`: https://fedorahosted.org/liveusb-creator/
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

|product| interactive installation

    It allows you to select the language, configure RAID support,
    network, and encrypted file system.  It will be described in depth
    in the next paragraph.


|product| unattended installation

    This installation mode does not require any kind of human
    intervention: a set of default parameters will be applied to the
    system.

Standard CentOS installations

    Use the standard CentOS installation procedure.

Tools

    Start the system in *rescue* (recovery) mode, execute a memory
    test or start the hardware detection tool.

Boot from local drive

    Attempts to boot a system that is already installed on the hard
    disk.


At the end of the installation process you will be asked to reboot the
machine. Be sure to remove the installation media before restarting.

.. _installation-unattended:

Unattended mode
---------------

After installation, the system will be configured as follows:

* User name: :samp:`root`
* Default password: :samp:`Nethesis,1234`
* Network: DHCP enabled on all interfaces
* Keyboard: |ks_keyboard|
* Time zone: |ks_timezone|
* Language: English
* Disks: if there are two or more disks, a RAID 1 will be created on
  first two disks

Install options
^^^^^^^^^^^^^^^

You can add extra parameters to unattended installation by pressing
:kbd:`TAB` and editing the boot loader command line.

To disable raid, just add this option to the command line: ::

    raid=none

If you need to select installation hard drives, use: ::

    disks=sdx,sdy

Other available options:

* lang: system language, default is :samp:`en_US`
* keyboard: keyboard layout, default is :samp:`us`
* timezone: default is :samp:`UTC Greenwich`
* fspassword: enable file system encryption with given password
  This option can be used even in Interactive Mode

.. _installation-interactive:

Interactive Mode
----------------

The interactive mode allows you to make a few simple choices on the
system configuration.

Required choices are:

* Language
* Keyboard layout
* Root password

All other options are set to a reasonable default accordingly to current hardware,
but you're free to edit any install configuration available.


Software RAID
^^^^^^^^^^^^^

RAID (Redundant Array of Independent Disks) allows you to combine all
the disks in order to achieve fault tolerance and an increase in
performance.

This screen is displayed when two or more disks were detected at
start.

Most used levels are:

* RAID 1: it creates an exact copy (mirror) of all the data on two or more disks.
  Minimum number of disks: 2

* RAID 5: it uses a subdivision of the data at the block level,
  distributing the parity data evenly across all disks.  Minimum
  number of disks: 3


System administrator password
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

You're strongly advised too choose a secure password for the ``root`` user.

A good password is:

* at least 8 characters long
* contain uppercase and lowercase letters
* contain symbols and numbers

Default password is :samp:`Nethesis,1234`.

Encrypted file system
^^^^^^^^^^^^^^^^^^^^^

When enabling this option, all data written to the disk will be
encrypted using symmetric encryption.  In case of theft, an attacker
will not be able to read the data without the encryption key.

.. note :: You will need to enter the encryption password at every system boot.


Network configuration
^^^^^^^^^^^^^^^^^^^^^

As default, all network interfaces are configure with DHCP.
Please, read the following notes before customizing network configuration.

Host and Domain Name (FQDN)

    Type the host name and domain in which the server will operate
    (e.g. :samp:`server.mycompany.com`).
    Domain name should only contain letters, numbers and the dash.

IP Address

    Type a private IP address (from RFC 1918) to be assigned to the
    server; if you want to install it in an existing network, you must
    provide a unused IP address valid for that network (in general you
    can use the first or last host inside the network range, e.g.
    192.168.7.1 or 192.168.7.254).

Netmask

    Type the subnet mask of the network. You can safely leave the
    default value.

Gateway

    Type the IP address of the gateway on which you are installing the
    server.


End of installation procedure
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

After parameters input, the procedure will start the installation.

.. include:: installation_interactive_end.inc


.. index::
   pair: installation; CentOS
   pair: installation; VPS
   pair: installation; USB

Install on CentOS
=================

It is possible to install |product| on a fresh CentOS installation
using the :program:`yum` command to download software packages. This
is the recommended installation method if you have:

* a virtual private server (VPS), or
* an USB stick.

For example, if you wish to install |product| |version|, just start
with a CentOS |version| on your system (many VPS providers offer
CentOS pre-installed virtual machines), and then execute below
commands to transform CentOS into |product|.

Enable specific YUM repositories with this command: ::

  yum localinstall -y http://mirror.nethserver.org/nethserver/nethserver-release-7.rpm

To install the base system, run: ::

  nethserver-install

Alternatively, to install base system *and* additional modules, pass
the name of the module as a parameter to the install script.  Example: ::

  nethserver-install nethserver-mail nethserver-nextcloud

.. include:: installation_centos_end.inc
