=======
Hylafax
=======

Hylafax is a fax server for receiving and sending faxes.

Key features:

* Modem automatic configuration
* Virtual modem
* Ingoing/outgoing fax configuration
* Extensible accounting system
* Mail2Fax
* Mail server integration

Modem configuration
===================

Hylafax+ uses a tool called ``faxaddmodem`` which guides the user throw modem configuration. We developed a simple non-interactive wrapper called ``neth-addmodem``.

The script reads basic information, like the fax device name, from the SME db and use these data to setup the modem.

Accounting (FaxAccounting)
==========================

Every time a fax is received or sent, Hylafax will execute the ``/var/spool/hylafax/etc/FaxAccounting`` script. FaxAccounting runs all executable scripts inside the directory ``/var/spool/hylafax/etc/accounting`` in alphabetical order.

The default configuration will execute the script ``00savefiles`` which saves all submitted and received faxes to ``/var/lib/nethserver/fax/docs``

Incoming fax (FaxDispatch)
==========================

Hylafax requires a mail address where incoming faxes will be sent.
If ``SendTo`` prop is not set, all faxes will be forwarded to root mailbox.

When a fax is received, Hylafax will execute the ``/var/spool/hylafax/etc/FaxDispatch`` script. FaxDispatch runs all executable scripts inside the directory ``/var/spool/hylafax/etc/dispatch`` in alphabetical order.

The default configuration will execute the script ``90print``. If ``hylafax`` prop ``PrintReceived`` is enabled, all faxes are printed into the ``PrinterName`` printer.

Outgoing fax (FaxNotify)
========================

When a fax is sent, Hylafax will execute the ``/var/spool/hylafax/etc/FaxNotify`` script. FaxNotify runs all executable scripts inside the directory ``/var/spool/hylafax/etc/notify`` in alphabetical order.

Custom scripts
==============

When adding a custom script not handled by an RPM, please add the script in a directory inside ``/var/lib/nethserver/fax/`` and link it to the final destination. In fact the ``/var/spool/hylafax/etc/`` directory is not (actually) in the backup.

So, for example, if you wish to add a ``90test`` script to accounting, save the files in the ``/var/spool/hylafax/etc/accounting`` directory and link to the Hylafax configuration directory: ::

 ln -s /var/lib/nethserver/fax/accounting/90test /var/spool/hylafax/etc/accounting/90test 

Authentication
==============

Clients are authenticated using reverse dns queries: all ip resolved with the same domain as server itself are automatically authenticated. If reverse dns query, client can authenticate using user name and password of a user inside ``faxmaster`` group.

Clients should always use username, despite of authentication method used.

Internationalization
====================

Notification on incoming and outgoing faxes can be localized using the ``Lang`` property. Default value is ``en_US``.

Client configuration
====================

The only tested client is YajHFC (see http://www.yajhfc.de/). Current configuration works only with LAN clients.

Configuration:

* Insert server ip (or hostname) and username
* Leave blank the password field
* Disable passive mode

Configuration DB
================

Example: ::

 hylafax=configuration
    AreaNumber=
    ClientShowReceived=disabled
    CountryCode=39
    DateFormat=DMY
    Debug=disabled
    DispatchFileType=ps
    FaxDevice=ttyS0
    FaxName=fax
    FaxNumber=
    InternationalPrefix=00
    Lang=it_IT
    LongDistance=0
    Mail2Fax=disabled
    Mode=both
    NotifyFileType=tif
    NotifyMaster=always
    PBXPrefix=
    PaperSize=A4
    PrintReceived=disabled
    PrinterDriver=ljet4
    PrinterName= 
    Resolution=196
    RingsBeforeAnswer=1
    SambaFax=disabled
    SambaFaxName=SambaFax
    SendReport=disabled
    SendTo=aa``test.tld
    SummaryReport=disabled
    WaitDialTone=enabled

 hylafax-hfaxd=service
    TCPPort=4559
    status=enabled
    access=private

 hylafax-faxq=service
    status=enabled
