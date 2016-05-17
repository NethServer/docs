nethserver-mail-filter
======================

Features
--------

* Anti-spam with DNSBL (see: `nethserver-unbound`_)
* Anti-virus
* Attachment block
* Real-time Blackhole List (RBL) (default disabled)
* Sender Policy Framework (SPF) (default disabled)
* Customized spam threshold 
* Sender WBL, Recipient whitelist 

.. _nethserver-unbound: http://github.com/NethServer/nethserver-unbound

Configuration database
----------------------

Postfix example: ::

  postfix=service
    ...
    RblStatus=disabled
    RblServers=host1,host2.. 
    SpfStatus=disabled
    ContentInspectionType=amavisd-before-queue

* ``ContentInspectionType {default,amavisd-before-queue}``:

* ``default``, apply the default content inspection type,
  depending on what packages are
  installed. ``nethserver-mail-filter`` changes the default to
  ``amavisd-before-queue``

* ``amavisd-before-queue``, executes anti-spam and anti-virus
  checks on open SMTP connections. Only CLEAN messages are
  allowed to enter the postfix queue

Amavis example: ::

  amavisd=service
    ...
    SpamCheckStatus=enabled
    VirusCheckStatus=enabled

    AdminNotificationStatus=disabled
    AvailableDecoders=mail,asc,uue,hqx,ync,F,Z,gz,bz2,lzo,rpm,cpio,tar,deb,zip,7z,rar,arj,arc,zoo,lha,doc,cab,tnef,exe
    BlockAttachmentClassList=
    BlockAttachmentCustomList=pif
    BlockAttachmentCustomStatus=disabled
    BlockAttachmentStatus=enabled
    EnabledDecoders=mail,asc,uue,hqx,ync,F,Z,gz,bz2,lzo,rpm,cpio,tar,deb,zip,7z,rar,arj,arc,zoo,lha,doc,cab,tnef,exe
    RecipientWhiteList=
    SenderBlackList=
    SenderWhiteList=clienti@example.it,marketing@domain.com
    SpamDsnLevel=20
    SpamKillLevel=9
    SpamSubjectPrefixStatus=disabled
    SpamSubjectPrefixString=***SPAM*** 
    SpamTag2Level=5
    SpamTagLevel=2.0


RBL server list
---------------

Enable RBL checks, by adding *zen.spamhaus.org* to the RBL server list: ::

    db configuration setprop postfix RblStatus enabled RblServers zen.spamhaus.org
    signal-event nethserver-mail-filter-save
