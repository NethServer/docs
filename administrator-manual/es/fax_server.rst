=============== 
Servidor de fax 
=============== 

El servidor de fax le permite enviar y recibir faxes a través de un módem 
conectado directamente a un puerto del servidor (COM o USB) oa través de un 
modem IAX virtual. 

El módem debe ser compatible con el envío y la recepción de faxes de preferencia en la clase 1 o 1,0 (2, 2.0 y 2.1 clases también son compatibles). 

General 
======== 

Código del país
    El prefijo internacional que se antepone a su número de fax.
Prefijo
    Código de área.
Núbero de fax
    El número de fax del remitente.
Remitente (TSI)
    La ETI se imprimirá en el encabezado del fax del destinatario, por lo general en la fila superior. Es posible introducir el número de fax o el nombre de una longitud total de hasta 20 caracteres (se recomienda el nombre de la empresa). Sólo se permiten caracteres alfanuméricos.


Módem 
===== 

Modem
     El puerto físico (COM o USB) a la que el módem está conectado o un módem fax virtual

     * Estándar de dispositivo: le permite seleccionar el dispositivo de una lista de los puertos comunes.
     * Dispositivo personalizado: permite especificar un dispositivo personalizado para ser utilizado como un módem fax. Debe ser el nombre de un dispositivo en el sistema.

Modo
    Especifica el modo de funcionamiento del dispositivo seleccionado. Los modos disponibles son:

    * Enviar y recibir: el módem se utiliza para enviar y recibir faxes
    * Recibir sólo: el módem sólo se utilizará para la recepción de faxes
    * Enviar sólo: el módem sólo se utilizará para el envío de faxes

Prefijo PBX
     Si el módem de fax está conectado a una centralita, puede que tenga que introducir un código de acceso a "obtener una línea externa". Si el módem está conectado directamente a una línea o el PBX requiere ningún código, deje el campo vacío. Si estás detrás de un PBX, introduzca el prefijo que se debe marcar.

Esperar tono de marcación
     Algunos módems no son capaces de reconocer el tono de marcación (sobre todo si está conectado a un PBX) y no marcar el número señalando la ausencia de tono (de error "No hay tono de marcado").

     Para configurar el módem para que ignore la ausencia de la línea y marcar inmediatamente el número seleccionar Desactivado. La configuración recomendada es "Habilitado", es posible que desee desactivar * Espere el tono de marcación * sólo en caso de problemas.

Notificaciones por correo electrónico 
===================================== 

Formato de los faxes recibidos
    De forma predeterminada, el servidor de fax envía los faxes recibidos como mensajes de correo electrónico con un archivo adjunto. Especifique la dirección de correo electrónico donde se entregarán los faxes, y uno o más formatos el archivo adjunto. Para no recibir el fax como archivo adjunto, pero sólo una notificación de recepción, anule la selección de todos los formatos.

Faxes recibidos hacia Adelante

    * Grupo "faxmaster"
        Por defecto, los fax recibidos se envían a *faxmaster*: si un usuario necesita para recibir los fax entrantes, debe añadirse a este grupo.
    * Correo electrónico externo
        Introduzca una dirección de correo electrónico externa en caso de que desea enviar los faxes recibidos a una dirección de correo electrónico no en este servidor.

Formato de fax enviados
    Si lo solicita el cliente, el servidor envía una notificación por correo electrónico con un archivo adjunto. Seleccione el formato en el que prefiere recibir el fax. Anule la selección de todas las opciones si no desea recibir el fax adjunto. 
Añadir notificación de entrega
    Si se selecciona, se agrega un informe de notificación de entrega en el correo electrónico enviado por fax.


Funciones adicionales 
===================== 

Ver los fax enviados por el cliente
    Los clientes de fax también le permiten ver todos los faxes entrantes. Si, por razones de confidencialidad, se desea filtrar faxes recibidos, desactive esta opción.

Imprimir automáticamente los fax recibidos
    Imprimir automáticamente todos los faxes recibidos en una impresora compatible con PCL5 configurado en |product|. La impresora debe estar seleccionado con la caída adecuada en el menú desplegable.

SambaFax
    Al seleccionar esta opción, el servidor de fax puede poner a disposición del red de área local de una impresora virtual llamada "sambafax" que se configurarse en el cliente, seleccionando el controlador Apple LaserWriter 16/600 PS. Documentos impresos en la impresora de red sambafax debe contener la frase exacta "Número de fax:" seguido del número de fax del destinatario.

Enviar informe diario
    Enviar un informe diario al administrador 

========= 
IAX Modem 
========= 

Esta página le permite configurar los módems IAX. 

Un módem IAX es un módem de software que utiliza un canal IAX (normalmente 
proporcionada por una centralita Asterisk) en lugar de una línea telefónica tradicional. 


Crear/Modificar 
================== 

Nombre
    Nombre el nuevo módem IAX que está creando.

Servidor IP
    Dirección IP del servidor en el que los registros de módem IAX (por ejemplo, la dirección IP del servidor Asterisk).

Extensión
    IAX extensión en el que desea recibir los faxes.

Contraseña
    Define IAX contraseña de la extensión previamente.

Identificador de llamadas
<<<<<<< HEAD
    Identificador de llamadas (número) que se muestra en los faxes salientes.
=======
    Identificador de llamadas (número) que se muestra en los fax salientes.
>>>>>>> 99905c435a6a42f3e2030515090433266821b19a

Nombre del llamante
    Nombre del llamante se muestra en los fax salientes.
