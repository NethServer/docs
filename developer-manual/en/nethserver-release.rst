==================
nethserver-release
==================

A NethServer system is constituted by RPMs that come mainly from CentOS mirrors and NethServer mirrors.

CentOS releases errata and bug fixes recompiling RHEL packages, as reported by the centos-announce mailing list,
and released inside upstream mirrors.
NethServer does the same, announcing new releases of its specific RPMs on https://github.com/NethServer/dev/issues.

A NethServer machine fetches:

- CentOS security updates from an URL like: ``http://mirror.centos.org/centos/$releasever/updates/$basearch/``
- NethServer updates from an URL like: ``http://mirror.nethserver.org/nethserver/$releasever/updates/$basearch/``

Where ``$releasever`` is currently ``7``, and ``$basearch`` is ``x86_64``.

All those packages updates improve the original system release by pushing it forward, like rolling continuously.

When CentOS produces a new minor version like 6.7 they publish a new "minimal" ISO image. 
The NethServer developers add a small RPM set on that image together with a kickstart file.
The resulting image is the NethServer ISO, with installer, server-manager and other stuff.

When NethServer 7.4 is released, any existing 7.3 installation can be upgraded seamlessly,
because both CentOS and NethServer ensure compatibility between minor releases.

Disabling rolling release
=========================

Sometime you may need to point a server to a specific release **only for testing purpose**.

NethServer
----------

Add the specific release to ``/etc/yum/vars/nsrlease`` file.

Example: ::

  echo 7.3.1611 > /etc/yum/vars/nsrlease

CentOS
------

1. Open ``/etc/yum.repos.d/CentOS-Base.repo``
2. Comment the line containing ``mirrorlist=``
3. Un-comment the line containing ``baseurl=``
4. Substitute ``baseurl`` value with a URL pointing to vault. Eg: http://vault.centos.org/7.2.1511/updates/x86_64/
