========================
nethserver-ipsec-tunnels
========================

This pacakge provides the configuration of VPN tunnels based using IPSec.
The implementation can support custom properties to override the configuration from web interface.

All records of type ``ipsec-tunnel`` are saved insided the ``vpn`` database.

Every property in the form ``Custom_<name>`` will override any existing property.
The same syntax can also be used to set *any* IPsec options supported by OpenSwan.

**Example: override left prop**

Given the following record: ::

 nethesis-test=ipsec-tunnel
    compress=no
    dpdaction=hold
    esp=auto
    ike=auto
    left=192.168.2.246
    leftid=@nethesis
    leftsubnets=192.168.1.0/24
    pfs=yes
    psk=Nethesis,12345678911
    right=1.2.3.4.5
    rightid=@test
    rightsubnets=192.168.6.0/24
    status=enabled

The admin can override the left property: ::

 db vpn setprop nethesis-test Custom_left %any
 signal-event nethserver-ipsec-save

**Example: set new option**

Set aggressive mode: ::

 db vpn setprop nethesis-test Custom_aggrmode yes
 signal-event nethserver-ipsec-save


Logs
----

Logs can be inspected using this command: ::

    journalctl -u ipsec.service 
