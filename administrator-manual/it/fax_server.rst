==========
Server fax
==========

Il server :index:`fax` (:index:`HylaFAX`) permette di ricevere e inviare fax attraverso un modem
fisico collegato direttamente a |product| o attraverso un :index:`modem virtuale`. 
Si veda :ref:`iax-modem` per maggiori informazioni. 

Il modem deve supportare l'invio e la ricezione di fax preferibilmente in classe 1 o 1.0 (sono supportati anche le classi 2, 2.0 e 2.1).

Generale
========

Prefisso internazionale
    Il prefisso internazionale da anteporre al proprio numero di fax.
Prefisso
    Il proprio prefisso telefonico.
Numero fax
    Numero fax del mittente.
Mittente (TSI)
    Il TSI viene stampato nell'intestazione del fax ricevente, generalmente nella prima riga in alto. E' possibile inserire il numero di fax oppure un nome di lunghezza massima pari a 20 caratteri (consigliato il nome dell'azienda). Sono consentiti solo caratteri alfanumerici.


Modem
=====

Porta modem
    Indica la porta fisica o virtuale a cui è collegato il modem fax

    * Device standard: consente di selezionare il device da una lista delle porte più comuni
    * Device personalizzato: permette di indicare un device personalizzato da utilizzare come modem fax. *Deve corrispondere al nome di un device del sistema.*
Modalità
    Specifica la modalità di funzionamento del device selezionato. Le modalità disponibili sono:

    * Invia e ricevi: il modem sarà utilizzato per inviare e ricevere fax
    * Solo ricezione: il modem sarà utilizzato esclusivamente per la ricezione di fax
    * Solo invio: il modem sarà utilizzato esclusivamente per l'invio di fax
Prefisso centralino
    Se il modem fax è collegato ad un centralino, potrebbe essere necessario inserire un prefisso per "prendere la linea esterna".
    Se il modem è direttamente collegato ad una linea, oppure il centralino non richiede prefisso, lasciare il campo vuoto.
    Se per chiamare si utilizza un centralino, inserire il prefisso da comporre.

Attesa segnale di linea libera
    Alcuni modem non sono in grado di riconoscere il tono di linea libera
    (in particolare se collegati a centralini) e non compongono il numero
    segnalando l'assenza di tono (errore "No Dial Tone").

    E' possibile configurare il modem per ignorare l'assenza di linea e
    comporre immediatamente il numero. L'impostazione raccomandata è
    "Abilitato", si consiglia di disattivare *Attesa segnale di linea libera* solo in caso di problemi.


Notifiche mail
==============

Formato fax ricevuti
    Il server fax, come operazione predefinita, inoltra i fax ricevuti sotto
    forma di e-mail con allegato. E' necessario specificare l'indirizzo
    e-mail a cui si desidera inoltrare i fax, ed uno o più formati per
    l'allegato. Se non si desidera ricevere il fax in allegato, ma solo una
    notifica di ricezione, deselezionare tutti i formati.

Inoltra fax ricevuti a

    * Gruppo "faxmaster"
        Di default i fax ricevuti vengono inviati al *faxmaster*: se
        un utente deve ricevere i fax in arrivo deve essere aggiunto a tale
        gruppo.
    * Indirizzo mail esterno
        E' possibile indicare un indirizzo mail esterno nel caso si
        vogliano inviare i fax ricevuti ad indirizzi email esterni.

Formato fax inviati
    Se richiesto dal client, il server inoltra una notifica d'invio sotto forma di e-mail con
    allegato. Scegliere il formato in cui si preferisce ricevere il fax
    allegato, se non si desidera ricevere il fax in allegato deselezionare
    tutti i formati.

Aggiungi rapporto spedizione nella notifica di invio fax
    Se selezionato, aggiunge un rapporto di spedizione nella notifica di invio fax.



Funzioni aggiuntive
===================

Visualizza fax inviati dai client
    I client fax consentono anche di visualizzare tutti i fax in arrivo. Se,
    per motivi di riservatezza, si desidera inibire la visione dei fax
    ricevuti, disabilitare questa opzione.

Stampa automaticamente i fax ricevuti
    E' possibile stampare automaticamente tutti i fax ricevuti su una
    stampante configurata su |product| compatibile PCL5. La stampante va
    selezionata tramite l'apposito menu a tendina.

SambaFax
    Selezionando questa opzione il server fax può mettere a disposizione della
    rete locale una stampante virtuale, denominata "sambafax" che dovrà
    essere configurata sui client, selezionando il driver Apple LaserWriter
    16/600 PS. I documenti stampati sulla stampante di rete sambafax
    dovranno contenere esattamente la dicitura "Numero Fax:" seguita dal
    numero di fax del destinatario.

Invia report giornaliero
    Invia un report giornaliero all'amministratore

.. _iax-modem:

=========
Modem IAX
=========

Questa pagina consente di configurare dei modem IAX.

Un modem IAX è un modem software che usa un canale IAX (normalmente
viene fornito da un centralino Asterisk) invece che una linea telefonica
tradizionale.

Crea / Modifica
===============

Nome
    Nome del nuovo modem IAX che si intende creare.
IP server
    Indirizzo IP del server sul quale il modem IAX si registra (es. IP del server Asterisk).
Interno
    Interno IAX sul quale si desidera ricevere i FAX.
Password
    Password dell'interno IAX definito precedentemente.
Numero chiamante
    Numero chiamante mostrato nei FAX in uscita.
Nome chiamante
    Nome chiamante mostrato nei FAX in uscita.

