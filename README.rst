========================
NethServer documentation
========================

Sphinx documentation sources for docs.nethserver.org_.

The docs sources are under ``administrator-manual/en/`` directory.  You can find
only English (en) here because translated paragraphs are handled by Transifex.
Under the same directory there are some specials files:

* conf.py: Sphinx configuration
* Makefile: Sphinx build makefile
* index.rst: document structure

All other ``.rst`` files are chapters of the manual.  If you wish to add a new
chapter, create a new file and add it to the index.rst file.

Documentation available here:

* Administrator manual: http://docs.nethserver.org
* Developer manual: http://docs.nethserver.org/projects/nethserver-devel

.. _www.nethserver.org: http://www.nethserver.org

How to contribute
=================

The easiest way to contribute is by forking and editing the repository 
directly on GitHub:

* Create a GitHub account if you don't already have it
* Go to https://github.com/NethServer/docs and fork the project
* You can now edit any page using GitHub web interface and see a live preview of the output
* When you're done, simply create a new pull request
* A new automatic build is launched after the pull request is merged by a developer

You can also use the traditional way by cloning the ``docs``
repository (https://github.com/nethesis/nethserver-docs ) to your
machine and sending patches to the mailing list.

While editing, please follow the guidelines below.

Editing guidelines
------------------

The document must start with a title such as ::

    ==============
    Document title
    ==============

Make sure to add only *one* first-level title for each rst file.

Next headers levels are::

    First level
    ===========

    Second level
    ------------

    Third level
    ^^^^^^^^^^^

    Fourth level
    ~~~~~~~~~~~~


To create cross-references set a label before headers, with ``-section`` suffix::

    .. _mytitle-section:

    My title
    --------

In other documents refer to "My title" with the ``:ref:`` command::
    
    More informations are explained on :ref:`mytitle-section`
    

Use the \* character for unordered list ::
 
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

Highlight important words ::
   
    This is and *important* word.
    
Add notes with ::
    
    .. note:: Highlight this text

Add warnings with ::

    .. warning:: Warning text fragments


    
You can find more info about **RST Inline Markup** here: rst-cheatsheet_

.. _rst-cheatsheet: https://github.com/ralsina/rst-cheatsheet/blob/master/rst-cheatsheet.rst
 

Do not use *NethServer* name inside documentation. Any time you need to add the product name, 
use the *product* macro::

  |product| has this amazing feature!

Output will be::

  NethServer has this amazing feature!

The same applies to *download_site* macro.

Use semantic markup whenever possible. Recommended RST roles are:

* guilabel
* file
* command
* menuselection

Remember to emphasize system object with *:dfn:*, only the first time you mention them inside a section.
For example if you are naming a system user::

 The :dfn:`admin` user is mighty powerful.

Also take care of indexing important content. You must index a word only one time per section::
 
 The :dfn:`admin` user is mighty powerful.
 Remember to change the :index:`admin` password.

The output will be a paragraph where the first *admin* word will be italic, the latter will use standard font
but it will be indexed.

See also: http://sphinx-doc.org/markup/inline.html

Use a spell checker program before submitting a pull request. For instance run ::

  hunspell -d en_US <filename>

Conditional sections
--------------------

You can use the ``only`` tag to include some sections inside
only inside the community or enterprise manual.

Use this syntax: ::

  .. only:: <tag>

     my conditional text

Where ``tag`` can be:

* ``nscom`` for community manual
* ``nsent`` for enterprise manual

Pushing translations
====================

After any commit, remember to push the new strings
to Transifex: ::

  make gettext
  tx push -s


Build documentation
===================

Whenever there are modifications, a build process will be launched from Read the Docs site.

If you wish to build documentation locally on your machine, make sure to install all Sphinx packages.

On Fedora 24 or later use: ::

  sudo dnf install python2-sphinx python2-sphinx-bootstrap-theme

Then, install all required modules: ::

  sudo pip install -f ./administrator-manual/en/nsent/requirements.txt


First clone the repository, enter language directory and type ::

   make html

Output files will be generated inside the *_build* directory.

To specify an alternative configuration (i.e. ``nsent``) type ::

   make SPHINXOPTS="-t nsent" html
   
Localization workflow
---------------------

To submit the English manual version to Transifex run: ::

    make gettext && tx push -s

When the resources has been translated on Transifex run: ::

    tx pull -a

To build a localized manual (for instance, Italian): ::
    
    make -e SPHINXOPTS="-D language='it' -t nscom" html

Substitute ``nscom`` with ``nsent`` or any other tag corresponding to a 
*documentation spin*.

Remember to **commit any change** to ``.po`` files (also newly added files), and
push commits to GitHub.  The ReadTheDocs build is triggered automatically.

When creating new rst files, remember also to add them as new 
resources to Transifex by manually editing ``.tx/config``.

Upgrading developer manual
==========================

Developer manual is now hosted at https://github.com/NethServer/dev