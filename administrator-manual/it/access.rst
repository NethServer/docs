====================
Accesso a |product|
====================

|product| viene configurato tramite una interfaccia web, per accedere
alle pagine di gestione si utilizza un programma per la navigazione in
internet (es. browser FireFox, Chrome, etc) su di un PC connesso alla
stessa rete LAN del server.

Nella barra degli indirizzi digitare:

https://a.b.c.d:980 oppure https://server:980

dove *a.b.c.d* e *server* sono rispettivamente l'indirizzo IP e il nome del server
impostati al momento dell’installazione.

Se il modulo web server è installato, l'interfaccia web è raggiungibile anche all'indirizzo:

https://server/server-manager

A causa dell'uso del protocollo di cifratura HTTPS per la
comunicazione con il server, il browser ci avviserà che la connessione
non è affidabile perché il server non ha un certificato rilasciato da
una autorità ufficiale.

E' necessario ignorare l'avviso, la procedura varia in base al
browser utilizzato, per esempio sarà necessario fare clic sulla voce “sono
consapevole dei rischi”, verrà così mostrato il pulsante Aggiungi
Eccezione. Fare clic su Aggiungi Eccezione, si aprirà un’ altra
finestra dove si deve fare click sul pulsante Conferma eccezione di
sicurezza.

La connessione rimarrà sicura e cifrata, ma il certificato del 
server non sarà ufficiale. Un certificato valido ha un costo di
abbonamento annuale e non è indispensabile in questa situazione.

Login
=====

La prima pagina dell’interfaccia web è quella di log in. Viene richiesto
nome utente e password. Per configurare il server occorre accedere con
diritti di amministratore quindi:

* Nome utente: **root**
* Password: **password_di_root** (inserita in fase di installazione)

Se è installato il modulo Directory, è possibile abilitare l'utente admin ed utilizzarlo
per accedere all'interfaccia web con gli stessi privilegi dell'utente root.
