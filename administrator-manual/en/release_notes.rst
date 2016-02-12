=============
Release notes
=============

|product| release |release|

.. include:: changelog.rst.inc

Testing
=======

Please, help us testing the alpha release!
Check out this wiki page for more details: http://wiki.nethserver.org/doku.php?id=developer:nethserver_7_needs_testing

Known bugs
==========

* Only unattended mode installation works
* Inside the monitoring group, nethserver-adagios is known to NOT work
  (See: https://github.com/NethServer/dev/issues/5015)
* ntopng package will install all build chain (gcc, make, etc.), we are working with
  upstream to fix the package and remove unwanted dependencies
* Postfix can't be used as SMTP server if the server is joined to Active Directory
* Inside the mail server group, nethserver-fetchmail is not fully functional.
  We are searching for a good replacement: https://github.com/NethServer/dev/issues/5021

  

.. warning: 
   Upgrade from previous major release is not available in alpha.
  

