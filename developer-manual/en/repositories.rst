============
Repositories
============

Main repositories are:

* nethserver-base: it contains packages and dependencies from core modules. It is updated when a new milestone is released. Enabled by default.
* nethserver-updates: it contains updated packages. If needed, these updates can be applied without requiring manual intervention. Enabled by default.
* nethforge: communty provided modules for NethServer. Enabled by default.
* nethserver-testing: contains packages under QA process. Disabled by default.
* base: base packages from CentOS. Enabled by default.
* updates: updated packages from CentOS. Enabled by default.
* centos-sclo-rh and centos-sclo-sclo: SCL repositories. Both enabled by default.
* extras: extra RPMs. Enabled by default.


A standard installation should have following enabled repositories:

* base
* updates
* nethserver-base
* nethserver-updates
* nethforge
* centos-sclo-rh
* centos-sclo-sclo
* extras

Packages published in above repositories should always allow a non-disruptive automatic update.

To reset repository configuration, execute::

 eorepo base updates nethserver-{base,updates} centos-sclo-{rh,sclo} epel nethforge extras

Third party repositories
========================

It's possible to install third party repositories, using standard CentOS methods.

The best practice is to enable third party repositories only when needed.

