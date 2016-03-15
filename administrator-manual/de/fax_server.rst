==========
Fax server
==========

Der :index:`fax`server macht es möglich Faxe über ein Modem, dass direkt an den Server angeschlossen ist, oder über ein :index:`virutelles Modem` zu senden.

Über das Webinterface sind folgende Konfigurationen möglich:

* Vorwahl und Faxnummer
* Absender (TSI)
* Ein physisches Modem mit Leitungsdaten und wie Faxes gesendet/empfangen werden sollen
* Ein oder mehrere :ref:`iax-modem`s
* E-Mail Benachrichtigungen für gesendete und empfangene Faxe mit einem Fax als Anhang (PDF, PostScript, TIFF)
* Empfangene Faxe drucken
* Virtual Samba Printer
* Täglicher Bericht über gesendete Faxe
* Versenden von Faxen via E-Mail


Modem
=====

Trotz das die genutzte HylaFAX-Implementierung eine Reihe von Herstellern und Modellen unterstützt, empfehlen wir die Nutzung eines externen serial- oder USB-Modems.

Der Grund für diese Empfehlung ist: Wenn ein internes Modem ein Problem erzeugt, muss der Server neugestartet werden. Extere Modems können separat neugestartet werden (Stecker raus, Stecker rein).
Viele erhältliche interne Modems sind sogenannte Winmodems. Dies sind "Software"-Modems, welche einen Treiber benötigen, der in der Regel nur für Windows erhältlich ist.

Achtung: Auch viele externe USB-Modems sind Winmodems!

Die Wahl sollte auf ein Modem der Klasse 1 oder 1.0 fallen, besondern wenn diese auf Rockwell-/Conexant- oder Lucent-/Agere- Chips basieren.
|product| unterstützt auch Modems der Klassen 2, 2.0 und 2.1.

Client
======

Wir empfehlen den Fax-Client YajHFC (http://www.yajhfc.de/). Dieser verbindet direkt zum Server und erlaubt folgende Funktionen:

* Nutzung eine LDAP-Adressbuchs
* Auswahl des Modems, über das gesendet werden soll
* Ansicht des Status des Modems

Authentifizierung
-----------------

|product| unterstützt zwei Möglichkeiten zur Authentifizierung beim Senden von Faxen:

* Systembasieren: Anhand der IP-Adresse wird die Berechtigung zum Senden von Faxen geprüft
* PAM: Nutzt Benutzernamen und Passwort. Der Benutzer muss der Gruppe "faxmaster" angehören.

Außerdem sollte sichergestellt sein, dass :guilabel:`Faxe vom Client ansehen` aktiviert ist.


Samba Virtual Printer
=====================

Wenn die Option SambaFax aktiviert ist, stellt der Server einen virtuellen Drucker mit dem Namen "sambafax" im Netzwerk zur Verfügung.

Jeder Client muss diesen Drucker mit den Apple LaserWriter 16/600 PS-Treibern einrichten.

Zu sendende Dokumente müsse folgende Voraussetzungen erfüllen:

* Sie müssen die Wörter "Fax Number" enthalten, gefolgt von der Faxnummer. Beispiel: ::

   Fax Number: 12345678

* Die Zeichenfolge kann überall im Dokument stehen, aber muss in einer Zeile enthalten sein
* Die Zeichenfolge muss in einer nicht-Bitmap-Schriftart geschrieben sein (z.B. Truetype)

Die Faxe werden gesendet, indem die Benutzerdaten des absendenden Benutzers genutzt werden. Diese Information wird auch in der Fax-Warteschlange angezeigt.


Mail2Fax
========

Alle E-Mails, die an ``sendfax@<domainname>`` gesendet werden, werden als Fax an den Empfänger gesendet.

``<domainname>`` muss einer Domäne entsprechen, die auf dem E-Mail-Server verarbeitet wird.

Die E-Mail muss wie folgt formatiert sein:

* Die Empfängernummer muss im Betreff angegeben sein
* Die E-Mail muss eine Nur-Text-E-Mail sein (kein HTML oder RichText!)
* Die E-Mail kann anhänge wie PDFs enthalten, welche zusammen mit dem Fax versendet werden

.. hinweis :: Diese Funktion steht nur für Clients zur Verfügung, welche aus einem grünen Netzwerk versenden

.. _iax-modem:

Virtual Modems
==============

Virtual Modems sind Softwaremodems, welche an eine PBX (Asterisk usually) mit einer IAX Erweiterung angeschlossen sind.

Die Konfiguration von virtuellen Modems enthält zwei Teile:

1. Erstellen der IAX-Eweiterung mit der PBX
2. Konfiguration des Virtuellen Modems

