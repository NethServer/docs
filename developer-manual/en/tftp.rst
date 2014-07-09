====
TFTP
====

:index:`TFTP` module contains configuration fragments that enables :index:`dnsmasq` built-in TFTP server.

TFTP server han no authentication or encription support. 

When installed tftp is disabled by default and need to be enabled with: ::

 config setprop tftp status enabled
 signal-event nethserver-tftp-save

The package also add directory :file:`/var/lib/tftpboot` that is the root of tftp server.

Enabling TFTP adds 5 new configuration options to :file:`/etc/dnsmasq.conf`. Here variables explanation according with dnsmasq documentation

* ``enable-tftp``: enable tftp server
* ``tftp-secure``: allow only files owned by the user dnsmasq is running as will be send over the net
* ``dhcp-boot= ...``: Set the boot filename for netboot/PXE. You will only need this is you want to boot machines over the network and you will need a TFTP server; driven by db prop
* ``tftp-root=/var/lib/tftpboot``: Set the root directory for files available via FTP.
* ``dhcp-option=66, LOCAL_IP``: set local ip as default tftp server for machines that receive dhcp from this server


Properties:
============

* ``status``: can be ``enabled`` or ``disabled``. If ``enabled``, TFTP server is configured and port 69 UDP is opened.
* ``UDPPort``: UDP port used. Only ``69`` is allowed.
* ``access``: define if access is ``public``, ``private`` or ``none``.
* ``dhcp-boot``:  Set the boot filename for PXE. Ths is needed for booting machines over the network. Empty by default.
* ``type``: only ``service`` is allowed.


Test TFTP
===========

Testing is very simple:

Install package and enable TFTP server: ::

 yum install nethserver-tftp
 config setprop tftp status enabled
 signal-event nethserver-tftp-save

Create a file to share, owned by ``nobody`` user: ::

 echo "test"  > /var/lib/tftpboot/foobar
 chown nobody:nobody /var/lib/tftpboot/foobar

From another machine, install tftp and get file
(on Fedora)::

 yum install tftp
 
Always from the other machine, allow incoming UDP connection from our TFTP server. Loading TFTP conntrack module should be enough::

 modprobe nf_conntrack_tftp 
 
Connect to TFTP server::

 tftp TFTP_SERVER_HOST

...and get the file::

 tftp> get foobar


Configure a PXE server
========================

Those instructions set up a PXE server for CentOS
Install and configure syslinux and nethserver-tftp: ::
 
 yum install syslinux
 cp /usr/share/syslinux/{pxelinux.0,menu.c32,memdisk,mboot.c32,chain.c32} /var/lib/tftpboot/
 config setprop tftp dhcp-boot pxelinux.0
 signal-event nethserver-tftp-save
 mkdir /var/lib/tftpboot/pxelinux.cfg

Create the file :file:`/var/lib/tftpboot/pxelinux.cfg/default` with the following content: ::

 default menu.c32
 prompt 0
 timeout 300

 MENU TITLE PXE Menu

 LABEL CentOS
 kernel CentOS/vmlinuz
 append initrd=CentOS/initrd.img

 Create a CentOS directory:

Create a CentOS directory: ::

 mkdir -p /var/lib/tftpboot/CentOS 

Copy inside the directory :file:`vmlinuz` and :file:`initrd.img` files. These files can be found inside the ISO or browsing the yum ``os`` mirror.

Change files owner to nobody: ::

 chown -R nobody /var/lib/tftpboot/*















