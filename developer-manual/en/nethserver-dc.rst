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

* it creates and configures systemd-nspawn machine (nethserver-dc-install
  action). Machine is provisioned with domain and realm taken from local system
  and won't be possible to change them anymore. For instance if system domain is
  `nethserver.org` domain will be `NETHSERVER` and realm `nethserver.org`. Those
  parameters are read from
  `/var/lib/machines/nsdc/etc/sysconfig/samba-provision` template. To have a
  shell inside nspawn machine, you can use ::

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
    signal-event nethserver-dnsmasq-save
    config setprop nsdc status disabled

Changing the IP address of DC
-----------------------------

.. warning:: 
    
    Before applying this procedure, read carefully the `official Samba wiki page
    <https://wiki.samba.org/index.php/Changing_the_IP_Address_of_a_Samba_AD_DC>`_.

Example, change the network address ("122" becomes "101"):

* domain ``dpnet.nethesis.it``, realm ``DPNET.NETHESIS.IT``
* bridge is ``br0``
* current host IP: 192.168.122.7
* current gateway IP: 192.168.122.1
* current nsdc container IP: 192.168.122.77
* new host IP: 192.168.101.7
* new gateway IP: 192.168.101.1
* new nsdc container IP: 192.168.101.77

.. warning::
    
    This procedure must be run from the system console. **Do not it run
    remotely!** The server can become unreachable!

1. Shut down the nsdc Linux container ::

    systemctl stop nsdc

2. Set the new host and gateway IP addresses ::
    
    db networks setprop br0 ipaddr 192.168.101.7 gateway 192.168.101.1 netmask 255.255.255.0

3. Set the new nsdc IP address ::
    
    config setprop nsdc IpAddress 192.168.101.77
    config setprop sssd AdDns 192.168.101.77

4. Expand the templates from nethserver-dc-save event ::

    for F in $(find /etc/e-smith/events/nethserver-dc-save/templates2expand -type f); do
        expand-template ${F##/etc/e-smith/events/nethserver-dc-save/templates2expand}
    done

5. Apply the changes ::

    signal-event interface-update
    signal-event nethserver-dnsmasq-save

6. Start nsdc ::

    systemctl start nsdc

7. Edit ``/var/lib/machines/nsdc/etc/krb5.conf`` and append a "realms" section like the following::
    
    [realms]
    DPNET.NETHESIS.IT = {
       kdc = 192.168.101.77
    }

8. Run ``samba_dnsupdate`` in nsdc container ::
    
    systemd-run -t -M nsdc /usr/sbin/samba_dnsupdate --verbose

9. Clean up ``/var/lib/machines/nsdc/etc/krb5.conf``, by removing the section appended at step 7

