===
VPN
===

A :index:`VPN` (Virtual Private Network) allows you to establish a secure and encrypted connection
between two or more systems using a public network, like the Internet.

The system supports two types of VPNs:

1. :index:`roadwarrior`: connect a remote client to the internal network

2. :index:`net2net` or :index:`tunnel`: connect two remote networks


OpenVPN
=======

OpenVPN lets you easily create VPN connections,
It brings with numerous advantages including:

* Availability of clients for various operating systems: Windows, Linux, Apple, Android, iOS
* Multiple NAT traversal, you do not need a dedicated static IP on the firewall
* High stability
* Simple configuration

Roadwarrior
-----------

The OpenVPN server in roadwarrior mode allows connection of multiple clients.

Supported authentication methods are:

* System user and password
* Certificate
* System user, password and certificate

The server can operate in two modes: :index:`routed` or :index:`bridged`.
You should choose bridged mode only if the tunnel must carry non-IP traffic.

To allow a client to establish a VPN:

1. Create a new account: it is recommended to use a dedicated VPN account
   with certificate, avoiding the need to create a system user.

   On the other hand, it's mandatory to choose a system account if you want to use
   authentication with user name and password.

2. Download the file containing the configuration and certificates.

3. Import the file into the client and start the VPN.


Tunnel (net2net)
----------------

When creating an OpenVPN net2net connection, a server will have the master role.
All other servers are considered as slaves (clients).

A client can be connected to another |product| or any other firewall which uses OpenVPN.

All tunnels use OpenVPN routed mode, but there are two kind of topologies: *subnet* and *p2p* (Point to Point)

**Topology: subnet**

This is the recommended topology.
In :index:`subnet topology`, the server will accept connections and will act as DHCP server for every connected clients.

In this scenario

* the server will authenticate clients using TLS certificates
* the server can push local routes to remote clients
* the client will be able to authenticate with TLS certificates or user name and password

**Topology: P2P**

In :index:`p2p topology`, the administrator must configure one server for each client.

In this scenario:

* the only supported authentication method is the PSK (Pre-Shared Key).
  Please make sure to exchange the PSK using a secure channel (like SSH or HTTPS)
* the administrator must select an IP for both end points
* routes to remote networks must be configured on each end point



To configure a tunnel, proceed as follow:

1. Access the tunnel server and open the :guilabel:`OpenVPN tunnels` page,
   move to :guilabel:`Tunnel servers` tab and click on :guilabel:`Create new` button

2. Insert all required fields, but please note:

   - :guilabel:`Public IPs and/or public FQDN`, it's a list of public IP addresses or host names which will be used 
     by clients to connect to the server over the public Internet
   - :guilabel:`Local networks`, it's a list of local networks which will be accessible from the remote server.
     If topology is set to p2p, the same list will be reported inside the client :guilabel:`Remote networks` field
   - :guilabel:`Remote networks`, it's a list of networks behind the remote server which will be accessible
     from hosts in the local network

3. After the configuration is saved, click on the :guilabel:`Download` action and select :guilabel:`Client configuration`

4. Access the tunnel client, open the :guilabel:`OpenVPN tunnels` page, move to :guilabel:`Tunnel clients` tab,
   click on :guilabel:`Upload` button

Advanced features
~~~~~~~~~~~~~~~~~

The web interface allows the configuration of advanced features like:

* on the client, multiple addresses can be specified inside the :guilabel:`Remote hosts` field for redundancy; the OpenVPN client will try to connect to each host in the given order
* :index:`WAN priority`: if the client has multiple WAN (red interfaces), the option allows to select the order in which the WAN will be used to connect
  to the remote server
* protocol: please bear in mind that OpenVPN is designed to operate optimally over UDP, but TCP capability is provided for situations where UDP cannot be used
* cipher: the cryptographic algorithm used to encrypt all the traffic. If not explicitly selected, the server and client will try to negotiate the best cipher
  available on both sides
* LZO compression: enabled by default, can be disabled when using legacy servers or clients


Legacy mode
^^^^^^^^^^^

Tunnels can still be created also using Roadwarriors accounts.

Steps to be performed on the master server:

* Enable roadwarrior server

* Create a VPN-only account for each slave

* During the account creation remember to specify the remote network configured behind the slave

Steps to be performed on the slave:

* Create a client from the :guilabel:`Client` page, specifying the connection data to the master server.

* Copy and paste the content of downloaded certificates from the master configuration page.


IPsec
=====

:index:`IPsec` (IP Security) protocol is the 'de facto' standard in VPN tunnels, it's tipically used to create net to net tunnels and it's supported from all manufacturers.
You can use this protocol to create VPN tunnels between a |product| and a device from another manufacturer as well as VPN tunnels between 2 |product|.


Tunnel (net2net)
----------------

IPsec is extremely reliable and compatible with many devices.
In fact, it is an obvious choice when you need to create net2net connections
between firewalls of different manufacturers.

Unlike OpenVPN configuration, in an IPsec tunnel, firewalls are considered peers.

If you are creating a tunnel between two |product|, given the firewalls A and B:

1. Configure the server A and specify the remote address and LAN of server B. 
   If the :guilabel:`Remote IP` field is set to the special value ``%any``, 
   the server waits for connections from the other endpoint.

2. Configure the second firewall B by mirroring the configuration from A inside the remote section.
   The special value ``%any`` is allowed in one side only!

If an endpoint is behind a NAT, the values for :guilabel:`Local
identifier` and :guilabel:`Remote identifier` fields must be set to
custom unique names prepended with ``@``.  Common names are the
geographic locations of the servers, such as the state or city name.


