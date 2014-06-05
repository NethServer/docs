============
Repositories
============

Main repositories are:

* nethserver-base: it contains packages and dependencies from core modules. It is updated when a new milestone is released. Enabled by default.
* nethserver-updates: it contains updated packages. If needed, these updates can be applied without requiring manual intervention. Enabled by default.
* nethserver-testing: contains packages under QA process. Disabled by default.
* centos-base: base packages from CentOS. Enabled by default.
* centos-updates: updated packages from CentOS. Enabled by default.

A standard installation should have following enabled repositories:

* centos-base
* centos-updates
* nethserver-base
* nethserver-updates

Packages published in above repositories should always allow a non-disruptive automatic update.

To reset repository configuration, execute::

 eorepo centos-{base,updates} nethserver-{base,updates}

Third party repositories
========================

It's possible to install third party repositories, like EPEL, using standard CentOS methods.

The best practice is to enable third party repositories only when needed.

EPEL example
------------

Download and install release rpm from: http://dl.fedoraproject.org/pub/epel/6/x86_64/repoview/epel-release.html : ::

  yum localinstall http://dl.fedoraproject.org/pub/epel/6/x86_64/epel-release-6-8.noarch.rpm -y

Globally disable EPEL repository: ::

  eorepo centos-{base,updates} nethserver-{base,updates}

Enable EPEL repository only when installing a single package: ::

  yum --enablerepo=epel install <mypackage>


