=====================
Rubrica Centralizzata
=====================

La rubrica centralizzata di |product| permette di aggregare i contatti provenienti da più fonti e renderli consultabili in sola lettura dai vari client.

L'aggiunta o la modifica dei contatti dovrà essere effettuata alla fonte degli stessi, quindi, e non direttamente sulla rubrica centralizata.

La sincronizzazione dei contatti dalle varie fonti esterne viene eseguita di default tutte le notti, il comando per forzarla ed eventualmente pianificarla più frequentemente è: ::

 /usr/share/phonebooks/phonebook

.. warning:: Se durante la sincronizzazione i database sorgente non sono raggiungibili, la rubrica centralizzata risulterà vuota.

La rubrica centralizzata è accessibile in LDAP, attivandone l'esportazione, impostando come Dominio Base: ::

 dc=phonebook,dc=nh

L'interfaccia permette di attivare l'importazione dei contatti provenienti da tutte le rubriche di SOGo condivise a tutti gli utenti locali, dei contatti condivisi del |product_cti| e dei Numeri Brevi di |product_voice|.

E' possibile importare nella rubrica centralizzata i contatti provenienti da altre sorgenti interne e/o esterne al |product|, per questo scopo vengono eseguiti tutti gli script presenti nella directory ::

 /usr/share/phonebooks/scripts

Gli script personalizzati possono essere scritti in un qualsiasi linguaggio, assicurarsi che ciascuno script sia eseguibile. Per farlo: ::

 chmod a+x /usr/share/phonebooks/scripts/mioscript.sh

La directory ::

 /usr/share/phonebooks/scripts

fa parte del backup della configurazione.

Nella directory ::

 /usr/share/phonebooks/samples/

si trovano degli esempi di script per collegare diversi tipi di sorgenti.

Per sorgenti di dati esterne (Mysql,PostgreSQL) al |product| è possibile creare un record ODBC che permetta il collegamento.

Configurazione ODBC
-------------------

1. Definire il record ODBC che descrive la connessione al database

Esempio MySql: ::

 config set miarubrica ODBC Description "MiaRubrica" Driver "MySQL" Server "localhost" Database miarubrica Port 3306
   
Esempio PostgreSQL ::

 config set miarubrica ODBC Description "MiaRubrica" Driver "PostgreSQL" Server 192.168.5.168 Database miarubrica Port 5432

Esempio MSSQL ::

 config set business ODBC Description "MSSQL" Driver "MSSQL" Server 192.168.5.169 Database PROVA Port 1433

2. Eseguire: ::

 signal-event nethserver-unixODBC-update

Testare il funzionamento
------------------------
Testare il funzionamento (sintassi: isql -v nomeDSN utente password): ::

 isql -v miarubrica sa test
 +---------------------------------------+
 | Connected!                            |
 |                                       |
 | sql-statement                         |
 | help [tablename]                      |
 | quit                                  |
 |                                       |
 +---------------------------------------+

Provare una query su una tabella del database selezionato precedentemente ::

 SQL> select * from Customers
 ....
 SQL> quit


Dettagli database
-----------------

::

 Database: phonebook
 Tabella: phonebook

Per visualizzare i campi della rubrica centralizzata: ::

 mysql -e "describe phonebook.phonebook"

Configurazione Avanzata Importazione SOGo
-----------------------------------------

L'interfaccia consente di attivare o disattivare l'importazione di tutte le rubriche condivise a tutti gli utenti locali, è possibile ottenere una configurazione più specifica con dei comandi da shell.

Abilitare l'esportazione rubrica di un singolo utente SOGo: ::

 config setprop phonebook sogo giacomo

Ritornare alla configurazione di default, importazione di tutte le rubriche condivise di SOGo: ::

 config setprop phonebook sogo all

Disabilitare esportazione rubriche di SOGo: ::

 config setprop phonebook sogo disabled

