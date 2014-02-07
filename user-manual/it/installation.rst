=============
Installazione
=============

Sono supportati due modi per installare NethServer. In breve:

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

Il file ISO di NethServer si scarica dal sito ufficiale
`www.nethserver.org`, dalla sezione *Download*.  

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
DVD, USB) con l'immagine ISO di NethServer, inserirlo e avviare la
macchina.  Se non viene riconosciuto, fare riferimento alla
documentazione del BIOS della scheda madre. Una problematica tipica è
impostare la priorità dei dispositivi all'avvio in modo da tentare per
primo il supporto con l'immagine ISO di NethServer.

.. [#] Per esempio, http://unetbootin.sourceforge.net/ 

All'avviò verrà mostrata un menù con i diversi tipi di installazione
disponibili.

.. warning:: L'installazione eliminerà tutti i dati esistenti sui
                dischi rigidi!

NethServer interactive install
    Consente di selezionare la lingua, configurare il supporto RAID,
    la rete, e il file system criptato.  Sarà descritta più nel
    dettaglio in `Modalità interattiva`_.

Other / NethServer unattended install 
    Non richiede alcun tipo di intervento ed applica dove necessario i
    parametri predefiniti.

Standard CentOS installations
    Utilizza le procedure di installazione standard di CentOS Minimal.

Tools
    Avvia in modalità *rescue* (recupero), esecuzione del memory test
    e strumenti di rilevazione dell'hardware.
   
Boot from local drive
    Tenta l'avvio di un sistema già installato sul disco rigido.

Alla fine della procedura di installazione verrà chiesto di effettuare
il riavvio della macchina. Assicurarsi di aver rimosso il CD o il
supporto USB prima di riavviare.


Modalità unattended
-------------------

Al termine dell'installazione, il sistema sarà così configurato:

* Credenziali: root/Nethesis,1234
* Rete: DHCP abilitato su tutte le interfacce
* Tastiera: us
* Fuso orario: Greenwich
* Lingua: en_US.UTF-8
* Dischi: se sono presenti due o più dischi, verrà creato un RAID1 sui primi due dischi

Opzioni installazione
^^^^^^^^^^^^^^^^^^^^^

E' possibile aggiungere parametri all'installazione automatica, premendo TAB e modificando la linea di comando.

Per disabilitare il raid, aggiungere questa opzione: ::

    raid=none

Se si desidera selezionare i dischi su cui isntallare, usare: ::

    disks=sdx,sdy

Altre opzioni disponibili:

* lang: lingua del sistema, default è en_US
* keyboard: layout tastiera, default è us
* timezone: fuso orario, default è UTC Greenwich
* password: abilita la il crittografia del filesystem usando la password immessa


Modalità interattiva
--------------------

La modalità interattiva consente di effettuare poche e semplici scelte sulla configurazione del sistema:

1. Lingua
2. Layout tastiera
3. Fuso orario
4. RAID software
5. Password amministratore di sistema
6. Filesystem cifrato
7. Interfacce di rete
8. Configurazione di rete


Lingua
~~~~~~

Selezionare in quale lingua si desidera utilizzare la modalità interattiva.
La lingua selezionata sarà la lingua di default del sistema installato. 
Inoltre saranno suggeriti i default per tastiera e fuso orario.

Layout tasitera
~~~~~~~~~~~~~~~

La tastiera può avere layout (disposizione dei tasti) dipendentemente dalla lingua per cui è stata realizzata.
Lasciare il valore suggerito o inserire un valore personalizzato.

Fuso orario
~~~~~~~~~~~

La scelta del fuso orario consente di configurare data e ora del sistema.
Lasciare il valore suggerito o inserire un valore personalizzato.

RAID software
~~~~~~~~~~~~~

Il RAID (Redundant Array of Independent Disks) consente di combinare tutti i dischi installati nel sistema,
al fine di ottenere tolleranza ai guasti ed un incremento delle performance.

Questa schermata viene visualizzata se in fase di avvio sono stati rilevati due o più dischi.

Livelli disponibili:

* RAID 1: crea una copia esatta (mirror) di tutti i dati su due o più dischi. 
  Numero minimo di dischi: 2
* RAID 5:  usa una suddivisione dei dati a livello di blocco, distribuendo i dati di parità uniformemente tra tutti i dischi.
  Numero minimo di dischi: 3

Disco di spare
''''''''''''''

Se il numero dei dischi è maggiore del numero minimo richiesto dal livello raid selezionato,
è possibile creare un disco di spare.
Un disco di spare è un disco che viene aggiunto al RAID qualora si verifichi un guasto.

Password amministratore di sistema
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

E' fortemente consigliato impostare una password di amministratore personalizzata.
Una buona password deve:

* essere lunga almeno 8 caratteri
* contenere lettere maiuscole e minuscole
* contenere simboli e numeri

Filesystem cifrato
~~~~~~~~~~~~~~~~~~

Abilitando il filesystem cifrato, tutti i dati scritti sul disco verrano cifrati usando la crittografia
simmetrica. In caso di furto, un malintenzionato non sarà in grado di leggere i dati a meno di 
non possedere la chiave crittografica.

E' possibile scegliere una password per la cifratura, altrimenti verrà utilizzata la password dell'amministratore.

.. note:: Sarà necessario inserire la password scelta ad ogni avvio del sistema.

Interfacce di rete
~~~~~~~~~~~~~~~~~~

Selezionare l'interfaccia di rete che sarà utilizzata per accedere alla LAN.
Questa interfaccia è detta anche *rete verde*.

Configurazione di rete
~~~~~~~~~~~~~~~~~~~~~~

Nome host e dominio (FQDN)
    Digitare il nome host e dominio con il quale opererà il server (es. server.mycompany.com).
    Si consiglia di scegliere il nome in funzione del ruole che avrà il server. Es: fax,
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



Installazione su CentOS
=======================

E’ possibile installare NethServer su una nuova installazione di CentOS
usando il comando *yum* per scaricare via rete i
pacchetti software. 

Per esempio, per installare NethServer 6.5 si
comincerà installando CentOS 6.5 sul sistema (molti fornitori di VPS
offrono CentOS già pre-installato) e poi si eseguiranno alcuni comandi
per trasformare CentOS in NethServer. 

Abilitare i repository specifici di NethServer con il comando:

::

 yum localinstall -y  http://pulp.nethesis.it/nethserver/nethserver-release.rpm

Per installare il sistema di base eseguire:

::

 nethserver-install

Per installare i moduli aggiuntivi, passare il nome dei moduli come parametro allo script di installazione.
Esempio:

::

  nethserver-install nethserver-mail nethserver-nut


Al termine della procedura il sistema è pronto all'uso.
