========================
Las carpetas compartidas
========================

Una carpeta compartida es un recurso en el sistema que se puede acceder de acuerdo a los servicios instalados en el sistema y los permisos establecidos por este módulo. 


Crear nueva / editar
--------------------

Dependiendo de los servicios instalados en el sistema, verá 
varias pestañas. 

General
^^^^^^^

Nombre 
     El nombre de la carpeta compartida. Sólo puede contener letras minúsculas, 
     números, puntos, guiones y guiones bajos. La longitud máxima del nombre es de 12 caracteres. 

Descripción 
     Campo opcional para una breve descripción de la carpeta compartida. 

Propietario del grupo 
     El grupo propietario de la carpeta compartida, sólo los miembros del 
     grupo puede acceder a la carpeta. 

Permitir escrito al propietario del grupo 
     Permitir el acceso de escritura a los miembros del grupo propietario. 

Permitir el acceso de lectura a todos 
     Acceso de lectura a cualquiera que se conecte al sistema, así como 
     redes públicas.

ACL
^^^

La Lista de control de acceso permite acceder  a los permisos especificos de la 
carpeta compartida para cada uno de los usuarios o grupos, además de aquellas del propietario del grupo. 

Leer 
     Permitir o denegar el acceso de lectura al usuario o grupo seleccionado. 

Escribir 
     Permitir o denegar el acceso de escritura para el usuario o grupo 
     seleccionado.


Borrar
------

Elimina la carpeta y todo su contenido. *La acción no es 
reversible!* La única manera de recuperar el contenido de una carpeta compartida 
que a medida que se han eliminado, para restaurar es una copia de seguridad.

Restablecer los permisos
------------------------

Establezca el propietario del grupo y las ACL configuradas usando este módulo 
en todos los archivos de la carpeta. La operación se lleva a cabo de forma recursiva en todos los archivos y subcarpetas de la carpeta compartida.


Acceso a la web 
^^^^^^^^^^^^^^^
Permite el acceso a la carpeta compartida desde la web. 

Host virtual 
     Te permite elegir que nombre de host se encuentra disponible en la carpeta compartida. La lista viene de la tarjeta de "Alias servidor" en el 
     módulo "DNS y DHCP." 

Dirección Web (URL) 
     Define la dirección web en la que el recurso está disponible. 

Permitir el acceso sólo desde redes locales 
     Si sólo se activa, restringe el acceso al recurso sólo para
     redes locales. 

Requerir una contraseña 
     El acceso a los recursos de la web no requiere 
     la autenticación. Active esta opción para solicitar una contraseña: especifique en el campo de abajo.


Samba
^^^^^ 
Samba ofrece compartir archivos e impresoras para clientes SMB / CIFS (compartir archivos e impresoras en Windows). 

Habilitar Samba 
      Permite el acceso como una "carpeta compartida" de Windows. 

Papelera de reciclaje de red 
      Recopila los archivos eliminados por esta carpeta compartida, de modo similar a la papelera de reciclaje de Windows. 

Mantener los archivos con el mismo nombre 
      Si dos archivos con el mismo nombre, que siguen siendo distintos en la basura. por 
      desactivar esta opción, el último sobrescribe el año anterior. 

Acceso de invitados 
      A *usuario invitado* es un usuario cuya identificación ha fallado porque 
      no proporcionó credenciales o ha facilitado información incorrecta. Para 
      usuarios o dispositivos que actúan de este modo, se pueden conceder la 
      siguientes permisos: 

      * Ninguno 
      * Sólo lectura 
      * Leer y escribir

