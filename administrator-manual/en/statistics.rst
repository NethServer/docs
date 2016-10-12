=====================
Statistics (collectd)
=====================

:index:`Collectd` is a daemon which collects system performance :index:`statistics` periodically and stores them in RRD files.
Statistics will be displayed inside a web interface, named

* Collectd Graph Panel (CGP), package *nethserver-cgp*

The web interfaces will create a random URL accessible from the :guilabel:`Applications` tab inside the :guilabel:`Dashboard`.
It's possible to share the random URL to let non-authenticated users view graphs. Access is allowed only from the
zones and IP addresses of the http-admin service (see Network services).

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

For each metric, the web interface will display a graph containing the last collected value and also minimum, maximum and average values.


Network latency
===============

The :index:`ping` plugin measure network latency. At regular intervals, it sends an ICMP ping to the configured upstream DNS.
If the multi WAN module is configured, any enabled provider is also checked.

Additional hosts could be monitored (i.e. a web server) using a comma separated list of hosts inside the ``PingHosts`` property.

Example: ::

 config setprop collectd PingHosts www.google.com,www.nethserver.org
 signal-event nethserver-collectd-update

