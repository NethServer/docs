.. _release-notes-section:

=======================
Release notes |version|
=======================

|product| release |version|

.. only:: nscom

    - ISO release 7.9.2009 "final" replaces any previous ISO

    - This release is based on `CentOS 7 (2009) <https://wiki.centos.org/Manuals/ReleaseNotes/CentOS7>`_

    - CentOS 7 will receive security updates until 2024-06-30
    
    - :ref:`nscom-releases-section`

    - List of `changes <https://github.com/NethServer/dev/issues?utf8=%E2%9C%93&q=is%3Aissue%20is%3Aclosed%20closed%3A2017-10-07T23%3A59%3A59Z..2024-06-30>`_

    - List of `known bugs <https://github.com/NethServer/dev/issues?utf8=%E2%9C%93&q=is%3Aissue+is%3Aopen+label%3Abug>`_

    - Discussions around `possible bugs <http://community.nethserver.org/c/bug>`_

.. only:: nsent

    - ISO release 7.9.2009 "final" replaces any previous ISO

    - This release is based on `CentOS 7 (2009) <https://wiki.centos.org/Manuals/ReleaseNotes/CentOS7>`_

    - CentOS 7 will receive security updates until 2024-06-30

Major changes on 2020-11-XX
---------------------------

* ISO release 7.9.2009 "final" replaces any previous ISO 7.8.2003

* The old Server Manager (namely Nethgui) is not available by default on new installations.
  To configure the system access the new Server Manager on port ``9090``.

  Old Server Manager can be still installed from :guilabel:`Software Center`.

* Until |product| 7.8.1908, CGP (Collectd Graph Panel), EveBox and Rspamd UI were available only on HTTPS port 980,
  under the old Server Manager Apache instance named ``httpd-admin``.
  These applications are now available also on port 443 and will be accessible even if the old Server Manager has
  not been installed.

  Access to the above applications can be restricted: see the respective manual pages for :ref:`CGP <cgp_restict_access-section>`,
  :ref:`Rspamd <rspamd-web-interface-section>` and :ref:`EveBox <evebox_restrict_access-section>`.

* On new installations, users belonging to the ``wheel`` group are now granted SSH and SFTP access.
  Note that users created by the Anaconda ISO installer can be members of ``wheel``. See :ref:`ssh-section` for details.

* On new installations, SSH weak ciphers are now disabled by default. To enable weak ciphers uncheck the :guilabel:`Disable weak ciphers`
  option inside the :menuselection:`System -> SSH` page.

* New installations of Nextcloud honor the StartTLS setting of the Active Directory accounts provider.
  As old installations ignore that setting and always send clear-text passwords, it is recommended
  to upgrade them to the new behavior. Make sure the remote AD accounts provider
  supports StartTLS, then run the following commands ::

      config setprop nextcloud HonorAdStartTls enabled
      signal-event nethserver-sssd-save

  Finally check that the :guilabel:`StartTLS` option is enabled in
  :guilabel:`System > Users & Groups > [Account provider] > Edit provider`.
  See also :ref:`dedicated-service-account`.

* To prevent errors during Nextcloud upgrades, the ``mail`` and ``theming`` have been disabled.
  After each upgrade, both applications should be manually updated and re-enabled by accessing
  Nextcloud administration interface.

* Netdata is now installed by default to serve charts for the Server Manager.
  Some plugins have been disabled to reduce resource usage.
  To re-enable such plugins see `netdata configuration <https://docs.nethserver.org/projects/nethserver-devel/en/latest/nethserver-netdata.html>`_ .

* Machines running a kernel older than ``3.10.0-1160.6.1.el7``, should be rebooted after installing ``nethserver-ndpi`` to enable
  ``xt_ndpi`` kernel module.

* Mattermost DB was upgraded to PostgreSQL 12. The PostgreSQL 9.4 instance is stopped and disabled
  automatically by the nethserver-mattermost upgrade procedure if no other service requires it.

  1. Ensure the old service is stopped and disabled: ::

      systemctl status rh-postgresql94-postgresql

  2. PostgreSQL 9.4 can be uninstalled with the following command: ::

      yum remove nethserver-postgresql94

