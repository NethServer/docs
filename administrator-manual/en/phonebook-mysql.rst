=========
Phonebook
=========

The |product| phonebook allows to collect contacts from multiple sources. After collecting the data, 
the contacts will be accessible in read-only mode from many clients.

You should add or edit any contacts inside the source, not inside the phonebook itself.

Synchronization of contacts from various external sources is performed by default every night, 
the command to force it: ::

 /usr/share/phonebooks/phonebook

.. warning:: If during synchronizations the data source are unreachable, the phonebook will be empty.

The phonebook is accessible using LDAP, only if enabled, using this base DN: ::

 dc=phonebook,dc=nh

The web interface allows to enable the import from:

- publicly shared SOGo address book
- shared contacts from |product_cti|
- speed dial from  |product_voice|

You can import contacts from other source using custom scripts inside: ::

 /usr/share/phonebooks/scripts

Custom scripts can be written in any language, but each script must be executable. 
Example: ::

 chmod a+x /usr/share/phonebooks/scripts/mioscript.sh

The ``/usr/share/phonebooks/scripts`` is already part of configuration backup.
Inside the ``/usr/share/phonebooks/samples/`` directory, you can find many custom script examples.

If you need to access external databases (Mysql,PostgreSQL), you can create a new ODBC record.

ODBC configuration
------------------

1. Define the ODBC record describing the database connection

Example MySql: ::

 config set miarubrica ODBC Description "MiaRubrica" Driver "MySQL" Server "localhost" Database miarubrica Port 3306
   
Example PostgreSQL ::

 config set miarubrica ODBC Description "MiaRubrica" Driver "PostgreSQL" Server 192.168.5.168 Database miarubrica Port 5432

Example MSSQL ::

 config set business ODBC Description "MSSQL" Driver "MSSQL" Server 192.168.5.169 Database PROVA Port 1433

2. Execute: ::

 signal-event nethserver-unixODBC-update

Test
----

To test if the configuration is working: ::

 isql -v <isdn> <user> <password>

 isql -v miarubrica sa test
 +---------------------------------------+
 | Connected!                            |
 |                                       |
 | sql-statement                         |
 | help [tablename]                      |
 | quit                                  |
 |                                       |
 +---------------------------------------+

Then, try to execute a query ::

 SQL> select * from Customers
 ....
 SQL> quit


Database details
----------------

::

 Database: phonebook
 Table: phonebook

Display phonebook fields: ::

 mysql -e "describe phonebook.phonebook"

