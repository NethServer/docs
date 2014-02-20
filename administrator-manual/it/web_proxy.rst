=========
Proxy web
=========
Il filtro contenuti serve per controllare la navigazione web ed
impostare dei blocchi in base ad alcuni elementi quali parole chiave, ip
interni, utenti interni, valutazione del contenuto della pagina web,
estensioni dei file. Grazie a questo strumento è possibile ad esempio abilitare
l'accesso solo su alcuni siti desiderati (ad esempio quelli di interesse
aziendale) bloccando tutti gli altri.

Nethserver è in grado di svolgere la funzione di server-proxy  con
l’installazione dell’ apposito pacchetto.

Installazione
=============

Per installare il pacchetto Proxy web fare click su Configurazione → Gestione pacchetti. Mettere la spunta su Proxy web e fare click sul pulsante Avanti.

Gestione Proxy web
==================

Per configurare il server proxy fare click su Configurazione → Proxy web.

Verrà aperta una pagina con quattro schede.

Il Proxy Web lavora per ridurre l'utilizzo della banda facendo cache
delle pagine visitate. E' trasparente ai web browser che utilizzano
questo server come loro gateway.

Scheda Proxy
------------

Nella scheda Proxy è possibile abilitare il servizio mettendo la spunta
su Abilita proxy e si può  scegliere la modalità con cui il servizio
dovrà lavorare.

Abilitato
    Abilita il Proxy.

Modalità
^^^^^^^^

Manuale
    Il proxy è abilitato sulla porta 3128. Tutti i client devono essere configurati per usare il proxy


Autenticato
    Il proxy è abilitato sulla porta 3128. Tutti i client devono essere configurati per usare il proxy, ma sono richiesti  lo username e la password prima di procedere con la navigazione. L'autenticazione è basata sugli utenti di |product|.


Trasparente
    Il proxy è abilitato sulla porta 3128, ma la configurazione dei client non è richiesta. Tutto il reaffico sulla porta 80 è rediretto verso proxy.


Trasparente SSL
    Il proxy è abilitato sulla porta 3128, ma la configurazione dei client non è richiesta. Tutto il reaffico sulla porta 80 e 443 è rediretto verso proxy.
    Tutto il traffico SSL è decriptato all'interno del proxy e criptato di nuovo prima di essere inviato
    

Opzioni Avanzate
^^^^^^^^^^^^^^^^

Parent proxy
    Inserire l'IP e la porta del parent proxy. La sintassi corretta è
    Indirizzo_IP:porta .



Filtro
-------------

Modalità
    Abilitando il Filtro Web è possibile configurarlo nella modalità
    "Blocca tutto" e poi permettere le categorie selezionate, oppure
    "Permetti tutto" e poi bloccare le categorie selezionate.

Blocca accesso con IP ai siti web
    Se abilitato, non è possibile accedere ai siti web usando un IP ma solo il nome host.

Abilita filtro con espressioni su URL
    Se abilitato, gli URL sono scansionati alla ricerca di parole che ricadono nelle categorie selezionate. 
    Ad esempio potrebbero essere bloccati gli url che contengono la parola *sesso*.

Lista di estensioni file bloccate
    Inserire le estensioni che si vogliono bloccare, separate da virgola.

Siti e IP bloccati
    Contiene la lista di siti sempre bloccati e la lista degli host della LAN che non possono navigare.

Siti e IP permessi
    Contiene la lista dei siti sempre permessi e degli host della LAN che possono bypassare il filtro contenuti.

Scheda Bypass proxy trasparente
-------------------------------

Nella scheda Bypass proxy trasparente è possibile impostare degli
indirizzi IP della rete che bypassano il proxy.

Per far ciò fare click su crea nuovo ed inserire l’indirizzo IP
sull’apposito campo. Fare click su salva per confermare.

Configurare alcuni IP per bypassare il proxy trasparente ed accedere ad
internet senza essere proxati


Crea una nuova regola di bypass.

Indirizzo IP
    Indirizzo IP dell'host che non sarà filtrato dal proxy.


Scheda Antivirus
----------------

Nella scheda Antivirus è possibile abilitare o disabilitare l’antivirus
ClamAV, fare click sul pulsante Salva per confermare l’impostazione
scelta.

Abilita / disabilita la scansione antivirus delle pagine web.

