.. _dns-section:

===
DNS
===

|product| kann als :dfn:`DNS` (Domain Name System) Server konfiguriert werden.
Ein :index:`DNS` Server ist dafür verantwortlich die Namensauflösung im Netzwerk zu betreiben und den DNS-Namen (z.B. www.beispiel.de) in die IP-Adresse (z.B. 11.112.231.3) aufzulösen und anders herum.

Der DNS-Server führt auf Anfrage der Clients die Namensauflösung aus. 
Der DNS-Server ist nur aus dem grünen und blauen Netzwerk erreichbar.

Bei einer Namensauflösung, wird der Server:

* den Namen im lokalen Netzwerk suchen
* eine Anfrage an den externen DNS-Server stellen und die Antwort zwischenspeichern um künftige Anfragen zu beschleunigen

Wenn |product| ebenfalls als DHCP-Server konfiguriert ist, werden alle Maschinen automatisch den |product| für die Namensauflösung nutzen.

.. note:: Es muss mindestes ein externer DNS-Server unter :guilabel:`DNS Server` angegeben werden.


Hosts
=====

Die :guilabel:`Hosts`-Seite erlaubt es Hostnamen IP-Adressen zuzuweisen. Dabei können die IP-Adressen local oder remote oder auch dummy-IP-Adressen sein.

Zum Beispiel: Wenn ein interner Webserver betrieben wird, kann der Hostname *www.meine-seite.de* mit der IP des internen Webservers verknüpft werden. 
Alle Clients im lokalen Netzwerk können dann die Seite bei der Eingabe dieser Adresse um Browser aufrufen.

Lokal konfigurierte Hosts werden immer zuerst verwendet bevor ein DNS-Eintrag eines externen Servers verwendet wird.
Dies bedeutet, dass der externe DNS-Server *www.meine-seite.de* mit der externen IP-Adresse der offiziellen Webseite auflöst.
Da jedoch innerhalb von |product| ein Hosteintrag für *www.meine-seite.de* vorhanden ist, werden alle Geräte im lokalen Netzwerk, die den |product| als DNS-Server werden, die interne IP-Adresse auflösen.


Alias
=====

Ein :dfn:`alias` ist ein alternativer Name um den |product| zu erreichen.
Zum beispiel wenn der Server *mail.meine-seite.de* heißt, kann ein :index:`DNS alias` *myname.meine-seite.de* erstellt werden.
Der Server wird dann auch von dem Alias erreichbar sein.

Aliase sind nur im LAN gültig. Soll der Alias auch aus dem Internet erreichbar sein, muss dieser Alias beim DNS-Provider eingetragen werden.

