=============
Reverse proxy
=============

The :index:`reverse proxy` feature is useful when you want to access internal sites
from the outside network.

Typical scenario:

* |product| is the firewall of your LAN

* You have a domain http://mydomain.com

* You would like http://mydomain.com/mysite to forward to the internal server
  (internal IP: 192.168.2.100)

In this scenario create a new record under :guilabel:`Reverse proxy` page. Set
the :guilabel:`Name` of the item to ``mysite`` and the :guilabel:`Target URL` to
``http://192.168.2.100``.

If only encrypted connections are allowed, enable the :guilabel:`Require SSL
encrypted connection`.

Only clients from certain networks can be allowed to connect, by specifying  a
comma-separated list of CIDR networks under the :guilabel:`Access from CIDR
networks`  field.


Manual configuration
====================

If :guilabel:`Reverse proxy` page is not enough, you can always configure Apache
manually, by creating a new file inside :file:`/etc/httpd/conf.d/` directory.

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
