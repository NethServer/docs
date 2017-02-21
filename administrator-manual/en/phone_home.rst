.. _phonehome-section:

==========
Phone Home
==========
During the first configuration wizard, you can opt-out from contributing to usage statistics.
Phone home is used to track all NethServer's installations around the world. Each time a new NethServer is installed, this tool sends some installation details to a central server. The information is stored in a database and used to display nice markers in a Google Map view with number of installation grouped by country and release.

Overview
========
The tool is *enabled* by default.

To disable it at a later time, run: ``config setprop phone-home status disabled``

If phone home is *enabled* the details sent are:
 * UUID: stored in ``/var/lib/yum/uuid``
 * RELEASE: from ``/sbin/e-smith/config getprop sysconfig Version``

All the data is used to populate the map.
