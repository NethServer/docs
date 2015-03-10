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
   
.. _proxy_ssl-section:

SSL Proxy
=========

.. warning:: Decrypting HTTPS connection without user consent is illegal in many countries.

In transparent SSL mode, server is able to also filter encrypted HTTPS traffic.
The proxy establishes the SSL connection with remote sites, it checks the validity of certificates and it decrypts the traffic.
Finally, it generates a new certificate signed by the Certification Authority (CA) server itself.

The traffic between client and proxy is always encrypted, but you will need to install on every client (browser)
the CA certificate of the server.

The server certificate is located in :file:`/etc/pki/tls/certs/NSRV.crt`.
It is advisable to transfer the file using an SSH client (eg FileZilla).

Bypass
======

In some cases it may be necessary to ensure that traffic originating
from specific IP or destined to some sites it's not routed through the HTTP/HTTPS proxy.

The proxy allows you to create:

* bypass by source, configurable from :guilabel:`Hosts without proxy` section
* bypass by destination, configurable from :guilabel:`Sites without proxy` section

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