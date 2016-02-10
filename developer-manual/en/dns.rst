===
DNS
===

The system will resolve host and domain names using DNS queries
to external DNS servers.
The configuration is saved inside the ``dns`` key from *nethserver-base* package.

Properties:

* ``NameServers``: comma separated IP list of external DNS
* ``role``: can be set to ``none`` or ``resolver``. 
  If role is set to ``none`` the server will always use external DNS. 
  For ``resolver`` role see :ref:`dns_server-section`. 


Example: ::

 dns=configuration
    NameServers=8.8.8.8,208.67.222.222
    role=none

Hosts
=====

The system can handle local DNS records.
When the server performs a DNS lookup, first it will search inside local DNS records.
If no local record is found, an external DNS query will be done.

.. note:: Local DNS record will always override records from external DNS servers.

DNS records are called :dfn:`hosts` and are saved inside the ``hosts`` database.
Each entry is saved inside the :file:`/etc/hosts` file.

There are three types of records:

* ``local``: hosts inside the internal network
* ``remote``: hosts outside the internal network
* ``self``: alias for the server itself 

Records of type ``local`` and ``remote`` can have following properties:

* ``IpAddress``: address of the host 
* ``Description``: optional description
* ``MacAddress``: mac address of the host. Used only for DHCP reservation. See :ref:`ip_reservation-section`.


For hosts inside local network, the record key doesn't have the domain part. Example: ::

  host1=local
      Description=Internal network host #1
      IpAddress=192.168.1.23

For hosts outside local network, the record key must have the domain part. Example: ::

  external.otherdomain.tld=remote
      Description=Other domain host
      IpAddress=8.9.10.11

Records of type ``self`` can have following properties:

* ``Description``: optional description

Example: ::

  vhost1.domain.tld=self
      Description=Virtual Host #1


.. _dns_server-section:

DNS server
==========

The system uses *dnsmasq* as DNS and DHCP server and it directly resolves all hosts inside its domain. 
All other names will be queried to external DNS servers.

The server will forward reverse lookups to upstream DNS servers, only if upstream DNS servers are inside a
private network (eg. network address is 192.168.x.x).

The option ``bind-interfaces`` is always enabled, as consequence (from dnsmasq man):

 This option has been patched to always use SO_BINDTODEVICE socket option when binding to  interfaces.  As  consequence,  dnsmasq
 WILL  NOT ANSWER to any DNS Queries that come to the socket with the correct destination IP address, but originally on different
 interface. This behavior differs from the original dnsmasq upstream version and is used for security reasons.


Properties:

* ``CacheSize``: entry to be cached by server, default is ``4000``
* ``dhcp-boot``: directly pass parameters to dhcp-boot option
* ``except-interface``: comma-separated list of interfaces. Do not listen to listed interfaces, useful to avoid conflicts with libvirt
* ``tftp-status``: can be ``enabled`` or ``disabled``. If enabled, enable the TFTP server for BOOTP (port 67)
* ``access``: default is ``private``, do NOT set to ``public``

Database example: ::

  dnsmasq=service
    AllowHosts=
    CacheSize=4000
    DenyHosts=
    TCPPort=53
    UDPPorts=53,67
    access=private
    dhcp-boot=pxelinux.0,myserver.mydomain.com,192.168.1.1
    except-interface=virbr0,tunspot
    status=enabled
    tftp-status=enabled

