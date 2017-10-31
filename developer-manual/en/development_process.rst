===================
Development process
===================

Issues
======

An issue is a formal description of a known problem, or desired
feature, inside a tracker. There are two kind of issues:

Bug
  describes a defect of the software; it must lead to a
  resolution of the problem. For example, a process crashing under certain
  conditions.

Feature/Enhancement
  describe an improvement of the current code or an entire new
  feature. For example, remove an harmless warning of a running process or
  designing a new UI panel.

Bugs and enhancements will always produce some code changes inside one or more
git repositories.

Each repository is associated to one or more RPM packages. Changes to the code
produce new releases of RPM packages.


Do I need to open a new issue?
------------------------------

Yes, if what you’re talking about will produce some code.
By the way, it’s perfectly reasonable not to fill issues for
occasional small fixes, like typos in translations.

Issues are not a TODO list. Issues track the status changes of a job, the
output of the job will be a new RPM implementing the issue itself.
If you are exploring some esoteric paths for new feature or hunting
something like an `heisenbug <http://en.wikipedia.org/wiki/Heisenbug>`__
, please write a draft wiki page with your thoughts, then create a new
issue only when you’re ready to write a formal description and produce
some output object.

A process for a new feature, should be something like this:

* Open a new topic on http://community.nethserver.org and discuss it.
* If the feature is complex, a dedicated wiki page could be written on 
  https://github.com/NethServer/dev/wiki (or http://wiki.nethserver.org/).

  * Create a wiki page with notes and thoughts (team contributions are welcome!).
  * If the wiki page is a feature design document, the feature can
    simply point to the wiki page.
  * The wiki page should become a changelog for a new release.
  * When the wiki page is pretty “stable” and the whole thing is well
    outlined, a team member will create one or more new issues.

* Open the issue on GitHub https://github.com/NethServer/dev/issues/new.

Feature planning is kept inside https://github.com/orgs/NethServer/projects/.
For any new feature, create a new card under the *Future* column.
The card should contain a brief description of the feature, the link to the discussion
and eventually links to related wiki page and issue.

At any point in time, make sure the card and the issue reflect the status of actual work.

Writing issues
--------------

How to write a bug report:

* Apply the **bug** label
* Point to the right software component with the associated version
* Describe the error, and how to reproduce it
* Describe the expected behavior
* If possible, suggest a fix or workaround
* If possible, add a piece of system output (log, command, etc)
* Text presentation matters: it makes the whole report more readable
  and understandable

How to write a feature or enhancement:

* Everybody should understand what you’re talking about: describe the
  feature with simple words using examples
* If possible, add links to external documentation
* Text presentation matters: it makes the whole report more readable
  and understandable

More information:

* https://developer.mozilla.org/en-US/docs/Mozilla/QA/Bug_writing_guidelines
* http://fedoraproject.org/wiki/Bugs_and_feature_requests
* http://fedoraproject.org/wiki/How_to_file_a_bug_report

Issue priority
--------------

Bugs should always have priority over features.

The priority of a bug depends on:

* security: if it's a security bug, it should have maximum priority
* number of affected users: more affected users means more priority


Issue tracker
-------------

The NethServer project is hosted on GitHub and is constituted by many git
repositories.  We set one of them to be the issue tracker:

https://github.com/NethServer/dev

Issues created on *dev* help coordinating the development process, determining
who is in charge of what.

Developer
^^^^^^^^^

The *Developer*.

* Sets the *Assignee* to himself.

* Bundle his commits as one or more GitHub *pull requests*, reporting the
  issue number reference on them (see also `Commit message style guide`_).

* For *enhancements*, writes the test case (for *bugs* the procedure to
  reproduce the problem should be already set).

* Writes and updates the `Documentation`_ associated with the code.

* Finally, clears the *Assignee*.

If the issue is not valid, it can be closed adding one of the labels **invalid**,
**duplicate**, **wontfix**.


QA team member (testing)
^^^^^^^^^^^^^^^^^^^^^^^^

The *QA team member*.

* Takes an unassigned issue with label **testing** and sets the *Assignee* field
  to him/herself.

* Tests the package, following the test case documentation written by the
  *Developer*.

* When test finishes he/she removes the **testing** label and clears the *Assignee*
  field.  If the test is *successful*, he/she sets the **verified** label,
  otherwise he/she alerts the *Developer* and the *Packager* to plan a new
  process iteration.


Packager
^^^^^^^^

The *Packager* coordinates the *Developer* and *QA member* work.  After the
*Developer* opens one or more pull requests:

