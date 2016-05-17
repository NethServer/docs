.. _users_and_groups-section:

===============
Utenti e gruppi
===============

|product| supporta autenticazione e autorizzazione su sorgenti remote o locali.

Le sorgenti supportate sono:

* LDAP: OpenLDAP eseguito su |product|
* Active Directory: Samba Active Directory che gira localmente (o in remoto) oppure una macchina Windows AD esistente

Dopo il wizard di prima configurazione, l'amministrazione può configurare la sorgente
di autenticazione dalla pagina :guilabel:`Utenti e gruppi`.
Se non è stato installato nessun pacchetto aggiuntivo, sarà possibile selezionare solo una sorgente remota.
Gli utenti e i gruppi che appartengono ad una sorgente remota non possono essere modificati
e sono configurati in *sola lettura*.

Dopo aver installato una sorgente locale (Samba Active Directory o OpenLDAP), sarà possibile
creare/modificare/eliminare utenti e gruppi locali.

OpenLDAP
========

Dal :guilabel:`Software Center` installare il pacchetto chiamato :guilabel:`Account provider: OpenLDAP`.
Al termine dell'installazione. il pacchetto sarà automaticamente configurato e l'amministratore
potrà gestire gli account dalla pagina :guilabel:`Utenti e gruppi`.


Samba Active Directory
======================

Quando si installa Samba Active Directory, il sistema richiede un indirizzo IP addizionale
che sarà l'indirizzo del controller Active Directory all'interno della LAN.

L'indirizzo aggiuntivo deve soddisfare tre condizioni:

* l'indirizzo IP deve essere nella subnet di una rete green
* la rete green deve essere configurata su interfaccia di tipo bridge
* l'indirizzo IP non deve essere usato da nessun'altra macchina nella LAN

Dal :guilabel:`Software Center` installare il pacchetto :guilabel:`Account provider: Samba Active Directory`.
Al termine dell'installazione, accedere alla pagina :guilabel:`Utenti e gruppi` e procedere
alla prima configurazione di Samba.
Inserire quindi l'indirizzo IP addizionale e premere il pulsante di salvataggio:
se necessario, il sistema creerà automaticamente un bridge sulla rete green.

Utenti e gruppi possono essere gestiti dalla pagina :guilabel:`Utenti e gruppi`.

Utenti predefiniti
------------------

Dopo aver installato Samba Active Directory, la pagina :guilabel:`Utenti e gruppi` contiene
l'utente predefinito :dfn:`administrator`.
Questo utente ha dei privilegi speciali su alcuni servizi specifici,
come aggiungere una workstation al dominio Samba.

La password di per l'utente administrator è: *Nethesis,1234*

.. tip:: Ricordarsi di cambiare la password dell'utente administrator al primo login.

Utenti
======

L'utente di sistema è necessario per accedere a molti servizi erogati da |product| (email, cartelle condivise etc.).
Ogni utente è caratterizzato da una coppia di credenziali (utente e password). 

I seguenti campi sono obbligatori per la creazione di un utente:

* Username
* Nome completo (nome e cognome)

Al termine della creazione, un utente risulta disabilitato fino a quando non viene impostata una password usando il pulsante
:guilabel:`Cambia password`.
Un utente bloccato non può utilizzare i servizi che richiedono autenticazione.
Quando un utente è abilitato, l'utente può accedere al Server Manager e cambiare la propria password: :ref:`user_profile-section`.

Un utente può essere aggiunto ad uno o più gruppi usando la pagina :guilabel:`Utenti` o :guilabel:`Groppi`.

A volte può essere necessario bloccare l'accesso ai servizi di un utente senza eliminare l'account.
E' possibile farlo usando i pulsanti :guilabel:`Blocca` e :guilabel:`Sblocca`.


.. note:: Quando utente viene eliminato, verranno eliminati anche tutti i dati dell'utente.

.. _users_services-section:

Accesso ai servizi
------------------

Dopo la creazione, un utente può essere abilito ad alcuni o tutti i servizi.
L'accesso deve essere effettuato usando il nome utente completo di dominio: `username@<domain>`.

Esempio:

