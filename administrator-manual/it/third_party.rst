====================
Third-party software
====================

E' possibile installare su |product| qualsiasi :index:`software di terze parti` certificato per CentOS/RHEL.

Se il software è disponibile solo a 32 bit, è necessario installare le librerie di compatibilità prima del software stesso.
Alcune librerie possibili:

* glibc
* glib
* libstdc++
* zlib

Ad esempio, per installare questi pacchetti usare il comando: ::

 yum install glibc.i686 libgcc.i686 glib2.i686 libstdc++.i686 zlib.i686

Installazione
-------------

Se il software è distribuito con un pacchetto RPM, si consiglia di usare il comando :command:`yum` per l'installazione: il sistema
si occuperà di risolvere e installare tutte le dipendenze necessarie.

In caso l'installazione con yum non sia possibile, la directory più corretta in cui installare il software è :file:`/opt`.
Per esempio, dato il software chiamato *mysoftware*, installare nella directory :file:`/opt/mysoftware`.

Backup
------

Le directory che contengono dati rilevanti devono essere incluse nel backup aggiungendo una linea al file :file:`/etc/backup-data.d/custom.include`.
Vedi :ref:`backup_customization-section`.

Firewall
--------

Se il software necessita di porte aperte sul firewall, creare un servizio chiamato ``fw_<softwarename>``.

Ad esempio, dato il software *mysoftware* che necessita la porta 3344 aperta sulla LAN, usare questi comandi: ::

 config set fw_mysoftware service status enabled TCPPorts 8090,8443,5632,5432 access private
 signal-event firewall-adjust
 signal-event runlevel-adjust

Avvio e arresto
---------------

|product| usa il runlevel standard 5.

Il software installato con yum dovrebbe già essere configurato per partire nel runlevel 5.
Per controllare la configurazione, eseguire il comando :command:`chkconfig`. Il comando mostra una lista dei servizi con la relativa configurazione.

Per abilitare un servizio al boot: ::

  chkconfig mysoftware on

Per disabilitare un servizio al boot: ::
  
  chkconfig mysoftware off

