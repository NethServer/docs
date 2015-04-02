========
ownCloud
========

`ownCloud <http://owncloud.org/>`_ provides universal access to your files via the web,
your computer or your mobile devices wherever you are. It also provides a platform to easily
view and synchronize your contacts, calendars and bookmarks across all your devices and enables
basic editing right on the web.

**Key features:**

* preconfigure :index:`ownCloud` with mysql and default access credential
* preconfigure httpd 
* integration with |product| system users and groups
* documentation
* backup ownCloud data with nethserver-backup-data tool


Installation
============

The installation can be done through the |product| web interface.
After the installation:

* open the url https://your_nethserver_ip/owncloud
* use **admin/Nethesis,1234** as default credentials
* change the default password

LDAP access authentication is enabled by default, so each user can login with its system credentials. 
After the installation a new application widget is added to the |product| web interface dashboard.

LDAP Configuration
==================

.. note:: New installations do not need the LDAP configuration because it is done automatically.

#. Copy the LDAP password using the following command: ::

    cat /var/lib/nethserver/secrets/owncloud

#. Login to ownCloud as administrator
#. Search LDAP user and group backend: *Applications -> LDAP user and group backend*
#. Enable "LDAP user and group backend"
#. Configure server parameters: *Admin -> Admin -> Server tab*
#. Fill "Server" tab with these parameters: ::

    Host: localhost:389
    Port: 389
    DN user: cn=owncloud,dc=directory,dc=nh
    Password: "you can use copied password"
    DN base: dc=directory,dc=nh

#. Fill "User filter" tab with: ::

    Modify coarse filter: (&(objectClass=person)(givenName=*))

#. Fill "Access filter" tab with: ::

    Modify coarse filter: uid=%uid

#. Fill "Group filter" tab with: ::

    Modify coarse filter: (&(objectClass=posixGroup)(memberUid=*))

#. Configure "Advanced" tab with: ::

    Directory settings
        Display username: cn
        User structure base: dc=directory,dc=nh
        Display group name: cn
        Group structure base: dc=directory,dc=nh
        Group-member association -> memberUid

    Special Attributes
        Email field: email

#. Configure "Expert" tab with: ::

    Internal username Attribute: uid
    Click on "Clear Username-LDAP user mapping" 

#. Click the "Save" button

LDAP Note
=========


User list
---------

After ownCloud LDAP configuration, the user list can show some usernames containing random numbers.
This is because ownCloud ensures that there are no duplicate internal usernames as reported in section `Internal Username. <http://doc.owncloud.org/server/6.0/admin_manual/configuration/auth_ldap.html#expert-settings>`_

If two administrator users are present, they are of ownCloud and LDAP. So you can remove that of ownCloud after have assigned the LDAP one to the administrator group. So, as a result, you can use only the LDAP administrator user. You can do this by the following steps:

#. login to ownCloud as administrator
#. open the user list: *admin -> Users*
#. change the group of "admin_xxx" user, checking "admin"
#. change the password of ownCloud admin user
#. logout and login with LDAP admin user
#. delete ownCloud admin user (named "admin")


Domain or IP change
-------------------

When you change the domain name or IP address of |product|, you have to adapt the ``trusted_domains`` key into the file: ::

 /var/www/html/owncloud/config/config.php

Modify the old values with the new ones. For example if the domain name and IP address were *oldname.server.it 192.168.5.250* and the new ones are *newname.server.it 192.168.5.251*, the old file was: ::

    ...
    'trusted_domains' =>
    array (
        0 => '192.168.5.250',
        1 => 'oldname.server.it',
    ),
    ...

and must be changed as: ::

    ...
    'trusted_domains' =>
    array (
        0 => '192.168.5.251',
        1 => 'newname.server.it',
    ),
    ...
