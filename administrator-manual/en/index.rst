.. NethServer documentation master file

Administrator Manual 
====================

.. only:: nscom

    .. image:: nscom/_static/logo.png
          :alt: |product|

    .. sidebar:: See also

        * `Web site <http://www.nethserver.org>`_

        * `Community <http://community.nethserver.org>`_

        * `Wiki <https://wiki.nethserver.org>`_

        * `Developer manual <http://docs.nethserver.org/projects/nethserver-devel>`_

.. only:: nsent

    .. sidebar:: Contacts

        Support: `helpdesk.nethesis.it <http://helpdesk.nethesis.it>`_

        Official site: `www.nethesis.it <http://www.nethesis.it>`_

Release notes |version|
-----------------------

.. toctree::
   :maxdepth: 2

   release_notes

Installation
------------

.. toctree::
   :maxdepth: 2

   installation
   access
   registration

.. only:: nscom

    .. toctree::
       :maxdepth: 1

       subscription

Configuration
-------------

.. toctree::
   :maxdepth: 2

   packages
   base_system
   accounts
   dns
   dhcp
   tlspolicy

Modules
-------

.. toctree::
   :maxdepth: 1

   backup
   mail
   webmail
   webtop5
   pop3_proxy
   pop3_connector
   chat
   team_chat
   ups
   fax_server
   firewall
   web_proxy
   content_filter
   suricata
   proxy_pass
   virtual_hosts
   shared_folder
   bandwidth_monitor
   statistics
   vpn
   nextcloud
   ftp
   phone_home
   snmp
   nethvoice_intro
   nethcti_intro
   phonebook-mysql
   weekly_report
   hotspot
   dedalo
   freepbx
   hotsync
   virtual_machines
   fail2ban
   rspamd

.. toctree::
   :hidden:

   mail2

.. only:: nscom

    NethForge modules
    -----------------

    .. toctree::
       :maxdepth: 1

       sogo

Best practices
--------------

.. toctree::
   :maxdepth: 2

   third_party
   
Appendix
--------

.. toctree::
   :maxdepth: 1

   migration
   upgrade
   license
   nscom_releases

.. only:: nscom

    Indices
    -------

    * :ref:`General index <genindex>`

.. toctree::
   :hidden:
   :glob:

   ui/*



.. image:: nscom/_static/by-nc-sa_small.png
   :alt: CC by-nc-sa
   :align: right
   :target: http://creativecommons.org/licenses/by-nc-sa/4.0/legalcode
