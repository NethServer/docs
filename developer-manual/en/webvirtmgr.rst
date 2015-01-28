==========
WebVirtMgr
==========

WebVirtMgr is a simple web interface for :index:`libvirt` administration, the main package is ``nethserver-webvirtmgr``.

By default there is a local socket connection named ``localhost``, 
it's a simply record in SQLite database, the db name is 
:file:`webvirtmgr.sqlite3` that can be found in :file:`/usr/lib/python2.6/site-packages/webvirtmgr/`.

The webvirtmgr service is handled using upstart, meanwhile webvirtmgr-console is handled by traditional init.d.

Database
========

Configuration is stored inside ``webvirtmgr`` and ``webvirtmgr-console`` keys in ``configuration`` database.

Properties of ``webvirtmgr``:

* TCPPort: listen TCP port, default is ``8000``
* User: login user, default is ``admin``
* Password: password for ``User``, automatically generated during first configuration
* status: default is ``disabled``
* access: default is ``private``, do not change for security reasons

Properties of ``webvirtmgr-console``:

* status: default is ``disabled``
* access: default is ``private``, do not change for security reasons

