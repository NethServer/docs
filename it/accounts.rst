================
Gestione Account
================

Gruppi
======

Per gestire i gruppi all’ interno di NethServer andare sulla sezione
Gestione→ Gruppi; all’interno di questa sezione si possono creare nuovi
gruppi, oppure eliminare e modificare gruppi già esistenti. Ad ogni
gruppo è possibile assegnare dei permessi di accesso per le varie
applicazioni di Nethserver.

Installazione
-------------

L’installazione delle funzionalità utenti e gruppi è manuale, ma avviene
automaticamente quando viene installato un pacchetto che ha bisogno di
questo modulo.

Creazione nuovo gruppo
----------------------

Per creare un nuovo gruppo fare click sul pulsante crea nuovo che si
trova a inizio pagina. Verrà aperta una nuova pagina dove ci sono due
schede: Gruppo e Servizi.

N.B.

Il nome gruppo può contenere solo lettere minuscole, numeri, trattini,
punti e trattino basso (\_) e deve iniziare con una lettera minuscola 

Scheda gruppo
^^^^^^^^^^^^^

Nella scheda Gruppo vanno inseriti:

Il nome scelto per il nuovo gruppo nel campo nome gruppo .

Una descrizione delle caratteristiche del gruppo nel campo descrizione.

Il campo membri serve ad aggiungere gli utenti al gruppo; l’utente va
inserito digitando il suo nome nel campo, il sistema ricerca
automaticamente fra tutti gli utenti, man mano che che viene composto il
nome, trovato l’ utente fare click sul pulsante aggiungi.

Sotto il campo verrà creata la tabella degli utenti appartenenti al
gruppo.

Per cancellare un membro dal gruppo fare click sulla “x” posta in
corrispondenza dell’utente.

Scheda Servizi
^^^^^^^^^^^^^^

Nella scheda Servizi è possibile selezionare i servizi che si vogliono
assegnare al gruppo, mettere la spunta su quelli che gli si vogliono
associare.

La creazione del gruppo sarà completa facendo click sul pulsante salva.

Il sistema crea di default il gruppo domadmins durante l’installazione
del modulo.

Modifica di un gruppo
---------------------

Per modificare un gruppo fare click sul pulsante modifica nella colonna
Azioni. Verrà mostrata la pagina per la creazione del gruppo dove sarà
possibile modificare sia i dati del Gruppo sia i Servizi ad esso
associati.

Eliminazione di un gruppo
-------------------------

Per eliminare un gruppo fare click sulla freccia adiacente al pulsante
modifica. Si apre un menù a tendina, fare click sulla voce elimina.
Verrà chiesta la conferma, fare click sul pulsante elimina per eliminare
definitivamente il gruppo.




Consente la creazione, la modifica o la rimozione di gruppi
di utenti utilizzati per assegnare servizi e permessi di accesso agli
utenti o come liste di distribuzione email.

Crea / Modifica
===============

Gruppo
-------------

Consente la creazione di un nuovo gruppo e l'associazione dei relativi
membri.

Nome gruppo
    Può contenere solo lettere minuscole, numeri,
    trattini, punti e trattino basso (underscore) e deve iniziare con
    una lettera minuscola. Per esempio "vendite", "beta3" e "riv_net"
    sono nomi validi, mentre "3d", "Ufficio Vendite" e "q&a" non lo
    sono.
Descrizione
    Inserire una breve descrizione del gruppo.
Membri
    Consente di ricercare gli utenti presenti sul server. Gli utenti si
    associano al gruppo con il tasto *Aggiungi*. Per eliminare gli
    utenti elencati usare il pulsante *X*.

Servizi
-------

Abilita i servizi disponibili sul nuovo gruppo.

Email
    Attiva la casella di posta per il gruppo.
Invia copia del messaggio ai membri del gruppo
    Abilita il comportamento standard della lista di distribuzione: ogni
    e-mail inviata al gruppo verrà duplicata a ciascun utente membro.
