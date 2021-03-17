=============
Threat shield
=============

.. note::

  The configuration page of this module is available only in the new Server Manager.


The Threat shield blocks connections to and from malicious hosts, preventing attacks, service abuse, malware, and other cybercrime activities using IP blacklists. It also blocks DNS requests for malicious domains using DNS blacklists.
The package can be installed both on firewalls and on machines without a red interface, like mail servers
or PBXs.

Configuration
=============

:guilabel:`IP blacklist` and :guilabel:`DNS blacklist` can be enabled and configured on the corresponding pages in the menu.
Their configuration is almost identical.

First, set the :guilabel:`Download URL` for the blacklists.
After setting the URL, the administrator can choose which :index:`blacklist` categories should be enabled.
Each category can have a :guilabel:`Confidence` score between 0 and 10.
Categories with a higher confidence are less prone to false positives.

Enabled categories will be automatically updated at regular intervals.

The download URL must contain a valid GIT repository.
Administrators can choose a public repository or subscribe to a commercial service. If the machine has a Community or an Enterprise subscription, the access to the URL will be authenticated using system id and secret.

A popular free IP blacklist is `Firehol <https://github.com/firehol/blocklist-ipsets>`_. Experienced administrators can also `setup their own IP blacklist server <https://docs.nethserver.org/projects/nethserver-devel/en/latest/nethserver-blacklist.html#setup-a-blacklist-server>`_.

An example of DNS blacklist is available at `dns-community-blacklist <https://github.com/NethServer/dns-community-blacklist>`_.

.. warning:: If :ref:`proxy-section` is enabled, in any mode, :guilabel:`DNS blacklist` will not work for proxied hosts.

Whitelist
---------

In case of a false positive, an IP address or a CIDR subnet can be added to the local :guilabel:`Whitelist`.
If the firewall module is installed, the whitelist will also accept host and CIDR firewall objects.

Hosts should be added to the whitelist only for a limited period of time.
As a best practice, when a false positive is found, please report it to the blacklist maintainer.

Incident response
=================

The :guilabel:`Analysis` page displays most recent attacks and DNS requests which can be easily filtered by source, destination and other attributes.
Using the :guilabel:`Check IP address or domain` section, administrators can also check if a given IP or domain has been blacklisted by enabled categories.

For advanced log analysis with regular expressions support, use the :guilabel:`Logs` page.

Statistics
==========

The :guilabel:`Dashboard` page provides an overview on current status of IP and DNS blacklists and displays graphical information about blocked attacks.

IP blacklist dashboard provides:

* Today's total number of threats blocked
* Today's most blocked source hosts
* Today's most blocked destination hosts

DNS blacklist dashboard provides:

* Today's total number of threats blocked
* Today's total number of DNS requests
* Today's threats percentage
* Top clients performing most DNS requests
* Top blocked domains
* Top requested domains

Geo-blocking
============

Threat shield integrates limited support for geo-blocking.
This feature is configurable only from the command line.
Geo-blocking is disabled by default.

To enable geo-blocking execute: ::

  config setprop geoip status enabled
  signal-event nethserver-blacklist-save geoips

The event will download network addresses for all countries.
Each country is identified by its own `ISO code <https://en.wikipedia.org/wiki/List_of_ISO_3166_country_codes>`_ composed by 2 letters.
To list available countries, use: ::

  find /usr/share/nethserver-blacklist/geoips/ -type f -exec basename '{}' \; | cut -d '.' -f1

Choose which countries should be blocked and set the ``Categories`` accordingly. Example to block China and Russia: ::

  config setprop geoip Categories cn,ru
  signal-event nethserver-blacklist-save geoips

If an IP address has been classified inside the wrong country, it's possible to allow the traffic from/to the host by adding the IP
address to the whitelist. Example: ::

  config setprop geoip Whitelist 1.2.3.4
  signal-event nethserver-blacklist-save geoips

All blocked IPs will be logged inside :file:`/var/log/firewall.log`.
Example: ::

  Mar 16 09:05:24 fw kernel: Shorewall:blacklst:DROP:IN=ppp0 OUT= MAC= SRC=1.2.3.4 DST=5.6.7.8 LEN=60 TOS=0x00 PREC=0x00 TTL=52 ID=39155 DF PROTO=TCP SPT=39749 DPT=22 WINDOW=14600 RES=0x00 SYN URGP=0

Finally, to completely disable the GeoIP use: ::

  config setprop geoip status disabled
  signal-event nethserver-blacklist-save geoips

