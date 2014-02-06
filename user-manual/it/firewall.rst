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
forward configurati.

Creare un nuovo port forward
----------------------------

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
disabilita/abilita nella colona Azioni. 

Le regole di Port Forwarding vengono abilitate di default al momento
della creazione, ed è possibile abilitarle e disabilitarle momentaneamente
attraverso questo pulsante

Si
    Abilita la regola.

No
    Disabilita la regola.


Modificare un port forward
--------------------------

Per modificare un port forward fare click sulla freccia adiacente al ulsante disabilita. 

Eliminare un port forward
--------------------------

Per eliminare un port forward già impostato fare click sulla freccia accanto al pulsante disabilita Si apre un menù a tendina, fare click ulla voce elimina..


Controllo Firewall
------------------
Esegue un controllo generale delle regole del firewall configurate. Utile per individuare inconsistenze.


Gestione banda
==============

La gestione banda permette di cambiare priorità al traffico che
attraversa il firewall (che dovrà avere almeno due interfacce di rete).



Installazione
-------------

Per installare il pacchetto  Gestione banda web fare click su Configurazione →Gestione pacchetti. Mettere la spunta su *Monitoraggio banda* e fare click sul pulsante *Avanti*. Verrano suggeriti dei pacchetti aggiuntivi da installare, selezionare quelli che si ritengono utili e confermare le modifiche al sistema facendo click sul pulsante applica.

Al termine dell’ installazione verrà mostrato in alto un messaggio che
ci informa che l’operazione è stata completata correttamente.


Configurazione
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


Per ogni interfaccia su cui si desidera gestire la priorità di banda è
necessario indicare la quantità massima di banda disponibile sia in
uscita che in entrata. E' fondamentale utilizzare valori reali,
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





