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

    .. sidebar:: See also

        Support: `helpdesk.nethesis.it <http://helpdesk.nethesis.it>`_

        Official site: `www.nethesis.it <http://www.nethesis.it>`_

        Italian `Manual <https://nethserver.docs.nethesis.it/it/v7/>`_

        Obsolete `NethServer 6 Manual <https://nethserver.docs.nethesis.it/en/v6/>`_

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

   mail
   webmail
   shared_folder
   nextcloud
   team_chat
   chat

   antivirus
   sandbox

   firewall
   web_proxy
   fail2ban
   vpn
   suricata
   blacklist
   bandwidth_monitor
   dedalo

   freepbx

   ups
   statistics
   report

.. toctree::
   :maxdepth: 1
   :caption: Other modules

   webtop5
   phone_home
   nethvoice_intro
   nethcti_intro
   phonebook-mysql
   rspamd

.. toctree::
   :maxdepth: 2
   :caption: Best practices

   disaster_recovery
   backup_customization
   virtual_machines
   third_party

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
   snmp
   fax_server
   hotspot
   weekly_report
   ui/*



.. image:: nscom/_static/by-nc-sa_small.png
   :alt: CC by-nc-sa
   :align: right
   :target: http://creativecommons.org/licenses/by-nc-sa/4.0/legalcode
