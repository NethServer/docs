====
CUPS
====

CUPS is the printer server. It converts the page descriptions produced by your application (put a paragraph here, draw a line there, and so forth) into something your printer can understand and then sends the information to the printer for printing.


Configuration
=============

Use the web configuration tool http://server:631

You'll need to create 2 printers:

* Raw printer for use with Samba and Windows hosts
* A PPD defined printer to user via IPP and Linux hosts

You already have a PDF printer configured and ready to use. All files printed via PDF Printer are saved in the user home directory, inside the directory called "Desktop". You can download the files using samba.

Printer discovery
=================

CUPS uses avahi to discover network-attached printer. If you wish to use this features, just install the optional package *nethserver-avahi*.


Old Windows clients
===================

If you have Windows NT/2000 client, you should use this option which enable "use client driver" in smb.conf:

 config setprop smb UseClientDriver yes

Configuration DB
================

Reference: ::

 cups=service
    TCPPort=631
    UDPPort=631
    access=private
    status=enabled


Links

* Offical CUPS web site: http://www.cups.org/
* Offical AVAHI web site: http://avahi.org/
  
