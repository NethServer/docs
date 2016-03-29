.. _firewall-section:

=====================
Firewall und Gateway
=====================

|product| kann als :index:`firewall` und als :index:`gateway` genutzt werden.
Der gesamte Netzwerkverkehr zwischen Computer im lokalen Netzwerk und dem Internet, der durch |product| geleitet wird, wird anhand von Regeln entsprechend weiterverarbeitet.

Hauptfunktionen:

* Erweiterte Netzwerkkonfiguration (Bridge ("Netzwerkbrücke"), Bonds, Alias usw.)
* Multi-WAN Unterstützung (bis zu 15)
* Regelbasierte Firewall
* Traffic Shaping (QoS)
* Port Weiterleitung
* Routen von Netzwerkverkehr zu unterschiedlichen WAN-Verbindungen
* Intrusion Prevention System (IPS)


Firewall und Gateway sind nur aktiv, wenn:

* Das Modul `nethserver-firewall-base` installiert ist
* Mindestens ein Netzwerkadapter ein rotes Webinterface ist

.. _policy-section:

Richtlinien
===========

Jeder Netzwerkadapter wird durch eine Farbe gekennzeichnet, die dessen Rolle im System angibt.
See :ref:`network-section`.

Wenn ein Netzwerkpaket die Firewall passiert, prüft |product|, ob das Paket erlaubt ist oder ob es blockiert wird.
:dfn:`Richtlinien` sind die Regeln, die angewendet werden, wenn ein Paket keiner existierenden Regel zuzuordnen ist.

Die Firewall implementiert zwei Standardrichtlinien, welche über :menuselection:`Firewall Regeln` -> :guilabel:`Konfigurieren` bearbeitet werden können:

* :dfn:`Erlaubt`: Der gesamte Netzwerkverkehr von grün nach rot ist erlaubt.
* :dfn:`Blockiert`: Der gesamte Netzwerkverkehr von grün nach rot ist blockiert. Nur explizit durch Firewall Regeln erlaubter Traffic darf die Firewall passieren.

Firewall :index:`Richtlinien` erlauben zonenübergreifenden Verkehr nach folgendem Schema: ::

 GRÜN -> BLAU -> ORANGE -> ROT

Netzwerkverkehr wird erlaubt von links nach rechts. Netzwerkverkehr von rechts nach links wird blockiert.

Das Standardverhalten kann unter :guilabel:`Firewall Regeln` angepasst werden.

.. hinweis:: Netzwerkverkehr vom lokalen Netzwerk zum Server auf dem SSH-Port (Standard: 22) und auf den Servermanager-Port (Standard: 980) ist IMMER erlaubt.

.. _firewall-rules-section:

Regeln
======

:index:`Regeln` betreffen allen Netzwerkverkehr, welcher durch die Firewall geleitet wird.
Wenn ein Netzwerkpaket von einer Zone zu einer anderen Zone möchte, prüft |product| die konfigurierten Regeln.
Wenn das Netzwerkpaket einer Regel entspricht, so wird diese Regel angewendet.

.. hinweis:: Die Reihenfolge der Regeln ist sehr wichtig! |product| wendet immer die erste Regel an, welche auf das Netzwerkpaket zutrifft.

Eine Regel besteht aus vier wesentlichen Bestandteilen:

* Aktion: Was soll gemacht werden, wenn die Regel auf ein Netzwerkpaket zutrifft?
* Quelle: Woher soll das Paket kommen, damit diese Regel ggf. angewendet wird?
* Ziel: An welche Adresse/Host ist das Paket gerichtet, damit diese Regel ggf. angewendet wird?
* Dienst: Auf welche Dienste (Ports) trifft diese Regel zu?


Verfügbare Aktionen sind:

* :dfn:`ACCEPT`: Erlaubt den Netzwerkverkehr
* :dfn:`REJECT`: Verweigert den Netzwerkverkehr und informiert den absendenden Host auf Netzwerkebene
* :dfn:`DROP`: Verweigert den Netzwerkverkehr und informiert den absendenden Host NICHT
* :dfn:`ROUTE`: Route den Netzwerkverkehr zu einem definierten WAN-Anschluss. Siehe :ref:`multi-wan-section`.

.. hinweis:: Die Firewall generiert keine Regeln für die blaue oder die orangene Zone, wenn nicht mindestens ein roter Netzwerkadapter konfiguriert wurde.

REJECT vs DROP
--------------

Generell sollte :index:`REJECT` gewählt werden, wenn der Quellhost informiert werden soll, dass die Verbindung die er geöffnet hat geschlossen wurde.
Normalerweise wird von Regeln für das lokale Netzwerk REJECT genutzt.

Für Verbindungen aus dem Internet wird empfohlen :index:`DROP` zu nutzen um potentiellen Angreifern keinerlei Antwort zu liefern.

