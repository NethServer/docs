
.. _pop3_connector-section:
 
==============
POP3 connector
==============

The :guilabel:`POP3 connector` page allows configuring a list of mail
accounts that will be checked regularly. Messages from these remote
accounts will be delivered to local users.

It is not recommended to use the POP3 connector as the primary method
for managing email.  Mail delivery can be affected by disk space and
connectivity problems of the provider's server.  Also the spam filter
is less effective, because the original email envelope information
are lost.

POP3/IMAP accounts are configured from :guilabel:`POP3 connector >
Accounts` page. For each account can be specified:

* the email address (as unique account identifier),
* the protocol (IMAP/POP3/IMAP with SSL/POP3 with SSL),
* the remote server address,
* the account credentials,
* the local user account where to deliver messages,
* if a message has to be deleted from the remote server after delivery,
* antiSPAM and antivirus checks.

.. note:: It is allowed to associate more external accounts to a local
          one.  Deleting an account will *not* delete already
          delivered messages.

After the account configuration has been completed, the account is automatically
checked for new mail.

.. index:: 
   pair: Gethmail; software

The underneath implementation is based on :dfn:`Getmail`
[#Getmail]_. After fetching mail messages from the POP3/IMAP
provider, Getmail applies all required filters (SPAM and virus),
finally it delivers them locally.
All messages are filtered accordingly to the :ref:`configured rules <email_filter>`.

All operations are logged in :file:`/var/log/maillog`.

.. warning:: If an account was selected for delivery and has been subsequently deleted,
             the configuration becomes inconsistent.
             The existing account configuration in :guilabel:`POP3 connector` page
             must be disabled or deleted.

.. rubric:: References

.. [#Getmail] Getmail is a remote-mail retrieval utility http://pyropus.ca/software/getmail/
