.. _email2-section:

==============
Email 2 (Beta)
==============

The **Email 2** module is an alternative to :ref:`email-section`, based on the
Rspamd [#RSPAMD]_ filter engine. It aims to be the  successor of
the current Email module, by providing its old features plus new ones. For
background information refer to the :ref:`email-section` chapter.

Once installed from the :guilabel:`Software center` page, go to the
:guilabel:`Email` page as usual.

This new module provides the email filter engine for the
:ref:`pop3_connector-section` and :ref:`pop3_proxy-section` modules too,
therefore an upgrade for those modules is required. See
:ref:`mail2-upgrade-procedures-section`.

The :guilabel:`Email > Domains > Append a legal note to sent messages` (also
known as "Disclaimer") feature was split in a separate, optional package:
``nethserver-mail2-disclaimer``. The upgrade procedures documented in this
section install it for backward compatibility, however new installations should
avoid it, as it relies on an old package [#ALTERMIME]_ that can be removed in
future releases.

Configuration options
=====================

New configuration options, specific to Email 2, are

* DKIM signature
* Rspamd web UI
* Greylist threshold [#GREY]_

DKIM signature
--------------

DomainKeys Identified Mail (DKIM) [#DKIM]_ provides a way to validate the
sending MTA, which adds a cryptographic signature to the outbound message MIME
headers.

To enable the DKIM signature for a mail domain, enable :guilabel:`Email >
Domains > Sign outbound messages with DomainKeys Identified Mail (DKIM)`.

To work effectively, the public DNS must be configured properly. Follow the
instructions provided by the configuration page itself.

The DKIM signature headers are added only to messages sent through TCP ports 587
(submission) and 465 (smtps).

Rspamd web UI
-------------

The Rspamd web UI is available via the administrative HTTPS
port 980 (the same of Server Manager) at the following URL: ::
    
    https://<HOST_IP>:980/rspamd

The actual URL is listed under the :guilabel:`Applications` page. By default
access is granted to:

* ``admin`` user
* members of ``domain admins`` group
* builtin ``rspamd`` login

A direct link with HTTP authentication credentials for ``rspamd`` login is
available from :guilabel:`Email > Filter > Rspamd user interface`.

.. warning::
    
    For security reasons, the ``root`` account is not granted access to Rspamd
    web UI

Greylist threshold
------------------

A new spam score threshold is provided by Rspamd. If the spam score is above it,
the message is temporarily rejected. An SMTP-compliant MTA must attempt to
deliver the deferred message again; spammers are likely to give up instead.

To adjust the threshold see :guilabel:`Email > Filter > Anti spam > Greylist threshold`.

.. _mail2-upgrade-procedures-section:

Upgrade procedures
==================

It is possible to switch a running system to this new module, starting from
the **Email** module, **SMTP proxy** or **POP3 connector**  module.

Make sure the system is updated with the latest packages before running the
upgrade procedure.

If something is wrong with ``rspamd``, please report the issue on
`community.nethserver.org <https://community.nethserver.org>`_.

To switch an old mail server with ``amavisd-new`` filter engine to ``rspamd``
run the upgrade commands reported on the following sections. It is possible
to revert the upgrade too.

From Email module
-----------------

Upgrade: ::

    yum swap \
        -- remove nethserver-mail-{common,disclaimer,filter,server} \
        -- install nethserver-mail2-{common,disclaimer,filter,server}

Revert upgrade: ::

    yum swap \
        -- install nethserver-mail-{common,disclaimer,filter,server} \
        -- remove nethserver-mail2-{common,disclaimer,filter,server}

From SMTP proxy module
----------------------

Upgrade: ::

    yum swap \
        -- remove nethserver-mail-{common,disclaimer,filter} \
        -- install nethserver-mail2-{common,disclaimer,filter}

Revert upgrade: ::

    yum swap \
        -- install nethserver-mail-{common,disclaimer,filter} \
        -- remove nethserver-mail2-{common,disclaimer,filter}

From POP3 connector module
--------------------------

When upgrading to **Email 2**, the POP3 connector settings of each account
regarding :guilabel:`Check messages for SPAM` and :guilabel:`Check messages for
virus` options are ignored and overridden by the new :guilabel:`Scan messages
with email filter`.

Upgrade: ::

    yum swap \
        -- remove nethserver-mail-{common,disclaimer,filter,server} nethserver-getmail nethserver-spamd \
        -- install nethserver-mail2-{common,disclaimer,filter,server,getmail}

Revert upgrade: ::

    yum swap \
        -- install nethserver-mail-{common,disclaimer,filter,server} nethserver-getmail \
        -- remove nethserver-mail2-{common,disclaimer,filter,server,getmail}

From POP3 proxy module
----------------------

Upgrade: ::

    yum swap \
        -- remove nethserver-mail-{common,disclaimer,filter} nethserver-p3scan nethserver-spamd \
        -- install nethserver-mail2-{common,disclaimer,filter,p3scan}

Revert upgrade: ::

    yum swap \
        -- install nethserver-mail-{common,disclaimer,filter} nethserver-p3scan nethserver-spamd \
        -- remove nethserver-mail2-{common,disclaimer,filter,p3scan}

.. rubric:: References

.. [#RSPAMD]
    Rspamd -- Fast, free and open-source spam filtering system.
    https://rspamd.com/

.. [#DKIM]
    Domain Keys Identified Mail (DKIM) is an email authentication method
    designed to detect email spoofing -- `Wikipedia
    <https://en.wikipedia.org/wiki/DomainKeys_Identified_Mail>`_

.. [#GREY]
    Greylisting is a method of defending e-mail users against spam. A mail
    transfer agent (MTA) using greylisting will "temporarily reject" any email from
    a sender it does not recognize -- `Wikipedia
    <https://en.wikipedia.org/wiki/Greylisting>`_

.. [#ALTERMIME]
    alterMIME is a small program which is used to alter your mime-encoded mailpack --
    https://pldaniels.com/altermime/
