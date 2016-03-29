======================
HA (High Availability)
======================

|product| supports High Availability only for some specific scenarios.

The cluster is based on two nodes in active-passive mode:
the master node (or primary node) runs all the service, meanwhile the slave node (or secondary node) 
takes over only if the master node fails.
Both nodes share a DRBD storage in active-passive mode.

This configuration supports:

* Virtual IPs connected to the green network
* Clustered services storing the date inside the shared storage


**Example**

The MySQL daemons listens to a virtual IP and stores the data inside the DRBD partition.
In case of failure of master node, the service will be restarted on the secondary node.
All clients connect to MySQL using the virtual IP.


Limitations
===========

* The LDAP service, and all services depending on it, can't be clustered.
  We recommend the use of and external LDAP server.
* Nodes can have only one green interface
* Only STONITH fence devices are supported


Hardware requirements
=====================

You must use two identical nodes. Each node must have

* a *green* interface, 
  both nodes must be connected to the LAN switch
* a network interface (gigabit ethernet) with the ``ha`` role,
  nodes can be directly connected with a cable
* a disk, or a partition, dedicated to shared storage DRBD (Distributed Replicated Block Device)

IP address on ``ha`` network are fixed and can't be modified:

* Primary node: 192.168.144.51
* Secondary node: 192.168.144.52

Fence device
------------

Each node must be connected to pre-configured fence device.

*Fencing* is the action which disconnects a node from shared storage. 
The *fence device* is a hardware device than can be used to shutdown a node using 
the STONITH method (Shoot The Other Node In The Head), thus cutting off the power to the failed node.

See also: https://access.redhat.com/articles/28603

Installation
============

Before install:

* connect both nodes as described before, also take care the secondary node is shut down. Proceed by installing |product| on the primary node
* make sure the System Name of the master node is *ns1*. Example: ns1.mydomain.com. 
  Also choose the domain name, which *can not* be changed later.

Primary node
------------

The primary node will be the one running services on normal conditions.
First, you must configure a logival volume reserved for DRBD shared storage.

Configuring DRBD storage
^^^^^^^^^^^^^^^^^^^^^^^^

* Add ad new disk (example, vdb)
* Create a new partition:

::

 parted /dev/vdb mklabel gpt
 parted /dev/vdb --script -- mkpart primary 0% 100%

* Create a physical volume:

::

 pvcreate /dev/vdb1

* Extend the volume group:

::

 vgextend VolGroup /dev/vdb1

* Create a logic volume for DRBD:

::

 lvcreate -n lv_drbd -l 100%FREE VolGroup


Software
^^^^^^^^

Cluster options are saved inside the ``ha`` configuration key. The key must have the same configuration
on both nodes.

Execute following steps to proceed with software installation and configuration.

* Configure the green interface, then add a new network interface for DRBD. This interface will have ``ha`` role.

  Example with eth1 on primary node:  

::

 db networks setprop eth1 device eth1 role ha ipaddr 192.168.144.51 netmask 255.255.255.0 onboot yes bootproto none 
 signal-event interface-update

* Install cluster services

::

 yum install nethserver-ha

* Install extra software, like MySQL

::

  yum install nethserver-mysql

* Configure the virtual IP

::

 config setprop ha VirtualIP <GREEN_IP_HA>

* Apply the configuration and start services on master node: 

::

 signal-event nethserver-ha-save


At the end, the primary node is ready to run the services.
You can check the cluster status with following command: ::

 pcs status

Service configuration
^^^^^^^^^^^^^^^^^^^^^

Cluster services must be handled by resource manager daemon (pacemaker),
you should disable |product| service handling for the clustered service: ::

 service mysqld stop
 chkconfig mysqld off
 /sbin/e-smith/config settype mysqld clustered

