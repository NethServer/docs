============
DNS and DHCP
============

Management of server aliases, host names, and DHCP server.

Server Alias
============

Aliases are alternate names for this server. For example, if the
name of the server is *nethserver.nethesis.it*, an alias may be
*mail.nethesis.it*. The server will use its own IP address
for the alias name.

Create / Modify
---------------------

Allows you to create a new alias for this server.

Host Name
    The host name that you want to add or modify. It can contain only
    letters, numbers and hyphens, and must begin with a letter or a number.

Description
    An optional description useful to identify the alias.


DHCP
====

The DHCP (Dynamic Host Configuration Protocol) allows you to
assign IP addresses to clients on the local network



Configure
---------

Configure the DHCP server.

Disabled
    The DHCP server will be disabled and the LAN clients will not receive
    the address in an automatic way by this server. Select this
    option if there is another DHCP server on your local network.

Enabled
    The server will issue IP addresses to computers on the local network (recommended).

Start
    The first IP address in the range assigned to the clients on the LAN.

End
    The last IP address of the range, addresses between Start and End will ge assigned to clients.

Create / Modify
---------------------

Adds a new static allocation (reservation) to the DHCP server.
The device with the specified MAC address will always receive the
specified IP Address.

Host Name
    The host name you want to assign to clients on the LAN with the specified
    IP address.

Description
    An optional description to identify the system.

IP Address
    The IP address you want to assign.

MAC Address
    The MAC address of the network system (eg 11:22:33:44:55:66:77:88).


DNS
===

The DNS (Domain Name System) is responsible for Domain Name Resolution
(eg www.nethesis.it) into their corresponding numerical IP addresses
(Eg. 10.11.12.13) and vice versa. |product| delegates the resolution of
names to the configured DNS servers, but you can specify addresses
for arbitrary selected names. For example, you can configure the
system for responding to requests for facebook.com with the IP address 
0.0.0.0, achieving the effect of making the Facebook site unreachable.


Configure
---------

Click Configure to enter the addresses of the DNS servers that
|product| will contact to resolve names.

Primary DNS
    The address of the primary server to contact for resolving names (mandatory).

Secondary DNS
    The address of the secondary server to be contacted in case the primary is not responding (optional).

Create / Modify
---------------------

Click Create to assign a host name to an IP address. The
server will return the IP address configured for requests of its name.


Host Name
    The domain name, for example www.nethesis.it. It's possible to create
    names for the local domain, which is useful for giving a mnemonic name to
    devices configured with static IP or for any domain,
    which take precedence over the provider's DNS server (see
    facebook.com example above).

IP Address
    The IP address of the host name.

Description
    An optional comment for the host name (example:
    "Block facebook" or "video server").
