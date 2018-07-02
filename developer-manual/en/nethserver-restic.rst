=================
nethserver-restic
=================

Implement backup enginge using restic (https://restic.net/), it can be used as duplicity replacement for standard
backup or as multiple backup.

Storage backends
================

Supported ``VFSType`` :

* ``usb``
* ``cifs``
* ``nfs``
* ``webdav``: only if used as duplicity replacement in the standard backup
* ``s3``: Amazon S3 (or compatibile server like Minio)
* ``sftp``: FTP over SSH
* ``b2``: BackBlaze B2
* ``rest``: Restic REST server


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

  db backups set t1 restic status enabled BackupTime '15 7 * * *' CleanupOlderThan 30D Notify error NotifyFrom '' NotifyTo root@localhost \
  VFSType sftp SftpHost 192.168.1.2 SftpUser root SftpPort 22 SftpDirectory /mnt/t1 
  echo -e "Nethesis,1234" > /tmp/t1-password; signal-event nethserver-backup-data-save t1  /tmp/t1-password

The temporary file containing the password will be deleted at the end of ``nethserver-backup-data-save`` event.

s3
--

Amazon S3 (https://aws.amazon.com/s3/) compatibile (like https://www.minio.io/).

Properties

* ``S3AccessKey``: user access key
* ``S3Bucket``: bucket (directory) name
* ``S3Host``: S3 host, use s3.amazonaws.com for Amazon
* ``S3SecretKey``: secret access key

Example: ::

  db backupst set t1 restic VFSType s3 BackupTime '15 7 * * *' CleanupOlderThan never Notify error NotifyFrom '' NotifyTo root@localhost status enabled \
  S3AccessKey XXXXXXXXXXXXXXXXXXXX S3Bucket restic-demo S3Host s3.amazonaws.com S3SecretKey xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx status enabled
  signal-event nethserver-backup-data-save t1


How to setup Amazon S3 access keys: https://restic.readthedocs.io/en/stable/080_examples.html


b2
--

Backblaze B2 (https://www.backblaze.com/b2/cloud-storage.html)

Properties:

* ``B2AccountId``: B2 account name
* ``B2AccountKey``: B2 account secret key
* ``B2Bucket``: B2 bucker (directory)

Example: ::
  
  db backupst set t1 restic VFSType b2 BackupTime '15 7 * * *' CleanupOlderThan never Notify error NotifyFrom '' NotifyTo root@localhost status enabled \
  B2AccountId B2AccountId xxxxxxxxxxxx B2AccountKey xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx 2Bucket restic-demo 
  signal-event nethserver-backup-data-save t1


Rest
----

Restic REST server (https://github.com/restic/rest-server)

Properties:

* ``RestDirectory``: destination directory
* ``RestHost``: REST server hostname or IP address
* ``RestPort``: REST srver port (default for server is 8000)
* ``RestProtocol``: REST protocol, can be ``http`` or ``https``
* ``RestUser``: user for authentication (optional)
* ``RestPassword``: password for authentication (optional)


Example: ::

  db backupst set t1 restic VFSType rest BackupTime '15 7 * * *' CleanupOlderThan never Notify error NotifyFrom '' NotifyTo root@localhost status enabled \
  RestDirectory t1 RestHost 192.168.1.2 RestPassword mypass RestPort 8000 RestProtocol http RestUser myuser
  signal-event nethserver-backup-data-save t1


 
Database
========

Example: ::

 t2=restic
    BackupTime=1 7 * * *
    CleanupOlderThan=never
    Notify=error
    NotifyFrom=
    NotifyTo=root@localhost
    SMBHost=192.168.1.234
    SMBLogin=test
    SMBPassword=test
    SMBShare=test
    VFSType=cifs
    status=enabled
 t3=restic
    BackupTime=15 7 * * *
    CleanupOlderThan=never
    NFSHost=192.168.1.234
    NFSShare=/test
    Notify=error
    NotifyFrom=
    NotifyTo=root@localhost
    VFSType=nfs
    status=enabled
 t4=restic
    BackupTime=15 7 * * *
    CleanupOlderThan=10D
    Notify=error
    NotifyFrom=
    NotifyTo=root@localhost
    USBLabel=backup
    VFSType=usb
    status=enabled
 t5=restic
    BackupTime=*/20 7 * * *
    CleanupOlderThan=10D
    Notify=error
    NotifyFrom=
    NotifyTo=root@localhost
    SftpDirectory=/tmp/t5/
    SftpHost=192.168.1.234
    SftpPort=22
    SftpUser=root
    VFSType=sftp
    status=enabled
 t6=restic
    BackupTime=15 7 * * *
    CleanupOlderThan=10D
    Notify=error
    NotifyFrom=
    NotifyTo=root@localhost
    S3AccessKey=XXXXXXXXXXXXXXXXXXXX
    S3Bucket=restic-demo
    S3Host=s3.amazonaws.com
    S3SecretKey=xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    VFSType=s3
    status=enabled
 t7=restic
    B2AccountId=xxxxxxxxxxxx
    B2AccountKey=xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
    B2Bucket=restic-demo
    BackupTime=15 7 * * *
    CleanupOlderThan=11D
    Notify=error
    NotifyFrom=
    NotifyTo=root@localhost
    VFSType=b2
    status=enabled
 t8=restic
    BackupTime=15 7 * * *
    CleanupOlderThan=10D
    Notify=error
    NotifyFrom=
    NotifyTo=root@localhost
    RestDirectory=t8
    RestHost=localhost
    RestPassword=test
    RestPort=8000
    RestProtocol=http
    RestUser=test
    VFSType=rest
    status=enabled

REST server
===========

To manually install the REST server, download it from https://github.com/restic/rest-server/releases and save it 
under ``/usr/local/bin/rest-server``, example Linux 64bit: ::

  R=0.9.7; wget https://github.com/restic/rest-server/releases/download/v$R/rest-server-$R-linux-amd64.gz -O - | zcat > /usr/local/bin/rest-server
  chmod a+x /usr/local/bin/rest-server

Then configure it for NethServer: ::

  wget https://raw.githubusercontent.com/restic/rest-server/master/examples/systemd/rest-server.service -O - | sed 's/www\-data/apache/g' > /etc/systemd/system/rest-server.service
  systemctl daemon-reload
  systemctl start rest-server
  systemctl enable rest-server
  config set rest-server service TCPPort 8000 access green status enabled
  signal-event firewall-adjust