Following commands will configure a MySQL instance bound to the virtual IP. Data are saved inside DRBD: ::

 /usr/sbin/pcs cluster cib /tmp/mycluster
 /usr/sbin/pcs -f /tmp/mycluster resource create DRBDData ocf:linbit:drbd drbd_resource=drbd00 op monitor interval=60s
 /usr/sbin/pcs -f /tmp/mycluster resource master DRBDDataPrimary DRBDData master-max=1 master-node-max=1 clone-max=2 clone-node-max=1 is-managed="true" notify=true
 /usr/sbin/pcs -f /tmp/mycluster resource create VirtualIP IPaddr2 ip=`config getprop ha VirtualIP` cidr_netmask=`config getprop ha VirtualMask` op monitor interval=30s
 /usr/sbin/pcs -f /tmp/mycluster resource create drbdFS Filesystem device="/dev/drbd/by-res/drbd00" directory="/mnt/drbd" fstype="ext4" 
 /usr/sbin/pcs -f /tmp/mycluster resource create mysqld lsb:mysqld
 /usr/sbin/pcs -f /tmp/mycluster resource create sym_var_lib_asterisk ocf:heartbeat:symlink params target="/mnt/drbd/var/lib/asterisk" link="/var/lib/asterisk" backup_suffix=.active
 /usr/sbin/pcs -f /tmp/mycluster resource create sym_etc_my.pwd ocf:heartbeat:symlink params target="/mnt/drbd/etc/my.pwd" link="/etc/my.pwd" backup_suffix=.active
 /usr/sbin/pcs -f /tmp/mycluster resource create sym_root_.my.cnf ocf:heartbeat:symlink params target="/mnt/drbd/root/.my.cnf" link="/root/.my.cnf" backup_suffix=.active

 /usr/sbin/pcs -f /tmp/mycluster constraint order promote DRBDDataPrimary then start drbdFS
 /usr/sbin/pcs -f /tmp/mycluster constraint colocation add drbdFS with DRBDDataPrimary INFINITY with-rsc-role=Master
 /usr/sbin/pcs -f /tmp/mycluster resource group add mysqlha drbdFS VirtualIP sym_var_lib_mysql sym_etc_my.pwd sym_root_.my.cnf var_lib_nethserver_secrets mysqld

 /usr/sbin/pcs cluster cib-push /tmp/mycluster

Check cluster and service status: ::

 pcs status

Take a look to the official pacemaker documentation for more information.

Secondary node
--------------

* Install |product| on the secondary node
* Make sure the secondary node is named *ns2* and the domain name is the same as primary node
* Configure the DRBD storage as already done for the primary node
* Install and configure software as already done for the primary node
* Configure ha network interface for DRBD. Example with eth1:

::

 db networks setprop eth1 device eth1 role ha ipaddr 192.168.144.52 netmask 255.255.255.0 onboot yes bootproto none 
 signal-event interface-update


Final steps
-----------

* Enable the STONITH, commands can be executed on any node:

::

 pcs property set stonith-enabled=true

* Configure the fence device, commands can be executed on any node.
  
  Example for libvirt fence, where nodes are virtual machines hosted on the same KVM-enabled host with IP 192.168.1.1: 

::

 pcs  stonith create Fencing fence_virsh ipaddr=192.168.1.1 login=root passwd=myrootpass pcmk_host_map="ns1.nethserver.org:ns1;ns2.nethserver.org:ns2" pcmk_host_list="ns1.nethserver.org,ns2.nethserver.org"

* Configure an email address where notification will be sent in case of failure:

::

  pcs resource create MailNotify ocf:heartbeat:MailTo params email="admin@nethserver.org" subject="Cluster notification"

* It's strongly advised to change root password from web interface on both nodes.
  Root password is used to send commands to all cluster nodes.

Start services
==============

All cluster services are disabled at boot to avoid problems in case of fencing.
To start clustered services execute: ::

 pcs cluster start

Backup
======

The backup must be configured on both nodes and must be executed on a network shared folder.
Only the primary node will actually execute the backup process, the backup script will be enabled
on the secondary node only if the master node has failed.

If both nodes fail, you should re-install the primary node, reconfigure the cluster and 
restore the backup only at the end.
After the restore, reboot the system.

