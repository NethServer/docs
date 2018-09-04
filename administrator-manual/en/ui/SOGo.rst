.. _SOGoUi-section:

==============
SOGo Groupware
==============

See also :ref:`SOGo-section`.


Enable CalDAV and CardDAV
   CalDAV allow users to access and share calendar data on a server.
   CardDAV allows users to access and share contact data on a server.

Enable Microsoft ActiveSync
   ActiveSync is a mobile data (email, calendar, task, contact) synchronization app developed by Microsoft.

Allow Users to add other IMAP accounts
   Allow users to add other IMAP accounts that will be visible from the SOGo Webmail interface.

Administrators
   List of users with administrative privileges over all the user datas.

Notifications
   Several different types of notifications(email-based) are available. Activate them according your needs.

Make SOGO reachable only from this domain(FQDN)
   SOGo is per default accessible from all server's virtualhosts, 
   If you specify a domain name here, SOGo will be usable only from this domaine name.

Number of workers
   This is the amount of instances of SOGo that will be spawned to handle multiple requests simultaneously. 
   You should have at least one worker per activesync device connected.

Maximum time in second
   Parameter used to set the maximum amount of time, in seconds, SOGo will wait before doing an internal 
   check for data changes (add, delete, and update).
