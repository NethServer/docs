.. _email-section:

=====
Email
=====

The email server is split in three main modules:

* IMAP and POP3 server to read email
* SMTP server for sending and receiving
* antispam filter, antivirus and attachments blocker

Benefits:

* complete autonomy in the mail management
* avoid problems due to the Internet Service Provider
* ability to track message's route in order to detect errors
* optimized antivirus and antispam scan


See also:
 
* How electronic mail works: http://en.wikipedia.org/wiki/Email
* MX record: http://en.wikipedia.org/wiki/MX_record
* SMTP protocol: http://en.wikipedia.org/wiki/Simple_Mail_Transfer_Protocol


Domains
=======

The server can handle an unlimited number of domains.  For each
domain, the server can:

* Deliver locally: mail is delivered to local users and stored in
  Maildir format
* :index:`Relay` to another server: incoming mail is forwarded to
  another mail server

See also:

* Maildir format: http://en.wikipedia.org/wiki/Maildir


.. note:: If you delete a domain, mail will not be deleted, any
   message already received will be kept on the server.


|product| allows you to keep a copy of all email traversing the
server: all messages will be delivered to the final recipient and to a
local user (or group).  This option can be configured for each domain
managed by the mail server.

.. warning:: On some countries, enabling the :index:`hidden copy` can
             be against privacy laws.

Disclaimer
----------

|product| can automatically append a default text to outgoing
email. This text is called :index:`disclaimer` and it can be used to
meet some law's requirements.  Please note :dfn:`signature` and
:dfn:`disclaimer` are very different concepts.

:dfn:`Signature` should be inserted inside message's text only from
mail client (MUA): Outlook, Thunderbird, etc.  Usually it's a
customizable text containing information such as sender addresses and
phone numbers.

Signature example: ::

 John Smith 
 President | My Mighty Company | Middle Earth 
 555-555-5555 | john@mydomain.com | http://www.mydomain.com

The :dfn:`disclaimer` is a fixed text and can only be "attached" to
messages from the server.  The disclaimer shall be attached to
outgoing email, not added to the message.  This technique allows you
to maintain the integrity of the message in case of using digital
signature.

Disclaimer example: ::

  This email and any files transmitted with it are confidential and
  intended solely for the use of the individual or entity to whom they
  are addressed.  If you have received this email in error please
  notify the system manager.  This message contains confidential
  information and is intended only for the individual named.


Discaliemr can contain :dfn:`markdown` code to format the text.

See also:

* http://en.wikipedia.org/wiki/Markdown


Mail addresses
==============

The system enables the creation of an unlimited number of email
addresses also known as :index:`pseudonyms`.  Each address is
associated with a system user or group. It can be enabled on all
configured domains or only on specific domains.

Example:

* First domain: mydomain.net
* Second domain: example.com
* Email address *info* valid for both domains: info@mydomain.net,
  info@example.com
* Email address *goofy* valid only for one domain: goofy@example.com

If the mail server module is installed, the system will create an
address for any new users using the user name.  When creating the
user, the administrator can choose which domains will be enabled for
the pseudonym.

Example:

* Domain: mydomain.net
* User: goofy
* Address: goofy@mydomain.net

Group addresses
---------------

When an address is associated with a group, the server can deliver
mail in two ways:

* send a copy to each member of the group
* store the message in a shared folder

.. note:: If the group has many members and messages contain big
   attachments, using the first method can lead to excessive disk
   space usage.

This option can be changed from the :guilabel:`Groups` page.


Private addresses
-----------------

Sometimes a company doesn't want to allow communications with external
world using personal mail addresses.

The :guilabel:`Local network only` option blocks the possibility of an
address to receive mail from the outside.  Still the address can be
used for index:`internal mail`.


.. _mailboxes-section:

Mailboxes
=========

Mailboxes can be accessed using two protocols:

* IMAP
* POP3 (not recommended)

All connections from/to clients are encrypted by default.  Even if
strongly not recommended, you can disable encryption by enabling the
option :guilabel:`Allow unencrypted connections`.


Messages marked as SPAM can be automatically moved into the
:dfn:`junkmail` folder by enabling the option :guilabel:`Move to
"junkmail" folder"`.  Finally you can set a timeout after which SPAM
messages should be removed from the mailbox.

See also:

* IMAP protocol:
  http://en.wikipedia.org/wiki/Internet_Message_Access_Protocol
* POP3 protocol: http://en.wikipedia.org/wiki/Post_Office_Protocol

.. _mail_messages-section:

Messages
========

The administrator can set the maximum message size: messages with
larger size will be rejected.

In case of errors, the server will attempt to deliver mail to remote
hosts at regular intervals until the maximum configured time is
reached: default value is 4 days.

Smarthost
---------

In this mode, the server will not directly send mail to remote hosts,
but it will deliver messages to an external mail server (usually the
ISP) that will take care of delivering.

The SMTP server (technically defined as :index:`smarthost`) will
accept mail if:

* it has been configured to act as a SMTP relay for the IP address of
  |product| (normal configuration for a provider)
* |product| is using the SMTP AUTH, authentication based on username
  and password

.. note:: The use of smarthost is not recommended. Use this function
   only in case the server is temporarily blacklisted.

See also:

* Blacklist antispam: http://it.wikipedia.org/wiki/DNSBL

Filter
======

All mail in transit is subjected to a list of checks that can be
selectively enabled:

* antivirus
* antispam
* block of attachment

Antivirus
---------

It finds mails containing viruses. Infected messages are discarded and
not delivered to the recipient.

Block attachments
------------------

Check for :index:`attachments` forbidden by company policies. The
server can check following types:

* :index:`executables` (eg. exe, msi)
* :index:`archives` (eg. zip, tar.gz, docx)
* custom extension list

