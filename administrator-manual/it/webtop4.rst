=========
NethTop 4
=========

NethTop è un groupware completo che implementa il protocollo ActiveSync.

L'indirizzo per accedere all'interfaccia web è: ``https://<nome_server>/webtop``.

Autenticazione
==============

Interfaccia web
---------------

Il login all'applicazione web è sempre
effettuato usando utente semplice e password, a prescindere da quanti domini di posta siano configurati.

**Esempio**

* Nome server: mymail.mightydomain.com
* Dominio di posta alternativo: baddomain.net
* Utente: goofy
* Login: goofy

Active Sync
-----------

Il login ad Active Sync è invece <utente>@<dominio> dove ``<dominio>`` è il dominio del server che fa parte del FQDN.

**Esempio**

* Nome server: mymail.mightydomain.com
* Dominio di posta alternativo: baddomain.net
* Utente: goofy
* Login: goofy@mightydomain.com

Quando si configura un account Active Sync, assicurarsi di specificare l'indirizzo del server
e lasciare vuoto il campo dominio.

.. note::
   Il protocollo Active Sync è supportato solo su dispositivi Android e iOS.
   Outlook non è supportato.
   

.. _webtop_admin-section:

Utente admin
------------

Dopo l'installazione, NethTop è accessibile con un utente amministrativo.
L'utente amministrativo può cambiare le impostazioni globali ed effettuare login come un altro utente,
ma non è un utente di sistema e non può accedere agli altri servizi come Mail, Calendario, ecc.

Le credenziali di default sono:

* Utente: admin
* Password: admin

La password del'utente admin deve essere cambiata dall'interfaccia di NethTop.

.. warning::
   E' fortemente consigliato cambiare la password di admin dopo l'installazione.

E' possibile controllare la posta dell'utente admin di sistema usando questo login: 
admin@<dominio> dove ``<dominio>`` è il dominio del server che fa parte del FQDN.

**Esempio**

* Nome server: mymail.mightydomain.com
* Utente: admin
* Login: admin@mightydomain.com

NethTop vs SOGo
===============

NethTop e SOGo possono essere installati sullo stesso server.

ActiveSync è abilitato di default sia su SOGo che su NethTop, ma se sono entrambi
installati, SOGo avrà la precedenza.

Per disabilitare ActiveSync su SOGo: ::

  config setprop sogod ActiveSync disabled
  signal-event nethserver-sogo-update

Per disabilitare ActiveSync su NethTop: ::

  config setprop webtop ActiveSync disabled
  signal-event nethserver-webtop4-update

 
Tutti i filtri di posta configurati da SOGo, devono essere ricreati manualmente all'interno
dell'interfaccia di NethTop.
La stessa cosa si applica se l'utente sta effettuando il passaggio inverso da NethTop a SOGo.

Autenticazione Active Directory
===============================

Dopo aver eseguito il join al dominio Active Directory, accedere alla pagina di amministrazione
di WebTop, dall'albero di sinistra selezionare :guilabel:`Domini` -> :guilabel:`NethServer`.

Modificare i campi nella pagina come segue:

* Authentication Uri: selezionare la modalità ``ldapAD`` e indicare il nome FQDN completo del server e la porta 389.
  Esempio: w2k8.nethserver.org:389

* Admin Ldap: nome dell'utente amministratore del dominio AD

* Password Ldap: password dell'utente amministratore del dominio AD

Dopo il salvataggio, nella pagina :guilabel:`Utenti` saranno visualizzati gli utenti di Active Directory.


Importazione dati da SOGo
=========================

E' possibile migrare alcuni dati da SOGo a WebTop utilizzando i seguenti script:

* calendari: :file:`/usr/share/webtop/doc/sogo2webtop_cal.php`
* rubriche: :file:`/usr/share/webtop/doc/sogo2webtop_card.php`

Prima di utilizzare gli script è necessario installare questo pacchetto: ::

  yum install php-mysql -y


Entrambi gli script vanno eseguiti indicando il nome utente di cui si vuole eseguire l'importazione da SOGo: :: 
 
  php /usr/share/webtop/doc/sogo2webtop_cal.php <user>
  php /usr/share/webtop/doc/sogo2webtop_card.php <user>

Dove ``user`` può essere un nome utente oppure ``all``.

**Esempi**

Importare tutte le rubriche presenti su SOGo: ::

  php /usr/share/webtop/doc/sogo2webtop_card.php all

Importare il calendario dell'utente "pippo": ::
 
  php /usr/share/webtop/doc/sogo2webtop_cal.php pippo


.. note::
   Se lo script viene eseguito più volte verranno importati più volte sia calendari che rubriche.
   Attualmente non è supportata l'importazione sia delle liste di distribuzione dalle 
   rubriche che degli eventi ricorrenti dai calendari.

