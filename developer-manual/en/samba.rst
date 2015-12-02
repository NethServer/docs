=====
Samba
=====

Accounts, files and printers server for a MS-Windows network based on "Samba":http://samba.org.

Ibay profiles
=============

.. note:: Ibay profiles are not related to "Roaming profiles"!

Ibays serve different purposes and ``smb.conf`` provides a lot of parameters to configure a Samba share. It's difficult to find a combination of parameters that can fit all the possible requirements.  Thus an ibay configuration adheres to a *profile*. 

An *ibay profile* is a ``smb.conf`` sub-template that expands a cohesive set of share parameters. Each ibay has ``SmbProfileType`` prop that selects the template to apply to the ibay. The template path must be placed into ``/etc/e-smith/templates/etc/smb.conf/`` and prefixed by ``ibay-``. Eg: ``default`` profile is located at ``/etc/e-smith/templates/etc/smb.conf/ibay-default``.

The ``default`` profile is applied if the given custom profile is not found.


Configuration database
----------------------

Properties are saved inside the ``configuration`` database under the ``smb`` key:

* ``ServerRole {WS,PDC,ADS}``
  *WorkStation*, *Primary Domain Controller*, *Active Directory member* (available from version *1.3*) roles.
* ``Workgroup``
  The name of the Domain for ``PDC`` and ``ADS`` roles; if empty use the first domain name component from ``DomainName`` key (uppercase). When ``ServerRole=WS`` the default value from Samba is used (i.e. ``WORKGROUP``).
* ``AdsRealm``
  The name of the Kerberos realm of the Active Directory domain. If empty, use ``DomainName`` key value (uppercase).
* ``DeadTime`` (days)
  See ``deadtime`` parameter in smb.conf(5) manpage.
* ``LogonDrive [A-Z]:``
  if empty, falls back on ``Z:``. See ``logon drive`` parameter in smb.conf(5) manpage.
* ``RoamingProfiles {yes,no}``
  enables "Windows roaming profiles":http://wiki.samba.org/index.php/Samba*%26*Windows*Profiles.
* ``WinsServerStatus``
  if ``enabled`` act as a WINS server.
* ``WinsServerIP`` *ipaddress*
  if ``WinsServerStatus`` is ``disabled``, ``nmbd`` will register with the given WINS server. See ``wins server``, ``remote announce``, ``remote browse sync`` parameters in smb.conf(5) manpage.
* ``UseCups {enabled,disabled}``
  Use cups as printing server.
* ``UseClientDriver {yes,no}``
  See ``use client driver`` parameter in smb.conf(5) manpage.
* ``NetbiosAliasList``
  See ``netbios aliases`` parameter in smb.conf(5) manpage.


Example: ::

 smb=service
    ...
    Workgroup=
    AdsRealm=
    ServerRole=WS
    DeadTime=10080
    LogonDrive=
    RoamingProfiles=no
    WinsServerStatus=disabled
    WinsServerIP=
    UseCups=enabled
    UseClientDriver=yes    
    NetbiosAliasList=



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
    HttpStatus=disabled
    OtherAccess=r
    OwningGroup=locals
    SmbGuestAccessType=none
    SmbRecycleBinStatus=disabled
    SmbShareBrowseable=enabled
    SmbStatus=enabled


Active Directory domain member
==============================

The *Active Directory member* role integrates AD users and groups into the system, through the ``winbind`` ``nsswitch`` module and provides some configuration hooks that other packages (i.e. [[nethserver-mail-server]]) can use to authenticate themselves through the "Kerberos protocol":http://en.wikipedia.org/wiki/Kerberos*(protocol).

Join the AD domain
------------------

This is the environment where I tested the AD join

* *NethServer 6.x*
  host name ``nsrv2.ads1.tld``
* *Windows Sever 2008 R2 Standard* 
  host name ``w2k8-ad.ads1.tld``
  domain ``NSRV1``
  realm ``ADS1.TLD``
  IP address ``192.168.88.1``
* *Windows XP Professional 5.1 (2600) SP2*
  Thunderbird 10 ESR client


**Example: Server-manager graphical interface procedure (provided that ``nethserver-hosts`` and ``nethserver-ntp`` packages are installed)**

* Point your browser to the server-manager URL, here ``https://nsrv2.ads1.tld:980``
* Authenticate as ``admin``
* In ``DNS & DHCP > DNS > Configure`` set ``192.168.88.1`` as primary DNS server
* Set ``pool.ntp.org`` as timesource on AD. I followed the instructions about "Windows Time Service":http://support.ntp.org/bin/view/Support/WindowsTimeService, from *support.ntp.org*. It seems that *after* setting the external time source, AD works as NTP server as well.
* Back on server-manager, in ``Date and Time`` set ``pool.ntp.org``, or the AD itself, ``192.168.88.1``, as NTP server
* In ``Windows Network`` select ``Active Directory member`` role and fill required fields

**Example: Command line procedure**

* Login as ``root`` into ``nsrv2``.

* AD must be the DNS server: it contains ``SRV`` records necessary to the LDAP/Kerberos infrastructure. Set the AD controller as DNS name server: ::

   rpm -q nethserver-hosts || yum install nethserver-hosts   
   config setprop dns NameServers 192.168.88.1
   signal-event nethserver-hosts-update

* AD Kerberos usually requires that the difference between machine clocks is less than 5 minutes; -unfortunately upstream ``ntpd`` still does not support ``MSNTP`` authentication, thus we must configure both AD and NethServer to synchronize with an external time source: ``pool.ntp.org``. 

  For NethServer type: ::

    rpm -q nethserver-ntp || yum install nethserver-ntp
    config setprop ntpd status enabled NTPServer pool.ntp.org
    signal-event nethserver-ntp-save

