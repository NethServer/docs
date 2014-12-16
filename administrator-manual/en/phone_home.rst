==========
Phone Home
==========
This tool is used to track all NethServer's installations around the world. Each time a new NethServer is installed, this tool sends some installation information through comfortable APIs. The information are stored in database and used to display nice markers in a Google Map view with number of installation grouped by country and release.

Overview
========
The tool is *disabled* by default.

To enable it simply run: ``config set phone-home configuration status enabled``

If the tool is *enabled* the information sent are:
 * UUID: stored in ``/var/lib/yum/uuid``
 * RELEASE: get by ``/sbin/e-smith/config getprop sysconfig Version``

All the infos are used to populate the map.

Configuration
=============
If you use a proxy edit the correct placeholders in file ``phone-home`` stored in ``/etc/sysconfig/`` : ::

 SERVER_IP=__serverip__
 PROXY_SERVER=__proxyserver__
 PROXY_USER=__proxyuser__
 PROXY_PASS=__proxypass__
 PROXY_PORT=__proxyport__