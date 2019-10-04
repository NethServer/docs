.. _package_manager-section:
.. _software-center-section:

===============
Software center
===============

.. note:: For the old Server Manager see :ref:`software_center_legacy-section`.

|product| is highly modular: at the end of the installation a bare minimum set
of features like *network configuration* and *backup* are installed. The
:guilabel:`Software Center` page allows the administrator to select and
**install** additional  :dfn:`applications`, and also list and **update** the already
installed software :dfn:`packages`.

An *application* is usually constituted by multiple *packages*. It extends the system
functionality. For instance a module can transform |product| into an Email
server, or a Web proxy.

A software *package* is an atomic unit of software. It is published by a public
software repository. |product| packages are files in the RPM [#RPM]_ file
format. Thus within this context the terms *package* and *RPM* can be used as
synonyms.

Applications installation
=========================

The :guilabel:`Applications` section lists all modules that can be installed.
This list can be filtered by category.
To **install an application**, check the corresponding box and click on
:guilabel:`Install applications`.

Once a module has been installed, it is listed under the :ref:`applications-section` page.


.. _software-updates-section:

Software updates
================

Enterprise and community subscriptions
--------------------------------------

|product| receives controlled updates from a set of managed software
repositories. See :ref:`automatic-updates` to receive new features and
fix bugs and security issues.

Community without subscription
------------------------------

A NethServer 7 system receives updates from different software projects:

* the NethServer project itself [#NETHSERVER]_
* the CentOS project [#CENTOS]_
* the EPEL repository [#EPEL]_

Each project releases software updates according to its specific rules and
development cycle, but all of them prefer software stability over bleeding
edge features.

Refer to the Community forum [#NSCOM]_ and :ref:`release-notes-section` for
more information about NethServer updates.

Updates released by the CentOS project are immediately available on
|product| directly from the CentOS mirrors. Only updates for the current
system release (i.e. "7.6.1804") are considered, until a manual upgrade to
the next system release is started.

More info about CentOS updates:

- https://wiki.centos.org/FAQ/General
- https://access.redhat.com/support/policy/updates/errata/
- https://access.redhat.com/security/updates/backporting
- https://access.redhat.com/security/

Updates released by EPEL are immediately available from the official EPEL
mirrors. As EPEL is not bound to the current system release number, the
:guilabel:`Software Center` always installs the latest available software
versions from EPEL.

More info about EPEL updates:

- https://fedoraproject.org/wiki/EPEL

.. hint::

     Even if the above projects strive for software stability, care is
     necessary to check if the updates fit well together. Every time the
     system is going to be updated, **create a backup of the data and review
     the updates changelog** to understand what is going to happen. If
     possible, test the updates in a non-production system. For any doubt ask
     the NethServer community forum! [#NSCOM]_

.. _manual-updates:

Manual update procedure
^^^^^^^^^^^^^^^^^^^^^^^

When updates are available, the list of new packages is available under the :guilabel:`Updates` section.

Further details are available clicking the :guilabel:`Changelog` button.

To expand the list of updates, cick on the :guilabel:`Details` button,
you can then update a single |product| package by clicking on the :guilabel:`Update` button.
To start a full system update click the :guilabel:`Update all` button.

.. hint::

   On community machines without any type of subscription,
   remember to regularly update the installed software to fix bugs, security issues and
   receive new features


.. _automatic-updates:

Automatic update procedure
^^^^^^^^^^^^^^^^^^^^^^^^^^

It is possible to perform some automatic actions when new software updates are available.

* Download and (optionally) install the updates

* Send an email to the system administrator (root) and to an additional list of recipients

The updates availability is checked by a task that runs at a random time overnight.
To configure the update policy click on the :guilabel:`Configure` button.

.. hint::

    If the notification email is not delivered or is marked as spam, it is
    possible to configure a  :ref:`smarthost <smarthost-configuration>`



.. rubric:: References

.. [#RPM] RPM Package Manager -- http://rpm.org
.. [#NETHSERVER] NethServer -- http://www.nethserver.org
.. [#CENTOS] CentOS -- Community ENTerprise Operating System https://www.centos.org/
.. [#EPEL] EPEL -- Extra Packages for Enterprise Linux https://fedoraproject.org/wiki/EPEL

.. only:: nscom

   .. [#NSCOM] NethServer community forum -- http://community.nethserver.org
