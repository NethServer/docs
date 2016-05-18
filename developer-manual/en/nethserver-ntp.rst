==============
nethserver-ntp
==============

Manage server date and time, ntp server for lan clients.

How it works
============

When the time and date are modified, some services must be restarted. Each package must subscribe ``service2adjust`` interface. Note that there's no need to restart rsyslog on date and time changing. Rsyslog daemon is smart enough to read new time setting on the fly.

Date and time can be set *manually* or automatically via a *ntp server*.

The current time zone is accessible from the configuration database, but the value is read and written using systemd commands.

Events
------

* ``nethserver-ntp-update``, standard event triggered on package installation/update.
* ``nethserver-ntp-save``, standard event triggered on UI module ``SAVE`` action

Actions
-------

* ``nethserver-ntp-localtime``, create a lint to the zoneinfo file from ``/usr/share/zoneinfo`` to ``/etc/localtime`` according to ``TimeZone`` key in _configuration_ database.
* ``nethserver-ntp-clock-adjust``, adjust the system date and hardware clock when NTP is disabled. Requires the *event name* and *timestamp* arguments. When NTP is enabled, restarts the ntp daemon.

Database
--------

Example: ::

 chronyd=service
    NTPServer=pool.ntp.org
    access=private

Daemon status
-------------

Run following command command: ::

  chronyc sourcestats

Sample output: ::

  210 Number of sources = 1
  Name/IP Address            NP  NR  Span  Frequency  Freq Skew  Offset  Std Dev
  ==============================================================================
  yourntp.server.com    41  20   43m     +0.001      0.172    +58ns   227us

