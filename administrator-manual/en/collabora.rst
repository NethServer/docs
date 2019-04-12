.. _collabora-section:

================
Collabora Online
================

.. note::

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

Virtual host configuration
--------------------------

Collabora Online requires a dedicated virtual host and it's only accessible from
HTTPS with a valid certificate.

.. note::

 Collabora Online will **not be enabled** without a dedicated virtual host

To configure Collobora Online, execute: ::

  config setprop loolwsd VirtualHost collabora.yourdomain.com
  signal-event nethserver-collabora-update

After virtual host configuration, obtain a valid HTTPS certificate via Let's Encrypt
from ``Server certificate`` section of Server Manager interface.

Usage
-----

Collabora Online will be automatically enabled in Nextcloud if the package ``nethserver-nextcloud``
is present when the virtual host is configured, otherwise you can enable with: ::

  yum install nethserver-nextcloud
  signal-event nethserver-collabora-update

If your instance of Nextcloud is not installed in the same server of Collabora Online,
you must set the host name of Nextcloud in the prop ``AllowWopiHost``: ::

  config setprop loolwsd AllowWopiHost nextcloud-office.yourdomain.com
  signal-event nethserver-collabora-update

And manually configure the Nextcloud `richdocuments app <https://github.com/nextcloud/richdocuments#nextcloud-app>`_.

Admin user
==========

After installation, admin dashboard can be enabled with ``loolconfig set-admin-password`` and accessible at: ::

  https://collabora.yourdomain.com/loleaflet/dist/admin/admin.html
