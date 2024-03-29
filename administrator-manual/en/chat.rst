.. _chat-section:

====
Chat 
====

The :index:`chat` service uses the standard protocol :index:`Jabber`/:index:`XMPP` and support TLS on standard ports (5222 or 5223). 

The main features are: 

* Messaging between users of the system 
* Chat server administration
* Broadcast messages 
* Group chat 
* Offline messages 
* Transfer files over LAN
* S2S
* Message archiving 

All system users can access the chat using their own credentials.

.. note::       If |product| is bound to a remote Active Directory account provider
                a dedicated user account in AD is required by the module to be fully
                operational! See :ref:`join-existing-ad-section`.

.. only:: nscom
.. note::
               Nethserver-ejabberd use a version of ejabberd known as stable. 
               System administrator and developers might need a version more recent of ejabberd, 
               in that case you could install nethserver-ejabberd-next (NethForge Repository) and download after manually the ejabberd version 
               you need on the `website <https://www.process-one.net/en/ejabberd/downloads/>`_. 
               Please note that you will need to add your custom-templates or configuration files.
               if you think that a change can be valuable to the NethServer community, 
               please open a pull-request to the `repository <https://github.com/NethServer/nethserver-ejabberd-next>`_


Configuration
=============

All configuration options are available from *Configuration* page inside the **ejabberd** application.
Main options are:

* enable and disable ejabberd daemon
* enable built-in web administration interface

Under the *Advanced options* section, the administrator can also configure:

- S2S federation
- message archive
- file upload to exchange data among clients using URL
- file transfer speed

Server to server (S2S)
----------------------

The XMPP system is federated by nature. If :index:`S2S` is enabled, users with accounts on one server
can communicate with users on remote servers.
S2S allows for servers communicating seamlessly with each other, forming a global 'federated' IM network.

For this purpose, the SRV DNS record must be configured for your domain (https://wiki.xmpp.org/web/SRV_Records#XMPP_SRV_records)
and the server must have a valid SSL/TLS certificate.

Message Archive Management
--------------------------

Message Archive Management (mod_mam) implements Message Archive Management as described in `XEP-0313 <http://xmpp.org/extensions/xep-0313.html>`_.
When enabled, all messages will be stored inside the server and compatible XMPP clients can use it to store their chat history on the server.

The database can store a maximum of 2GB of messages, archived messages can be purged automatically.
To configure message retention policy, set :guilabel:`Clean messages older than X days` option.

.. note::

   If enabled, this module will store every message sent between users.
   This behavior will affect the privacy of your users.


Administrators
==============

All users within the group ``jabberadmins`` are considered administrators of the chat server. 

The group ``jabberadmins`` must be created and configured from the :ref:`groups-section` page.

Administrators can: 

* Send broadcast messages 
* Check the status of connected users 

Clients
=======

Jabber clients are available for all desktop and mobile platforms. 

Some widespread clients:

* Pidgin is available for Windows and Linux 
* Adium for Mac OS X 
* BeejibelIM for Android and iOS, Xabber only for Android

When you configure the client, make sure TLS (or SSL) is enabled.
Enter the user name and the domain of the machine. 

If |product| is also the DNS server of the network, the client should automatically find the server's address through special 
pre-configured DNS records. Otherwise, specify the server address in the advanced options.

With TLS capabilities, strictly configured servers or clients could reject connections with your Ejabberd server 
if the SSL/TLS certificate doesn't match the domain name.
Also, the certificate should contain two sub-domains ``pubsub.*`` and ``conference.*``.
This certificate can be obtained for free with Let's Encrypt (see :ref:`server_certificate-section`).


