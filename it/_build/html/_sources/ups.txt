====
UPS
====

NethServer supporta NUT (Network UPS Tools), un pacchetto di programmi
che permette di monitorare e amministrare UPS, PDU e SCD

Installazione
=============

Per installare il
pacchetto\  UPS
web fare click su  Configurazione →Gestione pacchetti. Mettere la spunta
su Supporto UPS e fare click sul pulsante Avanti. Verrano suggeriti dei
pacchetti aggiuntivi da installare, selezionare quelli che si ritengono
utili e confermare le modifiche al sistema facendo click sul pulsante
applica.

Al termine dell’ installazione verrà mostrato in alto un messaggio che
ci informa che l’operazione è stata completata correttamente.

Gestione UPS
============

Per configurare i programmi di gestione dell’UPS fare click su
Configurazione →UPS.

In questa pagina è possibile abilitare il pacchetto di programmi NUT
scegliendo abilita. Si deve anche inserire la modalità di utilizzo del
UPS a seconda che sia configurato master o slave.

Se viene impostato master occorre fornire al sistema i drivers per il
corretto funzionamento del dispositivo.

Per installare i driver digitare il nome del dispositivo sul campo cerca
driver per modello, verra aperto un menù a tendina dove è presente la
lista dei modelli già supportati da NethServer scegliere il modello
corrispondente all’UPS che si sta installando.

Scegliere anche il tipo di collegamento all’ UPS tra seriale o USB

Se viene impostato slave occorre fornire l’indirizzo IP del server
master.


La gestione di un gruppo di continuità (UPS - Uninterruptible Power
Supply) collegato a NethServer è affidata a NUT (Network UPS Tools), che
provvederà ad effettuare uno shutdown in caso di assenza di
alimentazione. NUT supporta diversi modelli di gruppi di continuità,
collegabili con apposito cavo seriale o USB.

In questo pannello si effettuano le configurazioni di NUT, per
visualizzarne il funzionamento occorre accedere alla Dashboard.

Abilita NUT UPS
    Abilita o disabilita il servizio NUT.


Modalità
--------

Master
    Questa modalità va selezionata se l'UPS è collegato
    direttamente a NethServer tramite cavo seriale o USB.

Cerca driver per modello
    Consente di cercare un driver compatibile con il proprio modello di UPS. Dopo aver selezionato il modello dall lista, 
    il campo *Driver* verrà valorizzato con il nome del driver opportuno.

Driver
    I driver da utilizzare per il modello di UPS collegato.

Collegamento USB
    Selezionare questa opzione se l'UPS è collegato a NethServer tramite USB.

Collegamento seriale
    Selezionare questa opzione se l'UPS è collegato a NethServer tramite cavo seriale.

Slave
    Questa modalità deve essere utilizzata se l'UPS non è collegato
    direttamente a NethServer, ma ad un altro server con NUT configurato
    in modalità Master al quale NethServer si collegherà.

Indirizzo server master
    Indirizzo IP o nome host del server master. Il client utilizzerà l'utente *UPS* per collegarsi al server master.
    Assicurarsi che tale utente sia configurato nel server master.

Password
    La password da specificare qui è quella configurata sul server
    master per la connessione dello slave.
