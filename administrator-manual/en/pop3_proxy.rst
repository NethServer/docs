
.. _pop3_proxy-section:

==========
POP3 proxy
==========

.. warning::

    This module is provided by two alternative implementations, "POP3 proxy" and
    "POP3 proxy 2 (Beta)". See :ref:`email2-section` for upgrade instructions
    and more information

A user on the LAN can configure an email client 
in order to connect to an external POP3 server and download mail messages. 
Please note that fetched mail could contain viruses that may infect computer on the network.

The POP3 proxy intercepts connection to external servers on port 110, then it scans all incoming email, 
in order to block viruses and tag spam. 
The process is absolutely transparent to mail clients. The user will believe that they are connected directly 
to the provider's POP3 server, but the proxy will intercept all traffic and handle the connection to the server. 

It's possible to selectively activate the following controls: 

* antivirus: messages containing virus are rejected and a notification email is sent to the user
* spam: messages will be marked with the appropriate anti-spam scores


POP3s
=====

The proxy can also intercept POP3s connections on port 995. 
The proxy will establish a secure connection to the external server, but data exchange with LAN client 
will be in the clear text.

.. note:: Mail clients must be configured to connect to port 995 and will have to turn off encryption. 
