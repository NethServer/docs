=================
Yomi mail sandbox
=================

.. warning::

  The sandbox service must be explicitly enabled for each server. For more information, please contact Nethesis sales.

Yomi sandbox is an automated malware analysis system provided by `Yoroi <http://yoroi.company/>`_.

Every mail message received or sent by the server is analyzed by the mail filter.
If the message contains attachments of MIME type used to deliver malware the attached file
is uploaded to the sandbox for analysis.
Yomi analyzes the behavior of the file when executed inside a realistic but isolated environment
and return a confidence score.

Suspicious files will receive an high SPAM score and will be likely moved inside the Junk folder.

Requirements
============

Yomi sandbox is automatically enabled after installation if:

- the server is correctly registered to `my.nethesis.it <https://my.nethesis.it/>`_
- the antivirus check is enabled inside the mail filter
- the server has a valid entitlement to access the service

The administrator can check if all requirements are satisfied using the following command: ::

 check-sandbox-status

If everything is correctly set, the output should look like this: ::

  [OK] Sandbox is enabled


Configuration
=============

The sandbox should not require any tuning, but it can be disabled from command line.

To disable it: ::

  config setprop yomi status disabled
  signal-event nethserver-yomi-update

To enable it again: ::

  config setprop yomi status enabled
  signal-event nethserver-yomi-update
