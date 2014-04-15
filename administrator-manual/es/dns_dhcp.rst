============ 
DNS y DHCP 
============ 

Gestión de alias de servidor, nombres de host y el servidor DHCP. 

Servidor de Alias 
================= 

Los alias son nombres alternativos para este servidor. Por ejemplo, si el 
nombre del servidor es *nethserver.nethesis.it*, un alias puede ser 
*mail.nethesis.it*. El servidor usará su propia dirección IP 
para el nombre de alias. 

Crear / Modificar 
--------------------- 

Permite crear un nuevo alias para este servidor. 

Nombre de host 
     El nombre de host que desea agregar o modificar. Puede contener sólo 
     letras, números y guiones y deben comenzar con una letra o un número.

Descripción 
     Una descripción opcional útil para identificar el alias. 


DHCP 
==== 

El DHCP (Dynamic Host Configuration Protocol) le permite 
asignar direcciones IP a los clientes de la red local 



Configure 
--------- 

Configurar el servidor DHCP. 

Desabilitado 
     El servidor DHCP se desactivará y los clientes de LAN no recibirá 
     la dirección de una manera automática por este servidor. Seleccione este 
     opción si hay otro servidor DHCP en su red local.

Enabled
    The server will issue IP addresses to computers on the local network (recommended).

Start
    The first IP address in the range assigned to the clients on the LAN.

End
    The last IP address of the range, addresses between Start and End will ge assigned to clients.

Create / Modify
---------------------

Adds a new static allocation (reservation) to the DHCP server.
The device with the specified MAC address will always receive the
specified IP Address.

Host Name
    The host name you want to assign to clients on the LAN with the specified
    IP address.

Description
    An optional description to identify the system.

IP Address
    The IP address you want to assign.

MAC Address
    The MAC address of the network system (eg 11:22:33:44:55:66:77:88).


DNS
===

The DNS (Domain Name System) is responsible for Domain Name Resolution
(eg www.nethesis.it) into their corresponding numerical IP addresses
(Eg. 10.11.12.13) and vice versa. |product| delegates the resolution of
names to the configured DNS servers, but you can specify addresses
for arbitrary selected names. For example, you can configure the
system for responding to requests for facebook.com with the IP address 
0.0.0.0, achieving the effect of making the Facebook site unreachable.


Configure
---------

Click Configure to enter the addresses of the DNS servers that
|product| will contact to resolve names.

Primary DNS
    The address of the primary server to contact for resolving names (mandatory).

Secondary DNS
    The address of the secondary server to be contacted in case the primary is not responding (optional).

Create / Modify
---------------------

Click Create to assign a host name to an IP address. The
server will return the IP address configured for requests of its name.


Host Name
    The domain name, for example www.nethesis.it. It's possible to create
    names for the local domain, which is useful for giving a mnemonic name to
    devices configured with static IP or for any domain,
    which take precedence over the provider's DNS server (see
    facebook.com example above).

IP Address
    The IP address of the host name.

Description
    An optional comment for the host name (example:
    "Block facebook" or "video server").
