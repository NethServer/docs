.. _access-section:

.. index::
   single: Server Manager
   single: web interface

============================
Accessing the Server Manager
============================

|product| can be configured using the :dfn:`Server Manager` web interface. 
You need a web browser like Mozilla Firefox or Google Chrome to access the web interface using the address (URL) 
``https://a.b.c.d:980`` or ``https://server_name:980`` where *a.b.c.d* and *server_name* respectively are the server IP address and name 
configured during installation.

If the web server module is installed, you can also access the web interface using this address ``https://server_name/server-manager``.

The Server Manager uses self-signed SSL certificates.
You should explicitly accept them the first time you access the server.
The connection is safe and encrypted.

Login
=====

The login page will gave you a trusted access to the web interface. Log in
as **root** and type the password chosen during |product| installation.

.. note:: 
    
    The *unattended* install procedure sets the root's password to the default
    ``Nethesis,1234``.

Change the current password
===========================

You can change the root's password from the web interface by going to the
:guilabel:`root@host.domain.com` label on the upper right corner of the screen
and clicking on :guilabel:`Profile`.

The login page allows selecting an alternative language among those already
installed on the system. After logging in, go to the
:ref:`software-center-section` page to install additional languages.

Logout
======

Terminate the current Server Manager session by going to the
:guilabel:`root@host.domain.com` label on the upper right corner of the screen
and by clicking on :guilabel:`Logout`.
