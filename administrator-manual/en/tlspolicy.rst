.. _tlspolicy-section:

==========
TLS policy
==========

The :guilabel:`TLS policy` page controls how individual services configure the
Transport Layer Security (TLS) protocol, by selecting a *policy identifier*.

Each module implementation decides how to implement a specific policy
identifier, providing a trade off between security and client compatibility.
Newer policies are biased towards security, whilst older ones provide better
compatibility with old clients.

The following sections describe each policy identifier.

Policy 2018-03-30
-----------------

The goal of this policy is to harden the cipher set provided by the default
upstream policy.  It is not compatible with IE 8 XP and Java 6u45 and 7u25
clients. It does not support ECC certificates.

Apache
    * See https://bettercrypto.org/static/applied-crypto-hardening.pdf category B
    * Cipher suite ::
        
        EECDH+AESGCM:EDH+AESGCM:AES256+EECDH:AES256+EDH
        
    * Disabled SSLv2 and SSLv3
    * Ignore ``httpd/SSLCipherSuite`` property settings (see :ref:`Default upstream policy`)

Dovecot
    * See https://bettercrypto.org/static/applied-crypto-hardening.pdf category B
    * Cipher suite ::
        
        EDH+CAMELLIA:EDH+aRSA:EECDH+aRSA+AESGCM:EECDH+aRSA+SHA384:EECDH+aRSA+SHA256:EECDH:+CAMELLIA256:+AES256:+CAMELLIA128:+AES128:+SSLv3:!aNULL:!eNULL:!LOW:!3DES:!MD5:!EXP:!PSK:!DSS:!RC4:!SEED:!ECDSA:CAMELLIA256-SHA:AES256-SHA:CAMELLIA128-SHA:AES128-SHA
        
    * Disabled SSLv2 and SSLv3

OpenSSH
    * See https://github.com/NethServer/nethserver-openssh/pull/6
    * Configuration snippet ::
        
        Ciphers chacha20-poly1305@openssh.com,aes256-gcm@openssh.com,aes128-gcm@openssh.com,aes256-ctr,aes128-ctr
        MACs hmac-sha2-512-etm@openssh.com,hmac-sha2-256-etm@openssh.com,umac-128-etm@openssh.com,hmac-sha2-512,hmac-sha2-256,hmac-ripemd160
        KexAlgorithms curve25519-sha256@libssh.org,diffie-hellman-group-exchange-sha256,diffie-hellman-group14-sha1,diffie-hellman-group-exchange-sha1

Postfix
    * See https://bettercrypto.org/static/applied-crypto-hardening.pdf category B
    * Use TLS in outbound connections, if remote server supports it
    * Disable SSLv2 and SSLv3 on submission ports
    * Cipher suite ::
        
        EDH+CAMELLIA:EDH+aRSA:EECDH+aRSA+AESGCM:EECDH+aRSA+SHA256:EECDH:+CAMELLIA128:+AES128:+SSLv3:kEDH:CAMELLIA128-SHA:AES128-SHA
        
    * Exclude ciphers ::
        
        aNULL:eNULL:LOW:3DES:MD5:EXP:PSK:DSS:RC4:SEED:IDEA:ECDSA

Default upstream policy
-----------------------

The goal of this policy is retaining upstream settings. This is the original goal since |product| 7.