Consegna il messaggio in una cartella condivisa
    Ogni email inviata al gruppo verrà consegnata in una cartella IMAP
    condivisa visibile ai soli membri del gruppo.
Crea gli indirizzi email predefiniti
    Crea automaticamente gli indirizzi email associati alla casella di
    posta del gruppo per tutti i domini definiti nel server, del tipo
    *nome_gruppo@dominio*. Tali indirizzi email possono essere modificati
    nella sezione *Gestione -> Indirizzi email*.

Casella email
    Abilita la casella email per il gruppo.

Invia copia del messaggio ai membri del gruppo
    Ogni messaggio destinato al gruppo verrà copiato e consegnato ad ogni membro del gruppo.

Consegna il messaggio in una cartella condivisa
    I messaggi destinati al gruppo saranno consegnati in un'unica cartella condivisa in sola lettura tra i membri del gruppo.
    La sottoscrizione della cartella condivisa è automatica.


Elimina
=======

Questa azione consente di rimuovere i gruppi definiti e le relative
liste di distribuzione. Le caselle di posta condivise associate a questo gruppo verranno eliminate.








Utenti
======

Per gestire gli utenti all’ interno di NethServer andare sulla sezione
Gestione→ Utenti.

All’interno di questa sezione è possibile creare nuovi utenti del
sistema oppure eliminare o modificare gli utenti già esistenti.

L'utente di sistema è necessario per accedere a molti servizi erogati da
NethServer (email, cartelle condivise etc.).

Ogni utente è caratterizzato da una coppia di credenziali (utente e
password). Un utente appena creato rimane bloccato finché non viene
settata una password. Un utente bloccato non può utilizzare i servizi del
server che richiedono autenticazione.

Installazione
-------------

L’installazione delle funzionalità utenti e gruppi avviene
automaticamente quando viene installato un pacchetto che dipende da
questo modulo.

Creazione nuovo utente
----------------------

Per creare un nuovo utente occorre fare click sul pulsante crea nuovo ad
inizio pagina.

Il nome utente può contenere solo lettere minuscole, numeri, trattini,
punti e trattino basso (\_) e deve iniziare con una lettera minuscola.

Per scegliere il nome utente è consigliabile scegliere uno standard che
rende tutti i nomi presenti su NethServer omogenei ad una precisa
logica; (es. mrossi oppure mario\_rossi se si crea un utente Mario Rossi
e ciò vale per tutti gli altri utenti).

Verra aperta una nuova pagina dove ci sono tre schede: Utente, Dettagli,
Servizi

Scheda Utenti
^^^^^^^^^^^^^

Nella scheda Utente vanno inseriti:

Il nome scelto per il nuovo utente nel campo Nome Utente.

Il vero nome  e cognome dell’utente nel campo Nome Cognome.

Il campo Groups serve ad aggiungere l’utente ad un gruppo; il gruppo va
cercato digitando il nome nel campo, il sistema ricerca automaticamente
fra tutti i gruppi, man mano che che viene composto il nome; trovato il
gruppo fare click sul pulsante aggiungi.

Sotto il campo verrà creata la tabella dei gruppi di cui l’utente è
membro.

Per cancellare l’ utente da un gruppo fare click sulla “x” posta in
corrispondenza del gruppo.


Informazioni di base sull'utente. Questi campi devono essere
necessariamente compilati.

Nome utente
    Il *Nome utente*, sarà utilizzato per accedere ai servizi. Può
    contenere solo lettere minuscole, numeri, trattini, punti e
    underscore (\_) e deve iniziare con una lettera minuscola. Per
    esempio "luisa", "mrossi" e "liu-jo" sono nomi utente validi, mentre
    "4amici", "Franco Neri" e "aldo/sbaglio" non lo sono.
Nome
    È il nome reale dell'utente. Per esempio "Mario"
Cognome
    Il cognome dell'utente
Gruppi
    Grazie alla barra di ricerca è possibile selezionare i gruppi ai
    quali aggiungere l'utente. L'utente può appartenere a più gruppi.


