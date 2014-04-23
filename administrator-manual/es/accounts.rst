========
Usuarios
========

Se requiere un usuario del sistema para acceder a muchos servicios prestados por
|Product| (correo electrónico, carpetas compartidas , etc).

Cada usuario se caracteriza por un par de credenciales (usuario y
contraseña). Una cuenta de usuario recién creada permanece bloqueado hasta que tenga
establecer una contraseña. Un usuario bloqueado no puede utilizar los servicios de
servidores que requieren autenticación .

Crear/Modificar
===============

Le permite crear o modificar los datos de usuario *El nombre de usuario* no puede
ser cambiado después de la creación.

Usuario
-------

Información básica sobre el usuario. Estos campos son requeridos.

Nombre de usuario
     El *Nombre de usuario* se utiliza para acceder a los servicios. Puede
     contener letras solamente minúsculas, números,guiones ,puntos y
     guión bajo ( _ ) y debe comenzar con una letra minúscula . Por
     ejemplo, " luisa ", " jsmith " y " liu- jo" es un nombre de usuario válido y
     " 4friends ", " Franco Blacks " y " aldo / error " no lo son.

Nombre
     Es el nombre real del usuario. Por ejemplo, " John "

Apellido
     El apellido del usuario

Grupos
     Uso de la barra de búsqueda, puede seleccionar los grupos a los
     la que se agregará el usuario. El usuario puede pertenecer a varios grupos.

Cambiar contraseña
-------------------

Permite establecer una contraseña inicial, o cambiar la contraseña del usuario .

 
Bloquear/Desbloquear 
-------------------- 

Le permite bloquear o desbloquear un usuario. Los datos del usuario 
no se eliminarán. 

Borrar 
------- 

Eliminar el usuario. Se borrarán todos los datos del usuario. 

Detalles 
-------- 

En este apartado se recoge información sobre la organización a la que 
pertenece el usuario y es opcional. Los valores por defecto pueden especificar el elemento de menú *Organización de datos*. 

Durante los siguientes campos, puede especificar un valor personalizado, 
de lo contrario, es el ajuste realizado por el módulo de datos "organización", disponible sólo para el administrador del sistema. 

* Empresa 
* Oficina 
* Dirección 
* Ciudad 
* Teléfono 


Servicio 
--------- 

Esta sección contiene la lista de servicios a los que el usuario es 
permitido. 


Correo 
^^^^^^ 

Bandeja de entrada 
     Habilitar el buzón para el usuario.

Reenvío de mensajes
     Reenviar mensajes de correo electrónico recibidos a una dirección alternativa.

Guarde una copia en el servidor
     Email reenviado todavía se guarda en la bandeja de entrada del usuario.

Cuota de correo electrónico personalizado
     Permite especificar un valor de dimensión distinta de la predeterminada.

Personalizar el tiempo de retención de los mensajes de spam.
     Los correos electrónicos de spam se eliminan a intervalos regulares. Marcando la
     caja que puede establecer el número de días que los mensajes del usuario
     clasificado como spam, se mantendrán
     en el sistema antes de ser eliminados .

Direcciones de correo electrónico
     Lista de las direcciones de correo electrónico asociadas con el usuario.

Las carpetas compartidas (Samba)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Samba es la aplicación del protocolo CIFS, que permite el uso de
Carpetas compartidas de Windows.

Las carpetas compartidas (Samba)
     Conceder permisos de usuario para tener acceso a las carpetas compartidas a través de Samba.

Shell Remoto (SSH)
==================

Shell Remoto (SSH)
     Permite al usuario acceder a una shell segura en el servidor.

======
Grupos
======

Crear, modificar o eliminar grupos de usuarios
utilizado para asignar permisos de usuario y de acceso a los servicios
o listas de distribución de correo electrónico.

Crear/Modificar
===============

Grupo
-----

Crear un nuevo grupo, agregar miembros al grupo.


Nombre del grupo
     Solo puede contener letras minúsculas, números,
     guiones y guiones bajos y debe comenzar con
     una letra minúscula. Por ejemplo, " ventas ", " beta3 " y " rev_net "
     son nombres válidos, mientras que " 3d", " Oficina de Ventas " y " Q & A" no son .
Descripción
     Introduzca una breve descripción del grupo.
Afiliación
     Le permite buscar usuarios en el servidor. Usuarios
     puede ser añadido al grupo con el botón *Añadir*. Para eliminar el
     usuarios listados usar el botón *X*.

Servicios
---------

Habilitar servicios disponibles para el nuevo grupo.

Email
     Habilitar el buzón para el grupo.
Enviar una copia del mensaje a los miembros del grupo
     Habilitar el comportamiento estándar de la lista de distribución: cada
     e- mail enviado al grupo será copiado en el buzón de cada usuario.
Entregar el mensaje en una carpeta compartida
     Cualquier correo electrónico enviado al grupo será entregado a una carpeta IMAP
     compartida visibles sólo para los miembros del grupo.
Crear direcciones de correo electrónico predefinidas
     Creación automática de direcciones de correo electrónico para el grupo
     para todos los dominios configurados en el servidor, como
     *GROUP_NAME @ dominio*. Estas direcciones de correo electrónico se pueden cambiar en
     *Sección de Gestión - > Direcciones de correo electrónico*.

Borrar
======

Esta acción elimina los grupos definidos y su
listas de distribución. Los buzones compartidos asociados


.. _admin-user:

Usuario Administrador
=====================

