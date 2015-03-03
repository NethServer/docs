=============
Release notes
=============

Changes
=======

* At first login after system installation, the server-manager displays a *First
  Configuration wizard*, where the administrator ("root" user) can set its password, change
  the host name, select the timezone and tune other security related settings.

* The :guilabel:`Package manager` page has been renamed
  :guilabel:`Software center`, and moved to the *Administration*
  section.  To enhance the page usability, two separate tabs show
  respectively *Available* and *Installed* modules.  It is now possible
  to update the installed packages and read the updates changelog.
  
* A new page, :guilabel:`Server certificate` shows the self-signed
  SSL certificate and allows generating a new one, customizing also
  the *alternative names* of the server.  As a consequence, changing the
  host name from the :guilabel:`Server name` page does not generate a
  new SSL certificate any more.  The same applies for the
  :guilabel:`Organization contacts`.

* Added :ref:`phonehome-section` to collect limited usage statistics. Phone home is disabled
  by default.

* The :guilabel:`Remote access` page has been removed. Access to the
  *server-manager* is now controlled from :guilabel:`Network services`
  page, service :guilabel:`httpd-admin`.

* Secure Shell (SSH) access is configured from the new :guilabel:`SSH`
  page.
  
* The following sections has been removed from interactive installer:
  root password, filesystem encryption, keyboard selection, time zone selection.
  See :ref:`installation-interactive` and :ref:`installation-unattended`.
  These options can now be configured using the *First
  Configuration wizard*.

* Some new packages are installed by default to help troubleshooting: bind-utils, traceroute, tmpwatch.

* If ``nethserver-mail-filter`` and ``nethserver-firewall-base`` are both installed 
  (gateway mode), port 25 is blocked from green and blue zones. See :ref:`email-port25`.

* The ``php/DateTimezone`` prop value is now controlled from
  :guilabel:`Date and time` page, that already sets the system time zone.
  If the system-wide value is not valid for the PHP INI
  ``date.timezone`` parameter, the default ``UTC`` is set instead.

Upgrading from 6.5
==================

The system upgrade should be started from the command line shell.

Make sure the system is fully updated: ::

  yum update

Since repository configuration is changed, remove the old configuration file: ::

  rm -f /etc/yum.repos.d/NethServer.repo

Then, start the upgrade: ::

  yum -c http://pulp.nethserver.org/nethserver/nethserver-6.6.conf update

Things that can be tweaked:

* Upgrade the default PHP timezone (``date.timezone`` INI setting)
  from system default:
  
  1. In :guilabel:`Date and time` page change the :guilabel:`Timezone`
     to a temporary value and click :guilabel:`Submit` button.

  2. Set the :guilabel:`Timezone` to the original value and click
     :guilabel:`Submit` again.
  	      
Finally, reboot the system.

