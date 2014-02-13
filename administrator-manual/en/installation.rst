=============
Installation
=============

Minimum requirements
====================

Minimum requirements for NethServer are:

* 64bit CPU (x86_64)
* 1GB of RAM
* 8GB of disk space


We recommend to use at least 2 disks to setup a RAID 1. 
The RAID software will ensure data integrity in case of a disk failure.

Hardware compatibility
----------------------

NethServer is compatibile with all certificate hardware by 
Red Hat® Enterprise  Linux® (RHEL ®). See: `https://hardware.redhat.com/ <https://hardware.redhat.com/>`_


Installation types
==================

NethServer supports two installation modes. In short:

**Installing from ISO**

  * Download the ISO image, 
  * Prepare a CD / DVD or a bootable USB stick
  * Follow the wizard

**Installing from YUM**

  * Install CentOS Minimal
  * Configure the network
  * Install from network

Installing from ISO
====================

Download NethServer ISO file from official site
'ww.nethserver.org`, inside *Download*. section  

Downloaded ISO file can be used to create a
*Bootable media* such as a CD, a DVD, or a USB stick.
The creation of a bootable disk is different from writing
files into CD / DVD, and it requires the use of a dedicated function, 
usually present CD / DVD programs (eg *write* or *burn ISO image*).
nstructions on how to create a bootable CD / DVD from the ISO are easily
avaialble on the Internet or in the documentation of your system
operating system.


A similar procedured applies for bootable USB stick.
There are specific programs [#] _ which will convert downloaded ISO into bootable USB sticks.

In both cases, you can now start the machine using the freshly backed media.
If the machine will not start from the CD/DVD (or USB), please refer to the
documentation of the motherboard BIOS. A typical problem is
how boot device priority is configured.
First boot device should be the CD/DVD reader (or USB stick).

.. [#] For example, http://unetbootin.sourceforge.net/ 


On startup a menu will display different types of installation:

.. warning :: The installation will erase all existing data on hard drives!


NethServer interactive install
    It allows you to select the language, configure RAID support,
    network, and encrypted file system.  It will be described in depth in the next paragraph.

Other / Unattended NethServer install 
    This installation mode does not require any kind of humant intervention: a set of default parameters will applied to the system.

Standard CentOS installations
    Use the standard CentOS installation procedure.

Tools
    Start the system in *rescue* (recovery) mode, execute a memory test or start the hardware detection tool.

Boot from local drive
    Attempts to boot a system that is already installed on the hard disk.


At the end of the installation process you will be asked to 
reboot the machine. Be sure to remove the CD or
USB support before restarting.


Unattended mode
---------------

After installation, the system will be configured as follows:

* Credentials: root / Nethesis 1234
* Network: DHCP enabled on all interfaces
* Keyboard: us
* Time zone: Greenwich
* Language: en_US.UTF-8
* Disks: if there are two or more disks, a RAID1 will be created on first two disks

Install options
^^^^^^^^^^^^^^^

You can add extra paramaters to unattend installation by pressing TAB and editing the command line.

To disable raid, just add this option to the command line: ::

    raid=none

If you need to select installation hard dirves, use: ::

    disks=sdx,sdy

Other available options:

* lang: system language, default is en_US
* keyboard: keybord layou, default is us
* timezone: default is UTC Greenwich
* password: enable filesystem encryption with given password

Interactive Mode
----------------

The interactive mode allows you to make a few simple choices on the system configuration:

1. Language 
2. Keyboard layout
3. Time zone
4. Software RAID
5. System administrator password
6. Encrypted filesystem
7. Network interfaces
8. Network configuration

Language
^^^^^^^^

Select the language in which you want to use the interactive mode.
Selected language will be the default language of installed system. 
The system will also suggest default values for keyboard and time zone.


Keyboard layout
^^^^^^^^^^^^^^^

A keyboard can have different layout depending on the language for which it was made.
Leave the suggested value or enter a custom value.


Time zone
^^^^^^^^^

The choice of time zone allows you to configure the date and time of the system.
Leave the suggested value or enter a custom value.


Software RAID
^^^^^^^^^^^^^

RAID (Redundant Array of Independent Disks) allows you to combine all the disks
in order to achieve fault tolerance and an increase in performance.

This screen is displayed when two or more disks were detected at startup.

Available levels:

* RAID 1: it creates an exact copy (mirror) of all the data on two or more disks. 
  Minimum number of disks: 2

* RAID 5: it uses a subdivision of the data at the block level, distributing the parity data evenly across all disks.
  Minimum number of disks: 3

Spare disk
~~~~~~~~~~

You can create a spare disk if disk number is greater than the minimum required by the selected level RAID,
A spare disk will be added to the RAID in case a failure occurs.


System administrator password
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

You are strongly advised to set a custom administrator password.

A good password is:

* at least 8 characters long
* contain uppercase and lowercase letters
* contain symbols and numbers


Encrypted filesystem
^^^^^^^^^^^^^^^^^^^^

When enabling this option, all data written to the disk will be encrypted using symmetric encryption.
In case of theft, an attacker will not be able to read the data without 
the encryption key.

It's possible to choose a password for the encryption, otherwise the system administrator password will be used.

.. note :: You will need to enter the password at every system boot.


Network interfaces
^^^^^^^^^^^^^^^^^^

Select the network interface that will be used to access the LAN.
This interface is also known as *green* interface.


Network configuration
^^^^^^^^^^^^^^^^^^^^^

Host and Domain Name (FQDN)
    Type the host name and domain in which the server will operate (eg server.mycompany.com).

    *Note:* Domain name can only contain letters, numbers and the dash.

IP Address
    Type a private IP address (from RFC1918) to be assigned to the server;
    if you want to install it in an existing network,
    you must provide a unused IP address valid for that network (in
    general you can use the first or last host inside the network range. Eg:
    192.168.7.1 or 192.168.7.254).

Netmask
    Type the subnet mask of the network. You can safely leave the default value. 

Gateway
    Type the IP address of the gateway on which you are
    installing the server.

DNS
    Type a valid DNS. Example: 8.8.8.8

End of installation procedure
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

After parameters input, the procedure will start the installation.


Install on CentOS
=================

It's possible to install NethServer on a fresh CentOS install
using the command *yum* to download software packages.

For example, if you wishi to install NethServer 6.5, just start 
with a CentOS 6.5 on your system (many VPS providers
offer CentOS pre-installed virtual machines), and then execute below commands
to transform CentOS into NethServer. 

Enable NethServer repositories with this command:

::

  yum localinstall -y http://pulp.nethesis.it/nethserver/nethserver-release.rpm

To install the base system, run:

::

  nethserver-install

To install additional modules, pass the name of the module as a parameter to the install script.
Example for mail and ups modules:

::

  nethserver-install nethserver-mail nethserver-nut


At the end of the procedure the system is ready for use.




