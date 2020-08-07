.. _email-section:

=====
Email
=====

The Email module is split into three main parts:

* SMTP server for sending and receiving [#Postfix]_
* IMAP and POP3 server to read email [#Dovecot]_, and Sieve language to organize it [#Sieve]_
* Antispam filter, antivirus and attachments blocker [#RSPAMD]_

Benefits are

* complete autonomy in electronic mail management
* avoid problems due to the Internet Service Provider
* ability to track the route of messages in order to detect errors
* optimized antivirus and antispam scan

See also the following related topics:

* How electronic mail works [#Email]_
* MX DNS record [#MXRecord]_
* Simple Mail Transfer Protocol (SMTP) [#SMTP]_
* DKIM signature [#DKIM]_

.. note::

    Since |product| 7.5.1804 new :ref:`email-section`,
    :ref:`pop3_connector-section` and :ref:`pop3_proxy-section` installations
    are based on the Rspamd filter engine. Previous |product| installations are
    automatically upgraded to Rspamd as described in :ref:`email2-section`

.. index::
   pair: email; relay
   pair: email; delivery
   pair: email; domain

.. _email_domains:

Domains
=======

|product| can handle an unlimited number of mail domains, configurable
from the :guilabel:`Email > Domains` page.  For each domain there are
two alternatives:

* *Deliver* messages to local mailboxes, according to the Maildir
  [#MailDirFormat]_ format.
* *Relay* messages to another mail server.

.. note:: If a domain is deleted, email will not be deleted;
   any message already received is preserved.

.. index::
   pair: email; always send a copy
   pair: email; hidden copy
   pair: email; bcc

|product| allows storing an :dfn:`hidden copy` of all messages
directed to a particular domain: they will be delivered to the final
recipient *and also* to a custom email address. The hidden copy is
enabled by the :guilabel:`Copy inbound messages` switch
(formerly :guilabel:`Always send a copy (Bcc)` check box).

.. warning:: On some countries, enabling the *Copy inbound messages*
             switch can be against privacy laws.

If the final recipient cannot be established (i.e. the recipient address does
not exist), the message is normally rejected. Sometimes (i.e. when a mail domain
is migrated) it could be useful to accept it and silently deliver the message to
a catch-all mailbox. This behavior can be obtained by enabling the
:guilabel:`Accept unknown recipients` option.

.. index::
   pair: email; disclaimer
   pair: email; signature
   pair: email; legal note

Append a legal notice
---------------------

.. warning::

    Since |product| 7.5.1804 this feature is shipped in a separate, optional
    package: ``nethserver-mail-disclaimer``. It is considered *deprecated*
    because the alterMIME [#alterMIME]_ project which provides the actual
    implementation is no longer developed and can stop working at any time.

If the optional ``nethserver-mail-disclaimer`` RPM was installed from the terminal,
|product| can automatically append a
legal notice to sent messages. This text is also known as "disclaimer" and
it can be used to meet some legal requirements.

To configure and enable the *disclaimer attachment*, turn on the option switch
:guilabel:`Email > Domains [List item] > Edit > Append a legal note to sent messages`.

The disclaimer text can contain Markdown [#Markdown]_ code to format the text.

Please note :dfn:`signature` and :dfn:`disclaimer` are very different concepts.

In general, the **disclaimer** is a fixed text and should be *attached* (not
added) to messages by the mail server. This technique helps in maintaining the
integrity of the message in case of digital signature.

Disclaimer example: ::

  This email and any files transmitted with it are confidential and
  intended solely for the use of the individual or entity to whom they
  are addressed.  If you have received this email in error please
  notify the system manager.  This message contains confidential
  information and is intended only for the individual named.

The **signature** should be inserted inside the message text only by the
mail client (MUA): Outlook, Thunderbird, etc.  Usually it is a
user-defined text containing information such as sender addresses and
phone numbers.

Signature example: ::

 John Smith
 President | My Mighty Company | Middle Earth
 555-555-5555 | john@mydomain.com | http://www.mydomain.com


DKIM signature
--------------

DomainKeys Identified Mail (DKIM) [#DKIM]_ provides a way to validate the
sending MTA, which adds a cryptographic signature to the outbound message MIME
headers.

To enable the DKIM signature for a mail domain, enable the :guilabel:`Signature` switch
under :guilabel:`Email > Domains > [list item] > Configure DKIM`.

The DKIM signature headers are added only to messages sent through TCP ports 587
(submission) and 465 (smtps).

To work effectively, the public DNS must be configured properly. Refer to the
instructions of your DNS provider to run the following steps:

1. Add a TXT record to your public DNS service provider with key "default._domainKey"

2. Copy and paste the given key text in the DNS record data (RDATA) section


.. index::
   pair: email; filter

.. _email_filter:

Filter
======

All transiting email messages are subjected to a list of checks that
can be selectively enabled in :guilabel:`Email > Filter` page:

* Attachments
* Antivirus
* Antispam

.. index::
   pair: email; attachment

Attachments
-----------

The system can inspect mail attachments, denying access to messages
carrying forbidden file formats. The server can check the following
attachment classes:

* :index:`executables` (eg. exe, msi)
* :index:`archives`  (eg. zip, tar.gz, docx)
* custom file format list

The system recognizes file types by looking at their contents,
regardless of the file attachment name.  Therefore it is possible that
MS Word file (docx) and OpenOffice (odt) are blocked because they
actually are also zip archives.

.. index::
   pair: email; antivirus
   see: anti-virus; antivirus

.. _anti-virus:

Antivirus
---------

The antivirus component finds email messages containing
viruses. Infected messages are discarded. The virus signature database
is updated periodically.

.. index::
   single: spam
   pair: email; antispam
   pair: spam; score
   see: anti-spam; antispam

.. _anti-spam:

Antispam
--------

The antispam component [#RSPAMD]_ analyzes emails by detecting
and classifying :dfn:`spam` [#SPAM]_ messages using heuristic
criteria, predetermined rules and statistical evaluations on the
content of messages.

The filter can also check if sender server is listed in one or more blacklists
(:index:`DNSBL` [#DNSBL]_). A score is associated to each rule.

Total spam score collected at the end of the analysis allows the server to
decide what to do with a message, according to three **thresholds** that can be
adjusted under :guilabel:`Email > Filter > Anti spam`.

1. If the spam score is above :guilabel:`Greylist threshold` the message is
   **temporarily rejected**. The :dfn:`greylisting` [#GREY]_ technique assumes
   that a spammer is in hurry and is likely to give up, whilst a
   SMTP-compliant MTA will attempt to deliver the deferred message again.

2. If the spam score is above :guilabel:`Spam threshold` the message is **marked
   as spam** by adding the special header ``X-Spam: Yes`` for specific
   treatments, then it is delivered like other messages. As an alternative, the
   :guilabel:`Add a prefix to spam messages subject` option makes the spam flag
   visible on the subject of the message, by prefixing the given string to the
   ``Subject`` header.

3. If the spam score is above :guilabel:`Deny message spam threshold` the
   message is **rejected**.

.. index::
   pair: email; spam training

Statistical filters, called Bayesian [#BAYES]_, are special rules that
evolve and quickly adapt analyzing messages marked as **spam** or
**ham**.

The statistical filters can then be trained with any IMAP client by
simply moving a message in and out of the :dfn:`Junk folder`. As a
prerequisite, the Junk folder must be enabled from the
:guilabel:`Email > Mailboxes [General settings] > Configure
[Advanced options] > Move spam to "Junk" folder` check box
(formerly :guilabel:`Email > Mailboxes > Move to
"Junk" folder"` check box).

* By *putting a message into the Junk folder*, the filters learn
  it is spam and will assign an higher score to similar messages.

* On the contrary, by *getting a message out of Junk*, the filters
  learn it is ham: next time a lower score will be assigned.

By default, all users can train the filters using this technique. If
a group called ``spamtrainers`` exists, only users in this group
will be allowed to train the filters.

The bayesian filter training applies to all users on the system, not only the user that marked an email as spam or ham.

It is important to understand how the Bayesian tests really work:

* It does not outright flag messages as spam if they contain a specific subject, or sender address. It is only collecting specific characteristics of the message.

* A message can only be flagged one time. If the same message is flagged multiple times, it will not affect anything as the dynamic tests have already been trained by that message.

* The Bayesian tests **are not active until it has received enough information. This includes a minimum of 200 spams AND 200 hams (false positives).**

  As the system receives that information, the progress of bayesian filter training
  can be monitored from the :guilabel:`Email > Filter [Statistics] > Bayes training` progress bar.

.. note:: It is a good habit to frequently check the Junk folder
          in order not to lose email wrongly recognized as spam.

.. index::
   pair: email; whitelist
   pair: email; blacklist

Rules for white and black lists
-------------------------------

If the system fails to recognize spam properly even after training,
the *whitelists* and *blacklists* can help. Those are lists of email
addresses or domains respectively always allowed and always blocked to
send or receive messages.

The section :guilabel:`Email > Filter [Rules] > Details` (formerly
:guilabel:`Rules by mail address`) allows creating three types of rules:

* :guilabel:`Allow From`: any message from specified sender is
  accepted

* :guilabel:`Allow To`: any message to the specified recipient is
  accepted

* :guilabel:`Block From`: any message from specified sender is blocked

The *Allow* rules have higher precedence over the *Block* ones. As soon as an *Allow* rule
matches, the antispam and antivirus checks are skipped, the *Block* rule is not
evaluated and the message is accepted.

.. warning::

    **Antivirus and antispam checks are skipped** if an *Allow* rule matches

It is possible to create an *Allow* or *Block* rule even for an entire
domain, not just for a single email address: you just need to specify the
domain name (e.g. ``dev.nethserver.org``).

When a second level domain domain name is specified it matches also its
subdomains. For instance ``nethserver.org`` matches ``nethserver.org`` itself,
``dev.nethserver.org``, ``demo.nethserver.org`` and so on.



.. _rspamd-web-interface-section:

Rspamd web interface
--------------------

The antispam component is implemented by Rspamd [#RSPAMD]_ which provides its
administrative web interface at ::

  https://<HOST_IP>:980/rspamd

For more information on Rspamd, please read the :ref:`rspamd-section` page.

.. only:: nscom

    .. _quarantine:

    Quarantine (beta)
    -----------------

    |product| scans all incomaing email messages before they are delivered to the user mailbox.
    The messages that are identified as spam will be sent to a specific user mailbox.
    The purpose of this feature is to verify the email before deleting it.
    If enabled, a mail notification is also sent to the postmaster (root alias) for each
    quarantined email.

    .. note::

      The quarantined messages can be accessed using a web mail or an IMAP account

    .. warning::

      The mailbox used for quarantine, must be able to accept spam.
      It should be a local shared mailbox or a user mailbox.
      If an external account is used, make sure the account exists on the remote server.
      Please make sure the quarantine mailbox has been created only for this specific purpose,
      otherwise the mailbox will be overloaded with unwanted spam.

    Quarantine is provided by an optional RPM named
    ``nethserver-mail-quarantine``. Once it has been installed from the
    terminal you must manually set its database properties.

    The properties are under the ``rspamd`` key (configuration database): ::

        rspamd=service
        ...
        QuarantineAccount=spam@domain.org
        QuarantineStatus=enabled
        SpamNotificationStatus=disabled


    * ``QuarantineAccount``: The user or the shared mailbox where to send all spam messages (spam
      check is automatically disabled on this account). You must create it
      manually. You could send it to an external mailbox  but then make sure to
      disable the spam check on the remote server

    * ``QuarantineStatus``: Enable the quarantine, spam are no more rejected:
      enabled/disabled. Disabled by default

    * ``SpamNotificationStatus``: Enable the email notification when email are
      quarantined: enabled/disabled. Disabled by default

    For example, the following commands enable the quarantine and the mail
    notification to root: ::

      config setprop rspamd QuarantineAccount spam@domain.org QuarantineStatus enabled SpamNotificationStatus enabled
      signal-event nethserver-mail-quarantine-save


.. _email_mailboxes:

Mailboxes
=========

.. index::
    pair: user; mailbox

Each user has a personal mailbox and any user name in the form
*<username>@<domain>* is also a valid email address to deliver messages into it.

The list of mailboxes is shown by the :guilabel:`Email > Mailboxes` page. There
are three types of mailboxes: Users, Groups and Public mailboxes.

Users mailboxes
---------------

The :guilabel:`Edit` button allows disabling the :guilabel:`Access to
email services` (IMAP, POP3, SMTP/AUTH) for a specific user.  Messages delivered
to that user's mailbox can be forwarded to multiple external email addresses.

.. warning::

    If the system is bound to a :ref:`remote account provider
    <account-providers>` and a user account is remotely deleted, the associated
    mailbox must be erased manually. The file system path prefix is
    :file:`/var/lib/nethserver/vmail/`.

Groups mailboxes
----------------

The *automatic aliases for groups mailboxes* are initially disabled. If enabled,
addresses like *<groupname>@<domain>* become valid email addresses. A specific group address
can be disabled and enabled again in a later stage, once Groups mailboxes are enabled.
To disable the automatic aliases globally, refer to :ref:`email_mailboxes_settings`.

A group mailbox has no disk space for it. When a message is sent to a group mailbox,
a copy of it is delivered to the group members, according to their delivery and forward
preferences.

Public mailboxes
----------------

.. index::
    pair: shared; mailbox

.. note::

   In the old Server Manager the :guilabel:`Shared mailboxes` label was used
   in place of :guilabel:`Public mailboxes`.

.. index::
    pair: public; mailbox

Public mailboxes can be shared among groups of users.  The :guilabel:`Email >
Mailboxes > Public mailboxes` section allows creating a new public mailbox
and defining one or more owning groups. Public mailboxes can also be created by
any IMAP client supporting IMAP ACL protocol extension (RFC 4314).

.. _email_mailboxes_settings:

General settings
----------------

The :guilabel:`Email > Mailboxes [General settings] > Configure` page controls what protocols are
available to access the user's mailbox:

* IMAP [#IMAP]_ (recommended)
* POP3 [#POP3]_ (obsolete)

For security reasons, all protocols require STARTTLS encryption by
default.  The :guilabel:`Allow unencrypted connections` check box,
disables this important requirement, and allows passing clear-text passwords and
mail contents over the network.

.. warning:: Do not allow unencrypted connections on production
             environments!

.. index::
   triple: email; custom; quota

From the same page, the :guilabel:`Quota limit` for each mailbox can be
limited to a default quota.  If the general mailbox quota is enabled, the
:guilabel:`Email > Mailboxes` list summarizes the quota usage for
each user.  This summary is updated when a user logs in or a message is
delivered. The quota can be customized for a specific user in :guilabel:`Email
> Mailboxes [users item] > Edit > Custom mailbox quota`.

.. index::
   pair: email; spam retention
   triple: email; custom; spam retention

Messages marked as **spam** (see :ref:`email_filter`) can be automatically
moved into the :dfn:`Junk` folder by enabling the option
:guilabel:`Move spam to "Junk" folder`. Spam messages are expunged
automatically after the :guilabel:`Keep spam for` period has elapsed.  The
spam retention period can be customized for a specific user in
:guilabel:`Email > Mailboxes [users item] > Edit > Custom spam retention`.

.. index::
   pair: email; master user

The ``root`` user can impersonate another user, gaining full rights
to any mailbox contents and folder permissions.  The
:guilabel:`Root can log in as another user` option controls this
empowerment, known also as *master user* in Dovecot [#Dovecot]_.

When :guilabel:`Root can log in as another user` is enabled, the following
credentials are accepted by the IMAP server:

* user name with ``*root`` suffix appended
* root's password

For instance, to access as ``john`` with root password ``secr3t``,
use the following credentials:

* user name: ``john*root``
* password: ``secr3t``

Additional options:

* If *Groups mailboxes* were enabled in :guilabel:`Email > Mailboxes > Groups`,
  unselect the :guilabel:`Automatic alias for groups` check box to disable them again.

* It is possible to record the IMAP actions by enabling :guilabel:`Log IMAP actions`.
  See also :ref:`email_log`.

.. _email_outlook_deleted:

* Unlike almost any IMAP client, Outlook does not move deleted messages
  to the trash folder, but simply marks them as "deleted".

  It is possibile to automatically move messages inside the trash folder,
  by enabling :guilabel:`Move deleted email to trash (Outlook)`.

  You should also change Outlook configuration to hide deleted messages from the inbox folder.
  This configuration is available in the Outlook options menu.

* :guilabel:`Max user connections per IP` changes the limit of connections for a user coming from
  the same IP address. This limit could be increased if messages like
  *Maximum number of connections* appear in the log files (see :ref:`email_log`).


*Shared seen* configuration
---------------------------

Users could share their mailbox (or some parts of it, folders) with selected accounts on the system.
Everyone who is given access to a shared mailbox can read or delete messages according to permissions
granted by the mailbox owner.

An IMAP flag named ``/Seen`` is used to mark if a message has been read or not. In a shared mailbox,
each user has their copy of the messages they have read, but sometimes a team sharing a mailbox
could prefer to know if a mail has already been read by someone else.
To enable sharing of the ``/Seen`` flag for all shared mailboxes use the following commands: ::

    config setprop dovecot SharedSeen enabled
    signal-event nethserver-mail-server-save

Please note that changing the ``SharedSeen`` status resets the ``/Seen`` flag for all users on all mailboxes.

Public folders are created by the administrator and are usually visible to all users (or large groups).
The ``/Seen`` flag is kept for each user and it cannot be shared.


.. index:: email address, pseudonym

.. _email_addresses:

Addresses
=========

In addition to the Users, Groups and Public mailboxes addresses, described in the
previous section, the system enables the creation of an unlimited number of email
addresses, from the :guilabel:`Email > Addresses` page. Each
:dfn:`mail address` is associated with one or more destinations. A
:dfn:`destination` can be of the following types:

* user mailbox,
* groups mailbox,
* public mailbox,
* external email address.

A mail address can be bound to any mail domain or be specific to one mail domain.
For example:

* First domain: ``mydomain.net``
* Second domain: ``example.com``
* Email address *info* bound to any domain: ``info@mydomain.net``,
  ``info@example.com``
* Email address *goofy* specific to one domain: ``goofy@example.com``

.. index::
   pair: email; local network only
   pair: email; internal visibility
   triple: email; private; internal

Sometimes a company forbids communications from outside the organization
using personal email addresses. The :guilabel:`Internal` check box
(formerly :guilabel:`Local network only`) and the :guilabel:`Make internal`
and :guilabel:`Make public` action buttons block the possibility of an address
to receive messages from the outside.  Still an *internal* address can be used to
exchange messages with other accounts of the system.

.. _email-connectors:

Connectors
==========

The :guilabel:`Email > Connectors` page is described in :ref:`pop3_connector-section`.

.. _email_imap_synchronization:

Synchronization
===============

The :guilabel:`Email > Synchronization` page  is based on an IMAP transfer tool called Imapsync.
The purpose is to migrate email messages from a remote IMAP account to a
local one.

The migration is recursive and incremental and
can be repeated as many times as needed. The emails will be copied locally
if they do not exist on the local server.

The system administrator of the local |product| does not need to know the
password of the local user. However, the administrator
has to know the password of the remote IMAP account, unless the IMAP admin
authentication is implemented also for the remote email server.

If the remote IMAP server is also a |product|,
the IMAP admin user is ``vmail`` and its password can be read from
:file:`/var/lib/nethserver/secrets/vmail`.
The username with a ``*vmail`` suffix (e.g. ``username@domain.com*vmail``) and the ``vmail`` password has to be set in the IMAP synchronization panel.

.. note::

    List of `IMAP servers with admin authentication <https://imapsync.lamiral.info/FAQ.d/FAQ.Admin_Authentication.txt>`_ in Imapsync documentation

.. index::
   pair: email; queue

.. _email-queue:

Queue
=====

The :guilabel:`Email > Queue` page lists the messages that are waiting to
be relayed in the SMTP mail queue. In normal conditions, this queue
should be empty or contain just a few messages.

The :guilabel:`Email > Queue [Charts] > Show charts` link shows a real-time
chart of the mail queue status in the last minutes, updated as the page is left opened.
The chart shows the number of message in the queue and the total queue size in kilo bytes.

While messages are in the queue, the administrator can request an
immediate message relay attempt, by pressing the button
:guilabel:`Resend all` (formerly :guilabel:`Attempt to send`),
or empty the queue with the :guilabel:`Delete all` button.

It is also possible to selectively :guilabel:`Resend` or :guilabel:`Delete` a queued message,
from the action buttons of :guilabel:`Email > Queue [List]` items.

.. index::
   pair: email; smarthost
   pair: email; relay

.. _email-relay:

Relay
=====

The :guilabel:`Email > Relay` page configures how messages are accepted
and routed from the |product| SMTP server to other SMTP servers.

.. _email_policies:

Special SMTP access policies
----------------------------

The default |product| configuration requires that all clients use the
submission port (587) with encryption and authentication enabled to
send mail through the SMTP server. See also :ref:`email_clients`.

To ease the configuration of legacy environments, the
:guilabel:`Email > Relay [Configuration] > Details` section (formerly the :guilabel:`Email
> SMTP access` page) allows making some exceptions on the default SMTP
access policy.

.. warning:: Do not change the default policy on new environments!

For instance, there are some devices (printers, scanners, ...) that do
not support SMTP authentication, encryption or port settings. Those
can be enabled to send email messages by listing their IP address in
:guilabel:`Allow relay from IP addresses` text area.

.. warning::

  The listed IP addresses are excluded from all mail filtering checks: use
  this feature only as a last resort

Moreover, in the same section there are further options:

* The :guilabel:`Allow relay from trusted networks` option allows any
  client in the trusted networks to send email messages without any
  restriction.

* The :guilabel:`Enable authentication on port 25` option allows
  authenticated SMTP clients to send email messages also on port 25.

* By default an authenticated SMTP client has no particular restrictions on
  setting the SMTP sender address.

  To avoid the unauthorized use of email addresses and the sender address
  spoofing, enable the :guilabel:`Enforce sender/login match` option.

  If enabled, only addresses associated to the current SMTP login are allowed.

.. index::
   pair: email; HELO
   alias: HELO; EHLO

.. _email_helo:

Custom HELO
-----------

The first step of an SMTP session is the exchange of :dfn:`HELO`
command (or :dfn:`EHLO`).  This command takes a valid server name as
required parameter (RFC 1123).

|product| and other mail servers try to reduce spam by not accepting
HELO domains that are not registered on a public DNS.

When talking to another mail server, |product| uses its full host name
(FQDN) as the value for the HELO command.  If the FQDN is not
registered in the public DNS, the HELO can be changed in the
:guilabel:`Custom HELO` text field.

This configuration is also valuable if the mail server is using a free
dynamic DNS service.

.. _email-multi-relay:

Relay hosts
-----------

The :guilabel:`Email > Relay` page allows to describe the route of an email message, by
sending it through an external relay host with specific port, authentication,
and TLS settings.

Create a relay host description under :guilabel:`Email > Relay > Create relay
host`.

The relay host is identified by **the SMTP sender address**. It is possible to match
the full sender address or only the domain part of it.

.. _smarthost-configuration:

Default relay host settings
---------------------------

If the sender address does not match the relay rules described in the above section it
is possible (though not recommended) to configure a default relay host instead of
relying on the standard SMTP relay rules.

.. note:: Sending through a *smarthost* is generally not recommended.
          It might be used only if the server is temporarily
          blacklisted [#DNSBL]_, or normal SMTP access is restricted
          by the ISP.

The :guilabel:`System > Settings > Smart host` section, configures the outgoing
messages to be directed through a special SMTP server, technically
named :dfn:`smarthost`.  A smarthost accepts to relay messages under
some restrictions. It could check:

* the client IP address,
* the client SMTP AUTH credentials.

Refer also to :ref:`smart-host` for more information.

.. _email_messages:

.. _email-settings:

Settings
========

.. index::
   pair: email; size
   pair: email; retries
   pair: email; message queue

From the :guilabel:`Email > Settings` page, the :guilabel:`Maximum message size`
(formerly :guilabel:`Queue message max size`) slider sets the maximum size of
messages traversing the system. If this limit is exceeded, a message cannot enter the
system at all and is rejected.

Once a message enters |product|, it is persisted to a :dfn:`queue`,
waiting for final delivery or relay. When |product| relays a message
to a remote server, errors may occur. For instance,

* the network connection fails, or
* the other server is down or is overloaded.

Those and other errors are *temporary*: in such cases, |product|
attempts to reconnect the remote host at regular intervals until a
limit is reached. The :guilabel:`Message queue lifetime` (formerly
:guilabel:`Queue message lifetime`) slider
changes this limit.  By default it is set to *4 days*.

.. index::
   pair: email; always send a copy
   pair: email; hidden copy
   pair: email; bcc

To keep an hidden copy of any message traversing the mail server,
enable the :guilabel:`Forward a copy of all messages` (formerly
:guilabel:`Always send a copy (Bcc)` check box). This feature
is different from the same check box under :guilabel:`Email > Domains` as
it does not differentiate between mail domains and catches also any
outgoing message.

.. warning:: On some countries, enabling the *Always send a copy
             (Bcc)* can be against privacy laws.


.. _email_log:

Logs
====

Every mail server operation is saved in the following log files:

* :file:`/var/log/maillog` registers all mail transactions
* :file:`/var/log/imap` contains users login and logout operations,
  plus the IMAP actions, if enabled in :ref:`email_mailboxes_settings`

A transaction recorded in the :file:`maillog` file usually involves
different components of the mail server.  Each line contains
respectively

* the timestamp,
* the host name,
* the component name, and the process-id of the component instance
* a text message detailing the operation

|product| configuration uses Rspamd as milter. It runs an Rspamd proxy worker in
"self-scan" mode [#SELFSCAN]_.

The key to track the whole SMTP transaction, including Rspamd decisions is the
message ID header, or the Postfix Queue ID (QID). Both are available from the
message source. The ``Message-ID`` header is generated by the sender, whilst the
QID is assigned by the receiving MTA. For instance ::

  Received: from my.example.com (my.example.com [10.154.200.17])
        by mail.mynethserver.org (Postfix) with ESMTP id A785B308622AB
        for <jsmith@example.com>; Tue, 15 May 2018 02:05:02 +0200 (CEST)
  ...
  Message-ID: <5afa242e.hP5p/mry+fTNNjms%no-reply@example.com>
  User-Agent: Heirloom mailx 12.5 7/5/10

Here ``A785B308622AB`` is the QID, whilst
``5afa242e.hP5p/mry+fTNNjms%no-reply@example.com`` is the Message ID.

Both strings can be used with the ``grep`` command to find relevant log lines in
``/var/log/maillog*`` (note the ending "*" to search also in archived log
files). For instance ::

    grep -F 'A785B308622AB' /var/log/maillog*

Yields ::

  /var/log/maillog:May 15 02:05:02 mail postfix/smtpd[25846]: A785B308622AB: client=my.example.com[10.154.200.17]
  /var/log/maillog:May 15 02:05:02 mail postfix/cleanup[25849]: A785B308622AB: message-id=<5afa242e.hP5p/mry+fTNNjms%no-reply@example.com>
  /var/log/maillog:May 15 02:05:02 mail rspamd[27538]: <8ae27d>; proxy; rspamd_message_parse: loaded message; id: <5afa242e.hP5p/mry+fTNNjms%no-reply@example.com>; queue-id: <A785B308622AB>; size: 2348; checksum: <b1035f4fb07162ba88053d9e38df9c93>
  /var/log/maillog:May 15 02:05:03 mail rspamd[27538]: <8ae27d>; proxy; rspamd_task_write_log: id: <5afa242e.hP5p/mry+fTNNjms%no-reply@example.com>, qid: <A785B308622AB>, ip: 10.154.200.17, from: <no-reply@example.com>, (default: F (no action): [-0.64/20.00] [BAYES_HAM(-3.00){100.00%;},AUTH_NA(1.00){},MID_CONTAINS_FROM(1.00){},MX_INVALID(0.50){},MIME_GOOD(-0.10){text/plain;},IP_SCORE(-0.04){ip: (0.22), ipnet: 10.154.192.0/20(0.18), asn: 14061(0.23), country: US(-0.81);},ASN(0.00){asn:14061, ipnet:10.154.192.0/20, country:US;},DMARC_NA(0.00){example.com;},FROM_EQ_ENVFROM(0.00){},FROM_NO_DN(0.00){},NEURAL_HAM(-0.00){-0.656;0;},RCPT_COUNT_ONE(0.00){1;},RCVD_COUNT_TWO(0.00){2;},RCVD_NO_TLS_LAST(0.00){},R_DKIM_NA(0.00){},R_SPF_NA(0.00){},TO_DN_NONE(0.00){},TO_DOM_EQ_FROM_DOM(0.00){},TO_MATCH_ENVRCPT_ALL(0.00){}]), len: 2348, time: 750.636ms real, 5.680ms virtual, dns req: 47, digest: <b1035f4fb07162ba88053d9e38df9c93>, rcpts: <jsmith@example.com>, mime_rcpts: <jsmith@example.com>
  /var/log/maillog:May 15 02:05:03 mail postfix/qmgr[27757]: A785B308622AB: from=<no-reply@example.com>, size=2597, nrcpt=1 (queue active)
  /var/log/maillog:May 15 02:05:03 mail postfix/lmtp[25854]: A785B308622AB: to=<vmail+jsmith@mail.mynethserver.org>, orig_to=<jsmith@example.com>, relay=mail.mynethserver.org[/var/run/dovecot/lmtp], delay=0.82, delays=0.8/0.01/0.01/0.01, dsn=2.0.0, status=sent (250 2.0.0 <vmail+jsmith@mail.mynethserver.org> gK8pHS8k+lr/ZAAAJc5BcA Saved)
  /var/log/maillog:May 15 02:05:03 mail postfix/qmgr[27757]: A785B308622AB: removed


.. _email_clients:

Client configuration
====================

The server supports standard-compliant email clients using the
following IANA ports:

* imap/143
* pop3/110
* smtp/587
* sieve/4190

Authentication requires the STARTTLS command and supports the
following variants:

* LOGIN
* PLAIN
* GSSAPI (only if |product| is bound to Samba/Microsoft Active Directory)

Also the following SSL-enabled ports are available for legacy software
that still does not support STARTTLS:

* imaps/993
* pop3s/995
* smtps/465

.. warning::

    The standard SMTP port 25 is reserved for mail transfers between MTA
    servers. Mail user agents (MUA) must use the submission port.

.. rubric:: References

.. [#Postfix] Postfix mail server http://www.postfix.org/
.. [#Dovecot] Dovecot Secure IMAP server http://www.dovecot.org/
.. [#Sieve] Sieve mail filtering language https://en.wikipedia.org/wiki/Sieve_(mail_filtering_language)
.. [#RSPAMD]
    Rspamd -- Fast, free and open-source spam filtering system.
    https://rspamd.com/
.. [#Email] Email, https://en.wikipedia.org/wiki/Email
.. [#MXRecord] The MX DNS record, https://en.wikipedia.org/wiki/MX_record
.. [#SMTP] SMTP, https://en.wikipedia.org/wiki/Simple_Mail_Transfer_Protocol
.. [#DKIM]
    Domain Keys Identified Mail (DKIM) is an email authentication method
    designed to detect email spoofing -- `Wikipedia
    <https://en.wikipedia.org/wiki/DomainKeys_Identified_Mail>`_
.. [#MailDirFormat] The Maildir format, https://en.wikipedia.org/wiki/Maildir
.. [#alterMIME]
    alterMIME is a small program which is used to alter your mime-encoded mailpack --
    https://pldaniels.com/altermime/
.. [#Markdown] The Markdown plain text formatting syntax, https://en.wikipedia.org/wiki/Markdown
.. [#IMAP] IMAP https://en.wikipedia.org/wiki/Internet_Message_Access_Protocol
.. [#POP3] POP3 https://en.wikipedia.org/wiki/Post_Office_Protocol
.. [#DNSBL] DNSBL https://en.wikipedia.org/wiki/DNSBL
.. [#SPAM] SPAM https://en.wikipedia.org/wiki/Spamming
.. [#GREY]
    Greylisting is a method of defending e-mail users against spam. A mail
    transfer agent (MTA) using greylisting will "temporarily reject" any email from
    a sender it does not recognize -- `Wikipedia
    <https://en.wikipedia.org/wiki/Greylisting>`_
.. [#BAYES] Bayesian filtering https://en.wikipedia.org/wiki/Naive_Bayes_spam_filtering
.. [#MailComponents] The wondrous Ways of an Email https://workaround.org/ispmail/wheezybig-picture/
.. [#SELFSCAN] https://rspamd.com/doc/workers/rspamd_proxy.html
