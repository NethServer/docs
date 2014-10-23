.. index::
   single: DHCP
   alias: DHCP, Dynamic Host Configuration Protocol
   single: PXE
   alias: PXE, Preboot eXecution Environment

.. _dhcp-section:

=================
Server DHCP e PXE
=================

Il server DHCP (:dfn:`Dynamic Host Configuration Protocol` [#DHCP]_)
permette di controllare la configurazione di rete di tutti i computer
o dispositivi collegati alla LAN.  Quando un computer (o un
dispositivo come una stampante, smartphone, etc.) si connette alla
rete il :index:`DHCP` gli assegna automaticamente un indirizzo IP
valido e effettua la configurazione di DNS e gateway.

.. note:: Nella maggior parte dei casi i dispositivi sono già
          configurati per utilizzare il protocollo DHCP.

La specifica PXE (:dfn:`Preboot eXecution Environment` [#PXE]_)
consente ad un dispositivo di scaricare da rete il sistema operativo
all'avvio da una postazione di rete centralizzata, mediante i
protocolli DHCP e TFTP.  Vedere :ref:`dhcp_pxe` per un esempio su come
configurare un caso simile.

.. _dhcp_configuration:

Configurazione DHCP
===================

Il server DHCP può essere abilitato su tutte le interfacce *green* e
*blue* (vedi :ref:`network-section`).  |product| sceglierà un
indirizzo IP libero all'interno dell':dfn:`intervallo DHCP`
configurato nella pagina :guilabel:`DHCP > Server DHCP`.

L'intervallo DHCP deve appartenere alla rete dell'interfaccia
associata. Per esempio, se l'interfaccia green ha IP ``192.168.1.1`` e
maschera di rete ``255.255.255.0``, allora l'intervallo DHCP può
andare da ``192.168.1.2`` a ``192.168.1.254``.


.. _dhcp_reservation:

IP riservato a un host
======================

Il server DHCP assegna (*lease*) un indirizzo IP ad un dispositivo per
un periodo di tempo limitato.  Se un device richiede di avere sempre
lo stesso indirizzo IP, può essere dichiarato un `IP riservato`
associato al suo indirizzo MAC.


Nella pagina :guilabel:`Riserva IP` sono elencati tutti gli indirizzi
IP correntemente assegnati.  

* una riga con il pulsante :guilabel:`Riserva IP` identifica un host
  con un lease temporaneo (colore grigio),

* una riga con il pulsante :guilabel:`Modifica` identifica un host con
  un IP riservato (colore nero).  Una piccola icona con due frecce
  indica che il lease DHCP è scaduto: questa è una condizione normale
  per gli host con configurazione IP statica, poiché non comunicano
  mai col server DHCP.


.. _dhcp_pxe:

Configurazione per l'avvio da rete
==================================

Per consentire ai client di avviarsi dalla rete, sono richiesti i
seguenti componenti:

* il server :ref:`DHCP <dhcp_configuration>`, come visto nelle sezioni
  precedenti,

* il server :dfn:`TFTP` [#TFTP]_,

* il software per il client, servito mediante TFTP.

.. index::
   single: TFTP
   alias: Trivial File Transfer Protocol; TFTP

.. _dhcp_tftp:



TFTP è un protocollo di trasferimento file molto semplice e
generalmente utilizzato per il trasferimento automatico di file di
configurazione o di boot.

In |product| l'implementazione di TFTP è contenuta nel modulo DHCP ed
è abilitata per default.  Per consentire l'accesso a un file mediante
TFTP è sufficiente mettere il file dentro la directory
:file:`/var/lib/tftproot`.

.. note:: Per disabilitare TFTP digitare i seguenti comandi in una
          console di root: ::
	     
	     config setprop dhcp tftp-status disabled
	     signal-event nethserver-dnsmasq-save

Per esempio, ora configuriamo un client per avviarsi da rete con
CentOS. In |product|, digitare in una console di root: ::
             
  yum install syslinux
  cp /usr/share/syslinux/{pxelinux.0,menu.c32,memdisk,mboot.c32,chain.c32} /var/lib/tftpboot/
  config setprop dnsmasq dhcp-boot pxelinux.0
  signal-event nethserver-dnsmasq-save 
  mkdir /var/lib/tftpboot/pxelinux.cfg
  
Quindi, creare il file :file:`/var/lib/tftpboot/pxelinux.cfg/default`
con il seguente contenuto: ::
 
  default menu.c32
  prompt 0
  timeout 300

  MENU TITLE PXE Menu

  LABEL CentOS
    kernel CentOS/vmlinuz
    append initrd=CentOS/initrd.img

Creare una directory CentOS: ::

  mkdir -p /var/lib/tftpboot/CentOS
 
Copiare dentro la directory appena creata i file :file:`vmlinuz` e
:file:`initrd.img`. Questi file sono pubblici e possono essere trovati
nella immagine ISO, sotto la directory :file:`/images/pxeboot`, oppure
scaricati da un mirror di CentOS.

Per finire, avviare il client, selezionando dalla schermata di avvio
la modalità "PXE boot" o "boot from network", o simile.

.. Rubric:: Riferimenti

.. [#DHCP] Dynamic Host Configuration Protocol (DHCP)
           http://en.wikipedia.org/wiki/Dynamic_Host_Configuration_Protocol
.. [#TFTP] Trivial File Transfer Protocol
           https://en.wikipedia.org/wiki/Tftp
.. [#PXE] Preboot eXecution Environment
           http://en.wikipedia.org/wiki/Preboot_Execution_Environment


