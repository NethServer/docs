.. _hotsync-section:

=======
HotSync
=======

.. note::

  This package is not supported in |product| Enterprise

.. warning::

   HotSync should be considered a `beta release <https://en.wikipedia.org/wiki/Software_release_life_cycle#Beta>`_.
   Please test it on your environment before using in production.

.. warning::

   For a correct restore, it's suggested to configure HotSync on two identical servers or two servers with same network cards number, name and position. If you restore master on a not identical slave server you can encounter some problems and you'll have to fix it consulting troubleshooting section.


HotSync aims to reduce downtime in case of failure, syncing your |product| with another one, that will be manually activated in case of master server failure.

Normally, when a hardware damage occurs, the time needed to restore service is:

1. fix/buy another server: from 4h to 2 days
2. install OS: 30 minutes
3. restore backup: from 10 minutes to 8 hours

In summary, users are able to start working again with data from the night before failure after a few hours/days. Using HotSync, time 1 and 3 are 0, 2 is 5 minutes (time to activate spare server). Users are able to start working again in few minutes, using data from a few minutes before the crash.


By default all data included in backup are synchronized every 15 minutes. MariaDB databases are synchronized too, unless databases synchronization isn't disabled.
Applications that use PostgreSQL are synchronized (Mattermost, Webtop5) unless databases synchronization isn't disabled.


Terminology
===========

- MASTER is the production system SLAVE is the spare server
- SLAVE is switched on, with an IP address different than MASTER
- Every 15 minutes, MASTER makes a backup on SLAVE
- If something went wrong, an email is sent to root (admin if mail server is installed)
- SLAVE check updates and makes some system operations every 60 minutes


Installation
============

.. only:: nscom

    Install nethserver-hotsync on both MASTER and SLAVE from Software Center or execute from command line: ::
    
      yum install -y nethserver-hotsync --enablerepo=nethforge

.. only:: nsent

    Install nethserver-hotsync on both MASTER and SLAVE.

    To install the module on MASTER execute from command line: ::

      yum install -y nethserver-hotsync --enablerepo=nethforge

    To install the module on SLAVE execute from command line: ::

      yum install -y nethserver-hotsync --enablerepo=nethforge --disablerepo=nethesis-*,nh-*



Configuration
=============

You can configure HotSync from Cockpit interface: access this from Master and Slave, select role and fill required fields with password and IP.
The ``<PASSWORD>`` must be the same on master and slave.

You can also configure HotSync from command line using these commands:

Master
------

::

    [root@master]# config setprop rsyncd password <PASSWORD>
    [root@master]# config setprop hotsync role master
    [root@master]# config setprop hotsync SlaveHost <SLAVE_IP>
    [root@master]# signal-event nethserver-hotsync-save


Slave
-----

::

    [root@slave]# config setprop rsyncd password <PASSWORD>
    [root@slave]# config setprop hotsync role slave
    [root@slave]# config setprop hotsync MasterHost <MASTER_IP>
    [root@slave]# signal-event nethserver-hotsync-save


If mysql or postgresql are installed, they will be synchronized by default. You can disable databases sync from Master Cockpit interface or from command line on master machine with this command:

::

    [root@master]# config setprop hotsync databases disabled
    [root@master]# signal-event nethserver-hotsync-save


Enabling/Disabling
------------------

HotSync is enabled by default. To disable it uncheck the checkbox into HotSync Cockpit GUI or use this command:

::

    [root@slave]# config setprop hotsync status disabled
    [root@slave]# signal-event nethserver-hotsync-save


and to re-enable it re-check the checkbox on interface or use CLI:

::

    [root@slave]# config setprop hotsync status enabled
    [root@slave]# signal-event nethserver-hotsync-save


.. note::

   After HotSync is configured, it's a good practice to launch ``hotsync`` command on master host and ``hotsync-slave`` command on slave host after master has properly syncronized with slave.
   You can force these commands also from Cockpit GUI and check ``/var/log/messages`` logs. It's suggested to launch first command directly from CLI to check if all is properly configured.



