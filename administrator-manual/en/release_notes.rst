=============
Release notes
=============

Changes
=======

* Always login as ``root``! The passwords of ``root`` and ``admin``
  users are no longer synchronized.  The ``AdminIsNotRoot`` DB key has
  been removed.

  The ``admin`` user name is available only if
  ``nethserver-directory`` RPM is installed. For backward
  compatibility it has still full privileges through Server Manager.

  When ``nethserver-directory`` is installed ``admin`` is
  automatically created, as in the past, but its Unix password is not
  copied from ``root`` any more.

* At first login after system installation, the *Server Manager* displays a *First
  Configuration wizard*, where the administrator (``root`` user) can set its password, change
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
  *Server Manager* is now controlled from :guilabel:`Network services`
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

Upgrading from 6.5
==================

The system upgrade should be started from the command line shell.

Make sure the system is fully updated: ::

  yum update

Since repository configuration is changed, remove the old configuration file: ::

  rm -f /etc/yum.repos.d/NethServer.repo

Then, start the upgrade: ::

  yum -c http://pulp.nethserver.org/nethserver/nethserver-6.6.conf update

Finally, reboot the system.
