==========
Proxy pass
==========

La funzionalità :index:`proxy pass` è utile quando si desidera accedere a siti
interni dall rete esterna.

La configurazione del proxy pass deve essere effettuata da linea di comando.
Prima di procedere, assicurarsi che il pacchetto ``nethserver-httpd`` sia installato: ::

  yum install -y nethserver-httpd

Scenario:

* |product| è il firewall della LAN
* Si possiede il dominio http://mydomain.com
* Si desidera che http://mydomain.com/mysite inoltri le richieste al server interno (IP privato: 192.168.2.00)

Comandi per questo esempio: ::

  db proxypass set mysite ProxyPass
  db proxypass setprop mysite Target http://192.168.2.100
  db proxypass setprop mysite Description "My internal server"
  db proxypass setprop mysite HTTP on
  db proxypass setprop mysite HTTPS on
  signal-event nethserver-httpd-update

E' possibile restringere l'accesso ad una lista di IP: ::

  db proxypass setprop mysite ValidFrom 88.88.00.0/24,78.22.33.44
  signal-event nethserver-httpd-update

Configurazione manuale
======================

Se questa configurazione non è abbastanza, è sempre possibile creare 
manualmente il proprio proxy pass creando un nuovo file nella directory :file:`/etc/httpd/conf.d/`.

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
