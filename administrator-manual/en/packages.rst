===============
Package manager
===============

The main view shows a list of software components. Checked items represents
installed components, while unchecked items are the available ones. You can
filter the list by category.

.. NOTE::

    Both components and categories are defined by YUM metadata.

To install or remove the listed software components, change the
checkbox states then click the :guilabel:`Apply` button. The next
screen summarizes what is going to be installed and removed. Also, a
list of optional packages is shown, to be selected for
installation.

.. NOTE:: 
    
   Optional packages can be installed also *AFTER* the installation of
   the relative component: click the :guilabel:`Apply` button again
   and select them from the summary screen.

Installed software
==================

It lists |product| RPM packages installed on your system.  Where
available, it is possible to open the development page by clicking on
the package name.

Packages are sorted alphabetically. Displayed fields are:

Name
    Name of the RPM package.

Version
    Version of the installed package.

Release
    Release of the installed package.
