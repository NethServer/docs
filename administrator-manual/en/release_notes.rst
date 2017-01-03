=======================
Release notes |release|
=======================

|product| release |release|

This release has been rebased on CentOS 7.3:
https://wiki.centos.org/Manuals/ReleaseNotes/CentOS7

Relevant changes on |product|:

* The web interface now lists remote users and groups in real time (#5168). See 
  the :ref:`users_and_groups-section` manual page for details of the updated 
  domain bind procedures.
* LDAP and Samba AD both have the same administrative built-in users and groups (#5157)
* Handle built-int administrators groups from Server Manager (#5168)
* Much simplified configuration of remote account providers (#5165)
* Samba shares support both NTLM and Kerberos authentication (#5160)
* Always enable LDAP secure protocols when connecting to remote account providers (#5161)
* Nextcloud has been updated to release 10.0.2 (#5155)
* Better certificate management (#5174)
* DPI module now works on standard kernel (#5170)
* SquidGuard has been replaced by ufdbGuard (#5171)
* Squid transparent HTTPS proxy doesn't require certificate installation on clients (#5169)
* Support UEFI bios (#5148)
* Boot partition size has been increased to 1GB


Upgrading rc2 to rc3
--------------------

To upgrade an rc2 installation to rc3, go to the :guilabel:`Software Center` 
page and start the update as usual. 
If the system is running a DPI-enabled kernel, before update
follow :ref:`dpi-kernel_section`.

All bug fixes are applied automatically, but there are some enhancements that
require a manual intervention.

After update run the following command: ::

  signal-event nethserver-sssd-save

If the the web filter is installed, run: ::

  /etc/cron.daily/update-squidguard-blacklists
  signal-event nethserver-squid-update

At the end of updating, a reboot it's recommended
to load the new kernel.

.. _dpi-kernel_section:

Upgrading a firewall with DPI-enabled kernel
--------------------------------------------

To upgrade a system running kernel-lt with DPI support, execute these commands
before updating: ::

  cat << EOF > /etc/sysconfig/kernel
  # UPDATEDEFAULT specifies if new-kernel-pkg should make
  # new kernels the default
  UPDATEDEFAULT=yes

  # DEFAULTKERNEL specifies the default kernel package type
  DEFAULTKERNEL=kernel
  EOF

  yum reinstall grubby -y



Changelog
---------

|product| `rc3 changelog <https://github.com/NethServer/dev/issues?utf8=%E2%9C%93&q=is%3Aissue%20is%3Aclosed%20milestone%3Av7%20closed%3A2016-11-10T14%3A40%3A00Z..2016-12-16T10%3A40%3A00Z%20>`_


Known bugs
----------

* WebTop 4 will not work with remote account providers since it doesn't support LDAPS

* List of `known bugs <https://github.com/NethServer/dev/issues?utf8=%E2%9C%93&q=is%3Aissue%20is%3Aopen%20label%3Abug%20milestone%3Av7%20>`_

* Discussions around `possible bugs <http://community.nethserver.org/c/bug>`_


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

