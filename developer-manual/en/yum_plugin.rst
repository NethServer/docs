===========
Yum plugin
===========

The ``nethserver-yum`` package contains the ``nethserver-events`` "Yum plugin":http://yum.baseurl.org/wiki/WritingYumPlugins which extends the post-RPM transaction hook.  It executes the ``*-update`` event of each ``nethserver-*`` package involved in the transaction, preserving the order of RPM dependencies. 

Signalling ``update`` events *after* RPM cleaning up assures that any old event handler and template fragments have been removed.

h2. Configuration

The configuration file is ``/etc/yum/pluginconf.d/nethserver.conf``. Available options are:

* enabled: 1 (default) or 0,  enable or disable the plugin
* verbose: 1 or 0 (default), enable or disable debugging messages

Caching
=======

When NethServer is behind a proxy server you can force to bypass an intermediate caching by adding this option to the ``yum.conf`` file, under the ``main`` section:
 
 http_caching=none

This command can raise load on remote repository servers, use with care!