.. _relnotes-ns78:

Major changes on 2020-05-05
---------------------------

* ISO release 7.8.2003 "final" replaces any previous ISO 7.7.1908

* The new Server Manager implementation based on Cockpit is now marked as stable

* On new installations, the :guilabel:`System > Settings > Shell policy > Override the shell of users` option is enabled by default.
  Normal users will be able to log in to the new Server Manager only if :guilabel:`System > Settings > User settings page > Enable user settings page` option has been enabled, or if the user has been
  delegated to access at least one module.

  SSH access is limited to ``root`` and users inside the designated administrative group (``Domain Admins`` by default). More granular permissions can be tuned from the :guilabel:`SSH` page.

* All IMAP actions will be logged by default into ``/var/log/imap``

* Shared seen flag is enabled by default for shared mail folders

* Mail server connection limit for each user has been increased to avoid errors on web mail clients

* When creating a new POP3 connector, filter check is disabled by default

* OpenVPN roadwarrior server will use the ``subnet`` `topology <https://community.openvpn.net/openvpn/wiki/Topology>`_ as default

* To increase security, when authentication mode is set to ``Username, Password and Certificate``, OpenVPN roadwarrior server will enforce a
  match between user name and certificate CN

* Default maximum PHP memory size has been increased from 128MB to 512MB

* Nextcloud now uses PHP 7.3 stack to improve performance and support widely used plugins

* Ejabberd has been upgraded to 20.03

* POP3 proxy (P3Scan) has been deprecated and can't be installed anymore from Software Center

* PHP 7.1 is now obsolete and has been removed from upstream repositories: restored machines will need to migrate custom applications to PHP 7.2 or higher



Major changes on 2019-10-07
---------------------------

* ISO release 7.7.1908 "final" replaces any previous ISO 7.6.1810

* The new Server Manager implementation based on Cockpit reached Beta stage and
  is available by default on new installations. Existing systems can add the new
  Server Manager module from the Software Center page.  See also
  :ref:`access2-section`.

* The :guilabel:`Software updates origin` (locked/unlocked) feature was removed
  from the "Software Center" page. |product| can be upgraded manually
  from the Software Center page when the next "point release" is released. See
  also :ref:`software-center-section`.

* Delta RPM files have been removed by the upstream distribution and are no longer
  available from YUM repositories

* OpenSSH configuration was removed from TLS policy settings and reverted to
  upstream defaults.

* Starting with the new Server Manager based on Cockpit, the Mail module
  feature :guilabel:`Shared mailboxes` has been renamed to :guilabel:`Public
  mailboxes`.

* The `Junk` public mailbox is created during the Mail module installation,
  granting IMAP access to the root user; further permissions can be added from the
  new Server Manager Email application or with an IMAP/ACL client, like Roundcube.

* Only users with enabled shell can access the new Server Manager.
  From the old Server Manager, go to the :guilabel:`Users and groups` page and enable
  the :guilabel:`Remote shell (SSH)` option for the selected user.
  From the new Server Manager, go to the :guilabel:`Users and groups` page and enable
  the :guilabel:`Shell` option for the selected user.

* Official ClamAV antivirus signatures are disabled by default.

* The web interface for selective restore has been removed from the old Server Manager.
  A new one is available inside Cockpit, see :ref:`selective_restore-section`.

* As default, the disk usage analyzer (duc) scans only the root file system contents. Other mount points are ignored.


Major changes on 2018-12-17
---------------------------

* ISO release 7.6.1810 "final" replaces any previous ISO 7.5.1804

* PHP 5.6 from SCL has reached end-of-life and is thus deprecated.
  See :ref:`dpw_php56scl`

* Default TLS policy is ``2018-10-01``

* Default systems log retention has been increased to 52 weeks

* The Zeroconf network protocol is now disabled by default

* By default, Evebox events are retained for 30 days. The new default is 
  applied to upgraded systems as a bug fix
  
