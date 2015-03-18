================
Note di rilascio
================

.. include:: changelog.rst.inc


Aggiornamento da 6.5
====================

L'aggiornamento del sistema deve essere eseguito dalla linea di comando.

1. Assicurarsi che il sistema sia aggiornato: ::

     yum update

2. Installare ``yum-presto`` per ridurre il volume complessivo dei dati da scaricare: ::

     yum install yum-presto
  
3. Dal momento che la struttura dei repository è cambiata, eliminare il vecchio file di configurazione: ::

     rm -f /etc/yum.repos.d/NethServer.repo

4. Quindi, avviare l'aggiornamento: ::
  
     yum -c http://mirror.nethserver.org/nethserver/nethserver-6.6.conf update

5. Cose che possono essere aggiustate:

   * Aggiornare il fuso orario di default di PHP (``date.timezone`` INI
     setting) dal valore di default del sistema:

     1. Nella pagina :guilabel:`Data e ora` cambiare :guilabel:`Fuso
	orario` in un valore temporaneo e premere il pulsante
	:guilabel:`Salva`.

     2. Impostare il valore di :guilabel:`Fuso orario` a quello originale
	e premere di nuovo :guilabel:`Salva`.
  
6. Al termine, riavviare il sistema.


Aggiornamento da 6.6 beta1
==========================

Gli URL dei repository YUM sono cambiati. Prima di aggiornare il
sistema scaricare la nuova configurazione di YUM: ::

  curl https://raw.githubusercontent.com/nethesis/nethserver-release/6.6-0.9/root/etc/yum.repos.d/NethServer.repo > /etc/yum.repos.d/NethServer.repo
  
