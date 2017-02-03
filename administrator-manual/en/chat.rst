.. _chat-section:

====
Chat 
====

The :index:`chat` service uses the standard protocol :index:`Jabber`/:index:`XMPP` and support TLS on standard ports (5222 or 5223). 

The main features are: 

* Messaging between users of the system 
* Possibility to divide the users into groups, according to the company or department / office 
* Chat server administration
* Broadcast messages 
* Group chat 
* Offline messages 
* Transfer files over LAN 

All system users can access the chat using their own credentials.

Client
======

Jabber clients are available for all desktop and mobile platforms. 

Some widespread clients:

* Pidgin is available for Windows and Linux 
* Adium for Mac OS X 
* BeejibelIM for Android and iOS, Xabber only for Android

When you configure the client, make sure TLS (or SSL) is enabled.
Enter the user name and the domain of the machine. 

If |product| is also the DNS server of the network, the client should automatically find the server's address through special 
pre-configured DNS records. Otherwise, specify the server address in the advanced options.

Administrators
==============

All users within the group ``jabberadmins`` are considered administrators of the chat server. 

Administrators can: 

* Send broadcast messages 
* Check the status of connected users 


The group ``jabberadmins`` is configurable from :ref:`groups-section` page.
