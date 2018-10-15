.. _email2-section:

=================================
Email module transition to Rspamd
=================================

Since |product| 7.5.1804 new :ref:`email-section`, :ref:`pop3_connector-section`
and :ref:`pop3_proxy-section` installations are based on the Rspamd [#RSPAMD]_
filter engine.

* Previous |product| installations are automatically upgraded to
  Rspamd as described by this section.

* New configuration features, specific to the Rspamd-based implementation, are
  documented in :ref:`email-section`. Here is a brief list:

    * DKIM signature
    * Rspamd web UI
    * Greylist threshold [#GREY]_

Feature changes
===============


Append a legal notice
---------------------

The :guilabel:`Email > Domains > Append a legal note to sent messages` (also
known as "Disclaimer") feature was split in a separate, optional package:
``nethserver-mail2-disclaimer``. New installations should avoid it, as it relies
on an old package [#ALTERMIME]_ that can be removed in future releases.

.. index::
   pair: port; imap
   pair: port; imaps
   pair: port; pop3
   pair: port; pop3s
   pair: port; smtp
   pair: port; smtps

.. _email-port25:

Block port 25
-------------

The block of port 25 can prevent abuse/misuse by LAN machines. If the system
is acting as the LAN network gateway, the administrator can create a firewall
rule inside the :ref:`firewall-rules-section` page.

.. _email-mxrecordstatus:

Additional host name aliases
----------------------------

The following host name aliases were automatically registered in the local DNS
service, if the ``postfix/MxRecordStatus`` was ``enabled``:

* ``smtp.<domain>``
* ``imap.<domain>``
* ``pop.<domain>``
* ``pop3.<domain>``

When upgraded from an old Email module based on Amavisd, the
``postfix/MxRecordStatus`` is removed and  those aliases are pushed as ``self``
records in the ``hosts`` DB. They can be edited from :guilabel:`DNS > Server
alias` page.

MX record for LAN clients
-------------------------

The new Email module implementation based on Rspamd does not push the MX record
override for LAN hosts any more.  Ensure the LAN mail user agents are configured
to use SMTP/AUTH or are listed in :guilabel:`Email > SMTP access > Allow relay
from IP addresses` before upgrading.

.. _mail2-upgrade-procedures-section:

Upgrade procedures
==================

Manual upgrade procedures are no longer needed: upgrade occurs automatically.

.. only:: nscom

    After the upgrade the old anti-spam engine services provided by amavisd 
    and spamassassin are stopped and their packages can be removed.

    To clean up the old anti-spam rpms type ::

        yum remove amavisd-new spamassassin


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
