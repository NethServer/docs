========
WebTop 4
========

WebTop è un groupware completo che implementa il protocollo Active Sync.

L'indirizzo per accedere all'interfaccia web è: ``http://<server_name>/webtop``.

.. note::
   WebTop e SOGo non possono essere installati sulla stessa macchina.
   Prima di installare WebTop, assicurarsi che SOGo non sia presente.

.. warning::
   E' fortemente consigliato cambiare la password di admin dopo l'installazione. Vedi :ref:`webtop_admin-section`.

Autenticazione
==============

Non importa quanti domini di posta siano configurati, il login all'applicazione web è sempre
effettuato con utente semplice e password.

Il logint ad Active Sync è invece <utente>@<dominio> dove dominio è il dominio del server.

**Esempio**

* Nome server: mymail.mightydomain.com
* Dominio di posta alternativo: baddomain.net
* Utente: goofy

Login all'applicazione web: goofy

Login Active Sync: goofy@mightydomain.com

.. _webtop_admin-section:

Utente admin
------------

Dopo l'installazione, WebTop è accessibile con un utente amministrativo.
Le credenziali sono:

* Utente: admin
* Password: admin

La password del'utente admin può essere cambiata con questo comando: ::

    su - postgres -c "psql webtop -c \"UPDATE users set password='_your_password_' WHERE login='admin'\";" 

