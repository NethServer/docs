===================
nethserver-yum-cron
===================

nethserver-yum-cron configures yum-cron package.
The cron job runs each night with a random time before to start of 6 hours for NS7 and 60 minutes for NS6.
You can decide who receive the notifications (default is root), which updates to do, if you just check, download, or install automatically the updates.

Original author: Stephane de Labrusse (@stephdl)

Branches:

- ns6: code for NethServer 6
- master: code for NethServer 7

Database
========

(Only for NS 7)

Properties:

- ``applyUpdate``: can be ``yes`` or ``no``. If set to ``yes``, downloaded updates will be installed
- ``customMail``: comma-separated list of extra mail recipients, as default a mail will be sent to root
- ``download``: can be ``yes`` or ``no``. If set to ``yes``, download new package updates
- ``messages``: can be ``yes`` or ``no``. Whether a message should be emitted when updates are available
- ``randomWait``: random number of minutes to wait before executing the download procedure
  - NS6: 1 to 60 minutes
  - NS7: 1 to 360 minutes, negative and the job start immediately
- ``status``: can be ``enabled`` or ``disabled``. When enabled, a cron script will search for package updates

Database example: ::

 yum-cron=service
    applyUpdate=yes
    customMail=
    download=no
    messages=no
    randomWait=360
    status=enabled

