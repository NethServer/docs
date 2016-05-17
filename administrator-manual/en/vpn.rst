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

When creating an OpenVPN net2net connection, you must choose a master between involved servers.
All other servers are considered as slaves (clients).

Steps to be performed on the master server:

* Enable roadwarrior server

* Create a VPN-only account for each slave

* During the account creation remember to specify the remote network configured behind the slave

Steps to be performed on the slave:

* Create a client from the :guilabel:`Client` page, specifying the connection data to the master server.

* Copy and paste the content of downloaded certificates from the master configuration page.

