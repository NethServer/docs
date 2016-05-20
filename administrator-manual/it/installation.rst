.. index::
   single: installazione

.. _installation-section:

=============
Installazione
=============

Requisiti minimi
================

La dotazione minima richiesta da |product| è un macchina con CPU a 64
bit, 1 GB di RAM e 10 GB di spazio su hard disk. Si consiglia l’uso di
due hard disk in modo che venga garantita l’integrità dei dati
attraverso il supporto automatico RAID1.

Compatibilità hardware
----------------------

|product| è compatibile con tutto l':index:`hardware certificato` per
Red Hat® Enterprise  Linux® (RHEL ®). Vedi: `hardware.redhat.com <https://hardware.redhat.com/>`__

Si richiede HW di classe server e non desktop, dato che garantisce
maggiore compatibilità e qualità dei componenti.

N.B. Un hardware dichiarato compatibile con Linux non è detto
sia compatibile con RHEL/|product|.

RAID
----

|product| supporta sia configurazioni RAID hardware che
software. Nel caso si scelga di implementare la
configurazione RAID hardware assicurarsi che il controller sia presente
nella lista dei controller supportati.

|product| di default prevede il RAID 1 software e supporta anche il
RAID 5.

Si consiglia di usare il RAID software perché viene controllato di
default da un apposito software pre-configurato che segnala eventuali
anomalie.

Tipi di installazione
=====================

Sono supportati due modi per :index:`installare` |product|. In breve:

* **Installazione da ISO**

  * scaricare l'immagine ISO, 
  * preparare un DVD o una chiavetta USB,
  * seguire la procedura guidata

* **Installazione da YUM**

  * installare CentOS Minimal
  * configurare la rete
  * eseguire l'installazione da rete


.. index::
   pair: installazione; ISO

Installazione da ISO
====================

.. warning:: L'installazione eliminerà tutti i dati esistenti sui
             dischi rigidi!


Il file :index:`ISO` di |product| si scarica dal sito ufficiale
|download_site|.  

Una volta scaricato, il file ISO può essere utilizzato per creare un
*supporto avviabile*, come un DVD o una chiavetta USB.

Chiavetta USB
-------------

Su una macchina Linux, aprire il terminale ed eseguire: ::

  dd if=NethServer.iso of=/dev/sdc

Dove `NethServer.iso` è il nome del file della ISO scaricata, e `/dev/sdc`
è la destinazione che corrisponde all'intera chiavetta USB, non una partizione
(come /dev/sdc1).

Su una macchina Windows, formattare la chiavetta USB e smontarla.
Quindi usare uno dei seguenti tool per scrivere i dati:

* `Rufus`_
* `Fedora LiveUSB Creator`_
* `Win32 Disk Imager`_
* `Rawrite32`_
* `dd for Windows`_

.. _`Rufus`: https://rufus.akeo.ie/ 
.. _`Fedora LiveUSB Creator`: https://fedorahosted.org/liveusb-creator/ 
.. _`Win32 Disk Imager`: http://sourceforge.net/projects/win32diskimager/ 
.. _`Rawrite32`: http://www.netbsd.org/~martin/rawrite32/ 
.. _`dd for Windows`: http://www.chrysocome.net/dd 


DVD
---

La creazione di un disco avviabile è diversa dalla semplice scrittura
di un file su DVD, e richiede l'uso di una funzione dedicata, di
solito presente nei programmi per la creazione di DVD (es. *scrivi
immagine* oppure *masterizza ISO*).  Le istruzioni su come creare un
DVD avviabile a partire dall'immagine ISO sono facilmente
reperibili su Internet o nella documentazione del proprio sistema
operativo.

Modalità di installazione
-------------------------

Una volta preparato il supporto avviabile (DVD o USB) con l'immagine 
ISO di |product|, inserirlo e avviare la
macchina.  Se non viene riconosciuto, fare riferimento alla
documentazione del BIOS della scheda madre. Una problematica tipica è
impostare la priorità dei dispositivi all'avvio in modo da tentare per
primo il supporto con l'immagine ISO di |product|.

All'avviò verrà mostrata un menù con i diversi tipi di installazione
disponibili.

|product| interactive install
    Consente di selezionare la lingua, configurare il supporto RAID,
    la rete, e il file system criptato.  Sarà descritta più nel
    dettaglio in `Modalità interattiva`_.

Other / |product| unattended install 
    Non richiede alcun tipo di intervento ed applica dove necessario i
    parametri predefiniti.

Standard CentOS installations
    Utilizza le procedure di installazione standard di CentOS Minimal.

Tools
    Avvia in modalità :dfn:`rescue` (recupero), esecuzione del memory test
    e strumenti di rilevazione dell'hardware.
   
Boot from local drive
    Tenta l'avvio di un sistema già installato sul disco rigido.

Alla fine della procedura di installazione verrà chiesto di effettuare
il riavvio della macchina. **Rimuovere il media di
installazione**, prima di riavviare.

.. _installation-unattended:

Modalità *unattended*
---------------------

Al termine dell'installazione, il sistema sarà così configurato:

* Nome utente: :samp:`root`
* Password di default: :samp:`Nethesis,1234`
* Rete: DHCP abilitato su tutte le interfacce
* Tastiera: |ks_keyboard|
* Fuso orario: |ks_timezone|
* Lingua: Inglese
* Dischi: se sono presenti due o più dischi, verrà creato un RAID1 sui primi due dischi

