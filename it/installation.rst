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
--------------------

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

Modalità interattiva
^^^^^^^^^^^^^^^^^^^^

1. Scelta della lingua
2. Tipo di tastiera (us o it)
3. Fuso orario
4. Password amministratore di sistema
5. Filesystem cifrato
6. Interfacce di rete
7. Configurazione di rete


Dominio
    Digitare il dominio con il quale opererà il server (es. tuo-dominio.it).

    Spostarsi con il tasto tab su next e premere tasto Invio.

    N.B i nomi di dominio posso contenere solo lettere, numeri e il
    trattino.

Nome del server
    Digitare il nome del server (per esempio la funzione del server, fax,
    mail, etc oppure un nome generico come server).

Indirizzo IP
    Digitare un indirizzo IP privato (da RFC1918) da assegnare al server;
    nel caso si voglia installare la macchina in una rete già esistente
    occorrerà fornire un indirizzo IP libero, valido per per quella rete (in
    genere si tende ad usare il primo o l’ultimo host, per esempio
    192.168.7.1 o .254).

Netmask
    Digitare la subnet mask di rete. Generalmente si lascia invariata quella
    suggerita dal sistema.

    Spostarsi con il tasto tab su next e  premere tasto invio.

Gateway
    Digitare l’indirizzo IP del gateway della rete su cui si sta
    installando il server.


DNS
    Digitare un DNS valido. Il sistema propone di default il DNS di Google
    (8.8.8.8)


Termine procedura installazione
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Immessi i parametri la procedura di installazione è terminata,
NethServer sarà già operativo per essere configurato.

Nel caso si abbia la necessità di tornare all’ interfaccia grafica di
installazione per correggere qualche parametro si deve accedere al
server tramite terminale come root e digitare il comando console seguito
dal tasto invio.


Installazione su CentOS via yum
-------------------------------

E’ possibile installare NethServer su una installazione di CentOS della
stessa versione, usando il comando yum per scaricare via rete i
pacchetti software. Per esempio, per installare NethServer 6.5 si
comincerà installando CentOS 6.5 sul sistema (molti fornitori di VPS
offrono CentOS già pre-installato) e poi si eseguiranno alcuni comandi
per “trasformare” CentOS in NethServer. La documentazione si trova al
seguente indirizzo:

`http://nethserver.nethesis.it/index.php?id=download\_yum-installation <http://nethserver.nethesis.it/index.php?id=download_yum-installation>`__


