.. _mail_server-section:

===========
Mail server
===========

Package: nethserver-mail-server

Mail server implementation based on Dovecot and Postfix. See also the :ref:`mail_common-section` and :ref:`mail_filter-section`.

Fetures:

* IMAP/POP3 mailbox access protocols
* TLS enabled by default
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


Reference
=========

Database values and feature setups.

Configuration database
----------------------

Example: ::

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

Postfix: ::

 postfix=service
    ...
    AdsMapUserPrincipalStatus=enabled
    AdsGroupsDeliveryType=copy
    SystemUserRecipientStatus=disabled

* ``AdsMapUserPrincipalStatus {enabled,disabled}``
  If ``enabled``, the user principal is considered a vaild mail address (if mail domain exists, also)
* ``AdsGroupsDeliveryType {shared,copy}``
  Mail to security group is delivered shared or copied to its members, according to the prop value
* ``SystemUserRecipientStatus {enabled,disabled}``
  ``enabled``, accept from any network the recipient addresses formed by user account names and domain part ``localhost``, ``localhost.<domainname>`` and FQDN hostname.

Domains database
----------------

Example: ::

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
   
Mutt
====

Read admin's mail with Mutt IMAP client.
Quickstart: ::

 yum install mutt
 cat - <<EOF > ~/.muttrc 
 set spoolfile="imaps://admin*vmail``localhost/"
 set folder=""
 EOF
 mutt

See: http://dev.mutt.org/doc/manual.html

When mutt starts always asks for the ``vmail`` master-user password. 
This is an auto-generated random password, stored in ``/etc/dovecot/master-users``. 
To avoid typing the password again and again write it in :file:`.muttrc`: ::

 set spoolfile="imaps://admin*vmail:PASSWORD``localhost/"
 set folder=""

``PASSWORD`` must be URL-encoded. For instance the slash character ``/`` is encoded as ``%2f``.

IP-based access table
=====================

Some SMTP clients do not support SMTPAUTH, submission ports, and are not fully compliant with SMTP standard (scanners, printers...). Those clients must be added to the ``access`` table, to enable IP-based access and bypass strict checks.

Adding IP 192.168.123.4 to the list of clients without restrictions: ::
   
  mkdir -p /etc/e-smith/templates-custom/etc/postfix/access
  echo "192.168.123.4 OK" >> /etc/e-smith/templates-custom/etc/postfix/access/10custom_whitelist
  signal-event nethserver-mail-common-save

Active Directory integration
============================

*Available since nethserver-mail-server-1.4.0*

When Samba role is Active Directory member dovecot and postifx configuration are changed as follow:

* SASL/GSSAPI authentication mechanism is available on IMAP and SMTP authentication protocols.
* dovecot uses AD LDAP as user database. The query configuration is in ``/etc/dovecot/active-directory.conf`` template. The dovecot ldap client library authenticate itself with Kerberos.
* postfix uses AD LDAP as additional *virtual* table, to resolve email aliases. The query configuration is in ``/etc/postfix/active-directory.cf``. The postfix ldap client library authenticate itself with Kerberos.

Configuring mail aliases in Active Directory
--------------------------------------------

The email address is matched against the following AD LDAP attributes/values:

* ``mail``: exact match
* ``userPrincipalName``:   exact match
* ``otherMailbox``:  ``smtp:<email address>`` ("otherMailbox":http://msdn.microsoft.com/en-us/library/windows/desktop/ms679091(v=vs.85).aspx is a multi-value attribute)
* ``proxyAddresses``:  ``smtp:<email address>`` ("proxyAddresses":http://technet.microsoft.com/en-us/library/cc720282(v=ws.10).aspx attribute should be used by Exchange servers)

Users and/or groups objects are searched, according to ``postfix/AdsGroupsDeliveryType`` prop value:

* ``shared`` mail to a security group is delivered to the group (shared) mailbox
* ``copy`` mail to a security group is delivered to group members

In other words, if  ``postfix/AdsGroupsDeliveryType`` is ``copy``, security groups are treated like distribution list groups.

Missing features
----------------

When using Active Directory LDAP as user database some features are currently not available:
* group copy delivery
* group shared folder delivery

What happens if AD is not available (even for a short period) when ``postfix`` and ``dovecot`` daemons are started? Kerberos tickets are not valid and GSSAPI authentication does not work, until daemons are restarted, or the hourly cronjob refreshes the tickets.  *We need to test this condition more deeply*.


Recompiled packages
===================

Kerberos support is limited on upstream Dovecot and Postfix packages.  
For Active Directory integration we must install more recent software versions provided 
by Morten Stevens from Fedora People (http://mstevens.fedorapeople.org/el6/):

* postfix recompiled with ``-DUSE_LDAP_SASL`` option 
* dovecot

