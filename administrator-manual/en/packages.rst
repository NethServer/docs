.. _package_manager-section:

===============
Package manager
===============

|product| is highly modular: at the end of the installation only base system will be ready to be used.
Base system includes modules like network configuration and log viewer.
The administrator can install additional modules like mail server, DHCP server and firewall.

The main page shows all available and installed (checked) modules.
The view can be filtered by category.

To install a module, check the corresponding box and click on :guilabel:`Apply`.
To remove a module, uncheck the corresponding box and click on :guilabel:`Apply`.
Next page will resume all modifications and display all optional packages.


.. NOTE:: 

    Optional packages can be added to the system *after* installation
    of the main component.
    Just click again on :guilabel:`Apply` and select optional packages
    from confirmation page.


The section :guilabel:`Installed software` displays all packages already installed into the system.


Inline help
===========

All packages inside the Server Manager contain an :index:`inline help`.
The inline help explains how the module works and all available options.

These help pages are available in all Server Manager's languages.

A list of all available inline help pages can be found at the address: ::

 https://<server>:980/<language>/Help

**Example**

If the server has address ``192.168.1.2``, and you want to see all English help pages, use this address: ::

 https://192.168.1.2:980/en/Help


