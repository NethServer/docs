=======
Microsoft SQL Server
=======

.. note::

  This package is not supported in |product| Enterprise


With this package you can install Microsoft SQL Server on NethServer: it will automatically configure Microsoft repository and default configuration.


Installation
============

To install this package go on Software Center and install Microsoft SQL Server application. Otherwise use this command:

    yum install -y nethserver-mssql --enablerepo=nethforge
    

Default configuration
=====================

When installed the module generates a default configuration as follow:
* Auto-generated SA password saved in /var/lib/nethserver/secrets/mssql
* Create default MSSQL databases (master, model, msdb, tempdb)
* Allow access to SQL service from Green network on default port 1433

User can change access network from Cockpit Services page or from Firewall section.

Database example:

    mssql-server=service
        ProductId=express
        ProductKey=
        TCPPort=1433
        access=green
        status=enabled


Install mssql-server service
============================

The package needs a first configuration. User had to go to Cockpit application and select MSSQL edition between these options: Evaluation, Developer, Web, Express, Standard, Enterprise. Alternatively it is possibile also to insert a product key.

You can do this also from command line:

    config setprop mssql-server ProductId <version>
    signal-event nethserver-mssql-save
    

Instead, if you want to configure a product key use these commands:
  
    config setprop mssql-server ProductId key
    config setprop mssql-server ProductKey <ProductKey>
    signal-event nethserver-mssql-save
    

.. note::

  After save event is launched, Microsoft package download will starts: this phase can be long, depending on Internet connection.


Now your SQL Server is ready to use!


Helpful actions
===============

Directly from Cockpit interface you can:
* create a new database under Databases page
* view and change SA password under Settings page
* see SQL Server status in MSSQL Dashboard page
* change SQL Server edition from Settings page


.. warning::

  Don't change SA password from SQL Server, but use Cockpit interface. Otherwise NethServer will not able to load correct informations and perform backup-data.


Backup and restore
==================

Configuration is saved with backup-config event. After you've restored configuration on new server download of MSSQL package will starts in post-config-restore event.
Database are automatically saved in backup-data event. They will be restored in post-restore-data.
