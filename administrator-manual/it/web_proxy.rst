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


Il proxy può essere attivato per le zone green e blue.
Le modalità supportate sono:

* Manuale: tutti i client devono essere manualmente configurati
* Autenticato: gli utenti devono inserire nome utente e password per poter navigare
* Trasparente: tutti i client sono automaticamente forzati ad usare il proxy per le connessioni HTTP
* Trasparente SSL: tutti i client sono automaticamente forzati ad usare il proxy per le connessioni HTTP e HTTPS

Configurazione client
=====================
   
Il proxy è sempre in ascolto sulla porta 3128. Quando si utilizzano le modalità Manuale o Autenticato,
tutti i client devono essere esplicitamente configurati per utilizzare il proxy.
La configurazione è accessibile dal pannello impostazioni del browser.
La maggior parte dei client verranno comunque configurati automaticamente attraverso il protocollo WPAD.
In questo caso è utile attivare l'opzione :guilabel:`Blocca porta HTTP e HTTPS` per evitare il bypass del proxy.

Se il proxy è installato in modalità trasparente, tutto il traffico web proveniente dai client viene intercettato dal firewall
e indirizzato attraverso il proxy. Nessuna configurazione è necessaria sui singoli client.

.. _proxy_ssl-section:

Proxy SSL
=========

.. warning:: Decifrare connessioni SSL senza il consenso dell'utente è illegale in molti stati. 

In modalità trasparente SSL, il server è in grado di filtrare anche il traffico cifrato in HTTPS. 
Il proxy stabilisce il collegamento SSL con i siti remoti, verifica la validità dei certificati, e decifra il traffico.
Infine genera un nuovo certificato firmato con la Certification Authority (CA) del server stesso.

Il traffico fra il client e il proxy è sempre cifrato, ma sarà necessario installare su tutti i client (browser)
il certificato CA del server.

Il certificato del server è posizionato in :file:`/etc/pki/tls/certs/NSRV.crt`, può essere scaricato dai client
all'indirizzo ``http://<ip_server>/proxy.crt``.

Bypass
======

In alcuni casi può essere necessario fare in modo che il traffico originato 
da specifici ip della rete o verso alcune destinazioni non passi per il proxy HTTP/HTTPS, 
ma sia instradato direttamente; il traffico in questione non sarà più sottoposto a proxy.

Il proxy consente di creare:

* bypass per sorgente, configurabili nella sezione :guilabel:`Host senza proxy`
* bypass per destinazione, configurabili nella sezione :guilabel:`Siti senza proxy`
