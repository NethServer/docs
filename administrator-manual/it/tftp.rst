=======================================
TFTP - Trivial File Transfer Protocol
=======================================

|product| può essere facilmente configurato come server :index:`TFTP` (https://it.wikipedia.org/wiki/Tftp). Il TFTP è un protocollo di trasferimento file molto semplice e generalmente utilizzato per il trasferimento automatico di file di configurazione o di boot. 

Configurazione
===============

Dopo l'installazione è necessario abilitare il server TFTP con i comandi: ::

 config setprop tftp status enabled
 signal-event nethserver-tftp-save

Da questo momento, il server TFTP è raggiungibile alla porta UDP 69.

Per rendere aggiungibile un file tramite TFTP, è sufficiente copiarlo nella cartella :file:`/var/lib/tftpboot` ed assicurarsi che il proprietario sia ``nobody``

Server PXE
===========

Il TFTP è anche parte di :index:`PXE`. Le istruzioni seguenti sono per usare |product| come server PXE di CentOS::

 yum install syslinux
 cp /usr/share/syslinux/{pxelinux.0,menu.c32,memdisk,mboot.c32,chain.c32} /var/lib/tftpboot/
 config setprop tftp dhcp-boot pxelinux.0
 signal-event nethserver-tftp-save
 mkdir /var/lib/tftpboot/pxelinux.cfg

Creare il file :file:`/var/lib/tftpboot/pxelinux.cfg/default` con il seguente contenuto: ::

 default menu.c32
 prompt 0
 timeout 300

 MENU TITLE PXE Menu

 LABEL CentOS
   kernel CentOS/vmlinuz
   append initrd=CentOS/initrd.img

Creare una directory CentOS: ::

 mkdir -p /var/lib/tftpboot/CentOS
 
Copiare dentro la directory appena creata i file :file:`vmlinuz` e :file:`initrd.img`. Questi file possono essere trovati nella iso di CentOS o cercando nei mirror di yum (nel repository "*os*")

Cambiare il proprietario in "nobody": ::

 chown -R nobody /var/lib/tftpboot/*

