Changes
=======

All packages have been rebuilt and adapted to CentOS 7.

Following packages are now part of default installation:

* nethserver-dnsmasq
* nethserver-httpd

Core
----

* EPEL repository is now enabled by default
* List of running service has been moved to a new page, also added a start/stop/restart button
* Dashboard has been split into multiple pages
* Data backup now supports any kind of storage
* All services are now controlled by systemd
* The e-smith database has been cleanup
* UID of user accounts now starts from 1000
* Sudo configuration has been rewritten
* Network configuration now uses persistent device naming

  * In case of network hardware change, if the system can't figure how to migrate old configuration,
    a new bridged named brdef will be created. The bridge will contain all free interfaces.

Web proxy
---------

Web proxy statistics (nethserver-ligtsquid package) are now installed
by default along with Squid.
Web filter has now its own clamd instance.
Also the full web filter stack has been updated to latest upstream release:

* c-icap
* squidclamav
* squidGuard


Mail server
------------

All stack has been updated ans is now from upstream:

* amavis
* postfix

Also the mail filter stack uses its own clamd instance.


Updated packages
----------------

Altos any packages have been updated to latest available release.
Most relevant are:

* Hylafax+ 5.5 from EPEL: also services are now handled by systemd
* Roundcubemail 1.1.4
* SOGo 3
* Snort 2.3.8 with support for OpenAppID
* Owncloud 8
* Ejabberd 16 from upstream
* ntopng 2.3

Various tweaks
--------------

Minor improvements and bug fixes on following packages:

* Apache: added a new customized landing page
* LSM: start the daemon only when needed
* OpenVPN: fixed psk configuration when the server is used ad client
* OpenSSH: configuration cleanup, enabled EC crypto
* FTP: system users must have a valid shell (SSH access) to login
* WebvirtMgr (KVM virtual machines manager)
* IPSec: moved implementation from OpenSwan to LibreSwan, reworked all l2tp configuration
* MySQL has been removed in favor of MariaDB, no changes should be needed by any application.
* OpenLDAP: configuration cleanup
* NethForge is now part of core packages
* Server manager: PHP configuration moved to /etc/php.d/nethserver.ini. /etc/php.ini is no more a template

Integrated apps
---------------

Following web applications are now integrated inside the Server Manager:

* CGP (collectd graphs), installed by default with collectd
* Samba audit
* Lightsquid (web proxy statistics), installed by default with Squid

Discontinued packages
---------------------

Following packages have been removed:

* nethserver-collectd-web: replaced by nethserver-cgp
* nethserver-password: integrated inside nethserver-directory
* nethserver-faxweb2: http://community.nethserver.org/t/ns-7-faxweb2-vs-avantafax/2645
