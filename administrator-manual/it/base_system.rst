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
visualizzato un riepilogo dello :index:`stato` del sistema e delle sue
impostazioni.

.. _duc-section:

Analizzatore disco
------------------

Questo strumento è usato per visualizzare l':index:`utilizzo del disco` in un semplice grafico in cui è possibile interagire con click e doppio click per navigare nelle cartelle.

Dopo l'installazione andare nella pagina :guilabel:`Dashboard` e poi nella scheda :guilabel:`Utilizzo disco`,
quindi cliccare su :guilabel:`Aggiorna` per indicizzare la directory root e mostrare il grafico.
Questo processo può durare diversi minuti in base allo spazio occupato su disco.

Alcune cartelle note sono:

* Cartelle condivise: :file:`/var/lib/nethserver/ibay`
* Home degli utenti: :file:`/var/lib/nethserver/home`
* Profili roaming Windows: :file:`/var/lib/nethserver/profile`
* Mail: :file:`/var/lib/nethserver/vmail`
* Fax: :file:`/var/lib/nethserver/fax`
* Database MySQL: :file:`/var/lib/mysql`


.. index::
   single: Rete
   pair: interfaccia; ruolo

.. _network-section:

Rete
====

La pagina :guilabel:`Rete` consente di stabilire in quale modo il
server è collegato alla rete locale (LAN) oppure alle reti pubbliche
(Internet).

Se il server svolge la funzionalità di firewall e gateway, sarà in grado di gestire reti aggiuntive
con funzionalità speciali come DMZ (DeMilitarized Zone) o rete ospiti.

|product| supporta un numero illimitato di schede di rete.
Le reti gestite devono sottostare alle regole seguenti:

* le reti devono essere fisicamente separate (non possono essere collegate allo stesso switch/hub)
* le reti devono essere logicamente separate (essere configurate su sotto-reti differenti)
* le reti private (es. LAN) devono rispettare le regole per gli indirizzi specificate nel documento RFC1918.
  Vedi :ref:`RFC1918-section`

.. index:: zone, role

Ogni interfaccia di rete ha un ruolo specifico che ne determina l'utilizzo e il comportamento. I ruoli sono indicati
tramite colori. Ogni colore indica la zona di appartenenza della scheda di rete e le regole ad essa applicate:

* *green*: rete locale. I computer su questa rete possono accedere a qualsiasi altra rete configurata sul server
* *blue*: rete ospiti.  I computer su questa rete possono accedere alle reti orange e red, ma non possono accedere alla zona green
* *orange*: rete DMZ. I computer su questa rete possono accedere alle reti red, ma non possono accedere alle zone blue e green
* *red*: rete pubblica. I computer in questa rete possono accedere solo al server stesso

Si veda :ref:`policy-section` per maggiori informazioni sull'uso dei ruoli nelle regole del firewall.

.. note:: Il server deve avere almeno un'interfaccia di rete. Quando il server ha una sola scheda di rete, tale scheda deve avere il ruolo green.

In caso di installazione su VPS (Virtual Private Server) pubblico, il server deve essere configurato con una schede di rete green.
Si consiglia quindi di chiudere le porte dei servizi critici usando il pannello :ref:`network_services-section`.

.. _alias_IP-section:

Alias IP
--------

Per assegnare più indirizzi IP alla stessa scheda è possibile utilizzare gli alias IP.

In tal modo è possibile ad esempio associare alla stessa red più indirizzi IP della stessa classe e gestirli in modo indipendente (ad esempio con dei port forward che discriminano in base allo specifico IP di destinazione).

L'alias è configurabile cliccando nel menu a tendina della specifica scheda di rete e avrà lo stesso ruolo della scheda fisica associata.

.. note:: L'alias IP su interfaccia PPPoE in alcuni casi potrebbe non funzionare correttamente a causa di differenze nella fornitura del servizio tra i vari provider internet.

.. _logical_interfaces-section:

Interfacce logiche
------------------

Nella pagina :guilabel:`Network` premere il pulsante :guilabel:`Nuova
interfaccia` per creare una interfaccia logica.  I tipi di interfacce
logiche supportate sono:

* :index:`bond`: combina due o più interfacce, garantisce bilanciamento del traffico e tolleranza ai guasti
* :index:`bridge`: collega due reti distinte, è spesso utilizzata per le VPN in bridge e le macchine virtuali
* :index:`VLAN` (Virtual Local Area Network): crea due o più reti fisicamente separate usando una singola interfaccia fisica
* :index:`PPPoE` (Point-to-Point Protocol over Ethernet): collegamento a Internet attraverso un modem DSL

I **bond** consentono di aggregare banda o tollerare guasti. I bond posso essere configurati in varie modalità.

Modalità che supportano aggregazione di banda e tolleranza ai guasti:

* Balance Round Robin (raccomandato)
* Balance XOR
* 802.3ad (LACP): richiede il supporto nel driver della scheda di rete
  ed uno switch in cui sia abilitata la modalità IEEE 802.3ad Dynamic link
* Balance TLB: richiede il supporto nel driver della scheda di rete
* Balance ALB

Modalità che supportano solo tolleranza ai guasti:

* Active backup (raccomandato)
* Broadcast policy

I **bridge** hanno la funzione di collegare segmenti di rete differenti, per esempio consentendo ai client collegati in VPN o macchine virtuali
di accedere alla rete locale (green).

