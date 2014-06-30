===============
Administration
===============

Dashboard
=========

The index:`Dashboard` page is the landing page after a successful login.
The page will display the :index:`status` and configurations of the system.

Shutdown
========

The machine where |product| is installed can be rebooted or halted from the :menuselection:`Shutdown` page.
Choose an option (reboot or halt) then click on submit button.

Always use this module to avoid bad shutdown which can cause data damages.

Log viewer
==========

All services will save operations inside files called :dfn:`logs`. 
The :index:`log` analysis is the main tool to find and resolve problems.
To analyze log files click in :menuselection:`Log viewer`.

This module allows to:

* start search on all server's logs
* display a single log
* follow the content of a log in real time


Remote access
=============

.. _trusted_networks-section:

Trusted networks
----------------

:dfn:`Trusted networks` are special networks (local or remote) allowed to access special server's services.

For example, hosts inside :index:`trusted networks` can access to:

* Server Manager
* Shared folders (SAMBA)

If users connected from VPNs must access system's services, add VPN networks to this page.

If the remote network is reachable using a router, remember to add a static route inside :ref:`static_routes-section` page.

Server Manager
--------------

It's possible to grant Server Manager's access to selected networks.
For example, if the server is inside a customer network, you should allow connections from remote management networks.

SSH
---

The :index:`SSH` (Secure Shell) should be always available.
SSH is a protocol to open remote shells over secure connections.

Default configuration allows authentication using password and public/private keys.


=====================
Organization contacts
=====================

Fields in this section are used to generate self-signed SSL certificates and for user creation.

.. note:: Any modification to these data will regenerate all SSL certificates. Most clients will must
   be reconfigured.


==============
User's profile
==============

All users can login to Server Manager using their own credentials.

After login, a user can :index:`change the password` and information about the account, like:

* Name and surname
* External mail address

The user can also overwrite fields set by the administrator:

* Company
* Office
* Address
* City

.. _static_routes-section:

==============
Static routes
==============

This page allow to create special :index:`static routes` which will use the specified gateway.
These routes are usually used to connect private network.

Remember to add the network to :ref:`trusted_networks-section`, if you wish to allow remote hosts to access local services.

