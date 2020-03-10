.. _dns-section:

===
DNS
===

|product| can be configured as :dfn:`DNS` (Domain Name System) server inside the network.
A :index:`DNS` server is responsible for the resolution of domain names (eg. *www.example.com*)
to their corresponding numeric addresses (eg. 10.11.12.13) and vice versa. 

The server performs DNS name resolution requests on behalf of local clients, 
and it is accessible only from the LAN network (green) and the guest's network (blue).

During a name lookup the server will: 

* search for the name between hosts configured locally 
* perform a query on external dns: requests are stored in cache to speed up subsequent queries

.. note::
    You must specify at least one external DNS server inside the :guilabel:`Network > DNS servers` page from the old Server Manager.
    Otherwise click on the DNS address inside the :guilabel:`Dashboard` of the new Server Manager.

If |product| is also the DHCP server on the network, all the machines will be configured to use the server itself for name resolution.

Hosts
=====

The :guilabel:`Hosts` page allows you to map host names to IP addresses, whether they are local or remote.

For example, if you have an internal web server, you can associate the name *www.mysite.com* with the IP 
of the web server. Then all clients can reach the website by typing the chosen name.

Locally configured names always take precedence over DNS records from external servers. 
In fact, if the provider inserts *www.mydomain.com* with an IP address corresponding to the official web server, 
but inside |product| the IP of *www.mydomain.com* is configured with another address, hosts inside the LAN will not be able to see the site.


.. _dns_alias-section:

Alias
=====

An :dfn:`alias` is an alternative name used to reach the local server. 
For example, if the server is called *mail.example.com*, you can create a :index:`DNS alias` *myname.example.com*. 
The server will then be accessible from clients on the LAN even using the name you just defined. 

Aliases are only valid for the internal LAN. If you want the server is reachable from the outside with the same name 
you need to ask the provider to associate the public address of the server to the desired name.


.. _dns_redirection-section:

Domain redirection
==================

The administrator can override the upstream DNS for specific domains.
A typical usage scenario is setting the Active Directory server as resolver for the queries to the internal domain.

Such change can be done by editing the ``DomainRedirection`` property via command line.
The property accepts a comma-separated list of couples in the form ``<domain>:<ip_address>``.

Example: ::

  config setprop dnsmasq DomainRedirection my.local.domain.org:192.168.1.1,my.domain.com:192.168.1.2
  signal-event nethserver-dnsmasq-save

The ``my.domain.org:192.168.1.1`` configuration will send all queries for ``my.local.domain.org`` to ``192.168.1.1``. 

The special server address ``#`` can be used to send queries to the default DNS server. Example: ::

  config setprop dnsmasq DomainRedirection domain.org:1.1.1.1,sub.domain.org:#
  signal-event nethserver-dnsmasq-save

In this example all queries for ``domain.org`` will be sent to ``1.1.1.1``, while queries for ``sub.domain.org`` will be sent to default upstream DNS.
