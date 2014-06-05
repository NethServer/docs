=========================
Web interface translation
=========================

All module language files are placed in :file:`/usr/share/nethesis/NethServer/Language/<lang>`.

Given a module with name "Test", the English language file will be :file:`/usr/share/nethesis/NethServer/Language/en/NethServer_Module_Test.php`.

Missing translations can be found in :file:`/var/log/messages` after Nethgui debug is enabled.
To enable the debug, use index_dev.php on URLs, eg: :file:`https://<ipaddress>/index_dev.php/en/<module>`.

Inside nethserver-devbox there are two helper scripts:

* translate-module: generate a language file for a module
* translate-merge: merge two existing language files
