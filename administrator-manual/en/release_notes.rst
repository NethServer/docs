=============
Release notes
=============

|product| release |release|

.. include:: changelog.rst.inc
  
Upgrading from 6.6
==================

The system upgrade should be started from the command line shell.

1. Make sure the system is fully updated: ::

     yum update

2. Upgrade the ``nethserver-release`` package: ::

     yum localinstall http://mirror.nethserver.org/nethserver/nethserver-release-6.7.rpm

3. Clean up yum cache and run update again: ::

     yum clean all && yum update 

4. If installed, upgrade the firewall group: ::

     yum update @nethserver-firewall-base 
  	      
5. Finally, reboot the system.


