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
* Clustered services storing the data inside the shared storage


**Example**

The MySQL daemon listens on a virtual IP and stores the data inside the DRBD partition.
In case of failure of the master node, mysqld service will be restarted on the secondary node.
All clients connect to MySQL using the virtual IP.


Limitations
===========

* The LDAP service and all services depending on it can't be clustered.
  We recommend the use of and external LDAP server.
* Only STONITH fence devices are supported


Hardware requirements
=====================

You must use two identical nodes. Each node must have

* a disk, or a partition, dedicated to shared storage DRBD (Distributed Replicated Block Device)
* two network interfaces to be bonded on a *green* role, both interfaces must be connected to LAN switches

You should also have two LAN switches, let's say SW1 and SW2.
On each node, create a bond using two interfaces. Every node must be attached both to SW1 and SW2.

Fence device
------------

Each node must be connected at least to one pre-configured fence device.

*Fencing* is the action which disconnects a node from shared storage. 
The *fence device* is a hardware device than can be used to shutdown a node using 
the STONITH (Shoot The Other Node In The Head) method, thus cutting off the power to the failed node.

We recommend a switched PDU (Power Distribution Unit), 
but IPMI (Intelligent Platform Management Interface) devices should work with some limitations.
It's also possible to use a managed switch that supports SNMP IF-MIB protocol.

External links:

* list of supported devices: https://access.redhat.com/articles/28603
* more info about fencing: http://clusterlabs.org/doc/crm_fencing.html

Installation
============

Before install:

* connect both nodes as described before, while the secondary node is powered off. Proceed by installing |product| on the primary node
* make sure the System Name of the master node is *ns1*. Example: ns1.mydomain.com. 
  Also choose the domain name, which *can not* be changed later.

Primary node
------------

The primary node will be the one running services on normal conditions.
First, you must configure a logical volume reserved for DRBD shared storage.

Configuring DRBD storage
^^^^^^^^^^^^^^^^^^^^^^^^

* Add a new disk (example: vdb)
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

Execute the following steps to proceed with software installation and configuration.

* Configure a bond on green interfaces.

* Install cluster services:

::

 yum install nethserver-ha

* Install extra software, like MySQL:

::

  yum install nethserver-mysql

* Configure the virtual IP, and inform the cluster about green IPs of both nodes:

::

 config setprop ha VirtualIP <GREEN_IP_HA>
 config setprop ha NS1 <NS1_GREEN_IP>
 config setprop ha NS2 <NS2_GREEN_IP>

* Apply the configuration and start services on master node: 

::

 signal-event nethserver-ha-save


When the command completes, the primary node is ready to run the services.
You can check the cluster status with following command: ::

 pcs status

Service configuration
^^^^^^^^^^^^^^^^^^^^^

Cluster services must be handled by resource manager daemon (pacemaker),
you should disable |product| service handling for the clustered service: ::

 service mysqld stop
 chkconfig mysqld off
 /sbin/e-smith/config settype mysqld clustered

The following commands will configure a MySQL instance bound to the virtual IP. Data are saved inside DRBD: ::

 /usr/sbin/pcs cluster cib /tmp/mycluster
 /usr/sbin/pcs -f /tmp/mycluster resource create DRBDData ocf:linbit:drbd drbd_resource=drbd00 op monitor interval=60s
 /usr/sbin/pcs -f /tmp/mycluster resource master DRBDDataPrimary DRBDData master-max=1 master-node-max=1 clone-max=2 clone-node-max=1 is-managed="true" notify=true
 /usr/sbin/pcs -f /tmp/mycluster resource create VirtualIP IPaddr2 ip=`config getprop ha VirtualIP` cidr_netmask=`config getprop ha VirtualMask` op monitor interval=30s
 /usr/sbin/pcs -f /tmp/mycluster resource create drbdFS Filesystem device="/dev/drbd/by-res/drbd00" directory="/mnt/drbd" fstype="ext4" 
 /usr/sbin/pcs -f /tmp/mycluster resource create mysqld lsb:mysqld
 /usr/sbin/pcs -f /tmp/mycluster resource create sym_var_lib_asterisk ocf:heartbeat:symlink params target="/mnt/drbd/var/lib/mysql" link="/var/lib/mysql" backup_suffix=.active
 /usr/sbin/pcs -f /tmp/mycluster resource create sym_etc_my.pwd ocf:heartbeat:symlink params target="/mnt/drbd/etc/my.pwd" link="/etc/my.pwd" backup_suffix=.active
 /usr/sbin/pcs -f /tmp/mycluster resource create sym_root_.my.cnf ocf:heartbeat:symlink params target="/mnt/drbd/root/.my.cnf" link="/root/.my.cnf" backup_suffix=.active

 /usr/sbin/pcs -f /tmp/mycluster constraint order promote DRBDDataPrimary then start drbdFS
 /usr/sbin/pcs -f /tmp/mycluster constraint colocation add drbdFS with DRBDDataPrimary INFINITY with-rsc-role=Master
 /usr/sbin/pcs -f /tmp/mycluster resource group add mysqlha drbdFS VirtualIP sym_var_lib_mysql sym_etc_my.pwd sym_root_.my.cnf var_lib_nethserver_secrets mysqld

 /usr/sbin/pcs cluster cib-push /tmp/mycluster

