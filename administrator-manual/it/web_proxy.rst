.. _proxy-section:

=========
Proxy web
=========

Il :index:`proxy web` è un server che si interpone fra i PC della LAN e i siti Internet.
I client effettuano le richieste al proxy che comunica con i siti esterni, quindi
trasmette le risposte al client.

I vantaggi del proxy web sono due:

* possibilità di filtrare i contenuti
* ridurre l'utilizzo della banda facendo cache delle pagine visitate


Il proxy supporta le seguenti modalità:

* Manuale: tutti i client devono essere manualmente configurati
* Autenticato: gli utenti devono inserire nome utente e password per poter navigare
* Trasparente: tutti i client sono automaticamente forzati ad usare il proxy per le connessioni HTTP
* Trasparente SSL: tutti i client sono automaticamente forzati ad usare il proxy per le connessioni HTTP e HTTPS


Configurazione client
=====================
   
Il proxy è sempre in ascolto sulla porta 3128. Quando si utilizzano le modalità Manuale o Autenticato,
tutti i client devono essere esplicitamente configurati per utilizzare il proxy.
La configurazione è accessibile dal pannello impostazioni del browser.
In questo caso è utile attivare l'opzione :guilabel:`Blocca porta HTTP e HTTPS` per evitare il bypass del proxy.

Se il proxy è installato in modalità trasparente, tutto il traffico web proveniente dai client viene intercettato dal firewall
e indirizzato attraverso il proxy. Nessuna configurazione è necessaria sui singoli client.

Proxy SSL
---------

.. warning:: Decifrare connessioni SSL senza il consenso dell'utente è illegale in molti stati. 

In modalità trasparente SSL, il server è in grado di filtrare anche il traffico cifrato in HTTPS. 
Il proxy stabilisce il collegamento SSL con i siti remoti, verifica la validità dei certificati, e decifra il traffico.
Infine genera un nuovo certificato firmato con la Certification Authority (CA) del server stesso.

Il traffico fra il client e il proxy è sempre cifrato, ma sarà necessario installare su tutti i client (browser)
il certificato CA del server.

Il certificato del server è posizionato in :file:`/etc/pki/tls/certs/NSRV.crt`.
Si consiglia di trasferire il file usando un client SSH (es. FileZilla).

    
Filtro contenuti
----------------

Il filtro contenuti analizza il traffico web ed è in grado di bloccare siti pericolosi o contenenti virus.

La configurazione prevede un unico profilo che può lavorare in due modalità:

* Permetti tutto: permette l'accesso a tutti i siti, ad eccezione di quelli esplicitamente bloccati
* Blocca tutto: blocca l'accesso a tutti i siti, ad eccezione di quelli esplicitamente consentiti.

Il filtro contenuti consente di:

* bloccare l'accesso a categorie di siti
* bloccare l'accesso ai siti acceduti usando indirizzi IP
* filtrare gli URL con espressioni regolari
* bloccare file con specifiche estensioni
* specificare blacklist e whitelist per sorgente (ip o utenti)
* specificare blacklist e whitelist per destinazione
* indicare gli indirizzi che possono effettuare il bypass del proxy

