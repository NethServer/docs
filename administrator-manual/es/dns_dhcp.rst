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

Nombre del host
    El nombre de host que desea agregar o modificar. Puede contener sólo letras, números y guiones y deben comenzar con una letra o un número.

Descripcion
    Una descripción opcional útil para identificar el alias. 


DHCP 
==== 

El DHCP (Dynamic Host Configuration Protocol) le permite 
asignar direcciones IP a los clientes de la red local 



Configure 
--------- 

Configurar el servidor DHCP. 

Desabilitado
    El  servidor DHCP se desactivará y los clientes de LAN no recibirá la dirección de una manera automática por este servidor. Seleccione esta opción si hay otro servidor DHCP en su red local.

Activado
    El servidor emitirá direcciones IP a los equipos de la red local (recomendado).

Comienzo
    La primera dirección IP del rango asignado a los clientes en la LAN.

Final
    La última dirección IP del rango, las direcciones entre inicio y fin se ge asignado a los clientes.
 

Crear / Modificar 
--------------------- 

Agrega una nueva asignación estática (reserva) para el servidor DHCP. 
El dispositivo con la dirección MAC especificada siempre recibirá la 
Dirección IP especificada. 

Nombre del host
    El nombre de host que desea asignar a los clientes en la LAN con la especificado Dirección IP.

Descripcion
    Una descripción opcional para identificar el sistema.

Direccion IP 
    La dirección IP que desea asignar.

Direccion MAC 
    La dirección MAC del sistema de red (por ejemplo 11:22:33:44:55:66:77:88).


DNS 
=== 

El DNS (Domain Name System) es responsable de la resolución de nombres de dominio
(por ejemplo www.nethesis.it) en sus direcciones IP numéricas correspondientes 
(Ej. 10.11.12.13), y viceversa. |Product| delega la resolución de 
nombres a los servidores DNS configurados, pero se puede especificar direcciones 
para los nombres seleccionados arbitrarias. Por ejemplo, puede configurar el 
sistema para responder a las solicitudes de facebook.com con la dirección IP 
0.0.0.0, logrando el efecto de hacer que el sitio de Facebook inalcanzable.


Configure 
--------- 

Haga clic en Configurar para ingresar las direcciones de los servidores DNS que 
|product| se pondrá en contacto para resolver nombres. 

DNS primario
    La dirección del servidor primario de contacto para la resolución de nombres (obligatorio).

DNS secundario
    La dirección del servidor secundario para ser contactado en caso de que el principal no está respondiendo (opcional). 

Crear / Modificar 
--------------------- 

Haga clic en Crear para asignar un nombre de host a una dirección IP. la 
servidor devolverá la dirección IP configurada para peticiones de su nombre.

Nombre de host
    El nombre de dominio, por ejemplo www.nethesis.it. Es posible crear nombres para el dominio local, que es útil para dar un nombre a mnemónico dispositivos configurados con IP estática o para cualquier dominio, que prevalecen sobre el servidor DNS del proveedor (véase facebook.com ejemplo anterior).

Direccion IP
    La dirección IP del nombre de host.

Descripcion
    Un comentario opcional para el nombre de host (ejemplo:
     "Bloquear facebook" o "servidor de video").