Check cluster and service status: ::

 pcs status

Take a look at the official pacemaker documentation for more information.

Secondary node
--------------

* Install |product| on the secondary node
* Make sure the secondary node is named *ns2* and the domain name is the same as primary node
* Configure the DRBD storage as already done for the primary node
* Install and configure software following the same steps as in the primary node
* Configure Virtual IP, NS1 and NS2 options, then apply the configuration:

::

 signal-event nethserver-ha-save


Final steps
-----------

* Enable the STONITH (commands can be executed on any node):

::

 pcs property set stonith-enabled=true

* Configure the fence device (commands can be executed on any node).
  
  Example for libvirt fence, where nodes are virtual machines hosted on the same KVM-enabled host with IP 192.168.1.1: 

::

 pcs  stonith create Fencing fence_virsh ipaddr=192.168.1.1 login=root passwd=myrootpass pcmk_host_map="ns1.nethserver.org:ns1;ns2.nethserver.org:ns2" pcmk_host_list="ns1.nethserver.org,ns2.nethserver.org"


* Configure an email address where notification will be sent in case of failure:

::

  pcs resource create MailNotify ocf:heartbeat:MailTo params email="admin@nethserver.org" subject="Cluster notification"

* It's strongly advised to change root password from web interface on both nodes.
  Root password is used to send commands to all cluster nodes.

Fencing with IPMI
-----------------

Many servers have a built-in management interface often known with commercial name like 
ILO (HP), DRAC (Dell) or BMC (IBM). Any of these interfaces follow the IPMI standard.
Since any management interface controls only the node where it resides, you must configure at least two fence
devices, one for each node.

If the cluster domain is ``nethserver.org``, you should use following commands: ::

 pcs stonith create ns2Stonith fence_ipmilan pcmk_host_list="ns2.nethserver.org" ipaddr="ns2-ipmi.nethserver.org" login=ADMIN passwd=ADMIN timeout=4 power_timeout=4 power_wait=4 stonith-timeout=4 lanplus=1 op monitor interval=60s
 pcs stonith create ns1Stonith fence_ipmilan pcmk_host_list="ns1.nethserver.org" ipaddr="ns1-ipmi.nethserver.org" login=ADMIN passwd=ADMIN timeout=4 power_timeout=4 power_wait=4 stonith-timeout=4 lanplus=1 op monitor interval=60s

Where ns1-ipmi.nethserver.org and ns2-ipmi.nethserver.org are host names associated with IP of the management interface.

Also, you should make sure that each stonith resource is hosted by the right node: ::

 pcs constraint location ns2Stonith prefers ns1.nethserver.org=INFINITY
 pcs constraint location ns1Stonith prefers ns2.nethserver.org=INFINITY

Fencing with IF-MIB switch
--------------------------

It's also possible to use a managed switch that supports SNMP IF-MIB as fence device. In this case, fenced node does not get powered off, but instead is cut offline by the switch, with the same effect. 

Verify switch configuration using fence agent for opening and closing ports on the switch:

  ::
  fence_ifmib -a <SWITCH_IP> -l <USERNAME> -p <PASSWORD> -P <PASSWORD_PRIV> -b MD5 -B DES -d <SNMP_VERSION> -c <COMMUNITY> -n<PORT> -o <off|on|status>

