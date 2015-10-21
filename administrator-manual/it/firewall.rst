.. _firewall-section:

==================
Firewall e gateway
==================

|product| è in grado di svolgere il ruolo di :index:`firewall` e :index:`gateway` all’interno della
rete in cui viene installato.
Tutto il traffico fra i computer della rete locale e Internet passa attraverso il server che decide come
instradare i pacchetti di rete (routing) e quali regole applicare.
 

Funzioni principali:

* Configurazione di rete avanzata (bridge, bonds, alias, ecc)
* Supporto WAN multiple (fino a 15)
* Gestione regole firewall
* Gestione banda (QoS)
* Port forwarding
* Regole per routing traffico su una specifica WAN
* Intrusion Prevention System (IPS)


La modalità firewall e gateway viene attivata solo se:

* il pacchetto `nethserver-firewall-base` è installato
* è configurata almeno una scheda di rete con ruolo red

.. _policy-section:

Policy
======

Ogni interfaccia di rete è identificata da un colore che ne indica il ruolo all'interno del sistema.
Vedi :ref:`network-section`.

Quando un pacchetto di rete attraversa una zona del firewall, il sistema valuta una lista di regole per decidere se 
il traffico debba essere bloccato o permesso.
Le :dfn:`policy` sono le regole di default che vengono applicate se il traffico di rete passante non corrisponde a nessun criterio
esistente.

Il firewall implementa due policy standard modificabili nella pagina :menuselection:`Regole firewall` -> :guilabel:`Configura`:

* :dfn:`Permesso`: tutto il traffico dalla rete green alla red è permesso
* :dfn:`Bloccato`: tutto il traffico dalla rete green alla red è bloccato. Il traffico permesso deve essere esplicitato con apposite regole

Le :index:`policy` del firewall permettono il traffico fra zone seguendo lo schema qui sotto: ::

 GREEN -> BLUE -> ORANGE -> RED

Il traffico è permesso da sinistra a destra, bloccato da destra a sinistra.

Per cambiare le policy di default è possibile creare delle regole tra zone nella pagina :guilabel:`Regole firewall`.

.. note:: Il traffico dalla rete locale verso il server sulla porta SSH (default 22) e Server Manager (default 980) è **sempre** permesso.

.. _firewall-rules-section:

Regole
======

Le :index:`regole` vengono applicate a tutto il traffico di rete che attraversa il firewall.
Quando un pacchetto di rete transita da una zona all'altra, il sistema cerca fra le regole configurate.
Se le caratteristiche del pacchetto corrispondono a quelle descritte in una regola, tale regola viene applicata.

.. note:: L'ordine delle regole è molto importante. Il sistema applica sempre la prima regola che corrisponde al traffico in transito.

Una regola si compone di tre parti principali:

* Azione: azione da intraprendere quando si applica la regola
* Origine traffico: indirizzo di origine del traffico, può essere una zona, una rete o un singolo host
* Destinazione traffico: indirizzo di destinazione del traffico, può essere una zona, una rete o un singolo host
* Servizio: porta e protocollo che individua un determinato tipo di traffico


Le azioni disponibili sono:

* :dfn:`ACCEPT`: accetta il traffico
* :dfn:`REJECT`: blocca il traffico ed informa il mittente che la richiesta effettuata non è permessa
* :dfn:`DROP`: blocca il traffico, i pacchetti vengono scartati e il mittente *non* viene notificato

.. note:: Se non è configurata almeno un'interfaccia red, il firewall non genererà nessuna regola per le zone blue e orange.

REJECT vs DROP
--------------

Come regola generale, si consiglia di usare :index:`REJECT` quando si desidera informare l'host sorgente del traffico che la porta a cui si
sta provando ad accedere è chiusa.
Solitamente le regole che rispondono alle richieste della LAN possono usare REJECT.

