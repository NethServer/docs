===================
nethserver-suricata
===================

The IPS (Intrusion Prevention System) module configures Suricata using the netfilter queue (NFQUEUE). 
NFQUEUE is an iptables and ip6tables target which delegate the decision on packets to a userspace software.

All traffic will be analyzed by Suricata itself and events are logged inside ``/var/log/suricata/eve.json``.
See EveBox for a report of blocking and alerting rules.

Suricata rules are managed by Pulledpork.

Manually enable/disable Suricata
================================

Suricata will analyze network traffic only if ``nfqueue`` property inside the ``firewall`` key is set to enabled.
The web interface will take care of this by assuring both ``firewall{nfqueue}`` and ``suricata{status}`` are set to ``enabled`` (or ``disabled``).

Enabling: ::

  config setprop firewall nfqueue enabled
  config setprop suricata status enabled
  signal-event firewall-adjust
  signal-event nethserver-suricata-save

Disabling: ::

  config setprop firewall nfqueue disabled
  config setprop suricata status disabled
  signal-event firewall-adjust
  signal-event nethserver-suricata-save


Troubleshooting
===============

When troubleshooting network traffic, just remember that Suricata will intercept all the traffic.

To temporary disable Suricata use: ::

  config setprop firewall nfqueue disabled
  signal-event firewall-adjust

To re-enable Suricata: ::
  
  config setprop firewall nfqueue enabled
  signal-event firewall-adjust
