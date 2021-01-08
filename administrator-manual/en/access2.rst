.. _access-section:

============================
Accessing the Server Manager
============================

|product| can be configured using the :dfn:`Server Manager` web interface. 
You need a web browser like Mozilla Firefox or Google Chrome to access the web interface using the address (URL) 
``https://a.b.c.d:9090`` or ``https://server_name:9090`` where *a.b.c.d* and *server_name* respectively are the server IP address and name 
configured during installation.

Since the Server Manager uses a self-signed SSL certificate as default, the first time you access the server
you should explicitly accept the certificate.
Despite the warning, the connection is safe and encrypted, but you are advised to configure a valid certificate, later.

Login
=====

The login page will give you a trusted access to the web interface. Log in
as **root** and type the password chosen during |product| installation.

.. note:: 
    
    The *unattended* install procedure sets the root password to the default
    ``Nethesis,1234``.


Besides root, all users with a :ref:`delegated<delegation-section>` panel can access the Server Manager.

The web interface language is automatically chosen depending on your browser configuration.
If you wish to change the language, go to your user name
on the upper right corner of the screen and select :guilabel:`Display Language`.


Login to remote servers
-----------------------

The login page allows access the local machine (default) or a remote one.
To access a remote server, first make sure the server is accessible using SSH.
Then click on :guilabel:`Other options` and enter the host name (or IP address) of 
the remote server inside the :guilabel:`Connect to` field.

The Server Manager will try to access the remote machine using SSH on port 22.
If the remote server use a different port, you can specify it with the ``host:port`` syntax
(eg. ``a.b.c.d:222``).

Hints
=====

After login, the system is ready to be used but you're advised to review the list of
hints which will guide you to correctly configure the machine.
Hints are shown as yellow markers with a number over the left menu items.

As best practice you should at least:

* change the default root password
* set the correct date and time

Change the current password
===========================

Users can change their own password using :ref:`user_settings-section`.

If :guilabel:`Shell Policy` options is not enabled,
users without shell access can still use the old Server Manager to change
their own password. See :ref:`access_legacy-section`.

Logout
======

Terminate the current Server Manager session by going to your user name
on the upper right corner of the screen and by clicking on :guilabel:`Log Out`.


