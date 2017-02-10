.. index::
   single: DHCP
   alias: DHCP, Dynamic Host Configuration Protocol
   single: PXE
   alias: PXE, Preboot eXecution Environment

.. _dhcp-section:

===================
DHCP and PXE server
===================

The :dfn:`Dynamic Host Configuration Protocol` (DHCP) [#DHCP]_ server
centralizes the management of the local network configuration for any
device connected to it.  When a computer (or a device such as a
printer, smartphone, etc.) connects to the local network, it can ask
the network configuration parameters by means of the DHCP protocol.
The DHCP server replies, providing the IP, DNS, and other relevant
network parameters.

.. note:: In most cases, the devices are already configured to use DHCP
	  protocol on start up.

The :dfn:`Preboot eXecution Environment` (PXE) [#PXE]_ specification
allows a network device to retrieve the operating system from a
centralized network location while starting up, through the DHCP and
TFTP protocols. See :ref:`dhcp_pxe` for an example about configuring a
such case.

.. _dhcp_configuration:

DHCP configuration
==================

The DHCP server can be enabled on all *green* and *blue* interfaces
(see :ref:`network-section`).  |product| will assign a free IP address
within the configured :dfn:`DHCP range` in :guilabel:`DHCP > DHCP
server` page.

The DHCP range must be defined within the network of the associated
interface. For instance, if the green interface has IP/netmask
``192.168.1.1/255.255.255.0`` the range must be ``192.168.1.2 -
192.168.1.254``.

.. _advanced options:

Advanced options
----------------------

There are seven advanced options for DHCP.  You can assign zero options, one option or all seven options.   

For the servers – DNS, NTP, WINS and TFTP – you can assign zero, one or more for each server; if you place more than one, use a comma between each server with no space.


.. _dhcp_reservation:

Host IP reservation
===================

The DHCP server leases an IP address to a device for a limited period
of time.  If a device requires to always have the same IP address, it
can be granted an *IP reservation* associated to its MAC address.

The page :guilabel:`DHCP > IP reservation` lists the currently
assigned IP addresses:

* a line with :guilabel:`IP reservation` button identifies an host
  with a temporary lease (gray color);

* a line with :guilabel:`Edit` button identifies an host with a
  reserved IP (black color).  A small two arrows icon near the host
  name says the DHCP lease is expired: this is a normal condition for
  hosts with static IP configuration, as they never contact the DHCP
  server.


.. _dhcp_pxe:

Boot from network configuration
===============================

To allow clients to boot from network, the following components are
required:

* the :ref:`DHCP <dhcp_configuration>` server, as we have seen in the
  previous sections, 

* the :dfn:`TFTP` server [#TFTP]_,

* the software for the client, served through TFTP.

.. index::
   single: TFTP
   alias: Trivial File Transfer Protocol; TFTP

.. _dhcp_tftp:

TFTP is a very simple file transfer protocol and usually it is used
for automated transfer of configuration and boot files.

In |product| the TFTP implementation comes with the DHCP module and is
enabled by default.  To allow accessing a file through TFTP, simply
put it in :file:`/var/lib/tftpboot` directory.

.. note:: To disable TFTP type the following commands in a root's
          console: ::
	    
	     config setprop dhcp tftp-status disabled
	     signal-event nethserver-dnsmasq-save

For instance, we now configure a client to boot CentOS from the
network. In |product|, type at root's console: ::

 yum install syslinux
 cp /usr/share/syslinux/{pxelinux.0,menu.c32,memdisk,mboot.c32,chain.c32} /var/lib/tftpboot/
 config setprop dnsmasq dhcp-boot pxelinux.0
 signal-event nethserver-dnsmasq-save 
 mkdir /var/lib/tftpboot/pxelinux.cfg

Then create the file :file:`/var/lib/tftpboot/pxelinux.cfg/default` with
the following content: ::

 default menu.c32
 prompt 0
 timeout 300

 MENU TITLE PXE Menu

 LABEL CentOS
   kernel CentOS/vmlinuz
   append initrd=CentOS/initrd.img

Create a CentOS directory: ::

 mkdir /var/lib/tftpboot/CentOS
 
Copy inside the directory :file:`vmlinuz` and :file:`initrd.img`
files. These files are public, and can be found in the ISO image, in
:file:`/images/pxeboot` directory or downloaded from a CentOS mirror.

Finally, power on the client host, selecting PXE boot (or boot from
network) from the start up screen.

.. Rubric:: References

.. [#DHCP] Dynamic Host Configuration Protocol (DHCP)
           https://en.wikipedia.org/wiki/Dynamic_Host_Configuration_Protocol
.. [#TFTP] Trivial File Transfer Protocol
           https://en.wikipedia.org/wiki/Tftp
.. [#PXE] Preboot eXecution Environment
          https://en.wikipedia.org/wiki/Preboot_Execution_Environment

