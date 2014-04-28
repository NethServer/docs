========
Services
========

A :dfn:`service` is a software which usually runs in background.
The system will ensure :index:`service` status accordignly to its configuration.
A service in :file:`configuration` database is something like this: ::

  httpd=service
      status=enabled
      access=public
      TCPPorts=80,443

Where :file:`httpd` is the service name and ``status`` tells the system if the service should be ``enabled`` or ``disabled``.

When the :index:`status` property is switched between enabled/disabled state, the change will be reflected into runlevel configuration using :command:`chkconfig` command. If both Upstart and SysV scripts are present, Upstart has the precedence and SysV script is disabled. For example see `httpd-admin` service.    

This is what :command:`runlevel-adjust` event and action do for all configured services. 
There is also another action called :command:`adjust-services` which does the same thing for services registered on a single event.

A service without a record in the configuration database is ignored and can be manually manged using :command:`chkconfig` and :command:`service` commands.

For more information on ``TCPPorts`` and ``access`` properties, see firewall section.

Control a service
=================

Enable a service: ::
  
  config setprop myservice status enabled  
  signal-event runlevel-adjust

Disable a service: ::
  
  config setprop myservice status disabled 
  signal-event runlevel-adjust

Where ``myservice`` is the service name to be enabled or disabled.

Add a new service
=================

Create a new record inside configuration database: ::
  
  config set myservice service status enabled  

Where ``myservice`` is the name of the new service.
Signal the new service to the system: ::

  signal-event runlevel-adjust
