================
nethserver-samba
================

File and print server for a MS-Windows network based on `Samba
<http://samba.org>`_.


Configuration database
======================

Example: ::

 smb=service
    ...
    Workgroup=
    NetbiosAliasList=
    DeadTime=10080
    WinsServerStatus=disabled
    WinsServerIP=
    UseCups=enabled
    UseClientDriver=yes

* ``Workgroup``
  The old workgroup name or NT-style domain name, depending on the actual
  security mode (see also nethserver-sssd for implementation); if empty use the
  first domain name component from the machine FQDN.

* ``NetbiosAliasList``
  See ``netbios aliases`` parameter in smb.conf(5) manpage.

* ``DeadTime`` (days)
  See ``deadtime`` parameter in smb.conf(5) manpage.

* ``WinsServerStatus``
  if ``enabled`` act as a WINS server.

* ``WinsServerIP`` *ipaddress*
  if ``WinsServerStatus`` is ``disabled``, ``nmbd`` will register with the given
  WINS server. See ``wins server``, ``remote announce``, ``remote browse sync``
  parameters in smb.conf(5) manpage.

* ``UseCups {enabled,disabled}``
  Use cups as printing server.

* ``UseClientDriver {yes,no}``
  See ``use client driver`` parameter in smb.conf(5) manpage.


Accounts database
=================

Only records with type ``ibay``.

Properties:

* ``SmbStatus``
  if ``enabled``, activates ibay sharing through SMB protocol
* ``SmbProfileType`` select the profile template to apply to the share (optional).
    The template path must be placed into ``/etc/e-smith/templates/etc/smb.conf/`` and prefixed by ``ibay-``.
    Eg: ``default`` profile is located at ``/etc/e-smith/templates/etc/smb.conf/ibay-default``.

* ``SmbRecycleBinStatus``: enable or disable the recycle bin; when a file is deleted it is moved inside the recycle bin.
* ``SmbShareBrowseable``: controls the visibility of the shared folder, default is ``enabled``.

Example: ::

 iba1=ibay
    AclRead=domadmins,admin
    AclWrite=domadmins,admin
    Description=test
    GroupAccess=rw
    OtherAccess=r
    OwningGroup=locals
    SmbGuestAccessType=none
    SmbRecycleBinStatus=disabled
    SmbShareBrowseable=enabled
    SmbStatus=enabled

Shared folder profile
=====================

.. note:: Shared folder profile is not related to "Roaming profiles"!

Ibays serve different purposes and ``smb.conf`` provides a lot of parameters to
configure a Samba share. It's difficult to find a combination of parameters that
can fit all the possible requirements.  Thus an ibay configuration adheres to a
*profile*.

An *ibay profile* is a ``smb.conf`` sub-template that expands a cohesive set of
share parameters. Each ibay has ``SmbProfileType`` prop that selects the
template to apply to the ibay. The template path must be placed into
``/etc/e-smith/templates/etc/smb.conf/`` and prefixed by ``ibay-``. Eg:
``default`` profile is located at
``/etc/e-smith/templates/etc/smb.conf/ibay-default``.

The ``default`` profile is applied if the given custom profile is not found.
