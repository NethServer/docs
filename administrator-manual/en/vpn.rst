===
VPN
===

VPN supported configurations:

1. Connecting a remote terminal to the internal network
   (Roadwarrior), based on L2TP/IPsec or OpenVPN.

2. Connecting two remote networks (net2net), based on OpenVPN.


Account
=======

The account tab allows to manage users used for
VPN connections to the local server. Users can be normal
system users or dedicated exclusively to the VPN service (without standard services like email).

Create new
----------

Allow the creation of a new user. For each user, the system
creates a x509 certificate.

VPN only
    The name used for VPN access. It can contain only
    lowercase letters, numbers, hyphens, underscores (_) and
    must begin with a lowercase letter. For example "luisa",
    "Jsmith" and "liu-jo" is a valid user name, while "4Friends"
    "Franco Blacks" and "aldo / mistake" are not.

System User
    Enable VPN access for a user already existing in the system.
    The user can be selected from the drop-down list.

Remote network
    Enter this information only when you want to create a nt2net VPN.
    These fields are used by the local server to correctly create
    routes to the remote network.

    * Network Address: the network address of the remote network. Eg: 10.0.0.0 
    * Netmask: Netmask of the remote network. Eg: 255.255.255.0


Client
======

The VPN client allows you to connect the server to another VPN server
in order to create a net2net VPN.  Currently only OpenVPN net2net are supported.


