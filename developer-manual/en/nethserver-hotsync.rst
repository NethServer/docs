==================
nethserver-hotsync
==================

What is it ?
============

NethServer HotSync aims to reduce downtime in case of failure. Normally, when an hardware damage occurs, the time needed to restore service is:

* fix or buy another server: from 4h to 2 days
* install the OS: 30 minutes
* restore backup: from 10 minutes to 8 hours

In summary, users are able to start working again with data from the night before failure after a few hours or days. Using HotSync, time 1 and 3 become 0 and 2 becomes 5 minutes (time to activate the slave server). Users are able to start working again in few minutes, using data from a few minutes before the crash.

Requirements
============

Two server machines are needed:

* MASTER: active server on production
* SLAVE: warm backup server

How it works
============

**MASTER** machine is the currently production server and it makes a backup in the **SLAVE** machine every *"n"* minutes. When a crash occurs on the master, slave becomes active taking the same IP address of the master. Doing so the downtime is minimal, only the time to launch some commands on the SLAVE.

Installation
============

On both MASTER and SLAVE, install nethserver-hotsync: ::

    # yum install nethserver-hotsync

Configuration
=============

MASTER configuration: ::

    [root@master]# config setprop rsyncd password <PASSWORD>
    [root@master]# config setprop hotsync role master
    [root@master]# config setprop hotsync SlaveHost <SLAVE_IP>
    [root@master]# signal-event nethserver-hotsync-save

SLAVE configuration: ::

    [root@slave]# config setprop rsyncd password <PASSWORD>
    [root@slave]# config setprop hotsync role slave
    [root@slave]# config setprop hotsync MasterHost <MASTER_IP>
    [root@slave]# signal-event nethserver-hotsync-save

**The <PASSWORD> must be the same on both master and slave.**

If *MySQL* or *PostgreSQL* are installed, they will be synchronized by default. To disable databases synchronization: ::

    [root@master]# config setprop hotsync databases disabled
    [root@master]# signal-event nethserver-hotsync-save

How to restore
==============

The following procedure puts the SLAVE in production when the master has crashed.

1. switch off MASTER
2. if the SLAVE machine must run as network gateway, connect it to the router/modem with a network cable
3. following command changes the IP address and cuts off the network connection. If you are connected through an ssh console, launch the ``screen`` command ::

    [root@slave]# screen

4. on SLAVE launch command, and read carefully its output ::

    [root@slave]# hotsync-promote

5. go to Server Manager page ``Network`` and reassign roles to network interfaces if required
6. launch command ::

    [root@slave]# /sbin/e-smith/signal-event post-restore-data

7. if an USB backup is configured on MASTER, connect the backup HD to SLAVE

How to restore original server
==============================

To put again in production original crashed server:

1. configure it as SLAVE
2. synchronize it
3. switch off current MASTER
4. from bash execute: ::

       # hotsync-slave

5. restore configuration backup


How to synchronize custom paths
===============================

By default, all path of backup-data are synced. All paths in /etc/backup-data.d/\*.include are included and /etc/backup-data.d/\*.exclude are excluded. If you want to just add a custom path, create a custom include file for backup-data.

But if you want to do more complex operations, it is possible to customize HotSync adding all kind of data through the use of **plugins**. A plugin is a script that is launched during HotSync execution and is able to add path to include or exclude. The directory of plugins is `/etc/hotsync.d`. Executable files in this directory, are executed before the synchronization.

`INCLUDE_FILE` and `EXCLUDE_FILE` are the files that contain the list of paths to include and to exclude to/from HotSync. Those two variables are passed as arguments to the scripts of this directory when they are executed.

If you want to add files to the synchronization, append them to the INCLUDE_FILE. Append them to EXCLUDE_FILE to remove from the synchronization.

How to force synchronization from MASTER to SLAVE
=================================================

From MASTER bash launch the command: ::

    # hotsync

How to force packages installation on SLAVE
===========================================

*"hotsync-slave"* script extracts from MASTER configuration backup the
list of packages to install and install them. You can force the operation
executing bash command: ::

    # hotsync-slave

Components
==========

hotsync
-------

- is a shell script launched by cron every 15 minutes
- uses a lockfile to ensure that only one instance at a time is executed
- uses secure communication with rsync over stunnel
- creates a list of files to be included and another one to be excluded from rsync (using backup-data configuration and hotsync own logic)
- launch backup on MASTER
- launch an rsync that copy listed files from MASTER to SLAVE in a secure manner using stunnel
- if something fails, root is notified with an email
- you can check files that will be copied on the next synchronization using the command: ::
      
      hotsync --dry-run


hotsync-slave
-------------

Automatically executed on SLAVE every 60 minutes, extracts from MASTER
configuration backup the list of packages to install and install them.

Supported packages
==================

- nethserver-nextcloud
- nethserver-mysql
- nethserver-dnsmasq
- nethserver-squidguard
- nethserver-pulledpork
- nethserver-antivirus
- nethserver-samba-audit
- nethserver-freepbx > 14.0.3
- nethserver-webtop5 (z-push state is not synchronized)
- nethserver-collectd
- nethserver-cups
- nethserver-dc
- nethserver-letsencrypt
- nethserver-nextcloud
- nethserver-sssd
- nethserver-directory
- nethserver-ibays
- nethserver-mail-server

======================
Not supported packages
======================

- nethserver-evebox
- nethserver-getmail
- nethserver-ntopng


HotSync management using Cockpit Graphical Interface
====================================================

It can be possible to administrate HotSync from cockpit web graphical interface installing `nethserver-cockpit-hotsync`.


Configuration using Cockpit Web Gui
-----------------------------------

- On both MASTER and SLAVE browse to cockpit web gui -> "Applications" -> "NethServer Hotsync" -> "Settings"
- select the "role", then insert the requested data and click "Save" button

Restore using Cockpit Web Gui
-----------------------------

- From SLAVE browse to cockpit web gui -> "Applications" -> "NethServer Hotsync" -> "Settings"
- click on "Promote to Master" button