Per le connessioni provenienti da Internet si consiglia di usare :index:`DROP`, al fine di minimizzare la rivelazione di informazioni ad eventuali
attaccanti.

Log
---

Quando una regola viene applicata, è possibile registrare l'evento nel log abilitando la relativa spunta.
Il :index:`log del firewall` è salvato nel file :file:`/var/log/firewall.log`.

Esempi
------

Si riportano di seguito alcuni esempi di regole.

Bloccare tutto il traffico DNS proveniente dalla LAN e diretto verso Internet:

* Azione: REJECT
* Origine: green
* Destinazione: red
* Servizio: DNS (UDP porta 53)

Permettere alla rete ospiti di accedere a tutti i servizi in ascolto sul Server1:

* Azione: ACCEPT
* Origine: blue
* Destinazione: Server1
* Servizio: -


Multi WAN
=========

Con il termine :dfn:`WAN` (Wide Area Network) si indica una rete pubblica esterna al server, solitamente collegata a Internet.
I fornitori di collegamenti :index:`WAN` sono detti :dfn:`provider`.

Il sistema supporta fino ad un massimo di 15 connessioni WAN.
Se sul server sono configurare due o più schede red, è obbligatorio procedere alla configurazione dei :index:`provider`
dalla pagina :guilabel:`Multi WAN`.

Ogni provider configurato rappresenta una connessione WAN ed è associato ad una scheda di rete.
Ciascun provider definisce un :dfn:`peso`: maggiore è il :index:`peso`
maggiore è la priorità della scheda di rete associata al provider stesso.

Il sistema può utilizzare le connessioni WAN in due modalità (pulsante :guilabel:`Configura` nella pagina :menuselection:`Multi WAN`):

* :dfn:`Balance`: tutti i provider sono utilizzati contemporaneamente in base al loro peso 
* :dfn:`Active backup`: i provider sono utilizzati uno alla vola a partire da quello con il peso più alto. Se il provider in uso perde la connessione, tutto il traffico verrà dirottato sul successivo provider.


Esempio
-------

Dati due provider così configurati:

* Provider1: interfaccia di rete eth1, peso 100
* Provider2: interfaccia di rete eth0, peso 50

Se è attiva la modalità bilanciata, il server indirizzerà il doppio delle connessioni sul Provider1 rispetto al Provider2.

Se è attiva la modalità backup, il server indirizzerà tutte le connessioni sul Provider1; solo se il Provider1 diventa
inutilizzabile tutte le connessioni saranno indirizzate sul Provider2.



Port forward
============

Il firewall impedisce che richieste iniziate dall'esterno possano accedere alle reti private.
Se ad esempio all'interno della rete è presente un server web, solo i computer presenti nella rete green potranno accedere al servizio.
Qualsiasi richiesta fatta da un utente esterno alle reti locali viene bloccata.

Per permettere a qualsiasi utente esterno l'accesso al server web si utilizza il :dfn:`port forward`.
Il :index:`port forward` è una regola che consente un accesso limitato alle risorse delle LAN dall'esterno.

Quando si configura il server, è necessario scegliere le porte in ricezione o in ascolto su cui verrà redirezionato 
il traffico in ingresso nella scheda red.
Nel caso di un server web, le porte in ascolto sono solitamente la porta 80 (HTTP) e 443 (HTTPS).

Quando si crea un port forward è necessario specificare almeno i seguenti parametri:

* la porta di origine
* la porta di destinazione, che può essere diversa dalla porta di origine
* l'indirizzo dell'host a cui deve essere instradato il traffico
* è possibile specificare un range di porte utilizzando i due punti come separatore nella porta di origine (es: 1000:2000), in tale caso particolare il campo porta di destinazione dovrà rimanere vuoto


Esempio
-------

Dato il seguente scenario:

* Server interno con IP 192.168.1.10, detto Server1
* Server web in ascolto sulla porta 80 su Server1
* Server SSH in ascolto sulla porta 22 su Server1
* Altri servizi in ascolto sul range di porte compreso tra 5000 e 6000

