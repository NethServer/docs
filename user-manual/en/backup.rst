======
Backup
======

The backup contains all the data such as users home directories, 
shared folders, emails but also all the configurations
of the system. It runs daily and may be full or
incremental, depending on day of week and configuration. The
media available for backup are: USB disk, Windows share
and NFS share. At the end of the backup procedure, an email notification will be sent
to the administrator or to a custom address.

General
========

Enable automatic backup
    This option enables or disables the backup procedure. The default is *enabled*.

Schedule backup
    The time when the backup will start. Change the value directly in the field.

Full
    Selecting this option will run a full backup every day of the week

Incremental
    Selecting this option will run a full backup on the day
    selected through the specific field while the rest of
    week will run an incremental backup.

Retention policy
    Input the number of days for which the backup will be stored.

Destination
============

USB Disk
    Select the backup destination to a USB drive. The USB disk must
    be formatted with a compatible file system (ext2/3/4 or FAT, NTFS not supported) and a label configured.

    * Filesystem label: Lists the USB disks connected

Windows Share (CIFS)
    Select the backup destination, a Windows share (CIFS). Authentication is required.

    * Server: The IP address or FQDN of the target Windows server
    * Share: the name of the sahre on the target Windows system
    * User: username to use for authentication
    * Password: password to use for authentication.

NFS Share
    Select the backup destination on an NFS share

Host
   The IP address or FQDN of the NFS server

   * Share: name the NFS share target

Notifications
=============

In case of error
    Send notification only in the event of failure of the backup.

Always
    Always send notifications, if successful or in case of failure.

Never
    You will not get any notification.

Send notification to
    Input who will receive the email notification
   
    * System Administrator: notification of the backup will be sent to the system administrator (admin user)
    * Custom Address: notification of the backup will be sent

