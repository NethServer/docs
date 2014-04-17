======== 
Reserva 
======== 

La copia de seguridad contiene todos los datos, tales como los directorios principales de los usuarios, 
carpetas compartidas, mensajes de correo electrónico, sino también todas las configuraciones del sistema. Funciona todos los días y puede ser total o 
gradual, dependiendo del día de la semana y la configuración. la 
medios disponibles para la copia de seguridad son: disco USB, recurso compartido de Windows 
y NFS share. Al final del procedimiento de copia de seguridad, se enviará una notificación por correo electrónico 
al administrador o a una dirección personalizada. 

 
General
========

Habilitar copia de seguridad automatica
    Esta opcion activa o desactiva el procedimiento de copia de seguridad. El valor predeterminado es *habilitado*.

Horario de copia de seguridad
    El momento en el que la copia de seguridad se iniciara. Cambie el valor directamente en el campo.

Completo
    Al seleccionar esta opcion se ejecutara una copia de seguridad completa cada dia de la semana.

Incremental
    Al seleccionar esta opcion se ejecutara una copia de seguridad completa en el dia seleccionado a traves del campo especifico, mientras que el resto de la semana se ejecutara una copia de seguridad incremental.

Politica de retencion
    Introduzca el numero de dias que se guardara la copia de seguridad.
 

Destino 
======== 

Disco USB 
    Seleccione el destino de copia de seguridad en una unidad USB. El disco USB debe se formateado con un sistema de archivos compatible (ext2/3/4 o FAT, NTFS no se admite) y una etiqueta configurada.

    * Sistema de Archivos de etiquetas: Enumera los disco USB conectados

Compartido de Windows (CIFS)
    Seleccione el destino de copia de seguridad, una parte de Windows (CIFS). Es necesaria la autenticación.

    * Servidor: La direccion IP o el FQDN del servidor de Windows de destino.
    * Compartir: El nombre del recurso compartido en el sistema Windows de destino.
    * Usuario:El numero de usuario que se utilizara para la autenticacion
    * Contraseña: contraseña que se utilizará para la autenticación.

Compartir NFS 
    Seleccione el destino de copia de seguridad en un recurso compartido NFS

Host
   La direccion IP o el FQDN del servidor NFS

   * Compartir: nombrar el objetivo compartido de NFS

 

Notificaciones 
=============== 

En caso de error
    Enviar notificacion, solo en el caso de que falle el respaldo.

Siempre
    Siempre envia notificaciones, si tiene exito o en caso de fallo.

Nunca
    Usted no recibira ninguna notificacion.

Enviar notificacion
    Recibira la notificacion por correo electronico

    * Administrador de Sistemas: notificacion de la copia de seguridad se enviara al administrador del sistema (usuario administrador)
    * Direccion personalizada: Se enviara la notificacion de la copia de seguridad.
