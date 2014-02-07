================
Gestione Account
================

I pannelli e gruppi vengono visualizzati automaticamente quando viene installato un pacchetto che dipende da questo modulo.


Utenti
======

L'utente di sistema è necessario per accedere a molti servizi erogati da NethServer (email, cartelle condivise etc.).
Ogni utente è caratterizzato da una coppia di credenziali (utente e password). 
Un utente appena creato rimane bloccato finchè non viene settata una password. 
Un utente bloccato non può utilizzare i servizi di NethServer che richiedono autenticazione.

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



Creazione nuovo utente
----------------------

Per creare un nuovo utente occorre fare click sul pulsante "Crea Nuovo".

Il nome utente può contenere solo lettere minuscole, numeri, trattini,
punti e trattino basso (\_) e deve iniziare con una lettera minuscola.
Per esempio "luisa", "mrossi" e "liu-jo" sono nomi utente validi, mentre "4amici", "Franco Neri" e "aldo/sbaglio" non lo sono.

Per scegliere il nome utente è consigliabile scegliere uno standard che
rende tutti i nomi presenti su NethServer omogenei ad una precisa
logica; (es. mrossi oppure marior se si crea un utente Mario Rossi
e ciò vale per tutti gli altri utenti).


Scheda Utenti
^^^^^^^^^^^^^

Nella scheda Utente vanno inseriti:

* Il nome scelto per il nuovo utente nel campo *Nome Utente*.
* Il vero nome e cognome dell’utente nel campo *Nome Cognome*.
* Il campo *Gruppi* serve ad aggiungere l’utente ad un gruppo.


Il gruppo va cercato digitando il nome nel campo, il sistema ricerca automaticamente
fra tutti i gruppi, man mano che che viene composto il nome; trovato il
gruppo fare click sul pulsante aggiungi.

Sotto il campo verrà creata la tabella dei gruppi di cui l’utente è
membro.

Per cancellare l’ utente da un gruppo fare click sulla “x” posta in
corrispondenza del gruppo.


Scheda Dettagli
^^^^^^^^^^^^^^^

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
potrà usufruire fra quelli installati. Mettere la spunta su quelli da assegnare.


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


Password nuovo utente
----------------------

Il nuovo utente creato sarà immediatamente visibile sulla tabella
utenti; il suo nome è contraddistinto dall'icona con un lucchetto che indica
che non potrà avere accesso al sistema fino a quando non viene cambiata
la password.

Per cambiare la password fare click sul pulsante modifica sulla colonna
*Azioni* in corrispondenza della riga dell’utente. Verrà aperta la pagina
per la creazione dell’utente; fare click sul pulsante Cambia password. A
questo punto verrà chiesta la nuova password.

La password deve soddisfare i seguenti requisiti:

 * deve contenere almeno 5 caratteri diversi
 * non deve essere presente nei dizionari di parole comuni
 * deve essere diversa dallo username
 * non può avere ripetizioni di pattern formati da più 3 caratteri (ad esempio la password As1.$As1.$ non è valida)



Modifica di un utente
---------------------

Per modificare un utente fare click sul pulsante modifica nella colonna
*Azioni*. Verrà mostrata la pagina per la creazione dell’utente dove sarà
possibile modificare i dati esistenti.

Eliminazione di un utente
-------------------------

Per eliminare un utente fare click sulla freccia adiacente il pulsante
modifica sulla colonna azioni. Si apre un menù a tendina, fare click
sulla voce *Elimina*. Tutti i dati dell'utente verranno cancellati.

Blocca / Sblocca
----------------

Consente di bloccare o sbloccare un utente. I dati dell'utente non
verranno eliminati.


Gruppi
======

Per gestire i gruppi all’ interno di NethServer andare sulla sezione
Gestione→ Gruppi; all’interno di questa sezione si possono creare nuovi
gruppi, oppure eliminare e modificare gruppi già esistenti. Ad ogni
gruppo è possibile assegnare dei permessi di accesso per le varie
applicazioni di Nethserver.


Creazione nuovo gruppo
----------------------

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
    Sotto il campo verrà creata la tabella degli utenti appartenenti al
    gruppo.



Servizi
^^^^^^^^^^^^^^

Nella scheda Servizi è possibile selezionare i servizi che si vogliono
assegnare al gruppo.


Email
    Attiva la casella di posta per il gruppo.
Invia copia del messaggio ai membri del gruppo
    Abilita il comportamento standard della lista di distribuzione: ogni
    e-mail inviata al gruppo verrà duplicata a ciascun utente membro.
Consegna il messaggio in una cartella condivisa
    Ogni email inviata al gruppo verrà consegnata in una cartella IMAP
    condivisa visibile ai soli membri del gruppo.
    La sottoscrizione della cartella condivisa è automatica.
Crea gli indirizzi email predefiniti
    Crea automaticamente gli indirizzi email associati alla casella di
    posta del gruppo per tutti i domini definiti nel server, del tipo
    *nome_gruppo@dominio*. Tali indirizzi email possono essere modificati
    nella sezione *Gestione -> Indirizzi email*.
    


Modifica di un gruppo
---------------------
Consente la creazione, la modifica o la rimozione di gruppi
di utenti utilizzati per assegnare servizi e permessi di accesso agli
utenti o come liste di distribuzione email.

Per modificare un gruppo fare click sul pulsante modifica nella colonna
*Azioni*. Verrà mostrata la pagina per la creazione del gruppo dove sarà
possibile modificare sia i dati del Gruppo sia i Servizi ad esso
associati.


Eliminazione di un Gruppo
-------------------------

Questa azione consente di rimuovere i gruppi definiti e le relative
liste di distribuzione. Le caselle di posta condivise associate a questo gruppo verranno eliminate.















