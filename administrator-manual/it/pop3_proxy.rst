==========
Proxy POP3
==========

Un utente della LAN potrebbe configurare il proprio client di posta
al fine di collegarsi ad un server POP3 esterno, per scaricare i propri messaggi.
La posta scaricata potrebbe però contenere virus che potrebbero infettare il computer eludendo ogni controllo da parte del server.

Il proxy POP3 intercetta le connessioni ai server esterni sulla porta 110, scansionando tutte le mail in entrata,
in modo da bloccare i virus ed etichettare lo spam. 
Per i client di posta il processo è assolutamente trasparente: l'utente crederà di collegarsi direttamente
al server POP3 del proprio provider, mentre il proxy intercetterà tutto il traffico effettuando la connessione al server esterno.

E' possibile attivare selettivamente i seguenti controlli:

* antivirus: i messaggi contenenti antivirus vengono rifiutati ed una mail di notifica è inviata al destinatario
* antispam: i messaggi verranno marcati con gli opportuni punteggi antispam


POP3s
=====

Il proxy può intercettare anche le connessioni POP3s sulla porta 995.
Sarà compito del server stabilire una connessione sicura con i server esterni, mentre lo scambio dati con i client
della LAN avverrà in chiaro.

.. note:: I client dovranno essere configurati per collegarsi alla porta 995 ma dovranno disattivare la cifratura.
