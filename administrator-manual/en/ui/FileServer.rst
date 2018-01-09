.. _FileServer-section:

===================
Windows file server
===================

See also :ref:`shared_folders-section`

Workgroup/NetBIOS domain name
    The value can be changed only with LDAP accounts provider and defines the
    Windows workgroup name visible from Network neighborhood panel in 
    Windows systems. With Active Directory accounts provider the value is 
    determined by the joined domain

When a new file or directory is created in a shared folder
    Decide who owns a newly created file or directory: either the resource
    creator or the current owner of the directory containing the new resource 
    (also known as parent directory)

Grant full control on home directories to Domain Admins group (home$ share)
    Allow members of ``Domain Admins`` group to connect the hidden ``home$`` 
    share and grant them administrative access to any home folder inside of it

Grant full control on shared folders to Domain Admins group
    Allow members of ``Domain Admins`` group to connect any shared folder 
    and grant them administrative access on its content
