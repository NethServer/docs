==========
Fax Server
==========

The fax server allows you to send and receive faxes via a modem
connected directly to a server port (COM or USB) or through a 
virtual IAX modem. 

The modem must support sending and receiving faxes preferably in class 1 or 1.0 (2, 2.0 and 2.1 classes are also supported).

General
========

Country code
    The international prefix to be prepended to your fax number.
Prefix
    Area code.
Fax Number
    Fax number of the sender.
Sender (TSI)
    The TSI is printed in the header of the recipient fax, usually in the top row. It's possible to enter the fax number or name of a total length of up to 20 characters (recommended your company name). Only alphanumeric characters are allowed.


Modem
=====

Modem
    The physical port (COM or USB) to which the modem is attached or virtual fax modem

    * Device Standard: allows you to select the device from a list of common ports
    * Custom Device: allows you to specify a custom device to be used as a fax modem. * Must be the name of a device in the system.*
Mode
    Specifies the operating mode of the selected device. The available modes are:

    * Send and receive: the modem will be used to send and receive faxes
    * Receive only: the modem will be used only for receiving faxes
    * Send only: the modem will only be used for sending faxes
PBX Prefix
    If the fax modem is connected to a PABX, you may need to enter an access code to "get an outside line."
    If the modem is directly connected to a line, or the PBX requires no code, leave the field empty.
    If you are behind a PBX, enter the prefix to be dialed.

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
    PCL5 compatible printer configured on NethServer. The printer should be
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