Restore: put SLAVE in production
================================

The following procedure puts the SLAVE in production when the master has crashed.

1. Switch off MASTER.

2. If the SLAVE machine must run as network gateway, connect it to the router/modem with a network cable.

3. On SLAVE, if you are connected through an ssh console, launch the ``screen`` command, to make your session survive to network outages::

    [root@slave]# screen

   It's suggested to execute following procedure directly from the console and not via ssh.

4. on SLAVE launch the following command, and read carefully its output ::

    [root@slave]# hotsync-promote

   If no internet connection is detected (e.g. you are restoring a firewall on a machine that was passing through crashed master for internet connection), the scripts will purpose you some options ::
   
    1. Restore master network configuration (IMPORTANT: use this option only if two servers are identical - NIC number, names and positions must be identical)
    2. Fix network configuration from Cockpit GUI (if you are restoring on different hardware)
    3. Continue without internet: assign correct roles before proceed with this option. Some events could fails (not recommended)
   
   else restore will start automatically. If you are restore on different hardware you could encounter DC errors.
   
.. warning::

    If you are restoring on identical hardware choose option 1 and network configuration will be overwritten, else choose option 2. It's not recommended to start promote procedure without internet.
    If you are restoring on a different hardware and you've choosed option 2, you can encounter DC errors. Read troubleshooting section.

5. If necessary go to Server Manager or Cockpit GUI, in page ``Network`` and reassign roles to network interfaces as master one. Remember also to recreate bridge if you have configured DC. In case of DC errors consult troubleshooting section before proceed with network restore.

6. After all is restored launch the command ::

    [root@slave]# /sbin/e-smith/signal-event post-restore-data

7. Ypdate the system to the latest packages version ::

    [root@slave]# yum clean all && yum -y update

8. If an USB backup is configured on MASTER, connect the backup HD to SLAVE


Troubleshooting
===============

After restore on different hardware DC is not working
-----------------------------------------------------

Console could reports some errors like these ::

    [ERROR] /usr/libexec/nethserver/sambads: failed to add service primaries to system keytab
    Action: /etc/e-smith/events/nethserver-mail-server-update/S50nethserver-sssd-initkeytabs FAILED
    
To solve this, restore network configuration as master (including bridges) and then launch ::

    /sbin/e-smith/signal-event nethserver-dc-save
    /sbin/e-smith/signal-event nethserver-sssd-save
    

After restore permissions on ibays are not correct
--------------------------------------------------

Restore permissions from Cockpit GUI, under File Server, open shared folder menu and click on ``Restore permissions``.


After network restore server is unreachable
-------------------------------------------

If you cannot reach server after a network reconfiguration, check configuration and, if it's correct, try launching this commands ::

    /sbin/e-smith/signal-event interface-update
    /sbin/e-smith/signal-event nethserver-firewall-base-update
    
If you cannot reach the server yet, use ``network-recovery`` tool.


Some check after restore
------------------------

After you've solved issues of configuration restore you should make some checks:
- configuration is restored properly
- all enabled services are working
- applications interfaces (e.g. freepbx, webtop) are working
- file server (if installed) is working and users can log into shared folders
- email server is working and users can send and receive emails
- asterisk is working and users can make calls

After all is working fine, reboot the system and check all services start and all working as expected.


Supported packages
==================

* nethserver-antivirus
* nethserver-collectd
* nethserver-cups
* nethserver-dc
* nethserver-directory
* nethserver-dnsmasq
* nethserver-freepbx > 14.0.3
* nethserver-ibays
* nethserver-letsencrypt
* nethserver-mail-server
* nethserver-mysql
* nethserver-nextcloud
* nethserver-pulledpork
* nethserver-samba-audit
* nethserver-squidguard
* nethserver-sssd
* nethserver-webtop5 (z-push state is not synchronized)

.. warning::

   To avoid errors on the slave host, do not make any changes to the modules from the Cockpit GUI except the HotSync module.
