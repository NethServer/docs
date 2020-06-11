.. _ntopng-section:

=================
Bandwidth monitor
=================

**Bandwidth monitor** module allows you to analyze real-time network traffic using 
`ntopng <https://www.ntop.org/products/traffic-analysis/ntop/>`_ under the hood.
**ntopng** is a powerful tool that evaluates the bandwidth used by
individual hosts and identifies the most commonly used network protocols.

Settings
========

In :guilabel:`Settings` page you can manage **Bandwidth monitor** configuration through the following controls:

* :guilabel:`Enable bandwidth monitor`: if enabled, all traffic passing through selected network interfaces
  will be analyzed. Depending on the capabilities of your server, it may cause a slowdown of 
  the network and an increase in system load.
* :guilabel:`Interfaces`: the network interfaces **ntopng** will listen to.
* :guilabel:`Web interface port`: the TCP port where **ntopng** web interface will be available (default: **3000**).
* :guilabel:`Enable authentication`: if enabled, **ntopng** web interface will require login credentials.
  Username is ``admin`` and default password is ``admin``.

When **Bandwidth monitor** is enabled, **ntopng** web interface is available at: ``http://<SERVER_NAME>:<WEB_INTERFACE_PORT>``
