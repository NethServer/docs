============
Rete Windows
============

L'interoperabiltà con |Microsoft Windows (TM)| è fornita da
Samba_. Per installarlo selezionare il modulo :dfn:`File Server`, o
qualsiasi altro modulo che lo richiede.

|product| configura Samba per agire in una rete Windows secondo un
*ruolo* specifico. Il ruolo si sceglie dal Server Manager, dalla
pagina :menuselection:`Windows network`.

Attualmente sono disponibili i seguenti ruoli:

* Workstation

* Primary Domain Controller

* Membro di Active Directory

Le differenze tra questi ruoli riguardano *dove* si trova il database
degli utenti e *quali host* possono accedervi. Il database degli utenti
contiene la lista degli utenti del sistema, le loro password,
l'appartenenza ai gruppi e altre informazioni.

Workstation

    In questo ruolo |product| utilizza solo il database degli utenti
    locale. Solo gli utenti locali possono accedere alle sue risorse,
    presentando le corrette credenziali di accesso, nome utente e
    password.  Questo è il comportamento di una workstation Windows
    che sta da sola.

Primary Domain Controller

    Quando agisce come `Primary Domain Controller` (PDC), |product|
    emula un controller di dominio Windows 2000/NT, garantendo
    l'accesso al proprio database di utenti locale solo dalle
    workstation autorizzate.  Una persona può accedere alle
    workstation autorizzate digitando le propie credenziali di
    dominio, e da questa accedere a file e stampanti condivise.

Membro di Active Directory

    In questo ruolo |product| diventa un server autorizzato di un
    dominio Active Directory esistente.  Quando si accede ad una sua
    risorsa da una workstation del dominio, le credenziali dell'utente
    sono verificate da un controller di dominio (DC) e l'accesso alla
    risorsa viene concesso.

.. |Microsoft Windows (TM)| unicode:: Microsoft \x20 Windows U+2122
.. _Samba: http://www.samba.org/

.. _samba_ws:

Workstation
-----------

Quando agisce come workstation, |product| registra se stesso come
membro del *workgroup Windows* specificato nel campo :guilabel:`Nome del gruppo di lavoro`. 

Dagli altri host della rete Windows, |product| sarà elencato in
*Risorse di rete*, sotto il nodo chiamato come il valore del campo
:guilabel:`Nome del gruppo di lavoro`.

Come detto in precedenza, per accedere alle risorse del server, i
client devono fornire le credenziali di un account locale valido.

.. _samba_pdc:

Primary domain controller
-------------------------

Il *Primary Domain Controller* (PDC) è un luogo centralizzato dove sono
conservati gli account di utenti e host.  Per configurare una rete
Windows dove |product| agisce nel ruolo di PDC, seguire i seguenti
passi:

1. Dal Server Manager, pagina :menuselection:`Rete Windows`,
   selezionare :guilabel:`Primary Domain Controller` quindi
   :guilabel:`SALVA`.

   Si assume che il nome del Dominio predefinito sia la seconda parte
   del dominio del nome dell host in maiuscolo (es. se l'host name
   completo è ``server.example.com`` il nome del dominio predefinito è
   ``EXAMPLE``).  Se questo valore non va bene, scegliere un nome
   semplice che rispetti queste regole:

   * lunghezza tra 1 e 15 caratteri;

   * lettera iniziale, quindi solo lettere, numeri o il segno meno ``-``;

   * solo lettere maiuscole.

   Per maggiori informazioni riferirsi alle `Naming conventions`_ di Microsoft.

2. Per ogni workstation della rete Windows, eseguire la procedura di
   *join* al dominio. Questo passo richiede delle credenziali
   adeguate. In |product|, i membri del gruppo ``domadmins`` possono
   aggiungere le workstation al dominio. In più, i membri di
   ``domadmins`` hanno i permessi di amministratore nelle workstation
   del dominio.  Come impostazione predefinita, solo l'utente
   ``admin`` è membro del gruppo ``domadmins``.

   Alcune versioni di Windows potrebbero richiedere l'applicazione di
   una patch al registro di sistema per entrare nel dominio.  Dal
   Server Manager, seguire il link :guilabel:`Impostazioni di registro
   per i client` per scaricare i file ``.reg`` appropriati. Fare
   riferimento alla `documentazione ufficiale di Samba`_ per maggiori
   informazioni.

.. _Naming conventions: http://support.microsoft.com/kb/909264
.. _documentazione ufficiale di Samba: https://wiki.samba.org/index.php/Registry_changes_for_NT4-style_domains

.. _samba_ads:

Active Directory member
-----------------------

Il ruolo *membro di Active Directory* (ADS) configura |product| come
un server membro di un dominio Active Directory, e come tale delega
l'autenticazione degli utenti ai controller di dominio.  Quando opera
in questa modalità, Samba viene configurato per riportare gli account
del dominio dentro |product|, in modo da poter condividere file e
cartelle sull'intero dominio.

.. note:: Per l'integrazione tra il server mail e AD, fare riferimento
          alla documentazione del modulo :ref:`email-section`.

Per entrare in un dominio Active Directory ci sono alcuni pre-requisiti:

1. Nella pagina :menuselection:`DNS and DHCP`, impostare il controller
   di dominio come DNS. Se esiste un altro DC, impostarlo come DNS
   secondario.

2. Nella pagina :menuselection:`Data e ora`, impostare il DC come
   sorgente del tempo NTP; il protocollo Kerberos richiede infatti che
   la differenza tra gli orologi dei sistemi sia meno di 5 minuti.

Dopo aver sistemato i pre-requisiti, procedere nella pagina :menuselection:`Rete Windows`, selezionando :guilabel:`Membro di Active Directory`:

* Compilare i campi :guilabel:`Realm` e :guilabel:`Domain` con i valori appropriati. I valori di default vengono dal nome host completo e forse non sono adeguati all'ambiente reale, **quindi assicurarsi che i campi Reame e Dominio siano corretti**.

* :guilabel:`Ramo LDAP degli account` deve essere impostato al ramo
  LDAP che contiene gli account del dominio, se si pensa di installare
  il modulo :ref:`email-section`.  Di fatto non è richiesto da Samba.

* Premere :guilabel:`SALVA`. Verrà richiesto un nome utente e la
  password: digitare le credenziali di ``administrator`` o di
  qualsiasi altro account che ha il permesso di fare *join* della
  macchina al dominio.


