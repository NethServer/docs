==============
POP3 connector
==============

The package configure Fetchmail as a daemon to download external POP3/IMAP mail accounts to local accounts.

Fetchmail reads the configuration from standard input at startup, detaches in background and runs as the ``fetchmail`` user. 
The configuration is actually obtained from ``fetchmailrc`` template which is expanded on-the-fly by the ``fetchmail`` init script.

Log files:
* :file:`/var/log/fetchmail.log`
* :file:`/var/log/maillog`


Database
========

General configuration is saved in ``configuration`` database under the ``fetchmail`` key.

Properties:

* ``authType``: authentication type. Default: ``password``
* ``externalFreq``: polling interval in minutes
* ``extraOptions``:   command line options passed to daemon. Default: ``--fastuidl 1 --sslproto ssl23``


Example: ::

 fetchmail=service
    authType=password
    externalFreq=5
    extraOptions=--fastuidl 1


External mail accounts are record of type ``fetchmail`` inside the ``fetchmail`` database.

Properties:

* key: external mail address
* ``popserver``: remote mail server (ip or host name)
* ``username``: remote account user name
* ``password``: remote user password
* ``nokeep``: if ``YES``, delete remote fetched messages. Can be ``YES`` or ``NO`` (default is ``YES``)
* ``active``: enable/disable account. Can be ``YES`` or ``NO`` (default is ``YES``)
* ``ssl``   enable/disable SSL connection. Can be ``YES`` or ``NO`` (default is ``NO``)
* ``account``: local machine account (user or group) where delivery fetched mail

Example: ::

 goofy@myserver.com=fetchmail
    account=myinternaluser
    active=YES
    nokeep=NO
    password=mypass
    popserver=mail.myserver.com
    proto=imap
    ssl=YES
    username=goofy

