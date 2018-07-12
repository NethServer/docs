nethserver-httpd
================

NethServer tries to remain compliant with the upstream configuration for ``httpd``.

In Apache 2.4 every global option is inherit by all virtual hosts,
except for the *Rewrite* directives.

In a clean installation the only defined virtual host is the one on port 443.
When nethserver-httpd-virtualhosts is installed, the package adds a new default virtual host.
This virtual host includes the ``/etc/httpd/conf.d/default-virtualhost.inc`` file
to mimic the upstream behavior.

See also "Certificate management" and "Virtualhosts" section for further information.

Templates
---------

Available templates under ``/etc/e-smith/templates/`` directory:

* ``etc/httpd/conf.d/default-virtualhost.inc``: common configuration
  included inside default virtual host on port 80

* ``etc/httpd/conf.d/nethserver.conf``: default httpd configuration,
  includes ``conf.d/default-virtualhost.inc``. 
  Normally a package shouldn't add a fragment to it.

* ``httpd/vhost``: everything inside will be included in ``default-virtualhost.inc``.
  *DO NOT USE*, it's here only for backward compatibility


Web applications
----------------

Every package which needs to change the Apache configuration:

* should add a static (or template-generated) file inside ``/etc/httpd/conf.d/`` directory
* must include all Rewrite options inside a fragment for ``default-virtualhost.inc``

Example
^^^^^^^

Package named ``nethserver-mywebapp`` which requires a rewrite rule from http to https.
The web application must be accessible under ``http://<server_address>/mywebapp``.

Static file ``/etc/httpd/conf.d/mywebapp.conf``:

::
 
 Alias /mywebapp /usr/share/mywebapp
 <Directory "/usr/share/mywebapp">
     AllowOverride None
     Options None
     Require all granted
 </Directory>

Rewrite rule fragment ``/etc/e-smith/templates/etc/httpd/conf.d/default-virtualhost.inc/30mywebapp``:

::

 #
 # 30mywebapp
 #
 
 RewriteEngine on
 RewriteRule ^/mywebapp(/.*)?$ https://%\{SERVER_NAME\}/mywebapp$1 [L,R=301]

Inside the ``createlinks`` file, the configuration should be applied during the update event:

::

  my $event = "nethserver-mywebapp-update";
  event_templates($event, 
                     '/etc/httpd/conf.d/default-virtualhost.inc',
  );

  event_services($event, 
                     'httpd' => 'reload',
  );



configuration database
----------------------

::

 httpd=service
    SSLCipherSuite=DEFAULT:!EXP:!SSLv2:!DES:!IDEA:!SEED:+3DES
    TCPPorts=80,443
    access=green,red
    status=enabled


vhost database
--------------

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

The database contains a special ``default`` record which represents the default
virtual host: ::

  default=vhost
    Description=Default virtual host
    FtpPassword=
    FtpStatus=enabled

This virtual host is always enabled and can't be deleted. If FTP access is
enabled, the user will be chrooted inside ``/var/www/html`` directory.

Events
------

::

 signal-event nethserver-httpd-update
 signal-event nethserver-httpd-save


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

