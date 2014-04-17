===== 
Email 
===== 

Configure los servicios de correo electrónico 

Dominios 
======= 

La tabla contiene la lista de nombres de dominio de Internet para los que el 
servidor acepta correo electrónico entrante. 

Crear / Modificar 
----------------- 

Agregar un dominio a la lista de los configurados para la recepción de correo electrónico.

Dominio
    El nombre de dominio, por ejemplo *nethesis.it*.

Descripción
    Un campo opcional útil para el administrador del sistema a tomar nota de la información del dominio.

Entrega local
    Seleccione esta opción para configurar el servidor para entregar el correo entrante dirigido al dominio especificado en las carpetas locales.

Reenviar a otro servidor
    Si selecciona esta opción, el correo entrante será se transmitirá al servidor especificado.

Disclaimer (aviso legal)
    Añadir automáticamente un mensaje legal (disclaimer)
     a todos los mensajes salientes (no dirigida al dominio).

Borrar 
------- 

Retire el dominio de los gestionados por el servidor. Cualquier correo electrónico 
destinado para el dominio serán rechazadas.


Filtro 
====== 

Configure las opciones de filtrado de correo electrónico (antivirus, antispam, 
adjuntos prohibidos, etc.) 

Antivirus
    Habilitar la detección de virus de correos electrónicos en tránsito.

Antispam
    Activar el análisis antispam de mensajes de correo electrónico entrantes.

Spam Prefijo
    Este prefijo se añade al objeto fundamental de los correos electrónicos reconocidos como spam.

Bloqueo de archivos adjuntos
    El servidor de correo electrónico bloquee mensajes de correo electrónico que contengan archivos adjuntos de tipos especificado.

Ejecutable
    El servidor de correo electrónico bloqueará programas ejecutables en archivos adjuntos de correo electrónico.

Archivo
    El servidor de correo electrónico bloquee mensajes de correo electrónico con archivos adjuntos que contienen archivos comprimidos (ZIP,rar, etc.)

Lista personalizada
    Definir una lista de extensiones que serán bloqueados,
     tales como doc, pdf, etc (sin arrancar punto, es decir, doc y no. doc).


Buzones 
======== 

En esta ficha, puede configurar algunos parámetros relacionados con la 
carpetas de correo locales. 

IMAP
    Habilitar el acceso a carpetas a través del protocolo IMAP (recomendado).

POP3
    Habilitar el acceso a carpetas a través del protocolo POP3 (no recomendado).

Permitir conexions sin cifrar
    Permite habilitar el acceso a las carpetas que utilizan protocolos no encriptados (no recomendado).

Espacio en disco
    Le permite limitar el uso del disco por correo electrónico.

    * Ilimitado: seleccione no imponer límites
    * Aplicar cuota: límite de espacio máximo de correo para cada usuario con el valor indicado (cuota de correo electrónico).


Mover a la carpeta *junkmail*
    Mensajes de correo electrónico identificado como spam se mueven a cada carpeta de usuario *Junkmail* en lugar de ser entregado a la bandeja de entrada.


Mensajes 
======== 

Configurar la gestión de mensajes de correo electrónico. 

Accepte el tamaño del mensaje a
    Utilice el cursor para seleccionar el tamaño máximo de un  mensaje de correo electrónico única. El servidor rechazará electrónico más grande que el valor establecer y devolverá un error explicativo.


Vuelva a intentar el envio
    Utilice el cursor para seleccionar el tiempo máximo durante el cual el servidor tratar de enviar un mensaje. Cuando llega el tiempo máximo y el correo electrónico no ha sido entregado, el remitente recibirá un error y el mensaje se elimina de la cola de envío, el servidor no hay ya intentar entregarlo.

Enviar usando un host inteligente
    El servidor intentará enviar correos electrónicos directamente a destino (recomendado en la mayoría de los casos). Selección en lugar de enviar a través de un host inteligente, se intentará entregar a través del servidor SMTP del ISP (se recomienda en caso de conexión poco fiable o ADSL residencial, IP dinámica, etc.)

Nombre de host
    El nombre del servidor de correo del proveedor.

Puerto
    El puerto del servidor de correo del proveedor.

Nombre de usuario
    Si el servidor del proveedor requiere autenticación, especifique el nombre de usuario. 

Contraseña
    La contraseña requerida por el proveedor.

