==========
Phone Home
==========

This tool is used to tracks all NethServer's installations around the world.

* Use API to get and set installation
* Visualize the installations in Google Maps with nice markers

Overview
=============
This tool is composed by two parts: **server** and **client** and the data are stored and read through REST APIs. The REST APIs can be found in ``index.php`` file. To send data to REST APIs check out the ``phone-home`` file in ``root/etc/cron.weekly``.

Configuration
=============
After the repository clonig, you must set the correct placeholders in certain files.

Server
------

config.php
^^^^^^^^^^
Line ``2`` change ``__dbhost__, __dbuser__, __dbpass__, __dbname__`` with your own credentials: ::

 $GLOBALS['$dbhost'] = "__dbhost__";
 $GLOBALS['$dbuser'] = "__dbuser__";
 $GLOBALS['$dbpass'] = "__dbpass__";
 $GLOBALS['$dbname'] = "__dbname__";

widget_map.html
^^^^^^^^^^^^^^^

Line ``53`` change ``__serverip__`` with the server ip used to host REST APIs: ::

  // ip server with api
  var server_ip = '__serverip__';


Create table in your database
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
After setting up your own credentials, simply run (MySQL syntax): ::

 CREATE DATABASE phonehome;
 GRANT ALL ON phonehome.* TO user IDENTIFIED BY 'password';

 CREATE TABLE IF NOT EXISTS phone_home_tb (
  uuid                  VARCHAR(40) PRIMARY KEY, 
  release_tag           VARCHAR(10) NOT NULL,
  ip                    VARCHAR(16) NOT NULL,
  country_code          VARCHAR(5),
  country_name          VARCHAR(40),
  country_location_lat  VARCHAR(40),
  country_location_lng  VARCHAR(40),
  reg_date              TIMESTAMP
 )


Client
------
phone-home
^^^^^^^^^^
Create a file named ``phone-home`` in ``/etc/sysconfig`` and set the correct infos: ::

 SERVER_IP=__serverip__
 PROXY_SERVER=__proxyserver__
 PROXY_USER=__proxyuser__
 PROXY_PASS=__proxypass__
 PROXY_PORT=__proxyport__

the variables ``PROXY_SERVER, PROXY_USER, PROXY_PASS, PROXY_PORT`` are not mandatory.