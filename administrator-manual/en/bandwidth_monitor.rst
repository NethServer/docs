.. _ntopng-section:

=================
Bandwidth monitor
=================

.. note::

  The configuration page of this module is available only in the old Server Manager
  and will not be ported to the new one.

ntopng
======

ntopng is a powerful tool that allows you to analyze real-time
network traffic. It allows you to evaluate the bandwidth used by
individual hosts and to identify the most commonly used network protocols.

Enable ntopng
    Enabling ntopng, all traffic passing through the network interfaces
    will be analyzed. It can cause a slowdown of the network and an
    increased in system load.
Port
    The port where to view the ntopng web interface.
Password for 'admin' user
    Admin user password. This password is not related to
    the |product| admin password.
Interfaces
    Interfaces on which ntopng will listens to.
