=======
FreePBX
=======

The :index:`freepbx` is a web-based open source GUI (graphical user interface)
that controls and manages Asterisk (PBX), an open source communication server
(https://www.freepbx.org/).

Installation
============

You can install FreePBX from the package manager of NethServer, the package
is nethserver-freepbx.

Web Access
==========

After installed FreePBX will be accessible at https://ip_address/freepbx from
green interfaces.
You can also configure the access from the red interface under the "PBX Access"
page of the NethServer Web UI.

Backup
======

In order to backup FreePBX you have to install nethserver-backup-config and
nethserver-backup-data packages.

FwConsole
=========

The Fwconsole is a tool that allows the user to perform some FreePBX administrative tasks
(see https://wiki.freepbx.org/pages/viewpage.action?pageId=37912685).
In order to use it with NethServer you have to use it in conjunction with scl: ::

  /usr/bin/scl enable rh-php56 "/usr/sbin/fwconsole"


Advanced Documentation
======================

For further information you can read the FreePBX documentation at:
https://wiki.freepbx.org
