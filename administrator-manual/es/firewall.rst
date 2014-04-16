================
Puerto delantero
================

Utilice este panel para cambiar las reglas del cortafuegos
es decir, para abrir un puerto específico (o un rango de puertos) en el servidor
y reenviar el tráfico de un puerto a otro. Las reglas de reenvío de puerto
permiten el acceso a los hosts de la red local desde Internet.

Crear / Modificar
=================

Puerto de origen
    Inserte el puerto abierto en la dirección IP pública.

Puerto de destino
    Intoduzca el puerto en el host interno que será el destino del tráfico.

Host de destino
    Dirección IP de la máquina interna donde será redirigido tráfico.

Permitir sólo
    Permitir el tráfico hacia delante sólo de alguna fuente redes / hosts.

Descripción
    Descripción opcional de la regla de reenvío de puertos.

Activar / Desactivar
====================

Las reglas de reenvío de puerto están habilitadas de forma predeterminada en 
creación. Puede activar temporalmente / desactivarlos 
Con este botón 

Si
    Habilitar la regla.

No
    Deshabilitar la regla.

 

Verificacion del servidor de seguridad
======================================


Realiza un control general sobre las reglas del cortafuegos configuradas. Útil para la detección de inconsistencias.

===========================
Gestion de ancho de banda
===========================

El gestor de ancho de banda le permite cambiar las prioridades en el tráfico al
pasar por el servidor de seguridad (que debe tener al menos dos interfaces de red).

General
========

Activa o desactiva la gestión de ancho de banda. 


Reglas de interfaz
===============

Para cada interfaz en la que desea administrar la prioridad de ancho de banda es 
necesario especificar la cantidad máxima de ancho de banda disponible en 
direcciones salientes y entrantes. Si no hay datos se transmiten a una velocidad configurada. Es imprescindible utilizar los valores reales, 
medido preferiblemente con pruebas de velocidad, en particular para la banda en 
cargar (saliente). La tabla muestra los valores configurados en cada 
interfaz, lo que permite modificar los límites de ancho de banda. 

Crear / Modificar
---------------

Crear una configuración de límites de ancho de banda de la interfaz. 

Interfaz
    Seleccione la interfaz a la que se aplica el límite de ancho de banda.
    En general, el ancho de banda está limitado sólo en las interfaces WAN.

Ancho de banda entrante (kbps)
    Ajuste la cantidad de ancho de banda entrante (descargar).

Ancho de banda de salida (kbps)
    Ajuste la cantidad de ancho de banda de salida (carga).

Descripcion
    Una nota opcional (por ejemplo: ADSL 1280/256).


Reglas de direcciones
==============

La tabla muestra la lista de direcciones de red (IP o MAC) que tienen 
personalizada reglas de prioridad. Por ejemplo, usted puede decidir 
que el tráfico de un equipo específico en la red local 
tener una prioridad alta o baja en comparación con otros. 


Crear / Modificar 
-----------------

Dirección IP o MAC
    Introduzca la dirección IP o la dirección MAC que identifica el ordenador.

Descripción
     Una descripción opcional para identificar claramente el propósito de la regla. Por ejemplo: una alta prioridad para el jefe.
 

Reglas de puerto
================

La tabla muestra la lista de puertos TCP / UDP que tienen reglas
personalizadas prioridad. Por ejemplo, puede especificar que el 
tráfico en un servicio de red en particular (desde o hacia 
un puerto en particular) tiene una prioridad baja o alta 
en comparación con el tráfico normal de la red.


Crear
------

Puerto
    Especifique el puerto utilizado por el servicio de red.

Protocolo
    Introduzca el protocolo IP.

Descripción
    Una descripción opcional que establece claramente la finalidad de la norma. Por ejemplo: Fondo para Servicio FTP.
