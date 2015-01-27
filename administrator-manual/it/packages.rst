.. index::
   pair: installazione; software addizionale

.. _package_manager-section:

===============
Software center
===============

|product| è altamente modulare: al termine dell'installazione il sistema contiene solo
i moduli di base (es. configurazione di rete, visualizzazione log).
L'amministratore può quindi decidere quali componenti installare in base
alle proprie esigenze (es. :ref:`email-section`, :ref:`dhcp-section`, :ref:`firewall-section`, ecc.).

La vista principale mostra una lista di componenti software. Gli elementi
spuntati rappresentano i componenti installati, mentre quelli non spuntati sono
quelli disponibili. Si può filtrare la lista per categoria.


Per installare o rimuovere i componenti software elencati, aggiungere
o togliere il segno di spunta, quindi premere il pulsante
:guilabel:`Applica`.  La schermata successiva riepiloga cosa sarà
installato e rimosso. Inoltre, viene mostrata la lista di pacchetti
opzionali, da selezionare per l'installazione.

.. NOTE:: 

    I pacchetti opzionali possono essere installati anche *dopo*
    l'installazione del componente relativo: cliccare di nuovo sul
    bottone :guilabel:`Applica` e selezionarli dalla schermata di
    riepilogo.


La sezione :guilabel:`Software installato` elenca i pacchetti installati sul sistema.


Aiuto in linea
==============

Tutti i pacchetti che sono configurabili attraverso il Server Manager
contengono un :index:`manuale in linea` che spiega l'utilizzo base e tutti
i campi contenuti nella pagina.

Il manuale in linea è consultabile in tutte le lingue in cui è tradotto
il Server Manager.

Una lista di tutti i manuali installati nel sistema è disponibile all'indirizzo: ::

 https://<server>:980/<language>/Help

**Esempio**

Se il server ha indirizzo ``192.168.1.2`` e si desidera visualizzare la lista dei manuali in italiano,
usare il seguente indirizzo: ::

 https://192.168.1.2:980/it/Help
