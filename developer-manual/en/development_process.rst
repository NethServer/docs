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
output of the job will bew a new object implementing the issue itself.
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

The *triager* handles all issue in NEW state. He/she collects missing info, set NEEDINFO flag, set state to TRIAGED when having enough informations.
He/she can also change the status to CLOSE and set resolution: DUPLICATE, INSUFFICIENT_DATA, NOTABUG.

Developer
^^^^^^^^^

The *developer* takes a TRIAGED issue and put it ON_DEV setting the Assignee to himself/herself.
He/she moves the issue from TRIAGED (or ON_QA) to ON_DEV state. 
Developer write test cases, optionally annotate RPM changelog message for Packager.
Finally push changes to SCM and change to MODIFIED resetting the Assignee.

He/she can also change the status to CLOSE and set resolution: CANTFIX, WONTFIX, WORKSFORME, CURRENTRELEASE, NEXTRELEASE, UPSTREAM.

Packager
^^^^^^^^

The *packager* pulls changes from SCM and build the package. 
He/she puts the package in testing repository. Change state to ON_QA.
When the package is VERIFIED from the QA team, packager will tag the package, build the tagged release and upload to updates/base repository. 
Verify yum update works fine then push the tagged changelog in SCM. 
Finally he/she sets state to CLOSED leaving  resolution field blank.

QA team member
^^^^^^^^^^^^^^

The *QA team member* takes an unassigned issue ON_QA state and sets the Assignee to himself/herself. 
He/she tests the package, and can also set NEEDINFO flag if test case is missing. When test is passed he/she sets state VERIFIED, 
otherwise TRIAGED again without Assignee.


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

Activities
==========

ISO release
-----------

#. An ISO release starts whenever a target version is reached (see
   `Roadmap <http://dev.nethserver.org/projects/nethserver/roadmap)>`__
#. search for all new RPMs in nethserver-dev repository and select
   stable packages ready for production
#. rebuild each selected package and publish it to nethserver-testing
   repository
#. test new RPMs in existing machine and in a new freshly installed one
#. if all test pass, move RPMs to repository nethserver-update
#. build the new ISO (see [[Building ISO]])

Package release
---------------

#. update/commit changelog
#. add git tag
#. build RPM
#. move RPM to yum repository
#. (testing)
#. push git tag and package changelog
#. if needed, update yum groups file

Package creation
----------------

*  Create a wiki package for documentation named as the package itself
*  Add the package to [[Packages]] page
*  Update the dependency graph
   source:dev-nethesis-it\|/nethserver/package-dependencies.dot
*  Make sure the git repository is registered on Redmine
*  Make sure the git repository is replicated to Github
   (https://github.com/nethesis)
*  Make sure the git repository is registered at Ohlo
   (https://www.ohloh.net/p/nethserver)

