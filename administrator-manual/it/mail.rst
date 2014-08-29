.. _email-section:

=====
Email
=====

Nethserver ha la possibilità di svolgere la funzione di un potente e
sofisticato mail server. Le pagine di configurazione e gestione sono
molto semplici e intuitive.

Per i nuovi utenti registrati su Nethserver sarà creato in automatico un
indirizzo e-mail con il dominio introdotto in fase di installazione es.
nome.cognome@miodominio.it
(vedi paragrafo Dominio capitolo Installazione). Ogni utente potrà
sfruttare le potenzialità del mail server in particolare:

*  conservazione email sul server con relativo backup
*  possibilità di inviare e ricevere email anche al di fuori della LAN
*  uniformità di configurazione tra la webmail e il client di posta
   tradizionale
*  utilizzo di un protocollo sicuro per l'invio e ricezione della mail

Installazione
=============

Per installare il pacchetto Email fare clic su 
Gestione pacchetti. Mettere la spunta su Email e fare click sul
pulsante Avanti. Verranno suggeriti dei pacchetti aggiuntivi da
installare, selezionare quelli che si ritengono utili e confermare le
modifiche al sistema facendo click sul pulsante Applica.

Al termine dell'installazione verrà mostrato un messaggio che
ci informa che l’operazione è stata completata correttamente.

Gestione Email
==============

Per configurare il mail server fare clic su Email.

Verrà aperta una pagina con cinque schede.

Scheda Dominio
--------------

Nella scheda Dominio è possibile creare nuovi domini e modificare o
eliminare quelli già esistenti.

La tabella contiene l'elenco dei nomi di dominio internet per cui il
server accetterà mail in arrivo.

Creare un nuovo dominio
^^^^^^^^^^^^^^^^^^^^^^^

Per creare nuovi domini fare click sul pulsante Crea nuovo. Si aprirà un
pagina con dei campi dove inserire i parametri del nuovo dominio che si
intende creare. Inserire il nuovo dominio ed eventualmente una sua
descrizione sul campo dominio e descrizione .

Scegliere l'opzione “Consegna localmente” se si vuole che le mail
vengano consegnate alle caselle di posta residenti su |product|.

Scegliere l’opzione “Passa ad un altro server” se la posta elettronica
del dominio viene gestita da un altro mail server presente sulla rete;
in questo caso inserire l’indirizzo del server a cui deve essere
consegnata.

E' possibile aggiungere automaticamente un disclaimer (nota legale) in calce a tutte le e-mail spedite all'esterno
mettendo la spunta a “Aggiungi una nota legale in calce ai messaggi
inviati”, in questo caso si apre un campo dove inserire il testo della
nota. Terminato l'inserimento dei dati fare click sul pulsante salva.



Modificare un dominio
^^^^^^^^^^^^^^^^^^^^^

Per modificare un dominio esistente fare click sul pulsante
Modifica nella colonna Azioni. Si apre la pagina usata per la creazione
di un nuovo dominio dove è possibile  modificare i parametri; alla fine
delle modifiche fare click sul pulsante salva.

Eliminare un dominio
^^^^^^^^^^^^^^^^^^^^

Per eliminare un dominio esistente fare click sulla freccia accanto al
pulsante modifica sulla colonna azioni; si apre un menù a tendina,
scegliere Elimina, verrà chiesta la conferma fare click sul pulsante
elimina.

Per eliminare un dominio dall'elenco di quelli gestiti dal server,
selezionare Modifica dal menu nella colonna Azioni. Dopo aver fatto clic su
Elimina, verrà richiesta una conferma prima dell'eliminazione definitiva.
Eventuali email destinate al dominio verranno rifiutate.
.. note:: Eliminando un dominio, non verranno eliminate e-mail, ma solo inibita la ricezione di mail indirizzate al dominio. Eventuali mail già ricevute rimarrano conservate sul server.


Scheda Filtro
-------------

Nella scheda Filtro è possibile applicare vari tipi di filtro per i
messaggi ricevuti mettendo la spunta su quelli che si intende abilitare.
In particolare si può:

*  Abilitare il blocco degli allegati con un certo tipo di estensione
   potenzialmente dannosa; si può scegliere fra file eseguibili (es
   .exe), file di archivio (es .rar, .zip) oppure redigere una lista
   personalizzata di estensioni di file che si vogliono bloccare.
