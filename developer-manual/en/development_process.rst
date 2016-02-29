===================
Development process
===================

Issues
======

An issue is a formal description of a known problem, or wished
feature, inside a tracker. There are 4 types of issue:

* **Bug**: describe a defect on the software, it must lead to a
  resolution of the problem. For example, a process crashing under certain
  conditions
* **Feature**: describe a new wished function inside the software.
  For example, a new GUI interface to configure user preferences
* **Enhancement**: describe a small improvement of current code or
  features. For example, remove harmless warning of a running process
* **Task**: describe a generic task not strictly related to source
  code. For example, a document about a new feature

Bugs, features and enhancements will always produce a commit inside a
SCM repository and/or a new software package (typically RPM) containing
the new code.
Developer *must take care* to link commits to code reporting the
commit inside the issues, and the issue number inside the commit
comment.
All released packages must contain a list and a description of related
closed issues.

Do I need to open a new issue?
------------------------------

Yes, if what you’re talking about will produce some code.
By the way, it’s perfectly reasonable to not fill issues for
occasional small fixes, like typos in translations.

Issues are not TODO list. Issues track status changes of a job, to
output of the job will be a new object implementing the issue itself.
If you are exploring some esoteric paths for new feature or hunting
something like an `heisenbug <http://en.wikipedia.org/wiki/Heisenbug>`__
, please write a draft wiki page with your thoughts, then create a new
issue only when you’re ready to write a formal description and produce
some output object.

A process for a new feature, can be something like this:

* Make informal discussion using small meetings or ML discussions
* Create a wiki page with notes and thoughts (team contributions are welcome!)
* When the wiki page is pretty “stable” and the whole thing is well
  outlined, a team member will create one or more new issues.
* If the wiki page is a feature design document, the feature can
  simply point to the wiki page
* The wiki page should become a technical documentation of the
  feature, or a changelog for a new release

At any point in time, make sure the issue status reflects actual work.

Writing issues
--------------

How to write a bug report:

* Point to the right component with the associated version
* Describe the error and the expected behavior
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

Issue status
------------

Issues can have multiple states. Each state should be handled by a person who fit in the below roles.
Of course, one person can wear one or more roles.

See also the `workflow
figure <https://fedoraproject.org/wiki/BugZappers/BugStatusWorkFlow>`__
on FedoraProject.org.

Triager
^^^^^^^

The *Triager* handles all issues in NEW state. She 

* collects missing info, setting the NEEDINFO flag

* sets state to TRIAGED when the issue is clear enough and all
  requirements are discovered.

If the issue is a *Bug*, she can also change the status to CLOSE and
set resolution: DUPLICATE, INSUFFICIENT_DATA, NOTABUG. Additional
infos are appreciated.  If the issue is NOT a *Bug*, sets the generic
REJECTED resolution, specifying the reason in a comment.


Developer
^^^^^^^^^

The *Developer* 

* Takes a TRIAGED issue and put it ON_DEV setting the *Assignee* to himself,

* Writes test cases, optionally annotating RPM changelog message for Packager, or 

* Writes and updates the documentation associated with the code.

* Finally pushes the code/docs changes to SCM 

* Changes the issue state to MODIFIED, resetting the *Assignee*.

If the issue is a *Bug*, he can change the status to CLOSE and specify
a *Resolution*: CANTFIX, WONTFIX, WORKSFORME, CURRENTRELEASE,
NEXTRELEASE, UPSTREAM. Additional infos are appreciated. If the issue
is NOT a *Bug*, specify the generic REJECTED resolution, specifying
the reason in a comment.


Packager
^^^^^^^^

The *Packager*:

* Pulls changes from SCM and builds the RPM. 

* Uploads the RPM to the *testing* repository. 

* Changes state from ON_DEV to ON_QA, specifing the RPM file name and
  yum repository name in the issue comment.

* Takes care to write a test case (or ask to a developer), if the test case is missing.

When the package is VERIFIED from the QA team, the *Packager* 

* Commits a *release tag* (using ``release-rpm`` command from ``nethserver-mock``).

* Re-builds the tagged RPM.

* Uploads the RPM to *updates* (or *base*) repository. 

* Checks ``yum update`` works fine then pushes the tagged commit to SCM. 

* Finally, sets state to CLOSED (with blank *Resolution* field),
  adding a comment to the issue, containing the RPM file name and the
  yum repository name where to find the package.

When the package is CLOSED, all related documentation must be in place.


QA team member
^^^^^^^^^^^^^^

The *QA team member* 

* Takes an unassigned issue ON_QA state and sets the *Assignee* field to herself. 

* Tests the package, following the test case documentation written by the *Developer* 

* She can set NEEDINFO flag if informations about how to test the code are missing. 

* When test is passed she sets the issue state to VERIFIED, otherwise
  she puts it back in TRIAGED state cleaning the *Assignee* field.


Version numbering rules
=======================

NethServer releases bring the version number of the underlying CentOS.
For example ``NethServer 6.4 beta1`` is based on ``CentOS 6.4``.

Packages have a version number in the form **X.Y.Z-N** (Eg.
``nethserver-myservice-1.0.3-1.ns6.rpm``):

* X: major release, breaks retro-compatibility
* Y: minor release, new features
* Z: bug fixes/enhancements
* N: spec modifications inside the current release

Commit message style guide
==========================

Commit messages *must* include four components

* WHERE 
* WHAT
* WHY #Num (see http://www.redmine.org/projects/redmine/wiki/RedmineSettings#Referencing-issues-in-commit-messages)
* WHY Name

See also jQueryUI Commit message style guide: http://contribute.jquery.org/commits-and-pull-requests/#commit-guidelines.


Example:

 git commit createlinks -m "createlinks: add nethserver-myserver event. Refs #1234"

Refs links the commit to a Redmine issue.


Documentation
=============

The developer must take care to write all documentation on:

* wiki page during development
* Developer Manual before release
* Administrator Manual before release
* Inline help before release

Packages should be inside testing repositories untile all documentation is completed.

ISO releases
============

#. An ISO release starts whenever a target version is reached
#. Search for all new RPMs in nethserver-dev repository and select
   stable packages ready for production
#. Rebuild each selected package and publish it to nethserver-testing
   repository
#. Test new RPMs in existing machine and in a new freshly installed one
#. If all test pass, move RPMs to repository nethserver-update
#. Build the new ISO 

See :ref:`buildiso-section`.

New packages
============

Before creating a new package, make sure it's a good idea.
Often a simple documentation page is enough, and it requires much less effort.
When trying new things, just take care to write down on a public temporary document (maybe a wiki page)
all steps and comments.
If the feature collects many requests, it's time to think about a new package.
Otherwise, the temporary document can be moved to a manual page.

When creating a new package, make sure the following requirements are met:

* Create an issue describing the package
* Request the creation of a new repository (including Github mirror)
* Add the repository to Redmine to keep track of source changes from issues
* Add new record inside the package list http://dev.nethserver.org/projects/nethserver/wiki/Packages
* Add a wiki page describing the usage of package, the page should be named like the package itself
* Request Redmine administrators to add the package on  "NethServer package" custom field 
* If needed, add the package to a yum group as optional or mandatory package
* Add the repository to Ohloh for statics gathering


Steps to release a new package

#. Update/commit changelog
#. Add git tag
#. Build RPM
#. Publish the RPM to nethserver-update yum repository
#. Push git tag and package changelog
#. If needed, update yum groups file

See :ref:`buildrpm-section`.

