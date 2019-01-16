.. _phpVirtualBox-section:

=============
PhpVirtualBox
=============

.. note::

  This package is not supported in |product| Enterprise 


VirtualBox 
  VirtualBox is a powerful x86 and AMD64/Intel64 virtualization product for enterprise as well as home use. It is freely available as Open Source Software under the terms of the GNU General Public License (GPL) version 2.
  Please see the `official website <https://www.virtualbox.org/>`_



phpVirtualBox
  A web-based front-end to VirtualBox. This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License version 3 as published by the Free Software Foundation.
  Please see the `github page <https://github.com/phpvirtualbox/phpvirtualbox>`_


Installation
============

nethserver-virtualbox-X.X-phpvirtualbox requires nethserver-virtualbox-X.X-VirtualBox. The versions are bound togheter: nethserver-virtualbox-5.2-phpvirtualbox requires nethserver-virtualbox-5.2-VirtualBox

.. warning::

  VirtualBox compile its modules with the latest kernel, you must have the most updated kernel and start on it at boot. If the installer cannot compile the modules, then you should reboot your server and launch again the compilation using : ``/sbin/vboxconfig``



Install from the Software Center or use the command line: ::

  yum install nethserver-virtualbox-5.2-phpvirtualbox

Usage
-----

The URL of the phpVirtualBox application can be found at https://yourdomain.com/phpvirtualbox. The default credentials are :

* username: ``admin``
* password: ``admin``

More information are available at the Authentication section


Network access
--------------

The application is restricted to your local network (default is ``private``), to enable phpVirtualBox to the external IP ::

  config setprop phpvirtualbox access public
  signal-event phpvirtualbox-update

Access on an exclusive hostname
-------------------------------

To make phpVirtualBox accessible with an exclusive DNS name, for example https://webmail.example.com :

* In “DNS and DHCP” UI module (Hosts), create the DNS host name as a server alias (i.e. webmail.example.com)

* Add the host name to ``DomainName`` prop list (default is ''): ::

    config setprop phpvirtualhost DomainName webmail.example.com
    signal-event phpvirtualbox-update

Advanced settings
-----------------

phpVirtualBox attempts to look like the user interface of VirtualBox, but you can enable the ``AdvancedSettings`` property (default is ``false``) and get more settings, only available by the command line ::

    config setprop phpvirtualhost AdvancedSettings true
    signal-event phpvirtualbox-update

VM ownership and quota
----------------------

The administrator users are not limited on the virtual machine quota and can manage VM of other users. The VMs are visible only to the owner, as long as the property ``VMOwnerShip`` is to true (default is ``true``). ::

    config setprop phpvirtualhost VMOwnerShip false
    signal-event phpvirtualbox-update

Maximum number of VMs allowed for non admin user (default is ``5``) ::

    config setprop phpvirtualhost QuotaPerUser 10
    signal-event phpvirtualbox-update


User permissions
================

phpVirtualBox essentially has two access levels. ``admin`` and ``non-admin`` users. The administrator users have access to the Users section of phpVirtualBox and can add, edit, remove other users (only for the internal method). They can also perform actions that change VM group memberships and manipulate VM groups (Rename, Group, Ungroup). The administrator users are also not limited with the virtual machine quota and can manage VM of other users. The VMs are visible only by the owner, as long as the property ``VMOwnerShip`` is set to true.

Authentication
==============

You can change the authentication method by the property ``Authentication`` (``internal``, ``LDAP``, ``AD``, default is ``internal``). For LDAP and AD, phpVirtualBox will connect the |product| Account providers and grant or not the authorization to the web application.

Example: ::

  config setprop phpvirtualbox Authentication AD
  signal-event phpvirtualbox-update

internal
--------

The default credentials are :

* username: ``admin`` 
* password: ``admin``

Once logged in the first time, you should change the default password in the menu :menuselection:`File -> Change Password`.

In the phpvirtualbox user menu, you can create users, and set their permissions (only for the internal authentication method).

LDAP (openldap)
---------------

This authentication method is simple, all users from Openldap can login, but only users in the property ``AdminUser`` are administrators (comma separated list, default is ``admin``)

AD (active directory)
---------------------

This authentication method is the most complete, group based (you have to create manually the two groups in the group panel of |product| and associate members to these groups):

