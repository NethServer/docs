.. _users_and_groups-section:

====================
Benutzer und Gruppen
====================

Benutzer
========

Ein Systennutzer wird benötigt, um auf viele Dienste zuzugreifen. z.B.
|product| (email, shared folders, etc..).

Jeder Benutzer wird durch seine Anmeldedaten identifiziert (Benutzer und Kennwort). Ein neuer Benutzer ist solange gesperrt, bis ein Kennwort für diesen festgelegt wurde. Ein gesperrter Benutzer kann keine Dienste nutzen, die eine Authentifizierung benötigen.

Wenn ein neuer Benutzer erstellt wird, sind folgende Felder Pflichtfelder:

* Benutzername
* Vorname
* Nachname

Optionale Felder:

* Firma
* Büro/Abteilung
* Adresse
* Stadt
* Telefon


Nach dem Erstellen ist ein Benutzer zunächst deaktiviert. Um diesen zu aktivieren muss ein Kennwort gesetzt werden, indem die Schaltfläche :guilabel:`Change password` genutzt wird.
Nachdem der Benutzer aktiviert wurde, kann dieser sich am Servermanager anmelden und sein Kennwort ändern: :ref:`user_profile-section`.

Ein Benutzer kann zu einer oder mehreren Gruppen hinzugefügt werden. Dies geschieht über die Seite :guilabel:`Benutzer` oder über :guilabel:`Gruppen`.

Gelegentlich muss ein Benutzer gesperrt werden ohne seinen Account zu löschen.
Dies kann erreicht werden, indem die Schaltflächen :guilabel:`Sperren` und :guilabel:`Entsperren` genutzt werden.

.. Hinweis:: Wenn ein Benutzer gelöscht wird, werden auch seine Benutzerdaten gelöscht.

.. _users_services-section:

Zugriff auf Dienste
-------------------

Nachdem ein Benutzer erstellt wurde, kann ein Benutzer für einzelne (oder alle) Dienste aktiviert werden.
Dies kann auf der Seite :guilabel:`Dienste` durchgeführt werden.

.. _groups-section:

Gruppen
=======

Eine Gruppe von Benutzern kann benutzt werden um Berechtigungen für eine Gruppe von Benutzern zu vergeben oder um E-Mail-Verteiler zu erstellen.

Wie für Benutzer können auch Gruppen für einige (oder alle) Dienste genutzt werden.

.. tipp:: Zum Zuweisen von Berechtigungen für den Servermanager sollten die Gruppen ``managers`` oder ``administrators`` genutzt werden.

Zwei spezielle Gruppen können erstellt werden. Deren Benutzer bekommen mit Ihrer Mitgliedschaft Zugriff auf die Seiten des Servermanagers.

* :dfn:`administrators`: Benutzer dieser Gruppe haben die gleichen Berechtigungen wie die Benutzer root oder admin.
* :dfn:`managers`: Benutzer dieser Gruppe haben Zgruff auf den Management-Bereich.


.. _admin_user-section:

Admin Benutzer
==============

Die Seite :guilabel:`Benutzer` hat einen Standardeintrag: :dfn:`admin`. 
Dieser Benutzer ermöglicht mit den gleichen Berechtigungen wie mit dem Benutzer :dfn:`root` Zugriff auf den Servermanager .
Standardmäßig ist dieser Benutzer deaktiviert und hat keinen Zgurff auf die Konsole.

.. tipp:: Um den Benutzer ``admin`` zu aktiviert, muss nur der Kennwort gesetzt werden.

Bei einigen Diensten hat der Benutzer ``admin`` spezielle Rechte. 
z.B. :ref:`joining a workstation in Samba domain <samba_pdc>`.

Passwortverwaltung
==================

|product| kann Richtlinien für Kennwörter wie :dfn:`complexity` und :dfn:`expiration` konfigurieren.

Die Kennwortrichtlinien können im Webinterface geändert werden. Dafür ist das Modul ``nethserver-password`` erforderlich.

Komplexität
-----------

Die :index:`Passwort`-Komplexität sichert ein minimum an Sicherheit für das System und die genutzten Kennwörter.
Dabei kann zwischen zwei verschienenden Richtlinien gewählt werden:

* :dfn:`none`: Keine Komplexität. Dennoch existiert eine Mindestlänge von 7 Zeichen.
* :dfn:`strong`

Die :index:`strong`-Richtlinie setzt voraus, dass das Kennwort bestimmten Regeln entspricht:

* Mindestens 7 Zeichen
* Mindestens 1 Zahl
* Mindestens 1 Großbuchstaben
* Mindestens 1 Kleinbuchstaben
* Mindestens 1 Sonderzeichen
* Mindestens 5 unterschiedliche Zeichen
* Darf nicht im Wörterbuch vorkommen
* Darf nicht der Benutzername sein
* Darf nicht aus Wiederholungen von 3 oder mehr Zeichen bestehen (z.B. As1.$As1.$ ist unzulässig)

Die Standardrichtlinie ist :dfn:`strong`.

.. achtung:: Vom Ändern der Kennwortrichtlinie ist dringend abzuraten. Die Nutzung von schwachen Kennwörtern führen häufig zu kompromitierten Servern durch externe Angreifer.

