================
Virtual machines
================

|product| is capable of running virtual machines using KVM and libvirt, but it
doesn't provide a Web interface for it.

Virtualization software can be installed and started using the command line, just execute: ::

  yum install @virtualization-hypervisor @virtualization-tools @virtualization-platform
  systemctl enable libvirtd
  systemctl start libvirtd

If |product| is used as DHCP server, the Dnsmasq instance launched by libvirtd will conflict with the default one.
To avoid such conflict, remove ``default`` libvirt NAT network: ::

  systemct stop dnsmasq
  systemctl start libvirtd
  virsh net-destroy default
  systemct start dnsmasq

Finally, the system is ready to be managed using `Virtual Machine Manager (virt-manager) <https://virt-manager.org/>`_,
a Linux desktop user interface for managing virtual machines through libvirt.

Access virt-manager in your Linux desktop, then create a new connection to your |product| using SSH protocol.

External resources
==================

For more info see:

- `Virtual Machine Manager official site <https://virt-manager.org/>`_
- `Virtual Machine Manager on RHEL <https://access.redhat.com/documentation/en-us/red_hat_enterprise_linux/7/html/virtualization_deployment_and_administration_guide/sect-creating_guests_with_virt_manager>`_
- `Introduction to virtualization <https://access.redhat.com/documentation/en-us/red_hat_enterprise_linux/7/html/virtualization_getting_started_guide/chap-virtualization_getting_started-what_is_it>`_
- `KVM/Libvirt FAQ <https://access.redhat.com/articles/1344173>`_
