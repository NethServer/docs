===============
nethserver-mail
===============

.. warning::

            RPMs packages built from this repository are temporarily named with
            the ``nethserver-mail2-*`` prefix. See `Upgrade to rspamd`_ section
            for more information

Mail system implementation based on Postfix, Dovecot, Rspamd, OpenDKIM. The mail
system configuration is splitted in the following RPMs:

- nethserver-mail-common
- nethserver-mail-disclaimer
- nethserver-mail-filter
- nethserver-mail-server
- nethserver-mail-ipaccess
- nethserver-mail-getmail
- nethserver-mail-p3scan

mail-common
-----------

* Common infrastructure for ``nethserver-mail-server and nethserver-mail-filter``, Postfix-based.
* Relay
* Queue parameters: age + message size
* MX record configuration

mail-disclaimer
---------------

* Attach disclaimer/legal notice to outbound messages for certain domains
* Runs ``altermime`` with Postfix ``content_filter`` option

mail-filter
-----------

* Based on `Rspamd`_
* Anti-spam with DNSBL (see: `nethserver-unbound`_)
* Anti-virus
* Attachment block
* Real-time Blackhole List (RBL) (default disabled)
* Sender Policy Framework (SPF) (default disabled)
* Customized spam threshold 
* Sender WBL, Recipient whitelist 

.. _Rspamd: https://rspamd.com
.. _nethserver-unbound: http://github.com/NethServer/nethserver-unbound

mail-server
-----------

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

mail-ipaccess
-------------

See `IP-based IMAP access restriction`_.


mail-getmail
------------

The package configures getmail using cron.

For each enabled account the system:

* generates a ``.cfg`` file inside the ``/var/lib/getmail`` directory from the template ``/etc/e-smith/templates/getmailrc``
* adds a line inside the ``/etc/cron.d/getmail``, all getmail instances use a non-blocking flock
* delivers the messages using dovecot-lda

All operations are logged in ``/var/log/maillog``. 

If a virus is found inside a received mail, the message is dropped.

The evidence  of log in ``/var/log/maillog``: ::

  Feb 14 18:19:10 vm5 clamd[1791]: instream(local): Eicar-Test-Signature FOUND


mail-p3scan
-----------

This package configures p3scan, full-transparent POP3 proxy-server for email
clients.

* POP3 and POP3s proxy
* Anti-virus and anti-spam checks

Database format
---------------

configuration
^^^^^^^^^^^^^

Postfix example: ::

 postfix=service
    ...
    AccessPolicies=
    AlwaysBccStatus=disabled
    AlwaysBccAddress=
    MessageQueueLifetime=4
    MessageSizeMax=20000000
    MessageSizeMin=1048576
    ContentInspectionType=default
    ConnectionsLimit=
    ConnectionsLimitPerIp=
    SystemUserRecipientStatus=disabled

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
        RestrictedAccessGroup=


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
* ``RestrictedAccessGroup`` The value is a long group name, like ``domain
  admins@mydomain.tld``. Members of the given group can login to dovecot
  services only from trusted networks. Install the
  ``nethserver-mail-server-ipaccess`` package to enable this feature.

p3scan example: ::

  p3scan=service
    SSLScan=enabled
    SpamScan=enabled
    TCPPort=8110
    Template=/etc/p3scan/p3scan-en.mail
    VirusScan=enabled
    access=
    status=enabled


rspamd example: ::
    
    rspamd=service
        BlockAttachmentClassList=Exec
        BlockAttachmentCustomList=doc,odt
        BlockAttachmentCustomStatus=disabled
        BlockAttachmentStatus=enabled
        Password=uO9QjlnRCDsT0ZCD
        RecipientWhiteList=
        SenderBlackList=
        SenderWhiteList=
        SpamCheckStatus=enabled
        SpamDsnLevel=20
        SpamGreyLevel=4
        SpamKillLevel=15
        SpamSubjectPrefixStatus=disabled
        SpamSubjectPrefixString=***SPAM***
        SpamTag2Level=6
        SpamTagLevel=2
        VirusAction=reject
        VirusCheckStatus=enabled
        VirusScanOnlyAttachment=false
        VirusScanSize=20000000
        status=enabled


domains
^^^^^^^

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
  
accounts
^^^^^^^^

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

getmail
^^^^^^^

All records of type ``getmail`` are saved inside the ``getmail`` database.

Properties:

* The key is the mail account to be downloaded
* ``status``: can be ``enabled`` or ``disabled``, default is ``enabled``
* ``Account``: local user where messages will be delivered. Should be in the form *user@domain*
* ``Server``: server of the mail account
* ``Username``: user name of the mail account
* ``Password``: password of the mail account
* ``Delete``: numbers of days after downloaded messages will be deleted, ``-1`` means never, ``0`` means immediately
* ``Time``: integer number rappresenting the minutes between each check, valid valued are between 1 and 60
* ``FilterCheck``: if ``enabled``, check downloaded messages for viruses and spam using ``rspamc`` classifier
* ``Retriever``: can be any getmail retriever, see `Getmail official doc <http://pyropus.ca/software/getmail/documentation.html>`_
    Retrievers available in the web interface:

    * ``SimplePOP3Retriever``
    * ``SimplePOP3SSLRetriever``
    * ``SimpleIMAPRetriever``
    * ``SimpleIMAPSSLRetriever`` 

