===
VPN
===

VPN implementation is splitted into various packages:

* nethserver-vpn: general package containing common code for various VPN types, including certificate management
* nethserver-openvpn: OpenVPN implementation
* nethserver-ipsec: IPsec implementation

Certificates
============

All certificates are signed using NethServer default RSA key (``/etc/pki/tls/private/NSRV.key``).

CA environment
--------------

CA configuration is stored inside ``/var/lib/nethserver/`` directory, all certificates are stored inside ``/var/lib/nethserver/certs``. The ``nethserver-openvpn-conf`` action creates:

* ``serial``, ``certindex.attr`` and ``/certindex``: database of valid and revocated certificates
* ``crlnumber`` and ``/etc/openvpn/certs/crl.pem``: certificate revocation list
* ``dh1024.pem``: key for TLS negotation


Certificate creation
--------------------

Certificates in PEM format can be created using the command: ::

  /usr/libexec/nethserver/pki-vpn-gencert <commonName>

The ``commonName`` parameter is an unique name stored inside the certificate. 
The command will generate ``key``, ``crt`` and ``csr`` file.
Each generated certificate is referred with a numeric id and saved inside ``certindex`` database. OpenSSL will also create a certificated called as with the generated id (eg. ``02.pem``). 

Certificate revocation
----------------------

Certificate revocation is done via the command: ::

    /usr/libexec/nethserver/pki-vpn-revoke [-d] <commonName>

The ``commonName`` parameter is an unique name stored inside the certificate. 
If '-d' option is enabled, also delete ``crt``, ``csr``, ``pem`` and key files

Certificate renew
-----------------

All certificates will expire after ``X`` days, where ``X`` is the value of ``CertificateDuration`` property inside ``pki`` key.
Renew is done via the command: ::

  /usr/libexec/nethserver/pki-vpn-renew <commonName>

The ``commonName`` parameter is an unique name stored inside the certificate. 

Accounts
========

Accounts are used to identify clients connecting to the server itself. There are two types of account:

* user account: system user with ``VPNClientAccess`` set to ``yes``
* vpn-only account: simple account with only vpn access

Each account can be used in a roadwarrior connection (host to net). 
If a net to net tunnel (OpenVPN only) is needed, ``VPNRemoteNetwork`` and ``VPNRemoteNetmask`` 
properties must be set to inform the server about remote routes.
When a new account is created, a certificate with same name is generated inside ``/var/lib/nethserver/certs`` directory.

Properties:

* ``VPNRemoteNetwork``: remote network
* ``VPNRemoteNetmask``: remote netmask

Database reference
------------------

Database: ``accounts``

::

 <name>=vpn
    VPNRemoteNetwork=
    VPNRemoteNetmask=

 <name>=user
    ...
    VPNRemoteNetwork=
    VPNRemoteNetmask=
    VPNClientAccess=yes

Clients (OpenVPN)
=================

OpenVPN clients are used to connect the server with other network, typically to create a net 2 net tunnel. 

Common properties:

* ``AuthMode``: default value is ``certificate``. Possible values:
  * ``certificate``: use x509 certificate. Certificates, including CA and private key, are saved in ``/var/lib/nethserver/certs/clients`` directory in a PEM file named ``key``.pem
  * ``password``: use username and password
  * ``password-certificate``: use username, password and a valid x509 certificate
  * ``psk``: use a pre-shared key
* ``User``: username used for authentication, if ``AuthMode`` is ``password`` or ``password-certificate``
* ``Password``: password used for authentication, if ``AuthMode`` is ``password`` or ``password-certificate``
* ``Psk``: pre-shared key user for authentication, if ``AuthMode`` is ``psk``. Pre-shared key is saved ``/var/lib/nethserver/certs/clients/<name>.key`` 
* ``RemoteHost``: remote server hostname or ip address
* ``RemotePort``: remote host port
* ``VPNType``: VPN type, can be ``openvpn`` or ``ipsec``
* ``VPNRemoteNetwork``: remote network (behind remote firewall), used for a net to net tunnel
* ``VPNRemoteNetmask``: remote netmask, used for a net to net tunnel
* ``Compression``: can be ``enabled`` or ``disabled``, default is ``enabled``. Enable/disable adaptive LZO compression.


Database reference
------------------

Database: ``vpn``

::

 t1=tunnel
    Mode=routed
    AuthMode=certificate
    Crt=
    Psk=
    Password=
    RemoteHost=1.2.3.4
    RemotePort=1234
    User=
    VPNType=openvpn
    VPNRemoteNetmask=255.255.255.0
    VPNRemoteNetwork=192.168.4.0
    Compression=enabled


Events
======

* ``nethserver-vpn-create``: fired when a new account is created, takes the account name as argument
* ``nethserver-vpn-delete``: fired when a new account is deleted, takes the account name as argument
* ``nethserver-vpn-modify``: fired when a new account is modified, takes the account name as argument
* ``nethserver-vpn-save``: fired when a +client+ is created, modified or deleted



