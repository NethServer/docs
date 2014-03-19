======
Novità
======

Questo documento ha l'obiettivo di facilitare il passaggio dai vecchi prodotti a |product| che 
introduce numerose novità a livello funzionale ed estetico.

Sistema base
============

|product| è basato su CentOS 6.x ed è disponibile solo per sistemi a 64 bit. 

La struttura di |product| è altamente modulare, ovvero è possibile installare solo i software strettamente necessari.
Il sistema base è composto dall'interfaccia web per la configurazione, un firewall minimale e il server per l'accesso remoto sicuro (SSH).
Tutti gli altri moduli, compresi utenti e backup, sono opzionali.

La struttura del filesystem ha subito cambiamenti per adattarsi al Filesystem Hierarchy Standard (FHS). Tutti i dati sono posizionati
nella directory :file:`/var/lib/nethserver`. In particolare:

* home degli utenti: :file:`/var/lib/nethserver/home`
* maildir: :file:`/var/lib/nethserver/vmail`
* cartelle condivise (ibay): :file:`/var/lib/nethserver/ibay`

L'architettura del sistema è stata fortemente razionalizzata per aderire agli standard più diffusi, inoltre sono state adottate
convenzioni molto stringenti per agevolare la configurazione del sistema. 
Ad esempio, tutto quello che è possibile fare da interfaccia web, è facilmente replicabile e scriptabile da linea di comando.

Sono disponibili nuovi metodi di installazione, per maggiori informazioni vedi :ref:`installation`.

Interfaccia web
---------------
Il comando :command:`console` è deprecato e se ne sconsiglia l'utilizzo. Tutte le configurazioni possono essere effettuate da interfaccia web,
comprese le impostazioni delle interfacce di rete e il nome host/dominio della macchina.

L'interfaccia web è stata completamente riscritta ed è in ascolto sulla porta :dfn:`980`.
Il login può essere effettuato con le credenziali dell'utente :dfn:`root`.

Caratteristiche principali:

* Facilità d'uso
* Velocità
* Adattabile agli schermi di tutte le dimensioni
* Validatori complessi per i dati immessi
* Ricerca fra i menu
* Personalizzabile

Dashboard
---------

La Dashboard è uno speciale modulo dell'interfaccia web che consente di avere una visione d'insieme dello stato del sistema.
Include alcuni elementi di base:

* Tipo di hardware
* Utilizzo risorse (carico, RAM, SWAP, dischi)
* Stato RAID
* Lista dei servizi

Ogni modulo può estendere la Dashboard con widget e schede specifiche, ad esempio stato del backup, database antivirus, carico UPS, ecc.


Firewall
--------

La politica di sicurezza del firewall prevede che tutte le porte siano chiuse come impostazione di default, solo le porte espliciatemente
utilizzate sono aperte.
Se si desidera utilizzare la modalità server e gateway, è sufficiente installare il modulo Firewall base che include le funzionalità di gateway,
port forwarding e traffic shaping (priorità per porta e IP sorgente).

Accesso remoto
--------------

Il server SSH (porta standard 22) e l'intefaccia web sono abilitati di default ed accedibili da tutte le reti anche con l'utente :dfn:`root`.
Al termine della configurazione, si consiglia di limitare l'accesso alle sole reti affidabili e di cambiare la porta di default per SSH.

Gestore pacchetti
-----------------

Il Gestore pacchetti consente di installare e rimuovere software aggiuntivo nel sistema. 

Il Gestore pacchetti è accedibile solo con le credenziali
del rivenditore. Ogni rivenditore potrà installare sul sistema tutte le linee di prodotto per cui ha sottoscritto un contratto.
|product| potrà quindi essere composto sia da moduli che ricadono sotto il supporto NethService (es. server di posta)
sia da moduli specifici di NethSecurity (es. firewall avanzato).

Visualizzazione log
-------------------

Il nuovo visualizzatore dei log consente di consultare, ricercare e seguire in tempo reale tutti i log di sistema.

Backup
======

Il modulo di backup *non* è installato nella configurazione base ed è suddiviso in due parti: backup della configurazione e backup dei dati.

Il backup della configurazione è automatico e consente di ripristinare velocemente un sistema per minimizzare la discontinuità di servizio. 
In caso di guasto, sarà possibile ripristinare il backup della configurazione e consentire agli utenti di riprendere
il lavoro mentre il backup dei dati verrà ripristinato in background.

Il backup dei dati deve essere esplicitamente configurato secondo le proprie esigenze e prevede le classiche politiche di salvataggio dei dati
(backup incrementali, criteri di conservazione dei dati, notifiche, ecc).

Il supporto ai backup su nastro è stato rimosso.

Al momento, il restore di un backup è possibile solo da linea di comando.

Utenti e gruppi
===============

Il modulo utenti non è installato di default.
Utenti e gruppi sono salvati in LDAP che pertanto è divenuto uno dei servizi fondamentali del sistema.

I servizi di sistema (posta, accesso cartelle condivise, ecc) possono essere attivati o disattivati selettivamente per ciascun utente.

Ogni utente può inoltre accedere all'interfaccia web con le proprie credenziali per modificare password e dati personali. 

DNS e DHCP
==========

Il server DNS non è più autoritativo, ovvero è obbligatorio inserire uno o più indirizzi di server DNS esterni per la risoluzione dei nomi
al di fuori del dominio gestito dal server stesso.

I moduli di DNS e DHCP non sono installati di default e l'interfaccia è stata completamente rivista. Ad esempio è possibile definire alias DNS
multipli, visualizzare la lista degli IP in leasing e riservare un indirizzo agendo direttamente sulla lista degli ip rilasciati.

Server di posta
===============

L'architettura del server di posta è stato completamente riscritta usando i software più diffusi (Postfix + Dovecot + Amavis).

Impostazioni configurabili da interfaccia:

* Gestione coda
* Cartelle condivise
* Quota mail per utente o globale
* Gestione domini evoluta con smart host
* Disclaimer
* Utente spia
* Dimensione massima messaggi
* Politiche conservazione spam

Altre migliorie:

* Integrazione con utenti da Active Directory
* Log unificato in :file:`/var/log/maillog`
* webmail di default TODO

Sono inoltre state introdotte alcune impostatzioni di default che possono impattare sulla configurazione dei client:

* Porta per l'invio (submission): 587
* Obbligatorio l'uso di STARTTLS su porta 143

Cartelle condivise
==================

Le cartelle condivise, precedentemente conosciute come ibay, hanno subito profondi cambiamenti.
Per ciascuna cartella è possibile selezionare il protocollo di accesso.

Samba
-----

Funzioni abilitabili direttamente da interfaccia web:

* ACL
* Cestino di rete
* Accesso ospite
* Auditing

Quando il server è controller di dominio, è sufficiente aggiungere un utente al gruppo :dfn:`domadmins` per renderlo automaticamente
amministratore del dominio.

Web
---

Consente di configurare l'accesso HTTP alla cartella condivisa per un singolo dominio o per tutti i domini configurati. 
Inoltre è possibile personalizzare la configurazione del virtual host associato.

FTP
---

L'accesso FTP alle cartelle condivise è stato rimosso per questioni di sicurezza. 

Altri moduli
============

Alcuni dei nuovi moduli disponibili:

* Gestione UPS in modalità master e slave
* Gestione dei modem IAX