In caso si voglia rendere accessibile dall'esterno il server web direttamente sulla porta 80, si dovrà creare un port forward fatto così:

* porta origine: 80
* porta destinazione: 80
* indirizzo host: 192.168.1.10

Tutto il traffico che arriva sulle reti red del firewall sulla porta 80, verrà redirezionato alla porta 80 di Server1.


In caso si voglia rendere accessibile dall'esterno il server SSH sulla porta 2222, si dovrà creare un port forward fatto così:

* porta origine: 2222
* porta destinazione: 22
* indirizzo host: 192.168.1.10


Tutto il traffico che arriva sulle reti red del firewall sulla porta 2222, verrà redirezionato alla porta 22 di Server1.

In caso si voglia rendere accessibile dall'esterno il server sull'intero range di porte compreso tra 5000 e 6000 si dovrà creare un port forward fatto così:

* porta origine: 5000:6000
* porta destinazione: 
* indirizzo host: 192.168.1.10
 

Limitare accesso
----------------

E' possibile limitare l'accesso al port forward solo da alcuni IP o reti compilando il campo :guilabel:`Permetti solo da`.

Questa configurazione è utile in casi alcuni servizi debbano essere accessibili solo da IP/reti fidati.
Esempi di alcuni valori possibili:

* ``10.2.10.4``: abilita il port forward solo per il traffico proveniente dall'IP 10.2.10.4
* ``10.2.10.4,10.2.10.5``: abilita il port forward solo per il traffico proveniente dagli IP 10.2.10.4 e 10.2.10.5
* ``10.2.10.0/24``: abilita il port forward solo per il traffico proveniente dalla rete 10.2.10.0/24
* ``!10.2.10.4``: abilita il port forward per tutti gli IP tranne 10.2.10.4
* ``192.168.1.0/24!192.168.1.3,192.168.1.9``: abilita il port forward per tutta la rete 192.168.1.0/24  ad eccezione degli host 192.168.1.3 e 192.168.1.9

NAT 1:1
=======

Il NAT uno-a-uno consiste nell'associare un indirizzo IP privato ad un indirizzo IP pubblico per configurare, ad esempio, sistemi che si trovano dietro ad un firewall.

Se si hanno a disposizione diversi IP pubblici e si vuole associare uno di questi ad un determinato host della rete, è possibile farlo, appunto, mediante il :index:`NAT 1:1`. 


Esempio
-------

Nella nostra rete abbiamo un host di nome ``host_esempio`` che ha IP ``192.168.5.122``. Abbiamo inoltre associato un IP pubblico di cui disponiamo ``89.95.145.226`` come alias dell'interfaccia ``eth0`` (``RED``). 

Vogliamo quindi mappare il nostro host interno (``host_esempio`` - ``192.168.5.122``) con l'IP pubblico ``89.95.145.226``.

Dal pannello :guilabel:`NAT 1:1` andremo a scegliere per l'IP ``89.95.145.226`` (che compare come campo in sola lettura) il corrispondente host (``host_esempio``) che scegliamo dal combobox. Così facendo abbiamo configurato il NAT uno-a-uno per il nostro host.


Gestione banda
==============

La :index:`gestione banda` (:index:`traffic shaping`) permette di applicare regole di priorità sul traffico che attraversa il firewall.
In tal modo è possibile ottimizzare la trasmissione, controllare la latenza e sfruttare al meglio
la banda disponibile.

Per attivare il traffic shaping è necessario conoscere la quantità di banda disponibile nelle due direzioni
e compilare i campi indicando la velocità nominale del link Internet, consapevoli del fatto
che in caso di congestione da parte del provider non c'è nulla da fare per poter migliorare le prestazioni.
I classici valori per una ADSL sono 256 kbit/sec per uplink e 1280 per downlink.

