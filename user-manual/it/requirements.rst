========================
Requisiti per cominciare
========================

Dotazione
=========

La dotazione minima richiesta da  NethServer è un macchina con CPU a 64
bit, 1 GB di RAM e 8 GB di spazio su hard disk. Si consiglia l’uso di
due hard disk in modo che venga garantita l’integrità dei dati
attraverso il supporto automatico RAID1.

Compatibilità Hardware
======================

NethServer è compatibile con tutto l'hardware certificato per
Red Hat® Enterprise  Linux® (RHEL ®)

`https://hardware.redhat.com/ <https://hardware.redhat.com/>`

Si richiede HW di classe server e non desktop, dato che garantisce
maggiore compatibilità e qualità dei componenti.

N.B. Un hardware dichiarato compatibile con Linux non è detto
sia compatibile con RHEL/NethServer.

RAID
====

NethServer supporta sia configurazioni RAID hardware che
software. Nel caso si scelga di implementare la
configurazione RAID hardware assicurarsi che il controller sia presente
nella lista dei controller supportati.

NethServer di default prevede il RAID 1 software e supporta anche il
RAID 5.

Si consiglia di usare il RAID software perché viene controllato di
default da un apposito software pre-configurato che segnala eventuali
anomalie.

