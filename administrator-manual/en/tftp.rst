=======================================
TFTP - Trivial File Transfer Protocol
=======================================

|product| can be easily configured as :index:`TFTP` server (https://en.wikipedia.org/wiki/Tftp). TFTP is a very simple file transfer protocol and usually used for automated transfer of configuration or boot files.

Configuration
==============

After installation is necessary to enable TFTP with following commands: ::

 config setprop tftp status enabled
 signal-event nethserver-tftp-save

Now TFTP server is reachable on port 69 UDP.

To allow to access a file via TFTP, it has top be putted in :file:`/var/lib/tftpboot` and change it's owner to ``nobody``

PXE Server
====================

TFTP is also part of :index:`PXE`. Following instructions are to use |product| as CentOS PXE ::

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

Create a CentOS directory: ::

 mkdir -p /var/lib/tftpboot/CentOS
 

Copy inside the directory :file:`vmlinuz` and :file:`initrd.img` files. These files can be found inside the ISO or browsing the yum os mirror.

Change files owner to ``nobody``: ::

 chown -R nobody /var/lib/tftpboot/*

