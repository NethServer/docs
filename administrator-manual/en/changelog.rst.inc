Changes
=======

This is the first official release of |product| 7.
Starting from this release, any installation will be upgradable to the final release.

A complete list fo changes can be found here:

* https://www.nethserver.org/the-street-towards-nethserver-7-beta-1/

Discontinued packages
---------------------

The following packages have been removed:

* nethserver-collectd-web: replaced by nethserver-cgp
* nethserver-password: integrated inside nethserver-sssd
* nethserver-faxweb2: http://community.nethserver.org/t/ns-7-faxweb2-vs-avantafax/2645
* nethserver-fetchmail: should be replaced by getmail in the near future (https://github.com/NethServer/dev/issues/5021)
* nethserver-ocsinventory, nethserver-adagios: due to compatibility problems with Nagios, these modules will be 
  mantained only on |product| 6.x release
