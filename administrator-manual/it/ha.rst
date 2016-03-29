======================
HA (High Availability)
======================

|product| supporta una configurazione in HA limitata ad alcuni scenari specifici.

Il cluster è composto da due nodi in modalità active-passive:
il nodo master (o nodo primario) fornisce il servizio, mentre il nodo slave (o nodo secondario) entra in gioco in caso
di fallimento del nodo master.
Entrambi i nodi condividono uno storage DRBD in modalità active-passive.

Questa configurazione supporta:

* IP virtuali collegati sulla rete green
* Servizi clusterizzati che salvano i dati sullo storage condiviso


*Esempio*

Il demone MySQL risponde ad un IP virtuale e salva i propri dati all'interno del DRBD.
In caso di guasto del nodo master, il servizio viene fatto ripartire sul nodo secondario.

I client si collegano al server MySQL usando l'IP virtuale.


Limitazioni
===========

* Il servizio LDAP, e tutti i servizi che dipendono da esso, non possono essere clusterizzati.
  Si consiglia l'utilizzo di un LDAP esterno
* I nodi possono avere una singola interfaccia green
* Sono supportati solo i dispositivi di fencing di tipo STONITH


Requisiti hardware
==================

La procedura prevede l'installazione su due nodi gemelli. Ogni nodo dovrà avere

* un interfaccia di rete per la *green*, 
  entrambi i nodi devono essere collegati allo switch della rete locale
* un interfaccia di rete per il ruolo ``ha`` (Gigabit ethernet), 
  i nodi possono essere collegati fra di loro con un singolo cavo.
* un disco o una partizione dedicata allo storage condiviso DRBD (Distributed Replicated Block Device)

Gli indirizzi IP sulla rete ``ha`` sono così fissati e *non* possono essere modificati:

* Nodo primario: 192.168.144.51
* Nodo secondario: 192.168.144.52

Fence device
------------

Ogni nodo dovrà essere collegato con un fence device già correttamente configurato.

Con il termine *fencing* si intende la disconnessione di un nodo dallo storage condiviso.
Il *fence device* è il dispositivo hardware che consente tale disconnessione usando
il metodo STONITH (Shoot The Other Node In The Head), ovvero togliendo l'alimentazione al nodo guasto.

Per maggiori informazioni, consultare: https://access.redhat.com/articles/28603

Installazione
=============

Prima di iniziare:

* collegare i due nodi come previsto e assicurarsi che il nodo secondario sia spento, procedere poi installando |product| sul nodo primario
* assicurarsi che il nome host del nodo primario sia *ns1*. Esempio: ns1.mydomain.com. 
  Scegliere ora anche il dominio, che *non* potrà essere cambiato in seguito

Nodo primario
-------------

Il nodo primario sarà quello che fornirà i servizi in caso di normale funzionamento.
Per prima cosa è necessario configurare una partizione o un disco riservato allo storage
condiviso DRBD.

Configurazione storage per DRBD
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

* Aggiungere un disco (per esempio vdb)
* Partizionare il disco 

::

 parted /dev/vdb mklabel gpt
 parted /dev/vdb --script -- mkpart primary 0% 100%

* Creare sul disco una volume fisico 

::

 pvcreate /dev/vdb1

* Estendere il volume group 

::

 vgextend VolGroup /dev/vdb1

* Creare un volume logico per il DRBD 

::

 lvcreate -n lv_drbd -l 100%FREE VolGroup


Software
^^^^^^^^

Le opzioni del cluster sono salve all'interno della chiave di configurazione *ha* che deve essere
configurata specularmente su entrambi i nodi.

Eseguire i passi di configurazione come riportati di seguito.

* Configurare l'interfaccia green, quindi aggiungere un interfaccia dedicata per il DRBD. L'interfaccia avrà il ruolo **ha**. 

  Esempio con eth1 sul nodo primario:  

::

 db networks setprop eth1 device eth1 role ha ipaddr 192.168.144.51 netmask 255.255.255.0 onboot yes bootproto none 
 signal-event interface-update

* Installare i servizi del cluster

::

 yum install nethserver-ha

* Installare il software, esempio MySQL 

::

  yum install nethserver-mysql

* Configurare l'IP virtuale 

::

 config setprop ha VirtualIP <GREEN_IP_HA>

* Applicare le modifiche e avviare i servizi sul nodo primario: 

::

 signal-event nethserver-ha-save


Al termine della configurazione, il nodo primario è pronto ad erogare i servizi.
Per verificare lo stato del cluster, eseguire: ::

 pcs status

Configurazione servizi
^^^^^^^^^^^^^^^^^^^^^^

I servizi clusterizzati devono essere controllati dal demone che gestisce le risorse del cluster (pacemaker),
per tanto è necessario disattivare il riavvio automatico all'interno di |product|: ::

 service mysqld stop
 chkconfig mysqld off
 /sbin/e-smith/config settype mysqld clustered

I seguenti comandi configurano un'istanza di MySQL che salva i dati sul DRBD ed è legata all'IP virtuale: ::

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

Per verificare lo stato del cluster e dei servizi: ::

 pcs status

Si veda la documentazione ufficiale di pacemaker per maggiori informazioni

Nodo secondario
---------------

* Installare |product| sul nodo secondario
* Assicurarsi che l'hostname del nodo secondario sia *ns2* e che il dominio sia lo stesso del nodo primario
* Procedere alla configurazione storage DRBD come sul nodo primario
* Installare e configurare il software come per il nodo primario
* Configurazione interfaccia di rete per DRBD.  Esempio con eth1: 

::

 db networks setprop eth1 device eth1 role ha ipaddr 192.168.144.52 netmask 255.255.255.0 onboot yes bootproto none 
 signal-event interface-update


Passi finali
------------

* Abilitare lo STONITH, digitando su uno qualsiasi dei nodi il seguente comando: 

::

 pcs property set stonith-enabled=true

* Configurare i fence device, i comandi possono essere eseguiti su uno qualsiasi dei nodi.
  Esempio per fence con libvirt, dove i nodi sono macchine virtuali ospitate da un virtualizzatore con IP 192.168.1.1: 

::

 pcs  stonith create Fencing fence_virsh ipaddr=192.168.1.1 login=root passwd=myrootpass pcmk_host_map="ns1.nethserver.org:ns1;ns2.nethserver.org:ns2" pcmk_host_list="ns1.nethserver.org,ns2.nethserver.org"

* Configurare un indirizzo mail a cui inviare le notifiche in caso di guasto:

::

  pcs resource create MailNotify ocf:heartbeat:MailTo params email="admin@nethserver.org" subject="Cluster notification"

* E' fortemente consigliato di cambiare la password di root da interfaccia web su entrambi i nodi. 
  La password di root è infatti utilizzata per impartire ordini ai nodi del cluster.

Avviare i servizi
=================

Tutti i servizi clusterizzati sono disabilitati al boot per evitare problemi in caso di fencing.
Per avviare i servizi clusterizzati eseguire: ::

 pcs cluster start


Backup
======

Il backup deve essere configurato su entrambi i nodi ed eseguito su una condivisione di rete.
Solo il nodo primario effettuerà realmente il backup, il backup del nodo secondario
verrà automaticamente abilitato qualora il nodo primario sia guasto.

In caso di guasto di entrambi i nodi, reinstallare il nodo primario, riconfigurare il cluster
ed infine ripristinare il backup.
Al termine, riavviare il sistema.
