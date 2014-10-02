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

If |product| is also the DHCP server on the network, all the machines will be configured to use the server istelf for name resolution.


.. note:: You must specify at least one external DNS inside the :guilabel:`DNS server` page.


Hosts
=====

The :guilabel:`Hosts` page allows you to map host names to IP addresses, whether they are local or remote.

For example, if you have an internal web server, you can associate the name *www.mysite.com* with the IP 
of the web server. Then all clients can reach the website by typing the chosen name.

Locally configured names always take precedence over DNS records from external servers. 
In fact, if the provider inserts *www.mydomain.com* with an IP address corresponding to the official web server, 
but inside |product| the IP of *www.mydomain.com* is configured with another address, hosts inside the LAN will not be able to see the site.


Alias
=====

An :dfn:`alias` is an alternative name used to reach the local server. 
For example, if the server is called *mail.example.com*, you can create a :index:`DNS alias` *myname.example.com*. 
The server will then be accessible from clients on the LAN even using the name you just defined. 

Aliases are only valid for the internal LAN. If you want the server is reachable from the outside with the same name 
you need to ask the provider to associate the public address of the server to the desired name.

