.. _hotsync-section:

=======
HotSync
=======

.. warning::

   HotSync should be considered a `beta release <https://en.wikipedia.org/wiki/Software_release_life_cycle#Beta>`_.
   Please test it on your environment before using in production.

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

.. only:: nscom

    Install nethserver-hotsync on both MASTER and SLAVE, execute from command line: ::
    
      yum install nethserver-hotsync

.. only:: nsent

    Install nethserver-hotsync on both MASTER and SLAVE.

    To install the module on MASTER execute from command line: ::

      yum -y install nethserver-hotsync

    To install the module on SLAVE execute from command line: ::

      yum -y install --disablerepo=nethesis-*,nh-* nethserver-hotsync



If you want to tests the Cockpit-based web interface, execute also: ::

  yum --enablerepo=nethserver-testing install nethserver-cockpit-hotsync

Configuration
=============

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


The ``<PASSWORD>`` must be the same on master and slave.

If mysql or postgresql are installed, they will be synchronized by default. To disable databases sync

::

    [root@master]# config setprop hotsync databases disabled
    [root@master]# signal-event nethserver-hotsync-save


Enabling/Disabling
------------------

Hotsync is enabled by default. To disable it:

::

    [root@slave]# config setprop hotsync status disabled
    [root@slave]# signal-event nethserver-hotsync-save


and to re-enable it:

::

    [root@slave]# config setprop hotsync status enabled
    [root@slave]# signal-event nethserver-hotsync-save



Restore: put SLAVE in production
================================

The following procedure puts the SLAVE in production when the master has crashed.

1. switch off MASTER

2. if the SLAVE machine must run as network gateway, connect it to the
   router/modem with a network cable

3. on SLAVE, if you are connected through an ssh console, launch the ``screen``
   command, to make your session survive to network outages::

    [root@slave]# screen

4. on SLAVE launch the following command, and read carefully its output ::

    [root@slave]# hotsync-promote

5. go to Server Manager, in page ``Network`` and reassign roles to network
   interfaces as required

6. launch the command ::

    [root@slave]# /sbin/e-smith/signal-event post-restore-data

7. update the system to the latest packages version ::

    [root@slave]# yum clean all && yum -y update

8. if an USB backup is configured on MASTER, connect the backup HD to SLAVE

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
