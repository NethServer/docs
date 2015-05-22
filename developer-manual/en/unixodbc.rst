========
UnixODBC
========

This package contains templates that generates ODBC configuration.

/etc/odbc.ini
=============

The template that generates this file scan all configuration db searching for a key that has type=odbc (or ODBC for backward compatibility with SMEserver) and generates a section in /etc/odbc.ini.
For example, this is ODBC object is used for asterisk cdr database: ::

 # config show odbc-asteriskcdr
 odbc-asteriskcdr=odbc
    Database=asteriskcdrdb
    Description=ODBC on asteriskcdrdb
    Driver=MySQL
    Port=3306
    Server=localhost

this object generates the /etc/odbc.ini section: ::

  [odbc-asteriskcdr]
  Server = localhost
  Database = asteriskcdrdb
  Driver = MySQL
  Port = 3306
  Description = ODBC on asteriskcdrdb

/etc/odbcinst.ini
=================

This templates contains configuration for ODBC drivers. By default there are only MySQL and PostgreSQL driver configurated. The nethserver-unixODBC package requires those to be installed to: ::

  # rpm -q --requires nethserver-unixODBC
  ...
  mysql-connector-odbc                                                                                                                                                             
  postgresql-odbc                                                                                                                                                                  
  ...


Usage
=====

Creation of a new ODBC driver is as simply as launching: ::

  config set <new ODBC object name> odbc Description <description> Driver <MySQL|PostgreSQL> Server <server hostname> Database <database name> Port <database port>
  signal-event nethserver-unixODBC-update

