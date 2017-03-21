.. index:: shared folder

.. _shared_folders-section:

==============
Shared folders
==============

A *shared folder* is a place where files can be accessed by a group of
people using Samba (SMB/CIFS).

To create, edit and delete a shared folder go to the :guilabel:`Shared folders`
page.

Authorizations
--------------

If **Active directory** is selected as account provider, a shared folder is
owned by a group of users (:guilabel:`Owning group`). Each member of the group
is allowed to read the folder contents. Optionally the group can be entitled to
modify the folder contents and the read permission can be extended to everyone
accessing the system.  This simple permission model is based on the traditional
UNIX file system permissions. 

Access privileges can be refined further with the :guilabel:`ACL` tab, allowing
individual users and other groups to gain read and write permissions.

If :guilabel:`Guest access` is enabled, any provided authentication
credentials are considered valid.

If an **LDAP** account provider is selected or there is no account provider at
all, any access to shared folders is considered as *Guest access* so that
everyone is allowed to read and write its content. 

.. _smb-access-section:

Network access
--------------

SMB/CIFS is a widely adopted protocol that allows to share files
across a computer network. The shared folder name becomes the SMB "share name".

For instance, the SMB network addresses of the ``docs`` share could be ::

   \\192.168.1.1\docs
   \\MYSERVER\docs

When accessing a SMB share, some user interfaces provide a single user name
field. In that case, specify the **short user name** prefixed with the **NetBIOS
domain name**.  For instance, if the NetBIOS domain name is "COMPANY" and the
user name is "john.smith", the domain-prefixed user name to access a SMB share
is: ::

    COMPANY\john.smith

On the contrary, some applications provide separate input fields for the NetBIOS
domain name and the user name; in that case fill in the input fields
individually.

At any time, the :guilabel:`Reset permissions` button propagates the shared
folder UNIX permissions and Posix ACLs to its contents.

.. warning: 

    Compatible SMB clients can be used to set special ACLs on a specific file or
    sub-directory only if the File server is configured with Kerberos authentication.

If the option :guilabel:`Network recycle bin` is enabled, removed
files are actually moved into a special "wastebasket" directory. The
:guilabel:`Keep copies of files with the same name` keeps distinct file names inside
the wastebasket directory, preventing overwrites.

If :guilabel:`Browseable` is enabled, the shared folder is listed publicly. 
This does not affect the permission to use this resource.
