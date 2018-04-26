======================
nethserver-httpd-admin
======================

Apache configuration for the web administration console
This Apache instance listens SSL connections on a non-standard port (by default 980) and execute system commands through ``sudo``. 

The main PHP scripts (controllers) are located in ``/usr/share/nethesis/nethserver-manager/`` directory.

Apache ``mod_rewrite`` configuration hides ``index.php`` in URLs. A generic production URL has the following form:  ``https://<hostname>:980/<lang>/<ModuleId>``

An additional controller ``index_dev.php`` is available for development. 
It produces more verbose logging, uses uncompressed JS and CSS libraries, and shows clear text names of widget target names. 
The URL form for development is:  ``https://<hostname>:980/index_dev.php/<lang>/<ModuleId>``

To enable ``index_dev.php`` controller, you need to execute the following command: ::

 # touch /usr/share/nethesis/nethserver-manager/debug

smwingsd daemon
===============

To speed up database read operations, avoiding ``sudo`` calls, the ``smwingsd`` Perl daemon is contacted. 
As ``httpd-admin``, the daemon is controlled by systemd, and on start reads configuration from ``/etc/smwingsd.conf``. 
It listens on the local Unix socket ``/var/run/smwingsd.sock``. You  can contact it with a command like this: ::

 # php -r '$payload=json_encode(array_slice($argv, 1), TRUE); print pack("CN", 0x10, strlen($payload)) . $payload;' configuration getjson sysconfig \
   | nc -U /var/run/smwingsd.sock  \
   | cut -b 6-   \
   | python -mjson.tool 
 {
    "name": "sysconfig", 
    "props": {
        "Copyright": "", 
        "ProductName": "NethServer", 
        "Registration": "none", 
        "Release": "rc1", 
        "Version": "6.5"
    }, 
    "type": "configuration"
 }

Customization
=============

You can customize some parts of the NethServer web interface:

* logo
* favicon
* colors
* top bar background image
* menu bar background image

Top bar and menu bar
--------------------

The page ships two different themes:

* light-polygons (default): includes background only for top bar
* color-polygons: includes backgrounds for top and menu bars


Enable color-polygons: ::

   config setprop httpd-admin headerBackground color-polygons/toolbar.png
   config setprop httpd-admin menuBackground color-polygons/sidebar.png

Enable light-poligons: ::

   config setprop httpd-admin headerBackground light-polygons/toolbar.png
   config setprop httpd-admin menuBackground ''

Custom themes
^^^^^^^^^^^^^

* Choose a name for the theme, like *mytheme*

* Create a directory named *mytheme* inside the :file:`/usr/share/nethesis/nethserver-manager/images` directory ::

    mkdir -p /usr/share/nethesis/nethserver-manager/images/mytheme

* Copy the top bar background inside the new directory and name it *toolbar.png*

* Copy the menu bar background inside the new directory and name it *sidebar.png*

* Set the new backgrounds ::

   config setprop httpd-admin headerBackground mytheme/toolbar.png
   config setprop httpd-admin menuBackground mytheme/sidebar.png

Colors
------

Simple configuration database entries for a theme green and red:

::

    config setprop httpd-admin colors "green,red,#1d247c" 


Reload the interface, colors should be applied respectively on: top header, left menu, text headers (also in tables and links on left menu)

Logo and favicon
----------------

Copy a custom logo (best size: 185 x 30) inside /usr/share/nethesis/nethserver-manager/images/ directory. Change the default logo with this command:

::

    config setprop httpd-admin logo mylogo.png

Copy a custom favicon inside /usr/share/nethesis/nethserver-manager/images/ directory. The favicon can be in PNG or ICO format,
recommended sizes are 16x16 or 32x32 pixels.
Change the default logo with this command:

::

    config setprop httpd-admin favicon myfavicon.png


Reload the interface and check the new logo and favicon are loaded.

.. note:: Favicons are often cached by browsers: be patient and reload the page after a little while.


Database example
================

::

 httpd-admin=service
    ForcedLoginModule=
    MaxSessionLifeTime=
    MaxSessionIdleTime=
    SSL=enabled
    TCPPort=980
    access=green,red
    colors=
    favicon=favicon.png
    headerBackground=
    logo=
    menuBackground=
    status=enabled

Session timeouts
================

The Server Manager session validity is subjected to forced logoff under the following conditions

* after an idle/inactivity period. It occurs when no user activity is detected in a certain amount of time
* after the maximum session lifetime has elapsed. It occurs if the user does not log out voluntarily

To configure the timeouts (both expressed as seconds) run the following command: ::

    config setprop httpd-admin MaxSessionIdleTime 900 MaxSessionLifeTime 86400

To disable the session timeouts, set the values to ``0`` or the empty string: ::

    config setprop httpd-admin MaxSessionIdleTime '' MaxSessionLifeTime ''

The new timeout values will affect new sessions. They does not change any active session.
