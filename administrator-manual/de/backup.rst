======
Backup
======

:index:`Backup` ist der einzige Weg |product| im Fehlerfall wiederherzustellen.
|product| kennt zwei Arten von :index:`Sicherung`en:

* :index:`Konfigurationssicherung`
* :index:`Datensicherung`

Die Konfigurationssicherung sichert nur die Konfigurationsdaten von |product|.
Diese Art der Sicherung wird jede Nacht ausgeführt und erstellt ein neues Archiv, :file:`/var/lib/nethserver/backup/backup-config.tar.xz`, falls sich die Konfiguration in den letzten 24 Stunden geändert hat.
Die Konfigurationssicherung sichert außerdem eine Liste der installierten Module. Alle Module werden bei einer Rücksicherung wieder installiert.
Dieses Backupverfahren wird genutzt um im Falle des Fehlerfalls |product| schnellstmögoich wiederhergestellt werden kann.
Nachdem die Konfiguration aus dem Backup zurückgesichert wurde, kann die Datenrücksicherung durchgeführt werden, auch wenn |product| bereits in Betrieb ist.

Die Datensicherung wird aktiviert, indem das "Backup"-Mdoul installiert wird. Die Datensicherung enthält alle Daten wie die Home-Ordner der Benutzer sowie deren E-Mails. Die Datensicherung wird jede Nacht ausgeführt und kann inkrementell oder vollständig in einem wöchentlichen Intervall durchgeführt werden.
Die Datensicherung enthält ebenfalls die Daten aus der Konfigurationssicherung.

Das Backup kann an drei verschiedene Orte gesichert werden:

* USB: Eine USB-Laufwerk, dass an einem USB-Port von |product| angeschlossen ist (Siehe: :ref:`backup_usb_disk-section`)
* CIFS: Windows Netzwerkfreigaben (z.B. durch einen Server, PC oder NAS)
* NFS: Linux Netzwerkfreigaben, (z.B. durch einen Server, PC oder NAS; in der Regel schneller als CIFS)

Das Ergebniss einer Sicherung kann an den Administrator oder an eine E-Mail-Adresse gesendet werden.

.. hinweis:: Das Zielverzeichniss basiert auf dem Zielservernamen: Sollte der FQDN des Zielservers sich ändern, muss dieser auch im Backup angepasst werden.

Rücksicherung
=============

Zunächst muss sichergestellt sein, dass das Sicherungsmedium angeschlossen oder erreichbar ist.

Befehlszeile
------------

Dateien anzeigen
^^^^^^^^^^^^^^^^

Mit diesem Befehl lassen sich alle Dateien anzeigen, die in einem Backup enthalten sind: ::

 backup-data-list

Die Ausführung des Befehls kann, abhängig von der Backupgröße, einige Zeit in Anspruch nehmen.

Dateien und Ordner
^^^^^^^^^^^^^^^^^^

Alle relevanten Dateien sind im Verzeichniss :file:`/var/lib/nethserver/` zu finden:

* E-Mails: :file:`/var/lib/nethserver/vmail/<user>`
* Netzwerkfreigaben: :file:`/var/lib/nethserver/ibay/<name>`
* Home-Verzeichnisse: :file:`/var/lib/nethserver/home/<user>`

Zum Wiederherstellen einer Datei oder eines Ordners ist folgender Befehl zu verwenden: ::

  restore-file <position> <file>

Beispiel: Den E-Mail-Account "franz" nach :file:`/tmp` wiederherstellen: ::

  restore-file /tmp /var/lib/nethserver/vmail/franz

Beispiel: Den E-Mail-Account "franz" im Original wiederherstellen: ::

  restore-file / /var/lib/nethserver/vmail/franz


|product| kann auch alte Versionen von Ordnern und Dateien wiederherstellen.

Beispiel: Eine Version der Datei "myfile" von vor 15 Tagen nach /tmp wiederherstellen: ::

  restore-file -t 15D /tmp "/var/lib/nethserver/ibay/test/myfile" 

