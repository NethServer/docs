.. _buildrpm-section:

=============
Building RPMs
=============

The entire RPM building process is automatized and is run by
:command:`build-rpm` command, provided by `nethserver-devbox` package. 

The process has been successfully tested on

* NethServer 6.3-alpha1 and later
* Fedora 17 and later

Let assume you have a ``Projects/`` directory where you have cloned
some git repositories. The :command:`build-rpm` command requires that each project directory:

* is a git repository
* contains a file named after it, plus ``.spec`` or ``.spec.in`` extension
* has a tag representing the current version number: ``X.Y.Z``

For example, a simple directory layout would be:

* ``Projects/``

  * ``projA/``

    * ``.git/``
    * ``projA.spec.in``

  * ``projB/``

    * ``.git/``
    * ``projB.spec``


Spec template file
==================

A :file:`.spec.in` template file syntax is the same as RPM :file:`.spec` files,
where

* :dfn:`Version` and :dfn:`Release` tag values are placeholders that are substituted during the build process: ::
  
    Version: @VERSION@
    Release: @RELEASE@

* :dfn:`%changelog` section is at the bottom of the file.

.. _rpm_prepare_env:

Prepare your development machine
================================

NethServer
----------

On NethServer, you can simply install nethserver-devbox, by typing: ::

  yum install nethserver-devbox

Then copy :file:`/usr/share/doc/nethserver-devbox-<version>/config.sample` to :file:`Projects/config` and edit it.

Fedora
------

On Fedora, clone nethserver-devbox repository somewhere in your filesystem: ::

  git clone git://code.nethesis.it/nethserver-devbox

Then install some packages marked as "Requires" in :file:`nethserver-devbox.spec.in`: 

* mock
* expect
* tar
* fuse-iso fuse 
* genisoimage
* git
* rpm-build
* intltool

Add :command:`build-rpm` and :command:`build-iso` commands to your :file:`PATH`. For instance create symlinks in your :file:`~/bin` directory: ::

  ln -s <nethserver-devbox-dir>/build-rpm  ~/bin/
  ln -s <nethserver-devbox-dir>/build-iso  ~/bin/

Copy :file:`config.sample` to :file:`Projects/config` and edit it.

Build the RPM
=============

The build process uses mock (http://fedoraproject.org/wiki/Projects/Mock) and must be run as a non privileged user in the `mock` system group.
Add your user with: ::

  usermod -a -G mock <username>

The build-rpm script

* creates the tarball and the :file:`.spec` file for the given package name, 
* builds the source and binary RPMs
* signs RPMs with your GPG key (``-s`` or ``-S <KEYID>`` options)
* copy RPMs to a local yum repository  (if ``REPODIR`` directory exists)
* publish RPMs to a remote yum repository (``-p`` option. Configure ``PUBLISH_*`` parameters and ssh access)

The script can execute one or more tasks listed above in the same run. Intermediate files are written to ``WORKDIR``. ::
  
  build-rpm
  Usage: build-rpm [-cousp] [-S <gpgkeyid>] [[-D <key>=<value>] ... ] <package_name> ...
   
Development release
===================

If you want to create a package with a development release, just execute from the :file:`Projects/` directory: ::

  build-rpm <package>

The system will search for the first available tag inside the git
repository and will calculate the version and release values (see
:command:`git describe`). This means **the tag must exist**!::

  VERSION=<last_tag>

For ``.spec.in`` file: ::

  RELEASE=<commits_from_tag>.0git<commit_hash>.<DIST>

Or, if using plain ``.spec`` file: ::

  RELEASE=<spec_release>.<commits_from_tag>git<commit_hash>.<DIST>

For example, given the project nethserver-ntp with the tag 1.0.0 set two commits backwards from HEAD we have: ::

  VERSION=1.0.0
  RELEASE=2.0git5a6ddeb.ns6
  ---
  RELEASE=1.2git5a6ddeb.ns6


Stable release
==============

When you are ready for a production release, the :command:`release-rpm` command helps you in the following tasks:

* Fetch changelog info from git and relate commits with issues from Redmine installation at ``REDMINE_URL``.
* Update the changelog section in ``spec`` or ``spec.in`` file (whatever applies).
* Review and commit the changelog.
* Create a (signed) git tag.

Commit and tag are added locally, thus they need to be pushed to your
upstream git repository, once reviewed.

::

  release-rpm
  Usage: release-rpm [-s] -T  

For instance:

::

  release-rpm -s -T 1.2.3 nethserver-base

Your ``$EDITOR`` program (or git core.editor) is opened automatically to adjust the commit message. The same text is used as tag annotation. 

To abort at this point, save an empty message.

Specific releases
=================

If you want to create a RPM with a specific version: ::

  build-rpm -D VERSION=<X.Y.Z> <package>  

A tag equal to the given version MUST exists. ``RELEASE`` is set to ``1.<DIST>``.
If you want to set a release number for the spec files, use: ::

  build-rpm -D VERSION=<X.Y.Z> -D RELEASE=<R> <package>

Sign the RPM
============

Just execute:

::

  build-rpm -s 

or

::

  build-rpm -S  

If a password is not set in :file:`config` file, the :command:`print-gnome-keyring-secret` command asks gnome-keyring for a secret 
password stored in ``SIGN_KEYRING_NAME`` at ``SIGN_KEYRING_ID`` index.

Publish the RPM
===============

.. note::  
  The nethserver-devbox package must be installed on the remote
  machine (``PUBLISH_HOST``). In the repository root directory
  (``PUBLISH_DIR``), create a ``Makefile`` symbolic link to
  :file:`repository.mk` .

Copy the package to the remote server using SSH:

::

  build-rpm -p 

After the RPMs have been built, they are copied to ``PUBLISH_HOST`` into
``PUBLISH_DIR``. Then :command:`make` is run on the remote machine directory to
update the yum repository.

Known problems
==============

When using mock on a VirtualBox (or KVM) virtual machine, the system can
lock with error similar to this one:

::

    ... BUG: soft lockup - CPU#0 stuck for 61s! [yum:xxx] ... (repeating)..

The bug is reproducible with kernel 2.6.32-431.x.
To avoid the problem, downgrade the kernel:

::

    wget http://vault.centos.org/6.4/os/x86_64/Packages/kernel-2.6.32-358.el6.x86_64.rpm
    yum localinstall kernel-2.6.32-358.el6.x86_64.rpm

Then reboot and choose the 2.6.32-358 kernel.
