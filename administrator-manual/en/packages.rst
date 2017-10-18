.. _package_manager-section:
.. _software-center-section:

===============
Software center
===============

|product| is highly modular.  At the end of the installation a bare minimum set
of modules are ready to be used. The basic system includes modules like *network
configuration* and *log viewer*. Additionally, the administrator can install
additional modules, like :ref:`email-section`, :ref:`dhcp-section`, 
:ref:`firewall-section`...

The :guilabel:`Available` tab lists all of the modules that can be installed. 
This list can be filtered by category.

To **install a module**, check the corresponding box and click on :guilabel:`Add`.
Some modules suggest optional packages that can be installed whether at the same or at a
later time.

To **install optional packages** at a later time, select :guilabel:`Installed`
tab and push the :guilabel:`Edit` button on a listed entry. 

.. only:: nscom

    To **remove a module**, push the :guilabel:`Remove` button.

    .. warning::
        
        When removing a module other modules could be removed, too! Read carefully
        the list of affected packages to avoid removing required features.

.. only:: nsent

    .. warning::

        Installed packages **cannot be removed from the Software Center!**
        Please contact customer support if you need to remove an installed module.

.. index::
    pair: RPM; update
    pair: packages; update

.. _software-updates-section:

Software updates
^^^^^^^^^^^^^^^^

Updates for the installed software are listed under the :guilabel:`Updates` tab. A
message appears when software updates are available.

.. only:: nscom

    Updates released from upstream (CentOS) are automatically available on |product|.
    On every minor release of CentOS, for example when updating from 7.3.1611 to 7.4.1708,
    a banner is shown inside the Software Center to inform the user about the new release.
    
    Even if upstream updates can be considered safe, users should check Community forum (https://community.nethserver.org),
    to be informed about new changes.

    More info on upstream updates:

    - https://wiki.centos.org/FAQ/General
    - https://access.redhat.com/support/policy/updates/errata/
    - https://access.redhat.com/security/updates/backporting
    - https://access.redhat.com/security/


    .. hint:: Regularly update the installed software to fix bugs, security issues and receive new features.
    
.. only:: nsent

    .. hint:: Updates will be automatically installed by a scheduled procedure.

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
