
.. _email-section:

=====
Email
=====

Configure the e-mail services

Domains
=======

The table contains the list of internet domain names for which the
server will accept incoming email.

Create / Modify
---------------

Add a domain to the list of those configured for the email reception.


Domain
    The domain name, for example *nethesis.it*.

Description
    An optional field useful to the system administrator to take note
    of domain information.

Delivery locally
    Select this option to configure the server to deliver
    incoming mail addressed to the specified domain
    in local folders.

Forward to another server
    If you select this option, incoming mail will
    be forwarded to the specified server.

Disclaimer (legal notice)
    Automatically add a legal message (disclaimer)
    to all outgoing emails (not addressed to the domain).


Delete
-------

Remove the domain from those managed by the server. Any email
intended for the domain will be rejected.


Filter
======

Configure the filtering options of the email (antivirus, antispam,
forbidden attachments, etc).

Antivirus
    Enable virus scanning of emails in transit.

Antispam
    Enable antispam scanning of incoming emails.

Prefix Spam
    This prefix is added to the object underlying the recognized emails
    as spam.

Attachment Blocking
    The email server will block emails that contain attachments of types
    specified.

Executable
    The email server will block executable programs in email attachments.

Archives
    The email server will block emails with attachments containing archive files (zip,
    rar, etc.).

Custom List
    Define a list of extensions that will be blocked,
    such as doc, pdf, etc. (without starting dot, ie doc and not .doc).


Mailboxes
================

In this tab, you can configure some parameters related to the
local mail folders.

IMAP
    Enable folder access through the IMAP protocol (recommended).

POP3
    Enable folder access through the POP3 protocol (not recommended).

Allow unencrypted connections
    Allows you to enable access to the folders using unencrypted protocols (not recommended).

Disk space
    Allows you to limit disk usage by email.
    
    * Unlimited: select not to impose limits
    * Apply quota: limit maximum space of mail for each user to the value
      indicated (email quota).

Move to Folder * junkmail *
    Email messages identified as spam are moved to each user folder
    * Junkmail * instead of being delivered to the Inbox.


Messages
========

Configure the management of email messages.

Accept message size to
    Use the cursor to select the maximum size of a
    single email message. The server will reject mail larger than the value
    set, returning an explanatory error.

Retry sending for
    Use the cursor to select the maximum time for which the server
    try to send a message. When it reaches the maximum time
    and the email has not yet been delivered, the sender will receive a
    error and the message is removed from the send queue, the server will no
    longer attempting to deliver it.

Send using a smarthost
    The server will attempt to send emails directly to
    destination (recommended in most cases). Selecting
    instead to sent through a smarthost, it will attempt to deliver them through the 
    ISP's SMTP server (recommended in case of unreliable connection or
    Residential ADSL, dynamic IP, etc).

Host Name
    The name of the mail server of the provider.

Port
    The port of the mail server of the provider.

Username
    If the provider's server requires authentication, specify the 
    username.

Password
    The password required by the provider.

Allow non-encrypted connection
    Normally, if using an authenticated connection (with username and password),
    an encrypted connection is required to protect the password. Selecting this option will
    permit a non-secure connection to connect to the
    provider (not recommended, use only if ISP has problems).

Queue Management
================

This tab allows you to manage the queue of emails in transit on the server.
The table lists all the mail waiting to be delivered,
and is normally empty. The following fields will be shown:

* Id: identifier of the message
* Sender: from email address (who sent the message)
* Size: The size in bytes of the email
* Date: The date of creation of the email
* Recipients: the list of recipients


Delete
-------

It's possible to delete an e-mail in the queue, for example, an email sent
by mistake or too large.

Remove all
-------------

The button will delete all the emails in the queue.

Try sending
-------------

Normally, the server, in case of problems while sending the email,
retries at regular intervals. Clicking Attempt to send, emails
will be sent immediately.

Update
--------

Reload the list of emails in the queue.

===============
Email addresses
===============

Associate email address to users or groups of the system.


Create / Modify
===================

Create the association between a new email address and a
user or group already present in the system.

Email
    Specify in the text field only the part before **@** character.
    Then choose from the drop-down menu if the address is for a
    specific domain or for *all* domains in the system.

Description
    A free text field for recording any annotation.

Account
    Select a user or a group among those already in the
    system to be associated with the email address.

Only local networks
    Enabling this option will block the reception of messages
    from external senders.

Delete
=======

Delete the e-mail address. This does not affect
messages already delivered to the user or group associated with the address.
Future messages destined the address will be rejected.

========================
External email addresses
========================

External email addresses are mailboxes that
are checked at regular intervals using the **POP3** or **IMAP4** protocol.
Messages contained in the mailbox are downloaded and delivered to
local users or groups, as per configuration in 
this form.

External addresses
==================

Configure the list of external addresses and the association with the user of the system.

Create / Modify
---------------

Create or edit an external address.

Email
    The external email address to check.

Protocol
    The protocol used to access the remote server. It can be *POP3* or *IMAP4* (recommended).

Server Address
    Host name or IP address of the remote server.

Username
    Username used for authentication to the remote system.

Password
    The password used to authenticate.

Account
    Select the user or group that will receive the downloaded messages. 

Enable SSL
    Enable encryption of the connection with the remote server.

Delete messages downloaded
    If enabled, downloaded messages will be deleted from the remote server (recommended). Leave disabled to keep
    a copy on remote server.

Delete
-------

Deleting an account will *not* delete the messages already delivered.


Download now
------------

Immediately starts the download from all external addresses.


General
========

Enable
    Allows you to enable or disable the Fetchmail daemon that
    downloads emails from external addresses.

Check every
    Frequency of checking for new messages on the external addresses.
    It is recommended an interval of at least 15 minutes.
