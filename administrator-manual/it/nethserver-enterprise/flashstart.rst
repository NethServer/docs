======================
Filtro contenuti cloud
======================

Il filtro contenuti cloud consente di profilare e bloccare il traffico web degli utenti.
Il sistema consente di creare più profili basati sul nome utente (proxy web autenticato)
oppure sull'IP sorgente (proxy trasparente o manuale).

Configurazione
==============

La configurazione del filtro è composta da due parti:

* un profilo associato ad un gruppo di utenti o un groppo di host
* una selezione di blacklist associata al profilo creato

I profili devono essere creati attraverso l'interfaccia web di |product|,
mentre l'associazione profili-blacklist accedendo all'interfaccia remota
FlashStart. Per accedere a FlashStart, fare click su :guilabel:`Configura`,
nella pagina :guilabel:`Filtro contenuti cloud`. 

Proxy manuale o trasparente
---------------------------

Usando questa modalità è possibile profilare gli utenti solo attraverso l'indirizzo IP sorgente.

Procedere come segue:

* Creare un gruppo di host
* Aprire la scheda :guilabel:`Profili IP` e fare click su :guilabel:`Crea nuovo`
* Selezionare un gruppo di host e immettere una descrizione
* Per selezionare le blacklist associate al profilo, fare click su :guilabel:`Configura`
  ed accedere all'interfaccia di FlashStart

Proxy autenticato
-----------------

Usando questa modalità è possibile profilare gli utenti attraverso il nome utente.

Procedere come segue:

* Creare un gruppo di utenti
* Aprire la scheda :guilabel:`Profili utente` e fare click su :guilabel:`Crea nuovo`
* Selezionare un gruppo di utenti e immettere una descrizione
* Per selezionare le blacklist associate al profilo, fare click su :guilabel:`Configura`
  ed accedere all'interfaccia di FlashStart


.. note::
  Affinché il filtro sia in funzione, assicurarsi che tutti i client navighino usando il proxy web.
