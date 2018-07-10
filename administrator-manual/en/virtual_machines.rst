.. index:: virtual machines

.. _virtual_machines-section:

================
Virtual machines
================

|product| is capable of running virtual machines using KVM and libvirt.

Virtualization software can be installed and started using the command line: ::

  yum -y install qemu-kvm libvirt virt-install libvirt-client
  systemctl enable libvirtd
  systemctl start libvirtd

If |product| is used as DHCP server, the dnsmasq instance launched by libvirtd will conflict with the default one.
To avoid the conflict, remove the ``default`` libvirt NAT network: ::

  systemctl stop dnsmasq
  systemctl start libvirtd
  virsh net-destroy default
  virsh net-autostart default --disable
  systemctl start dnsmasq

The recommended client to manage virtual machines is `Virtual Machine Manager (virt-manager) <https://virt-manager.org/>`_

Install virt-manager in your Linux desktop, then create a new connection to your |product| using the SSH protocol.

Alternatively, virt-manager can be directly installed on |product|:

  yum -y install virt-manager

Then, use X11 Forwarding through SSH to view virt-manager graphical interface.

External resources
==================

For more info see:

- `Virtual Machine Manager official site <https://virt-manager.org/>`_
- `Virtual Machine Manager on RHEL <https://access.redhat.com/documentation/en-us/red_hat_enterprise_linux/7/html/virtualization_deployment_and_administration_guide/sect-creating_guests_with_virt_manager>`_
- `Introduction to virtualization <https://access.redhat.com/documentation/en-us/red_hat_enterprise_linux/7/html/virtualization_getting_started_guide/chap-virtualization_getting_started-what_is_it>`_
- `KVM/Libvirt FAQ <https://access.redhat.com/articles/1344173>`_
