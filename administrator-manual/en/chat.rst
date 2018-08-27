.. _chat-section:

====
Chat 
====

The :index:`chat` service uses the standard protocol :index:`Jabber`/:index:`XMPP` and support TLS on standard ports (5222 or 5223). 

.. note::       With TLS capabilities, stricly configured servers will reject connections with your Ejabberd server 
                if the SSL/TLS certificate doesn't match the domain name and the two subdomains ``pubsub.*`` and ``conference.*``. 
                This certificate can be obtained for free with Let's encrypt.

The main features are: 

* Messaging between users of the system 
* Chat server administration
* Broadcast messages 
* Group chat 
* Offline messages 
* Transfer files over LAN 

All system users can access the chat using their own credentials.

.. note::       If |product| is bound to a remote Active Directory account provider
                a dedicated user account in AD is required by the module to be fully
                operational! See :ref:`join-existing-ad-section`.

Server to server (S2S)
======================

The XMPP system is federated by nature. Users with accounts on one server, if the :index:`S2S` is allowed, can communicate 
with users on other servers. For example, to federate with Google’s “GTalk” XMPP network, you need to have S2S enabled.

For this purpose, the SRV DNS record must be configured for your domain (https://wiki.xmpp.org/web/SRV_Records#XMPP_SRV_records).

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

Modules
=======

* Message Archive Management (mod_mam)

  mod_mam is the new module of archiving messages, if enabled, the messages will be stored  in the server and can probably 
  affect the data privacy of your users. The database of mod_mam can be purged automatically all X days.

