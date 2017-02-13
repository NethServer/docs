.. index::
   single: registration
   single: Operation Center

.. _registration-section:

============
Registration
============

|product| offers the possibility to control the critical operating parameters using the :dfn:`Operation Center`,
which is accessible by login at |register_link|.
First, for each |product| installed, you must :index:`register` the machine to 
allow proper server identification during the communication with the web console.

Access the Server Manager (``https://server:980``), then click on :guilabel:`Software center` and follow the wizard:

* Please enter the reseller credentials used in the Operation Center |register_link|
* Select an existing server or choose the creation of new  one
* When creating make sure you enter a name that will help identify the server. You should also enter a description
* Associate an existing customer to the new server, or fill in the fields for the creation of new customer
* Confirm your entries to finish the registration process

At the end you will be able to :ref:`install additional software <package_manager-section>`.


The installation of additional software from the web interface is only allowed exclusively to the reseller credentials holders.
The use of :command:`yum` from the command line allows you to get around this limitation. 
Therefore, do not hand over the password :dfn:`root` end user.


:index:`Server key`
===================

The :dfn:`server key` allows to uniquely identify the server inside the Operation Center |register_link|.
Inside the details page of each server, there are two special buttons :guilabel:`Free key` and :guilabel:`Delete server`.

:index:`Delete server`
-----------------------

The :guilabel:`Delete server` button will remove the server from the Operation Center.
It's useful to remove old server or unused ones.

:index:`Free key`
-----------------

The :guilabel:`Free key` button allows another server to reuse the key during the registration process.
It's used in case you need to re-install the server for maintenance.

