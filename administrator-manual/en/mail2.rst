.. _email2-section:

==============
Email 2 (Beta)
==============

The **Email 2** module is an alternative to :ref:`email-section`, based on the
`Rspamd <https://rspamd.com/>`_ filter engine. It aims to be the  successor of
the current Email module, by providing the same old features plus new ones. For
background information refer to the :ref:`email-section` chapter.

Once installed from the :guilabel:`Software center` page, go to the
:guilabel:`Email` page as usual.

This new module provides the email filter engine for the
:ref:`pop3_connector-section` module too, therefore an upgrade for that module
is required. See :ref:`mail2-upgrade-procedures-section`.

Features planned for final release
==================================

* Backward-compatible disclaimer signature (on development)
* Integrate Rspamd UI in Server Manager (waiting for an upstream fix)

Configuration options
=====================

New configuration options, specific to Email 2, are

* DKIM signature
* Rspamd web UI
* :guilabel:`Delay for suspicious threshold` (greylisting)

DKIM signature
--------------

DomainKeys Identified Mail (DKIM) provides a way to validate the sending MTA, which
adds a cryptographic signature to the outbound message MIME headers.

To enable the DKIM signature for a mail domain, enable :guilabel:`Email >
Domains > Sign outbound messages with DomainKeys Identified Mail (DKIM)`.

To work effectively, the public DNS must be configured properly. Follow the
instructions provided by the configuration page itself.

Rspamd web UI
-------------

The Rspamd web UI is available on a randomized URL via the administrative HTTPS
port 980 (like Server Manager). For security reasons the connection is
restricted to trusted networks only.

The random URL and the password required to access Rspamd web UI are available
under :guilabel:`Email > Filter > Rspamd user interface`.

The URL is also available listed under the :guilabel:`Applications` page.

Delay for suspicious threshold
------------------------------

A new spam score threshold is provided by Rspamd. If the spam score is above it,
the message is temporarily rejected. An SMTP-compliant MTA must attempt to
deliver the deferred message again; spammers are likely to give up instead.

To adjust the threshold see :guilabel:`Email > Filter > Anti spam > Delay for
suspicious threshold`.

.. _mail2-upgrade-procedures-section:

Upgrade procedures
==================

It is possible to switch a running system to this new module, starting from
the **Email** module, **SMTP proxy** or **POP3 connector**  module.

If something is wrong with ``rspamd``, please report the issue on
`community.nethserver.org <https://community.nethserver.org>`_.

To switch an old mail server with ``amavisd-new`` filter engine to ``rspamd``
run the upgrade commands reported on the following sections. It is possible
to revert the upgrade too.

From Email module
-----------------

Upgrade: ::

    yum swap \
        -- remove nethserver-mail-{common,filter,server} \
        -- install nethserver-mail2-{common,filter,server}

Revert upgrade: ::

    yum swap \
        -- install nethserver-mail-{common,filter,server} \
        -- remove nethserver-mail2-{common,filter,server}

From SMTP proxy module
----------------------

Upgrade: ::

    yum swap \
        -- remove nethserver-mail-{common,filter} \
        -- install nethserver-mail2-{common,filter}

Revert upgrade: ::

    yum swap \
        -- install nethserver-mail-{common,filter} \
        -- remove nethserver-mail2-{common,filter}

From POP3 connector module
--------------------------

When upgrading to **Email 2**, the POP3 connector settings of each account
regarding :guilabel:`Check messages for SPAM` and :guilabel:`Check messages for
virus` options are ignored and overridden by the new :guilabel:`Scan messages
with email filter`.

Upgrade: ::

    yum swap \
        -- remove nethserver-mail-{common,filter,server} nethserver-getmail nethserver-spamd \
        -- install nethserver-mail2-{common,filter,server,getmail}

Revert upgrade: ::

    yum swap \
        -- install nethserver-mail-{common,filter,server} nethserver-getmail \
        -- remove nethserver-mail2-{common,filter,server,getmail}
