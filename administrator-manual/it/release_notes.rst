================
Note di rilascio
================

.. include:: changelog.rst.inc


Aggiornamento da 6.5
====================

L'aggiornamento del sistema deve essere eseguito dalla linea di comando.

Assicurarsi che il sistema sia aggiornato: ::

  yum update

Dal momento che la struttura dei repository è cambiata, eliminare il vecchio file di configurazione: ::

  rm -f /etc/yum.repos.d/NethServer.repo

Quindi, avviare l'aggiornamento: ::
  
  yum -c http://mirror.nethserver.org/nethserver/nethserver-6.6.conf update

Cose che possono essere aggiustate:

* Aggiornare il fuso orario di default di PHP (``date.timezone`` INI
  setting) dal valore di default del sistema:

  1. Nella pagina :guilabel:`Data e ora` cambiare :guilabel:`Fuso
     orario` in un valore temporaneo e premere il pulsante
     :guilabel:`Salva`.

  2. Impostare il valore di :guilabel:`Fuso orario` a quello originale
     e premere di nuovo :guilabel:`Salva`.
  
Al termine, riavviare il sistema.


Aggiornamento da 6.6 beta1
==========================

Gli URL dei repository YUM sono cambiati. Prima di aggiornare il
sistema scaricare la nuova configurazione di YUM: ::

  curl https://raw.githubusercontent.com/nethesis/nethserver-release/6.6-0.9/root/etc/yum.repos.d/NethServer.repo > /etc/yum.repos.d/NethServer.repo
  
