========
WebTop 4
========

WebTop è un groupware completo che implementa il protocollo ActiveSync.

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
   La sincronizzazione della posta non è attualmente supportata.
   

.. _webtop_admin-section:

Utente admin
------------

Dopo l'installazione, WebTop è accessibile con un utente amministrativo.
L'utente amministrativo può cambiare le impostazioni globali ed effettuare login come un altro utente,
ma non è un utente di sistema e non può accedere agli altri servizi come Mail, Calendario, ecc.

Le credenziali di default sono:

* Utente: admin
* Password: admin

La password del'utente admin deve essere cambiata dall'interfaccia di WebTop.

.. warning::
   E' fortemente consigliato cambiare la password di admin dopo l'installazione.

E' possibile controllare la posta dell'utente admin di sistema usando questo login: 
admin@<dominio> dove ``<dominio>`` è il dominio del server che fa parte del FQDN.

**Esempio**

* Nome server: mymail.mightydomain.com
* Utente: admin
* Login: admin@mightydomain.com

WebTop vs SOGo
==============

WebTop e SOGo possono essere installati sullo stesso server.

ActiveSync è abilitato di default sia su SOGo che su WebTop, ma se sono entrambi
installati, SOGo avrà la precedenza.

Per disabilitare ActiveSync su SOGo: ::

  config setprop sogod ActiveSync disabled
  signal-event nethserver-sogo-update

Per disabilitare ActiveSync su WebTop: ::

  config setprop webtop ActiveSync disabled
  signal-event nethserver-webtop4-update

 
Tutti i filtri di posta configurati da SOGo, devono essere ricreati manualmente all'interno
dell'interfaccia di WebTop.
La stessa cosa si applica se l'utente sta effettuando il passaggio inverso da WebTop a SOGo.

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
