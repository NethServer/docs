
.. index::
   single: interfaccia web
   single: Server Manager

.. _access-section:
   
=========================
Accesso al Server Manager
=========================

|product| viene configurato tramite una *interfaccia web*, detta :dfn:`Server Manager`.
Per accedere alle pagine di gestione si utilizza un browser (es. FireFox, Google Chrome, etc)
installato su un PC connesso alla stessa rete LAN del server.

Nella barra degli indirizzi digitare: ``https://a.b.c.d:980`` oppure ``https://server:980`` dove *a.b.c.d* 
e *server* sono rispettivamente l'indirizzo IP e il nome del server
impostati al momento dell’installazione.

Se il modulo web server è installato, l'interfaccia web è raggiungibile anche all'indirizzo: ``https://server/server-manager``

Il Server Manager utilizza certificati SSL auto-firmati, sarà quindi necessario
accettare esplicitamente tali certificati la prima volta che si accede al server.
La connessione è comunque sicura e cifrata.

Login
=====

Prima di accedere, è necessario autenticarsi attraverso nome utente e password.
Compilare i campi come segue:

* :index:`Nome utente di default`: **root**
* :index:`Password di default`: **Nethesis,1234**

.. warning:: Cambiare la password di root appena possibile,
             scegliendone una sicura, che sia composta da una sequenza
             casuale di lettere maiuscole, minuscole e da numeri e
             simboli.
  
Se è installato il pacchetto nethserver-directory, utilizzato dai moduli che abilitano la 
gestione utenti come File server o Mail, viene attivata nella Dashboard l'interfaccia di 
gestione :ref:`users_and_groups-section` dalla quale è possibile abilitare l'utente admin ed utilizzarlo 
per accedere all'interfaccia web con gli stessi privilegi dell'utente root. 
Vedi :ref:`admin_user-section`.
