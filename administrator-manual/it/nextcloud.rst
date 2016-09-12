=========
Nextcloud
=========

`Nextcloud <http://nextcloud.com/>`_ è una soluzione flessibile per la sincronizzazione dei file e la loro condivisione. È possibile avere i propri file sempre a portata di mano su ogni dispositivo, utilizzando un dispositivo mobile, un personal computer, una workstation o un accesso web. La condivisione viene realizzata in maniera semplice, sicura, e privata che significa avere il pieno controllo dei propri dati.

La piattaforma offre inoltre la possibilità di visualizzare, modificare e sincronizzare i propri contatti e calendari su tutti i propri dispositivi.

**Funzionalità:**

* configurazione automatica di :index:`Nextcloud` con database MariaDB con credenziali di default
* configurazione automatica di httpd
* integrazione automatica con gli utenti e gruppi di sistema di |product|
* documentazione
* backup dei dati automatico tramite nethserver-backup-data


Installazione
=============

È possibile installare Nextcloud tramite l'interfaccia web di |product|.
Dopo l'installazione:

* accedere all'interfaccia web di Nextcloud tramite l'url https://your_nethserver_ip/nextcloud
* usare le credenziali di default **admin/Nethesis,1234**
* cambiare la password di default

L'autenticazione LDAP è abilitata di default cosicché ciascun utente presente nel sistema può accedere tramite le sue credenziali.

Ciascun utente presente nel sistema può accedere automaticamente tramite le sue credenziali, indipendentemente dal provider utenti utilizzato (vedi :ref:`users_and_groups-section`).
Dopo l'installazione sarà presente anche un nuovo widget applicativo nella dashboard di |product|.


Lista utenti
------------

La lista utenti è mostrata all'interno del pannello dell'amministratore di Nextcloud e usa identificatori univoci contenenti lettere e numeri.
È una soluzione adottata da Nextcloud per garantire che non ci siano nomi duplicati. Per maggiori informazioni leggere la sezione `Internal Username` della `documentazione ufficiale <https://docs.nextcloud.com>`_.


Trusted Domains
===============

I `Trusted domains` sono una lista di domini su cui l'utente può effettuare il login. Quelli presenti di default sono:

* nome dominio
* indirizzo ip

Per aggiungerne uno nuovo eseguire: ::

    config setprop nextcloud TrustedDomains server.domain.com
    signal-event nethserver-nextcloud-update

Per aggiungerne più di uno è sufficiente concatenare i nomi con una virgola.
