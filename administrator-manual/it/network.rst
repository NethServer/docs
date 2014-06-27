.. _network-section:

====
Rete
====

La configurazione di rete consente di stabilire in quale modo il server è collegato
alla :index:`rete` locale (LAN) oppure alle reti pubbliche (Internet).

Se il server svolge la funzionalità di firewall e gateway, sarà in grado di gestire reti aggiuntive
con funzionalità speciali come DMZ (DeMilitarized Zone) o rete ospiti.

|product| supporta un numero illimitato di schede di rete.
Le reti gestite devono sottostare alle regole seguenti:

* le reti devono essere fisicamente separate (non possono essere collegate allo stesso switch/hub)
* le reti devono essere logicamente separate (essere configurate su sottoreti differenti)
* le reti private (es. LAN) devono rispettare le regole per gli indirizzi specificate nel documento RFC1918.
  Vedi :ref:`RFC1918-section`

Ogni interfaccia di rete ha un ruolo specifico che ne determina l'utilizzo e il comportamento. I ruoli sono indicati
tramite colori. Ogni colore indica la zona di appartenenza della scheda di rete e le regole ad essa applicate.

* *green*: rete locale. I computer su questa rete possono accedere a qualsiasi altra rete configurata sul server 
* *blue*: rete ospiti.  I computer su questa rete possono accedere alle reti orange e red, ma non possono accedere alla zona green
* *orange*: rete DMZ. I computer su questa rete possono accedere alle reti red, ma non possono accedere alle zone blue e green
* *red*: rete pubblica. I computer in questa rete possono accedere solo al server stesso

Si veda :ref:`policy-section` per maggiori informazioni sull'uso dei ruoli nelle regole del firewall.

.. note:: Il server deve avere almeno un'interfaccia di rete. Quando il server ha una sola scheda di rete, tale scheda deve avere il ruolo green.

In caso di installazione su VPS (Virtual Private Server) pubblico, il server deve essere configurato con una schede di rete green.
Si consiglia quindi di chiudere le porte dei servizi critici usando il pannello :ref:`network_services-section`. 


.. _network_services-section:

Servizi di rete
===============

Un :index:`servizio di rete` è un servizio che viene eseguito sul firewall stesso.

Tali servizi sono sempre accessibili da tutti i computer nella rete green (rete locale).
E' possibile cambiare le politiche di accesso dalla pagina :guilabel:`Servizi di rete`.

Le politiche di accesso disponibili sono:

* Accesso solo dalle reti locali (privato): comprende tutti gli host sulla rete green e tutti i computer collegati in VPN
* Accesso da tutte le reti (pubblico): tutti gli host
* Accesso solo dal server stesso (nessuno): nessun computer può collegarsi al servizio selezionato

Se si selezionano le prime due politiche elencate è possibile specificare un host (o una lista di host) a cui l'accesso
al servizio è sempre bloccato o sempre permesso.


.. _RFC1918-section:

Numerazione delle reti private (RFC1918)
========================================

Per reti private TCP/IP indirettamente connesse a Internet che utilizzano un servizio di 
conversione degli indirizzi di rete (NAT) o un gateway di livello applicazione, 
quale un server proxy, l'Internet Assigned Numbers Authority (IANA) consiglia di utilizzare
gli indirizzi IP privati indicati nella tabella che segue.

===============   ===========   =============================
ID rete privata   Subnet mask   Intervallo di indirizzi IP
===============   ===========   =============================
10.0.0.0          255.0.0.0     10.0.0.1 - 10.255.255.254
172.16.0.0        255.240.0.0   172.16.0.1 - 172.31.255.254
192.168.0.0       255.255.0.0   192.168.0.1 - 192.168.255.254
===============   ===========   =============================


I numeri di questi intervalli sono riservati da IANA per l'utilizzo privato in reti TCP/IP e non vengono utilizzati in Internet.
