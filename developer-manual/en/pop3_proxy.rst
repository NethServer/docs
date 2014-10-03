==========
Proxy POP3 
==========

:index:`P3Scan` is POP3/s a full-transparent proxy-server for email clients. 
It intercepts all request to POP3 servers, download the mail and scan it for virus and spam.


Properties:

* ``SSLScan``: intercept connections to POP3s servers (port 995). Can be ``enabled`` or ``disabled.  Default is ``disabled``.
* ``SpamScan``: search mails for spam. Can be ``enabled`` or ``disabled.  Default is ``enabled``. 
* ``VirusScan`` search mails for virus. Can be ``enabled`` or ``disabled.  Default is ``enabled``. 
* ``Template``: set the template used for mail. It must be a file path, default is: ``/etc/p3scan/p3scan-en.mail``

Example: ::

  p3scan=service
    SSLScan=disabled
    SpamScan=disabled
    TCPPort=8110
    Template=/etc/p3scan/p3scan-en.mail
    VirusScan=enabled
    access=none
    status=enabled


POP3s
=====

When ``SSLScan`` is set to enabled, clients must be configured to use POP3s port (995) but without encryption.
The proxy will take care to encrypt connection to the server.
  
