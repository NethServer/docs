==========================
Log retention and rotation
==========================

By default logs are rotated weekly and kept for 4 weeks.
Some packages come with different defaults, but the majority do not specify a custom rotate value.

Logrotate db property:

* ``Rotate``: rotation frequency, can be  ``daily``, ``weekly``, ``monthly``. Default is ``weekly``
* ``Times``: rotate log files ``Times`` number of times (days, weeks or months) before being removes, default is 4
* ``Compression``: can be ``enabled`` or ``disabled``. Defaults is ``disabled``

Keep logs for 6 months, rotate once a week: ::

  config setprop logrotate Rotate weekly
  config setprop logrotate Times 24
  signal-event logrotate-update
