====================
Accesso a NethServer
====================

NethServer viene gestito tramite interfaccia web quindi per accedere
alle pagine di gestione si deve usare un programma per la navigazione in
internet (es.  FireFox, IE oppure Chrome) su di un PC connesso alla
stessa rete del server.

Sul campo degli indirizzi digitare:

https://ip\_nethserver <https://192.168.1.x:980>/server-manager

dove ip\_nethserver è quello che è stato deciso al momento
dell’installazione (vedi paragrafo Indirizzo IP)

A causa dell’uso del protocollo di crittografia https per la
comunicazione con il server  il browser ci avviserà che la connessione
non è affidabile perché non ha un certificato valido. 

Per entrare nel server occorre perciò fare click sulla voce “sono
consapevole dei rischi”, verrà così mostrato il pulsante Aggiungi
Eccezione. Fare click su Aggiungi Eccezione, si aprirà un’ altra
finestra dove si deve fare click sul pulsante Conferma eccezione di
sicurezza.

La connessione rimarrà sicura e criptata ma il certificato del tuo
server non sarà ufficiale. Un certificato valido ha un costo di
abbonamento annuale e non è indispensabile in questa situazione. Vedi
figura TODO

#|image0|

Log in
======

La prima pagina dell’interfaccia web è quella di log in. Viene richiesto
nome utente e password. Per configurare il server occorre accedere con
diritti di amministratore quindi:

nome utente: admin