Scheda Dettagli
^^^^^^^^^^^^^^^

Nella scheda Dettagli è possibile introdurre informazioni specifiche per
l’utente come Società, Ufficio, Indirizzo, Città, Telefono.

Questa sezione raccoglie le informazioni sull'organizzazione a cui
appartiene l'utente e sono facoltative. I valori di default si possono
specificare dalla voce del menù *Dati organizzazione*.

Per i seguenti campi è possibile specificare un valore personalizzato,
altrimenti vale l'impostazione effettuata dal modulo "Dati
organizzazione", disponibile solo per l'amministratore del sistema.

* Società
* Ufficio
* Indirizzo
* Città
* Telefono


Scheda Servizi
^^^^^^^^^^^^^^

Nella scheda Servizi è possibile selezionare i servizi di cui l’utente
potrà usufruire fra quelli

installati. Mettere la spunta su quelli da assegnare.

La creazione dell’ utente sarà completa facendo click sul pulsante
salva.


Shell remota (SSH)
    Consente all'utente di accedere ad una shell sicura sul server.

Casella email
    Abilita la casella email per l'utente.

Inoltro messaggi
    Consente di inoltrare le email ricevute ad un indirizzo alternativo.

Tieni una copia sul server
    Le email inoltrate saranno comunque salvate nella casella email dell'utente.

Quota email personalizzata
    Permette di specificare un valore di quota diverso da quello di default.

Personalizza tempo di permanenza delle email di spam.
    Le email di spam vengono eliminate ad intervalli regolari. Spuntando
    la casella è possibile stabilire per quanti giorni i messaggi
    classificati come spam arrivati a questo utente, verranno mantenuti
    nel sistema prima di essere eliminati.

Indirizzi email
    Lista degli indirizzi email associati all'utente.

Cartelle condivise (Samba)
    Concede all'utente l'autorizzazione ad accedere alle cartelle
    condivise tramite Samba.


Password nuovo utente.
----------------------

Il nuovo utente creato sarà immediatamente visibile sulla tabella
utenti; il suo nome è contraddistinto dall'icona #|image2|\ che indica
che non potrà avere accesso al sistema fino a quando non viene cambiata
la password.

Per cambiare la password fare click sul pulsante modifica sulla colonna
Azioni in corrispondenza della riga dell’utente. Verrà aperta la pagina
per la creazione dell’utente; fare click sul pulsante Cambia password. A
questo punto verrà chiesta la nuova password.

Il sistema è impostato per richiedere una password efficace in termini
di sicurezza, perciò essa dovrà avere determinati requisiti per essere
valida. Tipicamente dovrà essere lunga più di 6 caratteri contenere
almeno un numero, un carattere maiuscolo e un carattere speciale. Fare
click su salva per procedere al cambio della password.

Permette di configurare per la prima volta, o modificare, la password dell'utente.

La password deve soddisfare i seguenti requisiti:

 * deve contenere almeno 5 caratteri diversi
 * non deve essere presente nei dizionari di parole comuni
 * deve essere diversa dallo username
 * non può avere ripetizioni di pattern formati da più 3 caratteri (ad esempio la password As1.$As1.$ non è valida)



Modifica di un utente
---------------------

Per modificare un gruppo fare click sul pulsante modifica nella colona
Azioni. Verrà mostrata la pagina per la creazione dell’utente  dove sarà
possibile modificare i dati Utente, i Dettagli e i servizi ad esso
associati.

Eliminazione di un utente
-------------------------

Per eliminare un utente fare click sulla freccia adiacente il pulsante
modifica sulla colonna azioni. Si apre un menù a tendina, fare click
sulla voce elimina. Verrà chiesta la conferma, fare click sul pulsante
elimina per eliminare definitivamente l’utente.

Elimina l'utente. Tutti i dati dell'utente verranno cancellati.

Blocca / Sblocca
----------------

Consente di bloccare o sbloccare un utente. I dati dell'utente non
verranno eliminati.









