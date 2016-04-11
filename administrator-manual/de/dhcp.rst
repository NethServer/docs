.. index::
   single: DHCP
   alias: DHCP, Dynamic Host Configuration Protocol
   single: PXE
   alias: PXE, Preboot eXecution Environment

.. _dhcp-section:

===================
DHCP und PXE Server
===================

Der :dfn:`Dynamic Host Configuration Protocol` (DHCP) [#DHCP]_ Server zentralisiert die Verwaltung des Netzwerks für alle Geräte, die zum Netzwerk verbunden sind und DHCP nutzen.
Wenn ein Computer (oder ein Gerät wie Drucker, Smartphone usw.) sich mit dem Netzwerk verbinden, kann es vom DHCP Server unter der Verwendung des DHCP Protokolls die Netzwerkkonfiguration anfragen.
Der DHCP Server stellt dann die Netzwerkparameter wie IP-Adresse, Subnetmask, Gateway, DNS-Server und weitere relevate Netzwerkparameter bereit.

.. note:: Meist sind Netzwerk-Geräte so konfiguriert, dass diese standardmäßig DHCP nutzen.

Die :dfn:`Preboot eXecution Environment` (PXE) [#PXE]_ Spezifikation erlaubt es einen Netzwerkgerät beim Starten das Betriebssystem von einem Netzwerkpfad anstelle der lokalen Installation zu laden.
Dies geschieht über das DHCP- und TFTP-Protokoll. Unter :ref:`dhcp_pxe` ist ein Beispiel aufgeführt, das diese Konfiguration zeigt.

.. _dhcp_configuration:

DHCP Konfiguration
==================

Der DHCP-Server kann auf allen *grünen* und *blauen* Netzwerkadaptern aktiviert werden (siehe :ref:`network-section`).
|product| wird eine freie IP-Adresse innerhalb der konfigurierten :dfn:`DHCP range` zuweisen. Diese kann unter :guilabel:`DHCP > DHCP Server` konfiguriert werden.

Der DHCP-Bereich muss innerhalb des Netzwerks definiert werden, das von einem Netzwerkadapter bereitgestellt wird.
Zum Beispiel wenn der grüne Netzwerkadapter die IP/Netzwerkmaske ``192.168.1.1/255.255.255.0`` hat, muss der IP-Bereich z.B. in folgendem Bereich liegen ``192.168.1.2-192.168.1.254``.

.. _dhcp_reservation:

Host IP Reservierung
====================

Der DHCP-Server teilt einem Netzwerkgerät eine IP-Adresse nur für einen Zeitraum zu ("Lease time"). 
Nach einer gewissen Zeit wird die IP-Adresse wieder für neue Netzwerkgeräte freigegeben, wenn das Gerät, das einer IP-Adresse zugewiesen ist, sich nicht beim DHCP-Server gemeldet hat (d.h. lange nicht eingeschaltet wurde).
Wenn ein Gerät immer die selbe IP-Adresse benötigt, kann eine *IP Reservierung* für die MAC-Adresse dieses Gerätes vorgenommen werden. Auf diese Weise erhält das Gerät bei jeder Anforderung, auch nach langer Zeit, immer die selbe IP-Adresse.

Unter :guilabel:`DHCP > IP Reservierungen` können die aktuellen Reservierungen eingesehen werden.

* eine Zeile mit der Schaltfläche :guilabel:`IP Reservierung` zeigt einen Eintrag mit einer zeitweisen IP-Zuweisung (grau);

* eine Zeile mit der Schaltfläche :guilabel:`Bearbeiten` zeigt einen Eintrag, der eine IP-Reservierung erhalten hat (schwarz). 
  Ein kleines Icon mit zwei schwarzen Pfeilen beim Hostnamen zeigt, dass eine DHCP lease abgelaufen ist.
  Dies ist normal, sofern der Host eine statische IP-Adresse hat und die Reservierung auf dem DHCP-Server durchgeführt wurde, damit diese IP nicht vom DHCP-Server vergeben wird.

.. _dhcp_pxe:

Starten aus einer Netzwerkkonfiguration (PXE-Boot)
==================================================

Um es Systemen zu ermöglichen aus dem Netzwerk zu starten, müssen folgende Bedingungen erfüllt sein:

* Der :ref:`DHCP <dhcp_configuration>` Server muss installiert und konfiguriert sein. (Siehe vorherige Abschnitte)

* Der :dfn:`TFTP` Server [#TFTP]_ muss konfiguriert sein

* Der Softwareclient, bereitgestellt via TFTP.

.. index::
   single: TFTP
   alias: Trivial File Transfer Protocol; TFTP

.. _dhcp_tftp:

TFTP ist ein sehr einfaches Dateiübertragungsprotokoll und wird normalerweise genutzt um automatisch Konfigurations- und Bootdateien zu übertragen.

In |product| wird TFTP zusammen mit dem DHCP-Modul installiert und ist standardmäßig aktiviert.
Um den Zugriff auf den TFTP-Server zu ermöglichen, muss eine Datei nur in den Ordner :file:`/var/lib/tftpboot` abgelegt werden.

.. note:: Um TFP zu deaktivieren, muss folgender Befehl in der Konsole als Root ausgeführt werden: ::
	    
	     config setprop dhcp tftp-status disabled
	     signal-event nethserver-dnsmasq-save

Als Beispiel wird nun eine Konfiguration durchgeführt, die ein CentOS aus dem Netzwerk startet.
Dazu in |product| in der Konsole folgende Befehle ausführen: ::

 yum install syslinux
 cp /usr/share/syslinux/{pxelinux.0,menu.c32,memdisk,mboot.c32,chain.c32} /var/lib/tftpboot/
 config setprop dnsmasq dhcp-boot pxelinux.0
 signal-event nethserver-dnsmasq-save 
 mkdir /var/lib/tftpboot/pxelinux.cfg

Anschließend die Datei :file:`/var/lib/tftpboot/pxelinux.cfg/default` erstellen und folgenden Inhalt einfügen: ::

 default menu.c32
 prompt 0
 timeout 300

 MENU TITLE PXE Menu

 LABEL CentOS
   kernel CentOS/vmlinuz
   append initrd=CentOS/initrd.img

Anschließend ein CentOS-Verzeichniss erstellen: ::

 mkdir /var/lib/tftpboot/CentOS
 
In dieses Verzeichniss die Dateien :file:`vmlinuz` und :file:`initrd.img` kopieren.
Diese Dateien sind öffentlich und können im ISO-Image gefunden werden, in dem Verzeichniss :file:`/images/pxeboot` oder vom CentOS-Mirror heruntergeladen werden.

Als letzten Schritt den Client starten und PXE-Boot auswählen (oder "Boot from Network") direkt nach dem Einschalten des PCs. 

.. Rubric:: Referenzen

.. [#DHCP] Dynamic Host Configuration Protocol (DHCP)
           http://en.wikipedia.org/wiki/Dynamic_Host_Configuration_Protocol
.. [#TFTP] Trivial File Transfer Protocol
           https://en.wikipedia.org/wiki/Tftp
.. [#PXE] Preboot eXecution Environment
          http://en.wikipedia.org/wiki/Preboot_Execution_Environment

