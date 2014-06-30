.. _installation:

=============
Installazione
=============

Requisiti minimi
================

La dotazione minima richiesta da |product| è un macchina con CPU a 64
bit, 1 GB di RAM e 8 GB di spazio su hard disk. Si consiglia l’uso di
due hard disk in modo che venga garantita l’integrità dei dati
attraverso il supporto automatico RAID1.

Compatibilità hardware
----------------------

|product| è compatibile con tutto l':index:`hardware certificato` per
Red Hat® Enterprise  Linux® (RHEL ®). Vedi: `https://hardware.redhat.com/ <https://hardware.redhat.com/>`_

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
======================

Sono supportati due modi per :index:`installare` |product|. In breve:

* **Installazione da ISO**

  * scaricare l'immagine ISO, 
  * preparare un CD/DVD o una chiavetta USB avviabile
  * seguire la procedura guidata

* **Installazione da YUM**

  * installare CentOS Minimal
  * configurare la rete
  * eseguire l'installazione da rete


Installazione da ISO
====================

Il file :index:`ISO` di |product| si scarica dal sito ufficiale
|download_site|.  

Una volta scaricato, il file ISO può essere utilizzato per creare un
*supporto avviabile*, come un CD, un DVD, o una chiavetta USB.

La creazione di un disco avviabile è diversa dalla semplice scrittura
di un file su CD/DVD, e richiede l'uso di una funzione dedicata, di
solito presente nei programmi per la creazione di CD/DVD (es. *scrivi
immagine* oppure *masterizza ISO*).  Le istruzioni su come creare un
CD/DVD avviabile a partire dall'immagine ISO sono facilmente
reperibili su Internet o nella documentazione del proprio sistema
operativo.

