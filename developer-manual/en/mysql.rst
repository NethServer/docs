=====
MySQL
=====

Manage and configure MySQL server.

When installed, the module will trigger the ``mysql_secure_installation`` script generating default configuration:

* Auto-generated root password saved in /var/lib/nethserver/secrets/mysql
* No anonymous user
* No remote root login allowed
* No test database

Differences from SME Server:

* InnoDB tables enabled, removed ``InnoDB`` property
* TCP connections enabled: can be disabled setting ``LocalNetworkingOnly`` property to ``yes``
* Removed ``OpenFilesLimit`` property
* ``max_allowed_packet`` option is 1MB (as MySQL default). To change the value set the ``MaxAllowedPacket`` property

The root password is also saved in :file:`/root/.my.cnf`, so the root user can use mysql client without typing any password.

Database example: ::

 mysqld=service
    LocalNetworkingOnly=no
    MaxAllowedPacket=16MB
    TCPPort=3306
    status=enabled


Loading data
============

There is a special action ``/etc/e-smith/events/actions/nethserver-mysql-init`` which can be used to load data inside the database.

*OBSOLETE*: For backward compatibility with SME Server, the ``mysql.init`` service can also be used instead of the new action. The use of the service is HIGHLY discouraged.

When launched, the script will search for links in ``/etc/e-smith/sql/init`` directory.
If a link point to a file with *.sql* extension, the content of the file will be loaded using the ``mysql`` command.
Otherwise if the file is executable it will be simply executed. 
If no error occurs, the link will be removed.

Given ad simple ``/tmp/test.sql`` script, you can load it using this commands: ::

  ln -s /tmp/test.sql /etc/e-smith/sql/init/temp.sql
  service mysql.init start

