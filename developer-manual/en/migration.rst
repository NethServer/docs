=====================================
Migration from NethService/SME Server
=====================================

Migration is the process to convert a SME Server (or NethService) machine into a NethServer.

#. In the *NethService* host, create a full backup archive and move it
   to the *NethServer* host.
#. In *NethServer*, install all packages that cover the same features of
   *NethService*.
#. Explode the full backup archive on some directory (for instance
   ``/var/lib/migration``)
#. Signal the event::

    # signal-event migration-import /var/lib/migration

   This step will require some time…
#. Search for any ``ERROR`` string in ``/var/log/messages``

--------------

Packages
========

Programming conventions
-----------------------

Most modules have already a migration action which handles the step
automatically.

A migration action:

* must be named as ``<packagename>-migrate``
* must be linked into ``migration-import`` event
* must migrate old properties values to new ones
* can copy original data files to the new location
* must take care to apply the imported configuration, possibly using
  the ``<packagename>-update`` event

During migration some properties will not be imported:
 
 * UDPPort, TCPPort, UDPPorts, TCPPorts: all network ports will be
   reset to new defaults
 * DNS forwarder, green IP address, default gateway: these properties
   are filled up in bootstrap-console

All e-smith databases are moved in ``/var/lib/nethserver/db`` directory.

Code snippets
^^^^^^^^^^^^^

A simple migrate action in perl.

.. code-block:: perl

  #!/usr/bin/perl
  use esmith::DB::db;
  use esmith::event;
  use strict;
  my $event = shift;
  my $sourceDir = shift;
  my $esmithDbDir = 'home/e-smith/db';
  my $errors = 0;
  if {
    die;
  }
  my $srcConfigDb = esmith::DB::db]>open\_ro(join('', $sourceDir, $esmithDbDir,'configuration')) || die("Could not open source configuration database in $sourceDir");
  my $dstConfigDb = esmith::DB::db->open || die;
  my $service = ‘ejabberd’;
  my $old = $srcConfigDb->get($service);
  my $new = $dstConfigDb->get || $dstConfigDb->new_record($service);
  $new->merge_props($old->props);
  # Apply configuration
  if( ! esmith::event::event_signal('nethserver-ejabberd-update')) {
   exit(1);
  }
  exit 0;



Remember to change the service name and add a license header.

Add the migrate action to createlinks::

  #-----------------------------------
  # actions for migration-import event
  #-----------------------------------
  $event ="migration-import";
  event_actions($event, '<packagename>-migrate' => 60);