In maniera simile, per preparare una chiavetta USB avviabile, la
semplice copia del file sulla chiavetta non è sufficiente. Ci sono
specifici programmi [#]_ che a partire dall'immagine ISO preparano la
chiavetta USB.

In entrambi i casi, una volta preparato il supporto avviabile (CD,
DVD, USB) con l'immagine ISO di |product|, inserirlo e avviare la
macchina.  Se non viene riconosciuto, fare riferimento alla
documentazione del BIOS della scheda madre. Una problematica tipica è
impostare la priorità dei dispositivi all'avvio in modo da tentare per
primo il supporto con l'immagine ISO di |product|.

.. [#] Per esempio, http://unetbootin.sourceforge.net/ 

All'avviò verrà mostrata un menù con i diversi tipi di installazione
disponibili.

.. warning:: L'installazione eliminerà tutti i dati esistenti sui
                dischi rigidi!

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
il riavvio della macchina. Assicurarsi di aver rimosso il CD o il
supporto USB prima di riavviare.


Modalità unattended
-------------------

Al termine dell'installazione, il sistema sarà così configurato:

* Nome utente: :samp:`root`
* Password: :samp:`Nethesis,1234`
* Rete: DHCP abilitato su tutte le interfacce
* Tastiera: :samp:`us`
* Fuso orario: :samp:`Greenwich`
* Lingua: :samp:`en_US.UTF-8`
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
* password: abilita la il crittografia del file system usando la password immessa


Modalità interattiva
--------------------

La modalità interattiva consente di effettuare poche e semplici scelte sulla configurazione del sistema:

1. Lingua
2. Layout tastiera
3. Fuso orario
4. RAID software
5. Password amministratore di sistema
6. File system cifrato
7. Interfacce di rete
8. Configurazione di rete


Lingua
^^^^^^

Selezionare in quale lingua si desidera utilizzare la modalità interattiva.
La lingua selezionata sarà la lingua di default del sistema installato. 
Inoltre saranno suggeriti i default per tastiera e fuso orario.

Layout tastiera
^^^^^^^^^^^^^^^

La tastiera può avere layout (disposizione dei tasti) dipendentemente dalla lingua per cui è stata realizzata.
Lasciare il valore suggerito o inserire un valore personalizzato.

Fuso orario
^^^^^^^^^^^

La scelta del fuso orario consente di configurare data e ora del sistema.
Lasciare il valore suggerito o inserire un valore personalizzato.

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

E' fortemente consigliato impostare una password di amministratore personalizzata.
Una buona password deve:

* essere lunga almeno 8 caratteri
* contenere lettere maiuscole e minuscole
* contenere simboli e numeri

File system cifrato
^^^^^^^^^^^^^^^^^^^

Abilitando il file system cifrato, tutti i dati scritti sul disco verrano cifrati usando la crittografia
simmetrica. In caso di furto, un malintenzionato non sarà in grado di leggere i dati a meno di 
non possedere la chiave crittografica.

E' possibile scegliere una password per la cifratura, altrimenti verrà utilizzata la password dell'amministratore.

.. note:: Sarà necessario inserire la password scelta ad ogni avvio del sistema.

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

Al termine dell'installazione, installare i moduli opzionali: :ref:`packages-section`.

Installazione su CentOS
=======================

E’ possibile installare |product| su una nuova installazione di :index:`CentOS`
usando il comando :command:`yum` per scaricare via rete i
pacchetti software. 

Per esempio, per installare |product| 6.5 si
comincerà installando CentOS 6.5 sul sistema (molti fornitori di VPS
offrono CentOS già pre-installato) e poi si eseguiranno alcuni comandi
per trasformare CentOS in |product|. 

Abilitare i repository specifici di |product| con il comando:

::

 yum localinstall -y http://pulp.nethserver.org/nethserver/nethserver-release.rpm

Per installare il sistema di base eseguire:

::

 nethserver-install

Per installare i moduli aggiuntivi, passare il nome dei moduli come parametro allo script di installazione.
Esempio:

::

  nethserver-install nethserver-mail nethserver-nut


Al termine dell'installazione, installare i moduli opzionali: :ref:`packages-section`.


.. _packages-section:

==================
Gestione pacchetti
==================

|product| è altamente modulare: al termine dell'installazione il sistema contiene solo
i moduli di base (es. configurazioen rete, visualizzazione log).
L'amministratore può quindi decidere quali componenti installare in base
alle proprie esigenze (es. mail server, DHCP server, firewall ecc.)

La vista principale mostra una lista di componenti software. Gli elementi
spuntati rappresentano i componenti installati, mentre quelli non spuntati sono
quelli disponibili. Si può filtrare la lista per categoria.


Per installare o rimuovere i componenti software elencati, aggiungere
o togliere il segno di spunta, quindi premere il pulsante
:guilabel:`Applica`.  La schermata successiva riepiloga cosa sarà
installato e rimosso. Inoltre, viene mostrata la lista di pacchetti
opzionali, da selezionare per l'installazione.

.. NOTE:: 

    I pacchetti opzionali possono essere installati anche *dopo*
    l'installazione del componente relativo: cliccare di nuovo sul
    bottone :guilabel:`Applica` e selezionarli dalla schermata di
    riepilogo.


La sezione :guilabel:`Software installato` elenca i pacchetti installati sul sistema.


Aiuto in linea
==============

Tutti i pacchetti che sono configurabili attraverso il Server Manager
contengono un :index:`manuale in linea` che spiega l'utilizzo base e tutti
i campi contenuti nella pagina.

Il manuale in linea è consultabile in tutte le lingue in cui è tradotto
il Server Manager.

Una lista di tutti i manuali installati nel sistema è disponibile all'indirizzo: ::

 https://<server>:980/<language>/Help

**Esempio**

Se il server ha indirizzo ``192.168.1.2`` e si desidera visualizzare la lista dei manuali
in lingua italiana, usare l'indirizzo: ::

 https://192.168.1.2:980/it/Help


Moduli opzionali
================

I seguenti moduli sono opzionali e devono essere installati dalla pagina :guilabel:`Gestione pacchetti`.


In alternativa, è possibile installare i moduli da linea di comando utilizzando :command:`yum` ::

  yum install @<module_id>

Dove ``module_it`` è l'ID del modulo preso dall lista qui sotto. Esempio per installare il modulo di backup: ::
   
  yum install @nethserver-backup


Moduli disponibili:

* **Backup** : Backup della configurazione del sistema e dei dati
   ID: ``nethserver-backup``
* **Server DNS e DHCP** : Demoni e strumenti per i servizi DNS e DHCP
   ID: ``nethserver-dns-dhcp``
* **Fax server** : Configura HylaFax+ e gestisce i modem IAX
   ID: ``nethserver-fax-server``
* **Web-based fax client** : Manage faxes from a simple web interface
   ID: ``nethserver-faxweb2``
* **Firewall base** : Configura le interfacce di rete e il firewall base
   ID: ``nethserver-firewall-base``
* **File server** : Demoni e strumenti per la condivisione file in rete
   ID: ``nethserver-file-server``
* **Groupware** : Server SOGo ed estensioni per Thunderbird
   ID: ``nethserver-groupware``
* **Email** : Server e filtri di posta elettronica
   ID: ``nethserver-mail``
* **Messaggistica istantanea** : Server di chat XMPP/Jabber
   ID: ``nethserver-messaging``
* **Server di stampa** : Servizio di gestione stampanti (CUPS)
   ID: ``nethserver-printers``
* **Server Web** : Strumenti di configurazione per il server web Apache
   ID: ``nethserver-web``
* **Monitoraggio banda** : Configurazione e gestione di Ntopng
   ID: ``nethserver-bandwidth-monitor``
* **Supporto UPS** : Configurazione della gestione e del monitoraggio dei gruppi di continuità
   ID: ``nethserver-nut``
* **Statistiche** : Registra e analizza le statistiche del sistema
   ID: ``nethserver-statistics``
* **Proxy web** : Configurazione Squid (web caching proxy)
   ID: ``nethserver-web-proxy``
* **Filtro web** : Filtro web per contenuti e virus
   ID: ``nethserver-web-filter``
* **VPN** : Configure remote-access and site-to-site Virtual Private Networks (VPN)
   ID: ``nethserver-vpn``
* **ownCloud** : Configura ownCloud - accesso completo ai propri file via web, computer o dispositivi mobili - da qualsiasi luogo
   ID: ``nethserver-owncloud``
* **Server MySQL** : Strumenti di configurazione per MySQL
   ID: ``nethserver-mysql``

