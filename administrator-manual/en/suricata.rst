.. _suricata-section:

==============
IPS (Suricata)
==============

Suricata is a :dfn:`IPS` (:index:`Intrusion Prevention System`), a system for the network intrusion analysis. 
The software analyzes all traffic on the firewall searching for known attacks and anomalies. 

When an attack or anomaly is detected, the system can decide whether to block traffic 
or simply save the event on a log (:file:`/var/log/suricata/fast.log`). 

:index:`Suricata` can be configured using sets of rules organized in uniform categories.
Each category can be set to:

   - Enable: traffic matching rules from this categories will be reported
   - Block: traffic matching rules from this categories will be dropped
   - Disable: rules from this categories are ignored

.. note:: The use of an IPS impacts on all traffic passing on the firewall. Make sure you fully understand 
   all the implications before enabling it. In particular, pay attention to blocking rules that may stop
   updates to the system itself.

Rule categories
===============

Suricata is configured to use free rules from https://rules.emergingthreats.net/. [#]_

Rules are divided into categories listed below.

ActiveX
  Attacks and vulnerabilities(CVE, etc.) regarding ActiveX.

Attack Response
  Responses indicative of intrusion—LMHost file download, certain
  banners, Metasploit Meterpreter kill command detected, etc. These are designed to catch
  the results of a successful attack. Things like "id=root", or error messages that indicate a
  compromise may have happened.

Botcc (Bot Command and Control)
  These are auto-generated from several sources of
  known and confirmed active Botnet and other Command and Control hosts. Updated daily,
  primary data source is Shadowserver.org. Bot command and control block rules generated
  from shadowserver.org, as well as spyeyetracker, palevotracker, and zeustracker. Port
  grouped rules offer higher fidelity with destination port modified in rule.

Botcc Portgrouped
  Same as above, but grouped by destination port.

Chat
  Identification of traffic related to numerous chat clients, irc, and possible check-in
  activity.

CIArmy
  Collective Intelligence generated IP rules for blocking based upon
  www.cinsscore.com.

Compromised
  This is a list of known compromised hosts, confirmed and updated daily
  as well. This set varied from a hundred to several hundreds rules depending on the data
  sources. This is a compilation of several private but highly reliable data sources. Warming:
  Snort does not handle IP matches well load-wise. If your sensor is already pushed to the
  limits this set will add significant load. We recommend staying with just the botcc rules in a
  high load case.

Current Events
  Category for active and short lived campaigns. This category covers
  exploit kits and malware that will be aged and removed quickly due to the short lived
  nature of the threat. High profile items that we don’t expect to be there long—fraud
  campaigns related to disasters for instance. These are rules that we don't intend to keep in
  the rule set for long, or that need to be tested before they are considered for inclusion. Most
  often these will be simple sigs for the Storm binary URL of the day, sigs to catch CLSID's of
  newly found vulnerable apps where we don't have any detail on the exploit, etc.

Decoder-events
  Suricata specific. These rules log normalization events related to
  decoding.

Deleted
  Rules removed from the rule set.

DNS
  Rules for attacks and vulnerabilities regarding DNS. Also category for abuse of the
  service for things such as tunneling.

DOS
  Denial of Service attempt detection. Intended to catch inbound DOS activity, and
  outbound indications.

