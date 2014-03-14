============
Rete Windows
============

Installazione
=============

Viene installato automanticamente quando si installa il pacchetto :dfn:`File Server` (:index:`Samba`). 
Si veda :ref:`shared-folder`.

Impostazione Rete Windows
=========================

Per gestire le impostazioni della rete Windows entrare nella sezione :menuselection:`Configurazione → Rete Windows`. Impostare il ruolo che deve avere il server nella rete Windows scegliendo una tra le tre opzioni presenti.

Workstation
-----------

Se viene assegnato il ruolo di workstation esso si comporterà come qualsiasi workstation della rete Windows.

Controller di dominio
----------------------

Se viene assegnato il ruolo di Controller di dominio è possibile fare Join da parte di qualsiasi altra workstation Windows, come se fosse un vero e proprio Controllere di dominio Windows.

Membro di Active Directory
--------------------------

Il ruolo di Membro di Active Directory viene selezionato quando sulla rete esiste un altro server Microsoft Windows come controller di dominio, e da quale si vogliono ereditare gli utenti/gruppi.


Ruolo
======

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
            
