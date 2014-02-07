==================
Cartelle condivise
==================

Cartelle condivise è uno strumento di NethServer che permette di
condividere file fra gli utenti del server.

Una cartella condivisa (conosciuta anche come I-bay) è una risorsa a
cui si può accedere in base ai servizi installati nel sistema e ai
permessi impostati da questo modulo.


Installazione
==================

Per installare il
pacchetto “Cartelle
condivise” fare click su  Configurazione →Gestione pacchetti. Mettere la
spunta su File server e fare click sul pulsante Avanti. Verrano
suggeriti dei pacchetti aggiuntivi da installare, selezionare quelli che
si ritengono utili e confermare le modifiche al sistema facendo click
sul pulsante applica.

Al termine dell’ installazione verrà mostrato in alto un messaggio che
ci informa che l’operazione è stata completata correttamente.

Gestione di Cartelle condivise
====================================

Per configurare Cartelle condivise andare sulla sezione Gestione →
Cartelle condivise.

Si aprirà una pagina che mostra una tabella dove sono elencate tutte le
cartelle condivise presenti sul sistema; qui è possibile creare una
nuova cartella condivisa oppure modificarne o eliminarne una già
esistente

Creare una nuova cartella condivisa
====================================

Per creare una cartella condivisa andare sulla sezione Gestione →
Cartelle condivise.

Si aprirà una pagina che mostra una tabella dove sono elencate tutte le
cartelle condivise presenti sul sistema; fare click sul pulsante crea
nuovo si aprirà una pagina con quattro schede.

Scheda Generali
---------------

Nella scheda generali si deve inserire il nome della nuova cartella
condivisa e una sua eventuale descrizione nei campi Nome e Descrizione.
Scegliere il gruppo proprietario della cartella attraverso il menù a
tendina. Lasciando tutti gli utenti autenticati la cartella sarà
disponibile a tutti gli utenti registrati e autenticati sul sistema.

E’ possibile scegliere i permessi di accesso alla cartella mettendo la
spunta su consenti scrittura a gruppo proprietario e/o consenti lettura
a tutti.

Scheda Accesso web
------------------

Nella scheda Accesso web è possibile abilitare l’accesso alle cartelle
condivise dal sito web del dominio registrato sul server in fase di
installazione.

Per abilitare l’accesso web mettere la spunta su abilita accesso web;
abilitata l’opzione si può

*  Personalizzare il percorso per accedere alla cartella condivisa
   scegliendo fra le opzioni default, radice sito web oppure
   personalizzato, in questo caso occorre inserire il percorso nel campo
   dedicato.
*  Decidere se riservare l’accesso solo dalle reti locali, in tal caso
   mettere la spunta su Consenti l'accesso solo dalle reti locali
*  Impostare una password di accesso alla cartella condivisa.

Fare click sul pulsante salva per salvare le impostazioni inserite.


Abilita l'accesso da web alla cartella condivisa.

Host virtuale
    Permette di scegliere da quale nome di host è accessibile la
    cartella condivisa. L'elenco è modificabile tramite la scheda
    "Alias server" del modulo "DNS e DHCP". 
    
Indirizzo web (URL)
    Definisce l'indirizzo web a cui è disponibile la risorsa.

Consenti l'accesso solo dalle reti locali
    Se abiltato, limita l'accesso alla risorsa alle sole reti locali.

Richiedi password
    L'accesso alla risorsa da web non richiede alcuna
    autenticazione. Abilitare questa opzione per richiedere una
    password: specificarla nel campo sottostante.



Scheda Samba
------------

Nella scheda Samba è possibile abilitare il server samba, il quale
permette di interagire con client o server Microsoft Windows.

Per abilitare Samba mettere la spunta su Abilita samba; è possibile
abilitare il cestino di rete dove finiranno i file cancellati dalle
cartelle condivise mettendo la spunta su Cestino di rete e decidere se
mantenere i file omonimi all’interno del cestino.

Si può abilitare anche un accesso di tipo ospite alle cartelle
condivise; se si sceglie nessuno non sarà consentito l’accesso
ospite, se si sceglie solo lettura gli utenti ospite potranno solamente
aprire i file delle cartella condivisa, mentre se si sceglie lettura e
scrittura potranno aprire e modificare i file condivisi.

Fare click sul pulsante salva per salvare le impostazioni inserite

Scheda ACL
----------