*  Abilitare l’antivirus.
*  Abilitare l’antispam e impostare i punteggi di soglia oltre i quali
   una email è considerata probabile spam oppure è rifiutata; far scorrere il
   cursore per variare il valore dei punteggi, valori bassi tendono a classificare
   come spam e-mail valide, valori consigliati 5 (soglia) e 10 (rifiuto). E' possibile aggiungere un prefisso
   nell'oggetto delle email considerate spam (es [SPAM])
*  Impostare delle regole di accesso per gli indirizzi
   email, tramite la
   creazione di una lista di indirizzi o domini i quali sono accettati o
   bloccati. Per creare una lista fare click su Regole di accesso per
   indirizzi email. Viene mostrato un pulsante il quale permette di
   aggiungere le voci alla lista. La freccia adiacente il pulsante
   permette di scegliere il tipo di azione da rivolgere all’indirizzo o
   dominio. Per bloccare scegliere blocca da, inserire l’indirizzo email
   o il dominio; fare click sull’icona disco #|image3|\ per salvare. Per
   accettare scegliere accetta da e procedere come sopra. 
   Per cancellare una regola già inserita
   fare clic sulla “x” posta in corrispondenza di essa.

.. note:: E' fortemente sconsigliato inserire su **accetta Da** un intero dominio.

Casella di posta
-----------------------

Nella scheda Casella di posta si possono impostare i protocolli di
accesso al mail server e decidere se vengono consentite connessioni non
cifrate. |product|
supporta sia POP3 sia IMAP, i due protocolli più diffusi per la gestione
email, ma è consigliato utilizzare il protocollo IMAP.

Ogni casella di posta può avere una dimensione illimitata oppure occupare
al massimo una predefinita quantità di spazio su disco.
In questa scheda si seleziona la dimensione massima generica per tutte le
caselle, ma è possibile specificare valori diversi per ogni casella nella scheda
*Servizi* del menu *Utenti*.

Si può decidere se spostare le email considerate spam in una apposita
cartella **junkmail** invece di consegnarli nella Posta in arrivo; in tal caso è possibile anche quanti giorni il
messaggio di spam viene conservato prima di essere eliminato definitivamente.

Consenti connessioni non cifrate
    Permette di abilitare l'accesso alla cartelle utilizzando protocolli non cifrati (sconsigliato).


Scheda Messaggi
---------------

Nella scheda Messaggi è possibile impostare la dimensione massima accettata
per gli allegati; la posta elettronica è uno strumento adatto
principalmente allo scambio di messaggi per cui è consigliabile tenere
basso tale valore; per lo scambio di file vi sono altri strumenti adatti
a tale scopo es. cartelle condivise; per modificare la dimensione consentita
agli allegati muovere il cursore fino a raggiungere il valore
desiderato.

In caso di problemi temporanei (server del destinatario irraggiungibile, servizio email bloccato, etc),
|product| tenterà di inviare le mail a destinazione per un tempo predefinito ad intervalli regolari. 
E' possibile modificare il tempo di invio portando il cursore al valore desiderato.

Invia tramite smarthost
^^^^^^^^^^^^^^^^^^^^^^^

|product| può consegnare i messaggi in uscita direttamente a
destinazione (raccomandato nella maggior parte dei casi) oppure
consegnarli attraverso il server SMTP del provider (raccomandato in caso
di connessione inaffidabile o ADSL di tipo residenziale, IP dinamico, IP
in Blacklist, etc),in tal caso mettere la spunta su “Invia tramite
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
    destinazione (raccomandato nella maggior parte dei casi). Selezionando
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
Aggiorna tentare di “forzare l’invio” di una email con il pulsante tenta
l’invio oppure eliminare una email con il pulsante elimina.


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

Il server filtra le email in transito analizzando il contenuto alla ricerca di virus, spam e allegati vietati.

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
    Il mail server bloccherà i programmi eseguibili allegati alle email.
Archivi
    Il mail server bloccherà le email con allegati file di archivio (zip,
    rar, etc).
Lista personalizzata
    E' possibile definire un elenco di estensioni che verranno bloccate, per
    esempio doc, pdf, etc, (senza punto iniziale, doc e non .doc).

Allenamento filtro Antispam
---------------------------

