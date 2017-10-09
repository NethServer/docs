=======================
Release notes |version|
=======================

|product| release |version|

.. only:: nscom

    - ISO release 7.4.1708 - 2017-10-XX

    - This release is based on `CentOS 7.4 <https://wiki.centos.org/Manuals/ReleaseNotes/CentOS7>`_

    - CentOS 7 will receive security updates until 2024-06-30

    - `List of changes <https://github.com/NethServer/dev/issues?utf8=%E2%9C%93&q=is%3Aissue%20is%3Aclosed%20milestone%3Av7%20closed%3A2017-01-30T23%3A59%3A59Z..2024-06-30>`_ (since 2017-01-30)

    - List of `known bugs <https://github.com/NethServer/dev/issues?utf8=%E2%9C%93&q=is%3Aissue%20is%3Aopen%20label%3Abug%20milestone%3Av7%20>`_

    - Discussions around `possible bugs <http://community.nethserver.org/c/bug>`_


.. only:: nsent

    - ISO release 7.4.1708 - 2017-10-XX

    - This release is based on `CentOS 7.4 <https://wiki.centos.org/Manuals/ReleaseNotes/CentOS7>`_

    - CentOS 7 will receive security updates until 2024-06-30


Major changes on 2017-10-XX
---------------------------

* ISO release 7.4.1708 replaces the old ISO 7.3.1611 "update 1"

* The local AD account provider applies security updates to the Samba DC
  instance automatically (`#5356 <https://github.com/NethServer/dev/issues/5356>`_).
  To disable automatic updates, run the following command ::

    config setprop nsdc AutoUpdateType disabled

Major changes on 2017-07-31
---------------------------

* ISO release 7.3.1611 "update 1" replaces the previous ISO 7.3.1611 "Final"

* Configuration backup page enhancement

* Accounts provider page enhancement

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

If you want to grant Server Manager access to other users than root,
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