Importazione email, calendari e contatti da PST
===============================================

E' possibile importare email e successivamente anche calendari e rubriche da un archivio :index:`PST` :index:`Outlook`.

Script iniziale per esportazione dati da PST e importazione email: :file:`/usr/share/webtop/doc/pst2webtop.sh`

Prima di utilizzare lo script installare questo pacchetto: ::

   yum install libpst -y

Eseguire lo script indicando il file PST e l'utente di sistema in cui importare le email: ::

   /usr/share/webtop/doc/pst2webtop.sh <filename.pst> <user>

Il contenuto del file PST verrà esportato e inserito in una cartella temporanea.
Alla fine dell'importazione verranno elencati i comandi per eseguire le eventuali importazioni di calendari e contatti.

Script importazione Contatti: :file:`/usr/share/webtop/doc/pst2webtop_card.php`

In base ai Contatti trovati durante l'esportazione dello script iniziale utilizzare lo script in questo modo: ::

   /usr/share/webtop/doc/pst2webtop_card.php <user> <file_to_import> <foldername>
   
**Esempio**

Ipotizziamo che lo script precedente (pst2webtop.sh) abbia esportato dal file PST questi Contatti: ::

   Contacts Folder found: Cartelle personali/Contatti/contacts
    Import to webtop:
   ./pst2webtop_card.php pippo '/tmp/tmp.0vPbWYf8Uo/Cartelle personali/Contatti/contacts' <foldername>
   
Per importare nella Rubrica predefinita (WebTop) dell'utente pippo: ::

   /usr/share/webtop/doc/pst2webtop_card.php pippo '/tmp/tmp.0vPbWYf8Uo/Cartelle personali/Contatti/contacts' WebTop
   
Script importazione Calendari: :file:`/usr/share/webtop/doc/pst2webtop_cal.php`

In base ai Calendari trovati durante l'esportazione dello script iniziale utilizzare lo script in questo modo: ::

   /usr/share/webtop/doc/pst2webtop_cal.php <user> <file_to_import> <foldername>
   
**Esempio**

Ipotizziamo che lo script precedente (pst2webtop.sh) abbia esportato dal file PST questo Calendario: ::

   Events Folder found: Cartelle personali/Calendario/calendar
    Import to webtop:
   ./pst2webtop_cal.php pippo '/tmp/tmp.0vPbWYf8Uo/Cartelle personali/Calendario/calendar' <foldername>
   
Per importare nel Calendario predefinito (WebTop) dell'utente pippo: ::

   /usr/share/webtop/doc/pst2webtop_cal.php pippo '/tmp/tmp.0vPbWYf8Uo/Cartelle personali/Calendario/calendar' WebTop

.. note::
   Lo script importa gli eventi utilizzando il fuso orario dall'utente WebTop, se configurato.
   Altrimenti verrà utilizzato il fuso orario del sistema.

Integrazione Google e Dropbox
=============================

Ogni utente può integrare i propri account Google Drive e Dropbox all'interno di WebTop.
Prima di procedere, l'amministratore deve creare una coppia di credenziali per l'accesso
alle API.

API Google
----------

* Accedere a https://console.developers.google.com/project e creare un nuovo progetto
* Creare una nuova coppia di credenziali di tipo "OAuth 2.0 clientID" avendo cura di 
  compilare la sezione "OAuth consent screen"
* Inserire la coppia di credenziali appena create (Client ID e Client Secret) nella 
  configurazione di WebTop

  Da shell accedere al database webtop: ::

    su - postgres -c "psql webtop"

  Eseguire le query, sostituendo al campo ``__value__`` il corrispettivo valore: ::

    INSERT INTO settings (idsetting,value) VALUES ('main.googledrive.clientid', '__value__');
    INSERT INTO settings (idsetting,value) VALUES ('main.googledrive.clientsecret', '__value__');

API Dropbox
-----------

* Accedere a https://www.dropbox.com/developers/apps e creare una nuova app
* Inserire la coppia di credenziali appena create (App key e App secret) nella
  configurazione di WebTop.

  Da shell accedere al database webtop: ::

    su - postgres -c "psql webtop"

  Eseguire le query, sostituendo al campo ``__value__`` il corrispettivo valore: ::

    INSERT INTO settings (idsetting,value) VALUES ('main.googledrive.clientsecret', '__value__');
    INSERT INTO settings (idsetting,value) VALUES ('main.dropbox.appsecret', '__value__');


Se si desidera cambiare il limite massimo di utenti, verificare la procedura corretta nella
documentazione ufficiale di Dropbox.

.. note::
   La versione Enteprise è già integrata con Google e Dropbox.