La configurazione della banda può essere effettuata nella pagina :menuselection:`Gestione banda` -> :guilabel:`Regole interfacce`.

Il sistema prevede tre livelli di priorità, alta, media e bassa: di default tutto il traffico ha priorità media,
ma è possibile assegnare priorità alta o bassa a determinati servizi in base alla porta utilizzata (per esempio bassa al traffico peer to peer).

Da evidenziare il fatto che il sistema funziona anche senza che vengano specificati servizi a priorità alta o bassa,
perché, di default, il traffico interattivo viene automaticamente gestito ad alta priorità
(significa che, per esempio, non è necessario specificare porte per il traffico VoIP o SSH).
Anche al traffico di tipo PING è garantita alta priorità.


.. note:: Assicurarsi di specificare una stima accurata della banda.


Oggetti firewall
================

Gli :index:`oggetti firewall` sono delle rappresentazioni dei componenti della rete e sono utili per semplificare la creazione
di regole.

Esistono 6 tipi di oggetti, 5 di questi sono relativi a sorgenti e destinazioni e sono:

* Host: rappresentano computer locali e remoti. Esempio: server_web, pc_boss
* Gruppi di host: rappresentano gruppi omogenei di computer. Gli host all'interno di un gruppo devono essere raggiungibili attraverso la stessa interfaccia.
  Esempio: servers, pc_segreteria
* Reti CIDR : E' possibile esprimere una intera rete CIDR per semplificare e rendere più leggibili le regole. 

  Esempio 1 : gli ultimi 14 ip della rete sono destinati ai server (192.168.0.240/28).

  Esempio 2 : Più interfacce green configurate ma vogliamo creare una regola di firewall valida solo per una di queste green (192.168.2.0/24).

* Range IP : Usati per lo stesso motivo delle reti CIDR, cambia solo la modalità di definizione.
* Zone: rappresentano reti di host, vanno espresse in notazione CIDR, utili se si vuole definire un segmento di rete con caratteristiche differenti dalla zona di cui fa parte. Solitamente utilizzate per esigenze molto specifiche.

.. note:: Di default gli host che fanno parte di una Zona non possono fare alcun tipo di traffico, sarà necessario quindi creare tutte le regole necessarie a caratterizzarne il comportamento.

L'altro oggetto invece specifica il tipo di traffico ed è quello dei:

* Servizi: rappresentano un servizio in ascolto su un host. Esempio: ssh, https

Durante la creazione delle regole, è possibile usare i record definiti in :ref:`dns-section` e :ref:`dhcp-section` come oggetti host.
Inoltre ogni interfaccia di rete con un ruolo associato è automaticamente elencata fra le zone disponibili.

Binding IP/MAC
==============

Quando il sistema è configurato come server DHCP, il firewall può utilizzare la lista delle riserve DHCP per
controllare il traffico generato dagli host presenti nelle reti locali.
Se il :index:`binding IP/MAC` è abilitato, l'amministratore può scegliere quale politica applicare agli host
senza riserva DHCP.
Solitamente questa funzione è utilizzata per permettere il traffico solo dagli host conosciuti e bloccare tutti gli altri.
In questo caso, gli host senza una riserva DHCP non potranno accedere ne al firewall ne alla rete esterna.

Per abilitare il traffico solo dagli host conosciuti, seguire questi passi:

1. Creare una riserva DHCP per l'host
2. Andare sulla pagina :menuselection:`Regole firewall` e selezionare :guilabel:`Configura` dal menu
3. Selezionare :guilabel:`Validazione MAC (Binding IP/MAC)`
4. Spuntare :guilabel:`Blocca traffico` come policy per gli host senza riserva DHCP


.. note:: Ricordarsi di creare almeno una riserva DHCP prima di abilitare la modalità binding IP/MAC, 
   altrimenti nessun host sarà in grado di configurare il server usando l'interfaccia web o SSH.

