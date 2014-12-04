.. index:: migrazione

.. _migration-section:

=====================================
Migrazione da NethService/SME Server
=====================================

La :index:`migrazione` è il processo che consente di convertire
un'installazione SME Server/NethService (:dfn:`origine`) in un
nuovo server |product| (:dfn:`destinazione`).

#. Sulla macchina origine, effettuare un backup completo e spostarlo
   sul server destinazione.

#. Sul server destinazione, installare tutti i moduli che implementano
   i servizi presenti sulla macchina origine.

#. Estrarre il backup in una directory; per esempio, creare la
   directory :file:`/var/lib/migration`.

#. Iniziare il processo di migrazione::

      signal-event migration-import /var/lib/migration

   Questa operazione potrebbe richiedere molti minuti.

#. Consultare il log di sistema :file:`/var/log/messages` ed
   assicurarsi che non si siano verificati errori::
 
     grep -E '(FAIL|ERROR)' /var/log/messages

.. note:: Nessun template custom sarà migrato durante il processo di migrazine.
   Controllare i nuovi template prima di copiare frammenti personalizzati dal vecchio backup.

.. index::
   pair: migrazione; email

Email
=====

Prima di mettere |product| in produzione, vanno fatte alcune
considerazioni sulla configurazione esistente della rete e dei client
di posta elettronica: quali porte sono in uso, se vengono utilizzati
SMTPAUTH e TLS.  Per maggiori informazioni, fare riferimento alle
sezioni :ref:`email_clients` e :ref:`email_policies`.

Nella migrazione di un server di posta, il server di origine può
essere in produzione anche dopo che il backup è stato fatto, e nuovi
messaggi di posta continuano ad essere consegnati finché non viene
spento definitivamente.

Uno script ``rsync`` di aiuto è fornito dal pacchetto
``nethserver-mail-server``, per ri-sincronizzare le caselle di posta
di destinazione con il server di
origine. :file:`/usr/share/doc/nethserver-mail-server-<VERSION>/sync_maildirs.sh`.
Lo script gira sul server di destinazione: ::

  Usage: 
    ./sync_maildirs.sh [-h] [-n] [-p] -s IPADDR 
	-h          help message
	-n          dry run
	-p PORT     ssh port on source host (default 22)
	-s IPADDR   rsync from source host IPADDR

Il server di origine con indirizzo ``IPADDR`` deve essere accessibile
dall'utente ``root``, mediante ``ssh`` con autenticazione a chiave
pubblica.
