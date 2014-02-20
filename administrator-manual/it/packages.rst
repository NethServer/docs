==================
Gestione pacchetti
==================

Dopo l’installazione |product| è ancora privo di funzioni specifiche.
Tramite il modulo *Gestione Pacchetti* è possibile 

* aggiungere al sistema i *gruppi di pacchetti*, secondo le proprie
  esigenze, tramite la scheda *Gruppi*,

* consultare l'elenco dei pacchetti già installati, tramite la scheda
  *Pacchetti RPM*.

Un gruppo di pacchetti implementa una funzione specifica all'interno
del sistema, come ad esempio *Mail server*, *Proxy web*, *Backup* o *VPN*.

Per installare un gruppo spuntare la voce corrispondente o, viceversa,
per rimuovere un gruppo già installato togliere il segno di
spunta; procedere quindi premendo il pulsante ``APPLICA``.

Nella schermata successiva viene richiesta conferma delle modifiche da
apportare.  Inoltre, se i gruppi da installare prevedono dei pacchetti
opzionali, è possibile selezionarli per aggiungerli all'elenco delle
cose da installare.

.. note:: L'installazione utilizza la rete per scaricare i pacchetti:
          è necessario che sia configurata e attiva una connessione a
          Internet.

Se i gruppi di pacchetti selezionati richiedono altri gruppi, questi
verranno installati automaticamente. Ad esempio se si seleziona *File
server* verrà installato anche *Utenti e gruppi*.


