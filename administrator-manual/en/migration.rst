.. index:: migration

.. _migration-section:

=====================================
Migration from NethService/SME Server
=====================================

Migration is the process to convert a SME Server/NethService
machine (:dfn:`source`) into a |product| (:dfn:`destination`).

#. In the source host, create a full backup archive and move it
   to the destination host.

#. In the destination host, install all packages that cover the same
   features of the source.

#. Explode the full backup archive into some directory; for instance,
   create the directory :file:`/var/lib/migration`.

#. In |product|, signal the event ``migration-import``::

     signal-event migration-import /var/lib/migration

   This step will require some time.

#. Check for any error message in :file:`/var/log/messages`::
 
     grep -E '(FAIL|ERROR)' /var/log/messages

.. index::
   pair: migration; email

.. _migration_email:

Email
=====

Before running |product| in production, some considerations about the
network and existing mail client configurations are required: what
ports are in use, if SMTPAUTH and TLS are enabled.  Refer to
:ref:`email_clients` and :ref:`email_policies` sections for more
informations.

In a mail server migration, the source mail server could be on
production even after the backup has been done, and email messages
continue to be delivered until it is taken down permanently.

An helper ``rsync`` script is provided by package
``nethserver-mail-server``, to re-synchronize destination mailboxes
with the source host:
:file:`/usr/share/doc/nethserver-mail-server-<VERSION>/sync_maildirs.sh`. It
runs on the destination host: ::

  Usage: 
    ./sync_maildirs.sh [-h] [-n] [-p] -s IPADDR 
	-h          help message
	-n          dry run
	-p PORT     ssh port on source host (default 22)
	-s IPADDR   rsync from source host IPADDR

The source host at ``IPADDR`` must be accessible by the ``root``
user, through ``ssh`` with public key authentication.
