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

.. note:: There is no need to install any certificate into the clients,
   just enabling the SSL proxy is enough.
.. note:: If the web proxy is enabled on the blue network this allows you to reach the green devices via the http or https protocols.
   If you want to avoid this behavior, simply create a bypass by destination by entering the CIDR of the green network as explained below.

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

.. _squid_rules-section:

Priority and divert rules
=========================

Firewall rules for routing traffic to a specific provider, or decrease/increase priority, are applied only to network traffic which traverse the gateway.
These rules don't apply if the traffic goes through the proxy because the traffic is generated from the gateway itself.

In a scenario where the web proxy is enabled in transparent mode and the firewall 
contains a rule to lower the priority for a given host, the rule applies only to non-HTTP services like SSH.

The :guilabel:`Rules` tab allows the creation of priority and divert rules also for the traffic
intercepted by the proxy.

The web interface allow the creation of rules for HTTP/S traffic to:

- raise the priority of an host or network
- lower the priority of an host or network
- divert the source to a specific provider with automatic fail over if the provider fails
- force the source to a specific provider without automatic fail over

.. _web_content_filter-section:

Content filter
==============

The :index:`content filter` analyzes all web traffic and blocks selected websites or sites containing viruses.
Forbidden sites are selected from a list of categories, which in turn must be downloaded from external sources and stored on the system.

The system allows to create an infinite number of profiles.
A profile is composed by three parts:

* **Who**: the client associated with the profile.
  Can be a user, a group of users, a host, a group of hosts, a zone or an interface role (like green, blue, etc).

* **What**: which sites can be browsed by the profiled client.
  It's a filter created inside the :guilabel:`Filters` section.

* **When**: the filter can always be enabled or valid only during certain period of times.
  Time frames can be created inside the :guilabel:`Times` section.


This is the recommended order for content filter configuration:

1. Select a list of categories from :guilabel:`Blacklists` page and start the download
2. Create one or more time conditions (optional)
3. Create custom categories (optional)
4. Create a new filter or modify the default one
5. Create a new profile associated to a user or host, then select
   a filter and a time frame (if enabled)

If no profile matches, the system provides a default profile that is applied to all clients.

Filters
-------

A filter can:

* block access to categories of sites
* block access to sites accessed using IP address (recommended)
* filter URLs with regular expressions
* block files with specific extensions
* enable global blacklist and whitelist

A filter can operate in two different modes:

* Allow all: allow access to all sites, except those explicitly blocked
* Block all: blocks access to all sites, except those explicitly permitted

.. note:: The category list will be displayed only after the download of list selected from :guilabel:`Blacklist` page.

Report
======

Install ``nethserver-lightsquid`` package to generate :index:`web proxy stats`.

LightSquid is a lite and fast log analyzer for Squid proxy, it parses logs and generates new HTML report every day, summarizing browsing habits of the proxy's users.
Lightsquid web interface can be found at the :menuselection:`Applications` tab inside the :guilabel:`Dashboard`.

Cleanup old reports
-------------------

LightSquid reports are saved as directories of text files inside ``/var/lightsquid/``.
Since all reports are kept forever, the size of the directory can greatly grow during the years.

To cleanup all reports older than 1 year, execute the following:
::

  find /var/lightsquid/  -maxdepth 1 -mindepth 1 -type d -name '????????' -mtime +360 -exec rm -rf {} \;

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


Logs
====

Squid logs are kept for 5 weeks in compressed format, to control disk space usage.
Web proxy logs are verbose to help troubleshoot problems. Web browsing activities are logged in aggregate and readable format by Lightsquid.

In environments where logs need to be preserved for more than 5 weeks, you could manually edit the logrotate configuration :file:`/etc/logrotate.d/squid`. Finally, remember to add :file:`/etc/logrotate.d/squid` to the configuration backup using the custom include. ::

  echo '/etc/logrotate.d/squid' >> /etc/backup-config.d/custom.include
