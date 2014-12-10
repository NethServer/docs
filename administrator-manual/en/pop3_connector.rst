
.. _pop3_connector-section:
 
==============
POP3 connector
==============

The :guilabel:`POP3 connector` page allows configuring a list of mail
accounts that will be checked regularly. Messages from these remote
accounts will be delivered to local users or groups.

It is not recommended to use the POP3 connector as the primary method
for managing email.  Mail delivery can be affected by space and
connectivity problems of the provider's server.  Also the spam filter
is less effective, because the original email envelope information
are lost.

POP3/IMAP accounts are configured from :guilabel:`POP3 connector >
Accounts` page. For each account can be specified:

* the email address (as unique account identifier),
* the protocol (IMAP/POP3),
* the remote server address,
* the account credentials,
* the local user or group account where to deliver messages,
* if SSL should be disabled (not recommended),
* if a message has to be deleted from the remote server after delivery.

.. note:: It is allowed to associate more external accounts to a local
          one.  Deleting an account will *not* delete already
          delivered messages.

After the account configuration has been completed, the POP3 connector
module must be activated explicitly from the :guilabel:`POP3 connector
> General` page. On the same page the remote server polling interval
can be set from :guilabel:`Check accounts every` menu.

.. index:: 
   pair: Fetchmail; software

The underneath implementation is based on :dfn:`Fetchmail`
[#Fetchmail]_. After fetching mail messages from the POP3/IMAP
provider, Fetchmail delivers them locally by connecting directly to
the local mail-filter server. All messages are filtered accordingly to
the :ref:`configured rules <email_filter>`.

All operations are logged to the following files:

* :file:`/var/log/fetchmail.log`
* :file:`/var/log/maillog`

.. warning:: If an :ref:`Active Directory <samba_ads>` account was
             selected for delivery and has been subsequently deleted,
             the configuration becomes inconsistent!  The existing
             account configuration in :guilabel:`POP3 connector` page
             must be disabled or deleted.

.. rubric:: References

.. [#Fetchmail] Fetchmail is a remote-mail retrieval and forwarding
                utility http://www.fetchmail.info/
