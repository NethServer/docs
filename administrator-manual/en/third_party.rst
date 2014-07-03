====================
Third-party software
====================

You can install any CentOS/RHEL certified :index:`third-party software` on |product|.

If the software is 32-bit only, you should install compatibility libraries before installing the software.
Relevant libraries should be:

* glibc
* glib
* libstdc++
* zlib

For example, to install this packages: ::

 yum install glibc.i686 libgcc.i686 glib2.i686 libstdc++.i686 zlib.i686

Installation
------------

If the software is an RPM package, please use :command:`yum` to install it: the system will take care to resolve all needed
dependencies.

In case a yum installation is not possible, the best target directory for additional software is under :file:`/opt`.
For example, given a software named *mysoftware*, install it on :file:`/opt/mysoftware`.

Backup
------

Directory containing relevant data should be included inside the backup by adding a line to :file:`/etc/backup-data.d/custom.include`.
See :ref:`backup_customization-section`.

Firewall
--------

If the software needs some open ports on the firewall, create a new service named ``fw_<softwarename>``.

For example, given the software *mysoftware* which needs port 3344 on LAN, use the following commands: ::

 config set fw_mysoftware service status enabled TCPPorts 8090,8443,5632,5432 access private
 signal-event firewall-adjust
 signal-event runlevel-adjust

Starting and stopping
---------------------

|product| uses the standard runlevel 5.

Software installed with yum should already be configured to start at boot on runlevel 5.
To check the configuration, execute the :command:`chkconfig` command. The command will display a list of services
with their own status.

To enable a service on boot: ::

  chkconfig mysoftware on

To disable a service on boot: ::
  
  chkconfig mysoftware off

