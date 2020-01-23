.. _ftp-section:

===
FTP
===

.. note::

    The FTP server is part of the :ref:`Web server <web-server-section>`
    application inside the new Server Manager.

.. warning::

    The FTP protocol is insecure: password are sent in clear text.

The :index:`FTP` server allows to transfer files between client and server.

A FTP user can be :dfn:`virtual` or a system users.
Virtual users can access only the FTP server. This is the recommended configuration.
The web interface allows the configuration only of virtual users.

When accessing the FTP server, a user can explore the entire filesystem accordingly to its own privileges.
To avoid information disclosure, the FTP user can be configured in a jail using the :dfn:`chroot` option: the user
will not be able to exit the jail directory.

This behavior can be useful in case a shared folder is used as part of a simple web hosting. Insert the shared folder
path inside the custom field. For example, given a shared folder called *mywebsite*, fill the field with: ::

  /var/lib/nethserver/ibay/mywebsite

The FTP virtual user will be able to access only the specified directory.

System users
============

.. warning:: This configuration is highly discouraged

After enabling system users, all virtual users will be disabled.
All configuration must be done using the command line.

Enable system users: ::

  config setprop vsftpd UserType system
  signal-event nethserver-vsftpd-save

Given a user name *goofy*, first make sure the user has Remote shell access.
Then, enable the FTP access: ::

  db accounts setprop goofy FTPAccess enabled
  signal-event user-modify goofy
  signal-event nethserver-vsftpd-save

To disable an already enabled user: ::

  db accounts setprop goofy FTPAccess disabled
  signal-event nethserver-vsftpd-save

If not explicitly disabled, all system users are chrooted. To disable a chroot for a system user: ::

  db accounts setprop goofy FTPChroot disabled
  signal-event nethserver-vsftpd-save


