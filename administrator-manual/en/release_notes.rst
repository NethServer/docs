=============
Release notes
=============

|product| release |release|

.. include:: changelog.rst.inc
  
Manual upgrade from 6.7
=======================

The system can be upgraded from the command line.

1. Make sure the system is fully updated: ::

     yum update

2. Upgrade the ``nethserver-release`` package: ::

     yum localinstall http://mirror.nethserver.org/nethserver/nethserver-release-6.rpm

3. Clean up yum cache and run update again: ::

     yum clean all && yum update 

4. Finally, reboot the system (optional).