Um den Wert auf none zu setzen, muss folgender Befehl ausgeführt werden ::

  config setprop passwordstrength Users none

Um den Wert auf strong zu setzen, muss folgender Befehl ausgeführt werden ::

  config setprop passwordstrength Users strong

Um zu prüfen, welche Regel derzeit angewendet wird, muss folgender Befehl ausgeführt werden ::

  config getprop passwordstrength Users

Ablauf
------

Das :index:`Kennwort läuft ab` ist standardmäßig aktiviert. Das maximale Kennwortalter beträgt 6 Monate vom Zeitpunkt des setzens des Kennworts.
|product| versendet eine E-Mail an den Benutzerm wenn das Kennwort abläuft.

.. hinweis:: |product| verweist auf das Datum des letzten Kennwortwechsels. Ist dies älter als 6 Monate sendet der Server eine E-Mail an den Benutzer mit dem Hinweis, dass das Kennwort abgelaufen ist. Der Benutzer muss das Kennwort nun ändern.
Zum Beispiel: Der letzte Kennwortwechsel war im Januar und es wird eine Anmeldung im Oktober durchgeführt. |product| geht nun davon aus, dass das Kennwort abgelaufen ist und benachrichtig den Benutzer.

Wenn die Kennwörter für alle Benutzer nicht ablaufen sollen oder auch abgelaufene Kennwörter weiterhin gültig sein sollen, müssen folgende Befehle ausgeführt werden ::

  config setprop passwordstrength PassExpires no
  signal-event password-policy-update

Um das Ablaufen des Kennworts für einzelne Benutzer zu deaktivieren, müssen folgende Befehle ausgeführt werden (<Benutzer> durch den Benutzernamen ersetzen):
  
  db accounts setprop <Benutzer> PassExpires no
  signal event password-policy-update


Einige Befehle um die derzeitige Richtlinie abzufragen:

Das maximale Kennwortalter abfragen (Standard: 180) ::

  config getprop passwordstrength MaxPassAge


Das minimale Kennwortalter abfragen (verhindert das mehrfache ändern des Kennworts innerhalb eines Zeitraums) (Standard: 0) ::
  
  config getprop passwordstrength MinPassAge


Anzahl an Tagen, an denen eine E-Mail an den Benutzer gesendet wird, bevor das Kennwort abläuft (Standard: 7) ::

  config getprop passwordstrength PassWarning


Um diese Einstellungen zu ändern, ersetze den :command:`getprop` durch :command:`setprop` und füge den gewünschten Wert an das Ende des Befehls hinzu.
Um die Information über das Ablaufen des Kennworts bereits 14 Tage vor Ablauf zu versenden, ist der Befehl ::

  config setprop passwortstrength PassWarning 14

Abschließend müssen die geänderten Einstellungen übernommen werden:

  signal-event password-policy-update


Verhalten von abgelaufenen Kennwörtern
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Nachdem das Kennwort abgelaufen ist, ist der Benutzer weiterhin in der Lage E-Mails zu senden und zu empfangen. Der Benutzer kann aber nicht mehr auf Netzwerkfreigaben und Drucker (Samba) zugreifen oder auf Computer, falls der Computer in der Domäne des |product|s ist.


Domänenkennwort
---------------

Falls |product| als Domänencontroller konfiguriert ist, können Benuter in Kennwort über Windows ändern.

Wenn das Kennwort über Windows geändert wird, kann das Kennwort nicht kürzer als 6 Zeichen sein - unabhänging von den in |product| konfigurierten Kennwortrichtlinien.
Windows prüft zuerst das Kennwort und sendet dies anschließend an |product| wo es dann anhand der konfigurierten Kennwortrichtlinien geprüft wird.

Sprache der Benachrichtigungen
==============================

Die Standardsprache für Benachrichtigungen ist Englisch.
Wenn diese geändert werden soll, muss folgender Befehl ausgeführt werden: ::

  config setprop sysconfig DefaultLanguage <lang>

Beispiel für Deutsch: ::

  config setprop sysconfig DefaultLanguage de_DE.utf8

Benutzer importieren
====================

|product| kann Benutzer anhand einer CSV-Datei importieren.
Diese Datei muss einen Benutzer pro Zeile enthalten. Die Werte der Zeile sind mittels TAB separiert und müssen dem folgenden Format entsprechen: ::

 Benutzername    Vorname    Nachname    E-Mail    Kennwort

Beispiel: ::

  mario   Mario   Rossi   mario@example.org       112233


Zunächst muss sichergestellt werden, dass der E-Mail-Server installiert ist. Anschließend muss die CSV-Datei auf den Server hochgeladen werden und folgender Befehl ausgeführt werden: ::

  /usr/share/doc/nethserver-directory-<Version>/import_users <Dateiname>

Zum Beispiel: Der Pfad zur CSV-Datei ist :file:`/root/users.csv`. Dann lautet der Befehl: ::

  /usr/share/doc/nethserver-directory-`rpm --query --qf "%{VERSION}" nethserver-directory`/import_users /root/users.csv


Der Befehl kann mehrfach ausgeführt werden. Bereits existierende Benutzer werden dabei übersprungen.

.. hinweis:: Der Befehl schlägt fehl, wenn das E-Mail-Servermodul nicht installiert ist.

