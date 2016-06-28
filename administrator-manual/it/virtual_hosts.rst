.. _virtual_host-section:

.. index:: virtual host
   single: HTTP

============
Virtual host
============

L'hosting virtuale è un metodo che consente di ospitare più nomi di dominio diversi su un singolo server. Su |product|, dalla pagina `Virtual host` è possibile configurare siti web come virtual host Apache

Nomi di dominio (FQDN)
-------------------------

È la lista dei nomi di dominio FQDN che sono associati al virtual host. I valori devono essere separati con "," (virgola).
Per raggiungere il virtual host sarà anche necessario un record DNS. Se abilitata l'opzione nella sezione "Azioni aggiuntive", un alias  per ogni FQDN verrà automaticamente creato su "DNS > Alias Server", ma è utile solo per i client che usano il server come DNS.

Configurare un'applicazione web
--------------------------------

Quando si crea un virtual host, viene creata automaticamente una cartella /var/lib/nethserver/vhost/`NOME`. 
Se è stato abilitato l'accesso FTP, sarà possibile caricare file sul virtual host usando un client FTP e il nome del virtual host come username.

.. warning:: L'FTP è disabilitato di default, bisogna anche abilitarlo dalla pagina di configurazione FTP

La password di autenticazione HTTP dovrebbe essere diversa da quella dell'FTP, in quanto l'FTP è usato per caricare contenuti, la password HTTP per limitare l'accesso alla lettura dei contenuti.  

Permessi Apache 
---------------

I file caricati con l'FTP hanno gruppo "apache". Se è necessario consentire il permesso di scrittura o esecuzione ad apache, è possibile cambiare i permessi del gruppo usando il client FTP

.. warning:: Se una virtual host contiene del codice eseguibile, come script PHP, 
             i permessi utente e le implicazioni di sicurezza vanno valutati con 
             attentamente
