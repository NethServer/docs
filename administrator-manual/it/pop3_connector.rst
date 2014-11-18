===============
Connettore POP3
===============

Il modulo :index:`connettore POP3` permette di configurare un elenco
di account di posta elettronica che il server scarica ad intervalli
regolari, consegnando le email agli utenti o gruppi locali.

.. note:: Si sconsiglia di utilizzare il connettore POP3 come metodo
   primario di gestione della posta elettronica, perché vincola al
   provider, con i relativi problemi di spazio sulla casella,
   disservizi dell'accesso pop3.  Inoltre l'efficacia dei filtri
   antispam viene ridotta perché si perdono le informazioni sulla
   provenienza diretta della mail.

Il server utilizza il software :index:`fetchmail` che scarica le mail
in POP3 dal provider e le consegna localmente collegandosi
direttamente al servizio SMTP locale, provvedendo al filtraggio dei
messaggi. Vedi :index:`mail_filter-section`.  E' possibile creare un
numero illimitato di account esterni associati ad un gruppo o un
utente di sistema.

Tutte le operazioni di download sono salvate nel file
:file:`/var/log/fetchmail.log`.

.. note:: L'eliminazione di un account *non* comporta l'eliminazione
          dei messaggi già consegnati.

