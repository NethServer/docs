==========
Proxy pass
==========

The :index:`proxy pass` feature is useful when you want to access internal sites
from the outside network.

Proxy pass configuration must be done via command line.
Before proceed, make sure ``nethserver-httpd`` package in installed: ::

  yum install -y nethserver-httpd

Scenario:

* |product| is the firewall of your LAN
* You have a domain http://mydomain.com
* You would like http://mydomain.com/mysite to forward to the internal server (internal IP: 192.168.2.00)

Commands for this example: ::

  db proxypass set mysite ProxyPass
  db proxypass setprop mysite Target http://192.168.2.100
  db proxypass setprop mysite Description "My internal server"
  db proxypass setprop mysite HTTP on
  db proxypass setprop mysite HTTPS on
  signal-event nethserver-httpd-update

You can also restrict the access to a list of IPs: ::

  db proxypass setprop mysite ValidFrom 88.88.00.0/24,78.22.33.44
  signal-event nethserver-httpd-update

Manual configuration
====================

If this is not enough, you can always manually create your own proxy pass 
by creating a new file inside :file:``/etc/httpd/conf.d/`` directory.

**Example**

Create :file:`/etc/httpd/conf.d/myproxypass.conf` file with this content: ::

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


Please refer to official Apache documentation for more information: http://httpd.apache.org/docs/2.2/mod/mod_proxy.html