Der Parameter ``-t`` gibt die Anzahl an Tagen an, die seit dem Backup vergangen sein sollen.


Grafische Oberfläche
--------------------

Unter dem Menüpunkt :menuselection:`Wiederherstellen` kann nach Backups gesucht werden. Eine Wiederherstellung von Daten aus einem Backup kann über die Oberfläche durchgeführt werden

Es gibt zwei Möglichkeiten der Wiederherstellung:

* Wiederherstellen der Daten in den ursprünglichen Pfad. Vorhandene Daten werden mit den Daten aus dem Backup überschrieben.
* Wiederherstellen der Daten in den ursprünglichen Pfad. Wiederhergestellte Daten werden jedoch in einen neuen Ordner zurückgesichert. Dieser lautet: ::

  /complete/path/of/file_YYYY-MM-DD (YYYY-MM-DD ist das Datum der Wiederherstellung)

Um das Suchfeld zu nutzen, mpssen mindestens 3 Zeichen eingegeben werden. Die Suche startet dann automatisch und markiert die übereinstimmenden Daten.

Über die Schaltfläche **Wiederherstellen** können die Daten wiederhergestellt werden.

.. hinweis:: Mehrere Daten können mittels drücken der Strg-Taste ausgewählt werden.


Rücksicherung im Fehlerfall
===========================

|product| wird in zwei Phasen wiederhergestellt: Zuerst die Konfiguration, anschließend den Daten.
Direkt nach der Wiederherstellung der Konfigration ist |product| wieder verwendbar, sofern alle Module vollständig wieder installiert wurden.
Zusätzliche Module können vor oder nach der Wiederherstellung installiert werden.
Beispiel: Wenn der E-mail-Server installiert ist, kann |product| wieder E-Mails senden und empfangen.

Weitere wiederhergestellte Konfigurationen:

* Benutzer und Gruppen
* SSL Zertifikate

.. hinweis:: Das root- und admin-Passwort wedern nicht wiederhergestellt.

Vorgehensweise zur Wiederherstellung:

1. Installiere eine neue |product|-Installation mit dem gleichen Hostname wie dem alten
2. Konfiguriere ein Datenbackup, sodass |product| auf die gesicherten Daten zugreifen kann
3. Wenn die alte (defekte) |product|-Installation das Netzwerk-Gateway war, nicht vergessen das Firewall-Modul zu installieren.
4. Stelle die Konfiguration aus dem Backup wieder her.
   :guilabel:`Backup (configuration) > Restore` im Servermanager oder führe folgenden Befehl aus:
   :command:`restore-config`
5. Sofern eine Warnung es verlangt, konfiguriere die Zuordnung der Netzwerkrollen erneut. Siehe :ref:`restore-roles-section`.
6. Prüfe, ob alle korrekt funktioniert (soweit möglich ohne Daten)
7. Stelle die Datensicherung wieder her. Führe dazu folgenden Befehl aus: :command:`restore-data`

.. _restore-roles-section:
   
Netzwerkrollen wiederherstellen 
-------------------------------

Wenn eine Konfiguration auf einen fehlenden Netzwerkadapter verweist, erscheint unter :guilabel:`Dashboard`, :guilabel:`Backup (configuration) > Restore` und :guilabel:`Network` eine Warnung.
Dies passiert zum Beispiel in folgenden Fällen:

* Die Konfiguration wurde auf neuer Hardware wiederhergestellt
* Eine oder mehrere Netzwerkkarten wurde ersetzt
* Die Festplatten wurden in einem neuen System wieder eingebaut

Durch das Anklicken der Warnung erfolgt eine Weiterleitung zur Liste der vorhandenen Netzwerkadapter. Dort sind die Adapter markiert, welche keine Zugewiesene :ref:`role<network-section>` haben.
Diese Adapter haben ein Dropdown-Menü, in dem eine Rolle für die Wiederherstellung ausgewählt werden kann.