If you choose to block executable files or archives, the system
recognizes these types regardless of file name.  Therefore it's
possible that MS Word file (docx) and OpenOffice (odt) are blocked
because they actually are archives.

Antispam
--------

:index:`Antispam` filter analyzes emails by detecting and classifying
spam using heuristic criteria, predetermined rules and statistical
evaluations on the content of messages.

The server uses a combination of rules and statistical filters.  The
rules are public and updated on a regular basis. A score is associated
to each rule.  Statistical filters, called Bayesian, are special rules
that evolve and quickly adapt analyzing messages marked as
:index:`SPAM` or HAM.

Total spam score collected at the end of the analysis allows the
server to decide whether to reject the message or mark it as spam.

Although not recommended, you can change the thresholds with
:guilabel:`Spam threshold` and :guilabel:`Deny message spam threshold`
options.

.. note:: Event if highly unlikely, the system may assign a score
   greater than 15 to a valid email.  In this case, the sender will
   receive a clear error (552 spam score exceeded threshold).

See also:

* What is SPAM: http://en.wikipedia.org/wiki/Spam e
  http://wiki.apache.org/spamassassin/Spam
* Bayesian filtering:
  http://en.wikipedia.org/wiki/Naive_Bayes_spam_filtering

.. _bayes-section:

Bayes
^^^^^

The anti-spam system is constantly trained through the messages
located in the folder :dfn:`junkmail`.  To inform the system about a
not recognized spam message, simply move it to the folder
:index:`junkmail` folder.  To report a valid email mistakenly marked
as spam you will need to move it out of junkmail folder.

By default, all users can train the filters using this technique.  If
you create a group called `spamtrainers``, only users in this group
will be allowed to train the filters.

.. note:: It's a good idea to constantly check your junkmail in order
   to not losing email wrongly recognized as spam.

Whitelist and blacklist
^^^^^^^^^^^^^^^^^^^^^^^

Whitelists and blacklists are lists of email addresses respectively
always allowed and always blocked.

The section :guilabel:`Rules by mail address` allows you to create
three types of rules:

* :guilabel:`Block From`: all messages from specified sender are
  always blocked
* :guilabel:`Allow From`: all messages from specified sender are
  always accepted
* :guilabel:`Allow To`: all messages destined to specified address are
  always accepted

.. warning:: The use of blacklists is not recommended. Use this option
   only if the system fails to recognize spam even after a proper
   training.


Queue management
================

Messages are placed in a queue before sending.  If a message can not
be delivered, the message remains in queue until maximum configured
time is reached (see :ref:`mail_messages-section`).

While messages are in queue, you can force a retry by pressing the
button :guilabel:`Attempt to send`.  Otherwise the administrator can
selectively delete queued messages or empty the queue with
:guilabel:`Delete all` button.

.. _mail_client-section:

Client configuration
====================

The server supports any type of mail clients. Ports to configure
inside clients are:

* IMAP: 143 with TLS
* POP3: 110 with TLS
* SMTP: 587 with TLS

Server is reachable from the LAN using the following aliases:

* smtp.<domain>
* imap.<domain>
* pop.<domain>
* pop3.<domain>

Example:

* Domain: mysite.com
* Available aliases: smtp.mysite.com, imap.mysite.com, pop.mysite.com,
  pop3.mysite.com

If the mail server is also DNS server for the network, some mail
clients (eg. Mozilla Thunderbird) are able to use DNS aliases to
automatically configure email accounts simply by entering username and
domain.

DNS alias
=========

Following DNS aliases are reserved:

* smtp.<domain>
* imap.<domain>
* pop.<domain>
* pop3.<domain>

To disable aliases: ::

  config setprop postfix MxRecordStatus disabled signal-event
  nethserver-hosts-save

Custom HELO
===========

The first step of an SMTP session is the exchange of :index:`HELO`
command (or :index:`EHLO`).  This command takes a valid server name as
required parameter (RFC 1123).

Some mail servers try to reduce spam by not accepting HELO domains
that are not registered on a public DNS.

|product| uses the value of the main domain (FQDN) as the parameter of
the HELO command.  If it is not possible to configure a server with
the real domain, you can still change value for the HELO command.
Just use these commands: ::

  config setprop postfix HeloHost myhelo signal-event
  nethserver-mail-common-save

Where `myhelo`` is the domain you want to use in HELO command.

This configuration can also be used when using a free dynamic DNS
service.

Send policies
=============

All clients must use the submission port 587 with encryption enabled
to send mail using SMTP server.

The server also implements additional access policies to ease the
configuration on in case of legacy environments.

Use these commands to enabled sending on port 25 with authentication
from any LAN or Internet clients: ::

  config setprop postfix AccessPolicies smtpauth signal-event
  nethserver-mail-server-save

Use these commands to enable sending on port 25 without authentication
from any client inside trusted networks: ::

  config setprop postfix AccessPolicies trustednetworks signal-event
  nethserver-mail-server-save

Policies can be used together: ::

  config setprop postfix AccessPolicies trustednetworks,smptauth
  signal-event nethserver-mail-server-save


However, there are some devices that do not support encryption or port
settings.  In this case you can force the configuration to accept send
operations on port 25 without authentication, but only for specific
hosts: ::

  mkdir -p /etc/e-smith/templates-custom/etc/postfix/access echo
  "192.168.1.22 OK" >> /etc/e-smith/templates-custom/etc/postfix/access/20clients
  signal-event nethserver-mail-common-save signal-event
  nethserver-mail-server-save

.. warning:: Avoid changing default policy unless it's really
             necessary

Log
===

All operations are saved inside log files:

* :file:`/var/log/maillog`: contains all sending and delivery
  operations
* :file:`/var/log/imap`: contains all login/logout actions to
  mailboxes
