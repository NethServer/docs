.. _mail_common-section:

===========
Mail common
===========

Package: nethserver-mail-common

Features

* Common infrastructure for :ref:`mail_server-section`, Postfix-based.
* Relay
* Smarthost
* Queue parameters: age + message size
* MX record configuration

Configure by console interface
==============================

Relay
-----

Enable relay host: messages to *mycompany.com* are routed to IP *10.1.1.7*, TCP port *25*: ::

  db domains setprop mycompany.com TransportType Relay RelayHost 10.1.1.7 RelayPort 25
  signal-event nethserver-mail-common-save


Disable relay host: ::

 db configuration setprop mydomain.com TransportType none
 signal-event nethserver-mail-common-save


Smarthost
---------

Enable smarthost: ::

  db configuration setprop postfix SmartHostStatus enabled SmartHostName smarthost.thatdomain.com 
  db configuration setprop postfix SmartHostAuthStatus enabled SmartHostUsername joe SmartHostPassword secret
  signal-event nethserver-mail-common-save


Disable smarthost: ::

  db configuration setprop postfix SmartHostStatus disabled
  signal-event nethserver-mail-common-save


Testing Postfix
===============

Install **nethserver-mail-dev** package: ::

  yum install nethserver-mail-dev 

Create or modify an existing domain record. Then set ``TransportType`` prop to ``SmtpSink``: ::

  db domains setprop test.tld TransportType SmtpSink
  signal-event domain-modify test.tld


Start the ``smtp-sink`` server: ::

  /usr/sbin/smtp-sink -L -c -u postfix unix:/var/spool/postfix/smtp-sink 128


Execute smtptest command (see command help for details): ::

  /sbin/e-smith/smtptest --from sender``example.com --to rcpt1``test.it --addr 10.1.1.4 --ehlo testhelo.test.it --subject 'Test message' 


Execute "smtp-source":http://linux.die.net/man/1/smtp-source command (from postfix package): ::

  smtp-source -c -l 32000 -m 50 -N -f sender``yourdomain.tld -t test``test.it -S TEST-SMTP-SOURCE -s 5 <HOST-IP-ADDRESS>



Code snippets
=============

Option ``reject_unknown_sender_domain`` may be too restrictive for testing setups. 
Add this custom template and initialize :file:`/etc/postfix/check_sender_access`
(see http://www.postfix.org/access.5.html) to allow your non existing domains. 

Don't forget to ``postmap /etc/postfix/check_sender_access`` !

::

 {
    #
    # 10check_sender_access
    #
    @smtpd_sender_restrictions = map {
        $_ eq 'reject_unknown_sender_domain' 
            ? ('check_sender_access hash:/etc/postfix/check_sender_access', 
               'reject_unknown_sender_domain') 
            : $_
    } @smtpd_sender_restrictions;
    '';
 }


Database Reference
==================

Sample database values.

Configuration database
----------------------

Postfix properties:

* ``AccessPolicies``: A comma separated list of values. Obsoletes ``SubmissionPolicyType`` prop. 
  Currently defined values are ``smtpauth`` and ``trustednetworks``.

  * *smtpauth* enable SMTP/AUTH on port 25, otherwise it is enabled only on 587 and 465 submission ports
  * *trustednetworks* allow relay from any host in trusted networks (green network included).

* ``AlwaysBccStatus {enabled,disabled}``: if ``enabled`` any message entering Postifx mail system is copied to the given ``AlwaysBccAddress``.
* ``AlwaysBccAddress``: an email address that always receives a message copy (controlled by ``AlwaysBccStatus``).
* ``MxRecordStatus {enabled,disabled}``: if ``enabled`` add ``smtp``, ``imap``, ``pop`` and ``pop3`` aliases into ``/etc/hosts`` 
  and configure ``smtp`` as MX record value.
* ``ContentInspectionType {default,amavisd-after-queue}``:

  * ``default``, apply the default content inspection type, depending on what packages are installed (i.e. nethserver-mail-filter)
  * ``amavisd-after-queue``, process messages through ``amavisd-new``. ``nethserver-mail-common`` uses amavis to append disclaimers to submitted messages


Example: ::

 postfix=service
    ...
    AccessPolicies=
    AlwaysBccStatus=disabled
    AlwaysBccAddress=
    MessageQueueLifetime=4
    MessageSizeMax=20000000
    MessageSizeMin=1048576
    MxRecordStatus=enabled
    SmartHostAuth=disabled
    SmartHostAuthStatus=disabled
    SmartHostName=192.168.5.252
    SmartHostPassword=password
    SmartHostPort=25
    SmartHostStatus=disabled
    SmartHostTlsStatus=enabled
    SmartHostUsername=ns1
    ContentInspectionType=default
    ConnectionsLimit=
    ConnectionsLimitPerIp=


Amavis: ::

 amavisd=service
    ...
    MaxProcesses=4
    VirusCheckStatus=disabled
    SpamCheckStatus=disabled


Domains database
----------------

Record of type `domain`: :: 

 internal.tld=domain
   ...
   TransportType=none

 mycompany.com=domain
   ...
   TransportType=Relay
   RelayHost=10.1.1.4
   RelayPort=25
   DisclaimerStatus=disabled

 test.tld=domain
   ...
   TransportType=SmtpSink



