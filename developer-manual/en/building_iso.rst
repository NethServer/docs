.. _buildiso-section:

============
Building ISO
============

The build process is tested on Fedora 17 and NethServer (CentOS). 

* We assume you have a non-root account and your working directory is ``$HOME``.
* Download a CentOS Minimal x86_64 iso
* See how to :ref:`rpm_prepare_env`.
* On NethServer, add your user to ``fuse`` group

Prepare the yum package groups file: ::

 git clone https://github.com/nethesis/comps.git
 cd comps
 make

Set some parameters in your devbox :file:`config` file: ::

  COMPS_FILE=~/comps/comps-ns64.xml

Run :command:`build-iso` script and relax..  ::

 build-iso -c -i CentOS-minimal.iso -v 6.4-beta1

The first time, be sure to pass ``-c``, the clean flag, that initializes mock chroot environment with a CentOS-minimal RPM set. 
Once you have the mock chroot initialized, you can run without ``-c`` and get quicker builds.

All file manipulations are performed on ``WORKDIR``. To change the ``WORKDIR`` path edit your :file:`config` file.
