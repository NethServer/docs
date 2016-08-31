nethserver-httpd
================

NethServer tries to remain compliant with the upstream configuration for ``httpd``.

In Apache 2.4 every global option is inherit by all virtual hosts,
except for the *Rewrite* directives.

In a clean installation the only defined virtual host is the one on port 443.
When nethserver-virtualhosts is installed, the package adds a new default virtual host.
This virtual host includes the ``/etc/httpd/conf.d/default-virtualhost.inc`` file
to mimic the upstram behavior.


See also "Certificate management" and "Virtualhosts" section for further information.

Templates
---------

Available templates under ``/etc/e-smith/templates/`` directory:

* ``etc/httpd/conf.d/default-virtualhost.inc``: common configuration
  included inside default virtual host on port 80

* ``etc/httpd/conf.d/nethserver.conf``: default httpd configuration,
  includes ``conf.d/default-virtualhost.inc``. 
  Normally a package shoudn't add a fragment to it.

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



Configuration database
----------------------

::

 httpd=service
    SSLCipherSuite=DEFAULT:!EXP:!SSLv2:!DES:!IDEA:!SEED:+3DES
    TCPPorts=80,443
    access=green,red
    status=enabled

 


Events
------

::

 signal-event nethserver-httpd-update
 signal-event nethserver-httpd-save
