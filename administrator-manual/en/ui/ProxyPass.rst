.. _ProxyPassUi-section:

=============
Reverse proxy
=============

This page configures certain paths and virtual host names under Apache to be
served by forwarding the original web request to another URL. See also
:ref:`proxy_pass-section`.


Create / Edit
-------------

Name
    The URL **path name** or the **virtual host name** (an host FQDN). A path name will
    match URLs like ``http://somehost/<path name>/...``, whilst a virtual host
    name will match an URL like ``http://<virtual host name>/...``.
    Matching URLs are forwarded to the :guilabel:`Target URL`.

Access from CIDR networks
    Restrict the access from the given list of CIDR networks. Elements must be
    separated with a "," (comma).

SSL/TLS certificate
    Select a certificate that is compatible with the virtual host name.

Require SSL encrypted connection
    If enabled, the URL path or virtual host name can be accessed only with an
    SSL/TLS connection.

Target URL
    The URL where the original request is forwarded.
    An URL has the form ``<scheme>://<hostname>:<port>/<path>``.

Accept invalid SSL certificate from target
    If the :guilabel:`Target URL` has the ``https`` scheme, accept its
    certificate even if it is not valid.

Forward HTTP "Host" header to target
    When enabled, this option will pass the HTTP "Host" header line from the
    incoming request to the proxied host, instead of the "hostname" specified in
    the :guilabel:`Target URL` field.

Delete
------

Removes the selected entry.
