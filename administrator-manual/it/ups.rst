====
UPS
====

|product| supporta NUT (Network UPS Tools), un pacchetto di programmi che permette di monitorare e amministrare UPS (Uninterruptible Power Supply).

Installazione
=============

Per installare il pacchetto UPS web fare click su :menuselection:`Gestione pacchetti`, 
selezionare :guilabel:`Supporto UPS` e fare click sul pulsante :guilabel:`Avanti`. 

Gestione UPS
============

Per configurare i programmi di gestione dell’UPS fare click su
:menuselection:`Configurazione --> UPS`.

In questa pagina è possibile abilitare il pacchetto di programmi NUT
scegliendo abilita. Sarà anche necessario inserire la modalità di utilizzo dell'UPS 
a seconda che sia configurato master (l'UPS è direttamente collegato al server) o slave 
(l'UPS è collegato ad un altro server raggiungibile via rete).

Se viene impostato *master* occorre indicare il driver da utilizzare ed il tipo di collegamento: seriale o USB.
Per scegliere il driver digitare il nome del dispositivo sul campo 
:guilabel:`Cerca driver per modello`, verrà aperto un menù a tendina dove è presente la
lista dei modelli già supportati da |product|.

Se viene impostato *slave* sarà necessario fornire l’indirizzo IP del server
master.

NUT provvederà ad effettuare uno shutdown controllato in caso di assenza di
alimentazione. 


Configurazione
--------------

Abilita NUT UPS
    Abilita o disabilita il servizio NUT.

Master
    Questa modalità va selezionata se l'UPS è collegato
    direttamente al server tramite cavo seriale o USB.

Cerca driver per modello
    Consente di cercare un driver compatibile con il proprio modello di UPS. Dopo aver selezionato il modello dalla lista, 
    il campo :guilabel:`Driver` verrà valorizzato con il nome del driver opportuno.

Driver
    I driver da utilizzare per il modello di UPS collegato.

Collegamento USB
    Selezionare questa opzione se l'UPS è collegato al server tramite USB.

Collegamento seriale
    Selezionare questa opzione se l'UPS è collegato al server tramite cavo seriale.

Slave
    Questa modalità deve essere utilizzata se l'UPS non è collegato
    direttamente al server, ma ad un altro server con NUT configurato
    in modalità Master al quale |product| si collegherà.

Indirizzo server master
    Indirizzo IP o nome host del server master. Il client utilizzerà l'utente *UPS* per collegarsi al server master.
    Assicurarsi che tale utente sia configurato nel server master.

Password
    La password da specificare qui è quella configurata sul server
    master per la connessione dello slave.
