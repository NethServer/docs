.. _shared-folders-section:

.. index:: cartelle condivise

==================
Cartelle condivise
==================

Una *cartella condivisa* è un posto dove i file sono accessibili da un
gruppo di persone tramite Samba (SMB/CIFS).

Permessi di accesso
-------------------

Il tipo di accesso consentito alle cartelle condivise, dipende dal metodo di autenticazione scelto: Se si è selezionato Active Directory come fornitore di autenticazione, è possibile scegliere un (:guilabel:`Gruppo proprietario`). Ogni membro del gruppo può leggere
i contenuti della cartella. Opzionalmente, al gruppo può essere
concesso di modificare il contenuto della cartella e i permessi di
lettura possono essere estesi a chiunque abbia accesso al sistema.
Questo semplice modello di permessi è basato sui tradizionali permessi
del filesystem di UNIX.

I permessi di accesso possono essere ulteriormente raffinati utilizzando le `ACL`, consentendo a singoli utenti o ad altri gruppi i permessi di lettura o scrittura.

Se non è stato scelto un metodo di autenticazione o si è scelto OpenLDAP, non c'è autenticazione per le cartelle condivise, che saranno leggibili e scrivibili da tutti.

Samba
-----

SMB/CIFS è un protocollo molto diffuso che consente di condividere
file in una rete di computer.  In un modo simile agli URL Web visti
sopra, il nome della cartella condivisa diventa il nome della
condivisione SMB.

Per esempio, l'indirizzo di rete SMB per la condivisione ``docs``
potrebbe essere ::

   \\192.168.1.1\docs
   \\MYSERVER\docs

I client compatibili con SMB possono essere utilizzati per impostare
le ACL su specifici file o sotto-directory.  
In ogni momento, il pulsante :guilabel:`Reimposta permessi` propaga i permessi UNIX e
POSIX della cartella condivisa alle sottodirectory.

Se l'opzione :guilabel:`Cestino di rete` è abilitata, i file rimossi
da una cartella condivisa sono in realtà spostati in una directory
"cestino" speciale. L'opzione :guilabel:`Mantieni file omonimi`
assicura che i file nel cestino abbiano sempre nomi distinti,
impedendo la sovrascrittura.

Se è attiva l'opzione :guilabel:`Accesso guest`, sono considerate valide
qualsiasi credenziali vengano presentate.

Se è attiva l'opzione :guilabel:`Visibile`, la cartella condivisa 
sarà elencata fra le cartelle disponibili.
Questa opzione non influisce sui permessi di accesso della cartella.

