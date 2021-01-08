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

.. toctree::
   :maxdepth: 2
   :caption: Release notes

   release_notes

.. toctree::
   :maxdepth: 2
   :caption: Installation

   installation
   access2
   registration

.. only:: nscom

    .. toctree::
       :maxdepth: 1

       subscription

.. toctree::
   :maxdepth: 2
   :caption: Configuration

   base_system2
   packages
   accounts
   dns
   dhcp
   tlspolicy

.. only:: nsent

.. toctree::
    :maxdepth: 1

    launcher

.. toctree::
   :maxdepth: 1
   :caption: Applications

   backup
   web_server
   web_proxy
   firewall
   mail
   webmail
   shared_folder
   blacklist
   sandbox

.. toctree::
   :maxdepth: 1
   :caption: Modules

   disaster_recovery
   backup_customization
   backup_legacy
   webtop5
   pop3_connector
   chat
   team_chat
   ups
   report
   fax_server
   content_filter
   suricata
   proxy_pass
   virtual_hosts
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
   virtual_machines
   fail2ban
   rspamd
   antivirus


.. only:: nscom

    .. toctree::
       :maxdepth: 1
       :caption: NethForge modules

       collabora
       docker
       sogo
       phpVirtualBox
       hotsync
       mssql

.. toctree::
   :maxdepth: 2
   :caption: Best practices

   third_party
   
.. toctree::
   :maxdepth: 1
   :caption: Appendix

   migration
   upgrade
   mail2
   license
   nscom_releases
   issue_trackers
   genindex


.. toctree::
   :hidden:
   :caption: Old Server Manager
   :glob:

   base_system
   backup_legacy
   pop3_proxy
   ui/*



.. image:: nscom/_static/by-nc-sa_small.png
   :alt: CC by-nc-sa
   :align: right
   :target: http://creativecommons.org/licenses/by-nc-sa/4.0/legalcode
