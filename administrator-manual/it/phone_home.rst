.. _phonehome-section:

==========
Phone Home
==========
Questo tool è usato per tracciare tutte le installazioni di NethServer nel mondo. Ogni volta che un nuovo NethServer è installato, questo tool invia alcune informazioni sull'installazione attraverso comode API. Le informazioni sono salvate nel database e usate per mostrare dei marcatori in Google Map, con il numero di installazioni raggrupate per paese e release.

Overview
========
Questo tool è *disabled* di default.

Per abilitarlo eseguire: ``config set phone-home configuration status enabled``

Se il tool è *enabled* le informazioni inviate sono:
 * UUID: che si trova in ``/var/lib/yum/uuid``
 * RELEASE: ottenuto da ``/sbin/e-smith/config getprop sysconfig Version``

Tutte le informazioni sono usate per popolare la mappa.

Configurazione
==============
Se usi un proxy modifica i corretti placeholders nel file ``phone-home`` salvato in ``/etc/sysconfig/``: ::

 SERVER_IP=__serverip__
 PROXY_SERVER=__proxyserver__
 PROXY_USER=__proxyuser__
 PROXY_PASS=__proxypass__
 PROXY_PORT=__proxyport__