Nella scheda ACL è possibile redigere una lista ordinata di regole che
stabiliscono quali  permessi delle cartella condivisa sono concessi ogni
singolo utente o per un intero gruppo.

Per impostare una regola inserire il nome utente o del gruppo nel campo,
il sistema cercherà automaticamente man mano che si compila il nome.
Scelto il nome da aggiungere fare click sul pulsante aggiungi.

Viene aggiunta una riga sotto il campo dove è inserito il nome scelto e
accanto le opzioni per impostare i permessi, mettere la spunta su
lettura se l’utente o il gruppo deve solo poter aprire la cartella o i
files condivisi, mettere la spunta su lettura e  scrittura se lìutente o
il gruppo può aprire e modificare la cartella o i files condivisi.

Per cancellare una regola fare click sulla “x” a destra della riga
contenente il nome dell’ utente o del gruppo

Modificare una cartella condivisa
---------------------------------

Per modificare una cartella condivise andare sulla sezione Gestione →
Cartelle condivise.

Si aprirà una pagina che mostra una tabella dove sono elencate tutte le
cartelle condivise presenti sul sistema; per modificarne una fare click
sul pulsante Modifica sulla colonna Azioni.

Si apre la stessa pagina usata per la creazione della cartella da dove è
possibile modificare le impostazioni. Per i dettagli vedi Il paragrafo
Creazione nuova cartella condivisa.

E’ anche possibile reimpostare i permessi direttamente al valore di
default facendo click sulla freccia adiacente il pulsante modifica. Si
apre un menù a tendina, fare click sulla voce Reimposta permessi. Verrà
chiesta la conferma, fare click sul pulsante ripristina per reimpostare
i permessi ai valori di default.

Eliminare una cartella condivisa
--------------------------------

Per eliminare una cartella condivisa fare click sulla freccia adiacente
il pulsante modifica. Si apre un menù a tendina, fare click sulla voce
elimina. Verrà chiesta la conferma, fare click sul pulsante elimina per
eliminare definitivamente la cartella.


Rimuove la cartella e tutto il suo contenuto. *L'eliminazione non è
reversibile!* L'unico modo per recuperare il contenuto di una cartella
condivisa eliminata è ripristinare un backup.


Reimposta permessi
------------------

Imposta ai valori configurati tramite questo modulo il gruppo
proprietario e le ACL. L'operazione sarà eseguita ricorsivamente su
tutti i file e le sottocartelle della cartella condivisa.


Samba
-----

Samba fornisce servizi di condivisione di file e stampanti a client
SMB/CIFS (Condivisione file e stampanti di Windows).

Abilita Samba 
    Abilita l'accesso come "cartella condivisa" di Windows.

Cestino di rete
    Raccoglie i file eliminati da questa cartella condivisa, in modo
    analogo al cestino di Windows.

Mantieni file omonimi
    Se due file omonimi vengono eliminati, rimangono distinti nel
    cestino. Disabilitando questa opzione, l'ultimo sovrascrive il
    precedente.

Accesso guest
    Un *utente guest* rappresenta un utente la cui identificazione è
    fallita poiché non ha fornito credenziali o le ha fornite
    errate. Per gli utenti o i dispositivi che agiscono in questa
    modalità si possono concedere i seguenti permessi:

    * Nessuno
    * Sola lettura
    * Lettura e scrittura




Generale
--------

Nome
    Il nome della cartella condivisa può contenere solo lettere
    minuscole, numeri, punti, trattini e underscore e deve iniziare con
    una lettera. La lunghezza massima consentita del nome è 12
    caratteri.

Descrizione
    Campo opzionale per una breve descrizione della cartella condivisa.

Gruppo proprietario
    Il gruppo proprietario della cartella condivisa, solo i membri del
    gruppo potranno accedere.

Consenti scrittura al gruppo proprietario
    Consenti l'accesso in scrittura ai membri del gruppo proprietario.

Consenti lettura a tutti
    Accesso in lettura a chiunque si connetta al sistema, anche da reti pubbliche.


ACL
---

Le Access Control List (lista di controllo accessi) consentono di
specificare i permessi di accesso alla cartella condivisa per singoli
utenti o gruppi, in aggiunta a quelli del gruppo proprietario.

Lettura
    Consenti o nega l'acceso in lettura all'utente o gruppo selezionato.  

Scrittura
    Consenti o nega l'acceso in scrittura all'utente o gruppo selezionato.





