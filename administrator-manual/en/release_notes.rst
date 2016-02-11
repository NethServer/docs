=============
Release notes
=============

|product| release |release|

.. include:: changelog.rst.inc

Known bugs
==========

* Only unattended mode installation works
* Inside the monitoring group, nethserver-adagios is known to NOT work
  (See: https://github.com/NethServer/dev/issues/5015)
* ntopng package will install all build chain (gcc, make, etc.), we are working with
  upstream to fix the package and remove unwanted dependencies
* Postfix can't be used as SMTP server if the server is joined to Active Directory

  

.. warning: 
   Upgrade from previous major release is not available in alpha.
  

