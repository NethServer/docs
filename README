========================
NethServer documentation
========================

Sphinx documentation sources for www.nethserver.org_.

You can find a directory for each available language.
Inside each language directory there are some specials files:

* conf.py: Sphinx configuration
* Makefile: Sphinx build makefile
* index.rst: document structure

All other .rst files are chapters of the manual. 
If you whish to add a new chapter, create a new file and add it to the index.rst file.

Documentation can be read at: nethserver.readthedocs.org_

.. _nethserver.readthedocs.org: http://nethserver.readthedocs.org
.. _www.nethserver.org: http://www.nethserver.org

How to contribute
=================

Fork the project, edit and make pull requests!

While editing, please follow below guidelines.

Editing guidelines
------------------

The document must start with a title such as ::

    ==============
    Document title
    ==============

Next headers levels are::

    First level
    ===========

    Second level
    ------------

    Third level
    ^^^^^^^^^^^

    Fourth level
    ~~~~~~~~~~~~

Use the \* character for unorderd list ::
 
    * First element
    * Second element

Use a definition list when describing fields ::

    My field
        This is my description

A field description can also contain a bullet list ::

    My field
        This is my description

        * First element
        * Second element

Highligt important words ::
   
    This is and *important* word.

Build documentation
===================

Whenever there are modifications, a build process will be launched from Read the Docs site.

If you whish to build documentation locally on your machine, make sure to install all Sphinx packages.

First clone the repository, enter language directory and type ::

   make html

Output files will be generated inside the *_build* directory.
