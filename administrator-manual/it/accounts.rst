.. _users_and_groups-section:

===============
Utenti e gruppi
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

.. _users_services-section:

Accesso ai servizi
------------------

Dopo la creazione, un utente può essere abilito ad alcuni o tutti i servizi.
La configurazione può essere fatta dalla sezione :guilabel:`Servizi`.


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
  permessi di ``root`` e ``admin``.

* :dfn:`managers`: Gli utenti di questo gruppo hanno l'accesso alle
  pagine della sezione *Gestione*.


.. _admin_user-section:

Utente admin
============

La pagina :guilabel:`Utenti` ha un elemento di default:
:dfn:`admin`. Questo account consente di accedere al Server Manager
con gli stessi permessi dell'utente :dfn:`root`.  Inizialmente è
*disabilitato* e non ha accesso dalla console.

.. tip:: Per abilitare l'account ``admin`` impostare la sua password.

Dove possibile, l'utente ``admin`` ha dei privilegi speciali su alcuni
servizi specifici, come :ref:`aggiungere una workstation al dominio
Samba <samba_pdc>`.


Gestione password
=================

Il sistema prevede la possibilità di impostare dei vincoli sulla :dfn:`complessità` e la :dfn:`scadenza` delle password.

Le politiche di gestione password possono essere cambiate usando l'interfaccia web dopo aver installato il modulo ``nethserver-password``.

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

.. warning:: Cambiare le politiche predefinite è altamente sconsigliato. L'utilizzo di password deboli è la prima
   causa di compromissione dei server da parte di attaccanti esterni.

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

Notification language
=====================

La lingua di default per le notifiche è l'inglese.
Se si desidera cambiarla, usare il seguente comando: ::

  config setprop sysconfig DefaultLanguage <lang>

Esempio per l'italiano: ::

  config setprop sysconfig DefaultLanguage it_IT.utf8


Importazione utenti
===================

E' possibile importare una lista di utenti a partire da un file CSV.
Il file deve contenere una linea per utente, ogni linea deve avere i campi separati da TAB, rispettando il seguente formato: ::

 username    firstName    lastName    email    password

Esempio: ::

 mario  Mario   Rossi   mario@example.org       112233


Assicurarsi che il modulo server di posta sia installato, quindi eseguire il comando: ::

  /usr/share/doc/nethserver-directory-<ver>/import_users <youfilename>

Per esempio, se il file che contiene gli utenti si chiama :file:`/root/users.csv`, eseguire: ::

  /usr/share/doc/nethserver-directory-`rpm --query --qf "%{VERSION}" nethserver-directory`/import_users /root/users.csv

Il comando può essere eseguito più volte: gli utenti esistenti saranno saltati.

.. note:: Il comando fallisce se il modulo del server di posta non è installto.

