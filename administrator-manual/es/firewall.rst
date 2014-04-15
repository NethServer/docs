============
Port forward
============

Use this panel to change firewall rules
ie to open a specific port (or a range of ports) on the server
and forward the traffic from a port to another. Port forwarding rules
allow access to hosts on the local network from the Internet.

Create / Modify
===============

Source port
    Insert the port open on the public IP.

Destination port
    Insert the port on the internal host which will be destination of the traffic.

Destination host
    IP address of the internal machine where traffic will be redirected.

Allow only
    Allow traffic forward only from some networks/hosts source.

Description
    Optional description of port forwarding rule.

Enable / Disable
====================

Port forwarding rules are enabled by default on
creation. You can temporarily enable/disable them
using this button

Yes
    Enable the rule.

No
    Disable the rule.

Firewall check
==================

Performs a general control over configured firewall rules. Useful for inconsistencies detection.

====================
Bandwidth management
====================

The bandwidth manager allows you to change priorities to traffic
going through the firewall (which must have at least two network interfaces).

General
========

Enables or disables bandwidth management.


Interface rules
===============

For each interface on which you want to manage the bandwidth priority is
necessary to specify the maximum amount of bandwidth available in both
outgoing and incoming directions. No data will be transmitted at a rate
over to that configured. It's imperative to use actual values,
preferably measured with speed tests, in particular for the band in
upload (outgoing). The table shows the values configured on each
interface, allowing you to modify the bandwidth limits.

Create / Modify
---------------

Create a configuration for interface bandwidth limits.

Interface
    Select the interface to which the limits of bandwidth applies.
     In general, the bandwidth is limited only on the WAN interfaces.

Incoming bandwidth (kbps)
    Set the amount of incoming bandwidth (download).

Outgoing bandwidth (kbps)
    Set the amount of output bandwidth (upload).

Description
    An optional note (for example: ADSL 1280/256).


Address rules
==============

The table shows the list of network addresses (IP or MAC) that have
customized priority rules. For example, you may decide
that traffic from a specific computer on the local network
have a low priority or high compared to others.


Create / Modify 
---------------

IP or MAC address
    Enter the IP address or MAC address that identifies the computer.

Description
     An optional description to identify
     clearly the purpose of the rule. For example: high priority for the
     boss.

Port rules 
==========

The table shows the list of TCP / UDP ports that have rules with
customized priority. For example, you can specify that the
traffic on a particular network service (from or to
a particular port) has a low priority or high
compared to normal network traffic.


Create 
------

Port
    Specify the port used by the network service.

Protocol
    Enter the IP protocol.

Description
    An optional description that 
    clearly states the purpose of the rule. For example: background for
    FTP service.
