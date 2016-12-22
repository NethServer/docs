==========================
Note di rilascio |release|
==========================

|product| versione |release|

Questa versione è basata su CentOS 7.3:
https://wiki.centos.org/Manuals/ReleaseNotes/CentOS7

Cambiamenti principali:

* L'interfaccia web ora elenca gli utenti e gruppi remoti in tempo reale (#5168)
* LDAP e Samba AD hanno entrambi gli stessi gruppi e utenti amministrativi (#5157)
* I gruppi amministrativi built-int possono essere configurati dal Server Manager (#5168)
* Configurazione semplificata degli account provider remoti (#5165)
* Le condivisioni Samba supportano sia l'autenticazione NTLM sia  l'autenticazione Kerberos (#5160)
* Il protocollo LDAP sicuro è sempre abilitato per le connessioni agli account provider remoti (#5161)
* Nextcloud è stato aggiornato alla versione 10.0.2 (#5155)
* Migliore gestione dei certificati (#5174)
* Il modulo DPI ora funziona su kernel standard (#5170)
* SquidGuard è stato sostituito da ufdbGuard (#5171)
* Il proxy web HTTPS trasparente non richiede l'installazione del certificato sui client (#5169)
* Supporto BIOS UEFI (#5148)
* La dimensione della partizione di avvio è stata aumentata a 1 GB

Aggiornamento di rc2 a rc3
--------------------------

Per aggiornare un sistema rc2 a rc3, andare alla pagina :guilabel:`Software
center` e avviare la procedura di aggiornamento come al solito.
Se il sistema sta utilizzando un kernel DPI, prima di aggiornare verificare
:ref:`dpi-kernel_section`.

Tutti i bug fix sono applicati automaticamente, ma alcuni miglioramenti
richiedono un intervento manuale.

Dopo l'aggiornamento eseguire: ::

    signal-event nethserver-sssd-save

Se il filtro web è installato, eseguire: ::

  /etc/cron.daily/update-squidguard-blacklists
  signal-event nethserver-squid-update

Al termine dell'aggiornamento, si consiglia di riavviare il sistema
per caricare il nuovo kernel.

.. _dpi-kernel_section:

Aggiornare un firewall con kernel DPI
-------------------------------------

Per aggiornare un sistema che utilizza il kernel-lt con supporto DPI, eseguire 
i seguenti comandi prima di aggiornare: ::

  cat << EOF > /etc/sysconfig/kernel
  # UPDATEDEFAULT specifies if new-kernel-pkg should make
  # new kernels the default
  UPDATEDEFAULT=yes

  # DEFAULTKERNEL specifies the default kernel package type
  DEFAULTKERNEL=kernel
  EOF

  yum reinstall grubby -y


Changelog
---------

|product| `rc3 changelog <https://github.com/NethServer/dev/issues?utf8=%E2%9C%93&q=is%3Aissue%20is%3Aclosed%20milestone%3Av7%20closed%3A2016-11-10T14%3A40%3A00Z..2016-12-16T10%3A40%3A00Z%20>`_


Bug noti
--------

* WebTop 4 al momento non funziona con account provider remoti in quanto non supporta il protocollo LDAPS

* Lista di `bug noti <https://github.com/NethServer/dev/issues?utf8=%E2%9C%93&q=is%3Aissue%20is%3Aopen%20label%3Abug%20milestone%3Av7%20>`_

* Analisi dei `possibili bug <http://community.nethserver.org/c/bug>`_


Pacchetti rimossi
-----------------

CentOS 7.3 include Squid 3.5, che non è compatibile con l'attuale
implementationze di antivirus web (C-ICAP + Squidclamav),
quindi in questa versione nethserver-squidclamav è stato rimosso.
Stiamo lavorando per trovare un sostituto adeguato per il prossimo rilascio.

I seguenti pacchetti erano disponibili nella precedente release 6 e sono stati 
rimossi nella 7:

* nethserver-collectd-web: sostituito con nethserver-cgp

* nethserver-password: integrato in nethserver-sssd

* nethserver-faxweb2: vedere la discussione 
  `faxweb2 vs avantfax <http://community.nethserver.org/t/ns-7-faxweb2-vs-avantafax/2645>`_.

* nethserver-fetchmail: sostituito con getmail

* nethserver-ocsinventory, nethserver-adagios: a causa di problemi di 
  compatibilità con Nagios, questi moduli verranno supportati solo su |product| 6

