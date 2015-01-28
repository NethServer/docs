====================
Filtro contenuti web
====================

Il :index:`filtro contenuti` analizza il traffico web ed è in grado di bloccare siti pericolosi o contenenti virus.

La configurazione consente di creare un numero illimitato di profili.
Ciascun profilo è composto da tre parti:

* **Chi**: il client associato al profilo.
  Può essere un utente, un gruppo di utenti, un host o un gruppo di host.

* **Cosa**: quali siti può vedere il client associato al profilo
  E' un filtro creato nella pagina :guilabel:`Filtri`.

* **Quando**: il profilo può essere sempre attivo o essere valido solo in alcuni periodi.
  Le condizioni temporali possono essere create nella sezione :guilabel:`Condizioni temporali`.


Si consiglia di procedere in questo ordine:

1. Selezionare una lista di categorie dalla pagina :guilabel:`Blacklist` ed avviare il download
2. Creare una o più condizioni temporali
3. Creare eventuali categorie personalizzate
4. Creare un nuovo filtro o modificare quello di default
5. Creare un nuovo profilo associato ad un utente o un host esistente, selezionare quindi
   un filtro e una condizione temporale

Il sistema prevede un profilo di default che viene applicato a tutti i client qualora
non rientrino in nessun altro profilo.


Filtri
======

Un filtro consente di:

* bloccare l'accesso a categorie di siti
* bloccare l'accesso ai siti acceduti usando indirizzi IP (consigliato)
* filtrare gli URL con espressioni regolari
* bloccare file con specifiche estensioni
* abilitare blacklist e whitelist globali

Ogni filtro può lavorare in due modalità:

* Permetti tutto: permette l'accesso a tutti i siti, ad eccezione di quelli esplicitamente bloccati
* Blocca tutto: blocca l'accesso a tutti i siti, ad eccezione di quelli esplicitamente consentiti

.. note:: La lista delle categorie compare solo al termine del download della lista selezionata
   nella pagina :guilabel:`Blacklists`.

Blocco Google Translate
-----------------------

E' noto che il servizio di traduzione online di intere pagine html di Google 
può essere usato per riuscire a scavalcare il filtro contenti.
Infatti le pagine visitate attraverso il traduttore fanno riferimento sempre ad un dominio riconducibile
a Google stesso pur avendo al loro interno contenuti provenienti da server esterni. 
In questo modo i blocchi imposti a livello di dominio non possono funzionare limitando l'azione del filtro contenuti.

E' possibile bloccare tutte le richieste a :index:`Google Translate` (in qualsiasi lingua), creando un URL bloccato
nella pagina :guilabel:`Generale` con il seguente contenuto: ``translate.google``.

Utenti da Active Directory
==========================

Se il server è stato configurato per fare il join ad un dominio Active Directory (:ref:`samba_ads`),
è possibile creare profili collegati ad utenti appartenenti al dominio.

.. note:: I gruppi residenti nell'Active Directory non sono supportati.

Antivirus
=========

Si consiglia di abilitare sempre la scansione antivirus sul contenuto delle pagine.
Se il proxy è configurato in modalità trasparente SSL (:ref:`proxy_ssl-section`), la scansione funziona anche sui contenuti scaricati via HTTPS.


Risoluzione problemi
====================

Nel caso una pagina indesiderata non venga bloccata, verificare che:

* il client stia navigando attraverso il proxy
* il client non abbia un bypass configurato nella sezione :guilabel:`Host senza proxy`
* il sito visitato non abbia un bypass configurato nella sezione :guilabel:`Siti senza proxy`
* il client sia associato ad un profilo in cui la pagina non è permessa
* il client non stia navigando in un periodo di tempo in cui il filtro ha una configurazione permissiva
