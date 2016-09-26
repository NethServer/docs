.. _suricata-section:

==============
IPS (Suricata)
==============

Suricata è un :dfn:`IPS` (:index:`Intrusion Prevention System`), un sistema per la previsione delle intrusioni in rete.
Il software analizza tutto il traffico che attraversa il firewall alla ricerca di attacchi noti e anomalie.

Quando un attacco o un'anomalia sono stati rilevati, il sistema può decidere se bloccare il traffico
o limitarsi a salvare l'evento sul log (:file:`/var/log/suricata/fast.log`).

:index:`Suricata` può essere configurato secondo le policy riportate. Ogni policy è composta da più regole:

* Connectivity: controlla un vasto numero di vulnerabilità, non impatta su applicazioni realtime (es. VoIP)
* Balanced: adatta alla maggior parte degli scenari, è un buon compromesso fra sicurezza e usabilità (consigliata)
* Security: modalità molto sicura ma invasiva, può impattare sul funzionamento di applicazioni di chat e peer to peer
* Esperto: l'amministratore deve procedere a selezionare manualmente le regole da linea di comando 


.. note:: L'utilizzo di un IPS impatta su tutto il traffico passante per il firewall. Assicurarsi di aver compreso a fondo
   tutte le problematiche prima di attivarlo.
