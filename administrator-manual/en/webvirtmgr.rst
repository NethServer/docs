==========
WebVirtMgr
==========

This tool is used to manage :index:`virtual machine` through a simple web interface:

* Create and destroy new machines (:index:`KVM`)
* Create custom template of virtual machines
* Easy shell remote access
* Amazing UI

Configuration
=============

The web application listen on port **8000** of your host machine, for example: ``http://HOST_IP:8000/``.

The service is disabled by default. 

From the :guilabel:`Virtual machines` page you can:

* enable the virtual machines manager
* enable the virtual machines console access from web browser

To access the web interface you must login with credentials that can be found on the same page:

* *User:* admin
* *Password*: random alphanumeric (editable)


.. warning:: 
   Do not create network bridges using WebVirtManager interface.
   Just create the bridge inside :guilabel:`Network` page and use it under WebVirtManager.
