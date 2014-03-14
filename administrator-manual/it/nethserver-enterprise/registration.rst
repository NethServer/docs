=============
Registrazione
=============

|product| offre la possibilità di tenere sotto controllo i parametri critici di funzionamento tramite 
il Centro Servizi Nethesis, accessibile con la coppia utente/password all'indirizzo https://register.nethesis.it.
Come prima operazione, per ogni |product| installato, è necessario effettuare la 
registrazione per permettere una corretta identificazione e comunicazione con la console web.

Accedere all'interfaccia web del server (https://server:980), fare click su :guilabel:`Registra server` e seguire la procedura guidata:

* Inserire le credenziali rivenditore utilizzate presso il sito https://register.nethesis.it
* Selezionare un server esistente oppure scegliere la creazione di nuovo server
* In caso di creazione assicurarsi di inserire un nome che faciliti l'identificazione del server. Si consiglia anche di immettere una descrizione
* Associare un cliente esistente al nuovo server oppure compilare i campi per la creazione di nuovo cliente
* Confermare i dati immessi per terminare la procedura di registrazione

Al termine sarà possibile installare il software aggiuntivo.

L'installazione di software aggiuntivo dall'interfaccia web è permessa esclusivamente solo ai possessori delle credenziali rivenditore.
L'utilizzo di :command:`yum` da linea di comando permette di aggirare questa limitazione. Pertanto si sconsiglia di consegnare la password di :dfn:`root` all'utente finale.

Il modulo utenti consente di utilizzare l'utente :dfn:`admin` per accedere all'interfaccia web con privilegi amministrativi. 
L'utente :dfn:`admin` potrà quindi configurare l'intero sistema ma non potrà installare software aggiuntivo. 
Per maggiori informazioni, vedi :ref:`admin-user`.
