.. _email-section:

=====
Email
=====

Il mail server è composto da tre moduli principali:

* server IMAP e POP3 per la lettura della posta
* server SMTP per l'invio e la ricezione
* filtro antispam, antivirus e blocco allegati

Vantaggi:

* Completa autonomia nella gestione della posta
* Esclusione di eventuali problemi dovuti al provider
* Possibilità di ricostruire tutto il tragitto dei messaggi al fine di individuare eventuali errori
* Scansione antispam ed antivirus ottimizzata

Approfondimenti:
 
* Come funziona la posta elettronica: http://it.wikipedia.org/wiki/E-mail
* Record MX: http://it.wikipedia.org/wiki/MX_record
* Protocollo SMTP: http://it.wikipedia.org/wiki/SMTP


Domini
======

Il server consente la gestione di un numero illimitato di domini.
Per ciascun dominio sono disponibili due modalità:

* consegna locale: la posta viene consegnata agli utenti locali e salvata in formato Maildir
* inoltro (:index:`relay`): la posta ricevuta viene inoltrata ad un altro server di posta

Approfondimenti:

* Formato Maildir: http://en.wikipedia.org/wiki/Maildir


.. note:: Eliminando un dominio, non verranno eliminate e-mail, 
   ma solo inibita la ricezione di mail indirizzate al dominio. 
   Eventuali mail già ricevute rimarranno conservate sul server.

Copia nascosta
--------------

|product| permette di conservare una copia di tutte le mail in transito, con relativo contenuto,
non un semplice log di mittenti e destinatari: tutti i messaggi verranno consegnati sia al destinatario sia 
ad un utente (o gruppo) locale.
Questa opzione è configurabile individualmente per ciascun dominio gestito dal server di posta.

.. warning:: L'attivazione della funzionalità :index:`copia nascosta` va valutata attentamente, 
   perché, in ambito aziendale, potrebbe essere equiparata ad un telecontrollo del lavoratore, 
   vietato dalla legge in alcuni stati.

Disclaimer
----------

|product| offre una funzionalità che permette di aggiungere automaticamente alle email in uscita un testo predefinito, 
detto :index:`disclaimer`, utilizzabile, per esempio, per soddisfare possibili requisiti di legge.
Si noti che :dfn:`firma` e :dfn:`disclaimer` sono concetti molto diversi.

La :dfn:`firma` dovrebbe essere inserita nel testo della e-mail solo dal client di posta (il MUA): Outlook, Thunderbird, ecc..
E' un testo personalizzabile contente ad esempio i dati del mittente, contatti, indirizzi, numeri di telefono.

Esempio di firma: ::

 Mario Rossi
 MiaAzienda srl
 Via Bianchi, 12345 Milano
 www.miaziendasrl.it - info@miaziendasrl.it

Il :dfn:`disclaimer` invece, è un testo fisso e può essere soltanto "allegato" dal server.
Il disclaimer viene allegato alla mail in uscita, non aggiunto al messaggio, per non alterarne la validità.
Questa tecnica consente di mantenere l'integrità del messaggio in caso di utilizzo di firma digitale.

Esempio di disclaimer: ::

 Le informazioni contenute nella presente comunicazione e i relativi allegati possono
 essere riservate e sono, comunque, destinate esclusivamente alle persone o alla
 Società sopraindicati.
 La diffusione, distribuzione e/o copiatura del documento trasmesso da parte di
 qualsiasi soggetto diverso dal destinatario è proibita, sia ai sensi dell'art. 616
 c.p. , che ai sensi del D.Lgs. n. 196/2003.

Il disclaimer può contenere codice :dfn:`markdown` che consente la formattazione del testo.

Approfondimenti:

* http://en.wikipedia.org/wiki/Markdown


Indirizzi email
===============

Il sistema consente la creazione di un numero illimitato di indirizzi email detti anche :index:`pseudonimi`.
Ciascun indirizzo è associato ad un utente o un gruppi di sistema,
può funzionare con tutti i domini configurati oppure solo su domini specifici.

Esempio:

* Primo dominio: miodominio.it
* Secondo dominio: esempio.com
* Indirizzo email *info* valido per entrambi i domini: info@miodominio.it, info@esempio.com
* Indirizzo email *pippo* valido solo per un dominio: pippo@esempio.com

