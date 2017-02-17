Abilitare i repository YUM specifici con il comando: ::

 yum localinstall -y http://mirror.nethserver.org/nethserver/nethserver-release-6.rpm

Per installare il sistema di base eseguire: ::

 nethserver-install

Oppure, per installare contestualmente del software addizionale,
passare il nome dei moduli desiderati come parametro allo script di
installazione.  Esempio: ::

 nethserver-install nethserver-mail nethserver-nut

Promozione ad Enterprise
========================

Per promuovere il sistema a |product| Enterprise seguire le indicazioni riportate in `questo link`_.

.. _`questo link`: http://helpdesk.nethesis.it/support/solutions/articles/3000062689-promozione-nethserver-enterprise-6-x-community-ad-enterprise
 
Passi successivi
================

Al termine dell'installazione, :ref:`accedere al Server Manager
<access-section>` per :ref:`installare il software
<package_manager-section>` addizionale.