* To set ``pool.ntp.org`` as timesource on AD I followed the instructions about "Windows Time Service":http://support.ntp.org/bin/view/Support/WindowsTimeService, from *support.ntp.org*.

* Now you're ready to join AD domain. If you're on a tty, ``nethserver-samba-adsjoin`` event will ask for ``administrator``'s password interactively, otherwise it will read the given file contents (``/tmp/dummy`` here). ::

    config setprop smb Workgroup NSRV1 AdsRealm ADS1.TLD ServerRole ADS
    signal-event nethserver-samba-save
    touch /tmp/dummy
    signal-event nethserver-samba-adsjoin -u administrator -F /tmp/dummy join

    Enter administrator's password: <enter password 1st time>
    Enter administrator's password: <enter password 2nd time>
    rm /tmp/dummy

Test if the join is OK with the following command: ::

   net -k ads testjoin

Join is OK ::
  
   getent passwd

   <the output is the list of system users: it must contain also users from AD user database>

Role description
^^^^^^^^^^^^^^^^

When playing the *Active Directory member* role, some major changes happen on the system:

* Users and groups from AD become available, through the ``winbind`` ``nsswitch`` module: ::
    getent passwd
    <user list output>
    getent group
    <group list output>

* The system Kerberos keytab ``/etc/krb5.keytab`` is initialized and credentials are exported to each *registered service* keytab, respecting path and permissions requirements 
* Every hour a cronjob tests Kerberos TGTs for registered services, and renews any ticket that will soon expire
* Every month a cronjob "changes the machine password":http://blogs.technet.com/b/askds/archive/2009/02/15/test2.aspx, and keeps Kerberos keytab files for registered services updated with the new machine credentials

Service configuration hooks
^^^^^^^^^^^^^^^^^^^^^^^^^^^

A service (i.e. *dovecot*) record in ``configuration`` DB can be extended with the following special props, that are read during the join operation, machine password renewal, and crojob tasks: ::

 dovecot=service
    ...    
    KrbStatus=enabled
    KrbCredentialsCachePath=
    KrbKeytabPath=/var/lib/dovecot/krb5.keytab
    KrbPrimaryList=smtp,imap,pop
    KrbKeytabOwner=
    KrbKeytabPerms=

* ``KrbStatus {enabled,disabled}``
  This is the main switch. If set to ``enabled`` a ticket credential cache file is kept valid by the hourly cronjob
* ``KrbCredentialsCachePath``
  The path of the credentials cache. It defaults to ``/tmp/krb5cc*<service*uid>``, if ``service`` is also a system user.
* ``KrbKeytabPath``
  Keytab file path. If empty, ``/var/lib/misc/nsrv-<service>.keytab`` is assumed
* ``KrbPrimaryList <comma separated words list>``
  Defines the keytab contents. In Kerberos jargon a "primary" is the first part of the "principal":http://web.mit.edu/kerberos/krb5-1.5/krb5-1.5.4/doc/krb5-user/What-is-a-Kerberos-Principal*003f.html string, before the slash (``/``) character. Any primary in this list is exported to the keytab.
* ``KrbKeytabOwner``
  The unix file owner. Default is the ``service`` name. This is applied to both the credentials cache file and the keytab file.
* ``KrbKeytabPerms``
  The unix bit permissions in octal form. Default is ``0400``. This is applied to both the credentials cache file and the keytab file.

The implementation is provided by source:nethserver-samba|root/usr/libexec/nethserver/smbads

Troubleshooting
^^^^^^^^^^^^^^^

# *CHECK* clock difference between NethServer and AD DC less than 5 minutes
# *CHECK* NethServer uses *only* DC as DNS

Samba join status
~~~~~~~~~~~~~~~~~

Commands:

* net ads info
* net ads testjoin

Does NSS/Winbind list AD users?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Use: ::

  getent passwd

Does Dovecot see AD users?
~~~~~~~~~~~~~~~~~~~~~~~~~~

Use: ::

  doveadm user \*

Can I obtain Kerberos TGT?
~~~~~~~~~~~~~~~~~~~~~~~~~~

* Using keytab: ::

    kinit -t /etc/krb5.keytab -k '<SERVERNAME>$'

* If keytab does not work, providing the secret machine password, stored in ``secrets.tdb``, without the trailing NULL character: ::

   tdbdump /var/lib/samba/private/secrets.tdb | grep -A 1 SECRETS/MACHINE*PASSWORD
   kinit '<SERVERNAME>$'


Changing hostname
=================

A new machine SID is generated when the server is in ``WS`` role and *hostname* changes. The SID is stored in ``secrets.tdb`` and in a new LDAP entry. When ``PDC`` role is then selected, one of the following scenarios applies:

* if the domain (workgroup) *was not* previously created , a new ``sambaDomain`` entry is generated with the same SID of the new hostname;
* if the workgroup was previously created, the old domain entry (and SID) is retained. In this scenario new user accounts retain the old workgroup SID.

In other words, a new SID seems to be generated from hostname only. This differs from the official Samba documentation.

"Security identifiers (SIDs)" section in "Updating Samba-3":http://www.samba.org/samba/docs/man/Samba-Guide/upgrades.html states about SIDs:

  The SID is generated in a nondeterminative manner. 
  This means that each time it is generated for a particular combination of machine name (hostname) and domain name (workgroup), it will be different.
