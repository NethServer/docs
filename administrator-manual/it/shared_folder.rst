.. _shared-folders-section:

.. index:: cartelle condivise
   single: HTTP
   single: SMB
   single: CIFS

==================
Cartelle condivise
==================

Una *cartella condivisa* è un posto dove i file sono accessibili da un
gruppo di persone, utilizzando diversi metodi, o *protocolli*.  Poiché
|product| è un sistema modulare, i metodi disponibili dipendono da
quali moduli sono stati installati.

I metodi/protocolli disponibili sono:

* Web access (HTTP)
* Samba (SMB/CIFS)

Permessi di accesso
-------------------

Una cartella condivisa appartiene sempre ad un gruppo di utenti
(:guilabel:`Gruppo proprietario`). Ogni membro del gruppo può leggere
i contenuti della cartella. Opzionalmente, al gruppo può essere
concesso di modificare il contenuto della cartella e i permessi di
lettura possono essere estesi a chiunque abbia accesso al sistema.
Questo semplice modello di permessi è basato sui tradizionali permessi
del filesystem di UNIX.

I permessi di accesso possono essere ulteriormente raffinati dalla
scheda :guilabel:`ACL`, consentendo a singoli utenti o ad altri gruppi
i permessi di lettura o scrittura.  Questo modello di permessi esteso
è basato sulla specifica POSIX ACL.


Accesso web
-----------

Il metodo :guilabel:`Accesso web` consente la connessione di un
*browser web* ad una cartella condivisa mediante il protocollo HTTP.
Le risorse web sono identificate da una stringa, detta *Uniform
Resource Locator*, o URL.

Per esempio, se il nome della cartella condivisa è ``docs`` gli URL
per accedervi potrebbero essere: ::

    http://192.168.1.1/docs
    https://192.168.1.1/docs
    http://myserver/docs
    http://www.domain.com/docs
    http://docs.domain.com/

Ogni URL ha tre componenti:

* protocollo (``http://`` or ``https://``),
* nome host (``192.168.1.1``, ``myserver``, ``www.domain.com``),
* percorso (``docs``).

Il gruppo :guilabel:`Indirizzo web (URL)` definisce il componente "percorso".

* :guilabel:`Nome cartella` è il default, lo stesso della cartella
  condivisa, come ``docs`` nell'esempio precedente.

* :guilabel:`Radice del sito web` significa nessun percorso. Per
  esempio ``http://docs.domain.com``.

* :guilabel:`Personalizzato` significa un nome alternativo, da specificare.

Il selettore :guilabel:`Host virtuale` elenca tutti gli
:guilabel:`Alias server` definiti nella pagina :guilabel:`DNS`.
"Tutti" significa che il nome host non è considerato nell'associare
l'URL alla cartella condivisa.

L'accesso web è anonimo è in sola lettura.  Ci sono alcune opzioni con
cui restringere ulteriormente il permesso di accesso.

* :guilabel:`Consenti l'accesso solo dalle reti fidate`, restringe
  l'accesso in base all'indirizzo IP del client,

* :guilabel:`Richiedi la password`, limita l'accesso a chi conosce la
  password condivisa (da specificare).

* :guilabel:`Richiedi connessione SSL cifrata`.


Configurare un'applicazione web
-------------------------------

La casella :guilabel:`Consenti override di .htaccess e dei permessi
di scrittura` attiva una speciale configurazione di Apache pensata per
ospitare una semplice applicazione web in una cartella condivisa.
Consente di modificare la configurazione di default di Apache e di
concedere i permessi di scrittura per specifice sub-directory.

.. warning:: Se una cartella condivisa contiene condice eseguibile,
             come ad esempio script PHP, i permessi degli utenti e le
             possibili implicazioni di sicurezza devono essere
             vaultati attentamente.

Se la casella è abilitata

* i file con nome :file:`.htaccess` sono caricati come `configurazione
  di Apache <http://httpd.apache.org/docs/2.2/howto/htaccess.html>`_.

* un file di testo con nome :file:`.htwritable` posizionato nella
  radice della cartella condivisa può contenere una lista di
  sotto-directory dove Apache ottiene i permessi di scrittura.  La
  sintassi del file è una sotto-directory per ogni riga.  Le righe che
  iniziano con ``#`` sono commenti.  Quando il contenuto del file
  :file:`.htwritable` cambia il pulsante :guilabel:`Reimposta
  permessi` deve essere premuto di nuovo per propagare i permessi al
  file system.

.. note:: Le cartelle condivise sono uno strumento potente ma non
          vanno intese come una soluzione completa per il web hosting!
          Per configurare Apache e i virtual host in maniera più
          avanzata aggiungere un file ``.conf`` sotto la directory
          :file:`/etc/httpd/conf.d/`.  Fare riferimento alla
          documentazione di Apache per questo.

Samba
-----

SMB/CIFS è un protocollo molto diffuso che consente di condividere
file in una rete di computer.  In un modo simile agli URL Web visti
sopra, il nome della cartella condivisa divente il nome della
condivisione SMB.

Per esempio, l'indirizzo di rete SMB per la condivisione ``docs``
potrebbe essere ::

   \\192.168.1.1\docs
   \\MYSERVER\docs

I client compatibili con SMB possono essere utilizzati per impostare
le ACL su specifici file o sotto-directory.  In ogni momento, il
pulsante :guilabel:`Reimposta permessi` ripristina i permessi UNIX e
POSIX secondo quanto definito nelle schede :guilabel:`Generale` e
:guilabel:`ACL`.

Se l'opzione :guilabel:`Cestino di rete` è abilitata, i file rimossi
da una cartella condivisa sono in realtà spostati in una directory
"cestino" speciale. L'opzione :guilabel:`Mantieni file omonimi`
assicura che i file nel cestino abbiano sempre nomi distiniti,
impedendo la sovrascrittura.

Se è attiva l'opzione :guilabel:`Accesso guest`, sono considerate valide
qualsiasi credenziali vengano presentate.

Se è attiva l'opzione :guilabel:`Visibile`, la cartella condivisa 
sarà elencata fra le cartelle disponibili.
Questa opzione non influisce sui permessi di accesso della cartella.

