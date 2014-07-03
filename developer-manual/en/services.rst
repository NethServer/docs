========
Services
========

A :dfn:`service` is a software which usually runs in background.
The system will ensure :index:`service` status accordingly to its configuration.
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

Any software can configure the init system using the standard :command:`chkconfig` command.
This approach always work for third-party software.


On the other hand, if the service must be controlled by NethServer, create a new record inside configuration database: ::
  
  config set myservice service status enabled  

Where ``myservice`` is the name of the new service.

Make sure also there are defaults values inside the directory :file:`/etc/e-smith/db/configuration/defaults`: if the key is present
inside the configuration database, but not inside defaults, the service will be stopped.
Given the above example, create these files: ::

  mkdir -p /etc/e-smith/db/configuration/defaults/myservice
  echo "service" > /etc/e-smith/db/configuration/defaults/myservice/type
  echo "enabled" > /etc/e-smith/db/configuration/defaults/myservice/status 

Signal the new service to the system: ::

  signal-event runlevel-adjust

Add a new network service
=========================

If a service not controlled by NethServer needs one or more open ports, use the TCPPort(s) or UDPPort(s) prop to declare the port(s) and signal the firewall to open it: ::

  config set fw_myservice service status enabled TCPPort 12345 access private
  signal-event firewall-adjust

Otherwise, if the service is controlled by NethServer, you can add the properties directly to the service key. For the service *myservice* on above
example: ::

  config set myservice service status enabled TCPPort 12345 access private
  signal-event firewall-adjust

See :ref:`firewall_gateway-section`.
