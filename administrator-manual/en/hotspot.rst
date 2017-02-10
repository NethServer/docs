=======
Hotspot
=======

The hotspot service allows the regulation, accountability and pricing of Internet access
in public places, like internet points, hotels and fairs.

Main features:

* Network isolation between corporate and guests
* Access management with user / password
* Pricing based on prepaid credit, date expiration, traffic usage or freely accessible
* Login manager from web panel
* Creation of users and  coupons to be delivered to the customer
* Bulk user creation and SMS/email registration
* Billing report
* Limiting the bandwidth used by users
* Export account list and connections report

Configuration
=============

.. note::

   You need a server with at least 3 ethernet interfaces.


The server must be connected to network access points.
User and billing management can be accessed at: http://hotspot.nethesis.it

How to proceed:

* Make sure you have at least one free interface (no role) which will be assigned to the hotspot
* Ensure that the system can communicate over the Internet to the Operation Center using  1812 and 1813 TCP/UDP ports
* Access the :guilabel:`Hotspot` page to define the interface to use and configure the parameters of the service
* Connect the ethernet interface to the access point

Web interface
-------------

The web interface allows you to enable and disable the HotSpot service.

You can:

* select the network interface associated with the HotSpot service
* modify the network address reserved to clients
* enable the transparent proxy and content filtering
* customize title, footers, disclaimers, and sites accessible without authentication


Access Point
------------

The Access Point (AP) must perform the sole function of enabling the connection with the firewall,
they should behave like an ordinary network switch. Follow these recommendations:

* configure the access point without authentication and without DHCP
* disable any service (security services, etc.) in order to avoid interference with hotspot behavior
* if you use more AP configure them with different SSID (eg: 1-SCHOOL / SCHOOL-2 / ...) in order to easily identify any malfunctioning AP
* configure the AP with a static IP address on a network segment (rfc-1918) different from the one used by the hotspot
* if possible, enable the "client isolation", to avoid traffic between clients connected to the access point
* configure the AP to work on different channels to minimize interference, a good AP allow you to manage the channels automatically or manually select them
* do not use too shoddy products, low quality AP can cause frequent disconnections which impact on the quality of the overall service, 
  the recommendation is even more important if you are using repeaters

Access the service
==================

Access to Operation Center, create a new hotspot instance (or use an existing one), than associate it to the firewall:

* https://docs.nethesis.it/Register_Amministrazione#Gestione_Hotspot

Then, you will be able to manage the hotspot using at https://hotspot.nethesis.it.
You must access the site using the credentials of the hotspot instance.

Administrator manual:

* https://docs.nethesis.it/Hotspot_NethSecurity#Configurazione_del_Centro_Servizi 

Disconnecting an account
========================

You can disconnect an account from the web interface, if the following conditions are met:

* the firewall must accept traffic from Internet at UDP port 3779
* the firewall must accept connections on UDP port 3779 from hotspot.nethesis.it

You can do it by executing the following command: ::

  config set hotspot-disconnect service UDPPort 3779 access private status enabled AllowHosts `dig +short hotspot.nethesis.it`
  signal-event firewall-adjust
