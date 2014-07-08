===
UPS
===

The nethserver-nut package provides:
* Network UPS Tool (NUT) configuration
* web UI for simple configuration
* optional collectd support

Configuration
=============

The package provides two configuration modes:

* Master: a master node is a machine directly connected to the UPS port
* Slave: a slave node is a machine connected to the master via tcp

If you need stand-alone mode, just configure the machine as master.

Master node
===========

A master node receives events from UPS, sends events to slaves and takes decisions (eg. power off the machine).

DB properties:

* *Mode*: master
* *Device*: UPS port, can be a device like ``/dev/ttyS0`` or ``auto`` if the UPS is USB
* *Model*: UPS driver name selected from :file:`/usr/share/driver.list`
* *Description*: UPS model description like "APC - Smart-UPS USB (**)" (used only on web UI)
* *Password*: chosen password to communicate between master and slaves
* *Ups*: ups name, default is ``UPS``
* *User*: upsmon user name, default is ``upsmon``
* *Notify*: if ``enabled`` notifications about UPS events are sent to the admin user, default is ``disabled``

The password is generated during first installation from the :file:`nethserver-nut-conf` action.

Slave node
==========

A slave node receives events from a master and takes decisions  (eg. power off the machine).

DB properties:

* *Mode*: slave
* *Master*: host name or ip address of master node
* *Password*: chosen password to communicate between master and slaves
* *User*: upsmon user name, default is ``upsmon``

Collectd-nut
============

If server is in master mode, collectd is configured to monitor the local connected UPS.

Optional package required: 

* collectd-nut
* nethserver-collectd

