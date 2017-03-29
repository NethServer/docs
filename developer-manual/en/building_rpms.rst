.. index::
   pair: Build; RPM
   single: Mock

.. _buildrpm-section:

=============
Building RPMs
=============

To build NethServer RPMs a few helper scripts are provided by the
``nethserver-mock`` package along with the Mock [#Mock]_ configuration
files pointing to NethServer YUM repositories.



.. _rpm_prepare_env:

Configuring the environment
===========================

On **NethServer**, install ``nethserver-mock`` package, by typing: ::

  yum install nethserver-mock

On **Fedora**, and other RPM-based distros run the command: ::

  yum localinstall <URL>

where <URL> is http://packages.nethserver.org/nethserver/7.3.1611/base/x86_64/Packages/nethserver-mock-1.3.2-1.ns7.noarch.rpm at the time of writing.
The build process uses Mock and must be run as a non privileged user,
member of the ``mock`` system group.  Add your user to the ``mock``
group: ::

  usermod -a -G mock <username>
  

Running the scripts
===================

The ``make-rpms`` command eases building of the NethServer RPMs by
hiding the complexity of other commands.  It is designed to work
inside the git repository directory of NethServer packages, but should
fit other environments, too.

Start by cloning the git repository and move inside it. For instance ::

  git clone https://github.com/nethesis/nethserver-mail-server.git
  cd nethserver-mail-server

To build the RPM just type ::

  make-rpms nethserver-mail-server.spec

The command writes the results into the current directory, assuming
every change to the source code has been commited. If everything goes
well they consist of:

* source RPM
* binary/noarch RPMs
* mock log files

To clean up the git repository directory, ``git clean`` may help: ::

  git clean -x -n

Substitute ``-n`` with ``-f`` to actually remove the files!
  
.. note::

   The ``make-rpms`` command is sensible to ``dist`` and ``mockcfg``
   environment variables.  If they are missing the default values are
   shown by invoking it without arguments.

For example: ::

  dist=ns7 mockcfg=nethserver-7-x86_64 make-rpms *.spec

The ``make-rpms`` command in turn relies on other scripts

``make-srpm``
  Builds the :file:`.src.rpm` file.
  
``prep-sources``
  Extracts and/or fetches the source tarballs.

The first ``Source`` tag in the :file:`.spec` file is assumed refer to
the local git repository.  If an absolute URL is specified, only the
last part is considered. Other ``SourceN`` tags must conform to the
Fedora RPM guidelines [#FedoraPG]_. The external sources are actually
fetched by the ``spectool`` command.

If the file :file:`SHA1SUM` exists in the same directory of the
:file:`.spec` file the tarballs are checked against it.

      
Development and Release builds
==============================

During the development, a package can be rebuilt frequently:
incrementing build numbers and unique release identifiers are useful
during this stage to help the whole process.

When ``make-rpms`` is invoked, it checks the git log history and tags
to decide what kind of build is required: *development* or *release*.

Release builds produce a traditional RPM file name, i.e.: ::

  nethserver-mail-server-1.8.4-1.ns6.noarch.rpm 

Development builds produces a *marked* RPM, i.e: ::

  nethserver-mail-server-1.8.3-1.6gite86697e.ns6.noarch.rpm

Other differences in *development* from *release* are

* the ``%changelog`` section in :file:`.spec` is replaced by the git
  log history since the last tag
  
* the number of commits since the last tag, and the latest git commit
  hash are extracted from ``git describe`` and prepended to the
  ``%dist`` macro.

.. index::
   pair: Sign; RPM
  
Signing RPMs
============

The command ``sign-rpms`` is a wrapper around ``rpm --resign``
command.  Its advantage is it can read a password for the GPG
signature from the filesystem. Sample invocation::

   sign-rpms -f ~/.secret -k ABCDABCD


Creating a release tag
======================

The :command:`release-tag` command executes the following workflow:

* Reads the git log history and fetches related issues from the issue
  tracker web site.
* Update the ``%changelog`` section in the :file:`spec` file.
* Commit changes to the :file:`spec` file.
* Tag the commit (with GPG signature).

This is the help output::

  release-tag -h
  Usage: release-tag [-h] [-k KEYID] [-T <x.y.z>] [<file>.spec]

For instance: ::

  release-tag -k ABCDABCD -T 1.8.5 nethserver-mail-server.spec

Replace ``ABCDABCD`` with your signing GPG key. The ``$EDITOR``
program (or git ``core.editor``) is opened automatically to adjust the
commit message. The same text is used as tag annotation.
Usage of ``-k`` option is optional.

The :file:`.spec` argument is optional: if not provided the first
:file:`.spec` file in the current directory is processed.



.. rubric:: References

.. [#Mock] Mock is a tool for building packages. http://fedoraproject.org/wiki/Projects/Mock
.. [#FedoraPG] Referencing Source http://fedoraproject.org/wiki/Packaging:SourceURL
