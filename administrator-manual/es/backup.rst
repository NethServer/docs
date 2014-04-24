======== 
Reserva 
======== 

La copia de seguridad contiene todos los datos, tales como los directorios principales de los usuarios, 
carpetas compartidas, mensajes de correo electrónico, sino también todas las configuraciones del sistema. Funciona todos los días y puede ser total o 
gradual, dependiendo del día de la semana y la configuración. Los 
medios disponibles para la copia de seguridad son: disco USB, recurso compartido de Windows 
y NFS share. Al final del procedimiento de copia de seguridad, se enviará una notificación por correo electrónico 
al administrador o a una dirección personalizada. 

 
General
========

Habilitar copia de seguridad automática
    Esta opción activa o desactiva el procedimiento de copia de seguridad. El valor predeterminado es *habilitado*.

Horario de copia de seguridad
    El momento en el que la copia de seguridad se iniciara. Cambie el valor directamente en el campo.

Completo
    Al seleccionar esta opción se ejecutara una copia de seguridad completa cada día de la semana.

Incremental
    Al seleccionar esta opción se ejecutara una copia de seguridad completa en el día seleccionado a través del campo específico, mientras que el resto de la semana se ejecutara una copia de seguridad incremental.

Política de retención
    Introduzca el número de días que se guardara la copia de seguridad.
 

Destino 
======== 

Disco USB 
    Seleccione el destino de copia de seguridad en una unidad USB. El disco USB debe ser formateado con un sistema de archivos compatible (ext2/3/4 o FAT, NTFS no se admite) y una etiqueta configurada.

    * Sistema de Archivos de etiquetas: Enumera los disco USB conectados

Compartido de Windows (CIFS)
    Seleccione el destino de copia de seguridad, una parte de Windows (CIFS). Es necesaria la autenticación.

    * Servidor: La dirección IP o el FQDN del servidor de Windows de destino.
    * Compartir: El nombre del recurso compartido en el sistema Windows de destino.
    * Usuario: El número de usuario que se utilizara para la autenticación
    * Contraseña: Contraseña que se utilizará para la autenticación.

Compartir NFS 
    Seleccione el destino de copia de seguridad en un recurso compartido NFS

Host
   La dirección IP o el FQDN del servidor NFS

   * Compartir: Nombrar el objetivo compartido de NFS

 

Notificaciones 
=============== 

En caso de error
    Enviar notificación, solo en el caso de que falle el respaldo.

Siempre
    Siempre envía notificaciones, si tiene éxito o en caso de fallo.

Nunca
    Usted no recibirá ninguna notificación.

Enviar notificación
    Recibirá la notificación por correo electrónico

    * Administrador de Sistemas: notificación de la copia de seguridad se enviara al administrador del sistema (usuario administrador)
    * Dirección personalizada: Se enviara la notificación de la copia de seguridad.
