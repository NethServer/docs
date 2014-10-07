.. _mail_filter-section:

===========
Mail filter
===========

Mail Filter enforces anti-spam and anti-virus checks on any message entering the system.

Package: nethserver-mail-filter

Features

* Anti-spam
* Anti-virus
* Attachment block
* Real-time Blackhole List (RBL) (disabled)
* Greylisting (by ``nethserver-mail-greylisting`` package)
* Sender Policy Framework (SPF) (disabled)
* Customized spam threshold 
* Sender WBL, Recipient whitelist 

RBL server list
===============

Enable RBL checks, by adding *zen.spamhaus.org* to the RBL server list: ::

  db configuration setprop postfix RblStatus enabled RblServers zen.spamhaus.org
  signal-event nethserver-mail-filter-save


Reference
==========

Database values and feature setups

Configuration database
----------------------

Properties: 

* ``ContentInspectionType {default,amavisd-before-queue}``:

  *  ``default``, apply the default content inspection type, depending on what packages are installed. ``nethserver-mail-filter`` changes the default to ``amavisd-before-queue``
  * ``amavisd-before-queue``, executes anti-spam and anti-virus checks on open SMTP connections. Only CLEAN messages are allowed to enter the postfix queue


Example: ::

 amavisd=service
    ...
    MaxProcesses=4
    SpamTagLevel=2.0
    SpamTag2Level=6.2
    SpamKillLevel=6.9
    SpamSubjectPrefixStatus=enabled
    SpamSubjectPrefixString=[SPAM] 
    SenderWhiteList=good1``green.tld,good2``green.tld,whiteguys.tld
    SenderBlackList=bad``spammers.org,blackguys.tld
    RecipientWhiteList=user01``domain.tld,info``domain.tld
    BlockAttachmentClassList=Arch,Exec
    BlockAttachmentCustomList=doc,pdf,xls
    BlockAttachmentCustomStatus=enabled
    BlockAttachmentStatus=enabled
    AdminNotificationStatus=disabled
    SaLearnGroup=salearn
    

 postfix=service
    ...
    RblStatus=disabled
    RblServers=host1,host2.. 
    SpfStatus=disabled
    ContentInspectionType=amavisd-before-queue

