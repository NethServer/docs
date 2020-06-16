.. _docker-section:

======
Docker
======

.. note::

  This package is not supported in |product| Enterprise 

Docker is an open platform for developing, shipping, and running applications. Docker enables you to separate your applications from your infrastructure so you can deliver software quickly. With Docker, you can manage your infrastructure in the same ways you manage your applications.

.. warning::

 Docker is customised to |product| and the firewall layer. The default bridge ``docker0`` is enabled to provide compatibility, however the official docker documentation `stated on why you should not use it <https://docs.docker.com/network/bridge/#differences-between-user-defined-bridges-and-the-default-bridge>`_. 
 Docker with |product| comes with 3 other networks called ``aqua``, ``aeria`` and ``macvlan``.

Official documentation
======================

The purpose of this documentation is to help you to install docker and enable the Portainer user interface. However all docker relative issues should be reported to the documentation or to the docker community.

The official documentation of docker can be found at : https://docs.docker.com/get-started/overview/



Installation
============

Install from the Software Center or use the command line: ::

  yum install nethserver-docker

Docker repository
=================

The official repository of docker is bundled but not enabled, the upgrade might break the running containers. It is advised to stop all containers before to upgrade ``docker-ce``. 

To upgrade to the latest stable version of docker: ::

 yum update --enablerepo=docker-ce-stable

to enable it permanently: ::

 config setprop docker enableRepository enabled
 signal-event nethserver-docker-update

Configuration
=============
If you have a free block device (required for production environments) assign it to Docker before starting it for the first time ::

 config setprop docker DirectLvmDevice /dev/sdb
 signal-event nethserver-docker-update

Review the current settings with ::

 config show docker

Network, is the IP network address of the aqua zone
IpAddress, is the IP address of the Docker host in the Network above

After each change, you have to restart docker ::

 signal-event nethserver-docker-update

Web user Interface
==================

`Portainer <https://www.portainer.io/>`_ is an interface to manage all containers running on this host or eventually on remote hosts, a property must be enabled before to create the portainer ::

  config setprop portainer status enabled
  signal-event nethserver-docker-update

The URL of portainer is ``https://<IP>:980/portainer/`` . The first time it is accessed, it asks to generate the administrative credentials.

Portainer is itself a container without important data, except the admin credential. Therefore if you need to do a clean installation you can remove the container and the data stored in ``/var/lib/nethserver/portainer``.

The official documentation of portainer can be found at : https://www.portainer.io/documentation/

Default network
===============

The default bridge docker0 is allowed in the firewall of |product|, any ports or the containers will be opened through shorewall. Any docker howto is supposed to be compatible.

Example of nginx container on port ``9001``: ::

 docker run  -dit --name nginx-test-01 -p 9001:80 --restart=unless-stopped nginx:alpine nginx-debug -g 'daemon off;'

Aqua network
============

A new firewall zone and docker network, ``aqua``. Basically, containers are attached to aqua and they can talk each other. IP traffic from other zones, like green and red must be configured with the usual Firewall rules and Port forwarding pages.

For an integration with system services, connections from the aqua zone are allowed to the MySQL/MariaDB port ``3306``. it means that a docker running on ``aqua`` can use the mysql database on the server.
More port rules can be opened to the system services running on the server with a esmith db command (these rules allow **only** the containers to connect to a service running on the server)::

 db dockrules set customName aqua TCPPorts 5141,5142 UDPPorts 5143,5144 status enabled
 signal-event firewall-adjust


You have to specify to use the network ``aqua`` for your container, the default ``docker0`` is another network. Each container on the network ``aqua`` will have an IP from the network ``172.28.0.0/16``. They can communicate each other and the server can ping each container.

For example (pihole on aqua with a static IP): :: 

 docker run -d --name nxfilter -v nxfilter-conf:/nxfilter/conf -v nxfilter-log:/nxfilter/log \
 -v nxfilter-db:/nxfilter/db -e TZ=Europe/Vienna \ 
 --net=aqua --ip=172.28.0.10/16 --restart=unless-stopped packetworks/nxfilter-base:latest


Aeria network
=============

