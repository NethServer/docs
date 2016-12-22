.. _users_and_groups-section:

===============
Utenti e gruppi
===============

Account provider
================

|product| supporta autenticazione e autorizzazione da un *account provider*
**locale** o **remoto**.

I tipi di account provider supportati sono:

* OpenLDAP locale in funzione sullo stesso |product|,
* Server LDAP remoto con schema RFC2307,
* Samba 4 Active Directory Domain Controller locale,
* Active Directory remoto (sia Microsoft che Samba).

Tenere in conto le seguenti regole sugli account provider:

1. Dopo che |product| è stato collegato ad un account provider, il suo FQDN non
   può più essere cambiato.

2. Gli account provider di tipo locale non possono essere disinstallati.

Provider remoto
    Un'installazione pulita di |product| è già pronta per connettersi ad un
    account provider **remoto** di entrambi i tipi (LDAP, AD). L'utente root può
    configurare l'account provider remoto dalla pagina :guilabel:`Account
    provider`.

    Dopo che |product| è stato collegato ad un account provider remoto, la
    pagina :guilabel:`Utenti e gruppi` visualizza gli account di dominio in sola
    lettura.

Provider locale
    Per eseguire un account provider **locale** andare alla pagina
    :guilabel:`Software center` e installare l'account provider OpenLDAP o Samba
    4 dalla lista dei moduli disponibili.

    Dopo aver installato un provider locale (sia Samba 4 che OpenLDAP),
    l'amministratore può creare, modificare ed eliminare gli utenti e i gruppi.

.. warning::

  Scegliere con cautela l'account provider perché **la scelta non è
  reversibile**. Inoltre il sistema impedisce di modificare l'FQDN dopo che
  l'account provider è stato configurato.


Scegliere l'account provider giusto
-----------------------------------

A parte collegarsi ad un account provider locale o remoto, l'amministratore deve
decidere che tipo di provider è adatto alle proprie esigenze.

Il modulo *File server* di |product|, che abilita la pagina :guilabel:`Cartelle
condivise`, può autenticare i client SMB/CIFS solo se |product| è collegato ad
un dominio Active Directory.  I provider LDAP consentono l'accesso alle
:guilabel:`Cartelle condivise` solo in modalita *guest*. Vedere inoltre
:ref:`shared-folders-section`.

D'altra parte il provider OpenLDAP locale è più semplice da installare e
configurare.

In pratica, se il protocollo di condivisione file SMB non è richiesto, il
provider LDAP è la scelta migliore.

Installazione del provider locale OpenLDAP
------------------------------------------

Dal :guilabel:`Software Center` installare il pacchetto chiamato *Account
provider: OpenLDAP*. Al termine dell'installazione. il pacchetto sarà
automaticamente configurato e l'amministratore potrà gestire gli account dalla
pagina :guilabel:`Utenti e gruppi`.

Installazione del provider locale Samba Active Directory
--------------------------------------------------------

Quando si installa Samba Active Directory come account provider locale il
sistema richiede un **indirizzo IP addizionale** e un collegamento ad internet
funzionante.

L'indirizzo IP addizionale è assegnato ad un Linux Container che esegue le
funzioni di un controllore di dominio Active Directory e deve essere accessibile
dalla LAN (rete green).

Pertanto l'indirizzo IP  aggiuntivo deve soddisfare tre condizioni:

1. l'indirizzo IP deve essere **libero**; non può essere usato da alcun
   dispositivo,

2. l'indirizzo IP deve appartenere alla stessa subnet di una rete green,

3. la rete green deve essere collegata ad un'interfaccia bridge, in modo che il
   container Linux possa aggiungervi la propria interfaccia di rete virtuale; la 
   procedura guidata può creare il bridge al momento automaticamente, se manca.

Dalla pagina :guilabel:`Software Center` installare il pacchetto *Account
provider: Samba Active Directory*.

Al termine dell'installazione, la pagina :guilabel:`Account provider` mostra un
pannello di configurazione. Inserire **l'indirizzo IP addizionale** come
spiegato sopra e premere il pulsante :guilabel:`Avvia DC`. Se necessario,
abilitare la creazione automatica del bridge per la rete green.

.. tip::
    
    La procedura di configurazione di Active Directory può richiedere un po' di
    tempo per completare. Essa crea il *chroot* per il container Linux,
    scaricando da internet dei pacchetti aggiuntivi.

Al termine della procedura di configurazione, la macchina host |product| è
automaticamente inserita nel dominio di Active Directory. Andare alla pagina
:guilabel:`Utenti e gruppi` per modificare gli account predefiniti.

.. index::
  pair: active directory; account predefiniti

Dopo aver installato Samba Active Directory, la pagina :guilabel:`Utenti e
gruppi` contiene due elementi predefiniti; entrambi sono disabilitati:
:dfn:`administrator` e :dfn:`admin`. "Administrator" è l'account privilegiato
predefinito di Active Directory e non è necessario in |product|; va bene tenerlo
disabilitato. "Admin" in |product| è l'account amministrativo predefinito. E'
membro dei gruppi AD "Administrators" e "Domain admins". Vedere
:ref:`admin-account-section` per maggiori informazioni.

Installazione su macchina virtuale
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Samba Active Directory viene eseguita all'interno di un container Linux che
utilizza un'interfaccia di rete virtuale in bridge con l'interfaccia di rete del
sistema. L'interfaccia di rete virtuale deve essere visibile all'interno della
rete fisica, ma spesso i software di virtualizzazione bloccano il traffico ARP e
questo preclude la visibilità del container Samba Active Directory dalla LAN.

È quindi necessario assicurarsi che il virtualizzatore abiliti il traffico di
rete con la *modalità promiscua*.

VirtualBox
++++++++++

Per configurare la modalità promiscua, selezionare "Permetti tutto" dal menù a
discesa presente nella sezione di configurazione di rete.

VMWare
++++++

Entrare nella sezione di configurazione di rete del nodo da virtualizzare e
abilitare lo switch virtuale in modalità promiscua.

KVM
+++

Assicurarsi che la macchina virtuale sia in bridge con un bridge reale (per
esempio br0) e che sia configurato in modalità promiscua.

È possibile forzare un bridge (per esempio, ``br0``) in modalità promiscua
usando il seguente comando: ::

  ifconfig br0 promisc
  
Hyper-V
+++++++

Configurare *MAC Address Spoofing for Virtual Network Adapters*

https://technet.microsoft.com/it-it/library/ff458341.aspx

Join ad un dominio Active Directory esistente
---------------------------------------------

In questo scenario |product| è collegato ad un account provider Active Directory
remoto.  Può essere una implementazione Samba o Microsoft.  |product| diventa
quindi un server membro di un dominio Active Directory esistente. Quando si
accede ad una risorsa su |product| da una workstation del dominio, le
credenziali dell'utente sono verificate da uno dei controllori di dominio e
l'accesso alla risorsa viene consentito.

Il join ad un dominio Active Directory ha i seguenti pre-requisiti:

1.  Il protocollo Kerberos richiede che la differenza tra gli orologi dei
    dispositivi del dominio sia meno di 5 minuti. Sincronizzare gli orologi dei
    client di rete con una sorgente di orario comune. Per |product| andare alla
    pagina :guilabel:`Data e ora`.
 
2.  Il sistema assume che i nome di dominio NetBIOS di default sia la parte iniziale
    del suffisso di dominio DNS, troncata ai primi 15 caratteri.

    **Esempio**

    - FQDN: test.local.nethserver.org
    - Dominio: local.nethserver.org
    - Dominio NetBIOS di default: LOCAL

    Se il dominio NetBIOS di default non è adatto al proprio ambiente può essere
    modificato dalla console: ::
       
        config set smb service Workgroup <your_netbios_domain>

3.  (Solo per Microsoft Active Directory) L'account del computer di default non è
    autorizzato ad effettuare bind LDAP semplici, a causa delle politiche di
    sicurezza di Microsoft AD. Per poter funzionare correttamente |product| richiede
    un account utente aggiuntivo che possa effettuare bind LDAP semplici. Creare un
    **account utente dedicato** in AD, e impostare per esso una password complessa,
    *senza scadenza*.

Dopo aver sistemato i pre-requisiti, procedere con il join dalla pagina
:guilabel:`Utenti e gruppi`:

* Compilare il campo :guilabel:`Indirizzo IP server DNS` che di solito è
  l'indirizzo IP del controller AD stesso.

* (solo per Microsoft Active Directory) specificare le credenziali
  dell'**account utente dedicato** nel pannello :guilabel:`Impostazioni
  avanzate`.

* Premere il pulsante :guilabel:`Salva`. Verrà richiesto un nome utente e la
  password: digitare le credenziali di ``administrator`` o di
  qualsiasi altro account che ha il permesso di fare *join* della
  macchina al dominio (per esempio ``admin`` su |product|).

.. _bind-remote-ldap-section:

Collegamento ad un server LDAP remoto
-------------------------------------

Se il server remoto è |product|, è sufficiente il solo indirizzo IP nella pagina
:guilabel:`Account provider`.

Per altre implementazioni, cambiare le credenziali per il bind, il *base DN* e
le impostazioni di cifratura sotto il pannello :guilabel:`Impostazioni
avanzate`.

Utenti
======

Un nuovo utente rimane bloccato finché non gli viene assegnata una password.
Agli utenti bloccati è negato l'accesso ai servizi del sistema.

I seguenti campi sono obbligatori per la creazione di un utente:

* Nome utente
* Nome completo (nome e cognome)

Al termine della creazione, un utente risulta disabilitato fino a quando non
viene impostata una password usando il pulsante :guilabel:`Cambia password`. Un
utente bloccato non può utilizzare i servizi che richiedono autenticazione.
Quando un utente è abilitato, l'utente può accedere al Server Manager e cambiare
la propria password: :ref:`user_profile-section`.

Un utente può essere aggiunto ad uno o più gruppi usando la pagina
:guilabel:`Utenti` o :guilabel:`Gruppi`.

A volte può essere necessario bloccare l'accesso ai servizi di un utente senza
eliminare l'account. E' possibile farlo usando le azioni :guilabel:`Blocca` e
:guilabel:`Sblocca`.

.. note::
    
    Quando utente viene eliminato, verranno eliminati anche tutti i dati
    dell'utente.

.. _users_services-section:

Accesso ai servizi
------------------

Ogni utente è caratterizzato da una coppia di credenziali: **nome utente** e
**password**. Le credenziali dell'utente sono necessarie per accedere ai servizi
installati sul sistema.

Il nome utente può essere fornito in due forme: *lunga* (default) e *corta*. La
forma *lunga* è sempre accettata dai servizi. L'accettare o meno la forma
*corta* dipende dal singolo servizio.

Per esempio se il dominio è *example.com* e il nome utente è *goofy*:

Forma lunga del nome utente
    *goofy@example.com*

Forma corta del nome utente
    *goofy*


.. _groups-section:

Gruppi
======

Un gruppo di utenti può essere usato per assegnare permessi speciali ad alcuni
utenti, come autorizzare l'accesso alle :ref:`cartelle condivise
<shared-folders-section>`.

Si possono creare due gruppi speciali.  Gli utenti che appartengono a questi
gruppi ottengono l'accesso alle pagine del Server Manager.

* :dfn:`administrators`: Gli utenti di questo gruppo hanno gli stessi
  permessi di ``root``.

* :dfn:`managers`: Gli utenti di questo gruppo hanno l'accesso alle
  pagine della sezione *Gestione*.

.. index: admin

.. _admin-account-section:

Account admin
=============

Se un **account provider locale** LDAP o AD è installato, l'utente *admin*, membro
del gruppo *administrators* è creato automaticamente. Questo account consente di
accedere a tutte le pagine di configurazione del Server Manager. Inizialmente è
bloccato e non ha accesso alla console.

.. tip:: Per abilitare l'account *admin* impostargli la password.

Dove possibile, l'account *admin* riceve dei permessi speciali da parte di
servizi specifici, come poter aggiungere una workstation al dominio di Active
Directory.

Se |product| è collegato ad un **account provider remoto**, l'utente *admin* e
il gruppo *administrators* possono essere creati, se non esistono già.

Se un utente o un gruppo con una funzione simile è già presente nella base dati
dell'account provider remoto, ma si chiama diversamente, può essere designato
come *admin* mediante una `procedura manuale <http://wiki.nethserver.org/doku.php?id=userguide:set_admin_account>`.

