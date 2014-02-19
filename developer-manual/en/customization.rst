=============
Customization
=============

Overview
========
You can customize some parts of the interface NethServer, such as the logo and colors.


Colors
======
Simple configuration database entries for a theme green and red:

::

    [root@nsrv -] config setprop httpd-admin colors "green,red,#1d247c" 

  
Reload the interface, colors should be applied respectively on: top header, left menu, text headers (also in tables and links on left menu)

Logo and favicon
================

Copy a custom logo (best size: 185 x 30) inside /usr/share/nethesis/nethserver-manager/images/ directory. Change the default logo with this command:

::

    [root@nsrv -]# config setprop httpd-admin logo mylogo.png

Copy a custom favicon inside /usr/share/nethesis/nethserver-manager/images/ directory. The favicon can be in PNG or ICO format,
recommended sizes are 16x16 or 32x32 pixels.
Change the default logo with this command:

::

    [root@nsrv -]# config setprop httpd-admin favicon myfavicon.png


Reload the interface and check the new logo and favicon are loaded. 

.. note:: Favicon are often cached by browsers: be patient and reload the page after a little while.
