=========
Proxy web
=========

Con l’avvento delle connessioni veloci tipo DSL la funzione del proxy
web è cambiata. Prima era usato per velocizzare la navigazione creando
una cache del traffico dati, ora questo servizio è tipicamente
utilizzato per scansionare, filtrare e loggare il traffico degli utenti.

Nethserver è in grado di svolgere la funzione di server-proxy  con
l’installazione dell’ apposito pacchetto; il proxy installato offre dei
filtri molto efficaci e molto flessibili.

Installazione
=============

Per installare il
pacchetto  Proxy
web fare click su  Configurazione →Gestione pacchetti. Mettere la spunta
su Proxy web e fare click sul pulsante Avanti. Verrano suggeriti dei
pacchetti aggiuntivi da installare, selezionare quelli che si ritengono
utili e confermare le modifiche al sistema facendo click sul pulsante
Applica.

Al termine dell’ installazione verrà mostrato in alto un messaggio che
ci informa che l’operazione è stata completata correttamente.

Gestione Proxy web
==================

Per configurare il server proxy fare click su Configurazione →Proxy web.

Verrà aperta una pagina con quattro schede.


Il Proxy Web lavora per ridurre l'utilizzo della banda facendo cache
delle pagine visitate. E' trasparente ai web browser che utilizzano
questo server come loro gateway.

Abilitato
    Abilita il Proxy.

Parent proxy
    Inserire l'IP e la porta del parent proxy. La sintassi corretta è
    Indirizzo_IP:porta .


Scheda Proxy
------------

Nella scheda Proxy è possibile abilitare il servizio mettendo la spunta
su Abilita proxy e si può  scegliere la modalità con cui il servizio
dovrà lavorare.

Con l’opzione manuale sarà necessario configurare i browser dei client,
con l’ opzione autenticato sarà necessario inserire le proprie
credenziali sul browser prima della navigazione, con l’ opzione
trasparente non c’è necessità di dichiararlo al browser, con l’opzione
Trasparente con SSL non c’è necessità di dichiararlo al browser e si
utilizzano i protocolli di rete cifrato.

Nel caso si abbiano più server proxy a cascata (es.
Squid3+Dansguardian+Squid) è possibile  dichiarare l’ indirizzo IP del
parent proxy successivo; facendo click su opzioni avanzate verrà
mostrata un campo dove poter inserire l’indirizzo IP del parent proxy



Scheda Filtro
-------------

Nella scheda Filtro si gestisce il filtro contenuti per la navigazione
degli utenti. Qui è possibile:

*  Abilitare il filtro contenuti per il traffico degli utenti. Il filtro
   può essere impostato secondo due diverse modalità speculari con la
   prima si blocca tutto e si scelgono le categorie permesse con la
   seconda di permette tutto e si scelgono le categorie da bloccare.

*  Abilitare l’opzione che blocca la navigazione per siti web che non
   hanno URL (es. `www.sito.it <http://www.google.it>`__) ma indirizzi
   IP. Ciò è utile per bloccare tutti quei siti che vogliono aggirare il
   filtro contenuti del proxy, utilizzando direttamente un indirizzo IP

*  Abilitare il filtro che blocca i siti con espessioni sul URL.

*  Redigere una lista di estenzioni di file che verrano bloccati durante
   la navigazione.

*  Impostare delle regole per amministrare il blocco o il permesso a
   determinati siti e indirizzi IP.

Per far ciò fare click sul pulsante siti e IP permessi oppure siti e IP
bloccati a seconda della regola che si vuole impostare, e inserire l’ IP
bersaglio; è anche possibile bloccare/permettere un dominio o un URL,
facendo click sulla freccia accanto al pulsante aggiungi IP, si apre un
menù a tendina dove scegliere cosa bloccare/permettere.

Una volta inserito il parametro, fare click sull’icona del dischetto
sulla destra per salvare la regola.


Il filtro contenuti serve per controllare la navigazione web ed
impostare dei blocchi in base ad alcuni elementi quali parole chiave, ip
interni, utenti interni, valutazione del contenuto della pagina web,
estensioni dei file. Grazie a questo strumento è possibile ad esempio abilitare
l'accesso solo su alcuni siti desiderati (ad esempio quelli di interesse
aziendale) bloccando tutti gli altri.

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

