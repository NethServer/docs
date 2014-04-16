=============
Instalacion
=============

Requerimientos minimos
======================

Los requerimientos minimos son:

* 64 bit CPU (x86_64)
* 1 GB ode RAM
* 8 GB de espacio del disco


.. hint:: Recomendamos el uso de al menos 2 discos para configurar un RAID 1. 
          El programa RAID llevará a asegurar la integridad de los datos en caso           de un fallo de disco.

Compatibilidad hardware
----------------------

|product| es compatible con cualquier hardware certificado por 
Red Hat® Enterprise Linux® (RHEL®), escuchado en `hardware.redhat.com <http://hardware.redhat.com/>`_


Tipos de instalacion
==================

|product| es compatible con dos modos de instalación. En resumen:

**Instalacion desde ISO**

  * Descargue la imagen ISO, 
  * Preparar un  CD / DVD o una memoria USB de arranque.
  * Siga el asistente

**Instalacion desde YUM**

  * Instale CentOS Minimal
  * Configurar la red
  * Instalar desde la red

Instalacion desde ISO
====================

Descargar |product|el archivo  ISO desde el sitio oficial
|download_site|. 

El archivo ISO descargado se puede utilizar para crear una 
*Dispositivo de arranque*, como un CD, un DVD o una memoria USB. 
La creación de un disco de inicio es diferente de escribir
archivos en un CD / DVD, y se requiere el uso de una función específica (por ejemplo, *escritura* o *Grabar imagen ISO*). 
Las instrucciones sobre cómo crear un CD / DVD de la ISO es fácilmente 
disponible en Internet o en la documentación de su sistema operativo. 

