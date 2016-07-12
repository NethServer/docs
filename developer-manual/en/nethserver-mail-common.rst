nethserver-mail-common
======================

Mail system implementation based on Postfix, Dovecot and Amavis.

Features
--------

* Common infrastructure for ``nethserver-mail-server and nethserver-mail-filter``, Postfix-based.
* Relay
* Queue parameters: age + message size
* MX record configuration
* Disclaimer (based on Amavis)

Configuration database
----------------------

Postfix example: ::

 postfix=service
    ...
    AccessPolicies=
    AlwaysBccStatus=disabled
    AlwaysBccAddress=
    MessageQueueLifetime=4
    MessageSizeMax=20000000
    MessageSizeMin=1048576
    MxRecordStatus=enabled
    ContentInspectionType=default
    ConnectionsLimit=
    ConnectionsLimitPerIp=
    
* ``AccessPolicies``: A comma separated list of values. Obsoletes
  ``SubmissionPolicyType`` prop.  Currently defined values are
  ``smtpauth`` and ``trustednetworks``.

* *smtpauth* enable SMTP/AUTH on port 25, otherwise it is enabled
  only on 587 and 465 submission ports

* *trustednetworks* allow relay from any host in trusted networks
  (green network included).

* ``AlwaysBccStatus {enabled,disabled}``: if ``enabled`` any message
  entering Postifx mail system is copied to the given ``AlwaysBccAddress``.

* ``AlwaysBccAddress``: an email address that always receives a
  message copy (controlled by ``AlwaysBccStatus``).

* ``MxRecordStatus {enabled,disabled}``: if ``enabled`` add ``smtp``,
  ``imap``, ``pop`` and ``pop3`` aliases into ``/etc/hosts`` and
  configure ``smtp`` as MX record value.

* ``ContentInspectionType {default,amavisd-after-queue}``:

* ``default``, apply the default content inspection type, depending
  on what packages are installed (i.e. nethserver-mail-filter)
  
* ``amavisd-after-queue``, process messages through
  ``amavisd-new``. ``nethserver-mail-common`` uses amavis to append
  disclaimers to submitted messages

Testing Postfix
---------------

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

