===
VPN
===

Configurazioni VPN possibili:

1. Collegamento di un terminale remoto alla rete interna
   (roadwarrior), basato su OpenVPN o L2TP/IPsec.

2. Collegamento di due reti remote (net2net), basato su OpenVPN.


Account
=======

La scheda Account consente la gestione degli utenti da utilizzare per
il collegamento VPN a questo server. Gli utenti possono essere di
sistema o dedicati esclusivamente alla VPN.

Crea nuovo
----------

Permette la creazione di un nuovo utente. Per ogni utente il sistema
creerà un certificato x509.

Solo VPN
    Il *Nome* sarà utilizzato per l'accesso VPN. Può contenere solo
    lettere minuscole, numeri, trattini, punti e underscore (\_) e
    deve iniziare con una lettera minuscola. Per esempio "luisa",
    "mrossi" e "liu-jo" sono nomi utente validi, mentre "4amici",
    "Franco Neri" e "aldo/sbaglio" non lo sono.

Utente di sistema
    Abilita l'accesso VPN ad un utente già presente nel sistema
    selezionandolo dal menu a tendina.

Rete remota
    Inserire questi dati solo quando si vuole creare una VPN
    net2net. Questi campi sono utilizzati dal server locale per creare
    correttamente le rotte verso le rete remota.
 
    * Indirizzo di rete: indirizzo di rete della rete remota. Es: 10.0.0.0 
    * Maschera di rete: maschera di rete della rete remota. Es: 255.255.255.0


Client
======

I client VPN consentono di collegare il server ad un altro server VPN
in modo da creare collegamenti net2net.  Al momento sono supportate
solo reti net2net di tipo OpenVPN.

Nome
    Identifica univocamente la VPN

Host remoto
     Nome host o indirizzo IP del server VPN remoto

Porta remota
     Porta UDP su cui il server remoto è in ascolto. Solitamente 1194.

Abilita compressione LZO
    La compressione dei dati LZO deve essere impostata allo stesso
    modo sia sul client che sul server.

Modalità
    Scegliere la stessa modalità configurata sul server.

    * Routed: gli host in VPN sono posizionati su una rete separata
      dalla rete LAN del server remoto
    * Bridged: gli host in VPN sono posizionati sulla rete LAN del
      server remoto

Autenticazione
    Scegliere la stessa modalità configurata sul server.

    * Certificato: incollare nell'apposito spazio il contenuto del
      certificato del client e della CA (Certification Authority)
    * Utente e password: inserire nome utente e password
    * Utente, password e certificato: inserire nome utente e password
      ed incollare il contenuto del certificato del client e della CA
      (Certification Authority)
    * Chiave condivisa: incollare nell'apposito spazio il contenuto
      della chiave condivisa (sconsigliato perchè poco sicuro)

OpenVPN
=======

Configura il server OpenVPN sia per i collegamenti roadwarrior sia
net2net.

Quando si crea una rete net2net, è necessario eleggere uno dei due
server come master.  Il master dovrà avere il server roadwarrior
abilitato.  Il server slave dovrà invece configurare un client
nell'apposita sezione *Client*, avendo cura di inserire i dati della
rete remota.

Abilita server roadwarrior
    Consente di abilitare il server OpenVPN in modalità roadwarrior.
    Tale modalità prevede l'esecuzione di un server in ascolto sulla
    porta 1194 UDP. E' possibile connettere più client VPN.

Modalità autenticazione
    Permette di scegliere la modalità di autenticazione desiderata.
    Sono disponibili tre differenti metodi di autenticazione:
    
    * Utente e password: selezionare quando si desidera usare un
      utente di sistema
    * Certificato: selezionare quando si desiderare creare una VPN
      net2net
    * Utente, password e certificato: selezionare quando si desidera
      il massimo della sicurezza. L'utente deve essere un utente di
      sistema

Modalità routed
    Selezionare quando si desidera trasportare solo traffico IP. La
    rete della VPN è diversa da quella della LAN. (Modalità
    consigliata).

    Il server OpenVPN risponderà alle richieste DHCP provenienti dagli
    host remoti fornendo un indirizzo dalla rete configurata qui
    sotto:

    * Rete: rete riservata per gli host in VPN. Es: 10.1.1.0
    * Netmask: maschera di rete per gli host in VPN. Es: 255.255.255.0

Modalità bridged
    Selezionare quando si desidera trasportare anche traffico non IP
    (es. NetBIOS). In questa modalità gli host remoti avranno un
    indirizzo IP della LAN.

    Il server OpenVPN risponderà alle richieste DHCP provenienti dagli
    host remoti fornendo un indirizzo IP della LAN.  Se nella rete è
    presente un server DHCP, o se |product| è il server DHCP stesso,
    stabilire un intervallo di IP al di fuori di quello configurato
    per il DHCP.  Inoltre assicurasi che gli IP nell'intervallo
    selezionato non siano associati staticamente a nessun host della
    rete aziendale.

    * Inizio range IP: primo indirizzo IP del range
    * Fine range IP: ultimo indirizzo IP del range

Dirotta traffico dei client attraverso la VPN
    Disponibile solo in modalità *routed*.  Tutti i client collegati
    useranno questo server come default gateway.

Consenti traffico fra client
    Disponibile solo in modalità *routed*.  I client collegati
    potranno scambiarsi traffico di rete, ad esempio file con FTP.

Abilita compressione LZO
    Abilita la compressione LZO dei dati. E' necessario che la direttiva
    sia presente sia sul client che sul server. (Consigliato)


L2TP/IPsec
==========

Questo tipo di VPN è disponibile di default su tutti i terminali
Android, iOS e sui sistemi Windows e consente l'accesso sicuro del
terminale da Internet alla rete privata aziendale.

Abilita L2TP
   Attivando L2TP è necessario impostare il ruolo 
   "Controller di dominio" (PDC) nel modulo "Rete Windows", 
   altrimenti l'autenticazione dei client fallirà.

Autenticazione IPsec
   Indica il tipo di autenticazione utilizzata dai client.  Se non è
   possibile importare un certificato nel client, si consiglia l'uso
   di PSK anche se meno sicura.

   * RSA: autenticazione basata sui certificati (si veda la sezione
     *Account*)
   * PSK (Pre-Shared Key): autenticazione basata su una chiave
     condivisa fra client e server.  Si consiglia di scegliere la
     chiave con gli stessi criteri di sicurezza usati per le password.

Indirizzi di rete
   Rete degli host remoti. Es: 192.168.78.0

Maschera di rete
   Maschera di rete degli host remoti. Es: 255.255.255.0

