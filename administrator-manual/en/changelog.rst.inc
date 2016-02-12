Changes
=======

All packages have been rebuilt and adapted to CentOS 7.

The following packages are now part of the default installation:

* HTTP server (nethserver-dnsmasq)
* DNS server (nethserver-httpd)

Core
----

* EPEL repository is now enabled by default
* List of running services has been moved to a new page
* Each service can be started/stoped/restarted pushing a button
* Dashboard tabs have been split into multiple pages under the Status menu
* Data backup destination now supports more storage types (iSCSI, eSATA)
* All services are now controlled by systemd
* UID of user accounts now starts from 1000
* Sudo configuration has been rewritten to be upstream compliant
* Network configuration now uses persistent device naming

  * In case of network hardware changes, if the system can't figure out how to migrate the old configuration,
    a new bridge adapter named *brdef* will be created. The bridge will contain all free interfaces.
    The system administrator is supposed to manually fix the network configuration using the
    server-manager web interface.

Web proxy
---------

The Web proxy statistics (nethserver-ligtsquid) package is installed
by default along with Squid.
The Web filter has now its own clamd instance.
Also the full web filter stack has been updated to latest upstream release:

* c-icap
* squidclamav
* squidGuard


Mail server
------------

The whole stack has been updated, from upstream:

* amavis
* postfix

Also the mail filter stack uses its own clamd instance.


Updated packages
----------------

Many packages have been updated to the latest available release.
The most relevant are:

* Hylafax+ 5.5 from EPEL (fax services are now handled by systemd)
* Roundcubemail 1.1.4
* SOGo 3
* Snort 2.9.8 with support for OpenAppID
* Owncloud 8
* Ejabberd 16 from upstream
* ntopng 2.2
* WebvirtMgr 4.8.9 (KVM virtual machines manager)

Various tweaks
--------------

Minor improvements and bug fixes on the following packages:

* Apache: added a new customized landing page
* LSM: start the link monitor daemon only when multiple WANs are enabled
* OpenVPN: fixed psk configuration when the system is used as client
* OpenSSH: configuration cleanup, enabled EC crypto
* FTP: system users must have a valid shell (SSH access) to login
* IPSec: moved implementation from OpenSwan to LibreSwan, reworked l2tp configuration
* MySQL has been removed in favor of MariaDB, no changes should be needed by any application
* OpenLDAP: configuration cleanup
* NethForge is now part of core packages, so that external contribs can be installed from Software Center
* Server manager: PHP configuration moved to /etc/php.d/nethserver.ini. /etc/php.ini is no longer a template

Integrated apps
---------------

The following web applications are now integrated inside the Server Manager:

* CGP (collectd graphs), installed by default with collectd
* Samba audit
* Lightsquid (web proxy statistics), installed by default with Squid

Discontinued packages
---------------------

The following packages have been removed:

* nethserver-collectd-web: replaced by nethserver-cgp
* nethserver-password: integrated inside nethserver-directory
* nethserver-faxweb2: http://community.nethserver.org/t/ns-7-faxweb2-vs-avantafax/2645
