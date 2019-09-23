====
SNMP
====

.. note::

  The configuration page of this module is available only in the old Server Manager
  and will not be ported to the new one.

ntopng
The SNMP (Simple Network Management Protocol) protocol allows to manage and monitor devices connected to the network.
The :index:`SNMP` server can reply to specific queries about current system status.

The server is disabled by default.

To enable it, you should set three main options:

* the SNMP community name
* the location name where the server is located
* the name and email address of system administrator

The implementation is based on the Net-SNMP project. Please refer to the official project page for more information:

http://www.net-snmp.org/

.. rubric:: References

.. [#SNMP] Simple Network Management Protocol https://en.wikipedia.org/wiki/Simple_Network_Management_Protocol