Log
---

Es ist möglich beim Zutreffen einer Regel ein Log-Eintrag zu schreiben, wenn die Option  im Webinterface aktiviert wurde.
Das :index:`Firewall Log` wird unter :file:`/var/log/firewall.log` gespeichert.

Beispiele
---------

Im Folgenden einige Beispiele für Regeln.

Allen DNS-Verkehr vom LAN in das Internet blockieren:

* Aktion: REJECT 
* Quelle: GRÜN 
* Ziel: ROT
* Dienst: DNS (UDP port 53) 

Allen Gästenetzwerken den Zugriff auf Server1 erlauben:

* Aktion: ACCEPT 
* Quelle: BLAU
* Ziel: Server1 
* Dienst: -

.. _multi-wan-section:

Multi WAN
=========

Der Begriff :dfn:`WAN` (Wide Area Network) bedeutet das öffentliche Netzwerk außerhalb der Server - im Normalfall das Internet.
Ein :dfn:`Provider` ist das Unternehmen, welches den Zugang zum internet, den :index:`WAN`-Link, bereitstellt.

|product| unterstützt bis zu 15 WAN-Anschlüsse.
Wenn der Server zwei oder mehr konfigurierte rote Netzwerkadapter hat, ist es nötig eine Providerkonfiguration auf der Seite :guilabel:`Multi WAN` durchzuführen.

Jeder Provider stellt eine WAN-Verbindung, welche an einen Netzwerkadapter gekoppelt ist.
Jeder Provider definiert eine :dfn:`Gewichtung`: je höhere die :index:`Gewichtung`, desto höher die Priorität des Netzwerkadapter, der mit dem Provider assoziiert ist.

|product| kann die WAN-Verbindungen in zwei Modi betreiben (Schaltfläche :guilabel:`Konfigurieren` auf der Seite :menuselection:`Multi WAN`): 

* :dfn:`Balance`: Alle Provider werden gleichzeitig unter Beachtung ihrer Gewichtung genutzt.
* :dfn:`Aktiv Backup`: Es wird der Provider mit der höchsten Gewichtung genutzt. Wenn dieser Provider die Verbindung verliert, wird der Netzwerkverkehr über den nächsthöheren Provider geleitet.

Um den Status eines Providers zu erfahren, sendet |product| ein ICMP Paket ("ping") in regelmäßigen Intervallen.
Wenn die Anzahl der verlorenen Pakete einen Grenzwert überschreitet, wird der Provider als nicht erreichbar angesehen.

Die Sensivität der Überwachung kann über die folgenden Parameter festgelegt werden:

* Prozent der verlorenen Pakete
* Anzahl der verlorenen Pakete
* Intervall in Sekunden zwischen gesendeten Paketen

Die :guilabel:`Firewall Regeln`-Seite erlaubt es Netzwerkpakete zu den vorhandenen WAN-Providern zu routen, wenn bestimmte Kriterien erfüllt werden.
Siehe :ref:`firewall-rules-section`.


Beispiel:
---------

Es gibt zwei konfigurierte Provider:

* Provider1: Netzwerkadapter eth1, Gewichtung 100
* Provider2: Netzwerkadpater eth0, Gewichtung 50

Wenn der Modus Balance gewählt ist, wird der Server über Provider 1 doppelt so viele Verbindungen aufbauen wie über Provider 2.

Wenn der Modus Aktiv Backup gewählt ist, wird der Server alles an Verkehr über Provider 1 leiten. Wenn Provider 1 nicht mehr verfügbar ist, wird auf Provider 2 ausgewichen.


Portweiterleitung
=================

Die Firewall blockert Anfragen aus öffentlichen Netzwerken zu den privaten Netzwerken.
Beispiel: Wenn ein Webserver im LAN betrieben wird, können nur Computer aus dem lokalen Netzwerk die Webseite(n) in der grünen Zone nutzen.
Jede Anfrage von einem Benutzer außerhalb des lokalen Netzwerks wird blockiert.

Um den Zugriff von Außen auf den Webserver zu erlauben, muss eine :dfn:`Portweiterleitung` eingerichtet werden.
Eine Portweiterleitung erlaubt begrenzten Zugriff auf die Resourcen aus öffentlichen Netzwerken.

Wenn der Zugriff konfiguriert wird, muss der genutzte Port angegeben werden. Der Netzwerkverkehr von roten Netzwerkadaptern wird dann auf für die gewählten Ports weitergeleitet.
Am Beispiel von Webservern ist dies normalerweise der port 80 (HTTP) und Port 443 (HTTPS).

Wenn eine Portweiterleitung eingerichtet wird, müssen mindestens die folgenden Parameter angegeben werden:

* Der Quellport
* Der Zielport, der sich vom Quellport unterscheiden kann
* Die Adresse des Servers, an den der Verkehr weitergeleitet werden soll

