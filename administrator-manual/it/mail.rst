.. _email-section:

=====
Email
=====

Il modulo Email è composto da tre parti principali:

* server SMTP per l'invio e la ricezione [#Postfix]_
* server IMAP e POP3 per la lettura della posta [#Dovecot]_, e
  linguaggio Sieve per organizzarla [#Sieve]_
* Filtro anti-spam, anti-virus e blocco allegati [#Amavis]_

Vantaggi:

* Completa autonomia nella gestione della posta
* Esclusione di eventuali problemi dovuti al provider
* Possibilità di ricostruire tutto il tragitto dei messaggi al fine di
  individuare eventuali errori
* Scansione anti-spam ed anti-virus ottimizzata

Vedi anche gli argomenti correlati:

* Come funziona la posta elettronica [#Email]_
* Record DNS di tipo MX [#MXRecord]_
* Simple Mail Transfer Protocol (SMTP) [#SMTP]_

.. index::
   pair: email; relay
   pair: email; consegna locale
   pair: email; dominio

.. _email_domains:

Domini
======

|product| consente la gestione di un numero illimitato di domini,
configurabili dalla pagina :guilabel:`Email > Domini`.  Per ciascun
dominio sono disponibili due modalità:

* *Consegna locale*: la posta viene consegnata agli utenti locali e
  salvata in formato Maildir [#MailDirFormat]_
* *Passa ad un altro server* (:dfn:`relay`): la posta ricevuta viene
  inoltrata ad un altro server di posta

.. note:: Eliminando un dominio, non verranno eliminate e-mail, ma
   solo inibita la ricezione di mail indirizzate al dominio.
   Eventuali mail già ricevute rimarranno conservate sul server.

.. index::
   pair: email; spedisci sempre una copia
   pair: email; copia nascosta
   pair: email; bcc

|product| permette di conservare una :dfn:`copia nascosta` di tutte le
mail in transito, con relativo contenuto (quindi non un semplice log
di mittenti e destinatari): tutti i messaggi verranno consegnati sia
al destinatario sia ad un indirizzo personalizzato.  Questa opzione è
configurabile individualmente per ciascun dominio gestito dal server
di posta.

.. warning:: L'attivazione della "copia nascosta" va valutata
   attentamente, perché, in ambito aziendale, potrebbe essere
   equiparata ad un telecontrollo del lavoratore, vietato dalla legge
   in alcuni stati.

.. index::
   pair: email; disclaimer
   pair: email; firma
   pair: email; nota legale in calce

La funzionalità :dfn:`Aggiungi una nota legale in calce ai messaggi
inviati` aggiunge automaticamente alle email in spedizione un testo
predefinito, detto :index:`disclaimer`, utilizzabile, per esempio, per
soddisfare possibili requisiti di legge.  Si noti che :dfn:`firma` e
disclaimer sono concetti molto diversi.

La firma dovrebbe essere inserita nel testo della email solo
dal client di posta (il MUA): Outlook, Thunderbird, ecc..  È un testo
personalizzabile contente ad esempio i dati del mittente, contatti,
indirizzi, numeri di telefono.

Esempio di firma: ::

 Mario Rossi
 MiaAzienda srl Via Bianchi, 12345 Milano
 www.miaziendasrl.it - info@miaziendasrl.it

Il "disclaimer" invece, è un testo fisso e può essere soltanto
"allegato" dal server.  Il disclaimer viene allegato alla mail in
uscita, non aggiunto al messaggio, per non alterarne la validità in
caso di utilizzo di firma digitale.

Esempio di disclaimer: ::

 Le informazioni contenute nella presente comunicazione e i relativi
 allegati possono essere riservate e sono, comunque, destinate
 esclusivamente alle persone o alla Società sopraindicati.  La
 diffusione, distribuzione e/o copiatura del documento trasmesso da
 parte di qualsiasi soggetto diverso dal destinatario è proibita, sia
 ai sensi dell'art. 616 c.p. , che ai sensi del D.Lgs. n. 196/2003.

Il disclaimer può contenere codice Markdown [#Markdown]_ che consente
la formattazione del testo.


.. index::
   pair: email; indirizzi email
   pair: email; pseudonimi

.. _email_addresses:

Indirizzi email
===============

Il sistema consente la creazione di un numero illimitato di
:dfn:`indirizzi email` detti anche :index:`pseudonimi` dalla pagina
:guilabel:`Indirizzi email`.  Ciascun indirizzo è associato ad un
utente o un gruppo di sistema, può funzionare con tutti i domini
configurati oppure solo su domini specifici.  Per esempio:

* Primo dominio: miodominio.it
* Secondo dominio: esempio.com
* Indirizzo email *info* valido per entrambi i domini:
  info@miodominio.it, info@esempio.com
* Indirizzo email *pippo* valido solo per un dominio:
  pippo@esempio.com

.. index::
   pair: email; solo reti locali
   triple: email; privato; interno

A volte, un'azienda preferisce che le comunicazioni aziendali tramite
email utilizzino degli indirizzi email "ufficiali"
(amministrazione@dominio.it o supporto@dominio.it) piuttosto che
indirizzi nominativi (nome.cognome@dominio.it), perché il destinatario
potrebbe essere assente, ed in questo caso non si corre il rischio di
lasciarsi sfuggire eventuali risposte.

L'opzione :guilabel:`Solo reti locali` permette di inibire per un
singolo indirizzo email la possibilità di ricevere messaggi
dall'esterno, pur mantenendo attiva la propria casella postale per la
posta interna.  L'indirizzo privato non potrà ricevere mail
proveniente dall'esterno: tale tecnica rende inutile qualsiasi tipo di
invio all'esterno, dato che inibisce ogni risposta da parte del
destinatario.

.. index::
   pair: email; casella di posta
   pair: email; mailbox

.. _email_mailboxes:


Caselle di posta
================

Il server consente di accedere alle proprie caselle di posta
utilizzando due protocolli:

* IMAP [#IMAP]_ (raccomandato)
* POP3 [#POP3]_ (sconsigliato)

Per motivi di sicurezza, tutti protocolli richiedono la connessione
cifrata in modalità STARTTLS.  Anche se fortemente sconsigliato, è
possibile disabilitare la cifratura abilitando l'opzione
:guilabel:`Consenti connessioni non cifrate`.  In questo modo le
password e i contenuti dei messaggi possono transitare in chiaro nella
rete.

.. warning:: Non consentire le connessioni in chiaro negli ambienti di
             produzione!

.. index::
   triple: email; custom; quota

Dalla stessa pagina lo :guilabel:`Spazio disco` di una casella di
posta può essere limitato da una :dfn:`quota` prestabilita.  Se alle
caselle di posta è applicata una quota, la pagina
:guilabel:`Dashboard > Mail quota` riassume l'utilizzo dello spazio
disco di ogni utente.  La quota può essere personalizzata per un
utente particolare dal controllo :guilabel:`Indirizzi email > Caselle utenti 
> Modifica > > Quota email personalizzata`.

.. index::
   pair: email; conserva spam
   triple: email; conserva spam; personalizzato

I messaggi marcati come **spam** (vedi :ref:`email_filter`) possono
essere spostati automaticamente all'interno della cartella
:dfn:`Junk` abilitando l'opzione :guilabel:`Sposta nella cartella
"Junk"`.  I messaggi di spam vengono automaticamente rimossi dopo
che è trascorso il periodo specificato da :guilabel:`Conserva per`.
Tale periodo può essere personalizzato per un utente particolare dal
controllo :guilabel:`Utenti > Modifica > Servizi > Personalizza tempo
di permanenza delle email di spam`.

.. index::
   pair: email; master user

L'utente ``root`` può impersonare un altro utente, acquisendo pieni
diritti sui contenuti della casella di posta e sui permessi delle
cartelle di quest'ultimo.  L'opzione :guilabel:`Root può accedere
impersonando un altro utente` controlla questa facoltà, conosciuta con
il nome di *master user* in [#Dovecot]_.

Quando :guilabel:`Root può accedere impersonando un altro utente` è
abilitata, il server IMAP accetta qualsiasi nome utente al quale sia
aggiunto il suffisso ``*root``, e la password di ``root`` come
credenziali valide.

Per esempio, per accedere come ``john`` con la password di root
``secr3t``, utilizzare le seguenti credenziali:

* nome utente: ``john*root``
* password: ``secr3t``

.. _email_messages:

Messaggi
========

.. index::
   pair: email; size
   pair: email; retries
   pair: email; coda dei messaggi

Dalla pagina :guilabel:`Email > Messaggi`, il controllo
:guilabel:`Accetta messaggi fino a` imposta la dimensione massima dei
messaggi che attraversano il sistema.  Se questo limite è superato, un
messaggio non entra affatto nel sistema, e viene rifiutato.

Quando un messaggio entra in |product|, viene registrato nella
:dfn:`coda messaggi`, in attesa di essere consegnato o inoltrato
altrove (relay).  Quando |product| inoltra un messaggio ad un server
remoto, possono verificarsi degli errori. Per esempio,

* la connessione di rete fallisce, oppure
* l'altro server è spento, o è sovraccarico.

Questi ed altri errori sono *temporanei*: in questi casi, |product|
tenta di riconnettersi all'host remoto ad intervalli regolari, finché
viene raggiunto un limite.  Il controllo :guilabel:`Tenta l'invio per`
imposta questo limite.  Di default è impostato a *4 giorni*.

Mentre i messaggi sono nella coda, l'amministratore può richiedere un
tentativo immediato di spedizione, premendo il pulsante
:guilabel:`Tenta l'invio` dalla scheda :guilabel:`Gestione coda`.  In
alternativa, l'amministratore può eliminare i messaggi in coda in
maniera selettiva, o svuotare completamente la coda mediante il
pulsante :guilabel:`Elimina tutti`.

.. index::
   pair: email; spedisci sempre una copia
   pair: email; copia nascosta
   pair: email; bcc

L'opzione :guilabel:`Spedisci sempre una copia` abilita la una copia
nascosta di qualsiasi messaggio attraversi il server di posta.  Questa
funzionalità è differente dall'opzione simile nella scheda
:guilabel:`Email > Domain` perché non fa differenza tra i domini di
posta e in più cattura i messaggi in uscita.

.. warning:: In alcuni Stati, abilitare l'opzione :guilabel:`Spedisci
             sempre una copia` può essere contro la legge sulla
             Privacy.

.. index::
   pair: email; smart-host

L'opzione :guilabel:`Invia tramite smarthost` obbliga tutti i messaggi
in uscita ad essere diretti verso un server SMTP speciale, detto in
gergo :dfn:`smarthost`.  Uno smarthost accetta di inoltrare i messaggi
sotto certe restrizioni.  Potrebbe controllare:

* l'indirizzo IP del client
* le credenziali SMTP AUTH

.. note:: Spedire tramite uno *smarthost* è in genere sconsigliato, a
          meno che il server non sia temporaneamente in una
          *blacklist* [#DNSBL]_, o il traffico SMTP sia bloccato
          dall'ISP.


.. index::
   pair: email; filter

.. _email_filter:

Filtro
======

Tutta la posta in transito è sottoposta ad una serie di controlli che
possono essere abilitati selettivamente dalla pagina :guilabel:`Email > Filtro`:

* Blocco allegati
* Anti-virus
* Anti-spam

.. index::
   pair:: email; allegati


Blocco allegati
---------------

Il sistema può ispezionare le email, negando l'accesso a messaggi che
contengono file in formati proibiti dalle politiche aziendali. E'
possibile bloccare i seguenti tipi:

* :dfn:`file eseguibili` (es. exe, msi)
* :dfn:`archivi` di file (es. zip, tar.gz, docx)
* lista personalizzata di estensioni

Il sistema riconosce il tipo del file guardando al suo contenuto,
indipendentemente dal nome del file. Quindi è possibile che file MS
Word (docx) e OpenOffice (odt) siano bloccati perché sono in realtà
anche degli archivi.

.. index::
   pair: email; anti-virus
   see: anti-virus; antivirus

Anti-virus
----------

Il componente anti-virus individua i messaggi di posta elettronica
contenenti virus. I messaggi infetti vengono scartati.  Il database
contenente le impronte dei virus è aggiornato periodicamente.

.. index::
   single: spam
   pair: email; anti-spam
   pair: spam; score
   see: anti-spam; antispam

Anti-spam
---------

Il filtro :dfn:`anti-spam` [#Spamassassin]_ analizza la posta
elettronica rilevando e classificando un messaggio come :dfn:`spam`
[#SPAM]_ utilizzando criteri euristici, regole predeterminate e
valutazioni statistiche sul contenuto del messaggio. 
Il filtro inoltre può controllare se il server mittente è presente in una 
o più blacklist (:index:`DNSBL`).
Un punteggio è associato ad ognuna di queste regole.

Il punteggio totale raccolto alla fine dell'analisi consente al server
di decidere se *rifiutare* il messaggio o *marcarlo* come spam e
consegnarlo lo stesso.  Le soglie dei punteggi sono controllate
mediante i cursori :guilabel:`Soglia spam` e :guilabel:`Soglia rifiuto
messaggio`, nella pagina :guilabel:`Email > Filtro`.

I messaggi marcati come spam hanno uno speciale header ``X-Spam-Flag:
YES``. L'opzione :guilabel:`Aggiungi un prefisso all'oggetto dei
messaggi spam` evidenzia i messaggi marcati come spam, modificandone
con la stringa data l'oggetto (header ``Subject``).

.. index::
   pair: email; spam training
   triple: email; filtri; bayesiani

I filtri statistici, chiamati :dfn:`bayesiani` [#BAYES]_, sono regole
speciali che evolvono e adattano rapidamente l'esito dell'analisi dei
messaggi marcandoli come **spam** o **ham**.

I filtri bayesiani possono essere addestrati mediante un qualsiasi
client IMAP, semplicemente spostando un messaggio dentro o fuori della
:dfn:`cartella "junkmail"`.  Come prerequisito, la cartella *junkmail*
deve essere abilitata dalla pagina :guilabel:`Email > Caselle di
posta`, abilitando l'opzione :guilabel:`Sposta nella cartella
"junkmail"`.

* *Spostando un messaggio dentro la cartella "junkmail"*, i filtri
  apprendono che il messaggio è spam e assegneranno un punteggio più
  alto ad altri messaggi simili.

* Al contrario, *spostando un messaggio fuori di "junkmail"*, i filtri
  apprendono che è *ham*: a messaggi simili sarà assegnato un
  punteggio più basso.

Normalmente qualsiasi utente può addestrare i filtri con questa
tecnica. Se un gruppo chiamato ``spamtrainers`` esiste, solo gli
utenti di questo gruppo saranno invece autorizzati ad addestrare i
filtri.

.. note:: E' buona norma controllare costantemente la propria "junkmail"
          per non correre il rischio di perdere messaggi riconosciuti
          erroneamente come spam.

.. index::
   pair: email; whitelist
   pair: email; blacklist

Se il sistema fallisce nel riconoscere lo spam anche dopo alcuni
tentativi di allenamento, la *whitelist* e la *blacklist* possono
venire in aiuto.  Queste sono liste di indirizzi di posta elettronica
che vengono o sempre ammessi o sempre rifiutati a spedire o ricevere
un messaggio.

La sezione :guilabel:`Regole di accesso per indirizzi email` consente
la creazione di tre tipi di regole:

* :guilabel:`Blocca da`: tutti i messaggi provenienti dal mittente
  indicato vengono sempre bloccati

* :guilabel:`Accetta da`: tutti i messaggi provenienti dal mittente
  indicato vengono sempre accettati

* :guilabel:`Accetta a`: tutti i messaggi destinati all'indirizzo
  indicato vengono sempre accettati

Benchè sconsigliato è possibile creare regole non solo sul singolo indirizzo email, ma su un intero dominio di posta, per farlo è sufficiente specificare solo il dominio nella regola (es: nethserver.org).

.. note:: Il controllo anti-virus è eseguito indipendentemente dalle
          impostazioni di *whitelist*.

.. index::
   pair: port; imap
   pair: port; imaps
   pair: port; pop3
   pair: port; pop3s
   pair: port; smtp
   pair: port; smtps

.. _email-port25:

Blocco porta 25
===============

Se il sistema è anche il gateway della rete, le zone blue e green
non potranno inviare mail a server esterni usando la porta 25 (SMTP).
Il blocco della porta 25 evita che macchine eventuali macchine nella LAN siano
utilizzate da remoto per l'invio di SPAM.

L'amministratore può cambiare questa politica creando un'apposita regola del firewall
nella pagina :ref:`firewall-rules-section`.


.. _email_clients:

Configurazione client
=====================

|product| supporta client per la posta elettronica aderenti agli
standard che utilizzano le seguenti porte IANA:

* imap/143
* pop3/110
* smtp/587
* sieve/4190

L'autenticazione richiede la cifratura in modalità STARTTLS e supporta
le seguenti varianti:

* LOGIN
* PLAIN

Inoltre le seguenti porte SSL sono disponibili per software datato che
ancora non supporta STARTTLS:

* imaps/993
* pop3s/995
* smtps/465

.. warning:: La porta SMTP standard 25 è riservata per i trasferimenti
	     di messaggi tra server MTA. Nei client utilizzare solo le
	     porte *submission*.

Se |product| agisce anche come server DNS nella LAN, registra il suo
nome come record MX insieme ai seguenti alias:

* ``smtp.<dominio>``
* ``imap.<dominio>``
* ``pop.<dominio>``
* ``pop3.<dominio>``

Esempio:

* Dominio: ``miosito.com``
* Hostname: ``mail.miosito.com``
* MX record: ``mail.miosito.com``
* Alias disponibili: ``smtp.miosito.com``, ``imap.miosito.com``,
  ``pop.miosito.com``, ``pop3.miosito.com``.

.. note:: Alcuni client email (es.: Mozilla Thunderbird) sono in grado
          di usare gli alias DNS e il record MX per configurare
          automaticamente gli account di posta, digitando soltanto
          l'indirizzo email.

Per disabilitare il record MX e gli alias, accedere alla console di
root e digitare: ::

  config setprop postfix MxRecordStatus disabled
  signal-event nethserver-hosts-update

.. _email_policies:

Politiche SMTP di invio speciali
================================

La configurazione predefinita di |product| richiede che tutti i client
utilizzino la porta submission (587) con cifratura e autenticazione
abilitate per inviare messaggi attraverso il server SMTP.

Per semplificare la configurazione di ambienti preesistenti, la pagina
:guilabel:`Email > Accesso SMTP` consente di specificare delle
eccezioni ai criteri di accesso SMTP di default.

.. warning:: non modificare i criteri di accesso di default in
             ambienti nuovi!

Per esempio, ci sono alcuni dispositivi (stampanti, scanner, ...) che
non supportano l'autenticazione SMTP, la cifratura o l'uso di porte
personalizzate.  Questi possono essere abilitati all'invio di messaggi
email elencando il loro indirizzo IP nell'area di testo
:guilabel:`Consenti relay dai seguenti indirizzi IP`.

Sotto :guilabel:`Opzioni avanzate` si trovano inoltre

* L'opzione :guilabel:`Consenti relay dalle reti fidate`, che abilita la
  spedizione di messaggi da qualsiasi client connesso dalle reti
  fidate.

* L'opzione :guilabel:`Abilita autenticazione sulla porta 25`, che consente
  l'autenticazione dei client SMTP e l'invio (relay) di messaggi anche
  sulla porta 25.


.. index::
   pair: email; HELO
   alias: HELO; EHLO

.. _email_helo:

HELO personalizzato
===================

Il primo passo di una sessione SMTP è lo scambio del comando
:dfn:`HELO` (o :dfn:`EHLO`).  Tale comando richiede un parametro
obbligatorio che l'RFC 1123 definisce come il nome di dominio
principale, valido, del server.

|product| ed altri server di posta, nel tentativo di ridurre lo spam,
non accettano HELO con domini non registrati nel DNS pubblico.

Quando comunica con un altro server di posta, |product| utilizza il
valore del dominio principale (FQDN) come parametro del comando
HELO. Se questo non è registrato nel DNS pubblico, l'HELO può essere
corretto impostando una *prop* speciale.  Per esempio, assumendo che
``myhelo.example.com`` sia il record registrato nel DNS pubblico,
digitare i seguenti comandi: ::

  config setprop postfix HeloHost myhelo.example.com
  signal-event nethserver-mail-common-save

Tale configurazione è utilizzabile anche quando non si è proprio in
possesso di un dominio registrato, in questo caso è possibile
registrare gratuitamente un DNS dinamico, associarlo all'IP pubblico
del server ed utilizzare questo dominio come parametro ``HeloHost``
del precedente comando.

.. _email_outlook_deleted:

Posta eliminata Outlook
=======================

A differenza della quasi totalià dei client IMAP, Outlook non sposta i messaggi eliminati nel cestino, ma si limita a marcarli "cancellati".
E' possibile forzare lo spostamento di tali messaggi nel cestino con questi comandi: ::

 config setprop dovecot DeletedToTrash enabled
 signal-event nethserver-mail-server-save

Si consiglia quindi di modificare la configurazione di Outlook in modo che nasconda i messaggi eliminati dalla posta in arrivo.
La funzione è disponibile nel menu delle opzioni di visualizzazione.


.. _email_log:

Log
===

Ogni operazione eseguita dal server di posta è trascritta nei seguenti
file di log:

* :file:`/var/log/maillog`: contiene tutte le operazioni di invio e
  consegna
* :file:`/var/log/imap`: contiene tutte le azioni di login/logout alle
  caselle di posta

Un transazione registrata nel file :file:`maillog` di solito coinvolge
diversi componenti del server di posta.  Ogni riga contiene
rispettivamente

* la data e l'ora
* il nome host
* il nome del componente e l'id del processo dell'istanza
* il testo che descrive l'operazione

Di seguito una breve descrizione dei nomi dei componenti e delle
azioni tipiche che eseguono:

``transfer/smtpd``

  Identifica il demone SMTP in ascolto sulla porta 25 pubblica.  Una
  riga di log di questo componente segnala un'attività che coinvolge
  un altro server di posta (MTA).

``submission/smtpd``

  Identifica il demone SMTP in ascolto sulla porta 587 o 465 pubblica.
  Una riga di log di questo componente segnala un'attività che
  coinvolge un client di posta (MUA) che spedisce un messaggio.

``amavis``

  Il demone SMTP Amavis applica tutte le regole di filtraggio della
  posta elettronica.  Le righe di log di questo componente dettagliano
  le decisioni prese dal filtro.

``relay/smtp``

  Questo è il client SMTP connesso ad un server remoto: prende un
  messaggio dalla coda e lo trasferisce al server remoto, così come
  specificato dalla configurazione dei domini di posta.

``delivery/lmtp``

  I messaggi diretti agli account locali sono presi dalla coda e
  trasferiti all'istanza di Dovecot locale.

``dovecot``

  Il demone Dovecot consegna i messaggi nelle caselle di posta degli
  utenti, eventualmente applicando i filtri Sieve.

Un quadro di tutto il sistema è disponibile dal sito *workaround.org* [#MailComponents]_.

.. rubric:: Riferimenti

.. [#Postfix] Postfix mail server http://www.postfix.org/
.. [#Dovecot] Dovecot Secure IMAP server http://www.dovecot.org/
.. [#Sieve] Sieve mail filtering language `http://en.wikipedia.org/wiki/Sieve_(mail_filtering_language) <http://en.wikipedia.org/wiki/Sieve_(mail_filtering_language)>`_
.. [#Amavis] MTA/content-checker interface http://www.ijs.si/software/amavisd/
.. [#Email] Posta elettronica, http://it.wikipedia.org/wiki/Posta_elettronica
.. [#MXRecord] Il record DNS MX, http://it.wikipedia.org/wiki/MX_record
.. [#SMTP] SMTP, http://it.wikipedia.org/wiki/Simple_Mail_Transfer_Protocol
.. [#MailDirFormat] The Maildir format, http://en.wikipedia.org/wiki/Maildir
.. [#Markdown] The Markdown plain text formatting syntax, http://en.wikipedia.org/wiki/Markdown
.. [#IMAP] IMAP http://it.wikipedia.org/wiki/Internet_Message_Access_Protocol
.. [#POP3] POP3 http://it.wikipedia.org/wiki/Post_Office_Protocol
.. [#DNSBL] DNSBL http://it.wikipedia.org/wiki/DNSBL
.. [#SPAM] SPAM http://it.wikipedia.org/wiki/Spam
.. [#Spamassassin] Spamassassin home page http://wiki.apache.org/spamassassin/Spam
.. [#BAYES] Filtro bayesiano http://it.wikipedia.org/wiki/Filtro_bayesiano
.. [#MailComponents] The wondrous Ways of an Email https://workaround.org/ispmail/wheezybig-picture/
