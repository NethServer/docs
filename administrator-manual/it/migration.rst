=====================================
Migrazione da NethService/SME Server
=====================================

La :index:`migrazione` è il processo che consente di convertire un'installazione SME Server (o NethService)
in un nuovo server |product|.

#. Sulla vecchia macchina, effettuare un backup completo e spostarlo sul nuovo server in cui è stato installato |product|.
#. Sul nuovo server, installare tutti i moduli che implementano i servizi presenti sulla vecchia macchina.
#. Estrarre il backup in una directory, ad esempio :file:`/var/lib/migration`.
#. Iniziare il processo di migrazione::

    # signal-event migration-import /var/lib/migration

   Questa operazione potrebbe richiedere molti minuti.

#. Consultare il log di sistema :file:`/var/log/messages` ed assicurarsi che non si siano verificati errori::
 
    # grep ERROR /var/log/messages

