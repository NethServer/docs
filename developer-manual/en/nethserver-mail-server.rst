nethserver-mail-server
======================

Features
--------

* IMAP/POP3 mailbox access protocols
* STARTTLS enabled by default
* Mail quota
* Sieve filters
* Postfix/dovecot-lda integration
* Multi-domain
* Domain-specific configuration
* Pseudonyms 
* SMTP authentication
* Active Directory integration
* SpamAssassin's Bayesian classifier training (``spamtrainers`` group)
* Spam retention time

Configuration database
----------------------

Postfix example: ::

  postfix=service
      ...
      AdsMapUserPrincipalStatus=enabled
      AdsGroupsDeliveryType=copy
      SystemUserRecipientStatus=disabled
    
* ``AdsMapUserPrincipalStatus {enabled,disabled}`` If ``enabled``,
  the user principal is considered a vaild mail address (if mail
  domain exists, also)

* ``AdsGroupsDeliveryType {shared,copy}`` Mail to security group
  is delivered shared or copied to its members, according to the
  prop value

* ``SystemUserRecipientStatus {enabled,disabled}`` ``enabled``,
  accept from any network the recipient addresses formed by user
  account names and domain part ``localhost``,
  ``localhost.<domainname>`` and FQDN hostname.

Dovecot example: ::

  dovecot=service
    ...
    ImapStatus=enabled    
    PopStatus=disabled
    TlsSecurity=optional
    MaxProcesses=400
    MaxUserConnectionsPerIp=12
    SharedMailboxesStatus=disabled
    LmtpInetListenerStatus=disabled
    QuotaStatus=enabled
    QuotaDefaultSize=20
    QuotaUiFunction=
    SpamFolder=junkmail

Properties:

* ``TlsSecurity {optional,required}`` 
  controls dovecot ``disable_plaintext_auth`` parameter: if set to ``required`` clear-text authentication methods are disabled, while ``optional`` enables them.
* ``QuotaUiFunction``
  If set the sliders in server-manager apply the given increments, expressed in units of 100MB. 



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

  example.com=domain
    ...
    TransportType=LocalDelivery
    UnknownRecipientsActionType=deliver
    UnknownRecipientsActionDeliverMailbox=jdoe
    AlwaysBccStatus=enabled
    AlwaysBccAddress=admin``there.org

  other.net=domain
    ...
    TransportType=Relay
    RelayHost=mail.other.net
    RelayPort=25
  
Accounts database
-----------------

Groups: ::

  employees=group
     ...
     MailStatus=enabled
     MailDeliveryType=shared

  administrators=group
     ...
     MailStatus=enabled
     MailDeliveryType=copy

  faxservice=group
     ...
     MailStatus=disabled
     MailDeliveryType={any}

User: ::

  jdoe=user
     FirstName=John
     LastName=Doe
     ...
     MailStatus=enabled
     MailQuotaType=custom
     MailQuotaCustom=15
     MailForwardStatus=disabled
     MailForwardAddress=
     MailForwardKeepMessageCopy=no

  and his pseudonyms: ::

   john.doe``example.com=pseudonym
     Account=jdoe
     ControlledBy=system
     Access=public

   doe``=pseudonym
     Account=jdoe
     ControlledBy=operators
     Access=private
   
Testing Dovecot with Mutt
-------------------------

Read admin's mail with Mutt IMAP client.
Quickstart: ::

  yum install mutt
  cat - <<EOF > ~/.muttrc 
  set spoolfile="imaps://admin*vmail@localhost/"
  set folder=""
  EOF
  mutt

See: http://dev.mutt.org/doc/manual.html

When mutt starts always asks for the ``vmail`` master-user password. 
This is an auto-generated random password, stored in ``/etc/dovecot/master-users``. 
To avoid typing the password again and again write it in ``.muttrc``: ::

  set spoolfile="imaps://admin*vmail:PASSWORD@localhost/"
  set folder=""

``PASSWORD`` must be URL-encoded. For instance the slash character ``/`` is encoded as ``%2f``.   