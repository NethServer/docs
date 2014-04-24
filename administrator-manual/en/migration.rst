=====================================
Migration from NethService/SME Server
=====================================

:index:`Migration` is the process to convert a SME Server (or NethService) machine into a |product|.

#. In the old host, create a full backup archive and move it
   to the new |product| host.
#. In the new server, install all packages that cover the same features of the old one.
#. Explode the full backup archive into some directory (for instance
   ``/var/lib/migration``)
#. Signal the event::

    # signal-event migration-import /var/lib/migration

   This step will require some time.
#. Search for any ``ERROR`` or ``FAIL`` string in ``/var/log/messages``

.. tip::
   For mail server migrations, you can re-synchronize the mail storage after 
   the ``migration-import`` event.  An helper script is provided by package
   ``nethserver-mail-server``: see 
   ``/usr/share/doc/nethserver-mail-server-<VERSION>/sync_maildirs.sh``.
