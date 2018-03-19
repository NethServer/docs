nethserver-dc
=============

The nethserver-dc package runs a systemd-nspawn container (``nsdc``) with a vanilla
Samba 4 inside of it. It downloads, installs, configures and provision an Active
Directory domain controller based on Samba.

The ``nsdc`` container needs an IP address in a green network, different from the
host machine one. It enslaves its network interface to a host bridge, with green
role. If needed, this bridge is created automatically. 

This is a typical configuration::

  # config show nsdc
  nsdc=service
     ProvisionType=newdomain
     IpAddress=192.168.122.50
     bridge=br0
     status=enabled

nethserver-dc-save event
------------------------

* it creates and configures systemd-nspawn machine (nethserver-dc-install
  action). The Samba domain is provisioned by the ``samba-provision.service`` unit, according 
  to the ``ProvisionType`` prop value. Supported values are:

  - ``newdomain`` (default): domain and realm are taken from local system and
    won't be possible to change them anymore. For instance if system domain is
    `nethserver.org` domain will be `NETHSERVER` and realm `nethserver.org`.

  - ``ns6upgrade``: connect the LDAP service running on the host machine and 
    migrate the WS/PDC domain from ns6 backup to an Active Directory domain.
    The realm and domain name are set as described in the ``newdomain`` provision 
    type.

* it creates a network bridge if needed, or select an existing one and save it in nsdc bridge db prop (`nethserver-dc-create-bridge` action)

* it waits for the machine to come up (`nethserver-dc-waitstart`)

* it joins the domain of new machine using default credentials (`nethserver-dc-join`).

* it sets the password policy (`nethserver-dc-password-policy`)

Realmd writes a lot of information on the system journal. See `journalctl` command. 

To have a shell inside the ``nsdc`` container, you can run ::

 # systemd-run -M nsdc -t /bin/bash


Manual Join
-----------

nethserver-dc-join action joins automatically to domain. If for any reason the
join is invalid you can attempt a manual join following this procedure

Check nsdc is running: ::

    systemctl status nsdc

Check the DNS is responding: ::

   # host -t SRV _ldap._tcp.$(config getprop sssd Realm)
   _ldap._tcp.nethsever.org has SRV record 0 100 389 nsdc-vm8.nethsever.org.

Clean up any previous join state: ::

    config setprop sssd Provider none
    signal-event nethserver-sssd-leave

Join the domain: ::

   realm join -v -U admin $(config getprop sssd Realm)

You can replace ``admin`` with any other administrative account name. The
command above prompts for a password. When join is successful: ::

   config setprop sssd Provider ad
   signal-event nethserver-sssd-save

If everything goes well ::

   getent passwd administrator@$(hostname -d)
   # output: administrator@nethserver.org:*:261600500:261600513:Administrator:/home/administrator@nethserver.org:/bin/bash
   
   /usr/libexec/nethserver/list-users -s administrator
   # output: {"administrator": ...

Once domain is joined, you can manage users from interface. From command line, you can use `net` command ::

  # net ads info

Factory reset
-------------

The "Start DC" procedure from the "Accounts provider" page is designed for a
single run.  If it fails, reinstalling the whole server can be avoided by
running the following command ::

    signal-event nethserver-dc-factory-reset

The command cleans up the DC state and prepare it for new provisioning run.
**Any existing user and group account is erased**.

If a full DC reinstall is desired, after factory reset event, run also ::

    rm -rf /var/lib/machines/nsdc

Uninstall nethserver-dc
-----------------------

Execute: ::

  signal-event nethserver-sssd-remove-provider

Upgrade the containter
----------------------

The upgrade procedure will:

- stop the container
- upgrade the chroot base system
- upgrade samba
- restart the container

To upgrade, execute: ::

    signal-event nethserver-dc-upgrade


Changing the IP address of DC
-----------------------------

.. warning:: 
    
    Before applying this procedure, read carefully the `official Samba wiki page
    <https://wiki.samba.org/index.php/Changing_the_IP_Address_of_a_Samba_AD_DC>`_.

The IP address of nsdc containter must be in the same network of the bridged green interface.
If needed, first change the address of the green interface, then proceed with the following.

Example, change the network address:

* current host IP: 192.168.101.7
* current nsdc container IP: 192.168.122.77
* new nsdc container IP: 192.168.101.77

Execute the ``nethserver-dc-change-ip`` with the new ip address: ::

    signal-event nethserver-dc-change-ip <new_ip_address>

Example: ::

    signal-event nethserver-dc-change-ip 192.168.101.77

Note that the event will fail if the new nsdc ip address is not in the same network
of the green interface.

Alternate UPN suffix
--------------------

The default UPN (User Principal Name) suffix for a user account is the SSSD realm, but
the nsdc containter is configured to use also an extra UPN suffix set
to the FQDN of the host machine.

Example:

- Host FQDN: nethserver.org
- SSSD realm: ad.nethserver.org
- Default UPN: ad.nethserver.org
- Extra UPN: nethserver.org

If required, the administrator can use RSAT tools to select the extra UPN for a specific user.


References:

- https://technet.microsoft.com/en-us/library/cc772007%28v=ws.11%29.aspx
- https://msdn.microsoft.com/en-us/library/ms680537%28v=vs.85%29.aspx
