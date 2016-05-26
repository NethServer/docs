================
nethserver-avahi
================

Configure avahi-daemon to start at boot.
The  Avahi  mDNS/DNS-SD daemon implements Apple's Zeroconf architecture.

It's used by CUPS for printers auto-discovery. See :ref:`cups-section`.

Database: ::

 avahi-daemon=service
    UDPPort=5353
    access=private
    status=enabled
