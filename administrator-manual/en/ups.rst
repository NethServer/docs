.. _ups-section:

====
UPS
====

|product| supports the management of :index:`UPS` (Uninterruptible Power Supply) connected to the system.

The server can be configured in two ways: 

* *master*: UPS is directly connected to the server, the server accepts connections from slaves
* *slave*: UPS is connected to another server accessible over the network

.. note:: You should consult the list of supported models before buying. 
   Via *Administration/Software centre* install the UPS package. In *Configuration*
   appears the new entry *UPS* where can be find the supported model by typing in
   *Search driver for model* field.

In :index:`master` mode, the UPS can be connected to the server:

* on a serial port 
* on a USB port 
* with a USB to serial adapter 


In :index:`slave` mode, you will need to provide the IP address of the master server.

The default configuration provides a controlled shutdown in the event of the absence of 
power.

Custom device 
============= 

If the UPS is connected to a port that is not listed in the web interface, you can configure a custom device with the following commands: :: 

 config setprop ups Device <your_device>
 signal-event nethserver-nut-save

UPS statistics
==============

If the statistics module (collectd) is installed and running, the module will automatically collect statistic data about UPS status.
