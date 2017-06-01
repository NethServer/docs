========================
nethserver-roundcubemail
========================

Roundcube is a fast webmail client written in PHP.

Database 
========

Configuration is saved in ``roundcubemail`` key inside ``configuration`` database.

Available properites:

* ``Server``: server address of the mail server, default is ``localhost``
* ``access``: can be ``public`` or ``private``, default is ``public``

  * *public*: webmail can be accessed from any networks
  * *private*: webmail can be accessed only from green interfaces and  trusted networks
* ``PluginsList``: comma separated list of enabled plugins, default is ``managesieve,markasjunk``.
  Before adding an option to this property, please be sure the plugin is already installed.
  A list of bundled plugins can be found inside file:``/usr/share/roundcubemail/plugins`` directory.

Example: ::

 roundcubemail=configuration
    PluginsList=managesieve,markasjunk
    Server=localhost
    access=private


Configuration can be applied using the ``nethserver-roundcubemail-update`` event.

