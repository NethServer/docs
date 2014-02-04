==========
DNS e DHCP
==========

Gestione alias server, nomi host e DHCP.

Alias server
============

Gli alias sono nomi alternativi per questo server. Per esempio, se il
server si chiama *nethserver.nethesis.it*, un alias potrebbe essere
*mail.nethesis.it*. Il server risponderà con il proprio indirizzo IP
alle richieste per il nome alias indicato.

Crea / Modifica
---------------------

Consente la creazione di un nuovo alias per questo server.

Nome host
    Il nome host che si desidera aggiungere o modificare. Può contenere solo
    lettere, numeri e trattini e deve iniziare con una lettera o un numero.

Descrizione
    Una descrizione opzionale utile a identificare l'alias.


DHCP
====

Il server DHCP (Dynamic Host Configuration Protocol) permette di
assegnare indirizzi IP ai client della rete locale in maniera
automatica.


Configura
---------

Configura il server DHCP.

Disabilitato
    Il server DHCP verrà disabilitato e i client della LAN non riceveranno
    l'indirizzo in maniera automatica da questo server. Selezionare questa
    opzione se è presente un altro server DHCP nella rete locale.

Abilitato
    Il server rilascerà indirizzi IP ai computer della rete locale (opzione consigliata).

Inizio
    Il primo indirizzo IP del range assegnabile ai client della LAN.

Fine
    L'ultimo IP del range, verranno assegnati indirizzi compresi tra Inizio e Fine.

Crea / Modifica
---------------------

Aggiunge una nuova assegnazione statica (reservation) al server DHCP.
L'apparato con l'indirizzo MAC specificato riceverà sempre l'indirizzo
IP inserito.

Nome host
    Il nome host che si vuole assegnare al client della LAN insieme
    all'indirizzo IP.

Descrizione
    Una descrizione opzionale per identificare l'apparato.

Indirizzo IP
    L'indirizzo IP che si desidera assegnare.

Indirizzo MAC
    L'indirizzo MAC dell'apparato di rete (es: 11:22:33:44:55:66:77:88).


DNS
===

Il DNS (Domain Name System) si occupa della risoluzione dei nomi di
dominio (es. www.nethesis.it) nei loro corrispettivi indirizzi numerici
(es. 10.11.12.13) e viceversa. NethServer demanda la risoluzione dei
nomi ai server DNS configurati, ma permette di specificare indirizzi
arbitrari per nomi selezionati. Per esempio, è possibile configurare il
sistema per rispondere alle richieste per l'IP del sito facebook.com con
0.0.0.0, ottenendo l'effetto di rendere irraggiungibile il sito
facebook.com.

Configura
---------

Fare clic su Configura per immettere gli indirizzi dei server DNS che
NethServer contatterà per la risoluzione dei nomi.

DNS primario
    L'indirizzo del server principale da contattare per la risoluzione nomi (obbligatorio).

DNS secondario
    L'indirizzo del server secondario da contattare nel caso in cui il primario non risponda (opzionale).

Crea / Modifica
---------------------

Fare clic su Crea per assegnare un nome host ad un indirizzo IP. Il
server ritornerà l'IP configurato per le richieste del relativo nome
host.

Nome host
    Il nome di dominio, per esempio www.nethesis.it. E' possibile creare
    nomi per il dominio locale, utile per dare un nome mnemonico ad
    apparati configurati con IP statico oppure per qualsiasi dominio,
    che avranno la precedenza sui server DNS del provider (vedere
    esempio di facebook.com sopra).

Indirizzo IP
    L'IP del nome host.

Descrizione
    Una descrizione opzionale per commentare il nome host (esempio:
    "blocco facebook" oppure "server video").

