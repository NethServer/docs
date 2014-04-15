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
     Seleccione esta opción para configurar el servidor para entregar 
     el correo entrante dirigido al dominio especificado 
     en las carpetas locales. 

Reenviar a otro servidor 
     Si selecciona esta opción, el correo entrante será 
     se transmitirá al servidor especificado. 

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
     Este prefijo se añade al objeto fundamental de los correos electrónicos reconocidos 
     como spam. 

Bloqueo de archivos adjuntos 
     El servidor de correo electrónico bloquee mensajes de correo electrónico que contengan archivos adjuntos de tipos 
     especificado.

Ejecutable 
     El servidor de correo electrónico bloqueará programas ejecutables en archivos adjuntos de correo electrónico. 

Archivo 
     El servidor de correo electrónico bloquee mensajes de correo electrónico con archivos adjuntos que contienen archivos comprimidos (ZIP, 
     rar, etc.) 

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

Permitir conexiones sin cifrar 
     Permite habilitar el acceso a las carpetas que utilizan protocolos no encriptados (no recomendado). 

Espacio en disco 
     Le permite limitar el uso del disco por correo electrónico. 

     * Unlimited: seleccione no imponer límites 
     * Aplicar cuota: límite de espacio máximo de correo para cada usuario con el valor 
       indicado (cuota de correo electrónico).

Mover a la carpeta *junkmail* 
     Mensajes de correo electrónico identificado como spam se mueven a cada carpeta de usuario 
     *Junkmail* en lugar de ser entregado a la bandeja de entrada. 


Mensajes 
======== 

Configurar la gestión de mensajes de correo electrónico. 

Acepte el tamaño del mensaje a 

     Utilice el cursor para seleccionar el tamaño máximo de un  mensaje de correo electrónico única. El servidor rechazará electrónico más grande que el valor establecer y devolverá un error explicativo. 

Vuelva a intentar el envío de 

     Utilice el cursor para seleccionar el tiempo máximo durante el cual el servidor 
     tratar de enviar un mensaje. Cuando llega el tiempo máximo 
     y el correo electrónico no ha sido entregado, el remitente recibirá un 
     error y el mensaje se elimina de la cola de envío, el servidor no hay 
     ya intentar entregarlo.

Send using a smarthost
    The server will attempt to send emails directly to
    destination (recommended in most cases). Selecting
    instead to sent through a smarthost, it will attempt to deliver them through the 
    ISP's SMTP server (recommended in case of unreliable connection or
    Residential ADSL, dynamic IP, etc).

Host Name
    The name of the mail server of the provider.

Port
    The port of the mail server of the provider.

Username
    If the provider's server requires authentication, specify the 
    username.

Password
    The password required by the provider.

Allow non-encrypted connection
    Normally, if using an authenticated connection (with username and password),
    an encrypted connection is required to protect the password. Selecting this option will
    permit a non-secure connection to connect to the
    provider (not recommended, use only if ISP has problems).

Queue Management
================

This tab allows you to manage the queue of emails in transit on the server.
The table lists all the mail waiting to be delivered,
and is normally empty. The following fields will be shown:

* Id: identifier of the message
* Sender: from email address (who sent the message)
* Size: The size in bytes of the email
* Date: The date of creation of the email
* Recipients: the list of recipients


Delete
-------

It's possible to delete an e-mail in the queue, for example, an email sent
by mistake or too large.

Remove all
-------------

The button will delete all the emails in the queue.

Try sending
-------------

Normally, the server, in case of problems while sending the email,
retries at regular intervals. Clicking Attempt to send, emails
will be sent immediately.

Update
--------

Reload the list of emails in the queue.

===============
Email addresses
===============

Associate email address to users or groups of the system.


Create / Modify
===================

Create the association between a new email address and a
user or group already present in the system.

Email
    Specify in the text field only the part before **@** character.
    Then choose from the drop-down menu if the address is for a
    specific domain or for *all* domains in the system.

Description
    A free text field for recording any annotation.

Account
    Select a user or a group among those already in the
    system to be associated with the email address.

Only local networks
    Enabling this option will block the reception of messages
    from external senders.

Delete
=======

Delete the e-mail address. This does not affect
messages already delivered to the user or group associated with the address.
Future messages destined the address will be rejected.

========================
External email addresses
========================

External email addresses are mailboxes that
are checked at regular intervals using the **POP3** or **IMAP4** protocol.
Messages contained in the mailbox are downloaded and delivered to
local users or groups, as per configuration in 
this form.

External addresses
==================

Configure the list of external addresses and the association with the user of the system.

Create / Modify
---------------

Create or edit an external address.

Email
    The external email address to check.

Protocol
    The protocol used to access the remote server. It can be *POP3* or *IMAP4* (recommended).

Server Address
    Host name or IP address of the remote server.

Username
    Username used for authentication to the remote system.

Password
    The password used to authenticate.

Account
    Select the user or group that will receive the downloaded messages. 

Enable SSL
    Enable encryption of the connection with the remote server.

Delete messages downloaded
    If enabled, downloaded messages will be deleted from the remote server (recommended). Leave disabled to keep
    a copy on remote server.

Delete
-------

Deleting an account will *not* delete the messages already delivered.


Download now
------------

Immediately starts the download from all external addresses.


General
========

Enable
    Allows you to enable or disable the Fetchmail daemon that
    downloads emails from external addresses.

Check every
    Frequency of checking for new messages on the external addresses.
    It is recommended an interval of at least 15 minutes.
