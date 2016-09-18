nethserver-dc
=============

The nethserver-dc package runs a systemd-nspawn container with a vanilla Samba 4.3.4 inside of it. It downloads, installs, configures and provision an Active Directory domain controller based on Samba.

Samba machine needs an IP address in a green network, different from the machine one. It also requires a bridge on the green interface. If needed, this bridge is created automatically. ::

  # config show nsdc
  nsdc=service
     IpAddress=192.168.122.50
     bridge=br0
     status=enabled

nethserver-dc-save event
------------------------

* it creates and configures systemd-nspawn machine (nethserver-dc-install action). Machine is provisioned with domain and realm taken from local system and won't be possible to change them anymore. For instance if system domain is `nethserver.org` domain will be `NETHSERVER` and realm `nethserver.org`. Those parameters are read from `/var/lib/machines/nsdc/etc/sysconfig/samba-provision` template
To have a shell inside nspawn machine, you can use ::

  # systemd-run -M nsdc -t /bin/bash

* it creates a network bridge if needed, or select an existing one and save it in nsdc bridge db prop (`nethserver-dc-create-bridge` action)

* it waits for the machine to come up (`nethserver-dc-waitstart`)

* it joins the domain of new machine using default credentials (`nethserver-dc-join`). To join domain manually, clear sssd.conf, join domain and expand sssd.conf template

* it sets the password policy (`nethserver-dc-password-policy`)

Realmd writes a lot of information on the system journal. See `journalctl` command. 


Manual Join
-----------

nethserver-dc-join action joins automatically to domain. If you want to join domain manually, check that machine came up ::

   # host -t SRV _ldap._tcp.`config get DomainName`
   _ldap._tcp.nethsever.org has SRV record 0 100 389 nsdc-vm8.nethsever.org.

then clear sssd.conf, join domain and expand sssd.conf template ::

   # > /etc/sssd/sssd.conf
   # realm join `config get DomainName`
   # expand-template /etc/sssd/sssd.conf

Then provide the default administrator password::

   Nethesis,1234

If everything goes well ::

   # getent passwd administrator@`config get DomainName`
   administrator@nethserver.org:*:261600500:261600513:Administrator:/home/administrator@nethserver.org:/bin/bash   

Once domain is joined, you can manage users from interface. From command line, you can use `net` command ::

  # net ads info

Factory reset
-------------

The "Start DC" procedure from the UI is designed for a single run.  If it fails,
reinstalling the whole server can be avoided with some bash commands.

The following steps are required to clean up the DC state and prepare it for a
new provisioning run. ::

    realm leave
    systemctl stop nsdc sssd
    rm -vf /var/lib/machines/nsdc/etc/samba/smb.conf
    find /var/lib/machines/nsdc/var/lib/samba/ -type f | xargs -- rm -vf
    config setprop sssd Provider none status disabled
    > /etc/sssd/sssd.conf
