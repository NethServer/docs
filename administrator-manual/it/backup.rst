======
Backup
======

L’attività di :index:`backup` è fondamentale perché in caso di malfunzionamenti o
guasti del sistema assicura il salvataggio e la conservazione dei dati.
Il sistema gestisce due tipi di backup:

* :index:`backup della configurazione`
* :index:`backup dei dati`

Il backup della configurazione contiene tutte e sole le configurazioni di sistema.
Viene eseguito automaticamente ogni notte e genera un nuovo archivio, :file:`/var/lib/nethserver/backup/backup-config.tar.xz`, solo in caso la configurazione sia cambiata nelle ultime 24 ore.
Lo scopo del backup della configurazione è quello di consentire un rapido ripristino della macchina in caso di disaster recovery.
Dopo aver ripristinato la configurazione, la macchina può già essere messa in produzione mentre i dati vengono ripristinati in background.

Il backup dei dati è abilitato installando il modulo "Backup" e comprende i dati degli utenti come caselle di posta e cartelle condivise. 
Viene eseguito ogni notte e può essere completo o incrementale su base settimanale.
Questo backup contiene anche il backup della configurazione.

Il backup dei dati può essere fatto su tre tipi di destinazione:

* USB: disco collegato via USB, utile in caso di molti dati ma limitato dalla velocità dell'USB
* CIFS: cartella condivisa Windows, disponibile su tutti i NAS  
* NFS: cartella condivisa Linux, disponibile su tutti i NAS, solitamente più veloce di CIFS


L'esito del backup può essere notificato all'amministratore o ad un indirizzo mail esterno.

.. note:: La directory di destinazione è basta sul nome host del server:
   in caso di cambio FQDN, l'amministratore dovrà occuparsi di spostare manualmente
   i dati del backup dalla vecchia alla nuova directory.


Ripristino dati
===============

Assicurarsi che la destinazione contenente il backup sia raggiungibile (es. disco USB collegato).

.. note:: Al momento non è ancora disponibile l'interfaccia web per il ripristino dei dati.

Elenco contenuti
----------------

E' possibile elencare i file presenti nell'ultimo backup con il comando: ::

 backup-data-list

Il comando può richiedere del tempo in base alla dimensione del backup.

File e directory
----------------

Tutti i dati sono sono posizionati nella directory :file:`/var/lib/nethserver/`:

* Cartelle di posta: :file:`/var/lib/nethserver/vmail/<user>`
* Cartelle condivise: :file:`/var/lib/nethserver/ibay/<name>`
* Home utenti: :file:`/var/lib/nethserver/home/<user>`

Dopo aver individuato il file da ripristinare, usare il comando: ::

  restore-file <position> <file>

Esempio, ripristinare nella directory :file:`/tmp` la cartella di posta *test*: ::

  restore-file /tmp /var/lib/nethserver/vmail/test

Esempio, ripristinare la cartella di posta *test* nella posizione originale: ::

  restore-file / /var/lib/nethserver/vmail/test


Il sistema supporta la possibilità di ripristinare file e directory ad una versione
precedente rispetto all'ultimo backup.

Esempio, ripristinare un file alla versione di 15 giorni fa: ::

  restore-file -t 15D /tmp "/var/lib/nethserver/ibay/test/myfile" 

L'opzione ``-t`` consente di specificare il numero di giorni, in questo caso 15.


Disaster recovery
=================

Il sistema è ripristinato in due fasi: prima la configurazione, poi i dati.
Al termine del ripristino, il sistema è pronto all'uso se i moduli sono già installati.
E' possibile installare i moduli opzionali sia prima che dopo il ripristino. 
Ad esempio, se il server di posta è installato, il sistema è già in grado di inviare e ricevere mail.

Altre configurazioni ripristinate:

* utenti e gruppi, inclusa la password di root/admin
* Certificati SSL

I passi da eseguire sono:

1. Installare una nuova macchina e configurarla con lo stesso nome host della vecchia
2. Installare e configurare il backup dei dati
3. Installare i moduli aggiuntivi (opzionale)
4. Eseguire il ripristino della configurazione lanciando il comando :command:`restore-config` oppure usando l'interfaccia web
5. Se la vecchia macchina era il gateway della rete, ricordarsi di reinstallare il modulo firewall
6. Riconfigurare la rete da interfaccia web
7. Verificare che la macchina sia funzionante
8. Ripristinare i dati eseguendo il comando :command:`restore-data`

.. _backup_customization-section:

Personalizzazione backup dati
=============================

In caso di installazione di software aggiuntivi, potrebbe esser necessario modificare
la lista delle directory e dei file inclusi (o esclusi) dal backup.

Includere
---------

Se si desidera includere una directory o un file nel backup dei dati, aggiungere una linea
al file :file:`/etc/backup-data.d/custom.include`.

Ad esempio, per eseguire il backup di un software installato nella directory :file:`/opt`, aggiungere la linea: ::

  /opt/mysoftware

Escludere
---------

Se si desidera escludere una directory o un file dal backup dei dati, aggiungere una linea
al file :file:`/etc/backup-data.d/custom.exclude`.

Ad esempio, per escludere dal backup tutte le directory chiamate *Download*, aggiungere la linea: ::

  **Download**

Per escludere una casella di posta *test*, aggiungere la riga: ::

  /var/lib/nethserver/vmail/test/ 


.. note:: Assicurarsi di non lasciare linee vuote nei file modificati.

Personalizzazione backup configurazione
=======================================

Nella maggior parte dei casi non è necessario modificare la configurazione
del backup dei dati.
Ma può essere utile, ad esempio, se è stato installato un certificato SSL personalizzato.
In questo caso è possibile aggiungere il percorso del file che contiene il certificato
al backup della configurazione.

Includere
---------

Se si desidera includere una directory o un file nel backup della configurazione, aggiungere una linea
al file :file:`/etc/backup-config.d/custom.include`.

Ad esempio, per eseguire il backup del file :file:`/etc/pki/mycert.pem`, aggiungere la linea: ::

  /etc/pki/mycert.pem

Non aggiungere mai directory e file voluminosi al backup della configurazione.

Escludere
---------

Se si desidera escludere una directory o un file dal backup della configurazione, aggiungere una linea
al file :file:`/etc/backup-config.d/custom.exclude`.

.. note:: 
   Assicurarsi di non lasciare linee vuote nei file modificati.
   La sintassi del backup della configurazione supporta solo percorsi file e directory semplici.