Per allenare il sistema antispam in caso di errori di classificazione è possibile utilizzare qualsiasi client IMAP, 
semplicemente spostando le mail erroneamente riconosciute.
In particolare, per indicare al sistema una mail di spam non riconosciuta basterà spostarla nella apposita cartella :dfn:`junkmail`.
Per segnalare invece una mail valida erroneamente marcata come spam sarà necessario spostarla fuori da :index:`junkmail`.

Di default, tutti gli utenti possono allenare i filtri in questo modo. Per restringere la facoltà di allenamento soltanto ad alcuni utenti,
è necessario creare un gruppo chiamato ``spamtrainers`` contenente gli utenti abilitati all'allenamento dei filtri.



Indirizzi email esterni
=======================

Gli indirizzi email esterni sono caselle di posta elettronica che
vengono controllate ad intervalli regolari tramite i protocolli **POP3**
o **IMAP**.  I messaggi ad essi recapitati vengono scaricati e
consegnati agli utenti o gruppi locali, in base alla configurazione
sottostante.

Indirizzi esterni
-----------------

Configura la lista degli indirizzi esterni e l'associazione con l'utente di sistema.

Crea / Modifica
^^^^^^^^^^^^^^^

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
^^^^^^^

L'eliminazione di un account *non* comporta l'eliminazione dei messaggi già consegnati.


Scarica ora
^^^^^^^^^^^

Avvia immediatamente il controllo di tutte gli indirizzi esterni.


Generale
--------

Abilita
    Consente di abilitare o disabilitare il demone Fetchmail che si
    occupa del download della posta dagli indirizzi esterni.

Controlla ogni
    Frequenza del controllo di nuovi messaggi sugli indirizzi esterni.
    Si consiglia un intervallo di 15 minuti.



Indirizzi email
===============

Installazione
-------------

Il modulo di gestione degli indirizzi email viene installato
automaticamente con l’installazione del pacchetto mail server (vedi
Capitolo Email)

Gestione
--------

Accedendo alla pagina *Indirizzi email* del server-manager, verrà mostrata una
tabella con l'elenco di tutti gli indirizzi email registrati su |product|.

Creare nuovo indirizzo email
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Per creare un nuovo indirizzo email fare clic sul pulsante CREA NUOVO.
Si aprirà una pagina con i campi per inserire i dati.

Occorre inserire un indirizzo email valido (senza la parte del dominio,
quella a destra della @) e selezionare dall'elenco il dominio su cui l'indirizzo
sarà valido oppure se dovrà essere attivato su tutti i domini presenti sul server.
E' anche possibile inserire una descrizione opzionale per aggiungere note relative
all'indirizzo email creato, per esempio "mail per la gestione degli ordini esteri").

Infine, selezionare a quale gruppo o utente verrà recapitata la mail in arrivo
all'indirizzo appena creato.

Spuntando l'opzione **Solo reti locali**, l'indirizzo e-mail non potrà ricevere posta
da mittenti esterni al server. L'opzione viene abitualmente usata per evitare l'abuso
di indirizzi speciali solo interni all'organizzazione oppure, spesso, per evitare che gli
utenti utilizzino il proprio indirizzo aziendale nominativo (es. mario.rossi@nethesis.it) per 
spedire corrispondenza all'esterno dell'azienda. Infatti, se mario.rossi@nethesis.it è
attivo solo sulle reti locali, chiunque tenti di spedire da internet riceverà un errore di indirizzo inesistente,
di fatto vanificando l'uso del mittente nominativo (in questi casi, si usano indirizzi generici quali
vendite@nethesis.it).

Fare clic sul pulsante SALVA per attivare l'e-mail appena creata.


Modificare un indirizzo email
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Per modificare un'indirizzo email fare clic sul pulsante Modifica nella
colonna azioni. Si aprirà una pagina di creazione dove è possibile
modificare l’utente o il gruppo a cui appartiene.

Eliminare un indirizzo email
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Per eliminare un indirizzo email fare clic sulla freccia accanto al
pulsante modifica nella colonna azioni e selezionare Elimina. Verrà chiesta la conferma
dell'operazione, fare clic sul pulsante Elimina per eliminare
definitivamente l'indirizzo email.

Eliminando l'indirizzo di posta elettronica non verranno eliminati i
messaggi già recapitati all'utente o al gruppo associato all'indirizzo.
Futuri messaggi destinati all'indirizzo saranno rifiutati.



