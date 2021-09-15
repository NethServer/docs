.. _web-server-section:

.. index:: virtual hosts
   single: HTTP
   single: HTTPS

==========
Web server
==========

.. note::

    This chapter describes the features of the *Web server* application,
    available in the new Server Manager.

After |product| has been installed the :guilabel:`Web server` application is
already available. It configures and starts the Apache HTTP web server.

The :guilabel:`Web server` application provides the following features:

- Apache HTTP web server
- Integration with system certificates for HTTPS
- Hosting of multiple web sites 
- HTTP :index:`reverse proxy`
- :index:`PHP` scripting language to run web applications
- :index:`FTP server`

The following sections describe the pages of the :guilabel:`Web server`
application. Some of them require additional software components that are
automatically downloaded, installed and configured when they are required for
the first time.


Web server dashboard
====================

The :guilabel:`Web server dashboard` page shows the current web server status
and statistics. It also lists the additional components installed on the system.

The default Apache configuration serves the contents of :file:`/var/www/html`
and is capable of executing PHP scripts by running them on the
:guilabel:`Default web stack`.

.. _webserver-settings-section:

Settings
========

The :guilabel:`Settings` page allows to change the PHP configuration parameters
for resources allocation (e.g. script maximum memory and execution time).

Changes affect the global PHP configuration: as such they are valid for both web
applications and command line scripts, unless they are overridden by some means.

PHP settings can also be adjusted for a specific web site from the
:guilabel:`Virtual hosts` page (see also :ref:`webserver-phpversions-section`),
or overridden with a custom configuration file. To this end,

  1. for PHP 7.2, look at current PHP-FPM settings in
     :file:`/etc/opt/rh/rh-php72/php-fpm.d/000-virtualhost.conf`;

  2. create a file under the same directory (e.g.
     :file:`/etc/opt/rh/rh-php72/php-fpm.d/001-custom.conf`) and refer to the
     official `PHP-FPM documentation`_ to adjust the pool directives;

  3. add the created file to your :ref:`configuration backup
     <configuration_backup-section>`.

.. _`PHP-FPM documentation`: https://www.php.net/manual/en/install.fpm.configuration.php

.. _virtual_hosts-section:

Virtual hosts
=============

Multiple web sites can be hosted on |product|. It is possible to configure the
web site hosting space in the :guilabel:`Virtual hosts` page.

When a new virtual host is created with one or more *server names* the new
Server Manager contextually creates a server alias name in the local DNS service
for each of them.

.. note::

    A server alias name is accessible from web clients if they use the |product|
    itself as their DNS server.  For public web sites, refer to your DNS
    provider documentation and ensure the server alias name is correctly set in
    the public DNS.

Server alias names are listed and can be changed from the new Server Manager
:ref:`dashboard <system-section>`.


Web site access restrictions
----------------------------

It is possible to limit how the web clients access the web site with the
following options, available under the :guilabel:`Advanced settings` section.

1. Enable the option :guilabel:`Allow access from trusted networks only`. Refer to
   :ref:`trusted_networks-section` for more information.

2. Enable the switch :guilabel:`Require HTTP authentication` to grant access
   only if the specified password is provided by the client. Web applications
   usually provide an authentication method by themselves: this option could be
   useful to protect the contents of static web sites.

3. If the web site must be always accessed through an encrypted channel it is
   possible to enable the :guilabel:`Require SSL encrypted connection` option. Any
   resource request received over the HTTP protocol is redirected over HTTPS.


SSL/TLS certificate
-------------------

Each virtual host can be assigned a reserved :guilabel:`SSL/TLS certificate` or
rely on the default system one. In any case, the virtual host names must be
present among the certificate alternative names, otherwise the web clients can
refuse to connect.

.. _configuring-web-app:

Configuring a web application
-----------------------------

When a new virtual host is created a web root directory is created as well. The
full web root path is displayed under :guilabel:`Virtual hosts > List > Web root
path`.

If the switch :guilabel:`Enable FTP access` is enabled, it is possible to upload
data, configuration and script files to the web root path using a FTP client.

.. hint::

    HTTP authentication password should be different from the FTP one, because
    FTP is used to upload the virtual host contents whilst HTTP is used to see
    them from the web.

The web site displays a "Welcome" page until a file named :file:`index.html`
or :file:`index.php` is uploaded under the web root directory. If this is not
desired, it is possible to enable the option :guilabel:`Root directory file
listings`, as alternative to the "Welcome" page.

FTP uploaded files are owned by the `apache` group with read-only permissions.
If write or execution permissions are needed, a FTP client can be used to grant
them.

.. warning::

    If a web site contains executable code, such as PHP scripts, the security
    implications of file permissions must be evaluated carefully. Grant write
    access to a limited set of special files and directories, as required by the
    web application documentation.

