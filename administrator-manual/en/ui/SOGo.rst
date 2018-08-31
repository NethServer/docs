.. _SOGoUi-section:

==============
SOGo Groupware
==============

The :index:`SOGo` groupware is the missing component of your infrastructure, 
it sits in the middle of your servers to offer your users a uniform and 
complete interface to access their information.. See also :ref:`SOGo-section`.


Enable CalDAV and CardDAV
   CalDAV allow users to access and share calendar data on a server.
   CardDAV allows users to access and share contact data on a server.

Enable Microsoft ActiveSync
   ActiveSync is a mobile data (email, calendar, task, contact) synchronization app developed by Microsoft.

Allow Users to add other IMAP accounts
   Allow users to add other IMAP accounts that will be visible from the SOGo Webmail interface.

Administrators
   List of users with administrative privileges over all the user datas.

Make SOGO accessible only from this domain name
   SOGo is per default accessible from all server's virtualhosts, 
   If you specify a domain name here, SOGo will be usable only from this domaine name.

Number of workers
   This is the amount of instances of SOGo that will be spawned to handle multiple requests simultaneously. 
   You should have at least one worker per activesync device connected.
