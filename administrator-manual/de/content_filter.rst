=================
Web Inhaltsfilter
=================

Der :index:`content filter` analysiert allen Webverkehr und blockiert definierte Seiten oder Seiten die Viren enthalten.
Verbotene Seiten können anhand einer Liste von Kategorien ausgewählt werden, welche von einer externen Quelle heruntergeladen werden können und auf dem |product| gespeichert werden müssen.

|product| erlaubt es unbegrenzt viele Profile zu erstellen.
Ein Profil besteht aus drei Teilen:

* **Wer**: Welcher Client ist diesem Profil zugewiesen?
  Dies kann ein Benutzer, eine Benutzergruppe, ein Host, eine Hostgruppe, eine Zone oder ein Netzwerkadapterrolle (grün, blau usw.) sein.

* **Was**: Welche Seiten können von den Clients aufgerufen werden?
  Dies ist ein Filter, der unter :guilabel:`Filter` definiert wird.

* **Wann**: Der Filter kann immer gelten oder nur zu einem bestimmten Zeitpunkt.
  Zeitfenster können unter :guilabel:`Zeiten` festgelegt werden.


Dies ist die empfohlene Reihenfolge für die Inhaltsfilter-Konfiguration:

1. Wähle eine Liste von Kategorien unter :guilabel:`Blacklists` und lade diese herunter
2. Erstelle eine oder mehrere Zeitfenster (optional)
3. Erstelle eigene Kategorien (optional)
4. Erstelle einen neuen Filter oder bearbeite den Standardfilter
5. Erstelle ein neues Profil, das eine Benutzer oder Host zugewiesen ist und wähle den Filter und das Zeitfenster (wenn aktiviert)

Wenn kein Profil den Filtern entspricht, wird das Standardprofil angewendet.

Filter
======

Ein Filter kann:

* den Zugang zu Seiten sperren, die einer Kategorien entsprechen
* den Zugang zu Seiten sperren, die über IP-Adressen aufgerufen werden (empfohlen)
* URL durch Regular Expressions filtern
* Das Herunterladen von Dateien mit bestimmten Endungen verbieten
* Eine globale Blacklist und Whitelist aktivieren

Ein Filter kann in zwei unterschiedlichen Modi ausgeführt werden:

* Alles erlauben: Alle Seiten erlauben, außer die Seiten, die explizit gesperrt sind
* Alles blockieren: Alle Seiten verieben, außer die Seiten, die explizit erlaubt sind

.. note:: Die Kategorien-Liste wird erst angezeigt, wenn die Liste unter :guilabel`Blacklist` heruntergeladen wurde.

Blockieren von Google Translate
-------------------------------

Online-Übersetzungsdienste wie :index:`Google Translate`, können missbraucht werden um den Inhaltsfilter zu umgehen.
Dies ist der Fall, weil die URL bei Nutzung der Übersetzung immer auf eine Google-Domain zeigt und dennoch Inhalt eines externen Servers enthält.

Es ist möglich alle Anfragen an Google translate zu blockieren, indem eine blockierte URL unter :guilabel:`General` erstellt wird.
Der Inhalt muss dann ``translate.google`` lauten.

Benutzer aus der Active Directory
=================================

Wenn |product| einer Active Directory (:ref:`samba_ads`) beigetreten ist, können Profile auch Domänen-Benutzern zugewiesen werden.

.. note:: Gruppen aus der  Active Directory werden nicht unterstützt.

Antivirus
=========

Es wird empfohlen den Virusscanner im Inhaltsfilter immer zu aktivieren.
Wenn der Proxy im SSL-Transparenzmodus (:ref:`proxy_ssl-section`) konfiguriert ist, wird der Virusscanner auch für HTTPS-Seiten verwendet.


Fehlerbehebung
==============

Wenn eine "böse Seite" nicht blockiert wird, prüfe folgendes:

* Der Client nutzt den Proxyserver
* Der Client hat keinen Proxy-Bypass für die Seite/IP konfiguriert
* Der Client ist eine Profil zugewiesen, dass den Besuch der Website verbietet
* Der Client surft in einem Zeitraum, in dem der Filter aktiv ist
