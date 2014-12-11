.. _base_system-section:

============
Sistema base
============

Questo capitolo descrive tutti i moduli disponibili al termine dell'installazione.
Tutti i moduli al di fuori di questa sezione devono essere installati dalla :ref:`package_manager-section`,
inclusi il backup e il supporto per gli utenti.


.. _dashboard-section:

Dashboard
=========

La pagina mostrata di default dopo il login è la :index:`Dashboard`; qui viene
visualizzato un riepilogo dello stato del sistema e delle sue
impostazioni.

Vengono riportate la configurazione di rete, l’uso della memoria, l’uso
del disco, informazioni sul carico ed uptime della macchina, etc.

.. _network-section:

Rete
====

La configurazione di rete consente di stabilire in quale modo il server è collegato
alla :index:`rete` locale (LAN) oppure alle reti pubbliche (Internet).

Se il server svolge la funzionalità di firewall e gateway, sarà in grado di gestire reti aggiuntive
con funzionalità speciali come DMZ (DeMilitarized Zone) o rete ospiti.

|product| supporta un numero illimitato di schede di rete.
Le reti gestite devono sottostare alle regole seguenti:

* le reti devono essere fisicamente separate (non possono essere collegate allo stesso switch/hub)
* le reti devono essere logicamente separate (essere configurate su sotto-reti differenti)
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

.. _logical_interfaces-section:

Interfacce logiche
------------------

I tipi di interfacce logiche supportate sono:

* :index:`alias`: associa uno o più IP ad una scheda esistenza. L'alias ha lo stesso ruolo della scheda fisica associata
* :index:`bond`: combina due o più interfacce, garantisce bilanciamento del traffico e tolleranza ai guasti
* :index:`bridge`: collega due reti distinte, è spesso utilizzata per le VPN in bridge e le macchine virtuali
* :index:`vlan` (Virtual Local Area Network): crea due o più reti fisicamente separate usando una singola interfaccia fisica

Gli alias sono utilizzati per configurare IP multipli su una singola scheda di rete. Ad esempio, se si desidera avere più IP pubblici su
un'interfaccia red.

I bond consentono di aggregare banda fra due o più interfacce di rete. Il sistema utilizzerà tutte le schede contemporaneamente bilanciando
il traffico fra tutte le schede attive. In caso di errore, la scheda guasta viene automaticamente esclusa dal bond.

I bridge hanno la funzione di collegare segmenti di rete differenti, per esempio consentendo ai client collegati in VPN o macchine virtuali
di accedere alla rete locale (green).

Quando non è possibile separare fisicamente due reti diverse, è possibile utilizzare le vlan con tag. Il traffico delle due reti può
essere trasmesso sullo stesso cavo ma sarà trattato come se fosse inviato e ricevuto da due schede separate.
L'utilizzo delle vlan necessita di switch adeguatamente configurati.

.. _RFC1918-section:

Numerazione delle reti private (RFC1918)
----------------------------------------

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

.. _reset_network-section:

Reset network configuration
---------------------------

In caso di configurazione errata, è possibile :index:`riconfigurare la rete` seguendo i passi descritti sotto.

1. Eliminare tutte le interfacce logiche e fisiche dal database

   Per visualizzare la configurazione corrente ::

     db networks show

   Eliminare le interfacce: ::

     db network delete eth0

   Ripetere l'operazione per tutte le le interfacce compresi bridge, bond e vlan.


2. Disabilitare le interfacce

   Interfacce fisiche: ::
   
     ifconfig eth0 down

   In caso di bridge: ::

     ifconfig br0 down
     brctl delbr br0 

   In caso di bond (eth0 collegata a bond0): ::

     ifenslave -d bond0 eth0
     rmmod bonding

3. Rimuovere i file di configurazione

   I file della configurazione di rete sono salvati all'interno della directory :file:`/etc/sysconfig/network-scripts/`
   nella forma :file:`/etc/sysconfig/network-scripts/ifcfg-<devicename>`. Dove `devicename` è il nome
   dell'interfaccia come `eth0`, `br0`, `bond0`.

   Eliminare i file: ::

     rm -f /etc/sysconfig/network-scripts/ifcfg-eth0
   
   Ripetere l'operazione per tutte le le interfacce compresi bridge, bond e vlan.

4. Riavviare la rete

   Dopo il riavvio della rete, dovrebbe risultare configurata solo l'interfaccia di loopback: ::

     service network restart

   usare il comando :command:`ifconfig` per controllare lo stato della rete.

5. Riconfigurare manualmente la rete

   Scegliere un IP da assegnare all'interfaccia, per esempio `192.168.1.100`: ::

     ifconfig eth0 192.168.1.100

   Quindi riconfigurare il sistema: ::

     signal-event system-init

   L'interfaccia avrà quindi l'IP scelto.

6. Aprire l'interfaccia web e riconfigurare secondo le proprie necessità


.. _network_services-section:

Servizi di rete
===============

Un :index:`servizio di rete` è un servizio che viene eseguito sul firewall stesso.

Tali servizi sono sempre accessibili da tutti i computer nella rete green (rete locale).
E' possibile cambiare le politiche di accesso dalla pagina :guilabel:`Servizi di rete`.

Le politiche di accesso disponibili sono:

