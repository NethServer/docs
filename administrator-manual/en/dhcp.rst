.. _dhcp-section:

====
DHCP
====

The :dfn:`DHCP` (Dynamic Host Configuration Protocol) server allows you to control the network configuration 
of all computers or devices connected to the LAN. 
When a computer (or a device such as a printer, smartphone, etc.) connects to the network, the :index:`DHCP` server
automatically assigns a valid IP address and performs the configuration of 
DNS and gateway. 

In most cases, the devices are already configured to use DHCP protocol. 
Otherwise, you must manually enable this configuration in each client.

The DHCP server can be enabled on all green and blue interfaces (see :ref: `network-section`). 
The system will pick a free IP address within the configured :index:`DHCP range`.

Il sistema sceglierà un indirizzo IP libero all'interno dell':index:`intervallo DHCP` (:index:`range DHCP`) configurato.

.. note:: The DHCP range must be defined within the network of associated interface.

Example:

* green interface with IP 192.168.1.1 and network mask 255.255.255.0
* the range can be between 192.168.1.2 and 192.168.1.254

IP reservation
==============

The DHCP server automatically assigns a valid IP address each time s computer is connected to the network. 
If some machines on the LAN should always have the same IP address, 
you can configure the DHCP server to assign a fixed IP based on the MAC address of the network card of the machine. 

The page :guilabel:`Reserve IP` lists all the IP addresses currently assigned. 
To reserve the address is sufficient to use the button :guilabel:`Reserve IP` or explicitly create a 
new configuration by entering the IP and MAC addresses of the device.