Se il modulo server di posta è installato, il sistema creerà un indirizzo per tutti i nuovi utenti usando il nome utente.
In fase di creazione dell'utente è possibile specificare per quali domini sarà valido l'indirizzo.

Esempio:

* Dominio: miodominio.it
* Utente: pippo
* Indirizzo creato: pippo@miodominio.it

Indirizzi di gruppo
-------------------

Quando un indirizzo è associato ad un gruppo, il server può consegnare la posta in due modalità:

* inviare una copia del messaggio a ciascun membro del gruppo
* depositare il messaggio in una cartella condivisa

.. note:: In caso di gruppi con molti membri e messaggi contenenti allegati corposi, la prima modalità
   può determinare un utilizzo eccessivo dello spazio su disco.

Tale opzione è configurabile dalla pagina :guilabel:`Gruppi`.


Indirizzi privati
-----------------

A volte, un'azienda preferisce che le comunicazioni aziendali tramite email utilizzino degli indirizzi e-mail "ufficiali"
(amministrazione@dominio.it o supporto@dominio.it) piuttosto che indirizzi nominativi (nome.cognome@dominio.it),
perché il destinatario potrebbe essere assente, ed in questo caso non si corre il rischio di lasciarsi sfuggire eventuali risposte.

L'opzione :guilabel:`Solo reti locali` permette di inibire per un singolo indirizzo e-mail la possibilità di ricevere e-mail dall'esterno,
pur mantenendo attiva la propria casella postale per la posta interna.
L':index:`indirizzo privato` non potrà ricevere mail proveniente dall'esterno: tale tecnica rende inutile qualsiasi 
tipo di invio all'esterno, dato che inibisce ogni risposta da parte del destinatario.



.. _mailboxes-section:

Caselle di posta
================

Il server consente di accedere alle proprie caselle di posta utilizzando due protocolli:

* IMAP
* POP3 (sconsigliato)

Tutti i collegamenti con i client sono cifrati di default.
Anche se fortemente sconsigliato, è possibile disabilitare la cifratura abilitando l'opzione :guilabel:`Consenti connessioni non cifrate`.
Vedi :ref:`mail_client-section`.

I messaggi marcati come SPAM consegnati nella casella possono essere spostati automaticamente all'interno della
cartella :dfn:`junkmail` abilitando l'opzione :guilabel:`Sposta nella cartella "junkmail"`.
Infine è possibile configurare dopo quanto tempo i messaggi di SPAM debbano essere eliminati dalla casella.

Approfondimenti:

* Protocollo IMAP: http://it.wikipedia.org/wiki/Internet_Message_Access_Protocol
* Protocollo POP3: http://it.wikipedia.org/wiki/Post_Office_Protocol 

.. _mail_messages-section:

Messaggi
========

L'amministratore può stabilire la dimensioni massima dei messaggi:
i messaggi con dimensione maggiore saranno rifiutati.

In caso di errore, il server tenterà di consegnare la posta ad host remoti ad intervalli regolari
sino a raggiungere il tempo massimo configurato: il default sono 4 giorni.

Smarthost
---------

In questa modalità il server non si occupa direttamente della spedizione, 
ma consegna la posta ad un mail server esterno (generalmente quello del provider) che spedisce l'e-mail al suo posto.

Il server SMTP (definito tecnicamente :index:`smarthost`) accetterà e-mail se:

* è stato configurato per fare da SMTP relay per l'indirizzo IP di |product| (normale configurazione per un provider)
* |product| utilizza l'SMTP AUTH, autenticazione basata su username e password

.. note:: L'utilizzo di smarthost è sconsigliato. Utilizzare questa funzione solo in caso
   il server sia temporaneamente in blacklist.

Approfondimenti:

* Blacklist antispam: http://it.wikipedia.org/wiki/DNSBL

Filtro
======

Tutta la posta in transito è sottoposta ad una serie di controlli che possono essere abilitati selettivamente:

* :index:`antivirus`
* antispam
* blocco allegati

Antivirus
---------

Individua le mail che contengono virus. I messaggi infetti vengono scartati e non sono consegnati al destinatario.

Blocco allegati
----------------

