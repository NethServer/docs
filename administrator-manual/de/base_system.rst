.. _base_system-section:

===========
Basis System
===========

Dieses Kapitel enthält eine Beschreibung aller Module, die am Ende der Installation verfügbar sind.
Alle weiteren, hier nicht genannten Module Müssen über das Paket-Management  :ref:`package_manager-section` 
installiert werden (einschließlich backup und Benutzerunterstützung).

.. _dashboard-section:

Dashboard
=========

Die :index:`Dashboard` Seite ist die Startseite nach einer erfolgreichen Anmeldung..
Hier ist der Status :index:`status` und die Konfiguration des Systems ersichtlich.

.. _duc-section:

Disk analyzer
-------------

Dieses Tool macht die Belegung der Festplatte optisch erkennbar :index:`disk usage`. Ein einfach bedinbares Diagramm
ermöglicht durch Klick und Doppelklick eine Navigation in der Ordnerstruktur.

Nach dem Ende der Installation kann man im Bereich :guilabel:`Disk usage` des :guilabel:`Dashboard`  den Punkt :guilabel:`Update`
auswählen um eine Katalogisierung des Verzeichnisbaums auszulösen und im Anschluss das Daigramm anzeigen zu lassen. 
Je nach Datenmenge kann dies mehrere Minuten dauern.

Bekannte Verzeichnisse sind:

* Shared folders: :file:`/var/lib/nethserver/ibay`
* User home directories: :file:`/var/lib/nethserver/home`
* Windows roaming profiles: :file:`/var/lib/nethserver/profile`
* Mail: :file:`/var/lib/nethserver/vmail`
* Faxes: :file:`/var/lib/nethserver/fax`
* MySQL databases: :file:`/var/lib/mysql`


.. index::
   single: Network
   pair: interface; role

.. _network-section:

Network
=======

Die Seite :guilabel:`Network` legt fest, wie der Server mit dem lokalen Netzwerk (LAN) 
und anderen Netzen (z.B. Internet) verbunden ist.

Falls der Server als Firewall und Gateway arbeitet, so wird er spezielle Netze verwalten, 
wie zum Beispiel eine DMZ (Entmilitarisierte Zone) und ein Gästenetz.

|product| unterstützt eine belibige Anzahl von Netzwerkkarten.
Jedes Netzwerk muss folgenden Anforderungen genügen:

* Netzwerke müssen physikalisch getrennt sein (keine verbindung mit dem gleichen Switch/Hub)
* Netzwerke müssen logisch getrennt sein (unterschiedliche Adressbereiche)
* Private Netzwerke (wie LANs) müssen den Adresskonventionen nach RFC1918 folgen.
  Siehe :ref:`RFC1918-section`

.. index:: zone, role

Jede Netzwerkkarte hat eine bestimmte *Rolle* (Funktion), die ihr Verhalten festlegt.
Die Rolle wird durch eine Farbkodierung beschrieben, die einer Zone mit bestimmten Regeln gehört: 


* *grün*: Lokales Netzwerk. Rechner in diesem Netz können auf alle anderen Netze zugreifen.
* *blau*: Gast Netzwerk. Rechner in diesem Netz können auf das rote und orange Netz zugreifen. Das grüne Netz ist nicht erreichbar.
* *orange*: DMZ Netzwerk.  Rechner in diesem Netz können auf das rote Netzwerk zugreifen. Blau, Grün und Orange sind nicht erreichbar.
* *rot*: Öffentliches Netzwerk. Rechner in diesem Netz können nur auf den Server zugreifen.

Siehe :ref:`policy-section` für weitere INformationen zu Rollen und Firewallregeln.

.. note:: Der Server benötigt immer mindestens eine Netzwerkkarte. Wenn nur eine Netzwerkkarte vorhanden ist, muss diese im grünen Netz sein.

Falls der Server auf einem öffentlichen Server (Virtual Private Server) installiert wird, so muss er mit einem grünen Netz konfiguriert werden. Alle kritischen Dienste sollten über die Konfigurationsoberfläche :ref:`network_services-section` deaktiviert werden.

.. _alias_IP-section:

Alias IP
--------

Mit Hilfe von Alias IPs können einer Netzwerkkarte mehrere IP-Adressen zugeordnet werden.

Beim typischsten Szenario werden einer roten Netzwerkkarte mehrere Adressen zugeordnet. Dies kann sinnvoll sein, wenn der ISP mehrere Adressen aus dem gleichen Subnet anbietet. Von diesen können dann mehrere (oder alle) an diese Netzwerkkarte gebunden werden. Auf diese Weise kann man individuelle Konfigurationen erstellen (z.B. im Bereich Port-Forwarding).

Der Alias IP Bereich befindet sich im Dropdown Menü der entsprechenden Netzwerkkarte.

.. _logical_interfaces-section:

Logische Metzwerkkarten
------------------

Im Bereich :guilabel:`Network` den Knopf :guilabel:`New interface` anklicken, 
um eine logische Netzwerkkarte zu erstellen.

