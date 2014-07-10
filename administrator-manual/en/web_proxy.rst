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


The proxy supports the following modes:

* Manual: all clients must be configured manually
* Authenticated users must enter a user name and password in order to navigate
* Transparent: all clients are automatically forced to use the proxy for HTTP connections
* Transparent SSL: all clients are automatically forced to use the proxy for HTTP and HTTPS connections


Client configuration
====================

The proxy is always listening on port 3128. When using manual or authenticated modes,
all clients must be explicitly configured to use the proxy.
The configuration panel is accessible from the browser settings.
In this case it is useful to enable :guilabel:`Block HTTP and HTTPS ports` option to avoid proxy bypass.

If the proxy is installed in transparent mode, all web traffic coming from clients is diverted
through the proxy. No configuration is required on individual clients.
   

SSL Proxy
---------

.. warning:: Decrypting HTTPS connection without user consent is illegal in many countries.

In transparent SSL mode, server is able to also filter encrypted HTTPS traffic.
The proxy establishes the SSL connection with remote sites, it checks the validity of certificates and it decrypts the traffic.
Finally, it generates a new certificate signed by the Certification Authority (CA) server itself.

The traffic between client and proxy is always encrypted, but you will need to install on every client (browser)
the CA certificate of the server.

The server certificate is located in :file:`/etc/pki/tls/certs/NSRV.crt`.
It is advisable to transfer the file using an SSH client (eg FileZilla).

