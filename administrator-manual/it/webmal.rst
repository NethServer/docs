=======
Webmail
=======

:index:`Roundcube` è il client web di posta predefinito.
Le caratteristiche principali della :index:`webmail` sono:

* Semplice e veloce
* Rubrica integrata con LDAP
* Supporto per messaggi HTML
* Cartelle condivise
* Plugin


Plugin
======

Roundcube supporta molti plugin già inclusi nell'installazione.

I plugin abilitati di default sono:

* Manage sieve: gestione dei filtri sulla posta in arrivo
* Mark as junk: marca i messaggi come spam e li sposta nell'apposita cartella

Altri plugin consigliati:

* Notifica nuova mail
* Emoticon
* Supporto VCard

I plugin possono essere aggiunti o rimossi modificando la lista separata da virgole salvata nell'opzione ``Plugins``.
Per esempio, è possibile abilitare i plugin "mail notification", "mark as junk" e "manage sieve plugins" con il seguente comando: ::

 config setprop roundcubemail PluginsList managesieve,markasjunk,newmail_notifier
 signal-event nethserver-roundcubemail-update

Una lista dei plugin inclusi può essere trovata nella directory file:``/usr/share/roundcubemail/plugins``.
Per recuperare la lista, eseguire: ::

 ls /usr/share/roundcubemail/plugins

Accesso
=======

La configurazione di default prevede l'accesso HTTPS alla webmail da tutte le reti.

Se si desidera restringere l'accesso solo alla reti green e alle reti fidate, eseguire: ::

  config setprop roundcubemail access private
  signal-event nethserver-roundcubemail-update

Se si desidera aprire l'accesso da tutte le reti: ::

  config setprop roundcubemail access public
  signal-event nethserver-roundcubemail-update

