.. _collabora-section:

================
Collabora Online
================

.. note: ::

  This package is not supported in |product| Enterprise


Collabora Online
 Collabora Online is a powerful LibreOffice-based online office that supports all
 major document, spreadsheet and presentation file formats, which you can integrate
 in your own infrastructure.
 Please see the `official website <https://www.collaboraoffice.com/collabora-online/>`_.

Installation
============

Install from the Software Center or use the command line: ::

  yum install nethserver-collabora

First configuration
===================

Collabora Online requires a dedicated virtual host and it's only accessible from HTTPS.  
On installation the (default) virtual host ``collabora.server_domain`` is created, an other virtual host can be set by executing:

::

  config setprop loolwsd VirtualHost loolwsd.yourdomain.com 
  signal-event nethserver-collabora-update

It is recommended to obtain a valid HTTPS certificate for the virtual host;
this can be done via Let's encrypt from ``Server certificate`` section of Server Manager interface.

.. note: ::

  If no valid certificate is present open the virtual host in your web-browser to add an exception for the certificate.

The package does the following:

* Create a virtual host for collabora.
* If nethserver-nextcloud is installed on the same server:

  * Install and configure richdocuments-app
  * Add server FQDN and Nextcloud custom virtual host, if present, to the trusted domains allowed to access to Collabora Online


If your instance of Nextcloud is not installed in the same server of Collabora Online,
you must set the host name of Nextcloud in the prop ``AllowWopiHost``: ::

  config setprop loolwsd AllowWopiHost nextcloud-office.yourdomain.com
  signal-event nethserver-collabora-update

Then manually install and configure the Nextcloud `richdocuments app <https://github.com/nextcloud/richdocuments#nextcloud-app>`_.


Database
========

The configuration is stored inside the ``configuration`` db, under the ``loolwsd`` key. To show it: ::

 config show loolwsd

Properties:

* ``AllowWopiHost``: additional trusted domain allowed to access to Collabora Online, only needed if nextcloud instance is on separate server.
* ``VirtualHost``: set dedicated virtual host for Collabora Online

examples: ::

  config setprop loolwsd VirtualHost loolwsd-dev.nethserver.net AllowWopiHost nextcloud-office.yourdomain.com
  config show loolwsd
  loolwsd=service
    AllowWopiHost=nextcloud-office.yourdomain.com
    VirtualHost=loolwsd.yourdomain.com
    status=enable


Admin user
==========

After installation, admin dashboard can be enabled with : ::

  loolconfig set-admin-password 
  
And is accessible at: ::

  https://collabora.yourdomain.com/loleaflet/dist/admin/admin.html