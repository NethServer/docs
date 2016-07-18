=============
Reverse proxy
=============

La funzionalità :index:`reverse proxy` è utile quando si desidera accedere a
siti interni dalla rete esterna.

Scenario tipico:

* |product| è il firewall della LAN

* Si possiede il dominio http://mydomain.com

* Si desidera che http://mydomain.com/mysite inoltri le richieste al server
  interno (IP privato: 192.168.2.100)

In questo scenario creare un nuovo record nella pagina :guilabel:`Reverse
proxy`. Impostare il :guilabel:`Nome` dell'elemento a ``mysite`` e
:guilabel:`URL destinazione` a ``http://192.168.2.100``.

Se sono consentite solo connessioni cifrate, abilitare l'opzione
:guilabel:`Richiedi connessione SSL cifrata`.

Si può restringere l'accesso solo ai client appartenenti ad alcune reti,
specificando un elenco separato da virgola di reti in notazione CIDR nel campo
:guilabel:`Accedi da reti CIDR`.


Configurazione manuale
======================

Se la pagina :guilabel:`Reverse proxy` non è abbastanza, è sempre possibile
configurare Apache manualmente, creando un nuovo file nella directory
:file:`/etc/httpd/conf.d/`.

**Esempio**

Creare il file :file:`/etc/httpd/conf.d/myproxypass.conf` con il seguente contenuto: ::

  <VirtualHost *:443>
      SSLEngine On
      SSLProxyEngine On
      ProxyPass /owa https://myserver.exchange.org/
      ProxyPassReverse /owa https://myserver.exchange.org/
  </VirtualHost>

  <VirtualHost *:80>
      ServerName www.mydomain.org
      ProxyPreserveHost On
      ProxyPass / http://10.10.1.10/
      ProxyPassReverse / http://10.10.1.10/
  </VirtualHost>


Far riferimento alla documentazione ufficiale di apache per maggiori informazioni: http://httpd.apache.org/docs/2.2/mod/mod_proxy.html
