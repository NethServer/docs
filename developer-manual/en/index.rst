.. NethServer documentation master file, created by
   sphinx-quickstart on Sun Jan 19 10:47:03 2014.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

Developer Manual
================

.. image:: _static/logo.png
      :alt: NethServer

**Official site**: `http://www.nethserver.org <http://www.nethserver.org>`_

.. toctree::
   :maxdepth: 2
   :caption: Rules and conventions
   
   introduction
   development_process
   rpm_rules
   i18n

.. toctree::
   :maxdepth: 2
   :caption: Architecture

   databases
   templates
   events
   services

.. toctree::
   :maxdepth: 2
   :caption: Implementation

   filesystem_options
   dns
   dhcp
   random_url
   migration
   certificate_management
   yum_plugin
   backup

.. toctree::
   :maxdepth: 2
   :caption: Web interface

   web_interface
   create_interface_module
   dashboard
   inline_help
   todos_api

.. toctree::
   :maxdepth: 2
   :caption: Packages
   
   building_rpms
   building_iso
   repositories
   package_groups

.. toctree::
   :maxdepth: 2
   :caption: Modules

   ftp
   ups
   tftp
   collectd
   phone_home
   content_filter
   webvirtmgr
   duc
   snmp
   tomcat7
   postgresql
   unixodbc
   ntopng
   samba_audit
   redis
   memcached
   smartd
   cups
   antivirus
   mysql

.. toctree::
   :maxdepth: 2
   :glob:
   :caption: Modules (new)
 
   nethserver-*

.. toctree::
   :maxdepth: 2
   :caption: Appendix

   license_headers
   rebranding_manual 
   license


Indices and tables
==================
   
* :ref:`genindex`
* :ref:`search`

.. image:: _static/by-nc-sa_small.png
   :alt: CC by-nc-sa
   :align: right
   :target: http://creativecommons.org/licenses/by-nc-sa/4.0/legalcode
