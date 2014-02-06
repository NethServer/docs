===========
Server mail
===========

Nethserver ha la possibilità di svolgere la funzione di un potente e
sofisticato mail server. Le pagine di configurazione e gestione sono
molto semplici e intuitive.

Spedizione posta
================

NethServer è un mailserver in grado spedire e ricevere posta
autonomamente, tramite il protocollo SMTP.

In *Figura 1* è descritto il tragitto di una mail dal mittente al
destinatario.


.. figure:: ../_static/email_works.png

   *Figura 1*: Schema di funzionamento del servizio e-mail. Tratto da `Wikipedia <http://www.wikipedia.org>`

SMTP Relay
----------

Partendo dalla *Figura 1* poniamo il caso che smtp.a.org sia un
NethServer, esso accetterà di spedire una mail proveniente da
alice@a.org se almeno una delle seguenti condizioni è soddisfatta:

*  il pc di Alice fa parte di una Rete Locale gestita da NethServer
   (vedi "Reti Locali")
*  l'indirizzo destinatario della mail fa parte di un dominio gestito da
   NethServer, ad esempio lucia@\ **a.org** (vedi "Gestione Domini")
*  il client di Alice utilizza l'autenticazione
   (`SMTP-AUTH <http://en.wikipedia.org/wiki/SMTP-AUTH>`__) attraverso
   lo username e password dell'utente *alice*

Se smtp.a.org accetta di spedire la mail di Alice, viene definito SMTP
relay di Alice.

Modalità standard
-----------------

In tale modalità NethServer contatta direttamente il mailserver
destinatario (mx.b.org) per consegnare l'e-mail, seguendo passo passo la
procedura descritta in *Figura 1*

Vantaggi
^^^^^^^^

*  Completa autonomia nella gestione della posta. Esclusione di
   eventuali problemi dovuti al provider.
*  Possibilità di ricostruire tutto il tragitto in *Figura 1* (tramite
   i log) al fine di individuare eventuali errori.

Server SMTP
-----------

In questa modalità NethServer non si occupa direttamente della
spedizione della e-mail, ma la consegna ad un mailserver esterno (generalmente quello
del provider) che spedisce l'e-mail al suo posto.

Il server SMTP (definito tecnicamente smarthost) accetterà e-mail da
NethServer se:

*  è stato configurato per fare da SMTP relay per l'indirizzo IP di
   NethServer (normale configurazione per un provider)
*  NethServer utilizza l'SMTP AUTH, autenticazione basata su username e
   password (vedi "Configurazione distribuzione e-mail" e
   "Autenticazione SMTP per provider internet")

Vantaggi
^^^^^^^^

*  Possibilità di spedire posta anche se l'ip di NethServer è stato
   inserito in una Blacklist (vedi prossimo paragrafo)

.. note:: Si consiglia sempre l'utilizzo di NethServer in modalità Standard. Utilizzare il Mailserver Delegato solo se si necessità dei vantaggi descritti sopra.

Inserimento dell'IP di NethServer nelle blacklist
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

L'inserimento in queste liste è un problema molto comune, esistono vari
tipi di blacklist e i vari provider e amministratori di mailserver ne
usano diverse in maniera arbitraria (vedi anche `Controllare le
blacklist <Antispam#Controllare_le_blacklist>`__).

Come si finisce in queste liste?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

*  Se dal proprio IP è stato spedito spam in passato
*  Utilizzando una connessione dial-up o un ip dinamico (blacklist DUL)
*  Se si ha un ip statico ma il reverse dns (il dns associato al nostro
   ip) contiene stringhe del tipo: adsl, dsl, dynamic, ecc. (DUL)

Soluzioni
~~~~~~~~~

Premesso che la soluzione immediata è quella di utilizzare come server
SMTP il mailserver del provider (come descritto nel pannello
"Distribuzione e-mail"), sarà possibile:

*  in caso di IP dinamico, richiedere un ip statico al provider oppure
   utilizzare il server SMTP del provider
