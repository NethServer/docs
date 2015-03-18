=============
Release notes
=============

.. include:: changelog.rst.inc
  
Upgrading from 6.5
==================

The system upgrade should be started from the command line shell.

1. Make sure the system is fully updated: ::

     yum update

2. Installing ``yum-presto`` should reduce the total download size: ::

     yum install yum-presto

3. Since repository configuration has changed, remove the old configuration file: ::

     rm -f /etc/yum.repos.d/NethServer.repo
  
4. Then, start the upgrade: ::

     yum -c http://mirror.nethserver.org/nethserver/nethserver-6.6.conf update

5. Things that can be tweaked:

   * Upgrade the default PHP timezone (``date.timezone`` INI setting)
     from system default:
  
     1. In :guilabel:`Date and time` page change the :guilabel:`Timezone`
	to a temporary value and click :guilabel:`Submit` button.

     2. Set the :guilabel:`Timezone` to the original value and click
	:guilabel:`Submit` again.
  	      
6. Finally, reboot the system.


Updating 6.6 beta1
==================

YUM repository URLs has changed. Before updating the system download
the new YUM configuration: ::

  curl https://raw.githubusercontent.com/nethesis/nethserver-release/6.6-0.9/root/etc/yum.repos.d/NethServer.repo > /etc/yum.repos.d/NethServer.repo

