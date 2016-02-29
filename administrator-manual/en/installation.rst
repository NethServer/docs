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
* 8 GB of disk space


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
  * Prepare a CD / DVD
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


**Download the ISO file** from official site |download_site|.  The
downloaded ISO file can be used to **create a bootable media** such as
CD or DVD.  The creation of a bootable disk is different from
writing files into CD/DVD, and it requires the use of a dedicated
function (e.g. *write* or *burn ISO image*).  Instructions on how to
create a bootable CD/DVD from the ISO are easily available on the
Internet or in the documentation of your operating system.

**Start the machine using the freshly backed media**.  If the machine
will not start from the CD/DVD, please refer to the documentation of
the motherboard BIOS. A typical problem is how boot device priority is
configured.  First boot device should be the CD/DVD reader.

On start a menu will display different types of installation:

|product| interactive install

    It allows you to select the language, configure RAID support,
    network, and encrypted file system.  It will be described in depth
    in the next paragraph.

Other / Unattended |product| install

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
TAB and editing the boot loader command line.

To disable raid, just add this option to the command line: ::

    raid=none

If you need to select installation hard drives, use: ::

    disks=sdx,sdy

Other available options:

* lang: system language, default is en_US
* keyboard: keyboard layout, default is us
* timezone: default is UTC Greenwich
* fspassword: enable file system encryption with given password
  This option can be used even in Interactive Mode

.. _installation-interactive:

Interactive Mode
----------------

The interactive mode allows you to make a few simple choices on the
system configuration:

* Language 
* Software RAID
* Network configuration

Language
^^^^^^^^

Select the language in which you want to use the interactive mode.
Keyboard layout and time zone are changed accordingly and can be 
modified just after the first login to the web interface.

System language is always set to English.

Software RAID
^^^^^^^^^^^^^

RAID (Redundant Array of Independent Disks) allows you to combine all
the disks in order to achieve fault tolerance and an increase in
performance.

This screen is displayed when two or more disks were detected at
start.

Available levels:

* RAID 1: it creates an exact copy (mirror) of all the data on two or more disks.
  Minimum number of disks: 2

* RAID 5: it uses a subdivision of the data at the block level,
  distributing the parity data evenly across all disks.  Minimum
  number of disks: 3

Spare disk
~~~~~~~~~~

You can create a spare disk if disk number is greater than the minimum
required by the selected level RAID, A spare disk will be added to the
RAID in case a failure occurs.


System administrator password
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

You can change the ``root`` user's password inside the first
configuration wizard.

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

It is possible to choose a password for the encryption, otherwise the
system administrator password will be used.

.. note :: You will need to enter the password at every system boot.

.. warning:: Following characters are not supported inside the password:
   ``#``, ``=`` and ``$``.


Network interfaces
^^^^^^^^^^^^^^^^^^

Select the network interface that will be used to access the LAN.
This interface is also known as *green* interface.


Network configuration
^^^^^^^^^^^^^^^^^^^^^

Host and Domain Name (FQDN)

    Type the host name and domain in which the server will operate
    (e.g. :samp:`server.mycompany.com`).

    *Note:* Domain name can only contain letters, numbers and the
     dash.

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

DNS

    Type a valid DNS. Example: 8.8.8.8

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
is the recommended installation method if you have

* a virtual private server (VPS), or
* an USB stick.

For example, if you wish to install |product| |version|, just start
with a CentOS |version| on your system (many VPS providers offer
CentOS pre-installed virtual machines), and then execute below
commands to transform CentOS into |product|.

Enable specific YUM repositories with this command: ::

  yum localinstall -y http://mirror.nethserver.org/nethserver/nethserver-release-6.7.rpm

To install the base system, run: ::

  nethserver-install

Alternatively, to install base system *and* additional modules, pass
the name of the module as a parameter to the install script.  Example: ::

  nethserver-install nethserver-mail nethserver-nut

.. include:: installation_centos_end.inc

