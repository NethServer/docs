===================
nethserver-unbonund
===================

Unbound is a validating, recursive, and caching DNS resolver.
Currently it's only used only as DNS server for anti-spam DNSBL implementation.

When a new mail arrives, the anti-spam filter checks if sender IP address is listed
in well-known blacklists.
Some blacklists doesn't allow multiple query from public DNS servers,
thus the system needs a DNS server which can directly query the blacklist DNS.

If the mail filter is installed, dnsmasq configuration is changed, and specific
domain query are redirect trough unbond.
See: :file:`/etc/e-smith/templates/etc/dnsmasq.conf/26unbound_rbl`.

Package: *nethserver-unbound*.

Database 
========

Configuration is saved in ``unbound`` key inside ``configuration`` database.

Available properties:

* ``UDDPort``: server address of the mail server, default is ``localhost``
* ``access``: default is ``none`` since unbound should not be used as a normal DNS server
* ``status``: can be ``enabled`` or ``disabled``, default is ``enabled``

Example: ::

 unbound=service
    UDPPort=10053
    access=none
    status=enabled

Configuration can be applied using the ``nethserver-unbound-update`` event.