Beispiel: Wenn die Karte mit der Rolle *orange* ersetzt wurde, so zeigt das Dropdown-Menü eine Liste mit dem Eintrag ``orange`` bei dem Netzwerkadapter an.

Das gleiche geschieht, wenn der alte Netzwerkadapter ein Teil eines logischen Adapters war (z.B. Bridge oder Bond).

Beim Auswählen eines Eintrags aus dem Dropdown-Menü wird die alte Rolle auf den neuen Adapter übertragen.

Zum Übernehmen muss auf die Schaltfläche :guilabel:`Übernehmen` geklickt werden.

.. achtung:: Die Neuzuordnung muss vor dem Übernehmen gründlich geprüft werden! Ein Fehler kann dazu führen, dass der |product| nicht mehr erreichbar sein wird und vom Netzwerk isoliert ist!

Wenn die fehlende Rolle ``GRÜN`` ist, so fragt beim Starten von |product| eine interaktive Prozedur danach, ob das Problem gelöst werden soll. Dies ist nötig um wieder eine Verbindung zum |product| herstellen zu können und die weitere Verwaltung über den Servermanager zu tätigen.

.. _backup_config_rpms:

Installierte Module wiederherstellen
------------------------------------

Standardmäßig werden beim Wiederherstellen der Konfigurationsdaten auch die vorher installierten Module installiert.

Um dieses Verhalten zu unterbinden, muss dieser Befehl vor der Wiederherstellung ausgeführt werden: ::

  config setprop backup-config reinstall disabled
     
.. _backup_customization-section:


Datensicherung anpassen
=======================

Wenn weitere Software installiert wurde, kann ein Administrator die Liste der Dateien und Ordner anpassen, die ein- oder ausgeschlossen werden sollen.

Einschließen
------------

Wenn eine Datei oder ein Verzeichniss aus dem Datenbackup ausgeschlossen werden soll, muss eine Zeile in diese Datei eingefügt werden: :file:`/etc/backup-data.d/custom.include`.

Beispiel: Um eine installierte Software zu sichern, die unter :file:`/opt/mysoftware` installiert wurde, muss diese Zeile hinzugefügt werden:

  /opt/mysoftware

Ausschließen
------------

Wenn eine Datei oder ein Verzeichniss aus der Sicherung ausgeschlossen werden soll, dann muss eine Zeile in diese Datei eingefügt werden: :file:`/etc/backup-data.d/custom.exclude`.

Beispiel: Um alle Verzeichnisse, die "Download" heißen, auzuschließen, muss diese Zeile hinzugefügt werden: ::

  **Download**

Um das E-Mail-Postfach "test" aus der Datensicherung auszuschließen, füge diese Zeile hinzu: ::

  /var/lib/nethserver/vmail/test/ 

  
Der gleiche Syntax trifft auch auf die Konfigurationssicherung zu. Änderung müssen jedoch in der Datei :file:`/etc/backup-config.d/custom.exclude` durchgefürht werden.


.. hinweis:: Stelle sicher, dass keine leeren Zeilen in den editierten Dateien vorhanden sind (auch nicht am Ende!)


Konfigurationssicherung anpassen
================================

In der Regel ist es nicht notwendig, dass an der Konfigurationssicherung anpassung vorgenommen werden müssen.
Es kann jedoch in Einzelfällen nützlich sein - zum Beispiel bei eigenen SSL-Zertifikaten.
In diesem Fall sollten die Dateien, die die Zertifikate enthalten, in die Liste der zu sichernden Dateien aufgenommen werden.

Einschließen
------------

Wenn eine Datei oder ein Verzeichniss aus dem Datenbackup ausgeschlossen werden soll, muss eine Zeile in diese Datei eingefügt werden: :file:`/etc/backup-config.d/custom.include`.

