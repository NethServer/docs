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
      MxRecordStatus=enabled
      SystemUserRecipientStatus=disabled

* ``MxRecordStatus {enabled,disabled}`` Push smtp, imap, pop, pop3 into /etc/hosts. They masquerade DNS A records in the LAN.
* ``SystemUserRecipientStatus {enabled,disabled}`` ``enabled``,
  accept from any network the recipient addresses formed by user
  account names and domain part ``localhost``,
  ``localhost.<domainname>`` and FQDN hostname.

Dovecot example: ::

    dovecot=service
        ...
        AdminIsMaster=disabled
        DeletedToTrash=disabled
        FtsLuceneStatus=enabled
        ImapStatus=enabled
        LmtpInetListenerStatus=disabled
        LogActions=disabled
        MaxProcesses=400
        MaxUserConnectionsPerIp=12
        PopStatus=enabled
        QuotaDefaultSize=20
        QuotaStatus=disabled
        SharedMailboxesStatus=enabled
        SpamFolder=Junk
        SpamRetentionTime=15d
        TlsSecurity=required


Properties:

* ``AdminIsMaster {enabled,disabled}`` allow root user to impersonate other users
* ``DeletedToTrash {enabled,disabled}`` deletedtotrash plugin
* ``FtsLuceneStatus {enabled,disabled}`` lucene indexed search plugin
* ``ImapStatus {enabled,disabled}`` IMAP protocol switch
* ``LmtpInetListenerStatus {enabled,disabled}`` open a TCP socket for LMTP protocol
* ``LogActions {enabled,disabled}`` IMAP actions logging plugin
* ``MaxProcesses N`` maximum number of worker processes spawned by dovecot. A single user session usually requires multiple processes.
* ``MaxUserConnectionsPerIp N`` maximum TCP connections for one user behind the same IP
* ``PopStatus {enabled,disabled}`` POP3 protocol switch
* ``QuotaDefaultSize N`` Default user quota size (1 unit is 10MB)
* ``QuotaStatus {enabled,disabled}`` General user mail quota switch
* ``SharedMailboxesStatus {disabled,enabled}`` Control the "Shared" IMAP namespace for per-user folder sharing
* ``SpamFolder FolderName`` Deliver spam tagged messages to the given folder (applied to all users)
* ``SpamRetentionTime Nd`` Expunge messages in SpamFolder if older than the given time span. "d" is for days.
* ``TlsSecurity {optional,required}`` 
  controls dovecot ``disable_plaintext_auth`` parameter: if set to ``required`` clear-text authentication methods are disabled, while ``optional`` enables them.



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

Mail quota
----------

The default mail quota is configured in ``dovecot.conf``. Custom user mail quota
is set by the ``dovecot-postlogin`` script, by reading
``/etc/dovecot/user-quota`` (which is a template). If a custom mail quota is set
the UI interface does not show the updated value until the user performs an IMAP
login.

Disabled users
--------------

By default all system users are also Dovecot users. To disable a user we
configure a blacklist in ``dovecot.conf``: ``/etc/dovecot/deny.passwd``.

As Dovecot is configured as authentication backend for Postfix, a disabled user
loses also SMTP AUTH access.


Testing Dovecot with Mutt
-------------------------

Read admin's mail with Mutt IMAP client.
Quickstart: ::

  yum install mutt
  cat - <<EOF > ~/.muttrc 
  set spoolfile="imaps://root@localhost/"
  set folder=""
  EOF
  mutt

See: http://dev.mutt.org/doc/manual.html

When mutt starts always asks for the ``root`` password.
To avoid typing the password again and again write it in ``.muttrc``: ::

  set spoolfile="imaps://root:PASSWORD@localhost/"
  set folder=""

``PASSWORD`` must be URL-encoded. For instance the slash character ``/`` is encoded as ``%2f``.

Set special ACL on mailboxes
----------------------------

The ``nethserver-mail-shrmbx-modify`` action applies some predefined ACL 
settings to shared mailboxes (type the mailbox name twice: the action performs also rename): ::

   /etc/e-smith/events/actions/nethserver-mail-shrmbx-modify EVENT OLDNAME NEWNAME ID PERM [ID PERM ...]

For instance, let's grant full "admin" permissions to group "administrators": ::

   /etc/e-smith/events/actions/nethserver-mail-shrmbx-modify ev 'Public folder1' 'Public Folder One' group=administrators@$(hostname -d) ADMIN

You can also use ``doveadm`` to set special ACL on a shared mailbox: ::

  doveadm acl set -u <user> <shared_mailbox> <subject> <flags>

Example: allow insert and expunge to user goofy on public mailbox testshare (domain of the machine is local.nethserver.org): ::

  doveadm acl set -u goofy@local.nethserver.org Public/testshare "user=goofy@local.nethserver.org" insert expunge