password: password\_di\_root (la quale, come già detto è sincronizzata
con quella di admin.

#|image1|

=============================
Amministrazione di Nethserver
=============================

Status
======

Dashboard
---------

La pagina mostrata di default dopo il log in è la Dashboard; qui viene
visualizzato un riepilogo dello stato del sistema e delle sue
impostazioni.

Vengono riportate la configurazione di rete, l’uso della memoria, l’uso
del disco, informazioni sul carico ed uptime della macchina.

Arresto
=======
La macchina dove è installato Nethserver può essere riavviata o spenta andando su Amministrazione→ Arresto. Selezionare l’opzione Riavvia oppure Spegni e 
fare click sul pulsante Arresta il sistema


Consente di spegnere o riavviare il server.
E' obbligatorio arrestare il sistema prima di spegnere il server.
L'esecuzione di queste funzioni richiede alcuni minuti.

ATTENZIONE! Cliccando ARRESTA IL SISTEMA l'operazione inizierà
immediatamente.

Riavvia
    Riavvia il server terminando tutti i processi in esecuzione.
Spegni
    Spegne il server dopo aver terminato tutti i processi in esecuzione.


Visualizza Log
==============
Come per ogni sistema Linux, Nethserver è molto ricco di file di log che registrano tutte le operazioni che vengono svolte; ciò può essere molto utile in situazioni di malfunzionamento del sever per individuare i problemi in maniera rapida.
Per visualizzare i file di log fare click su Amministrazione→ Visualizza Log. Si apre una pagina con l’elenco di tutti i file di log disponibili; fare click sui file che si intendo visualizzare.

Trova e mostra il contenuto dei file di log.

Trova nei file di log
---------------------

Permette di consultare tutti i file di log del server e di effettuare
ricerche approfondite all'interno degli stessi.

Trova
    Consente di ricercare termini ed espressioni all'interno di tutti i
    log del server.

È possibile accedere direttamente a ciascun log attraverso i link
riportati nella pagina.

Visualizzazione singolo log
---------------------------

Permette di consultare il contenuto più recente del log selezionato e di
seguirne il popolamento in tempo reale.

Chiudi
    Chiude la finestra relativa al log selezionato e torna alla pagina
    principale della visualizzazione log.
Svuota
    Permette di svuotare il contenuto della finestra del log. I dati
    vengono rimossi solamente dalla finestra di visualizzazione, non
    viene modificato il contenuto del log.
Segui
    Aggiorna in tempo reale la finestra di visualizzazione con le nuove
    informazioni che vengono scritte nel log.
Ferma
    Interrompe l'aggiornamento in tempo reale della visualizzazione del
    log.


Accesso remoto
==============

Reti locali
-----------

Per ragioni di sicurezza alcuni servizi del server sono a disposizione
soltanto della rete locale; eventuali reti private (ad esempio reti
collegate in VPN) possono avere gli stessi privilegi della rete locale
se configurate in questo pannello.

Il pannello può essere utilizzato anche per specificare instradamenti
particolari che non facciano uso del default gateway (ad esempio per
raggiungere reti private collegate tramite linee dedicate o simili).

E' possibile consentire l'accesso a computer su reti remote
all'interfaccia web, inserendo le reti abilitate qui.

I computer abilitati potranno accedere all'interfaccia web in HTTPS.


Crea / Modifica
^^^^^^^^^^^^^^^

Crea un nuovo instradamento verso una rete remota e/o permette ad una
rete remota di accedere a tutti i servizi del server.

Indirizzo di rete
    L'indirizzo della rete verso cui stabilire il nuovo instradamento

Maschera di rete
    La maschera della rete verso cui stabilire il nuovo instradamento

Indirizzo del router
    Indirizzo del gateway da utilizzare per raggiungere la rete
    specificata, questo campo non è obbligatorio.

Descrizione
    Un campo di testo libero, per registrare una qualsiasi annotazione.

Una volta creato l'instradamento, sarà possibile modificare solo
l'indirizzo del router e la descrizione.



Accesso web
-----------

Accesso all'interfaccia web di configurazione.

Indirizzo di rete
    È l'indirizzo dal quale sarà consentito accedere all'interfaccia
    web.

Maschera di rete
    Maschera di rete dell'indirizzo. Per consentire l'accesso ad un solo
    host, utilizzare come maschera di rete 255.255.255.255.

SSH
---

Gestione dell'accesso SSH (Secure Shell)  al server.

Abilitato / Disabilito
    Abilita / disabilita l'accesso SSH.

Porta TCP
    Inserire la porta TCP usata per l'accesso SSH.

Accetta connessioni da reti locali
    Accesso SSH abilitato solo da connessioni provenienti da reti
    locali.

Accetta connessioni da qualsiasi rete
    Accesso SSH abilitato per connessioni provenienti da qualsiasi rete.

Consenti l'accesso per l'utente root
    Consenti l'accesso SSH all'utente root (utente amministrativo).

Consenti l'autenticazione mediante password
    Consente l'accesso SSH tramite l'autenticazione con password
    semplice. Se non abilitato, gli utenti si potranno autenticare
    solamente utilizzando una chiave crittografica.

====
Rete
====

Cambia impostazioni delle interfacce di rete. Le interfacce di rete presenti nel sistema sono rilevate automaticamente.

Stato
=====

Link
    Indica se la scheda è collegata a qualche apparato di rete (ad es. cavo
    ethernet collegato allo switch aziendale).

Modello
    Modello della scheda di rete utilizzata.

Velocità
    Indica la velocità che la scheda di rete ha negoziato (espressa in Mb/s).

Driver
    Il Driver che il sistema utilizza per pilotare la scheda.

Bus
    Su quale bus è collegata la scheda di rete (es: pci, usb).



Modifica
========

Modifica le impostazioni dell'interfaccia di rete

Scheda
    Nome dell'interfaccia di rete. Questo campo non può essere
    modificato.

Indirizzo MAC
    Indirizzo fisico della scheda di rete. Questo campo non può essere
    modificato.

Ruolo
    Il ruolo indica la destinazione d'uso dell'interfaccia, ad esempio:
    
    * Green -> LAN Aziendale
    * Red -> Internet, ip pubblici

Modalità
    Indica quale metodo verrà usato per attribuire l'indirizzo IP alla
    scheda di rete, valori i possibili sono *Statico* e *DHCP*.

Statico
    La configurazione è attribuita staticamente.

    * Indirizzo IP: indirizzo IP della scheda di rete
    * Netmask: netmask della scheda di rete
    * Gateway: default gateway del server

DHCP
    La configurazione è attribuita dinamicamente (disponibile solo per interfacce
    RED)



===================
Dati organizzazione
===================

Questi campi contengono i valori di default per l'azienda.
I dati indicati verranno utilizzati come default durante la creazione
dei nuovi utenti.

Per ogni utente è possibile specificare valori diversi nel pannello
Utenti, scheda Dettagli.
La variazione di questi dati sostituisce i valori di default per gli
utenti che non hanno campi personalizzati.

**ATTENZIONE**: ogni modifica ai dati inseriti rigenera il certificato
SSL.

Azienda
    Inserire il nome dell'azienda.
Città
    Inserire la città dell'azienda.
Ufficio
    Inserire il dipartimento o ufficio i cui componenti avranno accesso
    ai servizi del server.
Telefono
    Inserire il numero di telefono dell'azienda.
Indirizzo
    Inserire l'indirizzo dell'azienda.


==============
Profilo utente
==============

Nome
    È il nome dell'utente, per esempio "Mario".

Cognome
    Il cognome dell'utente, per esempio "Rossi".

Indirizzo email esterno
    Indirizzo email dell'utente, presso un provider di posta
    elettronica esterno. Se specificato, questo indirizzo viene
    utilizzato dal sistema nelle procedure di recupero e di rinnovo
    della password.

Per i seguenti campi è possibile specificare un valore personalizzato,
altrimenti vale l'impostazione effettuata dal modulo "Dati
organizzazione", disponibile solo per l'amministratore del sistema.

* Società
* Ufficio
* Indirizzo
* Città
* Telefono


Cambia Password
===============

Cambia la password attuale con una nuova password.

Password attuale
    Inserire la password attuale.

Nuova password
    Inserire la nuova password.

Ripeti nuova password
    Ripetere la nuova password: deve coincidere con quella del campo
    *Nuova Password*.



