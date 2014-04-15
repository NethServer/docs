===
VPN
===

VPN configuraciones admitidas:

1. Conexión de un terminal remoto a la red interna 
    (Roadwarrior), basado en L2TP/IPsec o OpenVPN. 

2. Conexión de dos redes remotas (net2net), basado en OpenVPN.


Cuenta
=======
La ficha cuenta permite gestionar usuarios para las conexiones VPN al servidor local. Los usuarios pueden ser usuarios normales del sistema o dedicados exclusivamente al servicio VPN (sin servicios estándar como el correo electrónico).

Crear nueva
-----------

Permitir la creación de un nuevo usuario. Para cada usuario, el sistema 
crea un certificado x509. 

VPN sólo 
     El nombre que se utiliza para el acceso VPN. Puede contener sólo 
     minúsculas, números, guiones, guiones bajos (_) y 
     debe comenzar con una letra minúscula. Por ejemplo, "luisa", 
     "jsmith" y "liu-jo" es un nombre de usuario válido, mientras que "4Friends" 
     "Franco Blacks" y "aldo / error" no lo son. 

Usuario del Sistema 
     Habilitar el acceso VPN para un usuario ya existente en el sistema. 
     El usuario puede seleccionar de la lista desplegable. 

Red de control remoto 
     Introduzca esta información sólo cuando se desea crear una VPN nt2net. 
     Estos campos se utilizan por el servidor local para crear correctamente 
     rutas a la red remota. 

    * Dirección de red: la dirección de red de la red remota. Ejemplo: 10.0.0.0 
    * Máscara de red: máscara de red de la red remota. Por ejemplo: 255.255.255.0
    
Cliente
=======

El cliente VPN le permite conectarse al servidor a otro servidor VPN 
con el fin de crear una VPN net2net. Actualmente sólo OpenVPN net2net son compatibles.



