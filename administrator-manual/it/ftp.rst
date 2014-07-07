===
FTP
===

.. note:: Il protocollo FTP è insicuro: le password sono inviate in chiaro.

Il server :index:`FTP` consente di trasferire file fra client e server.

Un utente FTP può essere :dfn:`virtuale` oppure un utente di sistema.
Gli utenti virtuali possono accedere solo il server FTP: questa è la configurazione consigliata.
L'interfaccia web consente la configurazione solo degli utenti virtuali.

Quando accede al server FTP, un utente può esplorare l'intero filesystem a seconda dei suoi privilegi.
Per evitare di esporre involontariamente informazioni, l'utente può essere confinato in una directory usando l'opzione :dfn:`chroot`:
l'utente non potrà uscire dalla directory in cui è stato configurato.

Questa configurazione può essere usata in caso le cartelle condivise siano usate come un semplice web hosting.
Aggiungere il percorso della cartella condivisa nel campo chroot personalizzato.

Ad esempio, data una cartella condivisa chiamata *miosito*, inserire questo percorso: ::

  /var/lib/nethserver/ibay/miosito

L'utente virtuale potrà accedere solo alla directory specificata.

Utenti di sistema
=================

.. warning:: Questa configurazione è altamente sconsigliata.

Dopo aver abilitato gli utenti di sistema, gli utenti virtuali saranno disabilitati.
Tutta la configurazione deve essere eseguita da linea di comando.

Abilitare gli utenti di sistema: ::

  config setprop vsftpd UserType system
  signal-event nethserver-vsftpd-save

Dato l'utente *goofy*, per prima cosa assicurarsi che sia abilitato per l'accesso remoto da shell. Vedi :ref:`users_services-section`.
Quindi, abilitare l'accesso: ::

  db accounts setprop goofy FTPAccess enabled
  signal-event user-modify goofy
  signal-event nethserver-vsftpd-save

Per disabilitare l'accesso ad un utente precedentemente abilitato ::

  db accounts setprop goofy FTPAccess disabled
  signal-event nethserver-vsftpd-save

Se non esplicitamente disabilitato, tutti gli utenti di sistema hanno l'opzione di chroot all'interno della propria home.
Per disabilitare il chroot di un utente di sistema ::

  db accounts setprop goofy FTPChroot disabled
  signal-event nethserver-vsftpd-save


