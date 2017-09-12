==================
nethserver-freepbx
==================

This package configures FreePBX and Asterisk for NethServer
MariaDB, Asterisk 13 and FreePBX 14 will be installed and configured.

FreePBX Web UI Access
======================

FreePBX is now reachable at https://IP_ADDRESS/freepbx from green interfaces. To add an IP address or a network from red allowed to access interface, configure it from NethServer Web UI under "PBX Access" page


Backup
======

Since FreePBX configuration is stored in MariaDB, database dump are split inside data and configuration backup:

* configuration backup: contains the ``asterisk`` db with all configurations (extensions, trunks, etc.)
* data backup: contanins the ``asteriskcdrdb`` db containg all PBX events

Open services from external networks
====================================

IAX and WebRTC access can be opened to external networks from server manager web gui -> PBX Access

SIP and other ports, from command line (Dangerous! Do it only if you know what you're doing)

::

    config setprop asterisk access public
    signal-event firewall-adjust


Users
=====

User are synced with NethServer users. You can manually force Userman module sync with

::

    /usr/bin/scl enable rh-php56 "/usr/sbin/fwconsole userman sync"


WebRTC
======

You can create WebRTC extensions following this official guide from freepbx:

- http://wiki.freepbx.org/display/FPG/WebRTC+Phone-UCP#WebRTCPhone-UCP-EnablingWebRTCPhoneforauser

After the installation of Certificate Manager and WebRTC modules there is a valid self-signed certificate that can be used for WebRTC.

How to test it
--------------

1. Install "Certificate management" module

2. From "Advanced settings" page:

   - Enable the mini-HTTP Server
   - Set "SIP Channel Driver" to `chan_pjsip`

3. From "SIP settings", inside the PJSIP tab, set the following values:

   - Certificate Manager: default
   - SSL Method: default
   - Verify Client: No
   - Verify Server: No
   - udp: yes
   - tcp: no
   - tls: no
   - ws: yes
   - wss: yes
   - Port listen: 5160

4. Configure a new PJSIP extension and set the following values:

   - Enable AVPF: yes
   - Enable ICE Support: yes
   - Media use received transport: no
   - RTP symmetric: yes
   - Media encryption: DTLS-SRTP
   - Require RTP (media) encryption: yes
   - Enable DTLS: yes
   - Use certificate: default
   - DTLS verify: no
   - DLTS setup: Act/Pass
   - DTLS Rekey Interval: 0


5. Restart asterisk and temporarly disable the firewall:

   ::
  
   systemctl restart asterisk
   shorewall clear

6. Open `https://<server_ip>:8089/ws` URL with the browser and accept the certificate

7. Try with one of the below WebRTC cients:

- http://jssip.net/
- https://www.doubango.org/sipml5/

Known bugs
----------

- WebRTC under Chrome is not allowed in HTTP
- WebRTC in UCP module on FreepBX may not work as expected. (http://community.freepbx.org/t/webrtc-phone-with-https/26698/9)
- WebRTC may not work on Firefox

Custom User Management configuration
------------------------------------

The ``nethserver-freepbx-conf-users action`` configures users using NethServer SSSD configuration. 
This creates an entry in userman FreePBX module called ``NethServer [AD|LDAP]``.

If you need to edit this entry and you don't want it to be modified when nethserver-freepbx-conf-users is launched again, 
change it's name adding "Custom" (or any other string) at the end. Example: 'NethServer AD' -> 'NethServer AD Custom'

If you remove ``NethServer [AD|LDAP]`` string, another entry will be created by ``nethserver-freepbx-conf-users`` action.

To check user synchronization, use this command: ::

 /usr/bin/scl enable rh-php56 -- /usr/sbin/fwconsole userman --syncall --force --verbose

Syncronization need a secure connection, use SSL or enable ``STARTTLS`` in ``Account Provider`` configuration in NethServer Web GUI
