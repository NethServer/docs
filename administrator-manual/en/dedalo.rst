.. _dedalo-section:

================
Hotspot (Dedalo)
================

Hotspot main goal is to provide internet connectivity via wi-fi to casual users.  
Users are sent to a captive portal from which they can access the network by authenticating themselves via social login, sms or email.
The hotspot service allows the regulation, accountability and pricing of Internet access in public places, like internet points, hotels and fairs.  

Main features:

* network isolation between corporate and guests
* guests can authenticate themselves using social login (Facebook, Instagram, Linkedin) as well as sms or email login
* paid service based on vouchers 
* hotspot manager with different accesses type (admin, customer, desk)
* bandwidth Limit for each user
* export account list and connections report (not yet implemented)

How it works?
=============
The implementation is based on 2 components:

* a remote hotspot manager with a Web GUI running on a cloud server that allows you to:

  * create a hotspot instance: usually each instance is referred to a specific location (e.g. Art Cafè, Ritz Hotel and so on)
  * edit the captive portal page 
  * choose what type of login to use
  * see session and users logged

* a client part (dedalo) installed in |product| physically connected to the Access Points network : it assigns IP addresses to the clients of the Wi-Fi Network and redirects them to the captive portal for authentication.

For more detailed information please refer to https://nethesis.github.io/icaro/docs/components/ .


How to install it
=================

* install the server component: https://nethesis.github.io/icaro/docs/provisioning/
  This procedure uses Vagrant to provision a Digital Ocean (DO) droplet. If you prefere to use another cloud provider, edit Vagrantfile accordingly.

* configure the server in order to make it possibile to login: https://nethesis.github.io/icaro/docs/configuration/

* install the client component in your |product|: https://nethesis.github.io/icaro/docs/client_installation/

* please remind that the installation requires at least 3 ethernet interfaces:

  * 1 for normal LAN clients, marked with green role (you need it even if unused, it can be a VLAN)
  * 1 (or more) for Internet connection, marked with red role
  * 1 one for the Dedalo, marked with hotspot role




Configuration
=============


Hotspot manager interface
-------------------------

* go to the hotspot manager
* go to the *Managers* section and create a new *Manager* of type *Reseller* or *Customer*. More info about *Roles* here : https://nethesis.github.io/icaro/docs/manager/.
* do logout and login with the new manager just created
* go in the *Hotspot* section and create a new hotspot instance
* click on the hotspot name and configure the captive portal


Hotspot Unit on |product|
--------------------------

* go to the section *Hotspot Unit* on |product|
* edit the parameters in the `Hotspot unit registration` page:

  * ``Host name`` : Public name of the Hotspot Manager 
  * ``User name`` : user of a working account (reseller or customer)
  * ``Password`` : password

After that just choose the ethernet interface where the hotspot will be active.

If you have the proxy web active a specific flag in the hotspot unit page will allow you to forward all the hotspot traffic (HTTP and HTTPS protocols) 
to the web proxy for logging purposes. Please be aware that this configuration has privacy implications.

Finally connect an Access Point (AP) to the hostpot interface.


Access Point Configuration
--------------------------

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

For test purposes only you can also connect a laptop or a pc via ethernet cable to the hotspot interface instead of a Wi-Fi network.
This can be very useful if you are experiencing problems and you want to check if they are caused by the hotspot service or by the AP network.


Free Mode and Voucher Mode
--------------------------

The free mode (default) allows you to make login by yourself without the need of any code, just click on the desired social (or sms, email).

The voucher mode force you to create a voucher (basically "a code") and give it to every user, only users with the voucher will be allowed to make login.


