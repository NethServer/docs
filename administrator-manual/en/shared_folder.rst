.. _shared_folders-section:

.. index:: shared folder
   single: HTTP
   single: SMB
   single: CIFS

==============
Shared folders
==============

A *shared folder* is a place where files can be accessed by a group of
people using different methods, or *protocols*.  Since |product| is a
modular system, the actual methods depends on what modules have been
installed.

The available methods/protocols are:

* Web access (HTTP)
* Samba (SMB/CIFS)

Access privileges
-----------------

A shared folder is always owned by a group of users (:guilabel:`Owning
group`). Each member of the group is allowed to read the folder
contents. Optionally the group can be entitled to modify the folder
contents and the read permission can be extended to everyone accessing the
system.  This simple permission model is based on the traditional UNIX
file system permissions. 

Access privileges can be refined further with the :guilabel:`ACL` tab,
allowing individual users and other groups to gain read and write
permissions.  This extended permission model is based on the POSIX ACL
specification.


Web access
----------

The :guilabel:`Web access` method allows the connection of a web
browser to a shared folder using the HTTP protocol.  Web resources
are identified by a string, the Uniform Resource Locator, or URL.

For instance, if ``docs`` is the name of the shared folder, the URLs
that allow the access to it could be: ::

    http://192.168.1.1/docs
    https://192.168.1.1/docs
    http://myserver/docs
    http://www.domain.com/docs
    http://docs.domain.com/

Each URL has three components:

* protocol (``http://`` or ``https://``),
* host name (``192.168.1.1``, ``myserver``, ``www.domain.com``),
* path (``docs``).

The :guilabel:`Web address` radio group defines the "path"
component. 

* :guilabel:`Folder name` is the default, the same as the shared
  folder name, as ``docs`` in the example above.

* :guilabel:`Web site root` means no path at all. For instance
  ``http://docs.domain.com``.

* :guilabel:`Custom` means an alternative name, to be detailed.

The :guilabel:`Virtual host` selector lists all :guilabel:`Server
alias` defined under the :guilabel:`DNS` page. "Any" means the host
part is not considered to map the URL to the shared folder.

The web access is anonymous and read-only. There are some options that
can be tweaked to restrict the access.

* :guilabel:`Allow access from trusted networks only`, restricts the
  access by looking at the IP address of the client,

* :guilabel:`Protect by password`, requires an unique password to gain read access (to be specified here),

* :guilabel:`Require SSL encrypted connection`.


Configuring a web application
-----------------------------

The :guilabel:`Allow .htaccess and write permissions overrides`
check box activates a special Apache configuration designed to host a
simple web application on a shared folder.  It allows overriding the
default Apache configuration and grants Apache the write permissions
on specific sub-directories.

.. warning:: If a shared folder contains executable code, such as PHP
             scripts, user permissions and security implications must
             be evaluated carefully.

If the check box is enabled 

* any file named :file:`.htaccess` is loaded as `configuration for
  Apache <http://httpd.apache.org/docs/2.2/howto/htaccess.html>`_.

* a text file named :file:`.htwritable` positioned in the root level of the
  shared folder may contain a list of sub-directories where Apache is
  granted write permission.  The syntax of the file is one
  sub-directory for each line.  Lines beginning with ``#`` are
  comments.  When the content of :file:`.htwritable` changes, the
  :guilabel:`Reset permission` button must be pressed again to
  propagate the file system permissions.

.. note:: Shared folders are a powerful tool but are not meant to be a
          complete web hosting solution! For advanced Apache and
          virtual host setups drop a ``.conf`` file under the
          :file:`/etc/httpd/conf.d/` directory. Refer to the official
          Apache documentation for this.


Samba
-----

SMB/CIFS is a widley adopted protocol that allows to share files
across a computer network.  In a way similar to Web URLs above, the
shared folder name becomes the SMB "share name".

For instance, the SMB network addresses of the ``docs`` share could be ::

   \\192.168.1.1\docs
   \\MYSERVER\docs

Compatible SMB clients can be used to set special ACLs on a specific
file or sub-directory. At any time, the :guilabel:`Reset permissions`
button restores UNIX and POSIX permissions according to what is defined
in the :guilabel:`General` and :guilabel:`ACL` pages.

If the option :guilabel:`Network recycle bin` is enabled, removed
files are actually moved into a special "wastebasket" directory. The
:guilabel:`Keep omonym files` keeps distinct file names inside
the wastebasket directory, preventing overwrites.

If :guilabel:`Guest access` is enabled, any provided authentication
credentials are considered valid.

