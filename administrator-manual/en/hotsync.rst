.. _hotsync-section:

=======
HotSync
=======

HotSync aims to reduce downtime in case of failure, syncing your |product| with another one, that will be manually activated in case of master server failure.

Normally, when a hardware damage occurs, the time needed to restore service is:

1. fix/buy another server: from 4h to 2 days
2. install OS: 30 minutes
3. restore backup: from 10 minutes to 8 hours

In summary, users are able to start working again with data from the night before failure after a few hours/days. Using hotsync, time 1 and 3 are 0, 2 is 5 minutes (time to activate spare server). Users are able to start working again in few minutes, using data from a few minutes before the crash.


By default all data included in backup are synchronized every 15 minutes. MariaDB databases are synchronized too, unless databases synchronization isn't disabled.
Applications that use PostgreSQL are synchronized (Mattermost, Webtop5) unless databases synchronization isn't disabled.


Terminology
===========

- MASTER is the production system SLAVE is the spare server
- SLAVE is switched on, with an IP address different than MASTER
- Every 15 minutes, MASTER makes a backup on SLAVE
- An email is sent to root (admin if mail server is installed)


Installation
============

Install nethserver-hosync on both MASTER and SLAVE

Configuration
=============

Master
------

::

    [root@master]# config setprop rsyncd password <PASSWORD>
    [root@master]# config setprop hotsync role master
    [root@master]# config setprop hotsync SlaveHost <SLAVE_IP>
    [root@master]# signal-event nethserver-hotsync-update


Slave
-----

::

    [root@slave]# config setprop rsyncd password <PASSWORD>
    [root@slave]# config setprop hotsync role slave
    [root@slave]# config setprop hotsync MasterHost <MASTER_IP>
    [root@slave]# signal-event nethserver-hotsync-update


<PASSWORD> must be the same on master and slave.

If mysql or postgresql are installed, they will be synchronized by default. To disable databases sync

::

    [root@master]# config setprop hotsync databases disabled
    [root@master]# signal-event nethserver-hotsync-update


Restore: put SLAVE in production
================================

1. Switch off MASTER if it's on
2. On SLAVE launch restore command:

::
       
    [root@slave]# signal-event nethserver-hotsync-restore


Don't forget to:

- connect modem to spare if you have one
- connect backup HD to spare
- connect router

To put again in production original server, configure it as SLAVE, sync it, switch off current MASTER and restore configuration backup.


==================
Supported packages
==================

* nethserver-nextcloud
* nethserver-mysql
* nethserver-dnsmasq
* nethserver-squidguard
* nethserver-pulledpork
* nethserver-antivirus
* nethserver-samba-audit
* nethserver-freepbx > 14.0.3
* nethserver-webtop5 (z-push state is not synchronized)
* nethserver-collectd
* nethserver-cups
* nethserver-dc
* nethserver-letsencrypt
* nethserver-nextcloud
* nethserver-sssd
* nethserver-directory
* nethserver-ibays
* nethserver-mail-server
