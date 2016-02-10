====
NTPd
====

Manage server date and time, ntp server for lan clients.

How it works
============

When the time and date are modified, some services must be restarted. Each package must subscribe ``service2adjust`` interface. Note that there's no need to restart rsyslog on date and time changing. Rsyslog daemon is smart enough to read new time setting on the fly.

Date and time can be set *manually* or automatically via a *ntp server*.

Note that

* ``ntpdate`` command is deprecated (see #934)
* ``ntp`` is executed with ``-g`` flag, to support large time steps - see ntpd manual page.

Events
------

* ``nethserver-ntp-update``, standard event triggered on package installation/update.
* ``nethserver-ntp-save``, standard event triggered on UI module ``SAVE`` action

Actions
-------

* ``nethserver-ntp-localtime``, copy the zoneinfo file from ``/usr/share/zoneinfo`` to ``/etc/localtime`` according to ``TimeZone`` key in _configuration_ database.
* ``nethserver-ntp-clock-adjust``, adjust the system date and hardware clock when NTP is disabled. Requires the *event name* and *timestamp* arguments. When NTP is enabled, restarts the ntp daemon.

Database
--------

Example: ::

 ntpd=service
    NTPServer=pool.ntp.org
    SyncToHWClockSupported=yes
    access=private

Daemon status
-------------

Run ``ntpdc -p`` command: ::

    # ntpdc -p        
     remote           local      st poll reach  delay   offset    disp
    =======================================================================
    *192.168.9.7     192.168.9.3      3   64   17 0.00143 -0.026033 0.12788