Permitir conexión no cifrada
    Normalmente, si se utiliza una conexión autenticada (con nombre de usuario y contraseña),
     Se requiere una conexión cifrada para proteger la contraseña. Al seleccionar esta opción, se permitira una conexión no segura para conectarse al proveedor (no se recomienda, utilizar solamente si el ISP tiene problemas). 

Gestión de Colas 
================ 

Esta ficha le permite gestionar la cola de mensajes de correo electrónico en tránsito en el servidor. 
La tabla recoge todo el correo en espera de ser entregado, 
y está normalmente vacía. Los siguientes campos se mostrarán: 

* Id: identificador del mensaje 
* Remitente: desde la dirección de correo electrónico (que envió el mensaje) 
* Tamaño: El tamaño en bytes de la dirección de correo electrónico 
* Fecha: La fecha de la creación del correo electrónico 
* Destinatarios: la lista de destinatarios


Borrar 
------- 

Es posible eliminar un e-mail en la cola, por ejemplo, un correo electrónico enviado 
por error o demasiado grande. 

Retire todo 
------------- 

El botón se borrará todos los mensajes de correo electrónico en la cola. 

Pruebe a enviar 
--------------- 

Normalmente, el servidor, en caso de problemas al enviar el correo electrónico, 
reintenta en intervalos regulares. Al hacer clic en el intento de enviar mensajes de correo electrónico, 
será enviado de inmediato. 

Actualización 
-------------- 

Actualizar la lista de mensajes de correo electrónico en la cola.

================================= 
Direcciones de correo electrónico 
================================= 

Dirección de correo electrónico asociado a los usuarios o grupos del sistema. 


Crear / Modificar 
=================== 

Crear la asociación entre una nueva dirección de correo electrónico y un 
usuario o grupo ya presente en el sistema. 

Correo
    Especifique en el campo de texto de sólo la parte antes **@** personaje.
     A continuación, seleccione en el menú desplegable, si la dirección es para un dominio específico o para *todos los dominios* en el sistema.

Descripción
    Un campo de texto libre para registrar cualquier anotación.

Cuenta
    Seleccione un usuario o un grupo entre los que ya están en el
     sistema que se asociará a la dirección de correo electrónico.

Sólo las redes locales
    Al habilitar esta opción bloqueará la recepción de mensajes de los remitentes externos. 

Borrar 
======= 

Elimine la dirección de correo electrónico. Esto no afecta a 
mensajes que ya se entregan al usuario o grupo asociado con la dirección. 
Los próximos mensajes destinados dirección será rechazada. 

========================================== 
Direcciones de correo electrónico externas 
========================================== 

Direcciones de correo electrónico externas son buzones que 
se comprueba a intervalos regulares utilizando los protocolos **POP3** o **IMAP4**.
Los mensajes contenidos en el buzón de correo se descargan y se entregan a 
los usuarios o grupos locales, como por configuración en 
este formulario. 

Direcciones externas 
==================== 

Configure la lista de direcciones externas y la asociación con el usuario del sistema. 

Crear / Modificar 
------------------ 

Crear o editar una dirección externa. 

Correo
    La dirección de correo electrónico externa para comprobar.

Protocolo
    El protocolo utilizado para acceder al servidor remoto. Puede ser *POP3* o *IMAP4* (recomendado).

Dirección del servidor
    Nombre de host o dirección IP del servidor remoto.

Nombre de usuario
    Nombre de usuario utilizado para autenticarse en el sistema remoto.

Contraseña
    La contraseña utilizada para autenticar.

Cuenta
    Seleccione el usuario o grupo que recibirá los mensajes descargados.

Habilitar SSL
    Habilitar el cifrado de la conexión con el servidor remoto.

Eliminación de los mensajes descargados
    Si está activado, los mensajes descargados se eliminan del servidor remoto (recomendado). Deja disabilitados para mantener una copia en el servidor remoto.


Borrar 
------- 

Eliminar una cuenta *no* eliminar los mensajes ya entregados. 


Descargar ahora 
--------------- 

Inmediatamente se inicia la descarga de todas las direcciones externas. 


General 
======== 

Permitir
    Le permite activar o desactivar el demonio de Fetchmail que descarga correos electrónicos de direcciones externas.

Comprobacion
    Frecuencia de comprobación de nuevos mensajes en las direcciones externas. Se recomienda un intervalo de al menos 15 minutos.
