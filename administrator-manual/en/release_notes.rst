=======================
Release notes |release|
=======================

|product| release |release|

This release is based on CentOS 7.3:
https://wiki.centos.org/Manuals/ReleaseNotes/CentOS7

Relevant changes since RC4:

* Installer: added new manual installation method
* Account providers: "administrators" group has been replaced by "domain admins" group (:ref:`server_manager-section`)
* Mail server: fix pseudonym expansion for groups
* Mail server: enable user shared mailbox by default (:ref:`enable_shared_folders-section`)
* Mail server: specific per-domain pseudonym now override generic ones
* OpenVPN: start VPN clients on boot
* Web filter: fix group-based profiles
* Firewall: fix selection of time conditions
* IPS: update configuration for latest pulledpork release

Upgrading RC4 to Final
----------------------

To upgrade a RC4 installation to Final, go to the :guilabel:`Software Center`
page and follow Server Manager instructions.

Upgrading |product| 6 to |product| |release|
--------------------------------------------

It is possible to upgrade the previous major release of |product| to |release|,
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


Changelog
---------

|product| `Final changelog <https://github.com/NethServer/dev/issues?utf8=%E2%9C%93&q=is%3Aissue%20is%3Aclosed%20milestone%3Av7%20closed%3A2017-01-17T00%3A00%3A00Z..2017-01-30%20>`_


Known bugs
----------

* List of `known bugs <https://github.com/NethServer/dev/issues?utf8=%E2%9C%93&q=is%3Aissue%20is%3Aopen%20label%3Abug%20milestone%3Av7%20>`_

* Discussions around `possible bugs <http://community.nethserver.org/c/bug>`_

.. _discontinued-section:

Discontinued packages
---------------------

The following packages were available in the previous 6 release and have been
removed in 7:

* nethserver-collectd-web: replaced by nethserver-cgp
* nethserver-password: integrated inside nethserver-sssd
* nethserver-faxweb2: see the discussion `faxweb2 vs avantfax <http://community.nethserver.org/t/ns-7-faxweb2-vs-avantafax/2645>`_.
* nethserver-fetchmail: replaced by getmail
* nethserver-ocsinventory, nethserver-adagios: due to compatibility problems with Nagios, these modules will be
  mantained only on |product| 6 release

