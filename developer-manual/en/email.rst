
.. _email-section:

=====
Email
=====

Mail server implementation based on Postfix, Dovecot and Amavis.

Mail Filter enforces anti-spam and anti-virus checks on any message entering the system.


Features
========

In package ``nethserver-mail-common``:

* Common infrastructure for ``nethserver-mail-server and nethserver-mail-filter``, Postfix-based.
* Relay
* Smarthost
* Queue parameters: age + message size
* MX record configuration
* Disclaimer (based on Amavis)

In package ``nethserver-mail-server``:

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

In package ``nethserver-mail-filter``:

* Anti-spam with DNSBL (see: :ref:`unbound-section`)
* Anti-virus
* Attachment block
* Real-time Blackhole List (RBL) (disabled)
* Sender Policy Framework (SPF) (disabled)
* Customized spam threshold 
* Sender WBL, Recipient whitelist 


Database Reference
==================


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

 ----8<----- mail-filter -----------

    RblStatus=disabled
    RblServers=host1,host2.. 
    SpfStatus=disabled
    ContentInspectionType=amavisd-before-queue

 ----8<----- mail-server -----------

    AdsMapUserPrincipalStatus=enabled
    AdsGroupsDeliveryType=copy
    SystemUserRecipientStatus=disabled


``nethserver-mail-common``

    * ``AccessPolicies``: A comma separated list of values. Obsoletes
      ``SubmissionPolicyType`` prop.  Currently defined values are
      ``smtpauth`` and ``trustednetworks``.

      * *smtpauth* enable SMTP/AUTH on port 25, otherwise it is enabled
	only on 587 and 465 submission ports

      * *trustednetworks* allow relay from any host in trusted networks
	(green network included).

    * ``AlwaysBccStatus {enabled,disabled}``: if ``enabled`` any message
      entering Postifx mail system is copied to the given
      ``AlwaysBccAddress``.

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

``nethserver-mail-filter``

    * ``ContentInspectionType {default,amavisd-before-queue}``:

      * ``default``, apply the default content inspection type,
         depending on what packages are
         installed. ``nethserver-mail-filter`` changes the default to
         ``amavisd-before-queue``
    
      * ``amavisd-before-queue``, executes anti-spam and anti-virus
        checks on open SMTP connections. Only CLEAN messages are
        allowed to enter the postfix queue
    

``nethserver-mail-server``

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



Amavis example: ::

 amavisd=service
    ...
    MaxProcesses=4
    VirusCheckStatus=disabled
    SpamCheckStatus=disabled

 ----8<----- mail-filter -----------

    SpamCheckStatus=enabled
    VirusCheckStatus=enabled

    AdminNotificationStatus=disabled
    AvailableDecoders=mail,asc,uue,hqx,ync,F,Z,gz,bz2,lzo,rpm,cpio,tar,deb,zip,7z,rar,arj,arc,zoo,lha,doc,cab,tnef,exe
    BlockAttachmentClassList=
    BlockAttachmentCustomList=pif
    BlockAttachmentCustomStatus=disabled
    BlockAttachmentStatus=enabled
    EnabledDecoders=mail,asc,uue,hqx,ync,F,Z,gz,bz2,lzo,rpm,cpio,tar,deb,zip,7z,rar,arj,arc,zoo,lha,doc,cab,tnef,exe
    RecipientWhiteList=
    SenderBlackList=
    SenderWhiteList=clienti@example.it,marketing@domain.com
    SpamDsnLevel=20
    SpamKillLevel=9
    SpamSubjectPrefixStatus=disabled
    SpamSubjectPrefixString=***SPAM*** 
    SpamTag2Level=5
    SpamTagLevel=2.0


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


Testing Dovecot with Mutt
=========================

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
To avoid typing the password again and again write it in :file:`.muttrc`: ::

 set spoolfile="imaps://admin*vmail:PASSWORD@localhost/"
 set folder=""

``PASSWORD`` must be URL-encoded. For instance the slash character ``/`` is encoded as ``%2f``.


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


RBL server list
===============

Enable RBL checks, by adding *zen.spamhaus.org* to the RBL server list: ::

  db configuration setprop postfix RblStatus enabled RblServers zen.spamhaus.org
  signal-event nethserver-mail-filter-save


Active Directory integration
============================

*Available since nethserver-mail-server-1.4.0*

When Samba role is ADS (Active Directory member) Dovecot and Postifx
configuration are changed as follow:

* SASL/GSSAPI authentication mechanism is available on IMAP and SMTP
  authentication protocols.

* dovecot uses AD LDAP as user database. The query configuration is in
  ``/etc/dovecot/active-directory.conf`` template. The dovecot ldap
  client library authenticate itself with Kerberos.

* postfix uses AD LDAP as additional *virtual* table, to resolve email
  aliases. The query configuration is in
  ``/etc/postfix/active-directory.cf``. The postfix ldap client
  library authenticate itself with Kerberos.



Configuring mail aliases in Active Directory
--------------------------------------------

The email address is matched against the following AD LDAP
attributes/values:

* ``mail``: exact match

* ``userPrincipalName``: exact match

* ``otherMailbox``: ``smtp:<email address>``
  ("otherMailbox":http://msdn.microsoft.com/en-us/library/windows/desktop/ms679091(v=vs.85).aspx
  is a multi-value attribute)

* ``proxyAddresses``: ``smtp:<email address>``
  ("proxyAddresses":http://technet.microsoft.com/en-us/library/cc720282(v=ws.10).aspx
  attribute should be used by Exchange servers)

Users and/or groups objects are searched, according to
``postfix/AdsGroupsDeliveryType`` prop value:

* ``shared`` mail to a security group is delivered to the group
  (shared) mailbox

* ``copy`` mail to a security group is delivered to group members

In other words, if ``postfix/AdsGroupsDeliveryType`` is ``copy``,
security groups are treated like distribution list groups.


Recompiled packages
===================

Kerberos support is limited on upstream Dovecot and Postfix packages.
For Active Directory integration we must install more recent software
versions provided by Morten Stevens from Fedora People
(http://mstevens.fedorapeople.org/el6/):

* ``postfix`` recompiled with ``-DUSE_LDAP_SASL`` option

* ``dovecot``