* Accesso solo dalle reti verdi (private): comprende tutti gli host sulla rete green e tutti i computer collegati in VPN
* Accesso dalle reti green e red (public): tutti gli host dalle reti green, VPN e reti esterne. Ma non dalla rete ospiti (blue) e dalla DMZ (orange)
* Accesso solo dal server stesso (none): nessun host può collegarsi al servizio selezionato

Se si selezionano le prime due politiche elencate è possibile specificare un host (o una lista di host) a cui l'accesso
al servizio è sempre bloccato o sempre permesso.

Accesso personalizzato
----------------------

Se la politica selezionata è private o public, è possibile specificare una lista di host e reti che sono sempre 
consentiti (o bloccati) usando i campi :guilabel:`Consenti host` e :guilabel:`Blocca host`.
La regola di applica anche per le reti orange e blue.

Esempio
^^^^^^^

Data la seguente configurazione:

* Rete orange: 192.168.2.0/24
* Server NTP con politica di accesso private

Se gli host dalla DMZ devono accedere al server NTP, aggiungere la rete 192.168.2.0/24 nel campo :guilabel:`Consenti host`.


.. _remote_access-section:

Accesso remoto
==============

Server Manager
--------------

E' possibile specificare reti a cui sia esplicitamente consentito l'accesso al Server Manager.
Ad esempio, se il server è presso un cliente, si consiglia di permettere il collegamento dalla rete
remota da cui si voglia amministrare la macchina.

SSH
---

Si consiglia di mantenere sempre attivo il servizio :index:`SSH` (Secure Shell).
SSH è un protocollo per aprire una shell remota usando connessioni cifrate.

La configurazione di default consente l'autenticazione via password e mediante chiave pubblica/privata.


.. _trusted_networks-section:

Reti fidate
===========

Le :index:`reti fidate` sono speciali reti (remote o locali) a cui è garantito l'accesso a servizi speciali del server.

Ad esempio, i computer sulle reti fidate possono accedere a:

* Server Manager
* Cartelle condivise (SAMBA)
* Servizi web per reti locali (Statistiche)

Se si desidera che gli utenti collegati in VPN possano accedere a tutti i servizi del sistema,
aggiungere le reti delle VPN a questo pannello.

Se la rete remota è raggiungibile attraverso un router, ricordarsi di creare la rotta statica corrispondente nel pannello :ref:`static_routes-section`.



.. _static_routes-section:

Rotte statiche
==============

Il pannello consente di specificare instradamenti
particolari (:index:`rotte statiche`) che non facciano uso del default gateway (ad esempio per
raggiungere reti private collegate tramite linee dedicate o simili).

Se si desidera che gli host nella rete remota possano accedere ai servizi
del server, ricordarsi di creare una rete corrispondente nel pannello
:guilabel:`Reti fidate`.


Vedi :ref:`trusted_networks-section`.


.. _organization_contacts-section:

Indirizzo dell'organizzazione
=============================

I campi della pagina :guilabel:`Indirizzo dell'organizzazione` sono
utilizzati come valori di default nella creazione degli utenti.
Inoltre il nome dell'organizzazione e l'indirizzo sono mostrati nella
pagina di login del Server Manager.


.. index::
   pair: Certificato; SSL   

.. _server_certificate-section:

Certificato del server
======================

La pagina :guilabel:`Certificato del server` mostra il certificato SSL
attualmente installato e che viene presentato da tutti i servizi
presenti nel sistema.

Il pulsante :guilabel:`Nuovo certificate` consente di generare un
nuovo certificato SSL auto-firmato. Se si genera un nuovo certificato,
tutti i servizi SSL verranno riavviati e ai client di rete sarà
richiesto di accettare il nuovo certificato.


.. _user_profile-section:

Profilo utente
==============

Ogni utente può collegarsi al Server Manager utilizzando le proprie credenziali.

Dopo l'accesso, l'utente potrà :index:`cambiare la propria password` e le informazioni associate al proprio account:

* Nome e Cognome
* Indirizzo email esterno

L'utente può anche sovrascrivere i seguenti campi già impostati dall'amministratore:

* Società
* Ufficio
* Indirizzo
* Città
* Telefono


Arresto
=======

La macchina su cui è installato |product| può essere riavviata o spenta dalla pagina :menuselection:`Arresto`.
Selezionare l’opzione Riavvia oppure Spegni e fare click sul :guilabel:`Arresta il sistema`.

Al fine di evitare danni al sistema, utilizzare sempre questo modulo per effettuare una corretta procedura
di riavvio o spegnimento del server.


Visualizza Log
==============

Tutti i servizi registrano le operazioni svolte all'interno di file detti :dfn:`log`.
L'analisi dei :index:`log` è lo strumento principale per individuare malfunzionamenti e problemi.
Per visualizzare i file di log fare clic su :menuselection:`Visualizza Log`.
Si aprirà una pagina con l'elenco di tutti i file di log disponibili; fare click sui file che si intendo visualizzare.

Questo modulo consente di:

* effettuare ricerche all'interno di tutti i log del server
* visualizzare un singolo log
* seguire in tempo reale il contenuto di un log


Data e ora
==========

Al termine dell'installazione, assicurarsi che il server sia configurato con il corretto fuso orario.
L'orologio della macchina può essere configurato manualmente o automaticamente usando server NTP pubblici (consigliato).

La corretta configurazione dell'orologio è importante per il funzionamento di molti protocolli.
Per evitare problemi, tutti gli host della LAN possono essere configurati per usare il server stesso come server NTP.

