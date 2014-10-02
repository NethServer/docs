.. _dns-section:

===
DNS
===

|product| può essere configurato come server :dfn:`DNS` (Domain Name System) della rete. 
Un server :index:`DNS` si occupa della risoluzione dei nomi di dominio (es. *www.esempio.com*)
nei loro corrispettivi indirizzi numerici (es. 10.11.12.13) e viceversa.

Il server DNS esegue le richieste di risoluzione nomi per conto dei client locali, ed è accessibile solo dalla LAN (rete green) e dalla rete ospiti (blue). 

Quando si effettua una risoluzione nomi, il server potrà:

* ricercare il nome all'interno degli host configurati localmente
* effettuare una query sui dns esterni: le richieste vengono salvate in cache per velocizzare le successive query

Se |product| è anche il server DHCP della rete, tutte le macchine saranno configurare per utilizzare il server stesso anche per la risoluzione nomi.


.. note:: E' obbligatorio specificare almeno un DNS esterno all'interno della scheda :guilabel:`Server DNS`


Host
====

La pagina :guilabel:`Host` consente di associare i nomi host ad indirizzi IP, siano essi locali o remoti.

Ad esempio, se si possiede un server web interno, è possibile associare il nome host *www.miosito.com* con l'IP del
server web stesso. Tutti i client potranno quindi raggiungere il sito web digitando il nome scelto.

I nomi configurati localmente hanno sempre la precedenza sui record DNS dei server esterni.
Infatti se il provider inserisce *www.dominio.it* con IP corrispondente al server web ufficiale,
ma in |product| *www.dominio.it* è configurato un ip diverso, i pc della LAN non saranno in grado di vedere il sito in questione.


Alias
=====

Un :dfn:`alias` è un nome alternativo usato per raggiungere il server stesso.
Ad esempio, se il server si chiama *mail.example.com*, è possibile creare un :index:`alias DNS` *myname.example.com*. 
Il server sarà quindi raggiungibile dai client della LAN anche usando il nome appena definito.

Gli alias valgono solo per la LAN interna. Se si desidera che il server sia raggiungibile con lo stesso nome anche dall'esterno
è necessario chiedere al provider di associare l'indirizzo pubblico del nostro server al nome desiderato.



