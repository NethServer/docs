.. _team_chat-section:

======================
Team chat (Mattermost)
======================

The :index:`team chat` module installs Mattermost Team Edition platform inside |product|.

Mattermost is an Open Source, private cloud :index:`Slack`-alternative. Check out the excellent official documentation: https://docs.mattermost.com/.

Configuration
=============

Mattermost installation needs a dedicated virtual host, an FQDN like ``chat.nethserver.org``.
 
Before proceeding with the configuration, make sure to create the corresponding DNS record. If |product| act as the DNS server of your LAN, please refer to :ref:`dns-section`.

If your server is using a Let's Encrypt certificate as default, make also sure to have a corresponding public DNS record. See :ref:`server_certificate-section` for more info.

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
The Mattermost administrator should take care of users and teams creation.
To ease this task, the system administrator can use the :guilabel:`Import users` button..

The command will:

- create a default team named as the Company from :ref:`organization_contacts-section`
- read all users from local or remote Account Providers and create them inside Mattermost

Please note that:

- users disabled in the Server Manager, or already existing in Mattermost, will be skipped
- a random password will be generated for each user

.. note::

   Users are not automatically synced inside Mattermost.
   Each time a user is created or removed, remember to execute ``mattermost-bulk-user-create`` command or
   manually create the user using Mattermost administration web interface.
   