Drop
  Rules to block spamhaus “drop” listed networks. IP based. This is a daily updated
  list of the Spamhaus DROP (Don't Route or Peer) list. Primarily known professional
  spammers. More info at http://www.spamhaus.org.

Dshield
  IP based rules for Dshield Identified attackers. Daily updated list of the DShield
  top attackers list. Also very reliable. More information can be found at
  http://www.dshield.org.

Exploit
  Exploits that are not covered in specific service category. Rules to detect direct
  exploits. Generally if you're looking for a windows exploit, Veritas, etc, they'll be here.
  Things like SQL injection and the like, while they are exploits, have their own category.

Files
  Example rules for using the file handling and extraction functionality in Suricata.

FTP
  Rules for attacks, exploits, and vulnerabilities regarding FTP. Also includes basic
  none malicious FTP activity for logging purposes, such as login, etc.

Games
  Rules for the Identification of gaming traffic and attacks against those games.
  World of Warcraft, Starcraft, and other popular online games have sigs here. We don't
  intend to label these things evil, just that they're not appropriate for all environments.

HTTP-Events
  Rules to log HTTP protocol specific events, typically normal operation.

Info
  General rules to track suspicious host network traffic.

Inappropriate
  Rules for the identification of pornography related activity. Includes
  Porn, Kiddy porn, sites you shouldn't visit at work, etc. Warning: These are generally quite
  Regex heavy and thus high load and frequent false positives. Only run these if you're really
  interested.

Malware
  Malware and Spyware related, no clear criminal intent. The threshold for
  inclusion in this set is typically some form of tracking that stops short of obvious criminal
  activity. This set was originally intended to be just spyware. That's enough to several rule 
  categories really. The line between spyware and outright malicious bad stuff has blurred to
  much since we originally started this set. There is more than just spyware in here, but rest
  assured nothing in here is something you want running on your net or PC. There are URL
  hooks for known update schemed, User-Agent strings of known malware, and a load of
  others.

Misc.
  Miscellaneous rules for those rules not covered in other categories.

Mobile Malware
  Specific to mobile platforms: Malware and Spyware related, no clear
  criminal intent.

Netbios
  Rules for the identification, as well as attacks, exploits and vulnerabilities
  regarding Netbios. Also included are rules detecting basic activity of the protocol for
  logging purposes.

P2P
  Rules for the identification of Peer-to-Peer traffic and attacks against. Including
  torrents, edonkey, Bittorrent, Gnutella, Limewire, etc. We're not labeling these things
  malicious, just not appropriate for all networks and environments.

Policy
  Application Identification category. Includes signatures for applications like
  DropBox and Google Apps, etc. Also covers off port protocols, basic DLP such as credit card
  numbers and social security numbers. Included in this set are rules for things that are
  often disallowed by company or organizational policy. Myspace, Ebay, etc.

SCADA
  Signatures for SCADA attacks, exploits and vulnerabilities, as well as protocol
  detection.

SCAN
  Things to detect reconnaissance and probing. Nessus, Nikto, portscanning, etc. Early
  warning stuff.

Shellcode
  Remote Shellcode detection. Remote shellcode is used when an attacker wants
  to target a vulnerable process running on another machine on a local network or intranet.
  If successfully executed, the shellcode can provide the attacker access to the target machine
  across the network. Remote shellcodes normally use standard TCP/IP socket connections 
  to allow the attacker access to the shell on the target machine. Such shellcode can be
  categorized based on how this connection is set up: if the shellcode can establish this
  connection, it is called a "reverse shell" or a connect-back shellcode because the shellcode
  connects back to the attacker's machine.

SMTP
  Rules for attacks, exploits, and vulnerabilities regarding SMTP. Also included are
  rules detecting basic activity of the protocol for logging purposes.

SMTP-events
  Rules that will log SMTP operations.

SNMP
  Rules for attacks, exploits, and vulnerabilities regarding SNMP. Also included are
  rules detecting basic activity of the protocol for logging purposes.

SQL
  Rules for attacks, exploits, and vulnerabilities regarding SQL. Also included are rules
  detecting basic activity of the protocol for logging purposes.

Stream-events
  Rules for matching TCP stream engine events.

TELNET
  Rules for attacks and vulnerabilities regarding the TELNET service. Also
  included are rules detecting basic activity of the protocol for logging purposes.

TFTP
  Rules for attacks and vulnerabilities regarding the TFTP service. Also included are
  rules detecting basic activity of the protocol for logging purposes.

TLS-Events
  Rules for matching on TLS events and anomalies

TOR
  IP Based rules for the identification of traffic to and from TOR exit nodes.

Trojan
  Malicious software that has clear criminal intent. Rules here detect malicious
  software that is in transit, active, infecting, attacking, updating, and whatever else we can
  detect on the wire. This is also a highly important rule set to run if you have to choose.

User Agents
  User agent identification and detection.

VOIP
  Rules for attacks and vulnerabilities regarding the VOIP environment. SIP, h.323,
  RTP, etc.

Web Client
  Web client side attacks and vulnerabilities.

Web Server
  Rules for attacks and vulnerabilities against web servers.

Web Specific Apps
  Rules for very specific web applications.

WORM
  Traffic indicative of network based worm activity.

Bypass
======

The bypass disables IPS protection for selected hosts: all traffic from/to the given host will not be analyzed.

To create a bypass access the new Server Manager and open the :guilabel:`IPS` application, then go to the :guilabel:`Bypass`
page and click on :guilabel:`Add bypass` button.

Fill the :guilabel:`Bypass` field and click on :guilabel:`Save` button. The :guilabel:`Bypass` field supports:

- host objects
- host groups objects
- IP range objects
- raw IP addresses

EveBox
======

:index:`EveBox` is a web based :index:`alert` and event management tool for events generated by the Suricata.

It can be accessed from the Server Manager under the :guilabel:`Applications` page.

.. [#]
   Categories documentation source:
   `proofpoint <https://www.proofpoint.com>`_ - `ETPro Category Descriptions <http://tools.emergingthreats.net/docs/ETPro%20Rule%20Categories.pdf>`_
