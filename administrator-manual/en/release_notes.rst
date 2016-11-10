=======================
Release notes |release|
=======================

|product| release |release|

Upgrading rc1 to rc2
--------------------

To upgrade an rc1 installation to rc2, go to the :guilabel:`Software Center` 
page and start the update as usual.

All bug fixes are applied automatically, but there are two enhancements that
require a manual intervention:

* LDAP account with read-only privileges (#5145). Required only if
  nethserver-directory RPM is installed.

* Legacy short user name support (#5142). Starting from rc2 the system is
  configured to accept both short and long user name formats.  That means the
  user can login to any PAM-based service either as *username* or
  *username@domain*.

To enable the enhancements run the following command: ::

    signal-event nethserver-sssd-save

If the command is not executed the system does not support short user name format.

Changelog
---------

|product| `rc2 changelog <https://github.com/NethServer/dev/issues?utf8=%E2%9C%93&q=is%3Aissue%20is%3Aclosed%20milestone%3Av7%20closed%3A2016-10-18T13%3A22%3A00Z..2016-11-09T14%3A40%3A00Z>`_


Known bugs
----------

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

