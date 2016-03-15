.. _access-section:

.. index::
   single: Servermanager
   single: Webinterface

===============================
Auf den Servermanager zugreifen
===============================

|product| kann über den :dfn:`Servermanager` im Webinterface konfiguriert werden. 

Es wird ein Browser wie Mozilla Firefox oder Google Chrome benötigt um auf der Webinterface zuzugreifen. Dies geschieht über die Adresse (URL)
``https://a.b.c.d:980`` oder ``https://server_name:980`` wobei *a.b.c.d* und *server_name* die IP-Adresse bzw. der Servername sind, welche während der Installation festgelegt wurden.

Wenn das Webserver-Modul installiert ist, kann dies über das Webinterface unter ``https://server_name/server-manager`` geöffnet werden.

Der Servermanager benutzt selbstsignierte SSL-Zertifikate.
Diese sollten akzeptiert werden wenn auf den Server zugegriffen wird.
Die Verbindung erfolgt gesichert und verschlüsselt.

Anmeldung
=========

Die Anmeldeseite ermöglicht Zugriff auf das Webinterface.
Hier sind folgende Anmeldedaten zu nutzen:

* :index:`Standardnutzer` name: **root**
* :index:`Standardpasswort`: **Nethesis,1234**

.. Achtung:: 
Das root-Kennwort sollte so bald wie möglicht geändert werden. Hierzu sollten Kombinationen aus Groß-/Kleinschreibung, Zahlen und Sonderzeichen verwendet werden.
  
Sollte der Fileserver, E-Mailserver oder ein anderes Modul mit 
Nutzerauthentifizierung und Gruppen via Softwarecenter installiert worden
sein, so ist der ``admin``-User ebenfalls mit den gleichen Berechtigungen
wie root berechtigt.
Näheres unter :ref:`admin_user-section`.
