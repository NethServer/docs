
.. _pop3_connector-section:
 
==============
POP3 connector
==============

.. note::

    Since |product| 7.5.1804 new :ref:`email-section`,
    :ref:`pop3_connector-section` and :ref:`pop3_proxy-section` installations
    are based on the Rspamd filter engine. Previous |product| installations are
    automatically upgraded to Rspamd as described in :ref:`email2-section`

The :guilabel:`POP3 connector` page allows configuring a list of mail
accounts that will be checked regularly. Messages coming from the remote
accounts will be delivered to local users.

It is not recommended to use the POP3 connector as the primary method
for managing email.  Mail delivery can be affected by disk space and
connectivity problems of the provider's server. Also, the spam filter will
be less effective due to the original email envelope information becoming lost. 

POP3/IMAP accounts are configured from :guilabel:`POP3 connector >
Accounts` page. Each account can be specified:

* the email address (as unique account identifier)
* the protocol (IMAP/POP3/IMAP with SSL/POP3 with SSL)
* the remote server address
* the account credentials
* the local user account where to deliver messages
* if a message has to be deleted from the remote server after delivery
* anti-spam and anti-virus checks

.. note:: It is allowed to associate more than one external accounts to a local
          one.  Deleting an account will *not* delete already
          delivered messages.

After the account configuration has been completed, the account is automatically
checked for new mail.

.. index:: 
   pair: Getmail; software

The underneath implementation is based on :dfn:`Getmail`
[#Getmail]_. After fetching mail messages from the POP3/IMAP
provider Getmail applies all required filters (SPAM and virus) prior
to delivering the mail locally.
All messages are filtered according to the :ref:`configured rules <email_filter>`.

All operations are logged in :file:`/var/log/maillog`.

.. warning:: If an account was selected for delivery and has been subsequently deleted
             the configuration becomes inconsistent. If this should happen
             then existing account configuration in :guilabel:`POP3 connector` page
             must be disabled or deleted.

.. rubric:: References

.. [#Getmail] Getmail is a remote-mail retrieval utility http://pyropus.ca/software/getmail/
