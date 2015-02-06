==========
WebVirtMgr
==========

WebVirtMgr è usato per la gestione di :index:`macchine virtuali`  attraverso una semplice interfaccia web:

* Creazione e rimozione di macchine virtuali (:index:`KVM`)
* Creazione di template per la creazione di macchine
* Accesso remoto alla macchine attraverso il web
* Interfaccia grafica accattivante

Configurazione
==============

L'applicazione web è in ascolto sulla porta **8000** del server. per esempio: ``http://HOST_IP:8000/``.

Il servizio è disabilitato di default.

Dalla pagina Macchine virtuali è possibile:

* abilitare il gestore delle macchine virtuali
* abilitare l'accesso alla console delle macchine virtuali direttamente dal browser

Per accedere all'interfaccia web, effettuare il login con le credenziali disponibili nella pagina stessa:

* *Utente:* admin
* *Password:* casuale, alfanumerica (modificabile)


.. warning:: 
   Non creare bridge di rete usando l'interfaccia di WebVirtManager.
   E' sufficiente creare il bridge dalla pagina :guilabel:`Rete` ed utilizzarlo all'interno di WebVirtManager.

Per maggiori informazioni si rimanda alla documentazione ufficiale:
* http://wiki.qemu.org/Manual
* http://www.linux-kvm.org/page/Documents
