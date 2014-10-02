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
Eeach entry is saved inside the :file:`/etc/hosts` file.

There are three types of records:

* ``local``: hosts inside the internal network
* ``remote``: hosts outside the internal networ
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

The system uses *dnsmasq* as DNS and DHCP server. If server role is ``resolver``, the server
will directly resolve all hosts inside its domain. All other names will be queried to external DNS servers.

Uninstall
---------

Before uninstalling *nethserver-dnsmasq* package, disable local name resolution. Execute: ::

  config setprop dns role none
