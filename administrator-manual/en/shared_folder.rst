.. _shared_folders-section:

.. index:: shared folder

==============
Shared folders
==============

A *shared folder* is a place where files can be accessed by a group of
people using Samba (SMB/CIFS).


Access privileges
-----------------

If Active directory is selected as authentication provider, a shared folder is owned by a group of users (:guilabel:`Owning
group`). Each member of the group is allowed to read the folder
contents. Optionally the group can be entitled to modify the folder
contents and the read permission can be extended to everyone accessing the
system.  This simple permission model is based on the traditional UNIX
file system permissions. 

Access privileges can be refined further with the `ACL`, allowing individual users and other groups to gain read and write
permissions.

If :guilabel:`Guest access` is enabled, any provided authentication
credentials are considered valid.

If no authentication or OpenLDAP is selected, shared folders doesn't have authentication and everyone is allowed to read and write its content. 

Samba
-----

SMB/CIFS is a widely adopted protocol that allows to share files
across a computer network.  In a way similar to Web URLs above, the
shared folder name becomes the SMB "share name".

For instance, the SMB network addresses of the ``docs`` share could be ::

   \\192.168.1.1\docs
   \\MYSERVER\docs

Compatible SMB clients can be used to set special ACLs on a specific
file or sub-directory. At any time, the :guilabel:`Reset permissions`
button propagate shared folder UNIX and POSIX permissions to subfolders.

If the option :guilabel:`Network recycle bin` is enabled, removed
files are actually moved into a special "wastebasket" directory. The
:guilabel:`Keep homonym files` keeps distinct file names inside
the wastebasket directory, preventing overwrites.

If :guilabel:`Browseable` is enabled, the shared folder is listed publicly. 
This does not affect the permission to use this resource.
