====================
Cloud content filter
====================

The cloud content filtering allows you to profile and block the user web traffic.
The system allows you to create multiple profiles based on user name (authenticated web proxy)
or on the IP source (transparent or manual proxy).

Preliminary operations
======================

You need to access https://register.nethesis.it, inside `Administration` section, and add the server to the `Cloud content filter` section.

Configuration
===============

The configuration is composed of two parts:

* a profile associated to a group of users or a host group
* a selection of blacklists associated with the created profile

Profiles must be created through the web interface of |product|,
while the association between profiles and blacklist can be configured
accessing the FlashStart remote interface.
To access FlashStart remote interface, click on :guilabel:`Configure` inside
the :guilabel:`Cloud content filter` page.

Manual or transparent proxy
---------------------------

Using manual or transparent proxy, you can profile the users only through the source IP address.

Steps:

* Create a host group
* Open the tab :guilabel:`IP profiles` and click on :guilabel:`Create new`
* Select a host group and enter a description
* To select the blacklist associated with the profile, click on :guilabel:`Configure`
  and access the FlashStart


Authenticated proxy
--------------------

Using authenticated proxy, you can profile the users through the user name.

Steps:

* Create a user group
* Open the tab :guilabel:`User profiles` and click on :guilabel:`Create new`
* Select a user group and enter a description
* To select the blacklist associated with the profile, click on :guilabel:`Configure`
  and access the FlashStart


.. note::
  
   The filter will work only if all client are using the web proxy.
