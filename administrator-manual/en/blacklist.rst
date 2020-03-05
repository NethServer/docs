=============
Threat shield
=============

.. note::

  The configuration page of this module is available only in the new Server Manager.


The threat shield blocks malicious hosts preventing attacks, service abuse, malware and other cybercrime activities.
The package can be installed both on firewalls and on machines without a red interface, like mail servers
or PBXs.

Configuration
=============

First, access the threat shield web interface to set the download URL for the blacklists.

After setting the URL, the administrator can choose what :index:`blacklist` categories should be enabled.
Each category can have a :guilabel:`Confidence` score between 0 and 10.
Categories with an higher confidence are less prone to false positives.

Enabled categories will be automatically updated at regular intervals.

The download URL must contain a valid GIT repository.
Administrators can choose a public repository, like `Firehol ipsets one <https://github.com/firehol/blocklist-ipsets>`_,
or subscribe to a commercial service. If the machine has a Community or an Enterprise subscription, the access to the URL
will be authenticated using system id and secret.

Experienced administrators can also `setup their own blacklist server <https://docs.nethserver.org/projects/nethserver-devel/en/latest/nethserver-blacklist.html#setup-a-blacklist-server>`_.

Whitelist
---------

In case of a false positive, a host or a CIDR can be added to the local :guilabel:`Whitelist`.
If the firewall module is installed, the whitelist will also accept host and CIDR firewall objects.

Hosts should be added to the whitelist only for a limited period of time.
As a best pratice, when a false positive is found, please report it to the blacklist maintainer.

Incident response
=================

The :guilabel:`Analysis` page displays most recent attacks which can be filtered by source, destination, protocol and port.
Using the :guilabel:`Check IP address` section, administrators can also check if a given IP has been blacklisted by an enabled category.

For advanced log analysis with regular expressions support, use the :guilabel:`Logs` page.
