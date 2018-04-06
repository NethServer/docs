.. _team_chat-section:

======================
Team chat (Mattermost)
======================

The :index:`team chat` module installs Mattermost Team Edition platform inside |product|.

Mattermost is an Open Source, private cloud :index:`Slack`-alternative. Check out the excellent official documentation: https://docs.mattermost.com/.

Configuration
=============

Mattermost installation needs a dedicated virtual host, a FQDN like ``chat.nethserver.org``.
 
Before proceed with the configuration, make sure to create the corresponding DNS record. If |product| act as the DNS server of your LAN, please refer to :ref:`dns-section`.

If you're server is using Let's Encrypt certificate as default, make sure also to have a corresponding public DNS record. See :ref:`server_certificate-section` for more info.

How to configure:

1. Access :guilabel:`Team chat` page inside the Server Manager
2. Check :guilabel:`Enable Mattermost Team Edition`, then enter a valid FQDN inside :guilabel:`Virtual host name` field (eg. ``chat.nethserver.org``)
3. Open the entered host name inside the browser, eg: ``https://chat.nethserver.org``.
   At first access, a wizard will create the administrator user

The following features are enabled by default:

- mail notifications
- push notifications for mobile apps
- redirect from HTTP to HTTPS


Authentication
==============

Mattermost authentication is *not* integrated with any Account Provider.
The Mattermost administrator should take care of user and teams creation.
To ease this task, the system administrator can use the ``mattermost-bulk-user-create`` command.

The command will:

- create a default team named as the Company from :ref:`organization_contacts-section`
- read all users from local or remote Account Providers and create them inside Mattermost

Please note that:

- disabled or existing users will be skipped
- a random password will be generated for each user

Invocation example: ::

  mattermost-bulk-user-create

  ...
  Creating default team: example (Example Org) ... OK
  Skipping locked user: 'goofy'
  Skipping locked user: 'admin'
  Creating user: 'pluto' with password '6aW221o7' ... OK
  ...

.. note::

   Users are not automatically synced inside Mattermost.
   Each time a user is created or removed, remember to execute ``mattermost-bulk-user-create`` command or
   manually create the user using Mattermost administration web interface.
   
Forcing a common default password
---------------------------------

It's possible to set a default password for each new Mattermost user, just append the default
password to command invocation. 

Example: ::

  mattermost-bulk-user-create Password,1234