.. note::

  This network is not standard on docker, the developer can be contacted at https://github.com/devplayer0/docker-net-dhcp

|product| docker provides a docker network named ``Aeria`` that is bound to a bridge. The container will have an IP attributed by the dhcp server of your local network, all containers will communicate like any servers on your network.

For the bridge creation the server manager could be used, if you have already installed the account provider Samba AD (nethserver-dc), you have already a bridge called ``br0``. 

.. warning::

  A bridge is mandatory to ``aeria``, you must accomplish this step before to go further: ``ip a`` can valid that the bridge is up and workable

To enable the Aeria network, the ``bridgeAeria`` property has to be set to the name of the bridge ::

 config setprop docker bridgeAeria br0
 signal-event nethserver-docker-update

The |product| DHCP module can be used to set IP addresses for the docker containers. By default docker containers use random MAC addresses so fixed ones need to be set for the containers to make DHCP reservations work.

Here is an example for starting pihole in the Aeria network and set the MAC address ::

 docker run -d --name pihole -e TZ="Europe/Vienna" -e WEBPASSWORD="admin" \ 
 -v "$(pwd)/etc-pihole/:/etc/pihole/" \ 
 -v "$(pwd)/etc-dnsmasq.d/:/etc/dnsmasq.d/" --cap-add NET_ADMIN \ 
 --net=aeria --mac-address=0e:6f:47:f7:26:1a --restart=unless-stopped pihole/pihole:latest

Aeria uses a docker plugin. To update the plugin ::

 signal-event nethserver-docker-plugin-update

Macvlan
=======

A container use TCP/UDP ports to communicate  outside of the server, this is the default networking. However your container could need to get a real IP on your network. Like this it will be reachable with ``http://IPofYourContainer`` 
instead of ``http://IPofYourServer:port``. A specific configuration like a DNS sinkhole (as pihole) must have an IP, because it might break the DNS resolution of your server. Therefore with a different IP, all hosts of your network will use the services of pihole like if it was on another server.

.. note::

  The difference between macvlan and aeria is that macvlan is not a plugin, it is an official network driver.

|product| docker provides a docker network named ``macvlan`` that must be bound to a bridge. Each container on the network ``macvlan`` must have a relevant IP in the range assigned to macvlan, all containers will communicate like any servers on your network.

For the bridge creation the server manager could be used, if you have already installed the account provider Samba AD (nethserver-dc), you have already a bridge called ``br0``. 

.. warning::

  A bridge is mandatory to ``macvlan``, you must accomplish this step before to go further: ``ip a`` can valid that the bridge is up and workable

Macvlan must be created by filling some important parameters, the goal is to create a container with an IP on your network, each parameter depends from your network setting.

- macVlanGateway : It is the gateway of your network, generally speaking it is your router (here **192.168.1.1**)

- macVlanLocalNetwork : It is the full network of your router (here **192.168.1.0/24** from **192.168.1.1** to **192.168.1.255**)

- macVlanNetwork : It is the restricted IP for ``macVlan0`` (here **192.168.1.224/27**, you can use **30 IP** for your containers from **192.168.1.225** to **192.168.1.254**)

- macVlanNic : It is the network interface where to run macvlan (**br0** here)

Create the network ::

  config setprop  docker macVlanGateway 192.168.1.1 macVlanLocalNetwork 192.168.1.0/24 macVlanNetwork 192.168.1.224/27 macVlanNic br0

Then trigger the event  ::

  signal-event nethserver-docker-update

You have to specify to use the network ``macvlan`` for your container, the default ``docker0`` is another network.

Docker creation example on macvlan ::

  docker run --net=macvlan -dit --name nginx-test-02 --ip=192.168.1.225 --restart=unless-stopped nginx:alpine nginx-debug -g 'daemon off;'

The container can be contacted at the relevant IP ::

  curl http://192.168.1.225

In case of the proposed CIDR doesn't fit your need, you should have a look to an `IP calculator <https://www.calculator.net/ip-subnet-calculator.html>`_

Issues
======

Please raise issues on `community.nethserver.org <http://community.nethserver.org/>`_.


Sources
=======

Source are available https://github.com/NethServer/nethserver-docker