Mögliche logische Netzwerkkarten sind:

* :index:`bond`: Zusammenfassen von zwei oder mehr Netzwerkkarten, um Lastausgleich und Fehrertoleranz zu ermöglichen.
* :index:`bridge`: Zwei verschiedene Netzwerke verbinden. Wird oft für bridged VPN und virtuelle Maschinen verwendet.
* :index:`VLAN` (Virtual Local Area Network): Erstellen von zwei oder mehr logisch getrennten Netzwerken auf einer Netzwerkkarte.
* :index:`PPPoE` (Point-to-Point Protocol over Ethernet): Internetverbindung über ein DSL-Modem

**Bonds** erlauben die Zusammenfassung von Bandbreite von zwei oder mehr Netzwerkkarten. Das System verwendet alle Netzwerkkarten gleichzeitig und verteilt den Verkehr auf die einzelnen Karten. Beim Auftreten von Fehlern wird die defekte Karte automatisch aus dem **bond** entfernt.

Eine **bridge** dient zur Verbindung zweier verschiedener Netzwerksegmente, zum Beispiel um virtuelle Maschinen zu verbinden oder einem Client via VPN eine Verbindung ins grüne Netz zu ermöglichen.

Wenn eine physikalische Trennung zweier Netze nicht möglich ist, kann ein **tagged VLAN** verwendet werden. Der Datenverkehr der beiden Netze läuft über das gleiche Kabel, wird aber behandelt, als käme er von getennten Netzwerkkarten. Die Verwendung von VLANs erfordert sauber konfigurierte Switche.

.. warning:: Die logische **PPPoE** Netzwerkkarte muss dem roten Netz zugeordnet werden,
             da dies für die Funktion als Gateway benötigt wird. Sie :ref:`firewall-section` für Details.

.. _RFC1918-section:

Addressen für private Netzwerke (RFC1918)
--------------------------------------

Private TCP/IP Netzwerke, die nicht direkt mit dem Internet verbunden werden, sollten spezielle Adressbereiche verwenden, die von der IANA (Internet Assigned Numbers Authority) dafür reserviert wurden:
 

=================     ===========   ================
Privates Netzwerk     Subnetmaske   IP Adressbereich
=================     ===========   ================
10.0.0.0              255.0.0.0     10.0.0.1 - 10.255.255.254
172.16.0.0            255.240.0.0   172.16.0.1 - 172.31.255.254
192.168.0.0           255.255.0.0   192.168.0.1 - 192.168.255.254
=================     ===========   =============================





.. _network_services-section:

Netzwerk Dienste
================

Ein :index:`network service` ist ein Dienst, der direkt auf der Firewall läuft.

Diese Dienste sind für alle Rechner im grünen Netz (LAN) erreichbar.
Zugriffsrichtlinien können über den Bereich :guilabel:`Network services` geändert werden.

Mögliche Richtlinien sind:

* Zugriff nur aus dem grünen Netz (private): Alle rechner aus dem grünen Netz und VPN-Clients.
* Zugriff aus grün und rot (public): Jeder Rechner aus grün, VPN-Clients und externe Netzwerke. Zugriff aus blau (Gäste) und orange (DMZ) sind nicht erlaubt.
* Zugriff nur vom Server (none): Kein Rechner kann den Dienst verwenden.

Benutzerdefinierter Zugriff
---------------------------
Wenn die gewählte Richtlinie *private* oder *public* ist, so kann man Rechner oder Netzwerke hinzufügen, denen der 
Zugriff immer erlaubt (verboten) ist, indem man :guilabel:`Allow hosts` oder :guilabel:`Deny hosts` wählt.
Diese Regeln gelten auch für das blaue und orange Netz.

Beispiel
^^^^^^^^

Gegeben ist folgende Konfiguration:

* Oranges Netz: 192.168.2.0/24
* Zugriff auf NTP Dienst ist *privat*

Wenn Rechner aus der DMZ auf den NTP Dienst zugreifen müssen, so fügt man das 192.168.2.0/24 Netz im Bereich :guilabel:`Allow hosts` hinzu.

.. index:: trusted networks

.. _trusted_networks-section:

Vertrauenswürdige Netzwerke
===========================

Vertrauenswürdige Netzwerke sind spezielle Netze (local, VPNs oder auch entfernt)
denen der Zugriff auf spezielle Dienste des Servers erlaubt wird.

Zum Beispiel können Rechner in vertrauenswürdigen Netzen auf folgende Dienste zugreifen:

* Server Manager
* Shared folders (SAMBA)

Wenn das entfernte Netzwerk über einen Router erreicht wird, so
muss in :ref:`static_routes-section` eine statische Route eingetragen werden.

.. _static_routes-section:

Statische Routen
================

Auf dieser Seite werden statische Routen erstellt :index:`static routes`, die ein bestimmtes Gateway verwenden. 
Derartige Routen werden üblicherweise verwendet, um Verbindungen zu privaten Netzen aufzubauen.

