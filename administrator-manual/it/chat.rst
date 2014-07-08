.. _chat-section:

====
Chat 
====

Il servizio di :index:`chat` utilizza il protocollo standard :index:`Jabber`/:index:`XMPP`, supporta TLS sulla porte :index:`XMPP` standard (5222 o 5223).

La principali funzionalità sono:

* messaggi fra gli utenti del sistema
* possibilità di suddividere gli utenti in gruppi, in base all'azienda o al dipartimento/ufficio
* amministratori chat
* messaggi broadcast
* chat di gruppo
* messaggi offline
* trasferimenti file in LAN

Tutti gli utenti di sistema possono accedere alla chat usando le proprie credenziali.


Client
======

I client Jabber sono disponibili per tutte le piattaforme desktop e mobile.

Fra i client più diffusi:

* Pidgin disponibile per Windows e Linux
* Adium per Mac OS X
* BeejibelIM per Android e iOS, o Xabber solo Android

Quando si configura il client, assicurarsi che sia abilitato TLS (o SSL).
Inserire il nome utente e il dominio della macchina.

Se |product| è anche il server DNS della rete, i client dovrebbero trovare automaticamente l'indirizzo del server attraverso speciali
record DNS preconfigurati. In caso contrario, specificare l'indirizzo del server nelle opzioni avanzate.


Amministratori
==============

Tutti gli utenti all'interno del gruppo ``jabberadmins`` sono considerati amministratori del server di chat.
Gli amministratori possono:

* inviare messaggi broadcast
* controllare lo stato degli utenti collegati 


Il gruppo ``jabberadmins`` è configurabile dalla pagina :ref:`groups-section`.
