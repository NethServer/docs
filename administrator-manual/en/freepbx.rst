=======
FreePBX
=======

.. note::

  The configuration page of this module is available only in the old Server Manager.

:index:`FreePBX` is a web-based open source GUI (graphical user interface)
that controls and manages :index:`Asterisk` (PBX), an open source communication server
(https://www.freepbx.org/).

Installation
============

You can install FreePBX from the package manager of NethServer, the module
named "FreePBX".

All FreePBX configurations and data are saved inside configuration and data backup.

Web Access
==========

After installed, FreePBX will be accessible at ``https://ip_address/freepbx`` from
green interfaces.
You can also configure the access from the red interface under the "PBX Access"
page of the |product| Server Manager.

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