* Dominio: nethserver.org
* Username: goofy

L'utente completo da utilizzare per l'accesso ai servizi è: `goofy@nethserver.org`.


.. _groups-section:

Gruppi
======

Un gruppo di utenti può essere usato per assegnare permessi speciali o per creare liste di distribuzione email.

Come gli utenti, un gruppo può essere abilitato ad alcuni (o tutti) i servizi.

.. tip:: Per delegare l'accesso al Server Manager è possibile
         utilizzare i gruppi ``administrators`` e ``managers``.

Si possono creare due gruppi speciali, gli utenti che appartengono a
questi gruppi ottengono dei permessi aggiuntivi alle pagine del Server
Manager.

* :dfn:`administrators`: Gli utenti di questo gruppo hanno gli stessi
  permessi di ``root``.

* :dfn:`managers`: Gli utenti di questo gruppo hanno l'accesso alle
  pagine della sezione *Gestione*.


Gestione password
=================

Il sistema prevede la possibilità di impostare dei vincoli sulla :dfn:`complessità` e la :dfn:`scadenza` delle password.
Le politiche di gestione password possono essere cambiate usando l'interfaccia web.

Complessità
-----------

La :index:`complessità password` è un insieme di condizioni minime che devono essere soddisfatte affinché la password venga accettata dal sistema: 
è possibile scegliere tra due differenti policy di gestione complessità delle password:

* :dfn:`none`: non viene fatto alcun controllo sulla password immessa se non sulla lunghezza di almeno 7 caratteri
* :dfn:`strong`

La policy :index:`strong` impone che la password debba rispettare le seguenti regole:

* lunghezza minima 7 caratteri
* contenere almeno 1 numero
* contenere almeno 1 carattere maiuscolo 
* contenere almeno 1 carattere minuscolo
* contenere almeno 1 carattere speciale
* contenere almeno 5 caratteri diversi
* non deve essere presente nei dizionari di parole comuni 
* deve essere diversa dallo username
* non può avere ripetizioni di pattern formati da più 3 caratteri (ad esempio la password As1.$As1.$ non è valida)
* se è installato Samba Active Directory, sarà abilitato anche lo storico delle password

La policy di default è :dfn:`strong`.

.. warning:: Cambiare le politiche predefinite è altamente sconsigliato. L'utilizzo di password deboli è la prima
   causa di compromissione dei server da parte di attaccanti esterni.

Scadenza
--------

La :index:`scadenza delle password` viene attivata di default a 6 mesi a partire dal momento in cui la password viene impostata.
Il sistema invierà una mail informativa all'utente quando la sua password è in scadenza.

.. note:: Al momento dell'attivazione il sistema farà riferimento alla data dell'ultimo cambio password, 
   se tale data è precedente più di 6 mesi, il server invierà una mail per segnalare che la password è scaduta. 
   In tal caso è necessario cambiare la password dell'utente.
   Ad esempio: se l'ultimo cambio password è stato fatto in gennaio, e l'attivazione della scadenza in ottobre, 
   il sistema riterrà la password cambiata in gennaio come scaduta, e lo segnalerà all'utente.


Effetti password scaduta
^^^^^^^^^^^^^^^^^^^^^^^^

Allo scadere della password l'utente sarà in grado di scaricare regolarmente la posta ma non potrà più accedere alle cartelle
e stampanti condivise sul server (Samba) o da altri pc in caso il pc faccia parte del dominio. 


Password di dominio
--------------------
In caso il sistema sia configurato come controller di Dominio, l'utente potrà cambiare la propria password usando gli strumenti di Windows.

In quest'ultimo caso non è possibile impostare password più corte di *6 caratteri* indipendentemente dalla configurazione
delle policy sul server. Infatti Windows esegue dei controlli preliminari e invia le password al server dove vengono poi valutate 
con le policy in uso.

Lingua notifiche
================

La lingua di default per le notifiche è l'inglese.
Se si desidera cambiarla, usare il seguente comando: ::

  config setprop sysconfig DefaultLanguage <lang>

Esempio per l'italiano: ::

  config setprop sysconfig DefaultLanguage it_IT.utf8


