.. index::
   single: registration
   single: Operation Center

.. _registration-section:

============
Registration
============

|product| offers the possibility to control the critical operating parameters using the :dfn:`Operation Center`,
which is accessible at |register_link|.
First, each |product| must be registered to access software repositories, support services and enable monitoring tools:

1. Open :guilabel:`Registration` page from the old Server Manager (``https://<server_name>:980``) or from the new one (``https://<server_name>:9090``)
2. Login to |register_link|
3. Click on :guilabel:`Create new server` from the Server Manager,
   or access the :guilabel:`Server` page inside |register_link|, click the :guilabel:`+` symbol under the :guilabel:`New server` section
4. Choose a name for the server and select an existing customer
5. Copy and paste the code inside the :guilabel:`authentication token` field
6. Click on :guilabel:`Register now` button

At the end you will be able to :ref:`install additional software <package_manager-section>`.

.. hint:: Run :ref:`software update <software-updates-section>` immediately after registration to get new features and security fixes!

The installation of additional software from the web interface is only allowed exclusively to the reseller credentials holders.
The use of :command:`yum` from the command line allows you to get around this limitation. 
Therefore, do not hand over the password :dfn:`root` end user.

Operation Center
================
￼
The :dfn:`system id` uniquely identify the server and it is reported inside the details page of each server.
There are also two special buttons :guilabel:`Free key` and :guilabel:`Delete server`.		

The :guilabel:`Free key` button allows another server to reuse the key during the registration process.
It's used in case you need to re-install the server for maintenance.

The :guilabel:`Delete server` button will remove the server from the Operation Center.
It's useful to remove old server or unused ones.

Recover an authentication token
-------------------------------

Access the :guilabel:`Server` page, select the server, then click on the :guilabel:`Show token` button on the right,
just below the system id.￼
￼
