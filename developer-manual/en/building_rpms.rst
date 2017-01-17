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

.. note::

  The ``nethserver-mock`` package obsoletes ``nethserver-devbox``
  commands such as ``build-rpm`` and does not support the
  :file:`.spec.in` templates any more. To convert a :file:`.spec.in`
  file to plain :file:`.spec` see :ref:`spec-in-conversion`.

.. _rpm_prepare_env:

Configuring the environment
===========================

On **NethServer**, install ``nethserver-mock`` package, by typing: ::

  yum install nethserver-mock

On **Fedora**, put the following content into :file:`/etc/yum.repos.d/nethserver-mock.repo`: ::

    [nethserver-mock]
    name=NethServer Mock (6.6)
    #baseurl=http://pulp.nethserver.org/nethserver/6.6/base/x86_64/
    mirrorlist=http://pulp.nethserver.org/mirrors/nethserver?release=6.6&repo=base&arch=x86_64
    enabled=1
    skip_if_unavailable=1
    gpgcheck=1
    gpgkey=https://raw.githubusercontent.com/nethesis/nethserver-release/6.5-5-Final/root/etc/pki/rpm-gpg/RPM-GPG-KEY-NethServer-6
    includepkgs=nethserver-mock

Then install ``nethserver-mock``: ::

  yum install nethserver-mock

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

.. _spec-in-conversion:

Converting ``.spec.in`` templates
=================================

The :file:`.spec.in` template format is not supported by
``nethserver-mock``. To convert it to a traditional :file:`.spec`
replace the two placeholders:

* ``@VERSION@``, becomes the actual package version in the form
  *MAJOR.MINOR.RELEASE*
* ``@RELEASE@``, becomes an integer with the conditional *dist*
  macro suffix. For instance: ``1%{?dist}``

.. rubric:: References

.. [#Mock] Mock is a tool for building packages. http://fedoraproject.org/wiki/Projects/Mock
.. [#FedoraPG] Referencing Source http://fedoraproject.org/wiki/Packaging:SourceURL
