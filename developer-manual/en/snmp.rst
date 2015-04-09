====
SNMP
====

Simple :index:`SNMP` server.

Package: *nethserver-net-snmp*.

Database 
========

Configuration is saved in ``snmpd`` key inside ``configuration`` database.

Available properties:

* ``Community``: name of the SNMP community, default is ``public``
* ``SysLocation``: name of the server location, default is ``Unknown``
* ``SysContact``: name and mail address of the system administrator, default is ``Root <root@localhost>``.  

Example: ::

 snmpd=service
    Community=public
    SysLocation=Unknown
    SysContact=Root <root@localhost>
    status=enabled
    access=private
    UDPPort=61

Query example: ::

  snmpwalk -mALL -v2c -cpublic localhost


Configuration can be applied using the ``nethserver-net-snmp-save`` event.