Opzioni installazione
^^^^^^^^^^^^^^^^^^^^^

E' possibile aggiungere parametri all'installazione automatica, premendo :kbd:`TAB` e modificando la linea di comando.

Per disabilitare il raid, aggiungere questa opzione: ::

    raid=none

Se si desidera selezionare i dischi su cui installare, usare: ::

    disks=sdx,sdy

Altre opzioni disponibili:

* lang: lingua del sistema, default è :samp:`en_US`
* keyboard: layout tastiera, default è :samp:`us`
* timezone: fuso orario, default è :samp:`UTC Greenwich`
* fspassword: abilita la crittografia del file system usando la password immessa
  Questa opzione puà essere usata anche in Modalità interattiva

.. _installation-interactive:

Modalità interattiva
--------------------

La modalità interattiva consente di effettuare poche e semplici scelte sulla configurazione del sistema:

* Lingua
* RAID software
* Configurazione di rete


Lingua
^^^^^^

Selezionare in quale lingua si desidera utilizzare la modalità interattiva.
Il layout della tastiera e il fuso orario saranno cambiati in base alla lingua selezionata.
Entrambe le configurazioni saranno modificabili al primo login nell'interfaccia web.
 
La lingua del sistema è sempre l'inglese.

RAID software
^^^^^^^^^^^^^

Il RAID (Redundant Array of Independent Disks) consente di combinare tutti i dischi installati nel sistema,
al fine di ottenere tolleranza ai guasti ed un incremento delle performance.

Questa schermata viene visualizzata se in fase di avvio sono stati rilevati due o più dischi.

Livelli disponibili:

* RAID 1: crea una copia esatta (mirror) di tutti i dati su due o più dischi. 
  Numero minimo di dischi: 2
* RAID 5:  usa una suddivisione dei dati a livello di blocco, distribuendo i dati di parità uniformemente tra tutti i dischi.
  Numero minimo di dischi: 3

Disco di spare
~~~~~~~~~~~~~~

Se il numero dei dischi è maggiore del numero minimo richiesto dal livello raid selezionato,
è possibile creare un disco di spare.
Un disco di spare è un disco che viene aggiunto al RAID qualora si verifichi un guasto.

Password amministratore di sistema
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

E' possibile cambiare la password dell'utente ``root`` durante la prima
configurazione.  Una buona password deve:

* essere lunga almeno 8 caratteri
* contenere lettere maiuscole e minuscole
* contenere simboli e numeri

La password di default è :samp:`Nethesis,1234`.

File system cifrato
^^^^^^^^^^^^^^^^^^^

Abilitando il file system cifrato, tutti i dati scritti sul disco verranno cifrati usando la crittografia
simmetrica. In caso di furto, un malintenzionato non sarà in grado di leggere i dati a meno di 
non possedere la chiave crittografica.

E' possibile scegliere una password per la cifratura, altrimenti verrà utilizzata la password dell'amministratore.

.. note:: Sarà necessario inserire la password scelta ad ogni avvio del sistema.

.. warning:: I seguenti caratteri non sono supportato all'interno della password:
   ``#``, ``=`` e ``$``.


Interfacce di rete
^^^^^^^^^^^^^^^^^^

Selezionare l'interfaccia di rete che sarà utilizzata per accedere alla LAN.
Questa interfaccia è detta anche *rete green*.

Configurazione di rete
^^^^^^^^^^^^^^^^^^^^^^

Nome host e dominio (FQDN)
    Digitare il nome host e dominio con il quale opererà il server (es. server.mycompany.com).
    Si consiglia di scegliere il nome in funzione del ruolo che avrà il server. Es: fax,
    mail, ecc.
    
    *NB:* I nomi di dominio posso contenere solo lettere, numeri e il
    trattino.

Indirizzo IP
    Digitare un indirizzo IP privato (da RFC1918) da assegnare al server;
    nel caso si voglia installare la macchina in una rete già esistente
    occorrerà fornire un indirizzo IP libero, valido per per quella rete (in
    genere si tende ad usare il primo o l’ultimo host, per esempio
    192.168.7.1 o .254).

Netmask
    Digitare la subnet mask di rete. Generalmente si lascia invariata quella
    suggerita dal sistema.

Gateway
    Digitare l’indirizzo IP del gateway della rete su cui si sta
    installando il server.

DNS
    Digitare un DNS valido. Esempio: 8.8.8.8


Termine procedura installazione
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Immessi i parametri la procedura avvierà l'installazione.

Alla fine della procedura di installazione verrà chiesto di effettuare
il riavvio della macchina. Assicurarsi di aver rimosso il CD o il
supporto USB prima di riavviare.

.. include:: installation_interactive_end.inc

.. index::
   pair: installazione; ISO
   pair: installazione; VPS
   pair: installazione; USB

.. _install_centos-section:
   
Installazione su CentOS
=======================

È possibile installare |product| su una nuova installazione di
:index:`CentOS` usando il comando :program:`yum` per scaricare via
rete i pacchetti software.  Questo è il metodo di installazione racommandato se si ha

* un server virtuale privato (VPS), oppure
* una chiavetta USB

Per esempio, per installare |product| |version| si
comincerà installando CentOS |version| sul sistema (molti fornitori di VPS
offrono CentOS già pre-installato) e poi si eseguiranno alcuni comandi
per trasformare CentOS in |product|. 

.. include:: installation_centos_end.inc

