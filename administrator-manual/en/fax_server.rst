==========
Fax server
==========

.. note::

  The configuration page of this module is available only in the old Server Manager
  and will not be ported to the new one.


The :index:`fax` server allows you to send and receive faxes via a modem
connected directly to a server port or through a :index:`virtual modem`. 

The web interface allows you to configure:

* Area code and fax number
* Sender (TSI)
* A physical modem with phone line parameters and how to send/receive faxes
* One or more :ref:`iax-modem`
* Email notifications for sent and received faces, with the attached document in multiple formats (PDF, PostScript, TIFF)
* Print received faxes
* Virtual Samba printer
* Daily report of sent faxes
* Sending faxes via email


Modem
=====

Although HylaFAX supports a large number of brands and models, we recommend using an external serial or USB modem.

If an internal modem blocks, you must reboot the whole server,
while an external modem can be turned off separately.
In addition, the majority of internal modems on the market belongs to the so-called family of winmodem,
"software" modems that need a driver, usually available only on Windows.

Also be aware that many external USB modem are also winmodem.

You should prefer modems in Class 1 or 1.0, especially if based on Rockwell/Conexant or Lucent/Agere chips.
The system also supports modems in classes 2, 2.0 and 2.1.

Client
======

We recommend using the fax client YajHFC (http://www.yajhfc.de/) that connects directly to the server and allows:

* the use of an LDAP address book
* ability to select the modem to send
* view the status of modems

Authentication
--------------

The system supports two authentication methods for sending faxes:

* Host Based: uses the IP address of the computer sending the request
* PAM: uses username and password, users must belong to the group *faxmaster*.
  The *faxmaster* group must be explicitly created.

Also make sure to enable the :guilabel:`View faxes from clients` option.


Samba virtual printer
=====================

If SambaFax option is enabled, the server will create virtual printer called "sambafax" available to the local network.

Each client must configure the printer using the Apple LaserWriter 16/600 PS driver.

Sent documents must meet the following prerequisites:

* Must contain exactly the string "Numero Fax:", containing the fax number, for example: ::

   Numero Fax: 12345678

* The string may be present in any position of the document, but on a single line
* The string must be written in non-bitmap font (eg. Truetype)

Faxes will be sent using the sending user id. This information will be displayed in the fax queue.


Mail2Fax
========

.. warning::
   To enable this function, make sure that ``Email`` module is installed.

All emails sent to the local network at ``sendfax@<domainname>`` will be transformed into a fax and sent to the recipient.

The ``<domainname>`` must match a local mail domain configured for local delivery.

The email must comply with this format:

* The recipient's number must be specified in the object (or subject)
* The email must be in plain text format
* It may contain attachments such as PDF or PS which will be converted and sent with your fax

.. Note :: This service is enabled only for clients that send mails from the green network.

.. _iax-modem:

Virtual modems
==============

Virtual modems are software modems connected to a PBX (Asterisk usually) using
a IAX extension.

The configuration of the virtual modems consists of two parts:

1. Creation of IAX extension within the PBX
2. Configuration of virtual modem