.. hinweis:: Es ist möglich einen Portbereich anzugeben. Dazu werden beim Quellport der erste und der letzte Port, getrennt von einem Doppelpunkt, angegeben. Z.B. "1000:2000". Der Zielport muss dann leer bleiben.


Beispiel
--------

Gegeben ist folgendes Szenario:

* Der interne Server hat die IP 192.168.1.10 mit dem Namen Server1
* Der Server betreibt einen Webserver auf Port 80
* Der Server hat einen Zugang via SSH auf Port 22
* Der Server hat weitere Dienste, die auf den Ports 5000 bis 6000 erreichbar sind.

Um den Zugang auf den Webserver von außerhalb freizugeben, muss folgende Regel eingerichtet werden:

* Quellport: 80
* Zielport: 80
* Host Adresse: 192.168.1.10

Jeder eingehende Netzwerkverkehr auf einem roten Netzwerkadapter der Firewall auf port 80 wird so zu Server1 weitergeleitet.

Wenn SSH von außerhalb auf Port 2222 erreichbar sein soll, so muss folgende Regel eingerichtet werden:

* Quellport: 2222
* Zielport: 22
* Host Adresse: 192.168.1.10

Jeder eingehende Netzwerkverkehr auf dem roten Netzwerkadapter der Firewall auf port 2222 wird so zu Server 1 auf Port 22 weitergeleitet.
 
Wenn Dienste auf den Ports 5000 bis 6000 von außerhalb freigegeben werden werden sollen und an Server 1 weitergeleitet werden sollen, so muss folgende Regel eingerichtet werden:

* Quellport: 5000:6000
* Zielport: 
* Host Adresse: 192.168.1.10

Jeder eingehende Netzwerkverkehr auf dem roten Netzwerkadapter der Firewall auf den Ports 5000 bis 6000 wird auf dem gleichen Port an Server1 weitergeleitet.

Beschränkter Zugriff
--------------------

Die Portweiterleitung kann eingeschränkt werden, sodass diesen nur noch bei Zugriff von bestimmten IP-Adressen oder Netzwerken durchgeführt wird. Dazu wird das Feld :guilabel:`Nur erlauben von` genutzt.

Diese Konfiguration ist hilfreich, wenn Dienste nur von vertrauenswürdigen Quellen erreichbar sein sollen.
Eine mögliche Werte:

* ``10.2.10.4``: Portweiterleitung nur durchführen, wenn von der IP 10.2.10.4 zugegriffen wird.
* ``10.2.10.4,10.2.10.5``: Portweiterleitung nur durchführen, wenn von der IP 10.2.10.4 oder 10.2.10.5 zugegriffen wird.
* ``10.2.10.0/24``: Portweiterleitung nur durchführen, wenn aus dem Netzwerk 10.2.10.0/24 zugegriffen wird (Alle IPs von 10.2.10.0 bis 10.2.10.255)
* ``!10.2.10.4``: Portweiterleitung für alle durchführen, nur nicht für die IP 10.2.10.4
* ``192.168.1.0/24!192.168.1.3,192.168.1.9``: Portweiterleitung für das Netzwerk 192.168.1.0/24 durchführen, nicht aber für die IPs 192.168.1.3 und 192.168.1.9

NAT 1:1
=======

Eins-zu-Eins NAT ist eine Möglichkeit Systeme hinter einer Firewall mit einer privaten IP so erscheinen zu lassen, als hätten sie eine öffentliche IP.

Sofern mehrere öffentliche IP-Adressen zur Verfügung stehen und eine IP einem definierten Host zugeordnet werden soll, dann ist :index:`NAT 1:1` die Lösung.

Beispiel
--------

In einem Netzwerk gibt es den Server ``BeispielServer`` mit der IP ``192.168.5.122``. außerdem haben wir die öffentliche IP-Adresse ``89.95.145.226`` als alias auf dem ``eth0`` Netzwerkadapter (``rot``).

Wir möchten den ``BeispielServer`` die IP-Adresse ``89.95.145.226`` zuweisen.


Unter :guilabel:`NAT 1:1` wählen wir für die IP ``89.95.145.226`` (read-only Feld) den Host (``BeispielServer``) aus der Auswahlbox. Somit wurde ein Eins-zu-Eins NAT konfiguriert.


Traffic Shaping
===============

:index:`Traffic Shaping` erlaubt es Netzwerkverkehr durch die Firewall zu priorisieren (:index:`QoS`).
So ist es möglich die Verbindungen von wichtigem Netzwerkverkehr zu priorisieren und die Latenz zu verringern indem die verfügbare Bandbreite optimal ausgenutzt wird.