Un procedimiento similar se aplica para la memoria USB de arranque. 
Hay programas específicos [#]_ que convertirán lo descargado ISO en memorias USB de arranque. 

En ambos casos, ahora se puede iniciar la máquina utilizando los medios de comunicación recientemente respaldado. 
Si el equipo no arranca desde el CD / DVD (o USB), consulte la 
documentación de la BIOS de la placa. Un problema típico es 
la configuración de arranque de prioridad del dispositivo. 
El primer dispositivo de arranque debe ser el lector de CD / DVD (o memoria USB).


.. [#] Por ejemplo, http://unetbootin.sourceforge.net/ 


En el arranque de un menú mostrará diferentes tipos de instalación: 

.. warning :: La instalación borrará todos los datos existentes en los discos duros!


|product| instalacion interactiva
    Le permite seleccionar el idioma, configurar el soporte RAID, 
    red y sistema de ficheros cifrado. Se describe en profundidad en el siguiente párrafo. 

Otros / desatendida |product| instalar
    Este modo de instalación no se requiere ningún tipo de intervención humana: un conjunto de parámetros por defecto serán aplicados al sistema.

Las instalaciones estándar de CentOS
    Utilice el procedimiento estándar de instalación de CentOS.

Instrumentos
    Inicie el sistema en modo de *rescate* (de recuperación), ejecuta una prueba de memoria o iniciar la herramienta de detección de hardware.

Arrancar desde la unidad local
    Los intentos para arrancar un sistema que ya está instalado en el disco duro. 
 
Al final del proceso de instalación, se le pedirá que 
reinicie la máquina. Asegúrese de retirar el CD o 
Soporte USB antes de reiniciar. 

Modo desantendido
-----------------
Después de la instalación, el sistema se configura de la siguiente manera: 

* Credenciales: root / Nethesis 1234 
* Red: DHCP habilitado en todas las interfaces 
* Teclado: us 
* Zona horaria: Greenwich 
* Idioma: en_US.UTF-8 
* Discos: si hay dos o más discos, RAID 1 se crearán en los dos primeros discos


Instalar opciones
^^^^^^^^^^^^^^^^^
Puede agregar parámetros adicionales para instalación desatendida pulsando TAB y editando en la línea de comandos del gestor de arranque. 

Para desactivar la raid, sólo tiene que añadir esta opción a la línea de comandos: :: 

    raid=none

Si usted necesita para seleccionar la instalación de discos duros, utilice: ::

    disks=sdx,sdy

Otras opciones disponibles: 

* Lang: idioma del sistema, por omisión es en_US 
* Teclado: distribución del teclado, por defecto es us 
* Zona horaria: por defecto es UTC Greenwich 
* Contraseña: habilitar el cifrado del sistema de archivos con la contraseña dada


Modo interactivo
----------------

El modo interactivo le permite hacer algunas opciones simples de la configuración del sistema:

1. Idioma 
2. Disposición del teclado 
3. Zona horaria 
4. Software RAID 
5. Contraseña del administrador del sistema 
6. Sistema de archivos cifrados 
7. Interfaces de red 
8. Configuración de la red

Idioma
^^^^^^
Seleccione el idioma en el que desea utilizar el modo interactivo. 
El idioma seleccionado será el idioma predeterminado del sistema instalado. 
El sistema también le sugerirá valores por defecto para el teclado y la zona horaria.


Distribucion del teclado
^^^^^^^^^^^^^^^^^^^^^^^^

Un teclado puede tener un diseño diferente en función del idioma para el que fue hecho. 
Deje el valor sugerido o escriba un valor personalizado.


Zona horaria
^^^^^^^^^^^^
La elección de la zona horaria permite configurar la fecha y la hora del sistema. Deje el valor sugerido o escriba un valor personalizado. 


Software RAID
^^^^^^^^^^^^^
RAID (matriz redundante de discos independientes) le permite combinar todos los discos con el fin de lograr la tolerancia a fallos y un aumento en el rendimiento. 

Esta pantalla aparece cuando se detectan dos o más discos en el arranque.


Niveles disponibles:

* RAID 1: crea una copia exacta (espejo) de todos los datos en dos o más discos. 
   Número mínimo de discos: 2 

* RAID 5: utiliza una subdivisión de los datos a nivel de bloque, distribuyendo los datos de paridad de manera uniforme en todos los discos. 
   Número mínimo de discos: 3 

Disco de repuesto
~~~~~~~~~~~~~~~~~

Puede crear un disco de repuesto si el número de disco es mayor que el mínimo exigido por el nivel de RAID seleccionado, 
Un disco de reserva se añadirá a la RAID en caso de que se produce un fallo. 


Contraseña del administrador del sistema 
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Se recomienda encarecidamente establecer una contraseña de administrador personalizado. 

Una buena contraseña es:

* al menos 8 caracteres de longitud
* Contener letras mayúsculas y minúsculas 
* Contener símbolos y números


Sistema de archivos cifrados
^^^^^^^^^^^^^^^^^^^^^^^^^^^^
Al habilitar esta opción, todos los datos escritos en el disco serán cifrados mediante cifrado simétrico. 
En caso de robo, un atacante no será capaz de leer los datos sin 
la clave de cifrado.

Es posible elegir una contraseña para la encriptación, de lo contrario se utilizará la contraseña de administrador del sistema. 

.. note ::  Usted tendrá que introducir la contraseña en cada inicio del sistema.


Los interfaces de red
^^^^^^^^^^^^^^^^^^^^^
Seleccione la interfaz de red que se utiliza para acceder a la LAN. 
Esta interfaz también se conoce como interfaz *verde*.


Configuracion de la red
^^^^^^^^^^^^^^^^^^^^^
Host y el nombre de dominio (FQDN) 
     Escriba el nombre de host y dominio en el que el servidor va a funcionar (por ejemplo: samp:`server.mycompany.com`).

    *Nota:* El nombre de dominio sólo puede contener letras, números y el guión.

Dirección IP 
     Escriba una dirección IP privada (por RFC 1918) que se asignará al servidor;     si quieres instalarlo en una red existente, usted debe proporcionar una dirección IP no utilizada válida para esa red (en general, se puede utilizar la primera o la última de acogida dentro del alcance de la red, por ejemplo, 192.168.7.1 o 192.168.7.254). 

Máscara de red 
     Escriba la máscara de subred de la red. Puede dejar el valor por defecto. 

Puerta de acceso 
     Escriba la dirección IP de la puerta de enlace en el que está 
     instalar el servidor. 

DNS 
     Escriba un DNS válido. Ejemplo: 8.8.8.8

Fin del proceso de instalacion
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Después de parámetros de entrada, el procedimiento iniciará la instalación.


Instalar desde CentOS
=====================

Es posible instalar |product| en  CentOS 
mediante el comando *yum* para descargar los paquetes de software

Por ejemplo, si desea instalar |product| |version|, acaba de empezar 
con CentOS |version| en su sistema (proveedores de muchos de VPS 
ofrecen CentOS en máquinas virtuales pre-instalado), y luego ejecutar los comandos a continuación 
transformar en CentOS |product|. 
 

Habilitar |product| repositorios con el comando

::

  yum localinstall -y http://pulp.nethserver.org/nethserver/nethserver-release.rpm

Para instalar el sistema base, ejecute

::

  nethserver-install

Para instalar módulos adicionales, pase el nombre del módulo como parámetro para el script de instalación. 
Ejemplo para el correo y los módulos de UPS:

::

  nethserver-install nethserver-mail nethserver-nut


Al final del procedimiento, el sistema esta listo para su uso.




