.. _ups-section:

====
UPS
====

|product| supporta la gestione di :index:`UPS` (Uninterruptible Power Supply) collegati al sistema.

Il server può essere configurato in due modalità:

* *master*: l'UPS è direttamente collegato al server, il server accetta connessioni dagli slave
* *slave*: l'UPS è collegato ad un altro server raggiungibile via rete

.. note:: Si consiglia di consultare la lista dei modelli supportati prima dell'acquisto. Installare il pacchetto UPS da *Amministrazione > Software center*. In *Configurazione* appare la nuova voce di menù *UPS* dove si può trovare il dispositivo supportato inserendo il modello all'interno del campo di ricerca *Cerca driver per modello*.

Nella modalità :index:`master`, l'UPS può essere collegato al server:

* su una porta seriale
* su una porta USB
* con un adattatore da USB a seriale

Nella modalità :index:`slave` sarà necessario fornire l'indirizzo IP del server
master.

La configurazione di default prevede uno spegnimento controllato in caso di assenza di
alimentazione. 


Device personalizzato
=====================

Se l'UPS è collegato ad una porta non elencata nell'interfaccia web, è possibile configurare un device personalizzato con i seguenti comandi: ::

 config setprop ups Device <your_device>
 signal-event nethserver-nut-save

Statistiche UPS
===============

Se il modulo statistiche (collectd) è installato e funzionante, il modulo raccoglierà automaticamente statistiche sullo stato dell'UPS.

