.. _email2-section:

==============
Email 2 (Beta)
==============

The **Email 2** module is an alternative to :ref:`email-section`, based on the
`Rspamd <https://rspamd.com/>`_ filter engine. It aims to be the  successor of
the current Email module, by providing the same features plus new ones. For
background information refer to :ref:`email-section` page.

Once installed from the :guilabel:`Software center` page, go to the
:guilabel:`Email` page as usual.

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


Upgrade procedures
==================

It is possible to switch a running system to this new module, starting from
the **Email** module, or a **SMTP proxy** module installation.

From Email module
-----------------

To switch an old mail server with ``amavisd-new`` filter engine to ``rspamd``
run the following command: ::

    yum swap \
        -- remove nethserver-mail-{common,filter,server} \
        -- install nethserver-mail2-{common,filter,server}

If something is wrong with ``rspamd``, please report the issue on
`community.nethserver.org <https://community.nethserver.org>`_. To switch back
to the old engine: ::

    yum swap \
        -- install nethserver-mail-{common,filter,server} \
        -- remove nethserver-mail2-{common,filter,server}

From SMTP proxy module
----------------------

To switch an old SMTP proxy based on ``amavisd-new`` filter engine to ``rspamd``
run the following command: ::

    yum swap \
        -- remove nethserver-mail-{common,filter} \
        -- install nethserver-mail2-{common,filter}

If something is wrong with ``rspamd``, please report the issue on
`community.nethserver.org <https://community.nethserver.org>`_. To switch back
to the old engine: ::

    yum swap \
        -- install nethserver-mail-{common,filter} \
        -- remove nethserver-mail2-{common,filter}

