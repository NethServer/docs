Changes
=======

This is the first official release of |product| 7.
Starting from this release, any installation will be upgradable to the final release.

A complete list fo changes for beta 1 can be found here:

* https://www.nethserver.org/the-street-towards-nethserver-7-beta-1/

Changes from beta 1 to beta 2
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

New features:

* Nextcloud 10
* SCL repository is now enabled by default
* Advanced static routes
* Bandwidthd (Simple bandiwidthd)
* Getmail (replaces Fetchmail)
* Refactored implementation of Apache configuration
* Improved package removal on Software Center

* Many bug fixed and code cleanup, mainly on the following components:
  * Let's Encrypt
  * Firewall
  * Samba
  * Home binding
  * DHCP on green
  * Roundcubemail
  * SSSD configuration
  * Certificate management
  * Installation from USB


Full changelog:
https://github.com/NethServer/dev/milestone/5?closed=1

Known bugs:
https://github.com/NethServer/dev/issues?q=is%3Aissue+is%3Aopen+label%3Abug



Discontinued packages
---------------------

The following packages have been removed:

* nethserver-collectd-web: replaced by nethserver-cgp
* nethserver-password: integrated inside nethserver-sssd
* nethserver-faxweb2: http://community.nethserver.org/t/ns-7-faxweb2-vs-avantafax/2645
* nethserver-fetchmail: replaced by getmail
* nethserver-ocsinventory, nethserver-adagios: due to compatibility problems with Nagios, these modules will be 
  mantained only on |product| 6.x release