* members of ``vboxadmin`` are administrators
* members of ``vboxuser`` are non privilegied users

The users who do not belong to s ``vboxadmin`` or ``vboxuser`` groups, can't use the phpVirtualBox web application. You can change the group name with the properties ``UserGroup`` and ``AdminGroup``

Uploading ISOs
==============

The user who runs virtualbox is ``vboxweb``, a home is created (:file:`/home/vboxweb`) to store all the virtual machines (in VirtualBox VMs) and also the needed ISOs for creating your VM. The password of this user is stored in :file:`/var/lib/nethserver/secrets/virtualbox`.

You could open a session by ssh to download directly the ISO with wget, or push them by rsync or scp, directly from your computer. You could provide to the ``vboxweb user`` a ssh key and open a ssh session without password. ::

  rsync -avz XXXXXXX.iso vboxweb@IpOfServer:/home/vboxweb/
  scp XXXXXXX.iso vboxweb@IpOfServer:/home/vboxweb/


Oracle VM VirtualBox Extension Pack
===================================

This `Extension Pack <https://www.virtualbox.org/manual/ch01.html#intro-installing>`_ provides some good features like the usb support, Virtualbox RDP, disk encryption, NVMe and PXE boot for Intel cards. It is installed by the event nethserver-virtualbox-X.X-virtualbox-update automatically (by the installation or a rpm update). The pack is relevant of the VirtualBox version, if you need to update it, then trigger the event virtualbox-update : ::

  signal-event virtualbox-update

The RDP console
===============

You could use your own RDP software client for the installations of your guests, but phpVirtualBox comes with a Flash RDP console that you could use with your browser.

* The RDP console is restricted to the local network ( default is green), the ports are between ``[19000-19100]``. If you want to enable RDP for the external IP ::

    config setprop phpvirtualhost accessRDP red
    signal-event phpvirtualbox-update

* For specific needs you could specify the IP (default is '') of the integrated RDP console ::

    config setprop phpvirtualhost ipaddrRDP xxx.xxx.xxx.xxx
    signal-event phpvirtualbox-update


VM networking
=============

The networking side is probably the most difficult part of the virtualization, you should consult the VirtualBox Documentation

Promiscuous way
  Enable the promiscuous mode policy, select “Allow all” from the drop down list located in the network settings section.

W10
  When you want to join a virtualized W10 to the sambaAD container, bridge the guest NIC to br0 and create a script

Example script ::

  VBoxTunctl -u root -g vboxusers -t vbox0
  ifconfig vbox0 up
  brctl addif br0 vbox0
  sudo -H -u vboxweb VBoxManage startvm VMname --type headless

Esmith database
================

You can modify the available properties of phpvirtualhost: ::

     AdminGroup=vboxadmin       # members of this group can authenticate in  `AD` as administrators
     AdminUser=admin            # User list (comma separated) of administrators that can authenticate in `LDAP`
     AdvancedSettings=false     # Display the advanced settings in phpvirtualbox (true, false)
     Authentication=internal    # Authentication in phpvirtualbox: internal (builtin), AD (SAMBA AD), LDAP (openldap)
     DomainName=                # If set, a domain name or FQDN is used instead of https://server/phpvirtualbox
     QuotaPerUser=5             # Number maximal of VMs allowed for non admin user 
     TCPPortsRDP=19000-19100      # RDP ports for the console RDP of phpvirtualbox (the firewall is opened)
     URL=                       # If set, the path is modified to https://server/URL
     UserGroup=vboxuser         # members of this group can authenticate in  `AD` as simple users
     VMOwnerShip=true           # If set to true, users can see only their VM (true, false)
     access=private             # Restric phpvirtualbox access (private, public)
     accessRDP=green            # Access usage of the integrated RDP console (green, red)
     ipaddrRDP=                 # Set the IP of the integrated RDP console for specific need
     status=enabled             # Enable phpvirtualbox (disabled, enabled)


Example: ::

  config setprop phpvirtualbox accessRDP red AdvancedSettings enabled
  signal-event phpvirtualbox-update

Documentation
=============

VirtualBox
  The `official documentation <http://download.virtualbox.org/virtualbox/UserManual.pdf>`_ is available on the VirtualBox website.

phpVirtualbox
  The `official documentation <https://github.com/phpvirtualbox/phpvirtualbox/wiki>`_ is available on the github website.
