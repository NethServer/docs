==================
nethserver-release
==================

A NethServer system is constituted by RPMs that come mainly from CentOS, EPEL
and NethServer mirrors. Updates are announced by each project on its specific 
channel:

* NethServer https://github.com/NethServer/dev/issues?q=is%3Aissue+is%3Aclosed

* CentOS https://lists.centos.org/mailman/listinfo/centos-announce

* EPEL https://lists.fedoraproject.org/admin/lists/epel-package-announce@lists.fedoraproject.org/

A NethServer machine fetches:

- NethServer updates from an URL like: ``http://mirror.nethserver.org/nethserver/$releasever/updates/$basearch/``

- CentOS updates from an URL like: ``http://mirror.centos.org/centos/$releasever/updates/$basearch/``

- EPEL updates from an URL like: ``http://download.fedoraproject.org/pub/epel/7/$basearch``

Where ``$releasever`` is currently ``7``, and ``$basearch`` is ``x86_64``.

All those packages updates improve the original system release by pushing it forward, like rolling continuously.

When CentOS produces a new minor version like 7.5.1804 they publish a new "minimal" ISO image. 
The NethServer developers add a small RPM set on that image together with a kickstart file.
The resulting image is the NethServer ISO, with installer, server-manager and other stuff.

When NethServer 7.5.1804 is released, any existing 7.4.1708 installation can be upgraded seamlessly,
because both CentOS and NethServer ensure compatibility between minor releases.

Locking to a specific distribution release
==========================================

It is possible to lock to a specific distribution release, like ``7.5.1804`` as
explained in the "Software center" section of the administrator's manual.

The implementation is provided by the ``nethserver-base`` package and is based
on the following elements:

* ``sysconfig/NsReleaseLock`` prop
* ``software-repos-save`` event
* ``software-repos-upgrade`` event