Es ist wichtig, dass das Netzwerk in :ref:`trusted_networks-section` als vertrauenswürdiges Netz eingetragen wird.


.. _organization_contacts-section:

Firmenkontaktdaten
=====================

Die Felder der :guilabel:`Organization contacts` Seite liefert die Voreinstellungen
für Benutzeraccounts. Der NAme der Firme sowie die Adresse werden auch auf der Login-Seite 
angezeigt.

.. index::
   pair: Certificate; SSL   

.. _server_certificate-section:

Server Zertifikate
==================

Die :guilabel:`Server certificate` Seite zeigt das aktuell installierte
SSL-Zertifikat, das für alle Systemdienste gültig ist.

Der Knopf :guilabel:`Generate certificate` erlaubt die Erstellung eines 
neuen selbstsignierten  SSL-Zertifikat.
Wird ein neues Zertifikat erstellt, so werden alle dienste neu gestartet.
Alle Clients müssen dieses Zertifikat dann noch akzeptieren.

.. note::
   Um Probleme beim Import des Zertifikates in den Internet Explorer zu vermeiden,
   sollte der *Common Name* (CN) dem FQDN des Servers entsprechen.

.. _custom_certificate-section:

Installation eines Benutzerzertifikates
---------------------------------------

:index:`Custom certificates` sollten in den den folgenden 
(üblichen) Verzeichnissen abgespeichert werden:

* :file:`/etc/pki/tls/certs`: public key
* :file:`/etc/pki/tls/private`: private key

Einstellen der Pfade für den privaten Schlüssel und das Zertifikat

::

    db configuration setprop pki CrtFile '/path/to/cert/pem-formatted.crt'
    db configuration setprop pki KeyFile '/path/to/private/pem-formatted.key'

Man kann auch ein *SSL certificate chain file* verwenden:

::

    db configuration setprop pki ChainFile '/path/to/cert/pem-formatted-chain.crt'

Informieren der Dienste über das neue Zertifikat:

::

    signal-event certificate-update

Sicherung eines Benutzerzertifikates
------------------------------------

Benutzerzertifikate müssen explizit in das Konfigurationsbackup aufgenommen werden.   
Dafür müssen die Pfade in :file:`/etc/backup-config.d/custom.include` eingetragen werden.

Wenn das Zertifikat beispielsweise hier zu finden ist :file:`/etc/pki/tls/certs/mycert.crt`,
so genügt die Ausführung von 

::

 echo "/etc/pki/tls/certs/mycert.crt" >> /etc/backup-config.d/custom.include

.. _user_profile-section:

Benutzerkennwort ändern
=======================

Alle Benutzer können sich an der Konfigurationsoberfläche anmelden und auf ihr :index:`user profile` zugreifen.

Nach der Anmeldung kann ein Benutzer sein Kennwort :index:`change the password` und 
folgende Informationen ändern:

* Name und Vorname
* External Mail-Addresse

Der Benutzer kann auch die vom Administrator voreingestellten Felder ändern:

* Company
* Office
* Address
* City

Herunterfahren
==============

der Rechner, auf dem |product| installiert ist kann von :menuselection:`Shutdown` heruntergefahren
oder neu gestartet werden. Man wählt die gewünschte Aktion an und klickt auf den *submit* Button.

Man sollte stets diesen Weg wählen, um den Computer herunterzufahren. Andere Methoden können
zu inkonsistenten Daten führen.

Log Betrachter
==============

Alle Dienste schreiben ihr Protokoll (Log) in die Dateien (:dfn:`logs`).

Die :index:`log` Analyse ist das Hauptwerkzeug um Probleme zu finden und zu lösen.
Das Werkzeug findet maun unter :menuselection:`Log viewer`.

Dieses Modul erlaubt:

* Alle Logs durchsuchen
* Eine einzelne Datei durchsuchen
* Die Einträge in eine Logdatei in Echtzeit verfolgen

Datum und Zeit
==============

Nach der Installation ist es wichtig, dass sich der Server in der richtigen Zeitzone befindet.
Die Uhrzeit des Rechners kann manuell oder automatisch via NTP (bevorzugt) eingestellt werden.

Die Uhrzeit des Rechners ist für viele Protokolleinträge wichtig. Um Probleme zu vermeiden, sollten alle
Rechner im LAN den Server als NTP-Server verwenden.


Inline Hilfe
===========

Alle Programme im  Server Manager enthalten eine :index:`inline help`.
Sie erklärt wie das Modul arbeitet und welche Optionen es besitzt.

Diese Hilfeseiten sind in allen Sprachen des Server Managers verfügbar.

Eine Liste aller verfügbaren Hilfeseitenfindet man unter 
::

 https://<server>:980/<language>/Help

**Beispiel**

Wenn der Server die Adresse ``192.168.1.2`` besitzt, so erhält man alle englischen Hilfeseiten durch
::

 https://192.168.1.2:980/en/Help