Individua le mail che contengono :index:`allegati proibiti` dalle politiche aziendali. E' possibile bloccare i seguenti
tipi:

* :index:`file eseguibili` (es. exe, msi)
* :index:`archivi` di file (es. zip, tar.gz, docx)
* lista personalizzata di estensioni

Nel caso si scelga di bloccare file eseguibili o archivi, il sistema riconosce tali tipi indipendentemente dal nome file.
E' quindi possibile che file MS Word (docx) e OpenOffice (odt) siano bloccati perché sono di fatto degli archivi.


Antispam
--------

Il filtro :index:`antispam` analizza i messaggi di posta rilevando e classificando lo spam utilizzando criteri euristici, 
regole predeterminate e valutazioni statistiche sul contenuto della mail.

Il server utilizza una combinazione di regole e filtri statistici.
Le regole sono pubbliche e aggiornate regolarmente come viene fatto da tempo per gli antivirus. Ad ogni regola è associato
un punteggio. I filtri statistici, detti bayesiani, sono speciali regole che evolvono e si adattano
velocemente analizzando i messaggi marcati come :index:`spam` o :index:`ham`.

Il totale del punteggio antispam ottenuto al termine dell'analisi consente al server di decidere se rifiutare 
il messaggio o marcarlo come spam.

Anche se sconsigliato, è possibile modificare le soglie con le opzioni :guilabel:`Soglia spam` e :guilabel:`Soglia rifiuto messaggio`.

.. note:: Anche se altamente improbabile, il sistema potrebbe assegnare un punteggio maggiore di 15 ad una mail valida. 
   In questo caso, il mittente riceverà un errore chiaro (552 spam score exceeded threshold).


Approfondimenti:

* Cos'è lo SPAM: http://it.wikipedia.org/wiki/Spam e http://wiki.apache.org/spamassassin/Spam
* Filtri bayesiani: http://en.wikipedia.org/wiki/Naive_Bayes_spam_filtering

.. _bayes-section:

Bayes
^^^^^

Il sistema antispam viene costantemente allenato attraverso i messaggi posizionati nella cartella :dfn:`junkmail`.
Per indicare al sistema una mail di spam non riconosciuta basterà spostarla nella apposita cartella :index:`junkmail`.
Per segnalare invece una mail valida erroneamente marcata come spam sarà necessario spostarla fuori da tale directory.

Di default, tutti gli utenti possono allenare i filtri in questo modo. 
Per restringere la facoltà di allenamento soltanto ad alcuni utenti,
è necessario creare un gruppo chiamato ``spamtrainers`` contenente gli utenti abilitati all'allenamento dei filtri.

.. note:: E' buona norma controllare costantemente la propria junkmail per non correre il rischio di perdere mail
   riconosciute erroneamente come spam.

Whitelist e blacklist
^^^^^^^^^^^^^^^^^^^^^

Whitelist e blacklist sono liste di indirizzi email rispettivamente sempre consentiti e sempre bloccati.

La sezione :guilabel:`Regole di accesso per indirizzi email` consente di creare tre tipi di regole:

* :guilabel:`Blocca da`: tutti i messaggi provenienti dal mittente indicato vengono sempre bloccati
* :guilabel:`Accetta da`: tutti i messaggi provenienti dal mittente indicato vengono sempre accettati
* :guilabel:`Accetta a`: tutti i messaggi destinati all'indirizzo indicato vengono sempre accettati

.. warning:: L'utilizzo delle blacklist è sconsigliato. Ricorrere a questa opzione
   solo se il sistema antispam fallisce il riconoscimento anche dopo un corretto allenamento
   dei filtri bayesiani.


Gestione coda
=============

I messaggi che devono essere inviati vengono posizionati in una coda.
Qualora un messaggio non possa essere consegnato, il messaggio rimarrà nella coda sino a quando
non raggiungerà il tempo massimo configurato per l'invio (vedi :ref:`mail_messages-section`).

Mentre i messaggi sono in coda è possibile forzare un nuovo tentativo attraverso il pulsante
:guilabel:`Tenta l'invio`. In alternativa l'amministratore può selettivamente eliminare i messaggi in coda o
svuotare la coda con il pulsante :guilabel:`Elimina tutti`.

.. _mail_client-section:

Configurazione client
=====================