Quando non è possibile separare fisicamente due reti diverse, è possibile utilizzare le **VLAN** con tag. Il traffico delle due reti può
essere trasmesso sullo stesso cavo ma sarà trattato come se fosse inviato e ricevuto da due schede separate.
L'utilizzo delle VLAN necessita di switch adeguatamente configurati.

.. warning:: All'interfaccia logica **PPPoE*** deve essere assegnato il ruolo di
             `red`, quindi richiede la funzionalità di gateway. Vedi :ref:`firewall-section` per i dettagli.

.. _RFC1918-section:

Numerazione delle reti private (RFC1918)
----------------------------------------

Per reti private TCP/IP indirettamente connesse a Internet che utilizzano un servizio di
conversione degli indirizzi di rete (NAT) o un gateway di livello applicazione,
quale un server proxy, l'Internet Assigned Numbers Authority (IANA) consiglia di utilizzare
gli indirizzi IP privati indicati nella tabella seguente.

===============   ===========   =============================
ID rete privata   Subnet mask   Intervallo di indirizzi IP
===============   ===========   =============================
10.0.0.0          255.0.0.0     10.0.0.1 - 10.255.255.254
172.16.0.0        255.240.0.0   172.16.0.1 - 172.31.255.254
192.168.0.0       255.255.0.0   192.168.0.1 - 192.168.255.254
===============   ===========   =============================


I numeri di questi intervalli sono riservati da IANA per l'utilizzo privato in reti TCP/IP e non vengono utilizzati in Internet.


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


Accesso personalizzato
----------------------

Se la politica selezionata è private o public, è possibile specificare una lista di host e reti che sono sempre
consentiti (o bloccati) usando i campi :guilabel:`Consenti host` e :guilabel:`Blocca host`.
La regola si applica anche per le reti orange e blue.

Esempio
^^^^^^^

Data la seguente configurazione:

* Rete orange: 192.168.2.0/24
* Server NTP con politica di accesso private

Se gli host dalla DMZ devono accedere al server NTP, aggiungere la rete 192.168.2.0/24 nel campo :guilabel:`Consenti host`.

.. index:: reti fidate

.. _trusted_networks-section:

Reti fidate
===========

Le reti fidate sono speciali reti (remote o locali) a cui è garantito
l'accesso a servizi speciali del server.

Ad esempio, i computer sulle reti fidate possono accedere a:

* Server Manager
* Cartelle condivise (SAMBA)

Se la rete remota è raggiungibile attraverso un router, ricordarsi di
creare la rotta statica corrispondente nel pannello
:ref:`static_routes-section`.



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

La pagina :guilabel:`Certificato del server` mostra i certificati X.509
attualmente installati e il certificato di default fornito dal sistema per
cifrare le comunicazioni TLS/SSL.

Il pulsante :guilabel:`Imposta default` consente di scegliere il certificato di
default. Quando viene scelto un nuovo certificato, tutti i servizi che
utilizzano TLS/SSL vengono riavviati e i client di rete devono accettare il
nuovo certificato.

Quando |product| è installato viene automaticamente generato un certificato
auto-firmato. Dovrebbe essere modificato inserendo dei valori appropriati prima
di utilizzarlo dai client di rete. Come alternative, la pagina
:guilabel:`Certificato del server` consente di:

* caricare un certificato esistente e la chiave privata RSA. In aggiunta può
  essere specificato anche un *chain file*. Tutti i file devono essere codificati
  nel formato PEM.

* richiedere un nuovo certificato di *Let's Encrypt* [#Letsencrypt]_. Questo è
  possibile se sono rispettati i seguenti requisiti:

  1. il server deve essere raggiungibile dall'esterno alla porta 80. Assicurarsi
     che la porta 80 è aperta alle connessioni da Internet (si può effettuare un
     test da siti come [#CSM]_);

  2. i domini che si vogliono associare al certificato devono essere domini pubblici,
     associati all'indirizzo IP pubblico del server. Assicurarsi di avere un nome
     registrato nel DNS pubblico che punta correttamente al proprio server (si
     può effettuare un test da siti come [#VDNS]_).

.. note::
       Per evitare problemi di importazione certificato con Internet Explorer,
       si consiglia di configurare il campo CN (Common Name) o Nome Comune
       in modo che corrisponda al FQDN del server.

.. [#Letsencrypt] Sito web di *Let's Encrypt* https://letsencrypt.org/
.. [#CSM] Sito web http://www.canyouseeme.org/
.. [#VDNS] Sito web http://viewdns.info/

.. _user_profile-section:

Cambio password utente
======================

Ogni utente può collegarsi al Server Manager utilizzando le proprie credenziali ed accedere al :index:`profilo utente`.

Dopo l'accesso, l'utente potrà :index:`cambiare la propria password`.


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
Si aprirà una pagina con l'elenco di tutti i file di log disponibili: fare click sui file che si intendo visualizzare.

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


Aiuto in linea
==============

Tutti i pacchetti che sono configurabili attraverso il Server Manager
contengono un :index:`manuale in linea` che spiega l'utilizzo base e tutti
i campi contenuti nella pagina.

Il manuale in linea è consultabile in tutte le lingue in cui è tradotto
il Server Manager.

Una lista di tutti i manuali installati nel sistema è disponibile all'indirizzo: ::

 https://<server>:980/<language>/Help

**Esempio**

Se il server ha indirizzo ``192.168.1.2`` e si desidera visualizzare la lista dei manuali in italiano,
usare il seguente indirizzo: ::

 https://192.168.1.2:980/it/Help
