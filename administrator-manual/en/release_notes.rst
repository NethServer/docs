=======================
Release notes |version|
=======================

|product| release |version|

.. only:: nscom

    - ISO release 7.5.1804 "beta" - 2018-05-16

    - This release is based on `CentOS 7 (1804) <https://wiki.centos.org/Manuals/ReleaseNotes/CentOS7>`_

    - CentOS 7 will receive security updates until 2024-06-30
    
    - :ref:`nscom-releases-section`

    - List of `changes since 2018-05-XX <https://github.com/NethServer/dev/issues?utf8=%E2%9C%93&q=is%3Aissue%20is%3Aclosed%20closed%3A2017-01-30T23%3A59%3A59Z..2024-06-30>`_

    - List of `known bugs <https://github.com/NethServer/dev/issues?utf8=%E2%9C%93&q=is%3Aissue+is%3Aopen+label%3Abug>`_

    - Discussions around `possible bugs <http://community.nethserver.org/c/bug>`_

    - `Project board <https://github.com/orgs/NethServer/projects/1>`_


.. only:: nsent

    - ISO release 7.5.1804 beta

    - This release is based on `CentOS 7 (1804) <https://wiki.centos.org/Manuals/ReleaseNotes/CentOS7>`_

    - CentOS 7 will receive security updates until 2024-06-30


Major changes on 2018-05-16
---------------------------

* The :ref:`email-section` module is now based on Rspamd

* MX DNS record override for LAN hosts has been removed. Removed ``postfix/MxRecordStatus`` prop.

* :file:`/etc/fstab` is no longer an expanded template. See :ref:`shared_folders_requirements-section` and :ref:`home_bind-section` for details.

* Default permissions for :ref:`shared_folders-section` is :guilabel:`Grant full control to the creator`

* Default :ref:`tlspolicy-section` is ``2018-03-30``

* Default Server Manager session idle timeout is 15 minutes, session life time is 8 hours

* The WebVirtMgr project is no longer maintained and the corresponding module has been removed
  along with nethserver-libvirt package.
  See :ref:`virtual_machines-section` chapter for details on how to use virtualization.

* The :guilabel:`NethServer subscription` module is available by default in new installations.
  Run the following command to update the base module set on existing installations: ::

    yum update @nethserver-iso

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
