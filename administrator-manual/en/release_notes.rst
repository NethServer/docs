=============
Release notes
=============

Changes
=======

* Following sections has been removed from interactive installer:
  root password, filesystem encryption, keyboard selection, time zone selection.
  See :ref:`installation-interactive` and :ref:`installation-unattended`.
  These options can now be configured using the *First
  Configuration wizard*.

* New packages installed by default: bind-utils, traceroute, tmpwatch.

* After system installation, the server-manager shows the *First
  Configuration wizard*, where the admin can set the password, change
  the host name and so on.

* The :guilabel:`Remote access` page has been removed. Access to the
  *server-manager* is now controlled from :guilabel:`Network services`
  page, service :guilabel:`httpd-admin`.

* Secure Shell (SSH) access is configured from the new :guilabel:`SSH`
  page.
  
* The :guilabel:`Package manager` page has been renamed
  :guilabel:`Software center`, and moved to the *Administration*
  category.  To enhance the page usability, now two separate tabs show
  respectively *Available* and *Installed* modules.  It is now possible
  to update the installed packages, and read the updates changelog.
  
* The new page, :guilabel:`Server certificate` shows the self-signed
  SSL certificate and allows generating a new one, customizing also
  the *alternative names* of the server.  As consequence, changing the
  host name from the :guilabel:`Server name` page does not generate a
  new SSL certificate any more.  The same applies for the
  :guilabel:`Organization contacts`.

* Added phone home to collect usage statistic. Phone home is disabled
  by default.

* If ``nethserver-mail-filter`` and ``nethserver-firewall-base`` are both installed 
  (gateway mode), port 25 is blocked from green and blue zones. See :ref:`email-port25`.

Upgrading from 6.5
==================

The system upgrade can be done using the shell.

Make sure the system is fully updated: ::

  yum update

Then, start the upgrade: ::

  yum update --releasever=6.6

At the end, reboot the system.
