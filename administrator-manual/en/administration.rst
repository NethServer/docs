==============
Remote access
==============

It is possible to allow access to the web interface from computers in remote networks. Add allowed networks here.

Enabled hosts can access the web interface over HTTPS.

Web access
===========

Access to  configuration web interface.

Network address
    This is the address from which access to the web interface will be allowed
    web.

Network Mask
     To allow access to only one host, use as a subnet mask of 255.255.255.255.
    

SSH
===

Manage Secure Shell (SSH) server access.

Enable / Disable
    Enable / disable SSH access.

TCP port
    Enter the TCP port used for SSH access.

Accept connections from local networks
    SSH access enabled only for connections from local networks.
    
Accept connections from any network
    SSH access enabled for connections from any network.

Allow access for the root user
    Allow SSH access to the root user (administrative user).

Allow password authentication
    Allows access through SSH with simple password authentication.
    If not enabled, users will be able to authenticate
    only using a cryptographic key.

==============
Local networks
==============

For security reasons, some server services are available
only on the local network. Any private networks (eg. networks
connected in VPN) can have the same privileges as the local network
if configured in this panel.

The panel can also be used to configure static routes
which don't use the default gateway (for example
to reach private networks connected via dedicated lines).

Create / Modify
===============

Create a new route to a remote network and / or allow a
remote network to access services of the server.

Network address
    Network address for the new route.

Network Mask
    Network mask for the new route.

Router address
    Address of the gateway used to reach the specified network,
    this field is not required.

Description
    A free text field to record any annotation.

After route creation, you can only change
router address and description.

==============
User Profile
==============

Name
    It is the user's name, for example "John".

Surname
    The user's last name, for example "Smith".

External email address
    User email address from an external mail provider.
    If specified, this address is
    used by the system in the process of recovery and renewal
    password.

You can specify a custom value for the following fields,
otherwise values from  module *Data
organization* will be used (this module is available only to the system administrator).

* Company
* Office
* Address
* City
* Phone


Change password
===============

Change current password with a new password.

Current Password
    Enter the current password.

New password
    Enter the new password.

Repeat new password
    Repeat new password: must match the one *New Password* field.

====================
Organization details
====================

These fields contain default values for the company.
Provided data will be used as default when creating
new users.

For each user you can specify different values in the panel
Users, Details tab.
Changing these data replaces the default values for the
users who do not have custom fields.

**WARNING**: any change to the data entered re-creates the SSL certificates.


Company
    Enter the company name.
City 
    Enter the city of the company.
Office
    Enter the department or office whose members will have access
    the services of the server.
Phone
    Enter the phone number of the company.
Address
    Enter the address of the company.

=======
Network
=======

Change settings for network interfaces. Network interfaces in the system are automatically detected.

State
=====

Link
    Indicates whether the adapter is connected to any network device (eg. Ethernet
    cable connected to the switch).

Model
    Model of used network card.

Speed
    Indicates the speed that network card has negotiated (expressed in Mb/s).

Driver
    The driver the system uses to control the card.

Bus
    Network card physical bus (eg, PCI, USB).


Edit
====

Change settings of the network interface

Card
    Name of the network interface. This field can not be
    changed.

MAC Address
    Physical address of the network card. This field can not be
    changed.

Role
    The role indicates the destination of use of the interface, for example:

    * Green -> LAN Business
    * Red -> Internet, public IP

Mode
    Indicates which method will be used to assign the IP address to
    the network adapter. Possible values are *Static* and *DHCP*.

Static
    The configuration is statically allocated.

    * IP Address: IP address of the network card
    * Netmask: netmask of the network card
    * Gateway: server default gateway

DHCP
    The configuration is dynamically allocated (available only for
    RED interfaces)

========
View log
========

Find and display the contents of log files.

Find in log files
=================

Allow you to browse all the server log files and do
full searches into them.

Find
    Allow you to search for words and phrases within all
    server logs.

You can go directly to each log through the links
listed on the page.

Show single log
===============

Allow you to browse the contents of the selected log and 
follow the text flow in real time.

Close
    Close the selected log window and return to
    the main page.

Empty
    It allows you to empty the contents of the log window. The data
    are removed only from the display window, no
    changes are made to contents of the log.

Follow
    Update in real time the display window with the new
    information that are written into the log.

Stop
    Stops updating the real-time log  visualization.
   
========
Shutdown
========


Allows you to turn off or restart the server.
It's mandatory to shutdown the system before turning off the server.
The execution of these functions takes a few minutes.


WARNING! Clicking SHUTDOWN THE SYSTEM operation will start 
immediately.


Restart
    Restart the server terminating all running processes.

Power-off
    Turn off the server after completing all the running processes.
