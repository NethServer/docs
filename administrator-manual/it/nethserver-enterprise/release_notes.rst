================
Note di rilascio
================

|product| versione |release|

.. include:: changelog.rst.inc

Aggiornamento da 6.7
====================

L'aggiornamento da 6.7 a 6.8 è automatico e verrà rilasciato gradualmente.

Qualora si desideri forzare l'aggiornamento manualmente seguire la procedura qui descritta.

Aggiornamento manuale
---------------------

1. Assicurarsi che il sistema attuale sia aggiornato: ::

     yum update

2. Installare la nuova versione del pacchetto ``nethserver-release``: ::

     yum localinstall http://mirror.nethserver.org/nethserver/nethserver-release-6.rpm

3. Abilitare solo i repository enterprise: ::

     /etc/cron.daily/00fixyumrepos

4. Pulire la cache di YUM e aggiornare di nuovo il sistema: ::

     yum clean all && yum update

5. Infine, riavviare il sistema (opzionale).

