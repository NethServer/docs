.. _proxy_pass-section:

=============
Reverse proxy
=============

The :index:`reverse proxy` feature is useful when you want to access internal sites
from the outside network.

Path and virtual host rules
===========================

A web client request can be forwarded to another web server transparently,
according to two types of matching rules:

* Requests matching an URL path, like ``http://mydomain.com/mysite``
* Requests matching a virtual host name, like ``http://my.secondary-domain.com``

We will see how to set up the two types of rule with a couple of examples.

The typical scenario for a path rule is the following:

* |product| is the firewall of your LAN

* You have a domain ``http://mydomain.com``

* You would like ``http://mydomain.com/mysite`` to forward to the internal server
  (internal IP: 192.168.2.100)

In this scenario create a new record under :guilabel:`Reverse proxy > Paths` page. Set
the :guilabel:`Name` of the item to ``mysite`` and the :guilabel:`Target URL` to
``http://192.168.2.100``.

If only encrypted connections are allowed, enable the :guilabel:`Require SSL
encrypted connection`.

Only clients from certain networks can be allowed to connect, by specifying  a
comma-separated list of CIDR networks under the :guilabel:`Access from CIDR
networks`  field.

Additional **virtual host names** can be forwarded to another web server with the
:guilabel:`Reverse proxy > Virtual hosts` page. In this case:

* |product| is the firewall of your LAN

* You have a domain ``http://my.secondary-domain.com``

* You would like ``http://my.secondary-domain.com`` to be forwarded to the internal web server
  ``192.168.2.101``, port 9000.

In this scenario set the :guilabel:`Name` of a new virtual host item to
``my.secondary-domain.com`` and the :guilabel:`Target URL` to
``http://192.168.2.101:9000``.

Refer also to :ref:`the UI description of Reverse Proxy <ProxyPassUi-section>`
for additional information about advanced features, like :guilabel:`Forward HTTP
"Host" header to target` and :guilabel`Accept invalid SSL certificate from
target`.

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


Please refer to official Apache documentation for more information: https://httpd.apache.org/docs/2.4/mod/mod_proxy.html
