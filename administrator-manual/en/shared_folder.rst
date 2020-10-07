.. index:: shared folder

.. _shared_folders-section:

==============
Shared folders
==============

A *shared folder* is a place where files can be accessed by a group of
people using Samba (SMB/CIFS).

Shared folder are part of the File server application in the new Server Manager.
The application dashboard now integrates the Samba status module, which displays shared folder usage in real time.

To create, edit and delete a shared folder go to the :guilabel:`Shared folders`
page.

.. _shared_folders_requirements-section:

Requirements
============

Shared folders use ACL (Access Control List) to provide flexible permission on files
and directories.

To enable ACL, the filesystem must be mounted with the ``acl`` option.
The ``acl`` option is already enabled on ``XFS``, the default CentOS filesystem,
and usually even on ``Ext3`` and ``Ext4`` filesystems.

Enabling ACL
------------

On Ext2/3/4 filesystems, use ``tune2fs`` command to check if ``acl`` option is already enabled: ::

  tune2fs -l /dev/sdXY | grep "Default mount options:"

Where ``sdXY`` is the name of your partition, the output should look like this: ::

  Default mount options:    user_xattr acl

If the ``acl`` option is not enabled, add the option inside the :file:`/etc/fstab`: ::

  /dev/mapper/VolGroup-lv_root /                       ext4     defaults,acl        0

Or use ``tune2fs`` to enable as default mount option: ::

  tune2fs -o acl /dev/sdXY



.. _smb-auth-section:

Authorizations
==============

If **Active directory** is selected as account provider, a shared folder is
owned by a group of users (:guilabel:`Owning group`). Each member of the group
is allowed to read the folder contents. Optionally the group can be entitled to
modify the folder contents and the read permission can be extended to everyone
accessing the system.  This simple permission model is based on the traditional
UNIX file system permissions. 

Access privileges can be refined further with the :guilabel:`ACL` tab, allowing
individual users and other groups to gain read and write permissions.

ACLs can also be set on individual files and directories from a Windows client,
if the user has enough permissions -- see section  :ref:`smb-perms-section` for
details.

.. warning::

  Some ACLs settings supported by Windows clients cannot be translated to POSIX
  ACLs supported by |product|, thus they will be lost when they are applied

At any time, the :guilabel:`Reset permissions` button propagates the shared
folder UNIX permissions and POSIX ACLs to its contents.

If :guilabel:`Guest access` is enabled, any provided authentication
credentials are considered valid.

If an **LDAP** account provider is selected or there is no account provider at
all, any access to shared folders is considered as *Guest access* so that
everyone is allowed to read and write its content. 

.. _smb-access-section:

Network access
==============

SMB/CIFS is a widely adopted protocol that allows to share files
across a computer network. The shared folder name becomes the SMB "share name".

For instance, the SMB network addresses of the ``docs`` share could be ::

   \\192.168.1.1\docs
   \\MYSERVER\docs

.. warning::

  Authenticated access to shared folders is available with an Active Directory
  accounts provider. LDAP provider allows guest access only.

When accessing a SMB share, some user interfaces provide a single user name
field. In that case, specify the **user short name** prefixed with the **NetBIOS
domain name**.  For instance, if the NetBIOS domain name is "DOMAIN" and the
user name is "john.smith", the domain-prefixed user name to access a SMB share
is: ::

    DOMAIN\john.smith

On the contrary, some applications provide separate input fields for the NetBIOS
domain name and the user name; in that case fill in the input fields
individually.

Network recycle bin
===================

If the option :guilabel:`Network recycle bin` is enabled, removed
files are actually moved into a special "wastebasket" directory. The
:guilabel:`Keep copies of files with the same name` keeps distinct file names inside
the wastebasket directory, preventing overwrites.

Hide a shared folder
====================

If :guilabel:`Browseable` is enabled, the shared folder is listed publicly. 
This does not affect the permission to use this resource.


Home share
==========

Each |product| user has a personal shared folder that is mapped to his Unix home
directory. The SMB share name correspond to the **user short name**. For example:

* user short name ``john.smith``
* server name ``MYSERVER``
* server address ``192.168.1.2``

The SMB network address is: ::

 \\MYSERVER\john.smith
 \\192.168.1.2\john.smith

Provide John's credentials as explained in :ref:`smb-access-section`.

.. tip::

    The Unix home directory is created the first time the user accesses it by
    either SMB or SFTP/SSH protocol.

.. _smb-perms-section:

Change resource permissions from Windows clients
================================================

When an user connects to a shared folder with a Windows client, he can change
permissions on individual files and directories. Permissions are expressed by
Access Control Lists (ACLs).

.. warning::

  Some ACLs settings supported by Windows clients cannot be translated to POSIX
  ACLs implemented by |product|, thus they will be lost when they are applied

Only the owner of a resource (being it either file or directory) has full
control over it (read, write, change permissions). The permission to delete a
resource is granted to users with write permissions on the parent directory. The
only exception to this rule is described in the :ref:`smb-admins-section`
section.

When a new resource is created, the owner can be defined by one of the following
rules:

* the owner is the user that creates the resource
* the owner is inherited from the parent directory

To enforce one of those rules, go to :ref:`FileServer-section` page and select
the corresponding radio button under :guilabel:`When a new file or directory is
created in a shared folder` section.

.. warning::
    
    The :guilabel:`Owning group` setting of a shared folder does not affect the
    owner of a resource. See also the :ref:`smb-auth-section` section above

.. _smb-admins-section:

Administrative access
=====================

The :ref:`FileServer-section` page allows to grant special privileges to
members of the ``Domain Admins`` group:

* extend the owner permission by enabling the :guilabel:`Grant
  full control on shared folders to Domain Admins group` checkbox

* access other users' home directories by enabling the
  :guilabel:`Grant full control on home directories to Domain Admins group
  (home$ share)` checkbox. To access home directories connect to the hidden
  share ``home$``. For instance, the SMB network address is: ::

    \\MYSERVER\home$
    \\192.168.1.2\home$

Auditing
========

.. note:: The audit module has been integrated inside the File server application of the new Server Manager.

Samba audit is a module that keeps track of all users activities on shared folders.
Auditing is disabled by default and must be explicitly enabled for each folder.

Actions are logged to a file during the the day and are moved to a browseable database overnight.
By default, to avoid the database overloading, read actions like access to files and directories are saved only inside :file:`/var/log/smbaudit.log`.
To change this behavior and store read actions inside the database, access the :guilabel:`Settings` page and enable the :guilabel:`Enable auditing of read actions`.

The auditing report is available under the :guilabel:`Audit` page.

The same report is also available from the old Server Manager inside the :guilabel:`Applications` page.
