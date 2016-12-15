===================
nethserver-suricata
===================

The IPS (Intrusion Prevention System) module configures Suricata using the netfilter queue (NFQUEUE). 
NFQUEUE is an iptables and ip6tables target which delegate the decision on packets to a userspace software.

All traffic will be analyzed by Suricata itself.

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




Policies
========

The package implements 4 policies. A policy is a set of rules which will change Suricata behavior. Available policies are:

* *Connectivity*: You run a lot of real time applications (VOIP, financial
  transactions, etc), and don't want to run any rules that could affect
  the current performance of your gateway. Rules in this category
  make Suricata happy, additionally this category focuses on the high
  profile most likely to affect the largest number of people type of
  vulnerabilities.

* *Balanced*:  You are normal, you run normal stuff and you want normal
  security protections.  This is the best policy to start from if you are 
  new, old, or just plain average.  If you don't have any special
  requirements for super high speeds or super secure networks start here.

* *Security*:  You don't care about dropping your bosses email, everything
  in your environment is tightly regulated and you don't tolerate people 
  stepping outside of your security policy.  This policy hates on IM, P2P,
  vulnerabilities, malware, web apps that cause productivity loss, remote
  access, and just about anything not related to getting work done.  
  If you run your network with an iron fist start here.

* *Expert*: no policy is applied. All rules must be manually selected by the administrator (see pulledpork documentation).


Changing the current policy to ``security``: ::

  config setprop pulledpork Policy security
  signal-event nethserver-pulledpork-save


Troubleshooting
===============

When troubleshooting network traffic, just remember that Suricata will intercept all the traffic.

To temporary disable Suricata use: ::

  config setprop firewall nfqueue disabled
  signal-event firewall-adjust

To re-enable Suricata: ::
  
  config setprop firewall nfqueue enabled
  signal-event firewall-adjust
