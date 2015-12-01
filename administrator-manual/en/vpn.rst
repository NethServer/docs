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
* Multiple NAT traversal, you do not need a static dedicated static IP on the firewall
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

   Instead, it's mandatory to choose a system account if you want to use
   authentication with user name and password.

2. Download the file containing the configuration and certificates.

3. Import the file into the client and start the VPN.


Tunnel (net2net)
----------------

When creating an OpenVPN net2net connection, you must choose a master between involved server.
All other server are considered as slave (client).

Steps to be performed on the master:

* Enable roadwarrior server

* Create a VPN-only account for each slave

* During the account creation remember to specify the remote network configured behind the slave

Steps to be performed on the slave:

* Create a client from the :guilabel:`Client` page, specifying the connection data to the master server.

* Copy and paste the content of downloaded certificates from the master configuration page.

IPsec
=====

:index:`IPsec` (IP Security) protocol is usually used to create tunnels with devices from other manufacturers.

Roadwarrior (L2TP)
------------------

:index:`L2TP` is considered the replacement for PPTP which is insecure.
Many devices include native support for this protocol but not all
implementations are compatible.

Supported authentication methods are:

* System user, password and certificate
* Secret shared key (PSK)

To allow a client to establish a VPN:

1. Configure the server as PDC (Primary Domain Controller) from the :guilabel:`Windows Network` page.

2. Create a new system account.

3. Download the file that contains certificates.

4. Import client and CA (Certification Authority) certificates within the client.

5. Proceed with the configuration of connection data and start the VPN.

.. note::
   Use of L2TP is recommended if and only if 
   is not possible to install a OpenVPN client into the device.

Tunnel (net2net)
----------------

IPsec is extremely reliable and compatible with many devices.
In fact, it is an obvious choice when you need to create net2net connections
between firewall of different manufacturers.

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



