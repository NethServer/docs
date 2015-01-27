==========
WebVirtMgr
==========

Questo componente viene usato per gestire le macchine virtuali attraverso una semplice intefaccia web.

* Creazione e rimozione di macchine virtuali
* Creazione di template per la creazione di macchine
* Accesso remoto alla macchine attraverso il web
* Interfaccia grafica accattivante.

Panoramica
=============
Questo componente è **disabilitato** di default. Puoi abilitarlo attraverso il pannelo dedicato (Gestione macchine virtuali).

L'applicazione web ascolta sulla porta **8000** della vostra macchina host.

Per accedere all'interfaccia web bisogna effettuare il login con le credenziali che possono essere trovate nel pannello dedicato.


**username:** *admin*

**password** (modificabile) *random-alphanumeric*.

Configuration
=============


WebVirtMgr
----------
Dopo l'installazione del pacchetto, per abilitare il servizio cliccare nel radio button alla voce **Abilita**.


WebVirtMgr-Console
------------------
Dopo l'installazione del pacchetto, per abilitare il servizio che gestisce la consolo remota cliccare nel radio button alla voce **Abilita**.

Credentials
-----------
Come è possibile vedere nel pannello dedicato è possibile cambiare le credenziali di accesso.

Start
-----
Vai su ``http://HOST_IP:8000/`` per vedere l'interfaccia web. Effettua il login and divertiti.

Warning
=======
Per creare un'interfaccia bridge, creare l'interfaccia **prima** con il metodo standard nella dashboard di NethServer e poi seleziona l'interfaccia nel tab *network* nell'interfaccia di webvirtmgr.