* Selects issues with open pull requests

* Reviews the pull request code and merges it

* Builds and uploads the RPMs to the *testing* repository
  and sets the **testing** label (see :ref:`buildrpm-section`)

After the *QA member* has completed the testing phase:

* Takes an unassigned issue with label **verified**

* Commits a *release tag* (see `Building RPMs`_).

* Re-builds the tagged RPM.

* Uploads the RPM to *updates* (or *base*) repository.

* Pushes the *release tag* and commit to SCM

* Closes the issue, specifying the list of released RPMs

When the package is CLOSED, all related `documentation`_ must be in place.

RPM Version numbering rules
===========================

NethServer releases carry the version number of the underlying CentOS.
For example ``NethServer 7 beta1`` is based on ``CentOS 7``.

Packages have a version number in the form **X.Y.Z-N** (Eg.
``nethserver-myservice-1.0.3-1.ns7.rpm``):

* X: major release, breaks retro-compatibility
* Y: minor release, new features - big enhancements
* Z: bug fixes - small enhancements
* N: spec modifications inside the current release - hotfixes

Commit message style guide
==========================

Individual commits should contain a cohesive set of changes to the code. These
`seven rules`_ summarize how a good commit message should be composed.

1. Separate subject from body with a blank line
2. Limit the subject line to 50 characters
3. Capitalize the subject line
4. Do not end the subject line with a period
5. Use the imperative mood in the subject line
6. Wrap the body at 72 characters
7. Use the body to explain what and why vs. how

.. _`seven rules`: http://chris.beams.io/posts/git-commit/#seven-rules

Documentation
=============

The developer must take care to write all documentation on:

* wiki page during development
* Developer Manual and/or README.rst before release
* Administrator Manual before release
* Inline help before release

Packages should be inside the *testing* or *nethforge-testing* repositories until 
all documentation is completed.

New packages
============

Before creating a new package, make sure it's a good idea. Often a simple
documentation page is enough, and it requires much less effort. When trying new
things, just take care to write down on a public temporary document (maybe a
wiki page) all steps and comments. If the feature collects many requests, it's
time to think about a new package. Otherwise, the temporary document can be
moved to a manual page.

When creating a new package, make sure the following requirements are met:

* Announce it on http://community.nethserver.org
* Create an issue describing the package
* Create a personal repository on GitHub
* Add a GPL license and copyright notice in the COPYING file
* Add a README.rst file, with developer documentation
* If needed, create a pull request for the NethServer/comps or NethServer/nethforge-comps repository,
  to list the package in the Software center page.
* Build the package and push it to *testing* or *nethforge-testing* repository

See also :ref:`buildrpm-section`.

Package updates
===============

Updates to RPM packages must obey the following rules:

* New features/enhancements and bug fixes must not alter the behavior of
  existing systems

* New behaviors must be enabled by an explicit and documented sysadmin operation

* RPM packages must support updates from any previous release of the same branch


Minor release from upstream
---------------------------

On every upstream (CentOS) minor release, the QA team should check the following
hot points before clearing the way to the new release:

- Samba: authenticated access to file shares

- Mail server 
  
  - sending and receiving mail
  - antivirus filter on received mail

- Groupware

  - basic mail features
  - access to calendars and contacts

- Web proxy

  - web access with transparent proxy
  - antivirus filter on using EICAR test

- Web applications (eg. NextCloud)

- Asterisk with dahdi kernel modules and FreePBX 

.. _iso-releases-section:

ISO releases
============

Usually, the NethServer project releases a new ISO image in the following cases:

* when the upstream project releases a new ISO image. The NethServer ISO is
rebased on it.

* when packages bundled in the ISO receive new features that affect the
installation procedure and/or the initial system configuration.

The NethServer ISO is almost equivalent to the upstream one, except for the
following points:

* Additional boot menu options and graphics

* Additional Anaconda kickstart scripts and graphics

* Additional RPMs from the NethServer project

See also :ref:`buildiso-section`.

Pre-releases
------------

Before any **final** ISO release, the software development process goes through
some test versions, usually called alpha, beta and release candidate (RC). These
releases are an excellent way to experiment with new features, but may require
some experience using a Linux system and/or the command line.

**Alpha** releases are not ready to be used in production because some features
are not finished, furthermore upgrade to the final release will not be supported
(but may be possible).

**Beta** releases could be used in production, especially if new features are
not used on mission critical systems. Upgrades to the final release is
supported.

**Release candidates** (RC) can be run in production, all features are supposed
to be complete and bug free. The upgrade to the final release will be minor
or less.


