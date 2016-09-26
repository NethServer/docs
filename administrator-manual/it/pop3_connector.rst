
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
* se un messaggio va eliminato dal server remoto dopo la consegna,
* se il messaggio scaricato deve essere sottoposto ai controlli antispam e antivirus

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
   pair: Getmail; software

L'implementazione sottostante è basata su :dfn:`Getmail`
[#Getmail]_.  Dopo aver scaricato i messaggi dal provider POP3/IMAP,
Getmail applica tutti i filtri richiesti, quindi consegna 
il messaggio localmente.
I messaggi vengono filtrati in base alle
:ref:`regole configurate <email_filter>`.

Tutte le operazioni di download sono riportate nel file :file:`/var/log/maillog`.

.. warning:: Se un account scelto per la consegna viene eliminato in un secondo
             momento, la configurazione diventa inconsistente.  La
             configurazione dell'account esistente nella pagina
             :guilabel:`Connettore POP3` deve essere disabilitata o
             eliminata.

.. rubric:: Riferimenti

.. [#Getmail] Getmail is a remote-mail retrieval utility http://pyropus.ca/software/getmail/

