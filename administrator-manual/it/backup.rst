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
Il backup della configurazione salva anche la lista dei moduli installati. Tutti i moduli saranno reinstallati durante il processo di ripristino.
Lo scopo del backup della configurazione è quello di consentire un rapido ripristino della macchina in caso di disaster recovery.
Dopo aver ripristinato la configurazione, la macchina può già essere messa in produzione mentre i dati vengono ripristinati in background.

Il backup dei dati è abilitato installando il modulo "Backup" e comprende i dati degli utenti come caselle di posta e cartelle condivise.
Viene eseguito ogni notte e può essere completo o incrementale su base settimanale.
Questo backup contiene anche il backup della configurazione.

Il backup dei dati può essere fatto su tre tipi di destinazione:

* USB: disco collegato via USB, utile in caso di molti dati ma limitato dalla velocità dell'USB (Vedi: :ref:`backup_usb_disk-section`)
* CIFS: cartella condivisa Windows, disponibile su tutti i NAS
* NFS: cartella condivisa Linux, disponibile su tutti i NAS, solitamente più veloce di CIFS


L'esito del backup può essere notificato all'amministratore o ad un indirizzo mail esterno.

.. note:: La directory di destinazione è basta sul nome host del server:
   in caso di cambio FQDN, l'amministratore dovrà occuparsi di spostare manualmente
   i dati del backup dalla vecchia alla nuova directory.


Ripristino dati
===============

Assicurarsi che la destinazione contenente il backup sia raggiungibile (es. disco USB collegato).

Linea di comando
----------------

Elenco contenuti
^^^^^^^^^^^^^^^^

E' possibile elencare i file presenti nell'ultimo backup con il comando: ::

 backup-data-list

Il comando può richiedere del tempo in base alla dimensione del backup.

File e directory
^^^^^^^^^^^^^^^^

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

.. note:: Nel caso si utilizzi *CIFS* per accedere alla condivisione e il comando di restore 
          non funzioni nel modo atteso, verificare che utente e password della condivisione di rete siano corretti.
          Se la coppia utente/password è sbagliata nel file :file:`/var/log/messages` si troveranno degli errori 
          di NT_STATUS_LOGON_FAILURE.
          Allo stesso tempo il comando :command:`backup-data-list` non andrà a buon fine e uscirà immediatamente 
          riportando degli errori.

Interfaccia grafica
-------------------

Nel menu :menuselection:`Restore file` è possibile cercare, selezionare e ripristinare
una o più cartelle dal backup, navigando l'albero grafico con tutti i percorsi inclusi nel backup.

Di default viene mostrato l'albero dell'ultimo backup, se si desidera ripristinare un file di un backup precedente, selezionare la data del backup dal seletto
re *"File Backup"*.

Ci sono due opzioni di ripristino:

* Ripristinare i file nel percorso originale, i file correnti del filesystem sono sovrascritti con quelli ripristinati dal backup.
* Ripristinare i file nel percorso originale ma i file ripristinati dal backup sono spostati in una nuova directory (i file non sono sovrascritti) in questo percorso: ::

  /percorso/completo/del/file_YYYY-MM-DD (YYYY-MM-DD è la data del restore)

Per usare il campo di ricerca, inserisci almeno tre caratteri e la ricerca parte da sola, evidenziando le cartelle corrispondenti alla ricerca

Il ripristino delle cartelle avviene cliccando sul bottone **Ripristina**.

.. note:: Tenendo premuto il tasto Ctrl è possibile effettuare la selezione multipla di cartelle.


Disaster recovery
=================

Il sistema è ripristinato in due fasi: prima la configurazione, poi i dati.
Al termine del ripristino, il sistema è pronto all'uso se i moduli sono già installati.
E' possibile installare i moduli opzionali sia prima che dopo il ripristino.
Ad esempio, se il server di posta è installato, il sistema è già in grado di inviare e ricevere mail.

Altre configurazioni ripristinate:

* Utenti e gruppi
* Certificati SSL

.. note:: La password di root/admin non viene ripristinata, verrà mantenuta quella impostata nel nuovo sistema.

I passi da eseguire sono:

1. Installare una nuova macchina e configurarla con lo stesso nome host della vecchia

2. Installare e configurare il backup dei dati

3. Se la vecchia macchina era il gateway della rete, ricordarsi di reinstallare il modulo firewall

4. Eseguire il ripristino della configurazione dalla pagina
   :guilabel:`Backup (configurazione) > Ripristino` nel Server Manager,
   oppure eseguendo il comando :command:`restore-config`

5. Se un avviso lo richiede, riconfigurare le interfacce di
   rete. Vedere :ref:`restore-roles-section` più sotto.

6. Verificare che la macchina sia funzionante

7. Ripristinare i dati eseguendo il comando :command:`restore-data`



.. _restore-roles-section:

Assegnamento delle interfacce di rete
-------------------------------------

