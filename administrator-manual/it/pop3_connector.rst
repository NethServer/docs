
.. _pop3_connector-section:

===============
Connettore POP3
===============

La pagina :guilabel:`Connettore POP3` permette di configurare un
elenco di account di posta elettronica che il server scarica ad
intervalli di tempo regolari, consegnando le email agli utenti o
gruppi locali.

Si sconsiglia di utilizzare il connettore POP3 come metodo primario di
gestione della posta elettronica, perché vincola al provider, con i
relativi problemi di spazio sulla casella, disservizi dell'accesso
POP3.  Inoltre l'efficacia dei filtri antispam viene ridotta perché
non sono più disponibili le informazioni sulla provenienza diretta
della mail (SMTP envelope).

Gli account POP3/IMAP sono configurati dalla pagina :guilabel:`POP3
connector > Indirizzi esterni`. Per ogni account possono essere
specificati:

* l'indirizzo email (come identificativo per l'account),
* il protocollo (IMAP/POP3),
* l'indirizzo del server remoto,
* le credenziali dell'account,
* l'utente o il gruppo locale dove consegnare i messaggi,
* se SSL va disabilitato (sconsigliato),
* se un messaggio va eliminato dal server remoto dopo la consegna.

.. note:: È possibile creare un numero illimitato di account esterni
          associati ad un gruppo o un utente di sistema.
          L'eliminazione di un account *non* comporta l'eliminazione
          dei messaggi già consegnati.

Dopo aver completato la configurazione degli account, il modulo
Connettore POP3 va attivato esplicitamente dalla pagina
:guilabel:`Connettore POP3 > Generale`. Nella stessa pagina si può
impostare ogni quanto controllare la presenza di messaggi nel server
remoto, dal menù :guilabel:`Controlla ogni`.

.. index::
   pair: Fetchmail; software

L'implementazione sottostante è basata su :dfn:`Fetchmail`
[#Fetchmail]_.  Dopo aver scaricato i messaggi dal provider POP3/IMAP,
Fetchmail li consegna localmente connetendosi direttamente al filtro
di posta locale.  I messaggi vengono filtrati in base alle
:ref:`regole configurate <email_filter>`.

Tutte le operazioni di download sono riportate nei seguenti file:

* :file:`/var/log/fetchmail.log`
* :file:`/var/log/maillog`

.. rubric:: Riferimenti

.. [#Fetchmail] Fetchmail è una programma per ricevere e inoltrare la
                posta remota http://www.fetchmail.info/

