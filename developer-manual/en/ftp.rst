===
FTP
===

The FTP module uses the vsftpd daemon. It is accessible only from local network and it is disabled by default.
It supports both virtual and system users, but not at the same time.
All virtual home directories are created inside :file:`/var/lib/nethserver/ftp`.

The daemon will run as ``ftp`` user with passive mode enabled.

Virtual users
=============

Virtual users are enabled by default.

Add a new user
--------------

Create a record inside the accounts db and activate changes: ::
 
  db accounts set <user> ftp status enabled Password <pass> Chroot enabled
  signal-event nethserver-vsftpd-save

The event will generate :file:`/etc/vsftpd/ftpusers.db` (Berkeley db) containing all user credentials. 
The db is used for pam authentication (see: :file:`/etc/pam.d/vsftpd-virtual`).

Properties:

* ``status``: can be ``enabled`` or ``disabled``. If ``enabled``, the user can access the ftp server
* ``Password``: the user password in clear text, can not be blank
* ``Chroot``: can be ``enabled`` or ``disabled``. If ``enabled``, the user will be chrooted to :file:`/var/lib/nethserver/ftp/<user>` directory. 
  If ``disabled`` the user is not chrooted. **ATTENTION**: non-chrooted users can explore the entire file system
* ``ChrootDir``: set a custom ChrootDir, it may be used to chroot a user inside a shared folder

Chroot a user inside a shared folder
------------------------------------

Use these commands: ::

  db accounts set <user> ftp status enabled Password <pass> Chroot enabled ChrootDir /var/lib/nethserver/ibay/<share_name>
  signal-event nethserver-vsftpd-save

Where *share_name* is the name of the share, *user* the username and *pass* the password of the user.

System users
============

.. warning:: This configuration is highly discouraged, because user's password is transmitted in *clear text*

After enabling system users, all virtual users will be disabled. 

Enable system users: ::

  config setprop vsftpd UserType system
  signal-event nethserver-vsftpd-save

Enable an existing system user to access FTP server: ::

  db accounts setprop myuser FTPAccess enabled
  db accounts setprop myuser Shell /bin/bash
  signal-event user-modify myuser

Apply configuration: ::

  signal-event nethserver-vsftpd-save

To disable an already enabled user: ::

  db accounts setprop myuser FTPAccess disabled
  signal-event nethserver-vsftpd-save

If not explicitly disabled, all system users are chrooted inside their home directories. To disable a chroot for a system user: ::

  db accounts setprop myuser FTPChroot disabled
  signal-event nethserver-vsftpd-save


Custom chroot
-------------

When the FTP server uses system users, custom chroot is *not* supported: all users are chrooted inside their own home directory.
Although it's possible to change a system user home directory. Use the command below if the system user will used only for FTP access: ::

 lusermod -d <your_custom_home> <user>
