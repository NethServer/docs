==========================
Note di rilascio |release|
==========================

|product| versione |release|

Cambiamenti
-----------

|product| `rc2 changelog <https://github.com/NethServer/dev/issues?utf8=%E2%9C%93&q=is%3Aissue%20is%3Aclosed%20milestone%3Av7%20closed%3A2016-10-18T13%3A22%3A00Z..2016-11-09T14%3A40%3A00Z>`_

Bug noti
--------

* Lista dei `bug noti <https://github.com/NethServer/dev/issues?utf8=%E2%9C%93&q=is%3Aissue%20is%3Aopen%20label%3Abug%20milestone%3Av7%20>`_

* Discussioni su `possibili bug <http://community.nethserver.org/c/bug>`_

Aggiornamento di rc1 a rc2
--------------------------

Per aggiornare un sistema rc1 a rc2, andare alla pagina :guilabel:`Software
center` e avviare la procedura di aggiornamento come al solito.

Tutti i bug fix sono applicati automaticamente, ma ci sono due cambiamenti che
richiedono un intervento manuale.

* LDAP account with read-only privileges (#5145). Richiesto solo se è installato
  l'RPM nethserver-directory.

* Legacy short user name support (#5142). A cominciare dalla release rc2 il sistema
  è configurato per accettare i nomi utenti in formato lungo e corto. Questo
  significa che l'utente può accedere a qualsiasi servizio basato su PAM o come
  *username* o come *username@domain*.

Per abilitare questi cambiamenti eseguire il seguente comando: ::

    signal-event nethserver-sssd-save

Se il comando non viene eseguito il sistema non supporterà il nome utente in 
formato corto.

Pacchetti rimossi
-----------------

I seguenti pacchetti erano disponibili nella precedente release 6 e sono stati 
rimossi nella 7:

* nethserver-collectd-web: sostituito con nethserver-cgp

* nethserver-password: integrato in nethserver-sssd

* nethserver-faxweb2: vedere la discussione 
  `faxweb2 vs avantfax <http://community.nethserver.org/t/ns-7-faxweb2-vs-avantafax/2645>`_.

* nethserver-fetchmail: sostituito con getmail

* nethserver-ocsinventory, nethserver-adagios: a causa di problemi di 
  compatibilità con Nagios, questi moduli verranno supportati solo su |product| 6

