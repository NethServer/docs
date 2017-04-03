nethserver-virtualhosts
=======================

Database
--------

A new ``vhost`` database is defined by this module. It contains records of type 
``vhost``, similar to: ::

    vh1=vhost
        Access=private
        Description=description_text
        ForceSslStatus=enabled
        FtpPassword=ftp_password_value
        FtpStatus=enabled
        PasswordStatus=enabled
        PasswordValue=http_password_value
        ServerNames=www.nethserver.org,www.example.com
        SslCertificate=/etc/pki/tls/certs/NSRV.crt
        status=enabled

The database contains a special ``default`` record which represents the defaul virtual host: ::

  default=vhost
    Description=Default virtual host
    FtpPassword=
    FtpStatus=enabled

This virtual host is always enabled and can't be deleted.
If FTP access is enabled, the user will be chrooted inside ``/var/www/html`` directory.

NethServer 6 upgrade
--------------------

Shared folders from NethServer 6 with property ``HttpStatus`` set to ``enabled`` can
be migrated to virtual hosts using the ``vhost-migrate-ibay`` event: ::

    signal-event vhost-migrate-ibay <ibay-name>

If the original ibay was availble to any virtual hosts (`HttpVirtualHost` = ``__ANY__``),
the ibay will be migrated inside the ``default`` virtual host.
Otherwise a new virtual host record will be created.

The migration process is also available from the web interface.

UI plugins
----------

The Modify action can be extended to display additional tabs, by adding a 
controller and the respective template under ``ModifyPlugin/`` directories.

See the `Samba User plugin`_ on NethServer 6.x as an example

.. _`Samba User plugin`: https://github.com/NethServer/nethserver-samba/blob/9012fbcd0cb3db60d8fb0ddfcd3db9e39a01956c/root/usr/share/nethesis/NethServer/Module/User/Plugin/Samba.php
