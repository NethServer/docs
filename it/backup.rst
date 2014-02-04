======
Backup
======

L’attività di backup è fondamentale perchè in caso di malfunzionamenti o
guasti del sistema ci assicura il salvataggio e la conservazione dei
nostri dati.

Installazione
=============

Per installare il
pacchetto  Backup
fare click su  Configurazione →Gestione pacchetti. Mettere la spunta su
Backup e fare click sul pulsante Avanti. Verrano suggeriti dei pacchetti
aggiuntivi da installare, selezionare quelli che si ritengono utili e
confermare le modifiche al sistema facendo click sul pulsante applica.

Al termine dell’ installazione verrà mostrato in alto un messaggio che
ci informa che l’operazione è stata completata correttamente.

Gestione Backup
===============

Per gestire le attività di backup di NethServer andare sulla sezione
Configurazione→ Backup

Si apre una pagina con tre schede

Scheda Generale
---------------

Nella scheda Generale si può abilitare la funzione di backup mettendo la
spunta su Abilita backup automatico. E’ possibile impostare l’ora in cui
verra eseguito sul campo orario backup.

Scegliere che tipologia di backup Nethserver deve eseguire tra full per
il backup integrale del sistema o incrementale per il backup basato
sull’aggiornamento delle modifiche ai file; in quest’ultimo caso si può
impostare il giorno in cui viene effettuato il backup full scegliendolo
dal menù a tendina.

Si può impostare il tempo di conservazione dei vecchi backup, scegliendo
il numero di giorni dal menù a tendina Elimina backup pià vecchi di.



Abilita backup automatico
    L'opzione abilita o disabilita la procedura di backup. Di default è *abilitato*.
Orario backup
    Indica l'orario in cui verrà eseguito il backup. E' possibile modificare il parametro intervenendo direttamente sul campo.
Full
    Selezionando questa opzione verrà eseguito un backup completo tutti i giorni della settimana
Incrementale
    Selezionando questa opzione verrà eseguito un backup full nel giorno
    selezionato attraverso il campo specifico mentre il resto della
    settimana verrà eseguito un backup incrementale.
Politica di conservazione
    Specifica il numero di giorni per i quali verranno conservati i backup.

Scheda destinazione
-------------------

Nella scheda destinazione è possibile scegliere dove salvare i dati di
backup fra tipi di supporto. Scegliere:

*  Disco USB se si vuole salvare i dati di backup su un hard disk USB
   installato sul server; in caso di più dischi in scegliere quale usare
   dal menù a tendina Etichetta filesystem.

*  Condivisione Windows (CIFS) nel caso si vuole salvare i dati su un
   server windows remoto, il quale condivide cartelle in rete. In questo
   caso specificare sul campo Server  l’indirizzo IP del server o il suo
   nome sul campo Condivisione il percorso della cartella condivisa dove
   si vogliono salvare i file, sui campi Utente e Password il nome
   utente e la sua password.

*  Condivisione NFS nel caso si vuole salvare i dati di backup su un
   server remoto che condivide cartelle in rete. Inquesto caso
   specificare nel campo Host il nome dell’ host e nel campo
   Condivisione il percorso della cartella condivisa dove si vogliono
   salvare i file.

Il backup contiene tutti i dati, come le home degli utenti, le
cartelle condivise, le email ma anche tutte le configurazioni di
sistema. Viene eseguito quotidianamente e può essere completo o
incrementale, in base al giorno della settimana e alla configurazione. I
supporti disponibili per il backup sono: disco USB, condivisione Windows
e condivisione NFS. Al termine del backup è possibile inviare via e-mail
una notifica all'amministratore o ad un indirizzo personalizzato.


Destinazione
------------

Disco USB
    Seleziona come destinazione del backup un disco USB. Il disco USB deve
    essere formattato in filesystem supportato (ext2/3/4 o FAT, NTFS non è supportato) ed una label configurata.

    * Etichetta filesystem: Vengono elencati i dischi USB collegati
Condivisione Windows (CIFS)
    Seleziona come destinazione del backup una condivisione Windows (CIFS). L'autenticazione è obbligatoria.

    * Server: indirizzo IP o FQDN del server Windows di destinazione
    * Condivisione: il nome della condivisione Windows di destinazione
    * Utente: utente da utilizzare per l'autenticazione
    * Password: password da utilizzare per l'autenticazione.
Condivisione NFS
    Seleziona come destinazione del backup una condivisione NFS
Host
   L'indirizzo IP o FQDN del server NFS

   * Condivisione: nome della condivisione NFS di destinazione

Notifiche
---------

In caso di errore
    Invia notifica solo in caso di fallimento del backup.
Sempre
    Verrà sempre inviata una notifica, sia in caso di successo che in caso di fallimento.
Mai
    Non verrà inviata alcuna notifica.
Invia notifica a
    Indica a chi verrà inviata l'e-mail di notifica
   
    * Amministratore di sistema: la notifica del backup verrà inviata alla mail dell'amministratore di sistema (utente admin)
    * Indirizzo personalizzato: la notifica del backup verrà inviata ad un indirizzo mail personalizzato

