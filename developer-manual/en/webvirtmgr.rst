==========
WebVirtMgr
==========

This tool is used to manage virtual machine through a simple web interface.

* Create and destroy new machines
* Create custom template of virtual machines
* Easy shell remote access
* Amazing UI.

Overview
=============
This tool is **disabled** by default. You can simply enable it through the dedicated panel.
The web application listen on port **8000** of your host machine.

To access the web interface
you must login with credentials that can be found on the dedicated panel.


**username:** *admin*

**password** (modifiable) *random-alphanumeric*.

Configuration
=============
After rpm installation the environment is ready to start, if you enable the services (webvirtmgr and webvirtmgr-console) you can easy manage virtual machines.

WebVirtMgr
----------
Props
^^^^^
With ``config show webvirtmgr`` you can see all the properties of webvirtmgr and with ``config setprop webvirtmgr <name_prop> <prop_value>`` you can modify the props.

In particularly you can change the port where web interface listens with ``config setprop webvirtmgr TCPPort <num_port>``.

Database
^^^^^^^^
By default there is a local socket connection named ``localhost``, it's a simply record in SQLite database, the db name is ``webvirtmgr.sqlite3`` that can be found in ``/usr/lib/python2.6/site-packages/webvirtmgr/``.

Upstart
^^^^^^^
The rpm installation enable the start of service on boot. There is a file under ``/etc/init/webvirtmgr.conf`` with configuration options.

WebVirtMgr Console
------------------
Props
^^^^^
With ``config show webvirtmgr-console`` you can see all the properties about webvirtmgr-console. Like above, to change props, simply run ``config setprop webvirtmgr-console <name_prop> <prop_value>``.


Config file
^^^^^^^^^^^
Under ``/etc/sysconfig/webvirtmgr-console`` there is the config file of service that enable remote shell.

Service
^^^^^^^
Under ``/etc/init.d/webvirtmgr-console`` there is the configurations options of remote shell console.