*  in caso di nome DNS generico, chiedere al provider di configurare un
   reverse DNS uguale al record MX
   (http://en.wikipedia.org/wiki/Forward-confirmed\_reverse\_DNS)

Ricezione della posta
=====================

NethService è un potente e sofisticato server di posta elettronica. La
configurazione consigliata permette di sfruttare completamente le
potenzialità del server da parte dei client, in particolare:

*  conservazione email sul server con relativo backup
*  possibilità di inviare e ricevere email anche al di fuori della LAN
*  uniformità di configurazione tra la webmail e il client di posta
   tradizionale
*  utilizzo di un protocollo sicuro per l'invio e ricezione della mail


IMAP e POP3
-----------

I 2 protocolli più diffusi per la gestione email sono IMAP e POP3,
NethService li supporta entrambi, per cui c'è la possibilità di
scegliere quello più adatto alle esigenze specifiche.

POP3
^^^^

POP3 è il primo e più conosciuto protocollo email, è stato progettato
per permettere il download delle email su un singolo client; l'email
rimane nel server finchè non viene richiesta (e scaricata) dal client
sulla macchina locale (se non espressamente specificato una volta
scaricata l'email viene eliminata dal server).

'''PRO: '''Accesso alle email anche quando il client è disconnesso dalla
rete

'''CONTRO: '''Il POP3 non è stato progettato per accedere alle email e
gestirle da remoto: dato che le email risiedono nella macchina locale
che le ha scaricate, accedervi da un altro computer può essere molto
complicato, quando non impossibile.

IMAP
^^^^

Il protocollo IMAP è stato pensato per permettere un accesso interattivo
a caselle di posta multiple da client diversi. Le email vengono gestite
nel mail server e lette dai vari client sfruttando la rete, ma non sono
memorizzate nei client stessi bensì permanentemente immagazzinate e
gestite sul server.

'''PRO: '''E' possibile accedere a tutte le email (nuove e non) da ogni
macchina connessa alla rete, inoltre anche il backup delle email è molto
più agevole. Qualsiasi configurazione sul server (filtri di posta etc.)
viene immediatamente replicata su tutti i client da cui si va a leggere
la posta, tale caratteristica rende molto agevole anche l'eventuale
sostituzione di un computer.

'''CONTRO: '''Se non si è connessi alla rete non è possibile accedere ai
messaggi di posta; questa limitazione può essere comunque aggirata
configurando opportunamente il client per scaricare i messaggi
desiderati (molto utile ad esempio nel caso di utenze con accessibilità
limitata alla rete es: utenze mobili).

Lato Server
-----------

NethService supporta due protocolli standard per la gestione della posta
dal client: POP3 e IMAP. Entrambi i protocolli sono utilizzabili dalla
LAN, ma non da Internet. I corrispondenti protocolli cifrati POP3S e
IMAPS sono invece accessibili anche dall'esterno (Internet).

Il protocollo consigliato per leggere la posta è IMAPS perché:

*  la posta viene conservata sul server e viene copiata nel backup
*  se il pc client viene sostituito, la posta è immediatamente
   accessibile sul nuovo, senza dover compiere operazioni di ripristino,
   oltre alla normale configurazione del programma client
*  permette di *vedere* la propria email da più client in maniera
   uniforme
*  offre totale sicurezza rispetto agli standard non sicuri (POP3 e
   IMAP)
*  offre la possibilità di scaricare la posta anche dall'esterno
*  le regole impostate nel client (eliminazione di email, filtraggio con
   spostamento su cartelle specifiche, etc.) si riflettono
   automaticamente in tutti i client, anche la webmail che risulta
   sempre allineata al client di posta tradizionale

L'invio della posta è sempre permesso dall'interno della LAN tramite
protocollo SMTP, mentre per inviare posta dall'esterno (per esempio
utenti mobili) è necessario utilizzare il protocollo sicuro SSMTP,
pertanto può essere utile configurare già tutti i client per spedire la
posta in SSMTP, evitando differenze di configurazione tra utenze
appartenenti alla LAN e utenze mobili/remote.

Lato Client
-----------

Nonostante sia possibile utilizzare qualsiasi client di posta elettronica con supporto IMAP, si consiglia l'utilizzo di  Mozilla Thunderbird che offre una completa implementazione delle funzionalità legate al protocollo IMAP.
Mozilla Thunderbird è completamente gratuito e può essere scaricato in italiano dal sito http://www.mozilla.com/thunderbird/.

Installazione
=============

Per installare il pacchetto Email fare click su  Configurazione
→Gestione pacchetti. Mettere la spunta su Email e fare click sul
pulsante Avanti. Verrano suggeriti dei pacchetti aggiuntivi da
installare, selezionare quelli che si ritengono utili e confermare le
modifiche al sistema facendo click sul pulsante Applica.

Al termine dell’ installazione verrà mostrato in alto un messaggio che
ci informa che l’operazione è stata completata correttamente.

Gestione Email
==============

Per configurare il mail server fare click su Configurazione →Email.

Verrà aperta una pagina con cinque schede.

Scheda Dominio
--------------

Nella scheda Dominio è possibile creare nuovi domini e modificare o
eliminare quelli già esistenti.

Creare un nuovo dominio
^^^^^^^^^^^^^^^^^^^^^^^

Per creare nuovi domini fare click sul pulsante Crea nuovo. Si aprirà un
pagina con dei campi dove inserire i parametri del nuovo dominio che si
intende creare. Inserire il nuovo dominio ed eventualmente una sua
descrizione sul campo dominio e descrizione .

Scegliere l’ opzione “Consegna localmente” se si vuole che le mail
vengano consegnate alle caselle di posta residenti su NethServer.

Scegliere l’opzione “Passa ad un altro server” se la posta elettronica
del dominio viene gestita da un altro mail server presente sulla rete;
in questo caso inserire l’indirizzo del server a cui deve essere
consegnata.

E’ possibile aggiungere una nota in calce a tutte le e-mail del dominio
mettendo la spunta a “Aggiungi una nota legale in calce ai messaggi
inviati”, in questo caso si apre un camp dove inserire il testo della
nota. Terminato l’inserimento dei dati fare click sul pulsante salva.



La tabella contiene l'elenco dei nomi di dominio internet per cui il
server accetterà mail in arrivo.

Aggiunge un dominio all'elenco di quelli configurati per la ricezione
della posta.

Dominio
    Il nome di dominio, per esempio *nethesis.it*.
Descrizione
    Un campo opzionale utile all'amministratore di sistema per prendere nota
    di informazioni sul dominio.
Consegna localmente
    Selezionare questa opzione per configurare il server in modo
    che le mail in arrivo destinate al dominio specificato vengano salvate
    in cartelle locali.
Passa ad un altro server
    Selezionando questa opzione le mail in arrivo verranno
    inoltrate al server specificato.
Disclaimer (nota legale)
    E' possibile aggiungere automaticamente un messaggio legale (disclaimer)
    a tutte le email in uscita (non destinate al dominio).


Modificare un dominio
^^^^^^^^^^^^^^^^^^^^^

Per modificare un dominio esistente fare click sul pulsante
modifica nella colonna Azioni. Si apre la pagina usata per la creazione
di un nuovo dominio dove è possibile  modificare i parametri; alla fine
delle modifiche fare click sul pulsante salva.

Eliminare un dominio
^^^^^^^^^^^^^^^^^^^^

Per eliminare un dominio esistente fare click sulla freccia accanto al
pulsante modifica sulla colonna azioni; si apre un menù a tendina,
scegliere elimina,  verrà chiesta la conferma fare click sul pulsante
elimina.

Elimina il dominio da quelli gestiti dal server. Eventuali email
destinate al dominio verranno rifiutate.

Scheda Filtro
-------------

Nella scheda Filtro è possibile applicare vari tipi di filtro per i
messaggi ricevuti mettendo la spunta su quelli che si intendo abilitare.
In particolare si può:

*  Abilitare il blocco degli allegati con un certo tipo di estensione
   potenzialmente dannosa; si può scegliere fra file eseguibili (es
   .exe), file di archivio (es .rar, .zip) oppure redigere una lista
   personalizzata di estensioni di file che si vogliono bloccare.
*  Abilitare l’antivirus.
*  Abilitare l’antispam e impostare i punteggi di soglia oltre i quali
   una email è considerata spam  oppure è rifiutata; far scorrere il
   cursore per variare il valore dei punteggi, più questi sono alti più
   il filtro antispam è selettivo. E’ possibile aggiungere un prefisso
   nell’oggetto delle email considerate spam
*  Impostare delle regole di accesso per gli indirizzi
   email, tramite la
   creazione di una lista di indirizzi o domini i quali sono accettati o
   bloccati. Per creare una lista fare click su Regole di accesso per
   indirizzi email. Viene mostrato un pulsante il quale permette di
   aggiungere le voci alla lista. La freccia adiacente il pulsante
   permette di scegliere il tipo di azione da rivolgere all’indirizzo o
   dominio. Per bloccare scegliere blocca da, inserire l’indirizzo email
   o il dominio; fare click sull’icona disco #|image3|\ per salvare. Per
   accettare scegliere accetta da e procedere come sopra. N.B. E’
   fortemente sconsigliato inserire su accetta da un intero dominio. E’
   possibile inoltre bloccare le email verso un indirizzo email o un
   dominio scegliendo blocca a. Per cancellare una  regola già inserita
   fare click sulla “x” posta  in corrispondenza di essa.

Casella di posta
-----------------------

Nella scheda Casella di posta si possono impostare i protocolli di
accesso al mail server e decidere se vengono consentite connessioni non
cifrate. NethServer
supporta sia POP3 sia IMAP i due protocolli più diffusi per la gestione
email per cui c'è la possibilità di scegliere quello più adatto alle
esigenze specifiche, è consigliato impostare la posta con il protocollo
IMAP.

Si può impostare lo spazio del disco riservato ai messaggi che può
essere illimitato oppure avere una determinata taglia; per deciderne le
dimensioni far scorrere il cursore per variare il valore.

Si può decidere se spostare le email considerate spam sul cestino
(cartella “junk mail”); in tal caso è possibile anche quanti giorni il
messaggio di spam viene conservato prima di essere spostato nel cestino;
per impostare il numero di giorni spostare il cursore fino a raggiungere
il valore desiderato.


In questa scheda è possibile configurare alcuni parametri relativi alla
cartelle di posta locali.

IMAP
    Attiva l'accesso alle cartelle del server attraverso il protocollo IMAP (consigliato).

POP3
    Attiva l'accesso alle cartelle del server attraverso il protocollo POP3 (sconsigliato).
Consenti connessioni non cifrate
    Permette di abilitare l'accesso alla cartelle utilizzando protocolli non cifrati (sconsigliato).
Spazio disco
    Permette di limitare l'occupazione del disco da parte delle email.
    
    * Illimitato: selezionare per non imporre limiti
    * Applica quota: limita la massima occupazione di posta per ogni utente al valore
      indicato (quota email).
Sposta nella cartella *junkmail*
    I messaggi email riconosciuti come spam verranno spostati nella cartella
    *junkmail* dell'utente invece che essere consegnati nella Posta in arrivo.


Scheda Messaggi
---------------

Nella scheda Messaggi è possibile impostare la taglia massima accettata
per gli allegati; la posta elettronica è uno strumento adatto
principalmente allo scambio di messaggi per cui è consigliabile tenere
basso tale valore; per lo scambio di file vi sono altri strumenti adatti
a tale scopo es. cartelle condivise; per modificare la taglia consentita
agli allegati muovere il cursore fino a raggiungere il valore
desiderato.

Si può decidere la finestra di tempo entro cui sarà tentato l’invio; per
decidere quanto grande sarà il lasso di tempo muovere il cursore fino a
raggiungere il valore desiderato.

NethServer può consegnare i messaggi in uscita direttamente a
destinazione (raccomandato nella maggior parte dei casi) oppure
consegnarli attraverso il server SMTP del provider (raccomandato in caso
di connessione inaffidabile o ADSL di tipo residenziale, IP dinamico, IP
in Blacklist, etc),in tal caso mettere la spunta su “Invia tamite
smarthost”, verranno mostrati i campi per inserire i parametri
necessari, quali nome smarthost, nome utente e password, e porta; per
configurare il server mailhost fare riferimento al proprio ISP.

Configura la gestione dei messaggi email.

Accetta messaggi fino a
    Utilizzare il cursore per selezionare la dimensione massima di un
    singolo messaggio email. Il server rifiuterà email più grandi del valore
    impostato, ritornando un errore esplicativo.
Tenta l'invio per
    Utilizzare il cursore per selezionare il tempo massimo per cui il server
    tenterà di inviare un messaggio. Quando verrà raggiunto il tempo massimo
    e l'email non sarà ancora stata consegnata, il mittente riceverà un
    errore e il messaggio verrà eliminato dalla coda di invio, il server non
    tenterà più di consegnarlo.
Invia tramite smarthost
    Il server tenterà di inviare le mail direttamente a
    destinazione (raccomandato nella maggior parte dei casi). Selezionando
    invece l'invio tramite smarthost, tenterà di consegnarli attraverso il server
    SMTP del provider (raccomandato in caso di connessione inaffidabile o
    ADSL di tipo residenziale, IP dinamico, etc).
Nome host
    Il nome del server mail del provider.
Porta
    La porta del mail server del provider.
Nome utente
    Se il server del provider richiede autenticazione, specificare il nome
    utente.
Password
    La password richiesta dal provider.
Consenti connessione non cifrata
    Normalmente, in caso di connessione autenticata (con utente e password),
    si utilizzerà una connessione cifrata. Selezionando questa opzione, sarà
    possibile anche usare una connessione non sicura per collegarsi al
    provider (sconsigliato, utilizzare con provider problematici).


Scheda gestione coda
--------------------

Nella scheda Gestione coda è mostrata una tabella dove ci sono le email
in uscita; è possibile aggiornare la tabella con il pulsante
Aggiorna tentare di “forzare l’invio” di una email con il pulsante tenta
l’invio oppure eliminare una email con il pulsante elimina.


La scheda permette di gestire la coda di email in transito nel server.
La tabella elenca tutte le mail in attesa di essere consegnate,
normalmente è vuota. Verranno mostrati i seguenti campi:

* Id: identificativo del messaggio
* Mittente: l'indirizzo email di chi ha inviato il messaggio
* Dimensione: la grandezza in byte della mail
* Data: la data in cui è stata creata la mail
* Destinatari: l'elenco dei destinatari


Elimina
^^^^^^^

E' possibile eliminare una mail in coda, per esempio una mail inviata
per errore o di grandi dimensioni.

Elimina tutti
^^^^^^^^^^^^^

Il pulsante eliminerà tutte le email in coda.

Tenta l'invio
^^^^^^^^^^^^^

Normalmente, il server, in caso di problemi durante l'invio della mail,
ritenta ad intervalli regolari. Facendo clic su Tenta l'invio, le email
verranno inviate immediatamente.

Aggiorna
^^^^^^^^

Ricarica l'elenco delle mail in coda.

Filtro
======

Configura le opzioni di filtraggio della mail (antivirus, antispam,
allegati vietati, etc).

Antivirus
    Abilita la scansione antivirus delle email in transito.
Antispam
    Abilita la scansione antispam delle email in ingresso.
Prefisso Spam
    Aggiunge il prefisso sottostante all'oggetto delle email riconosciute
    come spam.
Blocco allegati
    Il mail server bloccherà le email che contengono gli allegati dei tipi
    specificati.
Eseguibili
    Il mail server bloccherà i programmi eseguibili allegati alle email.
Archivi
    Il mail server bloccherà le email con allegati file di archivio (zip,
    rar, etc).
Lista personalizzata
    E' possibile definire un elenco di estensioni che verranno bloccate, per
    esempio doc, pdf, etc, (senza punto iniziale, doc e non .doc).




===============
Indirizzi email
===============

Per i nuovi utenti registrati su Nethserver sarà creato in automatico un
indirizzo e-mail con il dominio introdotto in fase di installazione es.
*mailto:nuovo_utente@miodominio.it*
(vedi paragrafo Dominio capitolo Installazione.) 

Installazione
=============

Il modulo di gestione degli indirizzi email viene installato
automaticamente con l’installazione del pacchetto mail server (vedi
Capitolo Email)

Gestione
========

Per gestire gli indirizzi email andare sulla sezione Gestione→ Indirizzi
email.

Si aprirà una pagina dove viene mostrata una tabella con tutti gli
indirizzi email registrati su NethServer.

Creare nuovo indirizzo email
----------------------------

Per creare un nuovo indirizzo email fare click sul pulsante crea nuovo.
Si aprirà una pagina con i campi per inserire i dati.

Occorre inserire un nome indirizzo e scegliere il dominio a cui
apparterrà (se nel server ce ne sono registrati più di uno altrimenti
sarà messo di default quello principale), ed una eventuale descrizione.

Per ultimo scegliere a quale gruppo o utente apparterrà tale indirizzo e
mettere la spunta su “solo per reti locali” su i messaggi di tale
indirizzo non potranno uscire dalla LAN (es. indirizzi email destinati
alla posta interna)

Fare click sul pulsante salva.


Crea l'associazione tra un nuovo indirizzo di posta elettronica ed un
utente o a un gruppo già presente nel sistema.

Indirizzo email
    Specificare nel campo di testo solo la parte prima del carattere
    **@**. Scegliere poi dal menù a tendina se l'indirizzo è per un
    dominio specifico o per *tutti i domini* presenti nel sistema.
Descrizione
    Un campo di testo libero per registrare una qualsiasi annotazione.
Account
    Selezionare un utente o un gruppo tra quelli già presenti nel
    sistema da associare all'indirizzo email.
Solo reti locali
    Abilitando questa opzione verrà bloccata la ricezione di messaggi
    provenienti da mittenti esterni.

Modificare un indirizzo email
-----------------------------

Per modificare un’indirizzo email fare click sul pulsante modifica nella
colonna azioni. Si aprirà una pagina di creazione dove è possibile
modificare l’utente o il gruppo a cui appartiene.

Eliminare un indirizzo email
----------------------------

Per eliminare un indirizzo email fare click sulla freccia accanto al
pulsante modifica nella colonna azioni. Verrà chiesta la conferma
dell’operazione, fare click sul pulsante elimina per eliminare
definitivamente l’indirizzo email.

Elimina l'indirizzo di posta elettronica. Questo non influisce sui
messaggi già recapitati all'utente o al gruppo associato all'indirizzo.
Futuri messaggi destinati all'indirizzo saranno rifiutati.




=======================
Indirizzi email esterni
=======================

Gli indirizzi email esterni sono caselle di posta elettronica che
vengono controllate ad intervalli regolari tramite i protocolli **POP3**
o **IMAP**.  I messaggi ad essi recapitati vengono scaricati e
consegnati agli utenti o gruppi locali, in base alla configurazione
sottostante.

Indirizzi esterni
=================

Configura la lista degli indirizzi esterni e l'associazione con l'utente di sistema.

Crea / Modifica
---------------

Crea o modifica un indirizzo esterno.

Indirizzo email
    L'indirizzo email esterno da controllare.

Protocollo
    Il protocollo utilizzato per accedere al server remoto. Può essere *POP3* o *IMAP* (consigliato).

Indirizzo server
    Nome host o indirizzo IP del server remoto.

Nome utente
    Nome utente utilizzato per l'autenticazione dell'account remoto.

Password
    Password utilizzata per l'autenticazione dell'account remoto.

Account
    Seleziona l'utente o il gruppo a cui verranno consegnate i messaggi scaricati. 

Abilita SSL
    Abilita la cifratura della connessione con il server remoto.

Elimina messaggi scaricati
    Se abilitato, i messaggi scaricati verranno eliminati dal server remoto (consigliato). Lasciare disabilitato se si desidera mantenere
    una copia sul server remoto.

Elimina
-------

L'eliminazione di un account *non* comporta l'eliminazione dei messaggi già consegnati.


Scarica ora
-----------

Avvia immediatamente il controllo di tutte gli indirizzi esterni.


Generale
========

Abilita
    Consente di abilitare o disabilitare il demone Fetchmail che si
    occupa del download della posta dagli indirizzi esterni.

Controlla ogni
    Frequenza del controllo di nuovi messaggi sugli indirizzi esterni.
    Si consiglia un intervallo di 15 minuti.












