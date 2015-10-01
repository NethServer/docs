Abilitare i repository YUM specifici con il comando: ::

 yum localinstall -y http://mirror.nethserver.org/nethserver/nethserver-release-6.7.rpm

Per installare il sistema di base eseguire: ::

 nethserver-install

Per promuovere la macchina a |product| eseguire da linea di comando: ::

    yum -c http://update.nethesis.it/nethserver-6_7-nethesis-support.conf install nethserver-register nethserver-nethserverenterprise-branding

Come ultimo passaggio per attivare il supporto Nethesis :ref:`accedere
al Server Manager <access-section>` e :ref:`registrare la macchina
<registration-section>`.