Um Traffic Shaping zu aktivieren ist es notwendig zu wissen wie viel Bandbreite in beide Richtungen einer Verbindung zur Verfügung steht. Dies ist in der Regel die Up- und Downloadgeschwindigkeit des Internetanschlusses.
Im Falle eines Problems beim Internetprovider kann an dieser Stelle keine vollständige Abhilfe geschaffen werden um die Geschwindigkeit zu erhöhen.

Traffic Shaping kann unter :menuselection:`Traffic Shaping` -> :guilabel:`Adapterregeln` konfiguriert werden.

|product| bietet drei Stufen von Prioritäten: Hoch, Mittel und Niedrig. Standardmäßig ist aller Netzwerkverkehr Mittel priorisiert.
Es ist möglich basierend auf den genutzten Ports eines Dienstes die Priorität auf Hoch oder Niedrig zu setzen (z.B. für niedrig priorisierten Peer-To-Peer traffic).

|product| hat für interaktiven Netzwerkverkehr bereits eine hoche Priorität vorkonfiguriert. Das Bedeutet, dass VoIP, SSH und PING bereits mit hoher Priorität verarbeitet werden.

.. hinweis:: Stelle sicher, dass die tatsächlich vorhandene Bandbreite des Anschlusses angegeben ist!


Firewall Objekte
================

:index:`Firewall Objekte` repräsentieren Netzwerkkomponente und sind hilfreich um das Erstellen von Regeln zu erleichtern.

Es gibt 6 Typen von Objekte. 5 davon repräsentieren Quellen und Ziele:

* Host: Stellen einen lokalen oder entfernten Computer dar. z.B. Webserver oder PCs.
* Gruppen von Hosts: Stellen eine Gruppe von Computern da. Hosts in einer Hostgruppe sollten immer über den gleichen Netzwerkadapter erreichbar sein. z.B.: Server, Buchhaltung-PCs
* CIDR Netzwerke: Es ist möglich CIDR-Netzwerke anzugeben um die Firewall Regeln zu vereinfachen.
  
  Beispiel 1: Die letzten 14 IP-Adressen eines Netzwerks sind Servern zugewiesen (192.168.0.240/28).

  Beispiel 2: Es sind zwei grüne Netzwerkadapter vorhanden, aber es soll nur eine Regel für einen Adapter erstellt werden (192.168.2.0/24).

.. index:: Zone

* Zone: Stellt ein Netzwerk mit Hosts dar. Dirse müssen zuvor in einer CIDR-Gruppe angelegt worden sein. Die Zonen sind dazu gedacht, dass einzelne Teile eines Netzwerks verschiedenen Firewallregeln unterliegen obwohl das gesamte Netzwerk auf einem Netzwerkadapter anliegt.

.. hinweis:: Standardmäßig dürfen alle Hosts einer Zone die Firewall nicht passieren. Es ist erforderlich, dass zum Passieren der Firewall Regeln erstellt werden.

Der letzte Objekttyp wird benutzt um den Typ (/Port) des Netzwerkverkehrs zu definieren:

* Dienste: Ein Dienst nutzt mindestens einen Port und ein Protokoll. Beispiel: ssh, https 

Wenn Regeln erstellt werden, können die Einträge, die unter :ref:`dns-section` und :ref:`dhcp-section` angelegt wurden, wie andere Host-Objekte genutzt werden.
Außerdem wird jeder Netzwerkadapter mit seiner zugewiesenen Rolle automatisch bei den verfügbaren Zonen aufgelistet.


IP/MAC Bindung
==============

Wenn |product| als DHCP-Server fungiert, kann die Firewall die DHCP-Reservierungen nutzen um allen Netzwerkverkehr innerhalb des lokalen Netzwerks zu prüfen.
Wenn :index:`IP/MAC Bindung` aktiviert ist, kann der Administrator auswählen welche Richtlinie auf Hosts ohne DHCP-Reservierung angewendet werden soll.
Ein häufiger Anwendungsfall ist, wenn nur bekannte Hosts kommunizieren dürfen und alle anderen Hosts blockiert werden.
In diesem Fall würden Hosts ohne Reservierung nicht in der Lage sein die Firewall zu passieren und auf andere Netzwerke zuzugreifen.

Um Netzwerkverkehr nur von bekannten Hosts zu erlauben, müssen folgende Schritte ausgeführt werden:

1. Erstelle eine DHCP-Reservierung für einen Host
2. Gehe zu :menuselection:`Firewall Regeln` und wähle :guilabel:`Konfigurieren` aus dem Schaltflächenmenü
3. Wähle :guilabel:`MAC Überprüfung (IP/MAC Bindung)`
4. Wähle :guilabel:`Blockiere Netzwerkverkehr` als Richtlinie, die auf unregistrierte Hosts angewendet werden soll


.. hinweis:: Erstelle mindestens eine DHCP-Reservierung bevor IP/MAC-Bindung aktiviert wird. Ansonsten hat kein System mehr zugriff auf das Webinterface oder SSH von |product|!

