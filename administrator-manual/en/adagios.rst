=======
Adagios
=======

`Adagios <http://adagios.org/>`_ is a web based :index:`Nagios` configuration interface built to be simple 
and intuitive in design, exposing less of the clutter under the hood of Nagios. Additionally :index:`Adagios` 
has a rest interface for both status and configuration data as well a feature complete status 
interface that can be used as an alternative to Nagios web interface.

**Key features:**

* full view/edit of hosts,services, etc
* tons of pre-bundled plugins and configuration templates
* network scan
* remote installation of linux/windows agents
* modern Status view as an alternative to default nagios web interface
* backup Adagios data with |product| backup data tool
* rest interface for status of hosts/services and for for viewing and modifying configuration
* full audit of any changes made


Installation
============

The installation can be done through the |product| web interface.
After the installation:

* enable the admin account (see :ref:`admin_user-section` for details)
* open the url https://your_nethserver_ip/adagios
* use :samp:`admin` credentials to access web interface

For more information, see official documentation:

* http://adagios.org/
* https://github.com/opinkerfi/adagios/wiki

