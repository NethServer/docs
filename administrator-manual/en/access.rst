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

The login page will gave you a trusted access to the web interface.
Use following credentials:

* :index:`Default user` name: **root**
* :index:`Default password`: **Nethesis,1234**

.. warning:: Change the root's password as soon as possible, by
             picking a secure one, composed of a random sequence of
             mixed-case letters, digits and symbols.