El :guilabel:`Usuario` modulo  crea el usuario :dfn:`administrador` que permite acceder a la interfaz web con la misma contraseña para la :dfn:`root` usuario.
El :index:`administrador` usuario no tiene acceso al sistema desde la línea de comandos. A pesar de ser dos usuarios distintos, la contraseña de ambos coincide y se puede cambiar desde la interfaz web.

En algunas ocasiones, puede ser útil para diferenciar el admin y la contraseña de root, por ejemplo, para permitir que un usuario sin experiencia
utilizar la interfaz web para realizar tareas comunes y que impide el acceso a la línea de comandos.

Evite :index:`root` y  sincronización de contraseña de administrador por ejecutar el siguiente comando ::

 config September AdminIsNotRoot enabled

A continuación, cambiar la contraseña de administrador del panel :guilabel:`Usuarios`. Sin sincronización de contraseñas, administrador tendrá la nueva contraseña y, a raíz mantendrá a mantener el antiguo.

Si desea cambiar la contraseña de root , debe hacerse desde la línea de comandos usando :command:`passwd`.


Gestión de contraseñas
=======================

El sistema ofrece la posibilidad de establecer limitaciones a la contraseña :dfn:`complejidad` :dfn:`caducidad` .

Complejidad
-----------

El índice de complejidad de contraseña es un conjunto de condiciones mínimas que debe coincidir con la contraseña que ser aceptado por el sistema:
Usted puede elegir entre dos políticas de gestión diferentes sobre la complejidad de contraseña:

* :dfn:`no`: no hay un control específico sobre la contraseña introducida, pero la longitud mínima es de 7 caracteres
* :dfn:`fuerte` 

El :index:`fuerte` política requiere que la contraseña debe cumplir con las siguientes reglas:

* Longitud mínima de 7 caracteres
* Contener al menos 1 número
* Contener al menos 1 carácter en mayúscula
* Contener al menos 1 carácter en minúscula
* Contener al menos 1 carácter especial
* Por lo menos 5 caracteres diferentes
* Debe ser no está presente en los diccionarios de palabras comunes
* Debe ser diferente del nombre de usuario
* No se puede tener repeticiones de patrones formados por 3 o más caracteres ( por ejemplo, AS1 contraseña. $ AS1 . $ Es inválido )

La política predeterminada es :dfn:`fuerte` .

Para cambiar el ajuste a ninguno ::

   config setprop PasswordStrength none Usuarios

Para cambiar el ajuste a la fuerte ::

   config setprop PasswordStrength Usuarios fuerte

Revise la política actualmente en uso en el servidor ::

   Usuarios config GetProp PasswordStrength

Vencimiento
-----------

El : index  caducidad de la contraseña está activada por defecto y 6 meses desde el momento en que se establece la contraseña.
El sistema le enviará un correo electrónico para informar a los usuarios cuando su contraseña está a punto de expirar.

.. Note :: El sistema se referirá a la fecha del último cambio de contraseña, cualquiera que sea anterior más de 6 meses, el servidor enviará un correo electrónico para indicar que la contraseña ha caducado. En este caso es necesario cambiar la contraseña de usuario.Por ejemplo, si el último cambio de contraseña se hizo en enero, y la activación de la fecha límite en octubre, el sistema asumirá la contraseña cambió en enero ha caducado, y notificar al usuario.

Si desea omitir la caducidad de las contraseñas a nivel mundial (también permitir el acceso a usuarios con contraseñas caducadas) ::

        config setprop PasswordStrength PassExpires no
        caso de la señal -password- - actualización de la política

Para desactivar la caducidad de la contraseña para un usuario único (reemplace username con el usuario) ::

   db cuentas setprop <username> PassExpires no
   caso de la señal -password- - actualización de la política


A continuación se presentan los comandos para ver las directivas habilitadas.

El número máximo de días en que se puede mantener la misma contraseña (por defecto: 180) ::

   config GetProp PasswordStrength MaxPassAge


Número mínimo de días en los que se ven obligados a mantener la misma contraseña (por defecto 0) ::

   config GetProp PasswordStrength MinPassAge


Número de días en que el aviso se envió por correo electrónico ( predeterminado : 7) ::

   config GetProp PasswordStrength PassWarning

Para cambiar los parámetros reemplazan el :command:`getprop` comando con :command:`setprop`,
Para cambiar los parámetros reemplazan el :command:`GetProp` comando con :command:`setprop` ,
a continuación, agregue el valor deseado en el extremo de la línea. Finalmente aplicar nuevas configuraciones ::

   caso de la señal -password- - actualización de la política



Por ejemplo, para cambiar al 5 " Número de días en que el aviso es enviado por correo electrónico " ::

   config setprop PasswordStrength PassWarning 5
   caso de la señal -password- - actualización de la política



Efectos de la contraseña caducada
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ 

Después de caducidad de la contraseña, el usuario será capaz de leer y enviar correos electrónicos, pero ya no puede acceder a las carpetas e impresoras (Samba) compartidos o 
u otro equipo si la máquina es parte del dominio. 


Contraseña de dominio 
--------------------- 

Si el sistema está configurado como controlador de dominio, los usuarios pueden cambiar su contraseña utilizando las herramientas de Windows. 

En este último caso no se puede establecer contraseñas más cortas que 6 *caracteres*, independientemente de las directivas de servidor. 
Windows realiza comprobaciones preliminares y envía la contraseña al servidor en el que se evalúan 
con las políticas habilitadas.