.. _password-management-section:

Gestione password
=================

Il sistema prevede la possibilità di impostare dei vincoli sulla
:dfn:`complessità` e la :dfn:`scadenza` delle password.

Le politiche di gestione password possono essere cambiate usando l'interfaccia
web.

Complessità
-----------

La :index:`complessità password` è un insieme di condizioni minime che devono essere soddisfatte affinché la password venga accettata dal sistema: 
è possibile scegliere tra due differenti policy di gestione complessità delle password:

* :dfn:`none`: non viene fatto alcun controllo sulla password immessa se non sulla lunghezza di almeno 7 caratteri
* :dfn:`strong`

La policy :index:`strong` impone che la password debba rispettare le seguenti regole:

* lunghezza minima 7 caratteri
* contenere almeno 1 numero
* contenere almeno 1 carattere maiuscolo 
* contenere almeno 1 carattere minuscolo
* contenere almeno 1 carattere speciale
* contenere almeno 5 caratteri diversi
* non deve essere presente nei dizionari di parole comuni 
* deve essere diversa dallo username
* non può avere ripetizioni di pattern formati da più 3 caratteri (ad esempio la password As1.$As1.$ non è valida)
* se è installato Samba Active Directory, sarà abilitato anche lo storico delle password

La policy di default è :dfn:`strong`.

.. warning::

    Cambiare le politiche predefinite è altamente sconsigliato. L'utilizzo di
    password deboli è la prima causa di compromissione dei server da parte di
    attaccanti esterni.

Scadenza
--------

La :index:`scadenza delle password` viene attivata di default a 6 mesi a partire dal momento in cui la password viene impostata.
Il sistema invierà una mail informativa all'utente quando la sua password è in scadenza.

.. note:: Al momento dell'attivazione il sistema farà riferimento alla data dell'ultimo cambio password, 
   se tale data è precedente più di 6 mesi, il server invierà una mail per segnalare che la password è scaduta. 
   In tal caso è necessario cambiare la password dell'utente.
   Ad esempio: se l'ultimo cambio password è stato fatto a gennaio e l'attivazione della scadenza in ottobre, 
   il sistema riterrà la password cambiata in gennaio come scaduta, e lo segnalerà all'utente.

.. _effects-of-expired-password:

Effetti della password scaduta
------------------------------

Allo scadere della password l'utente sarà in grado di scaricare regolarmente la
posta ma non potrà più accedere alle cartelle e stampanti condivise sul server
(Samba) o da altri pc in caso il pc faccia parte del dominio. 
