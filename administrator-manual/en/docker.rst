.. _docker-section:

======
Docker
======

.. note::

  This package is not supported in |product| Enterprise 

Docker is an open platform for developing, shipping, and running applications. Docker enables you to separate your applications from your infrastructure so you can deliver software quickly. With Docker, you can manage your infrastructure in the same ways you manage your applications.

.. warning::

 Docker is customised to NethServer and the firewall layer. It means that the default bridge ``docker0`` is disabled and we use other bridge called ``aqua`` and ``aeria``.
 If you have still some doubts why you should never use the default bridge ``docker0``, the official docker documentation `stated on it <https://docs.docker.com/network/bridge/#differences-between-user-defined-bridges-and-the-default-bridge>`_.

Official documentation
======================

The purpose of this documentation is to help you to install docker and enable the Portainer user interface. However all docker relative issues should be reported to the documentation or to the docker community.

The official documentation of docker can be found at : https://docs.docker.com/get-started/overview/



Installation
============

Install from the Software Center or use the command line: ::

  yum install nethserver-docker


Web user Interface
==================

`Portainer <https://www.portainer.io/>`_ is an interface to manage all containers running on this host or eventually on remote hosts, a property must be enabled before to create the portainer ::

  config setprop portainer status enabled
  signal-event nethserver-docker-update

The URL of portainer is ``https://<IP>:980/portainer/`` . The first time it is accessed, it asks to generate the administrative credentials.

Portainer is itself a container without important data, except the admin credential. Therefore if you need to do a clean installation you can remove the container and the data stored in ``/var/lib/nethserver/portainer``.

The official documentation of portainer can be found at : https://www.portainer.io/documentation/

Aqua network
============

A new firewall zone and docker network, ``aqua``. Basically, containers are attached to aqua and they can talk each other. IP traffic from other zones, like green and red must be configured with the usual Firewall rules and Port forwarding pages.

For an integration with system services, connections from the aqua zone are allowed to the MySQL/MariaDB port ``3306``. it means that a docker running on ``aqua`` can use the mysql database on the server.
More port rules can be opened to the system services running on the server with a esmith db command ::

 db dockrules set customName aqua TCPPorts 5141,5142 UDPPorts 5143,5144 status enabled
 signal-event firewall-adjust


You have to specify to use the network ``aqua`` for your container, the default ``docker0`` doesn't exist. Each container on the network ``aqua`` will have an IP from the network ``172.28.0.0/16``. They can communicate each other and the server can ping each container.

For example (pihole on aqua with a static IP): :: 

 docker run -d --name nxfilter -v nxfilter-conf:/nxfilter/conf -v nxfilter-log:/nxfilter/log \
 -v nxfilter-db:/nxfilter/db -e TZ=Europe/Vienna \ 
 --net=aqua --ip=172.28.0.10/16 --restart=unless-stopped packetworks/nxfilter-base:latest


Aeria network
=============

NethServer docker provides a docker network named ``Aeria`` that is bound to a bridge. The container will have an IP attributed by the dhcp server of your local network, all containers will communicate like any servers on your network.

For the bridge creation the server manager could be used, if you have already installed the account provider Samba AD (nethserver-dc), you have already a bridge called ``br0``. 

.. note::

  A bridge is mandatory to ``aeria``, you must accomplish this step before to go further: ``ip a`` can valid that the bridge is up and workable

To enable the Aeria network, the ``bridgeAeria`` property has to be set to the name of the bridge ::

 config setprop docker bridgeAeria br0
 signal-event nethserver-docker-update

The NethServer DHCP module can be used to set IP addresses for the docker containers. By default docker containers use random MAC addresses so fixed ones need to be set for the containers to make DHCP reservations work.

Here is an example for starting pihole in the Aeria network and set the MAC address ::

 docker run -d --name pihole -e TZ="Europe/Vienna" -e WEBPASSWORD="admin" \ 
 -v "$(pwd)/etc-pihole/:/etc/pihole/" \ 
 -v "$(pwd)/etc-dnsmasq.d/:/etc/dnsmasq.d/" --cap-add NET_ADMIN \ 
 --net=aeria --mac-address=0e:6f:47:f7:26:1a --restart=unless-stopped pihole/pihole:latest

Aeria uses a docker plugin. To update the plugin ::

 signal-event nethserver-docker-plugin-update


Docker repository
=================

The official repository of docker is enabled to update the latest stable version.

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

Issues
======

Please raise issues on `community.nethserver.org <http://community.nethserver.org/>`_.


Sources
=======

Source are available https://github.com/NethServer/nethserver-docker