Le pagine :guilabel:`Dashboard`, :guilabel:`Backup (configuration) >
Restore` e :guilabel:`Network` mostrano un avviso. Questo può accadere per
esempio nei seguenti casi:

* dopo il ripristino del backup della configurazione su un nuovo hardware
* una o più schede di rete sono state sostituite
* i dischi del sistema sono stati spostati su una nuova macchina

L'avviso punta verso una pagina che elenca le schede di rete fisiche
presenti nel sistema, evidenziando quelle che non hanno un :ref:`ruolo
<network-section>` assegnato. Per ogni scheda di questo tipo, un menù
a discesa mostra i ruoli da assegnare.

Per esempio, se una scheda con ruolo *orange* è stata sostituita, il
menù a discesa elencherà un elemento ``orange`` in corrispondenza
della nuova scheda di rete.

Lo stesso accade se la vecchia scheda era il componente di una
interfaccia logica, come un *bridge* o un *bond*.

Selezionando un elemento dal menù a discesa, le impostazioni del ruolo
sono trasferiti alla nuova scheda.

Premendo il pulsante :guilabel:`Salva` le modifiche vengono applicate.

.. warning:: Assegnare con attenzione i ruoli alle nuove
             interfacce. Un errore può portare ad un sistema isolato
             dalla rete.

Se il ruolo mancante è ``green`` una procedura interattiva chiede di
aggiustare la configurazione all'avvio del sistema, per assicurare una
connettività di rete minima e accedere di nuovo al Server Manager.


.. _backup_config_rpms:

Ripristino moduli installati
----------------------------

Il processo di ripristino della configurazione reinstalla tutti i moduli presenti precedentemente.

Per evitare che i moduli vengano reinstallati, eseguire questo comando prima del ripristino: ::

  config setprop backup-config reinstall disabled


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

La stessa sintassi si applica al backup della configurazione. Le modifiche dovrebbero essere fatte all'interno del file :file:`/etc/backup-config.d/custom.exclude`.

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

.. _backup_usb_disk-section:

Configurazione disco USB
========================

Si consiglia di formattare i dischi USB in formato EXT3 per le migliori prestazioni.
Generalmente i dischi utilizzano il filesystem NTFS, che **non è supportato**.
Il filesystem FAT è invece supportato ma *sconsigliato*.

Per eseguire la formattazione, è necessario collegare il disco e identificarlo correttamente: ::

 # dmesg | tail -20

 Apr 15 16:20:43 mynethserver kernel: usb-storage: device found at 4
 Apr 15 16:20:43 mynethserver kernel: usb-storage: waiting for device to settle before scanning
 Apr 15 16:20:48 mynethserver kernel:   Vendor: WDC WD32  Model: 00BEVT-00ZCT0     Rev:
 Apr 15 16:20:48 mynethserver kernel:   Type:   Direct-Access           ANSI SCSI revision: 02
 Apr 15 16:20:49 mynethserver kernel: SCSI device sdc: 625142448 512-byte hdwr sectors (320073 MB)
 Apr 15 16:20:49 mynethserver kernel: sdc: Write Protect is off
 Apr 15 16:20:49 mynethserver kernel: sdc: Mode Sense: 34 00 00 00
 Apr 15 16:20:49 mynethserver kernel: sdc: assuming drive cache: write through
 Apr 15 16:20:49 mynethserver kernel: SCSI device sdc: 625142448 512-byte hdwr sectors (320073 MB)
 Apr 15 16:20:49 mynethserver kernel: sdc: Write Protect is off
 Apr 15 16:20:49 mynethserver kernel: sdc: Mode Sense: 34 00 00 00
 Apr 15 16:20:49 mynethserver kernel: sdc: assuming drive cache: write through
 Apr 15 16:20:49 mynethserver kernel:  sdc: sdc1
 Apr 15 16:20:49 mynethserver kernel: sd 7:0:0:0: Attached scsi disk '''sdc'''
 Apr 15 16:20:49 mynethserver kernel: sd 7:0:0:0: Attached scsi generic sg3 type 0
 Apr 15 16:20:49 mynethserver kernel: usb-storage: device scan complete

Un altro buon comando da utilizzare può essere: ::

 lsblk -io KNAME,TYPE,SIZE,MODEL


In questo esempio, il disco è stato riconosciuto come device *sdc*.

* Creare una unica partizione Linux sull'intero disco sdc ::

    echo "0," | sfdisk /dev/sdc

* Creare il filesystem sulla partizione *sdc1* assegnando una label, ad esempio *backup* ::

    mke2fs -v -T largefile4 -j /dev/sdc1 -L backup

* Scollegare e ricollegare il disco USB

  E' possibile utilizzare il comando seguente per simulare il collegamento del disco: ::

    blockdev --rereadpt /dev/sdc

* A questo punto la voce *backup*  sarà selezionabile dalla pagina :guilabel:`Backup (dati)`.
