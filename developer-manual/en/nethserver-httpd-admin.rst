======================
nethserver-httpd-admin
======================

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
                                                                                                               
