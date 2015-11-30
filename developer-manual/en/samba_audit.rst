===========
Samba-audit
===========

Package: nethserver-samba-audit

Samba Audit tracks and show in a simple web GUI all Samba operations made on an i-bay.

The package configure Samba standard audit and save the log on a special file. Every night a script parses the log file and puts all data into a MySQL database. The database can be explored using a simple web interface.

After installation, a new enable/disable option is shown inside the i-bay module. The web GUI can be accessed directly from the Dashboard using auto-created random URL.
The GUI is accessible only from local networks.

From the GUI the user can:

* filter log by username, date, i-bay name, path or ip
* remove old logs
* force parsing of log file

**Database example**

:: 

 test=ibay
    ...
    SmbAuditStatus=enabled
    ...


