Changes
=======

* Shorewall is the new default firewall: it's now possible to create a red interface
  without installing an extra package, the system will be able to NAT and routing
  out of the box. The firewall web interface has been moved to nethserver-firewall-base-ui package.
* Web interface for password policy is now part of nethserver-directory
* Italian language has been removed from ISO, it's now an optional package
* SSLv2, SSLv3 and old insecure ciphers are disabled by default
* Upstream updates from CentOS 6.7
* All updates from 6.6: http://dev.nethserver.org/projects/nethserver/issues?query_id=60
