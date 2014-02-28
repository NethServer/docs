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

Documentation available here:

* Administrator manual (English and Italian): http://docs.nethserver.org
* Developer manual (English only): http://docs.nethserver.org/projects/nethserver-devel

.. _www.nethserver.org: http://www.nethserver.org

How to contribute
=================

The easiest way to contribute is by forking and editing the repository 
directly on GitHub:

* Create a GitHub account if you don't already have it
* Go to https://github.com/nethesis/nethserver-docs and fork the project
* You can now edit any page using Github web interface and see a live preview of the output
* When you're done, simply create a new pull request
* A new automatic build is launched after the pull request is merged by a developer

You can also use the traditional way by cloning nethserver-docs 
repository (https://github.com/nethesis/nethserver-docs ) to your 
machine and sending patches to the mailing list.

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
    
Add notes with ::
    
    .. note:: Highlight this text

Add warnings with ::

    .. warning:: Warning text fragments


    
You can find mrre info about **RST Inline Markup** here: rst-cheatsheet_

.. _rst-cheatsheet: https://github.com/ralsina/rst-cheatsheet/blob/master/rst-cheatsheet.rst
 

Do not use *NethServer* name inside documentation. Anytime you need to add the product name, 
use the *product* macro::

  |product| has this amazing feature!

Output will be::

  NethServer has this amazing feature!

The same applies to *download_site* macro.



Use semantic markup when possible. Recommended markups are:

* guilabel
* file
* command
* menuselection

See also: http://sphinx-doc.org/markup/inline.html


Build documentation
===================

Whenever there are modifications, a build process will be launched from Read the Docs site.

If you whish to build documentation locally on your machine, make sure to install all Sphinx packages.

First clone the repository, enter language directory and type ::

   make html

Output files will be generated inside the *_build* directory.
