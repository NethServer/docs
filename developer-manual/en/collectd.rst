========
Collectd 
========

This package automatically configure basic :index:`collectd` plugins and it's part of ``nethserver-statistics`` yum package group.

This package will install a base collectd configuration. Default enabled modules:

* cpu
* load
* processes
* memory
* swap
* uptime
* df
* disk
* interface
* network
* rrdtool
* ping

No configuration is needed, collectd is enabled by default when installed.

Ping plugin
===========

The ping plugin sends an ICMP packet every 5 seconds to the configured upstream DNS measure network latency.
If the multi wan module is configured, every checkip is also pinged.

Additional hosts could be monitored (i.e. a webserver) using a comma separeted list of hosts ``PingHosts`` property: ::

 config setprop collectd PingHosts www.nethesis.it,www.nethserver.org
 signal-event nethserver-collectd-update

Web interfaces
==============

To view graphs of collected data, there are two different web UI: nethserver-collectd-web and nethserver-cgp.
When installed, both interfaces create a random URL for accessing the interface.


Cleanup
=======

Every day a cronjob (:file:`/etc/cron.daily/collectd_cleanup`) takes care to clean up all rdd files not updated
during the last day.


Interesting plugins
===================

The following can be manually installed:

* collectd-nut
* collectd-sensors


Database
========

Configuration is saved inside the ``configuration`` database. Example: ::

 collectd=service
    PingHosts=
    status=enabled

