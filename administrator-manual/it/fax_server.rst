==========
Server fax
==========

Il server :index:`fax` (:index:`HylaFAX`) permette di ricevere e inviare fax attraverso un modem
fisico collegato direttamente al server o attraverso un :index:`modem virtuale`. 

L'interfaccia web consente di configurare:

* prefisso e numero di fax
* mittente (TSI)
* un modem fisico specificando i parametri della linea telefonica e la modalità di invio/ricezione
* uno o più :ref:`iax-modem`
* notifiche mail per fax inviati e ricevuti, con documento allegato in formati multipli (PDF, PostScript, TIFF)
* stampa dei fax ricevuti
* stampante virtuale Samba
* rapporto di invio giornaliero
* invio fax attraverso mail


Modem
=====

Sebbene HylaFAX supporti un vasto numero di marche e modelli, si consiglia di utilizzare modem esterni seriali o USB.

Un modem interno, in caso di blocco, richiede il riavvio completo del server, 
mentre un modem esterno ha la possibilità di essere spento in maniera distinta. 
Inoltre, la maggior parte dei modem interni in commercio appartiene alla cosiddetta famiglia dei winmodem, 
modem "software" che necessitano di un driver, solitamente disponibile solo in ambiente Windows. 

Inoltre si consiglia di fare attenzione al fatto che anche molti modem esterni USB sono winmodem.

In linea di massima sono da preferire modem funzionanti in classe 1 o 1.0, in particolare se basati su chipset Rockwell/Conexant o Lucent/Agere.
Sono supportati anche modem in classi 2, 2.0 e 2.1.


Client
======

Si consiglia l'utilizzo del client fax YajHFC (http://www.yajhfc.de/) che si collega direttamente al server e consente:

* l'utilizzo di una rubrica LDAP
* possibilità di selezionare i modem per l'invio
* visualizzare la situazione dei modem fax

Autenticazione
--------------

Il sistema supporta due metodi di autenticazione per l'invio di fax:

* Host Based: utilizza l'indirizzo IP del computer che invia la richiesta
* PAM: utilizza nome utente e password, gli utenti devono appartenere al gruppo *faxmaster*.

Assicurarsi inoltre che sia abilitata l'opzione :guilabel:`Visualizza fax inviati dai client`.

Stampante virtuale Samba
========================

Attivando l'opzione SambaFax il server mette a disposizione della rete locale una stampante virtuale, 
denominata "sambafax".

I singoli client dovranno configurare questa stampante usando il driver *Apple LaserWriter 16/600 PS*.

Il documento da inviare dovrà rispettare i seguenti prerequisiti:

* deve contenere esattamente la stringa "Fax Number: ", contente il numero fax, per esempio: ::

  Fax Number: 12345678

* la stringa può essere presente in qualsiasi posizione del documento, ma su una riga singola.
* la stringa deve essere scritta con carattere non bitmap (ad esempio Truetype)

I fax spediti avranno come mittente l'id del utente specificato. Questa informazione sarà ben visibile nella coda dei fax.

Mail2Fax
========

Tutto le email inviate da rete locale all'indirizzo ``sendfax@<nomedominio>`` saranno trasformate in fax ed inviate al destinatario.

Il ``<nomedominio>`` deve corrispondere ad un dominio di posa configurato per la consegna locale.

Le mail devono rispettare questo formato:

* Il numero del destinatario deve essere specificato nel campo oggetto (o subject)
* L'email deve essere in formato solo testo
* Può contenere allegati di tipo PDF o PS che saranno convertiti e inviati insieme al fax

.. note:: Questo servizio è abilitato solo per i client che inviano mail dalla rete green.

.. _iax-modem:

Modem virtuali
==============

I modem virtuali sono modem software che comunicano con un PBX (solitamente Asterisk) utilizzando 
degli interni IAX.

La configurazione dei modem virtuali si compone di due parti:

1. Creazione dell'interno IAX all'interno del PBX
2. Configurazione del modem virtuale 

