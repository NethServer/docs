==========
WebVirtMgr
==========

Mit diesem Tool verwaltet man :index:`virtual machine` über eine einfache Weboberfläche:

* Erstellen und Löschen von virtuellen Systemen (:index:`KVM`)
* Erstellen eigener Vorlagen für virtuelle Systeme
* Einfache Konsole für entfernten Zugriff
* Tolle Benutzeroberfläche

Konfiguration
=============

Die Webanwendung ist auf dem Port **8000** aktiv, zum Beispiel: ``http://SYSTEM_IP:8000/``.

Der Dienst ist standardmäßig deaktiviert.

Unter der Schaltfläche :guilabel:`Virtual machines` kann man folgende Einstellungen vornehmen:

* Aktivieren der Verwaltungskonsole für virtuelle Systeme
* Aktivieren des Konsolenzugriffs auf das virtuelle System per Web Browser

Um auf die Weboberfläche zugreifen zu können muss man sich mit den unten stehenden Anmeldedaten anmelden:

* *Benutzer:* admin
* *Passwort*: random alphanumeric (editable)


.. warning:: 
   Keine Netzwerkbrücken(Network bridges) innerhalb der WebVirtManager Oberfläche erstellen.
   Hierfür eine Brücke(bridge) unter :guilabel:`Network` erstellen und im WebVirtManager dann entsprechend nutzen.

Weiterführende Informationen findet man unter:

* http://wiki.qemu.org/Manual
* http://www.linux-kvm.org/page/Documents