* NDPI module has been updated to version 2.4 which no longer recognize some old protocols.
  See :ref:`dpw_ndpi24` for the list of removed protocols
  
* SMTP server can be directly accessed from trusted networks

* PPPoE connections use rp-pppoe plugin by default to improve network speed

.. only:: nscom

    * For repositories that support GPG metadata signature, YUM runs now an
      integrity check (``repo_gpgcheck=1``) for additional security. This new
      default setting is applied automatically unless a ``.repo`` file was changed
      locally. In that case an ``.rpmnew`` file is created instead of overwriting
      the local changes. Rename the ``.rpmnew`` to ``.repo`` to apply the new
      defaults. This is the list of files to be checked:

        - :file:`/etc/nethserver/yum-update.d/NsReleaseLock.repo`
        - :file:`/etc/yum.repos.d/NethServer.repo`
        - :file:`/etc/yum.repos.d/NsReleaseLock.repo`

Major changes on 2018-06-11
---------------------------

* ISO release 7.5.1804 "final" replaces any previous ISO 7.5.1804 "rc" and "beta"

* The :ref:`email-section` module is now based on Rspamd

* MX DNS record override for LAN hosts has been removed. Removed ``postfix/MxRecordStatus`` prop

* Host name aliases are converted into ``hosts`` DB records. See :ref:`email-mxrecordstatus`

* :file:`/etc/fstab` is no longer an expanded template. See :ref:`shared_folders_requirements-section` and :ref:`home_bind-section` for details

* Default permissions for :ref:`shared_folders-section` is :guilabel:`Grant full control to the creator`

* Default :ref:`tlspolicy-section` is ``2018-03-30``

* Default Server Manager :ref:`session idle timeout <session-timeouts-section>` is 60 minutes, session life time is 8 hours

* Quality of Service (QoS) implementation now uses `FireQOS <https://github.com/firehol/firehol/wiki/FireQOS>`_,
  current configuration is automatically migrated. See :ref:`traffic-shaping-section`

* The menu entry :guilabel:`Automatic updates` in Server Manager was removed.
  Automatic  updates are now configured from :guilabel:`Software center >
  Configure`. See :ref:`software-updates-section`

* The :guilabel:`NethServer subscription` module is available by default in new installations.
  Run the following command to update the base module set on existing installations: ``yum update @nethserver-iso``

* The WebVirtMgr project is no longer maintained and the corresponding module has been removed
  along with nethserver-libvirt package.
  See :ref:`virtual_machines-section` chapter for details on how to use virtualization

Major changes on 2017-10-26
---------------------------

* ISO release 7.4.1708 "final" replaces the old ISOs 7.4.1708 "beta1" and 7.3.1611 "update 1"

* The local AD account provider applies updates to the Samba DC
  instance automatically (`#5356 <https://github.com/NethServer/dev/issues/5356>`_)
  Latest Samba DC version is 4.6.8

* The Software center page warns when a new upstream release is available 
  (`#5355 <https://github.com/NethServer/dev/issues/5355>`_)
  
* Added FreePBX 14 module
  
* Squid has been patched for a smoother web navigation experience when using SSL transparent proxy

* Ntopng 3 replaces Bandwidthd, the Server Manager has a new "top talkers" 
  page which tracks hosts network usage

* Suricata can be configured with multiple categories rules

* EveBox can report traffic anomalies detected by Suricata

* Nextcloud 12.0.3

* Web antivirus based on ICAP instead of ECAP

* Web filters: ufdbGuard updated to 1.33.4, small UI improvements on web

* Diagtools: added speedtest

* ufdbGuard updated to release 1.33.4

* WebTop4 has been removed

Major changes on 2017-07-31
---------------------------

* ISO release 7.3.1611 "update 1" replaces the previous ISO 7.3.1611 "Final"

* Configuration backup page enhancement

* Accounts provider page enhancement

* Migration from sme8 and upgrade from ns6 procedures

* OpenvPN: improve net2net tunnels

* WebTop 5.0.7 

* Backup data: basic WebDAV support for backups and storage stats

