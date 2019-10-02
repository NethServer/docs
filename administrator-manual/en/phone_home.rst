.. _phonehome-section:

==========
Phone Home
==========

Phone home is used to track all |product| installations around the world.
Each time a new |product| is installed, this tool sends some installation details to a central server. 
The information is stored in a database and used to display the number of installations grouped by country and release: https://www.nethserver.org/phone-home/index.html

The phone home is enabled by default and it sends the following data:

 * UUID stored in ``/var/lib/yum/uuid``
 * RELEASE from ``/sbin/e-smith/config getprop sysconfig Version``

Disabling
=========

The phone home can be disabled from command line.
Just run the following command in a root shell: ::

  config setprop phone-home status disabled


