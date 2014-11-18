==============
POP3 connector
==============

The :index:`POP3 connector` allows you to configure a list of mail
accounts.  These accounts will be checked at regular intervals and
messages will be delivered to local users or groups.

.. note:: It is not recommended to use the POP3 connector as the
   primary method for managing e-mail.  Mail delivery can be affected
   by space and connectivity problems of provider's server.  Also the
   spam filter is less effective because original email information is
   lost.

The server uses a software named :index:`fetchmail`. Fetchmail
downloads mails from the POP3 provider and deliver them locally by
connecting directly to the local SMTP server. All messages are
filtered accordingly to configured rules. See
:index:`mail_filter-section`.

All operations are logged inside :file:`/var/log/fetchmail.log` file.

.. note:: Deleting an account will *not* delete already delivered
          messages.

