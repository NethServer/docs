========
WebTop 4
========

WebTop is a full-featured groupware which implements Active Sync protocol.

Access to web interface is: ``http://<server_name>/webtop``.

.. note::
   WebTop and SOGo can't be installed on the same machine.
   Before installing WebTop, make sure SOGo is not present.

.. warning::
   Remember to change the admin password just after installation. See :ref:`webtop_admin-section`.

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

.. _webtop_admin-section:

Admin user
----------

After installation, WebTop will be accessible with a super user.
Credentials are:

* User: admin
* Password: admin

Admin user password can be changed with this command: ::

    su - postgres -c "psql webtop -c \"UPDATE users set password='_your_password_' WHERE login='admin'\";" 
