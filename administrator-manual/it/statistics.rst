======================
Statistiche (collectd)
======================

:index:`Collectd` è un software che raccoglie periodicamente :index:`statistiche` sulle performance del sistema e 
le salva in speciali file :index:`RRD`.
Le statistiche sono quindi consultabili attraverso un'interfaccia web, denominata:

* Collectd Graph Panel (CGP), pacchetto *nethserver-cgp*

L'interfaccia web è accessibile attraverso un URL casuale, l'indirizzo è
visibile nella sezione :guilabel:`Applicazioni` all'interno della :guilabel:`Dashboard`.
E' possibile condividere l'URL casuale per consentire a utenti non autenticati di visualizzare i grafici.
L'accesso è limitato dalle zone e dagli indirizzi IP configurati nel servizio httpd-admin (in Servizi di rete).

Al termine dell'installazione, il sistema collezionerà le seguenti informazioni:

* utilizzo CPU
* carico di sistema
* numero di processi
* utilizzo memoria RAM
* utilizzo memoria virtuale (swap)
* tempo di accensione
* utilizzo spazio su disco
* operazioni di lettura e scrittura su disco
* interfacce di rete 
* :index:`latenza di rete`

Per ciascuna metrica, l'interfaccia mostra un grafico che contiene sia l'ultimo valore raccolto, sia i valori minimi, massimi e medi.

Latenza di rete
===============

Il plugin :index:`ping` misura la latenza di rete. Ad intervalli regolari, collectd invia un ping ICMP al DNS configurato.
Se la multi WAN è attiva, anche tutti i provider abilitati verranno controllati.

Host aggiuntivi possono essere monitorati (es. server web) usando una lista separata da virgole all'interno della proprietà ``PingHosts``.

Esempio: ::

 config setprop collectd PingHosts www.google.com,www.nethserver.org
 signal-event nethserver-collectd-update

