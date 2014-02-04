=======
Gateway
=======

Nethserver è in grado di svolgere il ruolo di Gateway all’interno della
rete in cui viene installato. Per una corretta funzionalità è possibile
impostare il reindirizzamento ed inoltro delle porte e la gestione della
banda utilizzata dalle varie macchine connesse in rete.

Port Forward
==============

Il Port Forward permette il reindirizzamento e l’inoltro di pacchetti in
entrata su di una determinata porta di un server in ascolto.

Installazione
==============

Gestione Port Forward
=====================

Per il Port forward dei pacchetti su una determinata porta occorre
andare sulla sezione Gestione→ Port Forward.

Si apre una pagina che mostra un tabella riassuntiva di tutti i port
forward impostati.

Creare un nuovo port forward
----------------------------

Per creare un nuovo port forward fare click sul pulsante crea nuovo. Si
apre una pagina dove inserire i parametri di impostazione. Scegliere il
tipo di protocollo usato tra TCP oppure UDP.

Nel campo Porta di origine inserire la porta nella quale vengono
ricevuti i pacchetti da reindirizzare.

Nel campo Porta di destinazione inserire la porta su cui il server sta
ascoltando, dove verranno reindirizzati i pacchetti.

Nel campo  Host di destinazione inserire l’indirizzo IP assegnato al
server.

Nel campo Permetti solo da inserire uno specifico indirizzo IP da cui
saranno accettati i pacchetti.

Nel campo Descrizione un eventuale descrizione della funzione del port
forward.

Fare click sul pulsante Salva per salvare le impostazioni inserite. Se
l’operazione è andata abuon fine verrà aggiunta una riga con i parametri
inseriti sulla tabella riassuntiva.


E' possibile usare questo pannello per modificare le regole del firewall
così da aprire una specifica porta (o un intervallo di porte) sul server
ed inoltrare una porta ad un altra. In questo modo è possibile
permettere l'accesso ad host privato nella rete locale.


Porta di origine
    Specifica la porta aperta sul IP pubblico.

Porta destinazione
    Specifica la porta sul host interno e destinazione del traffico.

Host destinazione
    E' la macchina interna alla LAN a cui verrà rediretto il traffico.

Permetti solo da
    Permette il forward del traffico solo da alcune sorgenti reti/host.

Descrizione
    Descrizione opzionale della regola di port forwarding.






Abilitare o disabilitare un port forward
----------------------------------------

Per disabilitare/abilitare un port forward fare click sul pulsante
disabilita/abilita nella colona Azioni. Verrà mostrata aperta una
finestra dove viene chiesta la conferma dell’operazione; fare click sul
pulsante ok per confermare

Le regole di Port Forwarding vengono abilitate di default al momento
della creazione, è possibile abilitare/disabilitare momentaneamente
attraverso questo pulsante

Si
    Abilita la regola.

No
    Disabilita la regola.

Modificare un port forward
--------------------------

Per modificare un port forward fare click sulla freccia adiacente al
pulsante disabilita. Verrà aperto un menù a tendina, scegliere la voce
modifica; sarà mostrata la pagina usata per la sua creazione dove sarà
possibile modificare i dati.

Eliminare un port forward
--------------------------

Per eliminare un port forward già impostato fare click sulla freccia
accanto al pulsante disabilita Si apre un menù a tendina, fare click
sulla voce elimina.Verrà chiesta la conferma, fare click sul pulsante
elimina per eliminare definitivamente il port forward.


Controllo Firewall
------------------
Esegue un controllo generale delle regole del firewall configurate. Utile per individuare inconsistenze.



Gestione banda
==============

La gestione della banda è un tema molto interessante di NethServer che
permette di regolare in modo calibrato la navigazione delle varie
macchine connesse alla rete.

La gestione banda permette di cambiare priorità al traffico che
attraversa il firewall (che dovrà avere almeno due interfacce di rete).



Installazione
-------------

Per installare il
pacchetto  Gestione
banda web fare click su  Configurazione →Gestione pacchetti. Mettere la
spunta su Monitoraggio banda e fare click sul pulsante Avanti. Verrano
suggeriti dei pacchetti aggiuntivi da installare, selezionare quelli che
si ritengono utili e confermare le modifiche al sistema facendo click
sul pulsante applica.

Al termine dell’ installazione verrà mostrato in alto un messaggio che
ci informa che l’operazione è stata completata correttamente.

Gestione banda
--------------

Per gestire la banda andare sulla sezione Configurazione→ Backup si apre
una pagina con quattro schede.

