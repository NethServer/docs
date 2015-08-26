Abilitare i repository YUM specifici con il comando: ::

 yum localinstall -y http://mirror.nethserver.org/nethserver/nethserver-release-6.7.rpm

Per installare il sistema di base eseguire: ::

 nethserver-install

Oppure, per installare contestualmente del software addizionale,
passare il nome dei moduli desiderati come parametro allo script di
installazione.  Esempio: ::

 nethserver-install nethserver-mail nethserver-nut

Al termine dell'installazione, :ref:`accedere al Server Manager
<access-section>` per :ref:`installare il software
<package_manager-section>` addizionale.
