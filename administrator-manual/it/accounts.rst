.. _users_and_groups-section:

===============
Utente e gruppi
===============

Utenti
======

L'utente di sistema è necessario per accedere a molti servizi erogati da |product| (email, cartelle condivise etc.).
Ogni utente è caratterizzato da una coppia di credenziali (utente e password). 

I seguenti campi sono obbligatori per la creazione di un utente:

* Username
* Nome
* Cognome

Campi opzionali:

* Società
* ufficio
* Indirizzo
* Città
* Telefono

Al termine della creazione, un utente risulta disabilitato fino a quando non viene settata una password usando il pulsante
:guilabel:`Cambia password`.
Un utente bloccato non può utilizzare i servizi che richiedono autenticazione.
Quando un utente è abilitato, l'utente può accedere al Server Manager e cambiare la propria password: :ref:`user_profile-section`.

Un utente può essere aggiunto ad uno o più gruppi usando la pagina :guilabel:`Utenti` o :guilabel:`Groppi`.

A volte può essere necessario bloccare l'accesso ai servizi di un utente senza eliminare l'account.
E' possibile farlo usando i pulsanti :guilabel:`Blocca` e :guilabel:`Sblocca`.


.. note:: Quando utente viene eliminati, verranno eliminati anche tutti i dati dell'utente.

Accesso ai servizi
------------------

Dopo la creazione, un utente può essere abilito ad alcuni o tutti i servizi.
La configurazione può essere fatta dalla sezione :guilabel:`Servizi`.

Gruppi
======

Un gruppo di utenti può essere usato per assegnare permessi speciali o per creare liste di distribuzione email.

Come gli utenti, un gruppo può essere abilitati ad alcuni o tutti i servizi.


.. _admin-user:

Utente amministratore
=====================

Il modulo :guilabel:`Utenti` crea l'utente :dfn:`admin` che consente l'accesso all'interfaccia web con la stessa password dell'utente :dfn:`root`.
L'utente :index:`admin` non ha accesso al sistema da linea di comando.
Pur essendo due utenti distinti, la password di entrambi coincide ed è possibile modificarla dall'interfaccia web.

In alcune occasioni, potrebbe essere utile differenziare le password di admin e di root, per esempio, per consentire ad un utente poco esperto 
di utilizzare l'interfaccia web per svolgere le operazioni più comuni, inibendo però l'accesso alla linea comandi.

Per dissociare la password di :index:`root` da quella di admin eseguire il seguente comando::

 config set AdminIsNotRoot enabled

Successivamente cambiare la password di admin dal pannello :guilabel:`Utenti`. Non venendo più sincronizzate le password, 
admin avrà la nuova password, mentre root manterrà la vecchia.

Se si desidera modificare la password di root, andrà fatto da linea di comando tramite il comando :command:`passwd`.



Gestione password
=================

Il sistema prevede la possibilità di impostare dei vincoli sulla :dfn:`complessità` e la :dfn:`scadenza` delle password.


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

La policy di default è :dfn:`strong`.

Per cambiare l'impostazione a none::
 
  config setprop passwordstrength Users none

Per cambiare l'impostazione a strong::
 
  config setprop passwordstrength Users strong

Verificare la policy attualmente in uso sul server::

 config getprop passwordstrength Users

Scadenza
--------

La :index:`scadenza delle password` viene attivata di default a 6 mesi a partire dal momento in cui la password viene impostata.
Il sistema invierà una mail informativa all'utente quando la sua password è in scadenza.

.. note:: Al momento dell'attivazione il sistema farà riferimento alla data dell'ultimo cambio password, 
   se tale data è precedente più di 6 mesi, il server invierà una mail per segnalare che la password è scaduta. 
   In tal caso è necessario cambiare la password dell'utente.
   Ad esempio: se l'ultimo cambio password è stato fatto in gennaio, e l'attivazione della scadenza in ottobre, 
   il sistema riterrà la password cambiata in gennaio come scaduta, e lo segnalerà all'utente.

Per ignorare la scadenza password globalmente (consentire l'accesso anche ad utenti con password scaduta)::

 config setprop passwordstrength PassExpires no
 signal-event password-policy-update

Per disabilitare la scadenza password su un utente (sostituire username con l'utente)::

 db accounts setprop <username> PassExpires no
 signal-event password-policy-update


Di seguito sono riportati i comandi per visualizzare le policy in uso.

Numero massimo di giorni per cui è possibile tenere la stessa password (default:180)::

 config getprop passwordstrength MaxPassAge


Numero minimo di giorni per cui si è costretti a tenere la stessa password (default 0)::

 config getprop passwordstrength MinPassAge


Numero di giorni in cui viene inviato il warning per email (default:7)::

 config getprop passwordstrength PassWarning


Per modificare i parametri sostituire al comando :command:`getprop` il comando :command:`setprop` e 
specificare in fondo alla riga il valore desiderato del parametro, infine dare il comando::

 signal-event password-policy-update

per rendere effettive le modifiche.

Ad esempio per modificare a 5 il "Numero di giorni in cui viene inviato il warning per email"::

 config setprop passwordstrength PassWarning 5
 signal-event password-policy-update



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

