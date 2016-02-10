=========
IAX modem
=========

The module uses ``modems`` database to store record describing a iax modem.
After a new record is created, the system will generate all configuration files in ``/etc/iaxmodem`` using the action ``nethserver-iaxmodem-modemsetup``.

When a modem is selected under the nethserver-hylafax web ui, the action ``nethserver-iaxmodem-hylasetup`` will create a sutiable modem configuration file under ``/var/spool/hylafax/etc`` directory.

Multiple IAX modems
===================

Current nethserver-hylafax implementation doesn't handle more than one modem.
To use multiple IAX modems:

1. Create a IAX from web UI
2. Copy an existing ``config.IAXxx`` file and change number and identification strings Eg: ::

     cp /var/spool/hylafax/etc/config.ttyIAX351 /var/spool/hylafax/etc/config.ttyIAX350

3. Copy an existing faxgetty configuration, and change the device name inside the new file: Eg: ::
 
     cp /etc/init/faxgetty-ttyIAX350.conf /etc/init/faxgetty-ttyIAX351.conf
     sed -i 's/ttyIAX350/ttyIAX351/g' /etc/init/faxgetty-ttyIAX350.conf

4. Start services ::

     start faxgetty-ttyIAX351
     service hylafax restart

Configuration database: ::

 mymodem=iax
    cidName=NethServer
    cidNumber=351
    extension=351
    password=351
    server=192.168.1.1
