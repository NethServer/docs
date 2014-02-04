============
Rete Windows
============

Installazione
=============

Viene installato automanticamente quando si installa il pacchetto file
server ( vedi capitolo Cartelle condivise)

Impostazione Rete windows
====================================

Per gestire le impostazioni della rete windows entrare nella
sezione Configurazione →Rete windows. Impostare il ruolo che deve avere
il server nella rete windows scegliendo una tra le tre opzioni presenti.
Posso essere assegnati a NethServer diversi ruoli:

-  Workstation
-  Controller di dominio
-  Membro di Active Directory

Workstation
-----------

Se viene assegnato il ruolo di workstation esso si comporterà come
qualsiasi workstation della rete windows

Controller di dominio
----------------------

Se viene assegnato il ruolo di Controller di dominio occorre aggiornare
il file di registro ai client windows che si vogliono aggiungere

La procedura per tale operazione è la seguente:

#. Fare click sul link Impostazioni di registro per i client.
#. Fare click sul link corrispondente al SO installato sul client che si
   vuole aggiungere (win7samba.reg per windows 7, win98pwdcache.reg per
   windows 98 e winxplogon.reg per windows xp)
#. Si apre una finestra del browser con un testo, copiare il testo e
   incollarlo su un documento di blocco note.

N.B. non deve essere nè Word nè Wordpad nè OpenOffice, consigliato l’uso
di notepad.

4. Salvare il documento di testo con il nome di Samba\_fix.reg;
   assicurarsi che il campo “Salva come” posta sotto “Nome file” abbia
   l’opzione tutti i file.

   N.B. Il file dovrà avere un icona di questo tipo #|image4|

5. Questo file va eseguito sulla macchina client che si vuole aggiungere
   al dominio.

N.B La modifica del file di registro è un’operazione molto delicata che
richiede una particolare attenzione nelle operazioni che si stanno
svolgendo.

Per la procedura sul sistema windows fare riferimento alla
documentazione del sistema operativo.

Membro di Active Directory
--------------------------

Il ruolo di Membro di Active Directory viene selezionato quando sulla
rete esiste un altro server Windows che svolge il ruolo di controllore
di dominio.

Per questa opzione occorre specificare il dominio Active Directory sul
campo Realm e il dominio di Nethserver sul campo Dominio.



Ruolo
------

Selezionare il ruolo che il sistema avrà all'interno della rete:
workstation, controller di dominio o membro di Active Directory.

Workstation
    Abilitando tale opzione il sistema si comporterà come una normale
    workstation.

Controller di dominio
    Abilitando tale opzione il sistema viene configurato come
    controller di dominio della rete.

Dominio
    Il nome del dominio.

Abilita profili roaming
    Se abilitato, il filo dell'utente viene salvalo sul server in modo
    che possa essere utilizzato indipendentemente dal computer su cui
    viene effettuato il login.

Membro di Active Directory
    Il server diventa membro di un dominio Active Directory esistente.
    È necessario essere in possesso delle credenziali
    dell'amministratore del dominio.

Realm
    Reame di Active Directory (per esempio *mydomain.local*).

Dominio
    Nome del dominio Active Directory.

Autenticazione Active Directory
-------------------------------

Inserire le credenziali per permettere al sistema di diventare membro
di un dominio Active Directory.

Nome utente
    Nome utente amministratore del Controller di Dominio Active
    Directory.

Password
    Password dell'utente amministratore del Controller di Dominio
    Active Directory.
            
