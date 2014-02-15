=========
Customization
=========

Overview
========
You can customize some parts of the interface NethServer, such as the logo and colors.


Colors
==============
Simple configuration database entries for a theme green and red:

::
    [root@nsrv -] config setprop httpd-admin colors "green,red,#1d247c" 

  
Reload the interface, colors should be applied respectively on: top header, left menu, text headers (also in tables and links on left menu)

Logo
===============

Copy a custom logo (best size: 185 x 30) inside /usr/share/nethesis/nethserver-manager/images/ directory. Change the default logo with this command:

::

    [root@nsrv -]# config setprop httpd-admin logo mylogo.png

Reload the interface and check the new logo is loaded
