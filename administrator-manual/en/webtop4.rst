========
WebTop 4
========

WebTop is a full-featured groupware which implements Active Sync protocol.

Access to web interface is: ``http://<server_name>/webtop``.

.. note::
   WebTop and SOGo can't be installed on the same machine.
   Before installing WebTop, make sure SOGo is not present.

Authentication
==============

No matters how many mail domains are configured, the login to the web application is
always with simple user name and password.

Login to Active Sync account is with <username>@<domain> where domain is the domain
of the server.

**Example**

* Server name: mymail.mightydomain.com
* Alternative mail domain: baddomain.net
* User: goofy

Login to web application: goofy

Login to Active Sync: goofy@mightydomain.com

