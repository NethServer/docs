=====================================
Migración de NethService/Servidor SME
=====================================

:index:`Migration` es el proceso de convertir un servidor SME (o NethService) máquina en  |product|.

#. En el antiguo anfitrión, crear un archivo de copia de seguridad completa y moverlo a la nueva |Product| host. 
#. En el nuevo servidor, instalar todos los paquetes que cubren las mismas características de la anterior. 
#. Explotar el archivo de copia de seguridad completa en algún directorio (por ejemplo,
   ``/var/lib/migration``)
#. Señale el evento::

    # signal-event migration-import /var/lib/migration

   Este paso requerirá algún tiempo.
#. Búsqua algún ``ERROR`` cadena en ``/var/log/messages``

