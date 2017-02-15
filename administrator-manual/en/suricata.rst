.. _suricata-section:

==============
IPS (Suricata)
==============

Suricata is a :dfn:`IPS` (:index:`Intrusion Prevention System`), a system for the network intrusion analysis. 
The software analyzes all traffic through the firewall searching for known attacks and anomalies. 

When an attack or anomaly is detected, the system can decide whether to block traffic 
or simply save the event on a log (:file:`/var/log/suricata/fast.log`). 

:index:`Suricata` can be configured accordingly to following policies. Each policy consists of several rules: 

* Connectivity: check a large number of vulnerabilities, do not impact on non-realtime applications (eg VoIP) 
* Balanced: suitable for most scenarios, it is a good compromise between security and usability (recommended) 
* Security: safe mode but very invasive, may impact on chat and peer-to-peer applications
* Expert: the administrator must manually select the rules from the command line 


.. note:: The use of an IPS impacts on all traffic passing through the firewall. Make sure you fully understand 
   all the implications before enabling it.

