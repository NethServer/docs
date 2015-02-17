================
Note di rilascio
================

Cambiamenti
===========

* Entrare sempre come ``root``! Le password degli utenti ``root`` e
  ``admin`` non sono più sincronizzate.  La chiave di database
  ``AdminIsNotRoot`` è stata rimossa.

  Il nome utente ``admin`` è disponibile solo se è installato l'RPM
  ``nethserver-directory``.  Per retro-compatibilità ha ancora tutti i
  permessi sul sistema tramite il *Server Manager*.

  Quando ``nethserver-directory`` è installato, ``admin`` viene creato
  automaticamente, come nel passato, ma la sua password Unix non è più
  copiata da ``root``.

* Al termine dell'installazione, il *Server Manager* mostra il 
  *Wizard di prima configurazione*, che consente all'amministratore (utente ``root``)
  di cambiare password, nome host e altri parametri di base.

* La pagina :guilabel:`Package manager` è stata rinominata in
  :guilabel:`Software center`, e spostata nella categoria *Amministrazione*.
  Per migliorare l'usabilità, sono state introdotte due nuove schede
  chiamate moduli *Disponibili* e *Installati*.
  E' ora possibile effettuare l'aggiornamento dei pacchetti e leggere
  il changelog degli aggiornamenti.

* La pagina :guilabel:`Certificato server` mostra il certificato SSL
  auto-firmato e consente di generarne e personalizzarne uno nuovo usando
  anche *nomi alternativi* per il server.
  Il cambio del nome del server dalla pagina :guilabel:`Nome server` non
  genererà più un nuovo certificato SSL. La stessa cosa si applica alla
  pagina :guilabel:`Dati organizzazione`.

* Aggiunto il software :ref:`phonehome-section` che raccoglie le statistiche di utilizzo.
  Il phone home è disabilitato di default.

* La pagina :guilabel:`Accesso remoto` è stata rimossa. L'accesso al
  *server-manager* è ora controllato dalla pagina :guilabel:`Servizi di rete`,
  scegliendo il servizio :guilabel:`httpd-admin`.

* L'accesso a Secure Shell (SSH) è ora configurabile dalla pagina
  :guilabel:`SSH`.

* Le seguenti sezioni sono state rimosse dall'installatore interattivo:
  password di root, filesystem cifrato, selezione tastiera, selezione fuso orario.
  Vedi :ref:`installation-interactive` e :ref:`installation-unattended`.
  Queste opzioni possono essere cambiate nel *Wizard di prima configurazione*.

* Nuovi pacchetti installati di default: bind-utils, traceroute, tmpwatch.

* Se entrambi i pacchetti ``nethserver-mail-filter`` e ``nethserver-firewall-base`` 
  sono installati (modalità gateway), la porta 25 è bloccata dalle reti blue e green.
  Vedi :ref:`email-port25`.


Aggiornamento da 6.5
====================

L'aggiornamento del sistema deve essere eseguito dalla linea di comando.

Assicurarsi che il sistema sia aggiornato: ::

  yum update

Dal momento che la struttura dei repository è cambiata, eliminare il vecchio file di configurazione: ::

  rm -f /etc/yum.repos.d/NethServer.repo

Quindi, avviare l'aggiornamento: ::
  
  yum -c http://pulp.nethserver.org/nethserver/nethserver-6.6.conf update

Al termine, riavviare il sistema.

