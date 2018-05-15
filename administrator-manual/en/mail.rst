.. _email-section:

=====
Email
=====

The Email module is split into three main parts:

* SMTP server for sending and receiving [#Postfix]_
* IMAP and POP3 server to read email [#Dovecot]_, and Sieve language to organize it [#Sieve]_
* Anti-spam filter, anti-virus and attachments blocker [#RSPAMD]_

Benefits are

* complete autonomy in electronic mail management
* avoid problems due to the Internet Service Provider
* ability to track the route of messages in order to detect errors
* optimized anti-virus and anti-spam scan

See also the following related topics:

* How electronic mail works [#Email]_
* MX DNS record [#MXRecord]_
* Simple Mail Transfer Protocol (SMTP) [#SMTP]_

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
enabled by the :guilabel:`Always send a copy (Bcc)` check box.

.. warning:: On some countries, enabling the *Always send a copy
             (Bcc)* can be against privacy laws.

If the final recipient cannot be established (i.e. the recipient address does
not exist), the message is normally rejected. Sometimes (i.e. when a mail domain
is migrated) it could be useful to accept it and silently deliver the message to
a catch-all mailbox. This behavior can be obtained by enabling the
:guilabel:`Accept unknown recipients` option.

.. index::
   pair: email; disclaimer
   pair: email; signature
   pair: email; legal note

|product| can automatically :guilabel:`append a legal notice to sent
messages`. This text is called :dfn:`disclaimer` and it can be used to
meet some legal requirements.  Please note :dfn:`signature` and
disclaimer are very different concepts.

The signature should be inserted inside the message text only by the
mail client (MUA): Outlook, Thunderbird, etc.  Usually it is a
user-defined text containing information such as sender addresses and
phone numbers.

Signature example: ::

 John Smith
 President | My Mighty Company | Middle Earth
 555-555-5555 | john@mydomain.com | http://www.mydomain.com

The "disclaimer" is a fixed text and can only be *attached* (not
added) to messages by the mail server.

This technique allows maintaining the integrity of the message in case
of digital signature.

Disclaimer example: ::

  This email and any files transmitted with it are confidential and
  intended solely for the use of the individual or entity to whom they
  are addressed.  If you have received this email in error please
  notify the system manager.  This message contains confidential
  information and is intended only for the individual named.

The disclaimer text can contain Markdown [#Markdown]_ code to format the text.

.. index:: email address, pseudonym

.. _email_addresses:

Email addresses
===============

.. index::
    pair: user; mailbox

Each user has a personal :dfn:`mailbox` and any user name in the form
*<username>@<domain>* is also a valid email address to deliver messages into it.

The list of mailboxes is shown by the :guilabel:`Email addresses > User
mailboxes` page. The :guilabel:`Edit` button allows disabling the :guilabel:`Access to
email services` (IMAP, POP3, SMTP/AUTH) for a specific user.  Messages delivered
to that user's mailbox can be forwarded to an external email address.

.. warning::

    If the system is bound to a :ref:`remote account provider
    <account-providers>` and a user account is remotely deleted, the associated
    mailbox must be erased manually. The file system path prefix is
    :file:`/var/lib/nethserver/vmail/`.

.. index::
    pair: shared; mailbox

Mailboxes can be shared among groups of users.  The :guilabel:`Email addresses >
Shared mailboxes` page allows creating a new :dfn:`shared mailbox` and defining
one or more owning groups. Shared mailboxes can also be created by any IMAP
client supporting IMAP ACL protocol extension (RFC 4314).

The system enables the creation of an unlimited number of additional email
addresses, from the :guilabel:`Email addresses > Mail aliases` page. Each
:dfn:`mail alias` is associated with one or more destinations. A
:dfn:`destination` can be of the following types:

* user mailbox,
* shared mailbox,
* external email address.

A mail alias can be bound to any mail domain or be specific to one mail domain.
For example:

* First domain: mydomain.net
* Second domain: example.com
* Email address *info* valid for both domains: info@mydomain.net,
  info@example.com
* Email address *goofy* valid only for one domain: goofy@example.com

.. index::
   pair: email; local network only
   triple: email; private; internal

Sometimes a company forbids communications from outside the organization
using personal email addresses. The :guilabel:`Local network only`
option blocks the possibility of an address to receive email from the
outside.  Still the "local network only" address can be used to
exchange messages with other accounts of the system.

.. _email_mailboxes:

Mailbox configuration
=====================

The :guilabel:`Email > Mailboxes` page controls what protocols are
available to access a user mailbox:

* IMAP [#IMAP]_ (recommended)
* POP3 [#POP3]_ (obsolete)

For security reasons, all protocols require STARTTLS encryption by
default.  The :guilabel:`Allow unencrypted connections`, disables this
important requirement, and allows passing clear-text passwords and
mail contents on the network.

.. warning:: Do not allow unencrypted connections on production
             environments!

.. index::
   triple: email; custom; quota

From the same page, the :guilabel:`disk space` of each mailbox can be
limited to a default :dfn:`quota`.  If the mailbox quota is enabled, the
:guilabel:`Dashboard > Mail quota` page summarizes the quota usage for
each user.  This summary is updated when a user logs in or a message is
delivered. The quota can be customized for a specific user in :guilabel:`Email
addresses > User mailboxes > Edit > Custom mailbox quota`.

.. index::
   pair: email; spam retention
   triple: email; custom; spam retention

Messages marked as **spam** (see :ref:`email_filter`) can be automatically
moved into the :dfn:`Junk` folder by enabling the option
:guilabel:`Move to "Junk" folder`. Spam messages are expunged
automatically after the :guilabel:`Hold for` period has elapsed.  The
spam retention period can be customized for a specific user in
:guilabel:`Email addresses > User mailboxes > Edit > Customize spam message
retention`.

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

.. _email_messages:

Messages
========

.. index::
   pair: email; size
   pair: email; retries
   pair: email; message queue

From the :guilabel:`Email > Messages` page, the :guilabel:`Queue
message max size` slider sets the maximum size of messages traversing
the system. If this limit is exceeded, a message cannot enter the
system at all and is rejected.

Once a message enters |product|, it is persisted to a :dfn:`queue`,
waiting for final delivery or relay. When |product| relays a message
to a remote server, errors may occur. For instance,

* the network connection fails, or
* the other server is down or is overloaded.

Those and other errors are *temporary*: in such cases, |product|
attempts to reconnect the remote host at regular intervals until a
limit is reached. The :guilabel:`Queue message lifetime` slider
changes this limit.  By default it is set to *4 days*.

While messages are in the queue, the administrator can request an
immediate message relay attempt, by pressing the button
:guilabel:`Attempt to send` from the :guilabel:`Email > Queue
management` page.  Otherwise the administrator can selectively delete
queued messages or empty the queue with :guilabel:`Delete all` button.

.. index::
   pair: email; always send a copy
   pair: email; hidden copy
   pair: email; bcc

To keep an hidden copy of any message traversing the mail server,
enable the :guilabel:`Always send a copy (Bcc)` check box. This feature
is different from the same check box under :guilabel:`Email > Domain` as
it does not differentiate between mail domains and catches also any
outgoing message.

.. warning:: On some countries, enabling the *Always send a copy
             (Bcc)* can be against privacy laws.

.. _smarthost-configuration:

.. index:: 
   pair: email; smarthost

Smarthost
=========

The :guilabel:`Email > Smarthost` page, configures all outgoing
messages to be directed through a special SMTP server, technically
named :dfn:`smarthost`.  A smarthost accepts to relay messages under
some restrictions. It could check:

* the client IP address,
* the client SMTP AUTH credentials.

.. note:: Sending through a *smarthost* is generally not recommended.
          It might be used only if the server is temporarily
          blacklisted [#DNSBL]_, or normal SMTP access is restricted
          by the ISP.


.. index::
   pair: email; filter

.. _email_filter:

Filter
======

All transiting email messages are subjected to a list of checks that
can be selectively enabled in :guilabel:`Email > Filter` page:

* Block of attachments
* Anti-virus
* Anti-spam

.. index::
   pair: email; attachment

Block of attachments
--------------------

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
   pair: email; anti-virus
   see: anti-virus; antivirus

Anti-virus
----------

The anti-virus component finds email messages containing
viruses. Infected messages are discarded. The virus signature database
is updated periodically.

.. index::
   single: spam
   pair: email; anti-spam
   pair: spam; score
   see: anti-spam; antispam

Anti-spam
---------

The anti-spam component [#Spamassassin]_ analyzes emails by detecting
and classifying :dfn:`spam` [#SPAM]_ messages using heuristic
criteria, predetermined rules and statistical evaluations on the
content of messages.  The rules are public and updated on a regular
basis.
The filter can also check if sender server is listed in one or more blacklists (:index:`DNSBL`).
A score is associated to each rule.

Total spam score collected at the end of the analysis allows the
server to decide whether to *reject* the message or *mark* it as spam
and deliver it anyway.  The score thresholds are controlled by
:guilabel:`Spam threshold` and :guilabel:`Deny message spam threshold`
sliders in :guilabel:`Email > Filter` page.

Messages marked as spam have a special header ``X-Spam-Flag: YES``.
The :guilabel:`Add a prefix to spam messages subject` option makes the
spam flag visible on the subject of the message, by prepending the
given string to the ``Subject`` header.

.. index::
   pair: email; spam training

Statistical filters, called Bayesian [#BAYES]_, are special rules that
evolve and quickly adapt analyzing messages marked as **spam** or
**ham**.

The statistical filters can then be trained with any IMAP client by
simply moving a message in and out of the :dfn:`Junk folder` or marking it as spam if your client provides such feature. As
prerequisite, the Junk folder must be enabled from
:guilabel:`Email > Mailboxes` page by checking :guilabel:`Move to
"Junk" folder"` option.

* By *putting a message into the Junk folder*, the filters learn
  it is spam and will assign an higher score to similar messages.

* On the contrary, by *getting a message out of Junk*, the filters
  learn it is ham: next time a lower score will be assigned.

By default, all users can train the filters using this technique.  If
a group called ``spamtrainers`` exists, only users in this group
will be allowed to train the filters.

The bayesian filter training applies to all users on the system, not only the user that marked an email as spam or ham.

It is important to understand how the Bayesian tests really work:

* It does not outright flag messages as spam if they contain a specific subject, or sender address. It is only collecting specific characteristics of the message.

* A message can only be flagged one time. If the same message is flagged multiple times, it will not affect anything as the dynamic tests have already been trained by that message.

* The Bayesian tests **are not active until it has received enough information. This includes a minimum of 200 spams AND 200 hams (false positives).** 

.. note:: It is a good habit to frequently check the Junk folder
          in order to not losing email wrongly recognized as spam.

.. index::
   pair: email; whitelist
   pair: email; blacklist

If the system fails to recognize spam properly even after training,
the *whitelists* and *blacklists* can help. Those are lists of email
addresses or domains respectively always allowed and always blocked to
send or receive messages.

The section :guilabel:`Rules by mail address` allows creating
three types of rules:

* :guilabel:`Block From`: any message from specified sender is blocked

* :guilabel:`Allow From`: any message from specified sender is
  accepted

* :guilabel:`Allow To`: any message to the specified recipient is
  accepted

It's possible to create an 'Allow' or 'Block' rule even for a complete email domain, not just for a single email address : you just need to specificy the desired domain (e.g. : nethserver.org).

.. note:: Antivirus checks are enforced despite *whitelist* settings.

.. index::
   pair: port; imap
   pair: port; imaps
   pair: port; pop3
   pair: port; pop3s
   pair: port; smtp
   pair: port; smtps

.. _email-port25:

Block port 25
=============

If the system is acting as the network gateway, green and blue zones 
will not be able to send mail to external servers through port 25 (SMTP).
Blocking port 25 could prevent remotely controlled machines inside the LAN from sending SPAM.

The administrator can change this policy creating a custom firewall rule inside the :ref:`firewall-rules-section` page.

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

.. warning:: The standard SMTP port 25 is reserved for mail transfers
             between MTA servers. On clients use only submission ports.

If |product| acts also as DNS server on the LAN, it registers its name
as MX record along with the following aliases:

* ``smtp.<domain>``
* ``imap.<domain>``
* ``pop.<domain>``
* ``pop3.<domain>``

For example:

* Domain: ``mysite.com``
* Hostname: ``mail.mysite.com``
* MX record: ``mail.mysite.com``
* Available aliases: ``smtp.mysite.com``, ``imap.mysite.com``,
  ``pop.mysite.com``, ``pop3.mysite.com``.

.. note:: Some email clients (e.g. Mozilla Thunderbird) are able to use DNS
          aliases and MX record to automatically configure email accounts by
          simply typing the email address.

To disable local MX and aliases, access the root's console and type: ::

  config setprop postfix MxRecordStatus disabled
  signal-event nethserver-hosts-update


.. _email_policies:

Special SMTP access policies
============================

The default |product| configuration requires that all clients use the
submission port (587) with encryption and authentication enabled to
send mail through the SMTP server.

To ease the configuration of legacy environments, the :guilabel:`Email
> SMTP access` page allows making some exceptions on the default SMTP
access policy.

.. warning:: Do not change the default policy on new environments!

For instance, there are some devices (printers, scanners, ...) that do
not support SMTP authentication, encryption or port settings.  Those
can be enabled to send email messages by listing their IP address in
:guilabel:`Allow relay from IP addresses` text area.

Moreover, under :guilabel:`Advanced options` there are further options:

* The :guilabel:`Allow relay from trusted networks` option allows any
  client in the trusted networks to send email messages without any
  restriction.

* The :guilabel:`Enable authentication on port 25` option allows
  authenticated SMTP clients to send email messages also on port 25.

.. index::
   pair: email; HELO
   alias: HELO; EHLO

.. _email_helo:

Custom HELO
===========

The first step of an SMTP session is the exchange of :dfn:`HELO`
command (or :dfn:`EHLO`).  This command takes a valid server name as
required parameter (RFC 1123).

|product| and other mail servers try to reduce spam by not accepting
HELO domains that are not registered on a public DNS.

When talking to another mail server, |product| uses its full host name
(FQDN) as the value for the HELO command.  If the FQDN is not
registered in public DNS, the HELO can be fixed by setting a special
*prop*.  For instance, assuming ``myhelo.example.com`` is the publicly
registered DNS record, type the following commands: ::

  config setprop postfix HeloHost myhelo.example.com
  signal-event nethserver-mail-common-save

This configuration is also valuable if the mail server is using a free
dynamic DNS service.

.. _email_outlook_deleted:

Outlook deleted mail
====================

Unlike almost any IMAP client, Outlook does not move deleted messages to the trash folder, but simply marks them as "deleted".

It's possibile to automatically move messages inside the trash using following commands: ::

 config setprop dovecot DeletedToTrash enabled
 signal-event nethserver-mail-server-save

You should also change Outlook configuration to hide deleted messages from inbox folder.
This configuration is available in the options menu.

.. _email_log:

Log
===

Every mail server operation is saved in the following log files:

* :file:`/var/log/maillog` registers all mail transactions
* :file:`/var/log/imap` contains users login and logout operations

A transaction recorded in the :file:`maillog` file usually involves
different components of the mail server.  Each line contains
respectively

* the timestamp,
* the host name,
* the component name, and the process-id of the component instance
* a text message detailing the operation

A picture of the whole system is available from *workaround.org* [#MailComponents]_.

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
.. [#MailDirFormat] The Maildir format, https://en.wikipedia.org/wiki/Maildir
.. [#Markdown] The Markdown plain text formatting syntax, https://en.wikipedia.org/wiki/Markdown
.. [#IMAP] IMAP https://en.wikipedia.org/wiki/Internet_Message_Access_Protocol
.. [#POP3] POP3 https://en.wikipedia.org/wiki/Post_Office_Protocol
.. [#DNSBL] DNSBL https://en.wikipedia.org/wiki/DNSBL
.. [#SPAM] SPAM https://en.wikipedia.org/wiki/Spamming
.. [#Spamassassin] Spamassassin home page http://wiki.apache.org/spamassassin/Spam
.. [#BAYES] Bayesian filtering https://en.wikipedia.org/wiki/Naive_Bayes_spam_filtering
.. [#MailComponents] The wondrous Ways of an Email https://workaround.org/ispmail/wheezybig-picture/