Following commands configure two switch connected in this way:
Node 1 network port 1 is connected to switch 1 port 1
Node 1 network port 2 is connected to switch 2 port 1
Node 2 network port 1 is connected to switch 1 port 2
Node 2 network port 2 is connected to switch 2 port 2

  ::

    pcs stonith create ns1sw1 fence_ifmib action=off community=<COMMUNITY> ipaddr=<SWITCH_1_IP> login=<USERNAME> passwd=<PASSWORD> port=1 snmp_auth_prot=MD5 snmp_priv_passwd=<PASSWORD_PRIV> snmp_priv_prot=DES snmp_sec_level=authPriv snmp_version=3 pcmk_host_list="<HOST_1>"
    pcs stonith create ns1sw2 fence_ifmib action=off community=fence ipaddr=<SWITCH_2_IP> login=<USERNAME> passwd=<PASSWORD> port=1 snmp_auth_prot=MD5 snmp_priv_passwd=<PASSWORD_PRIV> snmp_priv_prot=DES snmp_sec_level=authPriv snmp_version=3 pcmk_host_list="<HOST_1>"
    pcs stonith create ns2sw1 fence_ifmib action=off community=fence ipaddr=<SWITCH_1_IP> login=<USERNAME> passwd=<PASSWORD> port=2 snmp_auth_prot=MD5 snmp_priv_passwd=<PASSWORD_PRIV> snmp_priv_prot=DES snmp_sec_level=authPriv snmp_version=3 pcmk_host_list="<HOST_2>"
    pcs stonith create ns2sw2 fence_ifmib action=off community=fence ipaddr=<SWITCH_2_IP> login=<USERNAME> passwd=<PASSWORD> port=2 snmp_auth_prot=MD5 snmp_priv_passwd=<PASSWORD_PRIV> snmp_priv_prot=DES snmp_sec_level=authPriv snmp_version=3 pcmk_host_list="<HOST_2>"
    pcs stonith level add 1 <HOST_1> ns1sw1,ns1sw2
    pcs stonith level add 1 <HOST_2> ns2sw1,ns2sw2
    pcs constraint location ns1sw1 prefers <HOST_2>=INFINITY
    pcs constraint location ns1sw2 prefers <HOST_2>=INFINITY
    pcs constraint location ns2sw1 prefers <HOST_1>=INFINITY
    pcs constraint location ns2sw2 prefers <HOST_1>=INFINITY

Failure and recovery
====================

A two-node cluster can handle only one fault at a time.

.. note::
   If you're using IPMI fence devices, the cluster can't handle the power failure of a node,
   since the power is shared with its own fence device.

   In this case you must manually confirm the eviction of the node by executing this command
   on the running node: ::

     pcs stonith confirm <failed_node_name>

Failed nodes
------------

When a node is not responding to cluster heartbeat, the node will be evicted.
All cluster services are disabled at boot to avoid problems just in case of fencing:
a fenced node probably needs a little of maintenance before re-joining the cluster.

To re-join the cluster, manually start the services: ::

 pcs cluster start


Disconnected fence devices
--------------------------

The cluster will periodically monitor the status of configured fence devices.
If a device is not reachable, it will be put on stopped state.

When the fence device has been fixed, you must inform the cluster about each fence device with this command: ::

  crm_resource --resource <stonith_name> --cleanup --node <node_name>

Disaster recovery
-----------------

If case of hardware failure, you should simply re-install the failed node and rejoin the cluster.
Clustered services will be automatically recovered and data will be synced between nodes.

Just follow this steps.

1. Install |product| on machine.
2. Restore the configuration backup of the node, if you don't have the configuration backup,
   reconfigure the server and make sure to install ``nethserver-ha`` package.
3. Execute the join cluster event: ::

     signal-event nethserver-ha-save

Backup
======

The backup must be configured on both nodes and must be executed on a network shared folder.
Only the primary node will actually execute the backup process, the backup script will be enabled
on the secondary node only if the master node has failed.

If both nodes fail, you should re-install the primary node, restore the configuration backup
and start the cluster: ::

 signal-event nethserver-ha-save

Then restore the data backup only as the last step.
When the restore ends, reboot the system.

If you wish to backup the data inside the DRBD, take care to add the directories
inside the :file:`custom.include` file.

Example: ::

  echo "/mnt/drbd/var/lib/mysql" >> /etc/backup-data.d/custom.include 
