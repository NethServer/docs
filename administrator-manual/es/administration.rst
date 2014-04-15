================= 
El acceso remoto 
================= 

Se puede permitir el acceso a la interfaz web desde ordenadores en redes remotas. Añadir redes prohibidas aquí. 

Hosts habilitados pueden acceder a la interfaz web a través de HTTPS. 


=================
Acceso a la Web 
=================

El acceso a la interfaz web de configuración. 

Dirección de red 
  Esta es la dirección desde la que acceder a la interfaz web se permitirá  Web. 

Máscara de red 
  Para permitir el acceso a un solo host, utilice como máscara de subred  255.255.255.255.
    
=== 
SSH 
=== 

Administrar el acceso al servidor Secure Shell (SSH). 

Activar / Desactivar 
     Activar / desactivar el acceso SSH. 

Puerto TCP 
     Introduzca el puerto TCP utilizado para el acceso SSH. 

Aceptar conexiones de redes locales 
     Acceso SSH habilitado sólo para conexiones de redes locales. 

Aceptar conexiones desde cualquier red 
     Acceso SSH habilitado para las conexiones desde cualquier red. 

Permitir el acceso para el usuario root 
     Permitir el acceso SSH para el usuario root (usuario administrador). 

Permitir la autenticación de contraseña
Permite el acceso a través de SSH con autentificación de contraseña simple. 
     Si no está habilitada, los usuarios podrán autenticarse sólo usando una clave criptográfica. 

============== 
Redes locales 
============== 

Por razones de seguridad, algunos servicios de servidor están disponibles sólo en la red local. 
Cualquier redes privadas (por ejemplo,
redes conectados en VPN) puede tener los mismos privilegios que la red local 
si está configurado en este panel. 

El panel también puede ser usado para configurar rutas estáticas 
que no utilizan la puerta de enlace predeterminada (por ejemplo, 
para llegar a las redes privadas conectadas a través de líneas dedicadas).   

=================
Crear / Modificar 
================= 

Crea una nueva ruta a una red remota y / o permitir que un 
red a distancia para acceder a los servicios del servidor. 

Dirección de red 
     Dirección de red para la nueva ruta. 

Máscara de red 
     Máscara de red para la nueva ruta. 

Dirección del router
   Dirección de la puerta de enlace utilizado para llegar a la red especificada, 
     no se requiere este campo. 

Descripción 
     Un campo de texto libre para registrar cualquier anotación. 

Después de la creación de rutas, sólo se puede cambiar 
dirección del router y la descripción. 

==================
Perfil del usuario 
==================

Nombre 
     Es el nombre del usuario, por ejemplo "Juan". 

Apellido 
     El apellido del usuario, por ejemplo, "Smith". 

Dirección de correo electrónico externa 
     Dirección de correo electrónico del usuario de un proveedor de correo externo. 
     Si se especifica, esta dirección es 
     utilizado por el sistema en el proceso de recuperación y la renovación 
     contraseña. 

Puede especificar un valor personalizado para los campos siguientes, 
de lo contrario los valores de módulo * Datos 
organización * se utilizará (este módulo sólo está disponible para el administrador del sistema).

* Empresa 
* Oficina 
* Dirección 
* Ciudad 
* Teléfono 

==================
Cambiar contraseña 
================== 

Cambiar contraseña actual con una nueva contraseña. 

Contraseña actual 
     Introduzca la contraseña actual. 

Nueva contraseña 
     Introduzca la nueva contraseña. 

Repetir nueva contraseña 
     Repetir nueva contraseña: debe coincidir con el archivo *Nueva contraseña*

====================== 
Organización detalles 
====================== 

Estos campos contienen valores por defecto para la empresa. 
Los datos proporcionados se utilizarán como predeterminados al crear 
nuevos usuarios. 

Para cada usuario se pueden especificar diferentes valores en el panel 
Usuarios, ficha Detalles. 
La modificación de estos datos reemplaza los valores predeterminados para el 
los usuarios que no disponen de campos personalizados. 

**ADVERTENCIA**:Cualquier cambio en los datos introducidos vuelve a crear los certificados SSL. 


Empresa 
     Introduzca el nombre de la empresa. 
Ciudad 
     Entrar en la ciudad de la empresa. 
Oficina 
     Introduzca el departamento u oficina, cuyos miembros tendrán acceso.
Teléfono 
     Introduzca el número de teléfono de la empresa. 
Dirección 
     Introduzca la dirección de la empresa. 

==== 
Red 
====

Cambiar la configuración de las interfaces de red. Las interfaces de red del sistema se detectan automáticamente. 

=======
Estado 
======= 

Enlace 
     Indica si el adaptador está conectado a cualquier dispositivo de red (por ejemplo, Ethernet 
     cable conectado al interruptor). 

Modelo 
     Modelo de la tarjeta de red utilizada.

Velocidad 
     Indica la velocidad que la tarjeta de red ha negociado (expresada en Mb/s). 

Conductor 
     El controlador utiliza el sistema para controlar la tarjeta. 

Autobús 
     Tarjeta de red física del bus (por ejemplo;PCI,USB).

====== 
Editar 
====== 

Cambiar la configuración de la interfaz de red 

Tarjeta 
     Nombre de la interfaz de red. Este campo no puede estar 
     cambiado. 

MAC Address 
     Dirección física de la tarjeta de red. Este campo no puede estar 
     cambiado. 

Papel 
     El papel indica el destino de uso de la interfaz, por ejemplo: 

     * Verde -> Negocios LAN 
     * Red -> Internet, IP pública 

Modo 
     Indica qué método se utilizará para asignar la dirección IP a 
     el adaptador de red. Los valores posibles son *Estático* y *DHCP*.

Estático 
     La configuración se reserva estáticamente. 

     * Dirección IP: dirección IP de la tarjeta de red 
     * Máscara de red: máscara de red de la tarjeta de red 
     * Puerta de enlace: Servidor de puerta de enlace predeterminada 

DHCP 
     La configuración se asigna dinámicamente (sólo disponible para 
     Interfaces de RED) 

============ 
Ver registro 
============ 

Buscar y mostrar el contenido de los archivos de registro.

================================== 
Buscar en los archivos de registro 
==================================

Le permite navegar por todos los archivos de registro del servidor y hacer 
búsquedas exhaustivas sobre ellos. 

Encontrar 
     Le permite buscar palabras y frases dentro de todos los 
     los registros del servidor. 

Usted puede ir directamente a cada registro a través de los enlaces 
que aparece en la página.

===================== 
Mostrar solo registro 
=====================

Te permite navegar por el contenido del registro seleccionado y 
seguir el flujo de texto en tiempo real. 

Cerca 
     Cierre la ventana del registro seleccionado y volver al 
     la página principal. 

Vacío 
     Se le permite vaciar el contenido de la ventana de registro. los datos 
     se eliminan solamente desde la ventana de la pantalla, no 
     se hacen cambios en el contenido del registro. 

Seguir 
     Actualización en tiempo real de la ventana de la pantalla con el nuevo 
     la información que se escribe en el registro. 

Parar
     Detiene la actualización de la visualización de registros en tiempo real.
   
======== 
Cerrar 
======== 

Le permite apagar o reiniciar el servidor. 
Es obligatorio para apagar el sistema antes de apagar el servidor. 
La ejecución de estas funciones lleva unos pocos minutos. 


ADVERTENCIA! Al hacer clic en APAGADO la operación del sistema se iniciará 
inmediatamente. 


Reanudar 
     Reinicie el servidor termine todos los procesos en ejecución. 

Power-off 
     Apague el servidor después de completar todos los procesos en ejecución.
