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

UI plugins
----------

The Modify action can be extended to display additional tabs, by adding a 
controller and the respective template under ``ModifyPlugin/`` directories.

See the `Samba User plugin`_ on NethServer 6.x as an example

.. _`Samba User plugin`: https://github.com/NethServer/nethserver-samba/blob/9012fbcd0cb3db60d8fb0ddfcd3db9e39a01956c/root/usr/share/nethesis/NethServer/Module/User/Plugin/Samba.php