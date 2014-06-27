===============
Amministrazione
===============

Dashboard
=========

La pagina mostrata di default dopo il log in è la index:`Dashboard`; qui viene
visualizzato un riepilogo dello stato del sistema e delle sue
impostazioni.

Vengono riportate la configurazione di rete, l’uso della memoria, l’uso
del disco, informazioni sul carico ed uptime della macchina, etc.

Arresto
=======

La macchina su cui è installato |product| può essere riavviata o spenta dalla pagina :menuselection:`Arresto`.
Selezionare l’opzione Riavvia oppure Spegni e fare click sul :guilabel:`Arresta il sistema`.

Al fine di evitare danni al sistema, utilizzare sempre questo modulo per effettuare una corretta procedura
di riavvio o spegnimento del server.


Visualizza Log
==============

Come per ogni sistema Linux, Nethserver è molto ricco di file di :index:`log` che registrano tutte le operazioni che vengono svolte; ciò può essere molto utile in situazioni di malfunzionamento del sever per individuare i problemi in maniera rapida.
Per visualizzare i file di log fare clic su :menuselection:`Amministrazione → Visualizza Log`. Si aprirà una pagina con l'elenco di tutti i file di log disponibili; fare click sui file che si intendo visualizzare.

Questo modulo consente di:

* effettuare ricerche all'interno di tutti i log del server
* visualizzare un singolo log
* seguire in tempo reale il contenuto di un log

Accesso remoto
==============

.. _trusted_networks-section:

Reti fidate
-----------

Le :index:`reti fidate` sono speciali reti (remote o locali) a cui è garantito l'accesso a servizi speciali del server.

Ad esempio, i computer sulle reti fidate possono accedere a:

* Server Manager
* Cartelle condivise (SAMBA)
* Servizi web per reti locali (Statistiche)

Se si desidera che gli utenti collegati in VPN possanno accedere a tutti i servizi del sistema,
aggiungere le reti delle VPN a questo pannello.

Se la rete remota è raggiungibile attraverso un router, ricordarsi di creare la rotta statica corrispondente nel pannello :ref:`static_routes-section`.

Server Manager
--------------

Configura accesso all'interfaccia web Server Manager.

Indirizzo di rete
    È l'indirizzo dal quale sarà consentito accedere all'interfaccia
    web.

Maschera di rete
    Maschera di rete dell'indirizzo. Per consentire l'accesso ad un solo
    host, utilizzare come maschera di rete 255.255.255.255.

SSH
---

Gestione dell'accesso :index:`SSH` (Secure Shell) al server.

Abilitato / Disabilito
    Abilita / disabilita l'accesso SSH.

Porta TCP
    Inserire la porta TCP usata per l'accesso SSH.

Accetta connessioni da reti locali
    Accesso SSH abilitato solo da connessioni provenienti da reti
    locali.

Accetta connessioni da qualsiasi rete
    Accesso SSH abilitato per connessioni provenienti da qualsiasi rete.

Consenti l'accesso per l'utente root
    Consenti l'accesso SSH all'utente root (utente amministrativo).

Consenti l'autenticazione mediante password
    Consente l'accesso SSH tramite l'autenticazione con password
    semplice. Se non abilitato, gli utenti si potranno autenticare
    solamente utilizzando una chiave crittografica.



===================
Dati organizzazione
===================

Questi campi contengono i valori di default per l'azienda.
I dati indicati verranno utilizzati come default durante la creazione
dei nuovi utenti.

Per ogni utente è possibile specificare valori diversi nel pannello
Utenti, scheda Dettagli.
La variazione di questi dati sostituisce i valori di default per gli
utenti che non hanno campi personalizzati.

.. note:: Ogni modifica ai dati inseriti rigenera il certificato SSL.

Azienda
    Inserire il nome dell'azienda.
Città
    Inserire la città dell'azienda.
Ufficio
    Inserire il dipartimento o ufficio i cui componenti avranno accesso
    ai servizi del server.
Telefono
    Inserire il numero di telefono dell'azienda.
Indirizzo
    Inserire l'indirizzo dell'azienda.


==============
Profilo utente
==============

Ogni utente può collegarsi al Server Manager utilizzando le proprie credenziali.

Dopo l'accesso, l'utente potrà :index:`cambiare la propria password` e le informazioni associate al proprio account:

* Nome e Cognome
* Indirizzo email esterno

L'utente può anche sovracrivere i seguenti campi già impostati dall'amministratore:

* Società
* Ufficio
* Indirizzo
* Città
* Telefono


.. _static_routes-section:

==============
Rotte statiche
==============

Il pannello consente di specificare instradamenti
particolari (:index:`rotte statiche`) che non facciano uso del default gateway (ad esempio per
raggiungere reti private collegate tramite linee dedicate o simili).

Se si desidera che gli host nella rete remota possano accedere ai servizi
del server, ricordarsi di creare una rete corrispondente nel pannello
:guilabel:`Reti fidate`.


Vedi :ref:`trusted_networks-section`.
