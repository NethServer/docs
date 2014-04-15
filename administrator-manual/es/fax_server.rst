=============== 
servidor de fax 
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
Número de fax 
     El número de fax del remitente. 
Remitente (TSI) 
     La ETI se imprimirá en el encabezado del fax del destinatario, por lo general en la fila superior. Es posible introducir el número de fax o el nombre de una longitud total de hasta 20 caracteres (se recomienda el nombre de la empresa). Sólo se permiten caracteres alfanuméricos.


Módem 
===== 

Módem 
     El puerto físico (COM o USB) a la que el módem está conectado o un módem fax virtual 

     * Estándar de dispositivo: le permite seleccionar el dispositivo de una lista de los puertos comunes 
     * Dispositivo personalizado: permite especificar un dispositivo personalizado para ser utilizado como un módem fax. *Debe ser el nombre de un dispositivo en el sistema.* 
Modo 
     Especifica el modo de funcionamiento del dispositivo seleccionado. Los modos disponibles son: 

     * Enviar y recibir: el módem se utiliza para enviar y recibir faxes 
     * Recibir sólo: el módem sólo se utilizará para la recepción de faxes 
     * Enviar sólo: el módem sólo se utilizará para el envío de faxes 
PBX Prefijo 
     Si el módem de fax está conectado a una centralita, puede que tenga que introducir un código de acceso a "obtener una línea externa." 
     Si el módem está conectado directamente a una línea o el PBX requiere ningún código, deje el campo vacío. 
     Si estás detrás de un PBX, introduzca el prefijo que se debe marcar.

Wait for dial tone
    Some modems are not capable of recognizing a dial tone
    (especially if connected to a PBX) and do not dial the number
    signalling the absence of tone (error "No Dial Tone").

    To configure the modem to ignore the absence of line and
    immediately dial the number select Disabled. The recommended setting is
    "Enabled", you may want to disable * Wait for dial tone * only in case of problems.


Email notifications
===================

Received faxes format
    By default, the fax server forwards the received faxes as
    emails with an attachment. Specify the email address
    where faxes will be delivered, and one or more formats for
    the attachment. To not receive the fax as attachment, but only a
    notification of reception, deselect all formats.

Forward received faxes to

    * Group "faxmaster"
        By default, the received faxes are sent to *faxmaster*: if
        a user needs to receive incoming faxes should be added to this
        group.
    * External email
        Input an external email address in case you
        want to send received faxes to an email address not on this server.

Sent faxes format
    If requested by the client, the server sends an email notification with an
    attachment. Choose the format in which you prefer to receive the fax.
    Deselect all options if you do not want to receive the fax attached.
    

Add delivery notification
    If selected, adds a delivery notification report in the sent fax email.



Additional functions
=====================

View faxes sent by the client
    The fax clients also allow you to view all incoming faxes. If,
    for reasons of confidentiality, you want to filter out faxes
    received, disable this option.

Automatically print received faxes
    Automatically print all received faxes on a
    PCL5 compatible printer configured on |product|. The printer should be
    selected using the appropriate drop down menu.

SambaFax
    By selecting this option, the fax server can make available to the
    local area network a virtual printer named "sambafax" that will
    be configured on the client, by selecting the Apple LaserWriter driver
    16/600 PS. Documents printed on the network printer sambafax
    must contain the exact phrase "Fax Number:" followed by the
    fax number of the recipient.

Send daily report
    Send a daily report to the administrator

=========
IAX Modem
=========

This page allows you to configure IAX modems.

An IAX modem is a software modem that uses an IAX channel (usually 
provided by an Asterisk PBX) instead of a traditional telephone line.


Create / Modify
===============

Name
    Name the new IAX modem that you are creating.

Server IP
    IP address of the server on which the IAX modem registers (eg IP address of the Asterisk server).

Extension
    IAX extension on which you want to receive faxes.

Password 
    IAX extension password defined previously.

Caller ID
    Caller ID (number) shown in the outgoing faxes.

Caller Name
    Caller name shown in the outgoing faxes.

