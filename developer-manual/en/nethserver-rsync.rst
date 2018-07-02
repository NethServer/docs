=================
nethserver-rsync
=================

Implement Time machine-style backup engine using ``rsync_tmbackup.sh`` (https://github.com/laurent22/rsync-time-backup),
based on rsync (https://rsync.samba.org/). It can be used as duplicity replacement for standard
backup or as multiple backup.

Retention policy
================

Backup sets are automatically deleted when the disk is getting full.

More info on expiration strategy: https://github.com/laurent22/rsync-time-backup#backup-expiration-logic

Storage backends
================

Supported ``VFSType`` :

* ``usb``
* ``cifs``
* ``nfs``
* ``webdav``: only if used as duplicity replacement in the standard backup
* ``sftp``: FTP over SSH


sftp
----

sFTP: FTP over SSH

Connection to remote host uses a specific public key. A password is needed only once to copy the public key to the remote host.
SSH client configuration is addedd to ``/etc/ssh/sshd_config``.

Properties:

* ``SftpHost``: SSH hostname or IP address
* ``SftpUser``: SSH user
* ``SftpPort``: SSH port
* ``SftpDirectory``: destination directory, must be writable by SSH user

Example: ::

  db backups set t1 rsync status enabled BackupTime '15 7 * * *' CleanupOlderThan default Notify error NotifyFrom '' NotifyTo root@localhost \
  VFSType sftp SftpHost 192.168.1.2 SftpUser root SftpPort 22 SftpDirectory /mnt/t1 
  echo -e "Nethesis,1234" > /tmp/t1-password; signal-event nethserver-backup-data-save t1  /tmp/t1-password

The temporary file containing the password will be deleted at the end of ``nethserver-backup-data-save`` event.

 
Database
========

Example: ::

 t2=rsync
    BackupTime=1 7 * * *
    CleanupOlderThan=1:1 30:7 365:30
    Notify=error
    NotifyFrom=
    NotifyTo=root@localhost
    SMBHost=192.168.1.234
    SMBLogin=test
    SMBPassword=test
    SMBShare=test
    VFSType=cifs
    status=enabled
 t3=rsync
    BackupTime=15 7 * * *
    CleanupOlderThan=default
    NFSHost=192.168.1.234
    NFSShare=/test
    Notify=error
    NotifyFrom=
    NotifyTo=root@localhost
    VFSType=nfs
    status=enabled
 t4=rsync
    BackupTime=15 7 * * *
    CleanupOlderThan=default
    Notify=error
    NotifyFrom=
    NotifyTo=root@localhost
    USBLabel=backup
    VFSType=usb
    status=enabled
 t5=rsync
    BackupTime=*/20 7 * * *
    CleanupOlderThan=default
    Notify=error
    NotifyFrom=
    NotifyTo=root@localhost
    SftpDirectory=/tmp/t5/
    SftpHost=192.168.1.234
    SftpPort=22
    SftpUser=root
    VFSType=sftp
    status=enabled