Il server supporta qualsiasi :index:`client mail`, le porte da configurare sono:

* IMAP: 143 con TLS
* POP3: 110 con TLS
* SMTP: 587 con TLS

Il server è raggiungibile dalla LAN usando i seguenti alias:

* smtp.<dominio>
* imap.<dominio>
* pop.<dominio>
* pop3.<dominio>

Esempio:

* Dominio: miosito.com
* Alias disponibili: smtp.miosito.com, imap.miosito.com, pop.miosito.com, pop3.miosito.com

Se il server di posta è anche DNS della rete, alcuni client di posta (es. Mozilla Thunderbird)
sono in grado utilizzare gli alias DNS per configurare automaticamente gli account di posta inserendo semplicemente
nome utente e dominio.


Alias DNS
=========

I seguenti alias DNS sono riservati:

* smtp.<dominio>
* imap.<dominio>
* pop.<dominio>
* pop3.<dominio>

Per disabilitare gli alias: ::

  config setprop postfix MxRecordStatus disabled
  signal-event nethserver-hosts-save

HELO personalizzato
===================

Il primo passo di una sessione SMTP è lo scambio del comando :index:`HELO` (o :index:`EHLO`). 
Tale comando richiede un parametro obbligatorio che l'RFC 1123 definisce come il nome di dominio principale, valido, del server.

Alcuni mail server, nel tentativo di ridurre lo spam, non accettano HELO con domini non registrati 
o comunque pretendono di effettuare alcuni controlli sulla validità del dominio, 
motivo per cui, se si utilizza un dominio non registrato come dominio principale, 
sarà impossibile spedire posta ai mail server che verificano il campo HELO.

|product| utilizza il valore del dominio principale (FQDN) come parametro del comando HELO.
Nel caso in cui non sia possibile configurare sul server un dominio reale,
ad esempio quando si vuole mantenere la consistenza con un server di dominio esistente,
è possibile comunque cambiare il dominio comunicato da HELO, tramite questi comandi: ::

  config setprop postfix HeloHost myhelo
  signal-event nethserver-mail-common-save

Dove ``myhelo`` è il dominio che si vuole utilizzare nel comando HELO.

Tale configurazione è utilizzabile anche quando non si è proprio in possesso di un dominio registrato, 
in questo caso è possibile registrare gratuitamente un DNS dinamico, 
associarlo all'IP pubblico del server ed utilizzare questo dominio come parametro ``HeloHost`` del precedente comando.


Policy invio
============

Tutti i client che vogliono spedire posta usando il server SMTP devono obbligatoriamente
utilizzare la porta di submission 587 con cifratura abilitata.

Il server implementa politiche di accesso supplementari che consentono configurazioni
particolari in caso di ambienti legacy.

Per abilitare l'invio sulla porta 25 con autenticazione da qualsiasi client sulla LAN o Internet,
usare questi comandi: ::

  config setprop postfix AccessPolicies smtpauth
  signal-event nethserver-mail-server-save

Per abilitare l'invio sulla porta 25 senza autenticazione da tutti i client nelle reti 
fidate, usare questi comandi: ::

  config setprop postfix AccessPolicies trustednetworks
  signal-event nethserver-mail-server-save

Le policy possono anche essere combinate: ::

  config setprop postfix AccessPolicies trustednetworks,smptauth
  signal-event nethserver-mail-server-save


Esistono però alcuni dispositivi che non supportano la cifratura o il cambio di porta.
In questo caso si può forzare la configurazione del mail server affinché accetti
l'invio da uno o più IP sulla porta 25 senza autenticazione: ::

  mkdir -p /etc/e-smith/templates-custom/etc/postfix/access
  echo "192.168.1.22 OK" >> /etc/e-smith/templates-custom/etc/postfix/access/20clients
  signal-event nethserver-mail-common-save
  signal-event nethserver-mail-server-save

.. warning:: Il cambio delle policy di default è sconsigliato e deve essere effettuato solo per gestire
   client speciali o situazioni temporanee.

Log
===

Tutte le operazioni sono salvate sui file di log:

* :file:`/var/log/maillog`: contiene tutte le operazioni di invio e consegna 
* :file:`/var/log/imap`: contiene tutte le azioni di login/logout alle caselle di posta
