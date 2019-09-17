==================
Nethesis Launcher
==================

Nethesis Launcher is a Cockpit app launcher available on HTTPS and HTTP ports.
The launcher is enabled if:

- Cockpit UI is installed (package ``nethserver-cockpit``)
- there is no home page already configured in httpd (no index page in :file:`/var/www/html`)

.. note:: If Cockpit UI has been manually installed, execute the following command to enable
        Nethesis Launcher: ::

         signal-event nethserver-register-update

Launcher customization
=======================

You can use your company brand in the app launcher by editing this configuration file: :file:`/usr/share/httpd/noindex/nethesis/res/launcher_data.ini`.
The default content of :file:`launcher_data.ini` is the following:

::

  [Launcher data]
  LauncherTitle=Nethesis Launcher
  LogoImage=nethesis-logo-color.png
  LogoHref=https://www.nethesis.it/
  DocsHref=https://docs.nethesis.it/

The file contains four properties that can be customized:

- ``LauncherTitle``: text appearing at the top left corner of the page
- ``LogoImage``: logo image appearing at the bottom left corner of the page
- ``LogoHref``: logo hyperlink
- ``DocsHref``: documentation hyperlink

Example
--------

If you want to use your company brand in the Nethesis Launcher just follow these steps:

- upload your logo image (e.g. ``my-company-logo.png``) into :file:`/usr/share/httpd/noindex/nethesis/res` directory of your server: ::

    scp my-company-logo.png root@servername:/usr/share/httpd/noindex/nethesis/res/

- open :file:`/usr/share/httpd/noindex/nethesis/res/launcher_data.ini` using ``vim`` or any other text editor and edit ``LauncherTitle``, ``LogoImage``, ``LogoHref`` and ``DocsHref`` properties: ::

    vim /usr/share/httpd/noindex/nethesis/res/launcher_data.ini
  
  The resulting file content should be similar to this: ::

    [Launcher data]
    LauncherTitle=My Company
    LogoImage=my-company-logo.png
    LogoHref=https://www.my-company.com/
    DocsHref=https://docs.my-company.com/
