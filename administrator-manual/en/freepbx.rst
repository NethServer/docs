=======
FreePBX
=======

:index:`FreePBX` is a web-based open source GUI (graphical user interface)
that controls and manages :index:`Asterisk` (PBX), an open source communication server
(https://www.freepbx.org/).

Installation
============

You can install FreePBX from the package manager of |product|, the module
named "FreePBX".

All FreePBX configurations and data are saved inside configuration and data backup.

Configuration
=============

External access
---------------

As default, IAX and SIPs ports are open only for green interfaces.
To open access from remote networks, just enable the :guilabel:`Allow external IAX access`
and :guilabel:`Allow external SIP TLS access` options.

Web interface access
--------------------

After installed, FreePBX will be accessible at ``https://ip_address/freepbx`` from
green interfaces only.
You can allow access from extra networks by clicking on :guilabel:`Create new access` button
under the *Settings* page of FreePBX application.

FwConsole
=========

The ``fwconsole`` is a tool that allows the user to perform some FreePBX administrative tasks
(see `FreePBX wiki <https://wiki.freepbx.org/pages/viewpage.action?pageId=37912685>`_).
In order to use it with |product| you have to use it in conjunction with scl: ::

  /usr/bin/scl enable rh-php56 "/usr/sbin/fwconsole"


Advanced Documentation
======================

For further information you can read the FreePBX documentation at:
https://wiki.freepbx.org