Example: ::

 db getmail set test@neth.eu getmail Account pippo@neth.eu status enabled Password Nethesis,1234 Server localhost Username test@neth.eu Retriever SimplePOP3Retriever Delete enabled Time 30 VirusCheck enabled SpamCheck enabled


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


IP-based IMAP access restriction
--------------------------------

This feature allows to restrict IMAP access for a specific group.
Members of the given group have IMAP access restricted to trusted networks.

1. Install ``nethserver-mail2-ipaccess`` package ::

     yum install nethserver-mail2-ipaccess

2. Set the limited group, remember to use the full group name: ``<group>@<domain>`` ::

     config setprop dovecot RestrictedAccessGroup <group>@<domain>

   Example for group ``collaborators@nethserver.org``: ::

     config setprop dovecot RestrictedAccessGroup collaborators@nethserver.org

3. Apply the configuration ::

     signal-event nethserver-mail-server-save

Syntax of ``/etc/dovecot/ipaccess.conf``
----------------------------------------

The ``dovecot-postlogin`` script enforces an IP-based access policy to dovecot
services when the file :file:``/etc/dovecot/ipaccess.conf`` exists and is readable.

The file is composed by comments and records. Comments are line starting with ``#``,
whilst records have the following syntax: ::

    <long group name> = <cidr list>

A *long group name* is the group name with domain suffix, like ``domain
admins@mydomain.tld``.

The *cidr list* is a comma-separated list of IP and network addresses in CIDR
format, like ``127.0.0.1, 192.168.1.0/24, 10.1.1.2``. The binary conversion is
implemented by the ``NetAddr::IP`` Perl module. See ``perldoc NetAddr::IP`` for
details.

Access the rspamd UI
--------------------

The rspamd UI is available from the same httpd instance of Server Manager: ::
    
    https://<IP>:980/rspamd

Access is granted to any account defined in
``/etc/httpd/admin-conf/rspamd.secret``. By default a ``rspamd`` login is
created automatically. Its password is available with the following command: ::
    
    config getprop rspamd Password

Additional accounts can be created with the following command: ::
    
    /usr/bin/htpasswd -b -m /etc/httpd/admin-conf/rspamd.secret username S3cr3t

If an account provider is configured, the default access policy to rspamd UI is
granting access also to ``admin`` user and members of the ``domain admins`` group.
Type ``config show admins`` for details.

Upgrade to rspamd
-----------------

If something is wrong with ``rspamd``, please report the issue on
`community.nethserver.org <https://community.nethserver.org>`_.

To switch an old mail server with ``amavisd-new`` filter engine to ``rspamd``
and run the upgrade commands reported on the following sections. It is possible
to revert the upgrade too.

From Email module
^^^^^^^^^^^^^^^^^

Upgrade: ::

    yum swap \
        -- remove nethserver-mail-{common,disclaimer,filter,server} \
        -- install nethserver-mail2-{common,disclaimer,filter,server}

Revert upgrade: ::

    yum swap \
        -- install nethserver-mail-{common,disclaimer,filter,server} \
        -- remove nethserver-mail2-{common,disclaimer,filter,server}

From SMTP proxy module
^^^^^^^^^^^^^^^^^^^^^^

Upgrade: ::

    yum swap \
        -- remove nethserver-mail-{common,disclaimer,filter} \
        -- install nethserver-mail2-{common,disclaimer,filter}

Revert upgrade: ::

    yum swap \
        -- install nethserver-mail-{common,disclaimer,filter} \
        -- remove nethserver-mail2-{common,disclaimer,filter}

From POP3 connector module
^^^^^^^^^^^^^^^^^^^^^^^^^^

.. warning:: 
    
    Please note, on upgrade to mail2 old ``SpamCheck`` and ``VirusCheck`` props
    values are ignored. The default behavior of mail2 is performing anti-spam
    and anti-virus checks

Upgrade: ::

    yum swap \
        -- remove nethserver-mail-{common,disclaimer,filter,server} nethserver-getmail nethserver-spamd \
        -- install nethserver-mail2-{common,disclaimer,filter,server,getmail}

Revert upgrade: ::

    yum swap \
        -- install nethserver-mail-{common,disclaimer,filter,server} nethserver-getmail \
        -- remove nethserver-mail2-{common,disclaimer,filter,server,getmail}

From POP3 proxy module
^^^^^^^^^^^^^^^^^^^^^^

Upgrade: ::

    yum swap \
        -- remove nethserver-mail-{common,disclaimer,filter} nethserver-p3scan nethserver-spamd \
        -- install nethserver-mail2-{common,disclaimer,filter,p3scan}

Revert upgrade: ::

    yum swap \
        -- install nethserver-mail-{common,disclaimer,filter} nethserver-p3scan nethserver-spamd \
        -- remove nethserver-mail2-{common,disclaimer,filter,p3scan}
