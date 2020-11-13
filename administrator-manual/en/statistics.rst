=====================
Statistics (collectd)
=====================

:index:`Collectd` is a daemon which collects system performance :index:`statistics` periodically and stores them in RRD files.
Statistics will be displayed inside a web interface called Collectd Graph Panel (CGP).

After installation, the system will gather following statistics:

* CPU usage
* system load
* number of processes
* RAM memory usage
* virtual memory (swap) usage
* system uptime
* disk space usage
* disk read and write operations
* network interfaces 
* :index:`network latency`

For each check, the web interface will display a graph containing last collected value and also minimum, maximum and average values.

CGP is accessible on a random URL generated on first install, something like ``https://myserver.nethserver.org/02bf3f8364beea0d5f23044bf14d31d93f63e98d``.
The URL is available from the Server Manager inside the :guilabel:`Applications` page. Click the :guilabel:`Open` button
of :guilabel:`Collectd Charts` application.

From the old Server Manager, the web interface can be accessed using the :guilabel:`Graphs` section.

Network latency
===============

The :index:`ping` plugin measure the network latency. At regular intervals, it sends a ping to the configured upstream DNS.
If the multi WAN module is configured, any enabled provider is also checked.

Additional hosts could be monitored (i.e. a web server) using a comma separated list of hosts inside the ``PingHosts`` property.

Example: ::

 config setprop collectd PingHosts www.google.com,www.nethserver.org
 signal-event nethserver-collectd-update

.. _cgp_restict_access-section:

Restrict access
===============

As default CGP is accessible also from public networks.
To restrict the access only from local and trusted networks use: ::

  config setprop cgp PublicAccess disabled
  signal-event nethserver-cgp-update

