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
This tool is **disabled** by default. You can simply enable it through the dedicated panel (Virtual machine manager).

The web application listen on port **8000** of your host machine.

To access the web interface
you must login with credentials that can be found on the dedicated panel.


**username:** *admin*

**password** (modifiable) *random-alphanumeric*.

Configuration
=============


WebVirtMgr
----------
After the rpm installation, to enable the service switch the radio button on dedicated panel to **Enable**.


WebVirtMgr-Console
------------------
After the rpm installation, to enable the shell remote service switch the radio button on dedicated panel to **Enable**.

Credentials
-----------
As you can see on the dedicated panel you can simply change password for login.

Start
-----
Now go on ``http://HOST_IP:8000/`` to see the web interface. Login and enjoy.

Warning
=======
To create bridge interface, create the interface **before** with standard method in NethServer dashboard and then select the interface on *network* tab in webvirtmgr interface.
