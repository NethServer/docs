=======
Hotspot
=======

Il servizio hotspot permette la regolamentazione, tracciabilità e tariffazione dell'accesso
ad Internet nei luoghi pubblici, internet point, hotel, fiere, etc.

Caratteristiche dell hotspot:

* Separazione rete aziendale e rete ospiti
* Gestione degli accessi con utente/password
* Tariffazione a consumo, scadenza, prepagata, a traffico o libera
* Gestore degli accessi su Pannello Web
* Creazione degli utenti e stampa del tagliandino da consegnare al cliente
* Creazione seriale degli utenti e registrazione via SMS/email
* Report per la fatturazione del servizio, filtri e ricerca
* Limitazione della banda utilizzata dagli utenti
* Esportazione della lista account
* Esportazione dei report delle connessioni


Configurazione
==============

.. note::
   Per poter installare l'hotspot è necessario che la macchina abbia almeno una scheda green ed una red configurate e che disponga almeno di 3 schede di rete.


Il server deve essere collegato agli access point della rete per poter gestire il traffico.
La gestione degli utenti e della fatturazione risiede nel Centro Servizi: http://hotspot.nethesis.it

Come procedere:

* assicurarsi di avere almeno un'interfaccia libera (senza ruolo) che sarà assegnata esclusivamente all'hotspot
* assicurarsi che il sistema possa comunicare su Internet verso il Centro Servizi sulle porte TCP/UDP 1812 e 1813 
* accedere alla sezione :guilabel:`Hotspot` per definire l'interfaccia da utilizzare e configurare i parametri del servizio 
* collegare l'interfaccia all'Access Point

Interfaccia web
---------------

L'interfaccia web consente di attivare e disattivare il servizio HotSpot configurandolo secondo le proprie esigenze.

Inoltre è possibile:
* selezionre l'interfaccia di rete associata al servizio HotSpot
* modificare l'indirizzamento di rete dedicato ai client
* abilitare il proxy trasparente e il filtro contenuti
* personalizzare, titolo, piè di pagina, disclaimer e siti senza autenticazione


Access Point
------------

Gli Access Point (AP) devono svolgere la sola funzione di consentire il collegamento con il firewall, 
per cui devono comportarsi come un banale switch di rete, a tal fine è opportuno seguire queste raccomandazioni:

* configurare l’Access Point senza alcuna autenticazione e senza DHCP
* disabilitare qualsiasi servizio (servizi di sicurezza etc.) al fine di evitare interferenze col funzionamento dell'hotspot
* se si utilizzano più AP configurarli con SSID differenti (es: SCUOLA-1/SCUOLA-2/...) in modo da individuare facilmente eventuali AP malfunzionanti
* configurare gli AP con un indirizzo IP statico su un segmento di rete (rfc-1918) differente da quello utilizzato dall'hotspot
* se possibile abilitare la "client isolation", in modo che i vari client che si collegano all'access point non si vedano tra di loro
* configurare gli AP per lavorare su canali differenti in modo da minimizzare le interferenze, gli AP di buon livello permettono di gestire i canali in automatico oppure di selezionarli manualmente
* non utilizzare prodotti troppo scadenti, AP di bassa qualità possono provocare frequenti disconnessioni che poi impattano sulla qualità del servizio generale, la raccomandazione è ancora più importante nel caso si utilizzino dei repeater

Utilizzo del servizio
=====================

Il servizio è amministrabile da centro servizi Nethesis, la documentazione è disponibile al seguente link : https://docs.nethesis.it/Hotspot_NethSecurity#Configurazione_del_Centro_Servizi 

