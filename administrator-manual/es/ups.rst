===
UPS
===

La gestión de un sistema de alimentación ininterrumpida (UPS - Sistema de Alimentación Ininterrumpida) conectada a |product| se asigna a NUT (Herramientas de UPS de red), que llevarán a cabo un cierre en caso de falta de energía. NUT soporta diferentes modelos de UPS, conectados por un cable serie o USB. 

En este panel se realiza la configuración del NUT,para 
ver datos del SAI, utilice el Panel de control. 

Habilitar NUT UPS 
     Activar o desactivar el servicio NUT.

Modo
========

Maestro
     Este modo debe seleccionarse si el SAI está conectado 
     a |product| directamente a través de serie o cable USB. 

Buscar controladores para el modelo 
     Le permite buscar un controlador compatible con tu modelo de UPS. Después de seleccionar el modelo de la lista,     
 el *Driver* el campo se va a rellenar con el nombre del controlador adecuado. 

Driver 
     El driver que se utilizará para el modelo de UPS conectado. 
    
Conexión USB 
     Seleccione esta opción si el SAI está conectado a través de USB. 

Conexión en serie 
     Seleccione esta opción si el SAI está conectado a través del cable serie |product|.

Esclavo
      Este modo se debe utilizar si el SAI no está conectado directamente a |product|, sino a otro servidor configurado con NUT en modo Master para que |product| sea conectado.

Dirección del servidor maestro 
     Dirección IP o nombre de host del servidor maestro. El cliente utilizará el usuario *UPS* para conectar con el servidor maestro. 
     Asegúrese de que el usuario se configura en el servidor maestro.

Contraseña 
     La contraseña que especifique aquí es la configurada en el servidor maestro para las conexiones de esclavos.

