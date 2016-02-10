.. NethServer documentation master file, created by
   sphinx-quickstart on Sun Jan 19 10:47:03 2014.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

Developer Manual
================

.. image:: ../../_static/logo.png
      :alt: NethServer

.. rubric:: NethServer is an operating system designed for small offices and medium enterprises. It's simple, secure and flexible. 

.. sidebar:: About

    * **Official site**: `http://www.nethserver.org <http://www.nethserver.org>`_
    * **Bug tracker**: `http://dev.nethserver.org <http://dev.nethserver.org>`_
    * **Twitter**: `@nethserver <http://twitter.com/nethserver>`_
    * **Source code**: `http://dev.nethserver.org <http://dev.nethserver.org>`_
    * **Mailing list**: `nethserver@googlegroup.com` 
    * **ML archive**: `Google Groups <https://groups.google.com/d/forum/nethserver>`_
    * **IRC**: `#nethserver on freenode.net`

Rules and conventions
---------------------

.. toctree::
   :maxdepth: 2
   
   introduction
   development_process
   rpm_rules
   i18n

Architecture
------------

.. toctree::
   :maxdepth: 2

   databases
   templates
   events
   services

Implementation
--------------

.. toctree::
   :maxdepth: 2

   filesystem_options
   dns
   dhcp
   logs
   network
   random_url
   migration
   certificate_management
   yum_plugin
   backup
   gateway
   ips
   samba

Web interface
-------------

.. toctree::
   :maxdepth: 2

   web_interface
   create_interface_module
   dashboard
   customization
   inline_help
   todos_api

Packages
--------

.. toctree::
   :maxdepth: 2

   building_rpms
   building_iso
   repositories
   package_groups

Modules
-------


.. toctree::
   :maxdepth: 2

   directory
   email
   chat
   ftp
   ups
   tftp
   pop3_proxy
   pop3_connector
   owncloud
   roundcube
   collectd
   phone_home
   web_proxy
   web_antivirus
   content_filter
   lightsquid
   webvirtmgr
   duc
   snmp
   tomcat7
   postgresql
   unixodbc
   webtop4
   vpn
   unbound
   ntopng
   samba_audit
   redis
   memcached
   smartd
   cups
   avahi
   antivirus
   c-icap
   iaxmodem
   mysql
   hylafax
   ntpd

Appendix
--------

.. toctree::
   :maxdepth: 2

   license_headers
   rebranding_manual 
   license


Indices and tables
==================
   
* :ref:`genindex`
* :ref:`search`

.. image:: ../../_static/by-nc-sa_small.png
   :alt: CC by-nc-sa
   :align: right
   :target: http://creativecommons.org/licenses/by-nc-sa/4.0/legalcode
