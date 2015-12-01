======
c-icap
======

"c-icap is an implementation of an ICAP server. It can be used with HTTP proxies that support the ICAP protocol to implement content adaptation and filtering services."

This package configure the c-icap server, we also compile c-icap rpm:

* https://github.com/nethserver/c-icap
* https://github.com/nethserver/nethserver-c-icap

Options
=======

Enable debug to :file:`/var/log/c-icap/server.log`: ::

  config setprop c-icap DebugLevel 1
  signal-event nethserver-c-icap-update


DB example: ::

 c-icap=service
    DebugLevel=0
    TemplateDefaultLanguage=en
    status=enabled

