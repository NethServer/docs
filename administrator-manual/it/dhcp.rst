.. _dhcp-section:

====
DHCP
====

Il server :dfn:`DHCP` (Dynamic Host Configuration Protocol) permette di controllare la configurazione
di rete di tutti i computer o dispositivi collegati alla LAN.
Quando un computer (o un dispositivo come una stampante, smartphone, etc.) si connette alla rete
il :index:`DHCP` gli assegna automaticamente un indirizzo IP valido e effettua la configurazione di
DNS e gateway.

Nella maggior parte dei casi i dispositivi sono già configurati per utilizzare il protocollo DHCP.
In caso contrario, è necessario abilitare manualmente questa configurazione nei singoli client.

Il server DHCP può essere abilitato su tutte le interfacce green e blue (vedi :ref:`network-section`).
Il sistema sceglierà un indirizzo IP libero all'interno dell':index:`intervallo DHCP` (:index:`range DHCP`) configurato.

.. note:: L'intervallo DHCP deve essere definito all'interno della rete configurata nell'interfaccia associata.

Esempio:

* interfaccia green con IP 192.168.1.1 e maschera di rete 255.255.255.0
* l'intervallo può andare da 192.168.1.2 a 192.168.1.254

Riserva IP
==========

Il server DHCP assegna automaticamente un indirizzo IP valido ogni qualvolta un computer si connette alla rete. 
Se si desidera che alcune macchine della LAN debbano avere sempre lo stesso indirizzo IP,
è possibile richiedere al server DHCP di assegnare un IP fissato sulla base dell'indirizzo MAC della scheda di rete della macchina.

Nella pagina :guilabel:`Riserva IP` sono elencati tutti gli indirizzi IP correntemente assegnati.
Per riservare l'indirizzo è sufficiente usare il pulsante :guilabel:`Riserva IP` oppure creare esplicitamente una
nuova configurazione inserendo indirizzo IP e indirizzo MAC del dispositivo.
