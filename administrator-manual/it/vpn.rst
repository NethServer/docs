===
VPN
===

Una :index:`VPN` (Virtual Private Network) consente di instaurare un collegamento sicuro
e cifrato fra due o più sistemi utilizzando una rete pubblica come Internet.

Il sistema supporta due tipi di VPN:

1. :index:`roadwarrior`: collegamento di un terminale remoto alla rete interna

2. :index:`net2net` o :index:`tunnel`: collegamento di due reti remote


OpenVPN
=======

OpenVPN consente di creare facilmente collegamenti VPN, 
porta con sé numerosi vantaggi tra cui:

* Disponibilità di client per vari sistemi operativi: Windows, Linux, Apple, Android, iOS
* Attraversamento NAT multipli, ovvero non è necessario un IP statico dedicato al firewall
* Elevata robustezza
* Semplicità di configurazione


Roadwarrior
-----------

Il server OpenVPN in modalità roadwarrior consente il collegamento di client multipli. 

I metodi di autenticazione supportati sono:

* utente di sistema e password 
* certificato
* utente di sistema, password e certificato

Il server può operare in due modalità: :index:`routed` o :index:`bridged`.
Si consiglia di scegliere la modalità bridged solo se il tunnel deve trasportare traffico non-IP.

Per consentire ad un client di stabilire una VPN:

1. Creare un nuovo account: è consigliato creare un account VPN dedicato
   che utilizzi un certificato. In questo modo non è necessario creare un utente
   di sistema per garantire l'accesso VPN.
   E' invece obbligatorio scegliere un account di sistema se si desidera utilizzare
   l'autenticazione basta su nome utente e password.

2. Scaricare il file che contiene la configurazione e i certificati.

3. Importare il file all'interno del client ed avviare la VPN.


Tunnel (net2net)
----------------

Il collegamento OpenVPN net2net prevede che uno dei server coinvolti
venga eletto come master, mentre tutti gli altri sono considerati slave (client).

I passi da eseguire sul server master sono:

* Abilitare il server roadwarrior
* Creare un account solo VPN per ciascun slave che dovrà collegarsi
* Durante la creazione dell'account ricordarsi di specificare la rete remota
  configurata dietro allo slave

I passi da eseguire sugli slave sono:

* Creare un client dalla pagina :guilabel:`Client` specificando i dati di collegamento al server master
* Copiare e incollare il contenuto dei certificati scaricati dalla pagina
  di configurazione del master

