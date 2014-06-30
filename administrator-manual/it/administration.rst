===============
Amministrazione
===============

Dashboard
=========

La pagina mostrata di default dopo il login è la index:`Dashboard`; qui viene
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

Tutti i servizi registrano le operazioni svolte all'interno di file detti :dfn:`log`.
L'analisi dei :index:`log` è lo strumento principale per individuare malfunzionamenti e problemi.
Per visualizzare i file di log fare clic su :menuselection:`Visualizza Log`.
Si aprirà una pagina con l'elenco di tutti i file di log disponibili; fare click sui file che si intendo visualizzare.

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

E' possibile specificare reti a cui sia esplicitametne consentito l'accesso al Server Manager.
Ad esempio, se il server è presso un cliente, si consiglia di permettere il collegamento dalla rete
remota da cui si voglia amministrare la macchina.

SSH
---

Si consiglia di mantenere sempre attivo il servizio :index:`SSH` (Secure Shell).
SSH è un protocollo per aprire una shell remota usando connessioni cifrate.

La configurazione di default consente l'autenticazione via password e mediante chiave pubblica/privata.



===================
Dati organizzazione
===================

I campi in questa sezione vengono utilizzati per la generazione dei certificati
SSL auto-firmati e per la creazione degli utenti.

.. note:: Ogni modifica ai dati inseriti rigenera tutti i certificati SSL, peranto sarà necessario
   accettarli nuovamente nei client già configurati (es. client posta e browser).


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
