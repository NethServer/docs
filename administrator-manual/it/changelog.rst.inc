Cambiamenti
===========

Questa è la prima versione ufficiale di |product| 7.
Partendo da questa release, sarà possibile aggiornare qualsiasi installazione alla versione finale.

Di seguito la lista completa delle differenze con la versione beta 1:

* https://www.nethserver.org/the-street-towards-nethserver-7-beta-1/

Cambiamenti tra beta 1 e beta 2
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Nuove funzionalità:

* Nextcloud 10
* repository SCL abilitato di default
* Rotte statiche avanzate
* Bandwidthd (bandiwidthd semplice)
* Getmail (sostituisce Fetchmail)
* Configurazione di Apache cambiata
* Rimozione dei pacchetti da Software Center migliorata

* Molti bug fix a pulizia del codice, principalmente nei seguenti componenti:

  * Let's Encrypt
  * Firewall
  * Samba
  * Home binding
  * DHCP on green
  * Roundcubemail
  * Configurazione SSSD
  * Gestione dei certificati
  * Installazione da USB


Changelog completo:
https://github.com/NethServer/dev/milestone/5?closed=1

Bugs conosciuti:
https://github.com/NethServer/dev/issues?q=is%3Aissue+is%3Aopen+label%3Abug


Pacchetti rimossi
-----------------

I seguenti pacchetti sono stati rimossi:

* nethserver-collectd-web: sostituito con nethserver-cgp
* nethserver-password: integrato in nethserver-sssd
* nethserver-faxweb2: http://community.nethserver.org/t/ns-7-faxweb2-vs-avantafax/2645
* nethserver-fetchmail: sostituito con getmail
* nethserver-ocsinventory, nethserver-adagios: a causa di problemi di compatibilità con Nagios, questi moduli verranno supportati solo su |product| 6.x
