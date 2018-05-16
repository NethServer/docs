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

.. warning:: 

    * This procedure must be avoided in Subscription and Enterprise
      installations!
    
    * Human supervision of automatic updates is required in any case!

Sometimes you may need to lock the server to a specific release, like
``7.4.1708``. For instance, you enabled automatic updates but do not want
to update automatically when a new CentOS/NethServer minor version is available.

1. Ensure the ``nethserver-subscription`` RPM is installed. It is required
   because it ships the template configuration for ``/etc/yum/vars/nsrelease``, 
   that does not mean a *Subscription* is needed for this procedure to work: ::

    # yum install nethserver-subscription

1. Select a CentOS mirror from the `official mirror list <https://www.centos.org/download/mirrors/>`_, or run the command ::

    # yum --disablerepo=\* --enablerepo=updates repolist -v | grep ^Repo-baseurl

   The output is something like: ::

    Repo-baseurl : http://mirrors.prometeus.net/centos/7.4.1708/updates/x86_64/

   If the release is no more available from official mirrors, it has been
   probably moved to http://vault.centos.org/.

2. Copy the mirror prefix ``http://mirrors.prometeus.net/centos`` into a ``centosmirror`` YUM variable: ::

    # echo 'http://mirrors.prometeus.net/centos' > /etc/yum/vars/centosmirror

3. Add it to configuration backup: ::

    # echo /etc/yum/vars/centosmirror >> /etc/backup-config.d/custom.include
    # echo /etc/yum.repos.d/CentOS-Base.repo >> /etc/backup-config.d/custom.include

4. Make a backup copy of the current CentOS repo file: ::

    # cp -a /etc/yum.repos.d/CentOS-Base.repo{,.bak}

5. Configure CentOS repo to use the selected mirror: ::

    # sed -i 's/^mirrorlist=/#mirrorlist=/g; s|^#baseurl=http://mirror.centos.org/centos/$releasever|baseurl=$centosmirror/$nsrelease|g;' /etc/yum.repos.d/CentOS-Base.repo

6. Create a template for the locked version number and expand it: ::

    # mkdir -p /etc/e-smith/templates-custom/etc/yum/vars/nsrelease/
    # echo '7.4.1708' > /etc/e-smith/templates-custom/etc/yum/vars/nsrelease/00version_lock
    # expand-template /etc/yum/vars/nsrelease

7. Verify the repositories are configured correctly: ::

    # yum clean all && yum repolist -v

This procedure does not include the following upstream repositories, because
they do not provide minor version paths, like ``7.4.1708``. They just provide
``7``, so a **human supervision of the automatic updates is required in any case**:

* EPEL
* SCL

To remove the release lock above run the commands: ::

    # rm -f /etc/e-smith/templates-custom/etc/yum/vars/nsrelease/00version_lock
    # expand-template /etc/yum/vars/nsrelease
    # cp -a /etc/yum.repos.d/CentOS-Base.repo{.bak,}

