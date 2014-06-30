====================
Access to |product|
====================

|product| can be configured using the :dfn:`Server Manager` :index:`web interface`. 
You need a web browser like Mozilla Firefox or Google Chrome to access the web interface using the address (URL) 
``https://a.b.c.d:980`` or ``https://server_name:980`` where *a.b.c.d* and *server_name* respectively are the server IP address and name 
configured during installation.

If the web server module is installed, you can also access the web interface using this address ``https://server_name/server-manager``.

The :index:`Server Manager` uses self-signed SSL certificates.
You should explicitly accept them the first time you access the server.
The connection is safe and encrypted.

Login
=====

The login page will gave you a trusted access to the web interface.
Use following credentials:

* User name: **root**
* Password: **root_password** (chosen during installation process)

If the directory module is installed, and the admin user has been enabled, you can use it to access
the web interface with same privileges as root user. See :ref:`admin-user`.
