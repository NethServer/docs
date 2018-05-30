.. _package_manager-section:
.. _software-center-section:

===============
Software center
===============

|product| is highly modular: at the end of the installation a bare minimum set
of features like *network configuration* and *log viewer* is installed. The
:guilabel:`Software center` page allows the administrator to select and
**install** additional  :dfn:`modules`, and also list and **update** the already
installed software :dfn:`packages`.

A *module* is usually constituted by multiple *packages*. It extends the system
functionality. For instance a module can transform |product| into an Email
server, or a Web proxy.

A software *package* is an atomic unit of software. It is published by a public
software repository. |product| packages are files in the RPM [#RPM]_ file
format. Thus within this context the terms *package* and *RPM* can be used as
synonyms.

.. _software-updates-section:

Software updates
================

.. only:: nsent

    |product| receives controlled updates from a set of managed software
    repositories. See :ref:`automatic-updates` to receive new features and
    fix bugs and security issues.

.. only:: nscom

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
    NethServer directly from the CentOS mirrors. More info about CentOS updates:

    - https://wiki.centos.org/FAQ/General
    - https://access.redhat.com/support/policy/updates/errata/
    - https://access.redhat.com/security/updates/backporting
    - https://access.redhat.com/security/

    Updates released by EPEL are available only if the **unlocked** software
    updates origin is selected, as explained below.

    .. hint::

        Even if the above projects strive for software stability, care is
        necessary to check if the updates fit well together. Every time the
        system is going to be updated, **create a backup of the data and review
        the updates changelog** to understand what is going to happen. If
        possible, test the updates in a non-production system. For any doubt ask
        the NethServer community forum! [#NSCOM]_

    Every day an **automated scheduled task** checks if a new distribution
    release of CentOS is available; when this happens it sends an email
    notification message to the system administrator and changes the
    :guilabel:`Software updates origin`. The system administrator can
    temporarily change the software updates origin from :guilabel:`Software
    center > Configure`. The available choices are:

    :dfn:`Unlocked` (default)

        The Software center considers updates from all available software
        repositories. It ensures every installed package is at its latest
        version.

        The "unlocked" origin is automatically selected by the :dfn:`system
        upgrade` procedure that can be started only by the system administrator.

    :dfn:`Locked`

        The Software center prevents to install the updates coming from a CentOS
        release different than the current system version. For example, it
        prevents to install updates from CentOS 7.6 if NethServer version is
        7.5. Packages from other repositories which are generically compatible
        with "7" (like EPEL) are considered only when new modules are installed;
        once they have been installed they are never updated.

        The "locked" origin is automatically selected when a new CentOS
        distribution release is available. When also the NethServer project
        releases a new version, the Software center asks to start the
        :dfn:`system upgrade`. The upgrade procedure switches to the "unlocked"
        origin at the end.

        .. warning::

            When ``yum`` is run from the command line and the software origin is
            "locked", EPEL and other repositories which are generically
            compatible with "7" are **enabled**

.. _manual-updates:

Manual update procedure
^^^^^^^^^^^^^^^^^^^^^^^

When updates are available, a warning message appears in the :guilabel:`Software
center` page.

Updates for the installed software are listed under the :guilabel:`Updates` tab.
Further details about them are available under :guilabel:`Updates CHANGELOG`.

To start the system update click the :guilabel:`Download and install` button.

.. only:: nscom

    .. hint::

        Regularly update the installed software to fix bugs, security issues and
        receive new features


.. _automatic-updates:

Automatic update procedure
^^^^^^^^^^^^^^^^^^^^^^^^^^

It is possible to perform some automatic actions when new software updates are available. 

* Download and (optionally) install the updates

* Send an email to the system administrator (root) and to an additional list of recipients

The updates availability is checked by a task that runs at a random time overnight.

.. hint::

    If the notification email is not delivered or is marked as spam, it is
    possible to configure a  :ref:`smarthost <smarthost-configuration>`


Modules installation
====================

The :guilabel:`Available` tab lists all of the modules that can be installed.
This list can be filtered by category. See also :ref:`additional-languages`.

To **install a module**, check the corresponding box and click on
:guilabel:`Add`. Some modules suggest optional packages that can be installed
also at a later time.

Once a module has been installed, it is listed under the :guilabel:`Installed` tab.

To **install optional packages** at a later time, select :guilabel:`Installed`
tab and push the :guilabel:`Edit` button on a listed entry.

.. only:: nscom

    To **remove a module**, go to the :guilabel:`Installed` tab and push the
    corresponding :guilabel:`Remove` button.

    .. warning::

        When removing a module other modules could be removed, too! Read carefully
        the list of affected packages to avoid removing required features.

.. only:: nsent

    .. warning::

        Installed packages **cannot be removed from the Software Center!**
        Please contact customer support if you need to remove an installed module.

.. index::
    pair: RPM; installed
    pair: packages; installed

List of installed packages
^^^^^^^^^^^^^^^^^^^^^^^^^^

The complete list of installed RPM packages is available under
:guilabel:`Installed > Packages`.

The section :guilabel:`Installed software` displays all packages already
installed into the system with the full package version.

.. _additional-languages:

Additional languages
^^^^^^^^^^^^^^^^^^^^

The Server Manager allows selecting the interface language at the login screen.
Only installed languages are listed.

In :guilabel:`Available` tab, select the :guilabel:`Languages` category and install
the desired languages.


.. rubric:: References

.. [#RPM] RPM Package Manager -- http://rpm.org
.. [#NETHSERVER] NethServer -- http://www.nethserver.org
.. [#CENTOS] CentOS -- Community ENTerprise Operating System https://www.centos.org/
.. [#EPEL] EPEL -- Extra Packages for Enterprise Linux https://fedoraproject.org/wiki/EPEL

.. only:: nscom

   .. [#NSCOM] NethServer community forum -- http://community.nethserver.org