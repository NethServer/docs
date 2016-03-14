.. _access-section:

.. index::
   single: Server Manager
   single: web interface
   
===========================
Zugriff auf die Management-Oberfläche
============================

|product| kann mit Hilfe der :dfn:`Server Manager` Weboberfläche konfiguriert werden.
Man benötigt einen Browser, wie den Mozilla Firefox oder Google Chrome um auf die Weboberfläche zugreifen zu können.
Die Adresse (URL) lautet: ``https://a.b.c.d:980`` oder ``https://server_name:980`` wobei *a.b.c.d* und *server_name* 
die IP-Adresse bzw. der Name des Servers sind, die bei der Installation vergeben wurden.

Falls das Webserver-Modul installiert ist, kann auch über die Adresse ``https://server_name/server-manager`` auf die
Weboberfläche zugegriffen werden.

Die Konfigurationsoberfläche verwendet ein selbst-signiertes SSL-Zertifikat. Es muss bei der ersten Benutzung explizit akzeptiert werden.
Die Verbindung ist dann verschlüsselt und damit sicher.

Anmeldung (Login)
-----------------
Nach dem Ausfüllen des Anmeldedialogs kann der Zugriff auf die Konfigurationsoberfläche erfolgen.
Die erste Anmeldung ist mit folgenden Benutzerdaten möglich:

* :index:`Default user` name: **root**
* :index:`Default password`: **Nethesis,1234**



Warnung
--------

Das Kennwort des Benutzers root sollte so bald wie möglich geändert werden. Dabei sollte ein möglichst sicheres Kennwort 
verwendet werden. Ideal ist eine zufällige Zeichenkette aus Groß- und Kleinbuchstaben, die außerdem Zahlen und Sonderzeichen
enthält.

Falls der Dateiserver, Mailserver oder ein anderes Modul installiert wurde, das auf dem Benutzer- und Gruppenmodul basiert,
so kann der ``admin`` Benutzer mit dem gleichen Kennwort und den gleichen Rechten auf die Konfigurationsoberfläche zugreifen wie ``root`` (siehe :ref:`admin_user-section` für Details).
