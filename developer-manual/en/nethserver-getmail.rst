==================
nethserver-getmail
==================

The package configures getmail using cron.

For each enabled account the system:

* generates a ``.cfg`` file inside the ``/var/lib/getmail`` directory from the template ``/etc/e-smith/templates/getmailrc``
* adds a line inside the ``/etc/cron.d/getmail``, all getmail instances use a non-blocking flock
* delivers the messages using dovecot-lda

All operations are logged in ``/var/log/maillog``. 

Database
--------

All records of type ``getmail`` are saved inside the ``getmail`` database.

Properties:

* The key is the mail account to be downloaded
* ``status``: can be ``enabled`` or ``disabled``, default is ``enabled``
* ``Account``: local user where messages will be delivered. Should be in the form *user@domain*
* ``Server``: server of the mail account
* ``Username``: user name of the mail account
* ``Password``: password of the mail account
* ``Delete``: numbers of days after downloaded messages will be deleted, ``-1`` means never, ``0`` means immediately
* ``Time``: integer number rappresenting the minutes between each check, valid valued are between 1 and 60
* ``VirusCheck``: if ``enabled``, check downloaded messages for virus using amavis clamd instance
* ``SpamCheck``: if ``enabled``, check downloaded messaged for SPAM using spamc
* ``Retriever``: can be any getmail retriever, see `Getmail official doc <http://pyropus.ca/software/getmail/documentation.html>`_
    Retrievers available in the web interface:

    * ``SimplePOP3Retriever``
    * ``SimplePOP3SSLRetriever``
    * ``SimpleIMAPRetriever``
    * ``SimpleIMAPSSLRetriever`` 

Example: ::

 db getmail set test@neth.eu getmail Account pippo@neth.eu status enabled Password Nethesis,1234 Server localhost Username test@neth.eu Retriever SimplePOP3Retriever Delete enabled Time 30 VirusCheck enabled SpamCheck enabled


Virus check
-----------

If a virus is found inside a received mail, the message is dropped.

Example of log in ``/var/log/maillog``: ::

  Jul 26 22:31:52 test getmail: msg  4/12 (702 bytes) msgid 000008bb5785fb1d from <root@test.neth.eu> dropped by filter Filter_classifier clamdscan (allow_root_commands="True", arguments="('-c', '/etc/clamd.d/amavisd.conf', '--stdout', '--no-summary', '--infected', '-')", command="clamdscan", exitcodes_drop="('1',)", exitcodes_keep="('0',)", group="None", ignore_stderr="False", path="/usr/bin/clamdscan", unixfrom="False", user="None")