The Apache configuration can be overridden by uploading a file named
:file:`.htaccess`. Refer to the official Apache documentation for more
information about this feature [#HTACCESS]_.

.. _webserver-phpversions-section:


PHP versions and configuration
------------------------------

If the PHP version provided by the :guilabel:`Default web stack` does not fit a
web application it is possible to select and install an alternative one and
override the global PHP default settings, as explained by the
:ref:`webserver-settings-section` section.

Disabling a virtual host
------------------------

The :guilabel:`Disable` action hides the virtual host, making it not accessible
from web clients. This operation is reversible, by selecting the
:guilabel:`Enable` action.

Deleting a virtual host
-----------------------

The :guilabel:`Delete` action removes the virtual host configuration and erases
the web root directory. This operation is not reversible.

.. _proxy_pass-section:

Reverse proxy
=============

As alternative to a virtual host, which stores static files or a PHP web
application under a local web root directory, it is possible to forward web
requests to another HTTP server and serve responses in behalf of it. This
behavior can be configured from the :guilabel:`Reverse proxy` page.

Each reverse proxy item is actually a rule that can match an incoming web
request. Depending on the rule :guilabel:`Name` field value, the match can occur 
in either:

 A) the requested **web site name**, if :guilabel:`Name` starts with any character,
    but the slash ``/``, or

 B) the requested **resource path**, if :guilabel:`Name` starts with a slash ``/``
    character.

If the rule matches, the request is forwarded to another web server, defined by
the :guilabel:`Destination URL` field.

Web site name proxy pass
------------------------

Scenario for a named proxy pass:

* |product| is the firewall of your LAN with public name ``http://fw.myfirstdomain.org``
* You have a domain ``http://mydomain.com`` pointing to the public IP for |product|
* You would like ``http://mydomain.com`` to forward to the internal server
  (internal IP: 192.168.2.100)

In this scenario, create a new record by clicking :guilabel:`Create a reverse proxy` button.
Fill the :guilabel:`Name` field with ``mydomain.com`` and the :guilabel:`Destination URL` with
``http://192.168.2.100``.

Resource path proxy pass
------------------------

Scenario for path-based proxy pass:

* |product| is the firewall of your LAN
* You have a domain ``http://mydomain.com``
* You would like ``http://mydomain.com/mysite`` to forward to the internal server
  (internal IP: 192.168.2.100)

In this scenario, create a new record by clicking :guilabel:`Create a reverse proxy` button.
Fill the :guilabel:`Name` field with ``/mysite`` and the :guilabel:`Destination URL` with
``http://192.168.2.100``.

Extra options
-------------

If only encrypted connections are allowed, enable the :guilabel:`Require SSL
encrypted connection`.

Only clients from certain networks can be allowed to connect, by specifying  a
comma-separated list of CIDR networks under the :guilabel:`Access from CIDR
networks`  field.

Options available only for named proxy pass:

* Enable or disable forwarding of ``Host`` header
* Enable or disable WebSocket forwarding
* Accept invalid target SSL certificate: use this option only if 
  the target has a self-signed certificate


Advanced reverse proxy settings
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

When the reverse proxy rule matches a **web site name** it is possible to assign
it a dedicated certificate, choosing one from the :guilabel:`SSL/TLS
certificate` list.

.. warning:

    If the certificate does not include the web site name, web clients will
    refuse to open the web site.


It is not possible to select the certificate if the rule matches a **resource
path**. In this case only the default certificate can be used.

Regardless the rule type, the following settings are also available:

* :guilabel:`Access from CIDR networks`: restricts the access from the given
  list of CIDR networks. Only web clients connecting from those networks
  are allowed to open the web site.

* :guilabel:`Require SSL encrypted connection`: if enabled, any `http://`
  request is redirected to `https://`.

* :guilabel:`Accept invalid SSL certificate from target`: if the destination
  URL starts with `https://` and an invalid certificate is returned,
  enabling this option ignores the certificate validation error.

* :guilabel:`Forward HTTP "Host" header to target`: if enabled, a HTTP
  `Host` header containing the original request host name is forwarded to
  the destination URL. This could be required by the destination server
  application to work properly.

* `Allow encoded slashes`: Some web applications needs to use encoded path separators (``%2F`` for ``/``) in the URLs. 
  Such URLs are accepted, but encoded slashes are not decoded but left in their encoded state. 
  This options is disabled by default and must be enabled manually per proxypass.
::

 db proxypass setprop sub.domain.com AllowEncodedSlashes enabled
 signal-event  nethserver-httpd-save

.. _ftp-section:

FTP server
==========

.. warning::

    The FTP protocol is insecure. Passwords and file data are sent in clear text
    over the network.

The File Transfer Protocol is a standard network protocol used for the transfer
of computer files between a client and server [#FTPWIKI]_. The :guilabel:`FTP`
page enables the FTP service and configures additional user accounts limited to
the FTP service only.

.. index::
   pair: FTP; jail

Users of the FTP service can be restricted to access their own home directory by
enabling :guilabel:`Chroot user on home directory`. When this option is enabled
the user cannot see the other system directories. This configuration is also
known as *jailing*.

When a virtual host is created, a random FTP user name is assigned to it. It is
possible to upload the virtual host file contents with FTP. Refer to
:ref:`configuring-web-app` for more information.

System users
------------

.. warning:: 
   This configuration is highly discouraged.
   Also note that when enabled, the integration with the web server will break.

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



.. rubric:: References

.. [#HTACCESS] Apache documentation for :file:`.htaccess` files
   https://httpd.apache.org/docs/2.4/howto/htaccess.html

.. [#FTPWIKI] File Transfer Protocol
   https://en.wikipedia.org/wiki/File_Transfer_Protocol
