======================
Certificate Management
======================

*nethserver-base* provides a set of templates that output
PEM-formatted certificate parts:

*  *certificate/key* RSA private key
*  *certificate/crt* public certificate
*  *certificate/pem* both key+crt parts

A certificate consumer daemon should expand those templates to its own
certificate paths, by installing the proper configuration under
``/etc/e-smith/templates.metadata``.

For instance *nethserver-httpd* adds the following template
configuration:

*  ``/etc/e-smith/templates.metadata/etc/pki/tls/private/localhost.key``

::

   TEMPLATE_PATH="certificate/key"
   OUTPUT_FILENAME="/etc/pki/tls/private/localhost.key"
   PERMS=0600
   UID="root"
   GID="root"

*  ``/etc/e-smith/templates.metadata/etc/pki/tls/certs/localhost.crt``

::

   TEMPLATE_PATH="certificate/crt"
   OUTPUT_FILENAME="/etc/pki/tls/certs/localhost.crt"
   PERMS=0600
   UID="root"
   GID="root"

Set ``OUTPUT_FILENAME``, ``PERMS``, ``UID`` and ``GID`` values according
to daemon configuration.

Default behaviour
=================

By default, ``CrtFile`` and ``KeyFile`` properties have empty values. In
this case, ``nethserver-base`` generates a self-signed certificate
during ``nethserver-base-update`` event.

Default SELinux-aware certificate locations are:

* ``/etc/pki/tls/private/NSRV.key``: private key
* ``/etc/pki/tls/certs/NSRV.crt``: CA certificate

A daily cron job checks certificate validity. If expired, the
self-signed certificate is re-generated and ``certificate-update`` event
is signaled.

Default certificate duration is set to 365 days. To change it:

::

       db configuration setprop pki CertificateDuration 3650

The certificate Common Name is set to system FQDN. To override this
value type:

::

       db configuration setprop pki CommonName custom.cn

Install a custom certificate
============================

Set the private key and certificate file paths:

::

    db configuration setprop pki CrtFile '/path/to/cert/pem-formatted.crt'
    db configuration setprop pki KeyFile '/path/to/private/pem-formatted.key'

You can also set a SSL certificate chain file:

::

    db configuration setprop pki ChainFile '/path/to/cert/pem-formatted-chain.crt'

Notify registered daemons about certificate update:

::

    signal-event certificate-update

