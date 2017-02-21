=====================
Statistics (collectd)
=====================

:index:`Collectd` is a daemon which collects system performance :index:`statistics` periodically and stores them in RRD files.
Statistics will be displayed inside a web interface called

* Collectd Graph Panel (CGP), package *nethserver-cgp*

The web interface can be accessed from the :guilabel:`Graphs`.

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


Network latency
===============

The :index:`ping` plugin measure the network latency. At regular intervals, it sends a ping to the configured upstream DNS.
If the multi WAN module is configured, any enabled provider is also checked.

Additional hosts could be monitored (i.e. a web server) using a comma separated list of hosts inside the ``PingHosts`` property.

Example: ::

 config setprop collectd PingHosts www.google.com,www.nethserver.org
 signal-event nethserver-collectd-update

