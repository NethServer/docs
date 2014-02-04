============
Installation
============

CD installation
===============

NethServer installation CD is a simple CentOS with some extras packages and a small kickstart file.

* Download the ISO and check the integrity using MD5
* Write the ISO into a CD (or DVD) and boot the server using the burned media
* Installation is totally unattended and will erase all existing data
* At first boot, follow the istruction on the screen to configure the system
* Access the web interface using a browser at: https://<your_ip>:980 login: admin, password: <your_password>

ATTENTION: the CD installation will ERASE ALL data from the hard drive.

Default options
---------------
After installation the bootstrap console will start on tty1, but if you need to access the system, these are the defaults:

* Credentials: root/Nethesis,1234
* Network: DHCP on all interfaces
* Keyboard: it
* Timezone: Europe/Rome (UTC)
* Language: en_US.UTF-8
* Disks: if two or more disks are found, create a raid1 on the first two disks

Installation options
---------------------
To disable raid, just add this option to the command line: ::
    raid=none

If you need to select installation hard dirves, use: ::
    disks=sdx,sdy

Other options:

* lang: default is en_US
* keyboard: default is us
* timezone: default is UTC Greenwich
* password: crypt root filesystem with given password


YUM installation
================

It is possibile to install NethServer on a running CentOS.
On a fresh CentOS 6.4 minimal system configure hostname, domain and networking

Install NethServer configuration for yum repositories: ::

    yum localinstall http://pulp.nethesis.it/nethserver/nethserver-release.rpm

Import GPG keys: ::

    rpm --import /etc/pki/rpm-gpg/*

Install NethServer basic packages: ::

    yum --disablerepo=* --enablerepo=nethserver-base,nethserver-updates,centos-base,centos-updates --releasever=6.4 install @nethserver-iso

Activate first-boot event and restart the system: ::

    touch /var/spool/first-boot && reboot

After reboot, follow the istruction on the screen to configure the system
Access the web interface using a browser at: https://<your_ip>:980 login: admin, password: <your_password>
