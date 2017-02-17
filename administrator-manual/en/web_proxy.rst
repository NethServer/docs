.. _proxy-section:

=========
Web proxy
=========


The :index:`web proxy` is a server that sits between the LAN PCs and Internet sites.
Clients make requests to the proxy which communicates with external sites, 
then send the response back to the client.

The advantages of a web proxy are:

* ability to filter content
* reduce bandwidth usage by caching the pages you visit


The proxy can be enabled only on green and blue zones.
Supported modes are:

* Manual: all clients must be configured manually
* Authenticated users must enter a user name and password in order to navigate
* Transparent: all clients are automatically forced to use the proxy for HTTP connections
* Transparent SSL: all clients are automatically forced to use the proxy for HTTP and HTTPS connections

.. note:: If you plan to use authenticate mode, please make sure to configure an Account provider.

Client configuration
====================

The proxy is always listening on port **3128**. When using manual or authenticated modes,
all clients must be explicitly configured to use the proxy.
The configuration panel is accessible from the browser settings.
By the way, most clients will be automatically configured using WPAD protocol.
In this case it is useful to enable :guilabel:`Block HTTP and HTTPS ports` option to avoid proxy bypass.

If the proxy is installed in transparent mode, all web traffic coming from clients is diverted
through the proxy. No configuration is required on individual clients.

Certificate file is saved inside :file:`/etc/pki/tls/certs/NSRV.crt` file, it can be downloaded from client
at ``http://<ip_server>/proxy.crt`` address.

.. note:: To make the WPAD file accessible from guest network, add the address of blue network
   inside the :guilabel:`Allow hosts` field for httpd service from the :guilabel:`Network services` page.
 
.. _proxy_ssl-section:

SSL Proxy
=========

.. warning:: Decrypting HTTPS connection without user consent is illegal in many countries.

In transparent SSL mode, the server is able to also analyze HTTPS traffic.
The proxy implements the "peek and splice" behavior: it establishes the SSL connection with remote sites and
checks the validity of certificates without decrypting the traffic.
Then the server can filter requested URLs using the web filter and return back the response to the client.

.. note:: To prevent any malfunction when proxy is used in SSL Transparent Mode :

   * Use the same dns server for NethServer and for the clients
   * Avoid multiple dns for the clients, the best practice is setting only NethServer's local ip as dns for the clients
   * Avoid Google's dns (8.8.8.8., 8.8.4.4...) because there are some reported incompatibilities, you can use other free services as OpenDNS (https://www.opendns.com/) 
   * In case there are Domain Controllers,the best way is to set the ip address of the domain controller as dns for NethServer and for the clients

Bypass
======

In some cases it may be necessary to ensure that traffic originating
from specific IP or destined to some sites it's not routed through the HTTP/HTTPS proxy.

The proxy allows you to create:

* bypass by source, configurable from :guilabel:`Hosts without proxy` section
* bypass by destination, configurable from :guilabel:`Sites without proxy` section

Bypass rules are also configured inside the WPAD file.

Report
======

Install ``nethserver-lightsquid`` package to generate :index:`web navigation reports`.

LightSquid is a lite and fast log analyzer for Squid proxy, it parses logs and generates new HTML report every day, summarizing browsing habits of the proxy's users.
Link to web interface can be found at the :guilabel:`Applications` tab inside the :guilabel:`Dashboard`.

Cache
=====

Under tab :guilabel:`Cache` there is a form to configure cache parameters:

* The cache can be enabled or disabled (*disabled* by default)
* **Disk cache size**: maximum value of squid cache on disk (in MB)
* **Min object size**: can be left at 0 to cache everything, but may be raised if small objects are not desired in the cache (in kB)
* **Max object size**: objects larger than this setting will not be saved on disk. If speed is more desirable than saving bandwidth, this should be set to a low value (in kB)

The button :guilabel:`Empty cache` also works if squid is disabled, it might be useful to clear space on disk.

Sites without cache
-------------------

Sometime the proxy can't correctly handle some bad crafted sites.
To exclude one or more domain from the cache, use the ``NoCache`` property.

Example: ::

  config setprop squid NoCache www.nethserver.org,www.google.com
  signal-event nethserver-squid-save

Safe ports
==========

Safe ports are a list of ports accessible using the proxy.
If a port is not inside the safe port list, the proxy will refuse to contact the server.
For example, given a HTTP service running on port 1234, the server can't be accessed using the proxy.

The ``SafePorts`` property is a comma-separated list of ports.
Listed ports will be added to the default list of safe ports.

Eg. Access extra ports 446 and 1234: ::

  config setprop squid SafePorts 446,1234
  signal-event nethserver-squid-save

