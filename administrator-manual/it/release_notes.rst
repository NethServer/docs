==========================
Note di rilascio |release|
==========================

|product| versione |release|

Questa versione è basata su CentOS 7.3:
https://wiki.centos.org/Manuals/ReleaseNotes/CentOS7

Cambiamenti principali da RC4:

* Installatore: aggiunta modalità di installazione manuale
* Account provider: il gruppo "administrators" è stato sostituito dal gruppo "domain admins" (:ref:`server_manager-section`)
* Mail server: sistemata l'espansione di pseudonimi per i gruppi
* Mail server: le caselle di posta condivise sono ora abilitate per default (:ref:`enable_shared_folders-section`)
* Mail server: gli pseudonimi specifici per dominio hanno ora la precedenza su quelli generici
* OpenVPN: abilitato l'avvio automatico dei client VPN al boot
* Filtro web: corretti i profili basati su gruppi
* Firewall: corretta la selezione delle condizioni temporali
* IPS: configurazione aggiornata per l'ultima release pulledpork

Aggiornamento da RC4 a Final
----------------------------

Per aggiornare un sistema RC4 a Final, andare alla pagina :guilabel:`Software
center` e avviare la procedura di aggiornamento seguendo le istruzioni del Server Manager.

.. _server_manager-section:

Accesso al Server Manager
^^^^^^^^^^^^^^^^^^^^^^^^^

Se si desidera abilitare l'accesso al Server Manager ad altri utenti oltre root,
aggiungere gli utenti al gruppo "domain admins" ed eseguire: ::
 
  config delete admins
  /etc/e-smith/events/actions/initialize-default-databases


.. _enable_shared_folders-section:

Caselle di posta condivise
^^^^^^^^^^^^^^^^^^^^^^^^^^

Se si desidera abilitare le caselle di posta condivise dagli utenti, eseguire: ::

  config setprop dovecot SharedMailboxesStatus enabled
  signal-event nethserver-mail-server-update


Changelog
---------

|product| `Final changelog <https://github.com/NethServer/dev/issues?utf8=%E2%9C%93&q=is%3Aissue%20is%3Aclosed%20milestone%3Av7%20closed%3A2017-01-17T00%3A00%3A00Z..2017-01-30%20>`_

Bug noti
--------

* Lista di `bug noti <https://github.com/NethServer/dev/issues?utf8=%E2%9C%93&q=is%3Aissue%20is%3Aopen%20label%3Abug%20milestone%3Av7%20>`_

* Analisi dei `possibili bug <http://community.nethserver.org/c/bug>`_


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

