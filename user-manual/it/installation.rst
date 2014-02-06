=============
Installazione
=============

Download NethServer
===================

NethServer può essere scaricato com file immagine di tipo ISO
all'indirizzo:

`http://nethserver.nethesis.it/index.php?id=download <http://nethserver.nethesis.it/index.php?id=download>`__

Metodi di installazione
=======================

Installazione da CD
-------------------

Per installare NethServer da CD, occorre masterizzare il file immagine
NethServer-versione.iso direttamente su un CD.

Questo tipo di masterizzazione è diversa dalla semplice masterizzazione
di file su CD, infatti richiede l'uso di funzioni dedicate presenti nei
vari programmi di masterizzazione (es. "scrivi immagine" oppure
"masterizza ISO").

Creato il CD assicurarsi che nella macchina server l'unità ottica (CD o
DVD) abbia priorità 1 nella lista boot priority presente nel BIOS. (Fare
riferimento al manuale della scheda madre della macchina server)

Inserire il CD e avviare la macchina.

Installazione da chiavetta USB
------------------------------

Per installare NethServer da chiavetta USB occorre inserire il file
immagine di NethServer su un supporto USB che sia Bootable, per far ciò
vi sono specifici programmi che girano anche sotto windows ad esempio
UNebootin
(`http://unetbootin.sourceforge.net/ <http://unetbootin.sourceforge.net/>`__)

Creata la chiavetta USB bootable assicurarsi che nella macchina server
nella lista boot priority il supporto USB sia al primo posto. (Fare
riferimento al manuale della scheda madre della macchina server).

Inserire la chiavetta ed avviare la macchina.

Installazione guidata
---------------------

Avviata la macchina ci verrà mostrata una finestra con le opzioni
iniziali per eseguire l'installazione guidata.

Scegliendo la prima voce "NethServer install" più tasto Invio si avvierà
l'installazione dei pacchetti in modo automatizzato.

Alla fine viene chiesto il riavvio della macchina, ma prima di riavviare
assicurarsi di aver rimosso il CD o il supporto USB.

Inserimento dei parametri
-------------------------

Al successivo avvio NethServer richiede l'inserimento di alcuni
parametri di configurazione tramite una procedura guidata (denominata
console). Per muoversi all'interno della console non è possibile usare
il mouse quindi per andare da un
campo all'altro è necessario usare il tasto
tab, per cancellare il tasto del, per selezionare il tasto Invio ed i
tasti freccia per muovere il cursore all'interno dei
campi.

Password di root
----------------

Scegliere la password di root, spostarsi su next e premere tasto Invio.

Su Nethserver, per comodità, la password di root è sincronizzata con
quella di admin perciò è consigliabile scegliere una password sicura,
tipicamente deve contenere un carattere maiuscolo un carattere speciale
e un numero. In mancanza di tali caratteristiche il sistema ci avvisa
che stiamo procedendo con insufficienti requisiti di sicurezza.

La password viene richiesta due volte per avere la certezza di non aver
fatto errori di battitura.

Dominio
-------

Digitare il dominio con il quale opererà il server (es. tuo-dominio.it).

Spostarsi con il tasto tab su next e premere tasto Invio.

N.B i nomi di dominio posso contenere solo lettere, numeri e il
trattino.

Nome del server
---------------

Digitare il nome del server (per esempio la funzione del server, fax,
mail, etc oppure un nome generico come server).

Spostarsi con il tasto tab su next e premere tasto Invio.

Indirizzo IP
------------

Digitare un indirizzo IP privato (da RFC1918) da assegnare al server;
nel caso si voglia installare la macchina in una rete già esistente
occorrerà fornire un indirizzo IP libero, valido per per quella rete (in
genere si tende ad usare il primo o l’ultimo host, per esempio
192.168.7.1 o .254).

Spostarsi con il tasto tab su next e premere il tasto Invio.

Netmask
-------

Digitare la subnet mask di rete. Generalmente si lascia invariata quella
suggerita dal sistema.

Spostarsi con il tasto tab su next e  premere tasto invio.

Gateway
-------

Digitare l’indirizzo IP del gateway della rete su cui si sta installando
il server.

Spostarsi con il tasto tab su next e  premere tasto invio.

DNS
---

Digitare un DNS valido. Il sistema propone di default il DNS di Google
(8.8.8.8)

Spostarsi con il tasto tab su next e  premere tasto invio.

Termine procedura installazione
-------------------------------

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


