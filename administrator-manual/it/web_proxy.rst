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

.. note:: Se si desidera utilizzare la modalità autenticata, assicurarsi di avere configurato un Account provider.

Configurazione client
=====================
   
Il proxy è sempre in ascolto sulla porta **3128**. Quando si utilizzano le modalità Manuale o Autenticato,
tutti i client devono essere esplicitamente configurati per utilizzare il proxy.
La configurazione è accessibile dal pannello impostazioni del browser.
La maggior parte dei client verranno comunque configurati automaticamente attraverso il protocollo WPAD.
In questo caso è utile attivare l'opzione :guilabel:`Blocca porta HTTP e HTTPS` per evitare il bypass del proxy.

Se il proxy è installato in modalità trasparente, tutto il traffico web proveniente dai client viene intercettato dal firewall
e indirizzato attraverso il proxy. Nessuna configurazione è necessaria sui singoli client.

.. note:: Per rendere accessibile il file WPAD dalla rete ospiti, aggiungere l'indirizzo della rete blue
          nel campo :guilabel:`Consenti host` per il servizio httpd nella pagina :guilabel:`Servizi di rete`.
 
.. _proxy_ssl-section:

Proxy SSL
=========

.. warning:: Decifrare connessioni SSL senza il consenso dell'utente è illegale in molti stati. 

In modalità SSL trasparente, il server è in grado di analizzare anche il traffico HTTPS.
Il proxy implementa il comportamento "peek and splice": stabilisce la connessione SSL con i siti remoti e
verifica la validità dei certificati senza decrittografare il traffico.
Quindi il server può filtrare gli URL richiesti utilizzando il filtro web e tornare la risposta al client.

Bypass
======

In alcuni casi può essere necessario fare in modo che il traffico originato 
da specifici ip della rete o verso alcune destinazioni non passi per il proxy HTTP/HTTPS, 
ma sia instradato direttamente; il traffico in questione non sarà più sottoposto a proxy.

Il proxy consente di creare:

* bypass per sorgente, configurabili nella sezione :guilabel:`Host senza proxy`
* bypass per destinazione, configurabili nella sezione :guilabel:`Siti senza proxy`

Le regole di bypass create sono configurate anche all'interno del file WPAD.

Report
======

Installando il modulo ``nethserver-lightsquid`` il sistema genererà automaticamente i :index:`report di navigazione web`.

LightSquid è un analizzatore di log per Squid leggero e veloce che ogni giorno generare un nuovo report HTML.
Il collegamento all'interfaccia web è disponibile nella scheda :guilabel:`Applicazioni` all'interno della :guilabel:`Dashboard`.

Cache
=====
Nel pannello :guilabel:`Cache` è presente un form per configurare i parametri di cache:

* La cache può essere abilitata o disabilitata (*disabilitata* di default)
* **Dimensione cache disco**: valore massimo della cache di squid sul disco (in MB)
* **Dimensione minima oggetto**: può essere lasciato a 0 per mettere in cache tutto, ma può essere alzato se gli oggetti piccoli non sono desiderati in cache (in kB)
* **Dimensione massima oggetto**: gli oggetti più grandi di questa dimensione non vengono salvati in cache. Se si preferisce la velocità al salvataggio della banda, può essere impostato ad un valore basso (in kB)

Il pulsante :guilabel:`Svuota cache` funziona anche se squid è disabilitato, potrebbe essere utile per liberare spazio su disco.

Siti senza cache
----------------

A volte il proxy non è in grado di fare cache di alcuni siti mal costruiti.
Per escludere uno o più domini dalla cache, usare l'opzione ``NoCache``.

Esempio: ::

  config setprop squid NoCache www.nethserver.org,www.google.com
  signal-event nethserver-squid-save

Porte sicure
============

Le porte sicure sono una lista di porti accessibili attraverso il proxy.
Se una porta non è all'interno della lista delle porte sicure, il proxy si rifiuterà di collegarsi al server.
Per esempio, dato un servizio HTTP che gira sulla porta 1234, tale servizio non sarebbe accessibile usando il proxy.

L'opzione ``SafePorts`` è una lista di porte separata da virgole.
Le porte elencate saranno aggiunte alla lista preconfigurata di porte sicure.

Per esempio, per aprire l'accesso alle porte 446 e 1234: ::

  config setprop squid SafePorts 446,1234
  signal-event nethserver-squid-save

