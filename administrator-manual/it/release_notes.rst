==========================
Note di rilascio |release|
==========================

|product| versione |release|

.. include:: changelog.rst.inc


Aggiornamento manuale da 6.6
============================

E' possibile aggiornare il sistema da riga di comando.

1. Assicurarsi che il sistema attuale sia aggiornato: ::

     yum update

2. Installare la nuova versione del pacchetto ``nethserver-release``: ::

     yum localinstall http://mirror.nethserver.org/nethserver/nethserver-release-6.7.rpm

3. Pulire la cache di YUM e aggiornare di nuovo il sistema: ::

     yum clean all && yum update

4. Infine, riavviare il sistema (opzionale).

