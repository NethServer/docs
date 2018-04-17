======================
nethserver-letsencrypt
======================

This package requests and automatically renews Let's Encrypt (LE) certificates.
It adds httpd ACME-related configuration for all defined virtual hosts.

The main helper ``/usr/libexec/nethserver/letsencrypt-certs`` can be executed also from command line.

For more info, see: ::

  /usr/libexec/nethserver/letsencrypt-certs -h 


Database properties under ``pki`` key inside ``configuration`` database:

- ``LetsEncryptRenewDays``: days to the expiration, the certificate will be renewd when the condition is met
- ``LetsEncryptMail``: (optional) registration mail for LE notifications
- ``LetsEncryptDomains``: comma-separated list of domains added to certificate SAN field


