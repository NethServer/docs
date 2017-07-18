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

Authenticated mode
==================

Before enabling the web proxy in authenticated mode,
please make sure to configure a local or remote account provider.

When Samba Active Directory is installed, or the server is joined to a remote
Active Directory, Windows machines can use integrated authentication with Kerberos.
All Windows clients **must** access the proxy server using the FQDN.

All other clients can use basic authentication mechanism.

.. note:: NTLM authentications is deprecated and it's not supported.

Client configuration
====================

The proxy is always listening on port **3128**. When using manual or authenticated modes,
all clients must be explicitly configured to use the proxy.
The configuration panel is accessible from the browser settings.
By the way, most clients will be automatically configured using WPAD protocol.
In this case it is useful to enable :guilabel:`Block HTTP and HTTPS ports` option to avoid proxy bypass.

If the proxy is installed in transparent mode, all web traffic coming from clients is diverted
through the proxy. No configuration is required on individual clients.

.. note:: To make the WPAD file accessible from guest network, add the address of blue network
   inside the :guilabel:`Allow hosts` field for httpd service from the :guilabel:`Network services` page.
 
.. _proxy_ssl-section:

SSL Proxy
=========

In transparent SSL mode, the proxy implements the so-called "peek and splice" behavior: 
it establishes the SSL connection with remote sites and
checks the validity of certificates without decrypting the traffic.
Then the server can filter requested URLs using the web filter and return back the response to the client.

.. note:: Is not necessary to install any certificate into the clients, 
   just enabling the SSL proxy is enough.

Bypass
======

In some cases it may be necessary to ensure that traffic originating
from specific IP or destined to some sites it's not routed through the HTTP/HTTPS proxy.

The proxy allows you to create:

* bypass by domains
* bypass by source
* bypass by destination

Bypass by domains
-----------------

Bypass by domains can be configured from :guilabel:`Domains without proxy` section.
All domains listed inside this page can be directly accessed from LAN clients.
No antivirus or content filtering is applied to these domains.

Every domain listed will be expanded also for its own sub-domains.
For example, adding *nethserver.org* will bypass also *www.nethserver.org*, *mirror.nethserver.org*, etc.

.. note:: All LAN clients must use the server itself as DNS, either directly or as a forwarder.

Bypass by source and destinations
---------------------------------

A source bypass allows direct access to any HTTP/HTTPS sites from 
selected hosts, host groups, IP ranges and network CIDR.
Source bypasses are configurable from :guilabel:`Hosts without proxy` section.

A destination bypass allows direct access from any LAN clients to HTTP/HTTPS sites hosted on specific hosts, 
host groups or network CIDR.
Destination bypasses are configurable from :guilabel:`Sites without proxy` section.

These bypass rules are also configured inside the WPAD file.

Report
======

Install ``nethserver-lightsquid`` package to generate :index:`web proxy stats`.

LightSquid is a lite and fast log analyzer for Squid proxy, it parses logs and generates new HTML report every day, summarizing browsing habits of the proxy's users.
Lightsquid web interface can be found at the :guilabel:`Applications` tab inside the :guilabel:`Dashboard`.

Cache
=====

Under tab :guilabel:`Cache` there is a form to configure cache parameters:

* The cache can be enabled or disabled (*disabled* by default)
* **Disk cache size**: maximum value of squid cache on disk (in MB)
* **Min object size**: can be left at 0 to cache everything, but may be raised if small objects are not desired in the cache (in kB)
* **Max object size**: objects larger than this setting will not be saved on disk. If speed is more desirable than saving bandwidth, this should be set to a low value (in kB)

The button :guilabel:`Empty cache` also works if squid is disabled, it might be useful to free space on disk.

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