* UI tweaks for IPSec tunnels

* Web proxy: support divert and priority rules

* NextCloud 12

* Network diagnostic tools page

Major changes on 2017-01-30
---------------------------

* ISO release 7.3.1611 "Final" replaces the previous ISO 7.3.1611 "RC4"
* Installer: added new manual installation method
* Account providers: "administrators" group has been replaced by "domain admins" group (:ref:`server_manager-section`)
* Mail server: fix pseudonym expansion for groups
* Mail server: enable user shared mailbox by default (:ref:`enable_shared_folders-section`)
* Mail server: specific per-domain pseudonym now override generic ones
* OpenVPN: start VPN clients on boot
* Web filter: fix group-based profiles
* Firewall: fix selection of time conditions
* IPS: update configuration for latest pulledpork release

Deprecated features and packages
--------------------------------

.. _dpw_php56scl:

PHP 5.6 SCL
^^^^^^^^^^^

PHP 5.6 from the SCL repository has reached end-of-life (EOL) [#PHP56RHEOL]_
[#PHP56EOL]_.

To avoid problems with existing legacy applications, the PHP 5.6 SCL packages
from CentOS 7.5.1804 will be still available from |product| repositories during
the 7.6.1810 lifetime.

.. warning::

    PHP 5.6 SCL packages will **not** receive any security update. Very limited
    support will be provided as best-effort

The ``nethserver-rh-php56-php-fpm`` package will be removed from the next
|product| release.

Developers are invited to update their modules, replacing
``nethserver-rh-php56-php-fpm`` with ``nethserver-rh-php71-php-fpm`` as soon as
possible.

.. _dpw_ndpi24:

NDPI 2.4
^^^^^^^^

The following protocols have been removed:

* tds
* winmx
* imesh
* http_app_veohtv
* quake
* meebo
* skyfile_prepaid
* skyfile_rudics
* skyfile_postpaid
* socks4
* timmeu
* torcedor
* tim
* simet
* opensignal
* 99taxi
* easytaxi
* globotv
* timsomdechamada
* timmenu
* timportasabertas
* timrecarga
* timbeta

Rules using the above protocols, will be automatically disabled.

Upgrading |product| 6 to |product| |version|
--------------------------------------------

It is possible to upgrade the previous major release of |product| to |version|,
with a backup/restore strategy. See the :ref:`upgrade-section` for details.

.. _server_manager-section:

Server Manager access
^^^^^^^^^^^^^^^^^^^^^

If you want to grant :ref:`Server Manager access to other users than root <admin-account-section>`,
please add the users to the "domain admins" group and execute: ::

  config delete admins
  /etc/e-smith/events/actions/initialize-default-databases

.. _enable_shared_folders-section:

User shared mailbox
^^^^^^^^^^^^^^^^^^^

If you want to enable user shared mailbox, execute: ::

  config setprop dovecot SharedMailboxesStatus enabled
  signal-event nethserver-mail-server-update

.. _discontinued-section:

Discontinued packages
^^^^^^^^^^^^^^^^^^^^^

The following packages were available in the previous 6 release and have been
removed in 7:

* nethserver-collectd-web: replaced by nethserver-cgp
* nethserver-password: integrated inside nethserver-sssd
* nethserver-faxweb2: see the discussion `faxweb2 vs avantfax <http://community.nethserver.org/t/ns-7-faxweb2-vs-avantafax/2645>`_.
* nethserver-fetchmail: replaced by getmail
* nethserver-ocsinventory, nethserver-adagios: due to compatibility problems with Nagios, these modules will be
  mantained only on |product| 6 release
* nethserver-ipsec: IPSec tunnels are now implemented in nethserver-ipsec-tunnels, L2TP function has been dropped
* nethserver-webvirtmgr


----

.. rubric:: References

.. [#PHP56RHEOL] Red Hat Software Collections Product Life Cycle -- https://access.redhat.com/support/policy/updates/rhscl
.. [#PHP56EOL] PHP supported versions -- http://php.net/supported-versions.php