Beispiel: Um die Datei :file:`/etc/pki/mycert.pem` zu sichern, füge folgende Zeile hinzu:

  /etc/pki/mycert.pem

In die Konfigurationssicherung gehören keine großen Datenmengen! Die Konfigurationssicherung enthält ausschließlich Daten, die zur Neukonfiguration von |product| notwendig sind! Daten (z.B. Freigaben und E-Mails-Postfächer) gehören in die Datensicherung!

Ausschließen
------------

Wenn eine Datei oder ein Verzeichniss aus der Sicherung ausgeschlossen werden soll, dann muss eine Zeile in diese Datei eingefügt werden: :file:`/etc/backup-config.d/custom.exclude`.

.. hinweis:: Stelle sicher, dass keine leeren Zeilen in den editierten Dateien vorhanden sind (auch nicht am Ende!)
   Der Syntax der Konfigurationsssicherung erlaubt nur einfache Datei- und Ordnernamen.

.. _backup_usb_disk-section:

USB-Laufwerk konfigurieren
==========================

Das geeignetste Dateisystem für USB-Laufwerke ist EXT3. FAT-Dateisysteme sind möglich aber nicht empfohlen. NTFS-Dateisysteme sind nicht unterstützt.

Vor dem Formatieren des USB-Laufwerks muss dieses an den Server angeschlossen werden. Anschließend muss der Gerätename ermittelt werden: ::

 # dmesg | tail -20

 Apr 15 16:20:43 mynethserver kernel: usb-storage: device found at 4
 Apr 15 16:20:43 mynethserver kernel: usb-storage: waiting for device to settle before scanning
 Apr 15 16:20:48 mynethserver kernel:   Vendor: WDC WD32  Model: 00BEVT-00ZCT0     Rev:
 Apr 15 16:20:48 mynethserver kernel:   Type:   Direct-Access           ANSI SCSI revision: 02
 Apr 15 16:20:49 mynethserver kernel: SCSI device sdc: 625142448 512-byte hdwr sectors (320073 MB)
 Apr 15 16:20:49 mynethserver kernel: sdc: Write Protect is off
 Apr 15 16:20:49 mynethserver kernel: sdc: Mode Sense: 34 00 00 00
 Apr 15 16:20:49 mynethserver kernel: sdc: assuming drive cache: write through
 Apr 15 16:20:49 mynethserver kernel: SCSI device sdc: 625142448 512-byte hdwr sectors (320073 MB)
 Apr 15 16:20:49 mynethserver kernel: sdc: Write Protect is off
 Apr 15 16:20:49 mynethserver kernel: sdc: Mode Sense: 34 00 00 00
 Apr 15 16:20:49 mynethserver kernel: sdc: assuming drive cache: write through
 Apr 15 16:20:49 mynethserver kernel:  sdc: sdc1
 Apr 15 16:20:49 mynethserver kernel: sd 7:0:0:0: Attached scsi disk sdc
 Apr 15 16:20:49 mynethserver kernel: sd 7:0:0:0: Attached scsi generic sg3 type 0
 Apr 15 16:20:49 mynethserver kernel: usb-storage: device scan complete
 
Ein anderer hilfreicher Befehl ist: ::

  lsblk -io KNAME,TYPE,SIZE,MODEL

In diesem Beispiel ist das USB-Laufwerk als *sdc* aufgeführt.

* Erstelle eine Linux-Partition auf dem USB-Laufwerk: ::

    echo "0," | sfdisk /dev/sdc

* Erstelle das Dateisystem auf der *sdc1*-Partition mit den Namen "backup": ::

    mke2fs -v -T largefile4 -j /dev/sdc1 -L backup

* Entferne das USB-Laufwerk und verbinde es anschließend erneut:

  Dies kann mit folgendem Befehl simuliert werden: ::

    blockdev --rereadpt /dev/sdc

* Nun wird auf der Seite :guilabel:`Sicherung (Daten)` ein Laufwerk "Backup" angezeigt.