Scheda generale
^^^^^^^^^^^^^^^

Nella scheda generale è possibile abilitare la gestione della banda
scegliendo si; fare click sul pulsante salva per salvare l’impostazione.

Scheda Regole interfacce
^^^^^^^^^^^^^^^^^^^^^^^^

Nella scheda regole interfacce è possibile impostare l’utilizzo della
banda per ogni scheda di rete presente sul server. Nella pagina viene
mostrata una tabella riassuntiva delle regole impostate.

Per creare una nuova regola fare click sul pulsante crea nuovo. Si apre
una pagina dove scegliere la scheda di rete su cui applicare la regola e
dove impostare il valore in kbps per la banda in entrata e in uscita
riserveta all’interfaccia.

Per modificare una regola già impostata fare click sul pulsante
modifica nella colonna Azioni si apre la pagina usata per creare le
regole, dove è possibile modificare i parametri.


Per ogni interfaccia su cui si desidera gestire la priorità di banda è
necessario indicare la quantità massima di banda disponibile sia in
uscita che in entrata. Non verranno trasmessi dati ad una velocità
superiore a quella configurata. E' fondamentale utilizzare valori reali,
preferibilmente misurati con dei test, in particolare per la banda in
upload (in uscita). La tabella mostra i valori configurati su ogni
interfaccia, permettendo di modificare i limiti di banda.


Crea una configurazione di limiti di banda per interfaccia.

Interfaccia
    Selezionare l'interfaccia a cui si riferisce la quantità di banda
    sottostante. In genere si limita la banda solo nelle interfacce WAN.
Banda entrante (kbps)
    Impostare la quantità di banda in ingresso (download).
Banda uscente (kbps)
    Impostare la quantità di banda in uscita (upload).
Descrizione
    E' possibile indicare una nota (per esempio: ADSL 1280/256).





Scheda Regole indirizzi
^^^^^^^^^^^^^^^^^^^^^^^

Nella scheda indirizzi è possibile impostare la priorità per ogni MAC
address o indirizzo IP della rete. Nella Pagina viene mostrata una
tabella riassuntiva delle regole impostate.

Per creare una nuova regola fare click sul pulsante crea nuovo. Si apre
una pagina dove inserire il MAC address o l’indirizzo IP a cui assegnare
la regola e dove scegliere la priorità che dovrà avere fra alta, media
bassa. E’ possibile inserire anche un’eventuale descrizione.

Per modificare una regola già impostata fare click sul pulsante
modifica nella colonna Azioni si apre la pagina usata per impostare le
regole, dove è possibile modificare i parametri.


La tabella mostra l'elenco degli indirizzi di rete (IP o MAC) che hanno
regole di priorità personalizzate. Per esempio, è possibile decidere
che il traffico proveniente da uno specifico computer della rete locale
abbia una priorità bassa oppure alta rispetto agli altri.


Indirizzo IP o MAC
    Indicare l'indirizzo IP o MAC che identifica il computer.
Descrizione
     E' possibile aggiungere una descrizione opzionale per descrivere
     chiaramente la scopo della regola. Per esempio: priorità alta per il pc del
     direttore.


Scheda Regole porte
^^^^^^^^^^^^^^^^^^^

Nella scheda Regole porte è possibile impostare la priorità per una
porta aperta sul gateway. Nella pagina viene mostrata una tabella
riassuntiva delle regole impostate.

Per creare una nuova regola fare click sul pulsante crea nuovo. Si apre
una pagina dove inserire il numero di porta il suo protocollo scelto fra
TCP e UDP a cui assegnare la regola e dove scegliere la priorità che
dovrà avere fra alta, media e bassa. E’ possibile inserire anche
un’eventuale descrizione.

Per modificare una regola già impostata fare click sul pulsante
modifica nella colonna Azioni si apre la pagina usata per impostare le
regole, dove è possibile modificare i parametri.


La tabella mostra l'elenco delle porte TCP/UDP che hanno regole di
priorità personalizzate. Per esempio, è possibile specificare che il
traffico relativo ad un determinato servizio di rete (proveniente o
destinato a una determinata porta) abbia una priorità bassa oppure alta
rispetto al normale traffico di rete.


Porta
    Indicare la porta utilizzata dal servizio di rete
Protocollo
    Inserire il protocollo IP
Descrizione
    E' possibile aggiungere una descrizione opzionale che indichi
    chiaramente la scopo della regola. Per esempio: priorità bassa per il
    servizio ftp.





