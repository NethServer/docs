========
WebTop 5
========

WebTop is a full-featured groupware which implements ActiveSync protocol.

Access to web interface is: ``https://<server_name>/webtop``.

.. note::       If |product| is bound to a remote Active Directory account provider
                a dedicated user account in AD is required by the module to be fully
                operational! See :ref:`join-existing-ad-section`.


Authentication
==============

Always use the full user name format ``<user>@<domain>`` for login to the
web application and Active Sync.

**Example**

* Server name: mymail.mightydomain.com
* Alternative mail domain: baddomain.net
* User: goofy
* Login: goofy@mightydomain.com

.. note::
   Active Sync protocol is supported only on Android and iOS devices.
   Outlook is not supported.
   Mail synchronization is currently not supported.


.. _webtop5_admin-section:

Admin user
----------

After installation, WebTop will be accessible using the administrator user.
The administrator user can change global settings and login as any other user,
however, it's not a system user and can't access any other service like Mail, Calendar, etc.

Default credentials are:

* User: *admin*
* Password: *admin*

The administrator user's password must be changed from within the WebTop interface.

.. warning::
   **Remember to change the admin password after installation!**


To check the mail of the system's user admin account use the following login: admin@<domain> where ``<domain>`` is the
domain part of server FQDN.

**Example**

* Server name: mymail.mightydomain.com
* User: admin
* Login: admin@mightydomain.com

Change admin password
^^^^^^^^^^^^^^^^^^^^^

Access WebTop using the ``admin`` user, then open user settings by clicking on the menu in the top-right corner.

.. image:: _static/webtop-settings.png

Go to :guilabel:`Settings` then click on guilabel:`Change password`.


If you want to reset the admin password from command line, use the following commands: ::

  curl -s https://git.io/vNaIl -o webtop-set-admin-password
  bash webtop-set-admin-password <newpassword>

Remember to replace ``<newpassword>`` with your actual new password, example: ::

  bash webtop-set-admin-password VeryInsecurePass
  

Two factor authentication (2FA)
===============================

WebTop support :index:`two factor authentication`.
The user can choose between:

- Google Authenticator: the code will be generated using Google Authenticator app (https://support.google.com/accounts/answer/1066447?co=GENIE.Platform%3DAndroid)
- Secondary mail: the access code will be sent to selected mail address

To enable 2FA:

- Click on the menu button on the top-right corner and select the :guilabel:`Settings` icon
- Then select :guilabel:`Security` and click on the :guilabel:`Activate button`.

.. image:: _static/webtop-2fa.png 


Synchronization with ActiveSync (EAS)
=====================================

Mobile devices can be synchronized using ActiveSync.
:index:`ActiveSync` can be used only for **contacts** and **calendars**.

.. note::

   To synchronize **e-mails** you should configure an IMAP account.

Apple iOS
---------

Access your :index:`iOS device`, navigate to Settings and add an Exchange account following the official guide: https://support.apple.com/en-us/HT201729

Fill the required fields with:

- **E-mail**: add your mail address, eg: goofy@nethserver.org
- **Server**: add your server public name, eg: mail.nethserver.org
- **Domain**: leave blank
- **User name**: enter your full user name, eg: goofy@nethserver.org
- **Password**: enter your password

Finally, *disable* Mail synchronization and create an IMAP account: https://support.apple.com/en-us/HT201320

.. note::

   iOS devices require a valid SSL certificate on the server.
   See :ref:`server_certificate-section`

Google Android
--------------

Access your :index:`Android device`, navigate to Settings, then select :guilabel:`Add account` -> :guilabel:`Exchange` (or "Company" for older releases).

Fill the required fields with:

- **User name**: enter your full user name, eg: goofy@nethserver.org
- **Password**: enter your password

Then select :guilabel:`Manual configuration` and change the name of the *Server* field accordingly
to your server public name.
Finally, if you have a self-signed certificate on your server, make sure to select :guilabel:`SSL/TLS (accept all certificates)` option.

Finally, *disable* Mail synchronization and create an IMAP account.

.. note::

   On some Android releases (notably Samsung), the User name and Domain must be entered in the same line.
   In this case, leave blank the field before the backslash character (\), and enter the user name in the following format: ``\goofy@nethserver.org``

Multiple calendars and contacts
-------------------------------

Calendars and address books shared by others with the user can be synchronized using the ActiveSync protocol.

Shared resources are displayed with the owner's name and category (the number in square brackets is the internal id).
Private events are not synchronized.

Mobile devices based on Apple iOS fully support folders / categories for calendar, contacts and activities (called reminders), including original colors.

Mobile devices based on Android support only calendars and contacts (activities are not supported), 
but using the Google Calendar application all items will have the same colour.

Installing and using the `CloudCal <https://pselis.com/cloudcal/>`_ application,
you can change the colors associated with each calendar, including shared ones.

On Android devices, contacts from shared phone books are merged with the personal phone book and displayed in 
a single view. Contacts can be modified and changes will be saved it the original source.

.. note::

  In order to receive data via EAS on mobile devices, it is necessary to verify 
  that the shared resources (Calendars and Contacts) have synchronization enabled (Full or Read only):

  .. image:: _static/webtop-multiple_sync.png
               :alt: Multiple synchronization

It is possible to enable or disable the synchronization for each shared resource (calendars and contacts).
The user can customize every resource sharing with him by deciding the type of synchronization.
 
To do so, just right click on the shared resource → Customize → Devices sync.:

  .. image:: _static/webtop-sync_shared_eas.png
               :alt: Sync shared EAS

The default setting is “Not active”.

Synchronization with CalDAV and CardDAV
=======================================

Calendars and address books can be synchronized also through :index:`CalDAV and CardDAV protocols`.

To synchronize a calendar, pick up its ``URL`` link right-clicking on the calendar and selecting :guilabel:`Links to this calendar`,
then use it to configure your third-party client.

To synchronize an address book, pick up its ``URL`` link right-clicking on the address book and selecting :guilabel:`Links to this addressbook`,
then use it to configure your third-party client.

To authenticate, provide your credentials in the following form:

- **User name**: enter your full user name (i.e. *goofy@nethserver.org*)
- **Password**: enter your password

Some third-party clients allow to simplify the configuration through the *autodiscovery* feature that automatically discovers the 
synchronizable resources, as in the case of mobile devices clients (i.e. Android or iOS devices).


.. note::

   If you are using clients that do not support autodiscovery, you need to use the full URL: ``https://<server_name>/webtop-dav/server.php``
   
   If you are using clients that support autodiscovery use URL: ``https://<server_name>``

Google Android
--------------

A good, free, Android third-party client is `Opensync <https://deependhulla.com/android-apps/opensync-app>`_.

- install the suggested app from the market;
- add a new account clicking on :guilabel:`+` key and select :guilabel:`Login with URL and username` method;
- insert the ``URL`` (``https://<server_name>``), complete username (i.e. *goofy@nethserver.org*) and password;
- click on the new profile and select the resources you want to synchronize.

Apple iOS
---------

CalDAV/CardDAV support is built-in on iOS, so to configure it:

- go to Settings -> Account and Password -> Add account;
- select :guilabel:`Other` -> Add :guilabel:`CalDAV` or :guilabel:`CardDAV` account;
- insert the server name (i.e. *server.nethserver.org*), complete username (i.e. *goofy@nethserver.org*) and password.

By default the syncronization ``URL`` uses the server principal name (``FQDN``), if you need to change it: ::

 config setprop webtop DavServerUrl https://<new_name_server>/webtop-dav/server.php
 signal-event nethserver-webtop5-update


Desktop clients
-----------------------------

**Thunderbird**

To use CalDAV and CardDAV on Thunderbird you need third-party add-ons like :guilabel:`Cardbook` (for contacts) and :guilabel:`Lightning` (for calendars).

- :guilabel:`Cardbook` add-on works fine, with easy setup and autodiscovery support.
- :guilabel:`Lightning` add-on doesn't support autodiscovery: any calendar must be manually added.

**Outlook**

- open source :guilabel:`Outlook CalDav Synchronizer` client works fine, supporting both CardDAV and CalDAV.

.. note::

   At the moment CalDAV and CardDAV support **only personal resources synchronization**.

.. warning::

   Webtop is a **clientless groupware**: its functionalities are fully available **only using the web interface**!

   The use of CalDAV/CardDAV through third-party clients **cannot be considered a web interface alternative**.


Sharing email folders or the entire account
===========================================

It is possible to share a single folder or the entire account with all the subfolders included.
Select the folder to share -> right click -> "Manage sharing":

.. image:: _static/webtop-sharing_mail_folder_1.png

- select the user to share the resource (1).
- select if you want to share your identity with the user and possibly even if you force your signature (2).
- choose the level of permissions associated with this share (3).
- if you need to change the permission levels more granularly, select "Advanced" (4).
- finally, choose whether to apply sharing only to the folder from which you started, or only to the branch of subfolders or to the entire account (5).

.. image:: _static/webtop-sharing_mail_folder_2.png

.. note::

   If you also select "Force signature", when this identity is used, the user signature from which the shared mail was received will be automatically inserted.

In this case, however, it is necessary that the personalized signature of the User from which it originates has been associated to the Email address and not to the User.

Sharing calendars and contacts
==============================

Sharing Calendar
----------------

You can share each personal calendar individually.
Select the calendar to share -> right click -> "Sharing and permissions":

.. image:: _static/webtop-sharing_cal_1.png

Select the recipient user of the share (or Group) and enable permissions for both the folder and the individual items:

.. image:: _static/webtop-sharing_cal_2.png

Sharing Contacts
----------------

In the same way, you can always share your contacts by selecting the directory you want to share -> right click -> "Sharing and permissions".
Select the recipient user of the share (or Group), and enable permissions for both the folder and the individual items.


Mail tags
=========

You can tag each message with different colored labels.
Just select a message, right-click and select :guilabel:`Tag`.

You can edit existing tags or add new ones selecting :guilabel:`Manage tags`.

Tags can be used to filter messages using the filter top bar.

Mail inline preview
===================

By default, the mail page will display a preview of the content of latest received messages.

This feature can be enabled or disabled from the :guilabel:`Settings` menu, under the :guilabel:`Mail` tab,
the check box is named :guilabel:`Show quick preview on message row`.

.. image:: _static/webtop-preview.png

Mail archiving
==============

Archiving is useful for keeping your inbox folder organized by manually moving messages.

.. note::
    Mail archiving is not a backup.

The system automatically creates a new special Archives folder  

.. image:: _static/webtop-archive_archive1.png

If the :guilabel:`Archives` folder does not appear immediately upon login, it will appear at the first archiving.

 There are three archiving criteria in :menuselection:`Settings -> Mail -> Archiving`

* **Single folder:** a single root for all archived emails
* **Per year:** a root for each year
* **By year / month:** a root for each year and month

.. image:: _static/webtop-archive_archive2.png

To maintain the original structure of the folders is possible to activate :guilabel:`Keep folder structure` 

.. image:: _static/webtop-archive_archive3.png

The archiving operation is accessible from the contextual menu (right click). Click on :guilabel:`Archive`

.. image:: _static/webtop-archive_archive4.png

The system will process archiving according to the last settings chosen.

Subscription of IMAP folders
============================

On WebTop, by default, all IMAP folders on the server are automatically subscribed and therefore visible since the first login.

If you want to hide from the view some folders, which is equivalent to removing the subscription,
you can do so by simply clicking the right mouse button on the folder to hide and select from the interactive menu the item "Hide from the list".

For example, if you want to hide the subfolder "folder1" from this list, just right-click on it and select "Hide from the list":

.. image:: _static/webtop-sub_imap_folder1.png

It is possible to manage the visibility of hidden folders by selecting the "Manage visibility" function:

.. image:: _static/webtop-sub_imap_folder2.png

For example, if you want to restore the subscription of the "folder1" just hidden, just select it from the list of hidden folders
and click on the icon on the left:  

.. image:: _static/webtop-sub_imap_folder3.png

Export events (CSV)
===================

To export calendars events in CSV (Comma Separated Value) format, click on the icon on top right corner.

.. image:: _static/webtop-export_calendar_csv.png

Finally, select a time interval and click on :guilabel:`Next` to export into a CSV file.

Nextcloud integration
=====================

.. note::

   Before proceeding, verify that the "Nextcloud" module has been installed 
   from :guilabel:`Software Center`

By default, Nextcloud integration is disabled for all users.
To enable it, use the administration panel which can be accessed using the webtop admin password

For example, if you want to activate the service for all webtop users, proceed as follows:

1. access the administrative panel and select "Groups":

   .. image:: _static/webtop-admin_panel_groups.png

2. modify the properties of the "users" group by double clicking and select the button related to the Authorizations:
   
   .. image:: _static/webtop-admin_panel_permission.png

3. add to existing authorizations those relating to both the ``STORE_CLOUD`` and ``STORE_OTHER`` resources by selecting the items as shown below:

   .. image:: _static/webtop-admin_panel_nextcloud_auth_1.png

   .. image:: _static/webtop-admin_panel_nextcloud_auth_2.png


   so get this:

   .. image:: _static/webtop-admin_panel_nextcloud_auth_3.png


4. save and close.

At this point from any user it will be possible to insert the Nextcloud resource (local or remote) in your personal Cloud.

To do this, simply select the Cloud button and add a new **"Nextcloud"** resource by right clicking on **"My resources"** and then **"Add resource"** in this way:

.. image:: _static/webtop-nextcloud_1.png

A precompiled wizard will open:

.. image:: _static/webtop-nextcloud_2.png

.. note::

   Remember to fill in the User name and Password fields related to access to the Nextcloud resource,
   otherwise it will not be possible to use the public link to the shared files

Proceed with the Next button until the Wizard is complete.

Use the personal Cloud to send and receive documents
====================================================

Cloud module allows you to send and receive documents throug web links.

.. note::

   The server must be reachable in HTTP on port 80
   
How to create a link to send a document
---------------------------------------
To create the link, select the button at the top right:

.. image:: _static/webtop-doc_cloud1.png

Follow the wizard to generate the link, use field :guilabel:`date` to set the deadline.

.. image:: _static/webtop-doc_cloud2.png

you can create a :guilabel:`password` to protect it:

.. image:: _static/webtop-doc_cloud3.png

The link will be generated and will be inserted in the new mail:

.. image:: _static/webtop-doc_cloud4.png
.. image:: _static/webtop-doc_cloud5.png

Downloading the file, generates a notification to the sender:

.. image:: _static/webtop-doc_cloud6.png

Request for a document
----------------------
To create the request, insert the subject of the email than select the button at the top right:

.. image:: _static/webtop-doc_cloud7.png

Follow the wizard. You can set both an expiration date and a password. The link will be automatically inserted into the message:

.. image:: _static/webtop-doc_cloud8.png

A request email will be sent to upload the document to the Cloud:

.. image:: _static/webtop-doc_cloud9.png

The sender will receive a notification for each file that will be uploaded:

.. image:: _static/webtop-doc_cloud10.png

To download the files just access your personal :menuselection:`Cloud --> Uploads --> Folder` with date and name:

.. image:: _static/webtop-doc_cloud11.png

Chat integration
================

Web chat integration installation is disabled by default for all users.

To enable chat integration:

1. Install "Instant messaging"" module from :guilabel:`Software Center`.

2. Access WebTop as admin user then enable the web chat authorization:

   - Access the :guilabel:`Administration` menu, then :menuselection:`Domains --> NethServer --> Groups --> Users --> Authorizations`
   - :menuselection:`Add (+) --> Services --> com.sonicle.webtop.core (WebTop) --> Resource --> WEBCHAT --> Action --> ACCESS`
   - Click :guilabel:`OK` then save and close

Audio and video WebRTC calls with chat (Beta)
=============================================

.. warning::
   This feature is currently released in Beta.
   When the final version will be released it is likely that the configurations previously made will be reset.

Configuration is currently only possible via the WebTop administration panel.
The settings to be inserted are documented `here <https://www.sonicle.com/docs/webtop5/core.html#webrtc-settings-section>`_ 
In addition to the WebRTC settings, it is also necessary to add the **XMPP BOSH** public URL as shown `here <https://www.sonicle.com/docs/webtop5/core.html#xmpp-settings>`_

From web interface by accessing the administration panel -> :guilabel:`Properties (system)` -> :guilabel:`Add` -> select :guilabel:`com.sonicle.webtop.core (WebTop)` and enter the data in the :guilabel:`Key` and :guilabel:`Value` fields according to the key to be configured:

``webrtc.ice.servers`` : defines the list of ICE servers as JSON arrays

``xmpp.bosh.url`` : specifies the XMPP URL that can be accessed via the BOSH protocol


For the key field ``webrtc.ice.servers`` as "Value" insert the content in json format that shows the values of these variables:

``url`` : URL ice server

``username`` : server username (optional)

``credential`` : server password (optional)

For example: ::

 [
  {
    'url': 'stun:stun.l.google.com:19302'
  }, {
    'url': 'stun:stun.mystunserver.com:19302'
  }, {
    'url': 'turn:myturnserver.com:80?transport=tcp',
    'username': 'my_turn_username',
    'credential': 'my_turn_password'
  }
 ]

For the key field ``xmpp.bosh.url`` as "Value" enter this type of URL: ``https://<public_server_name>/http-bind``

With these configurations, every user authorized to use the **WEBCHAT** service can perform audio and video calls with other users that are available on the same chat server through the buttons available on the chat window.

.. note::

   If the buttons are grayed out, the requirements for activating the call are not satisfied.
   For example: XMPP BOSH URL unreachable or ICE server unreachable.


Send SMS from contacts
======================

It is possible to send SMS messages to a contact that has the mobile number in the addressbook.
To activate sending SMS, first you need to choose one of the two supported providers: `SMSHOSTING <https://www.smshosting.it/it>`_ or `TWILIO <https://www.twilio.com/>`_.

Once registered to the service of the chosen provider, retrieve the API keys (AUTH_KEY and AUTH_SECRET) to be inserted in the WebTop configuration db.
The settings to configure are those shown `here <https://www.sonicle.com/docs/webtop5/core.html#sms-settings>`_ .

It is possible to do this in two ways:

1) from web interface by accessing the administration panel -> :guilabel:`Properties (system)` -> :guilabel:`Add` -> select :guilabel:`com.sonicle.webtop.core (WebTop)` and enter the data in the :guilabel:`Key` and :guilabel:`Value` fields according to the key to be configured:

``sms.provider`` = smshosting or twilio

``sms.provider.webrest.user`` = API AUTH_KEY

``sms.provider.webrest.password`` = API AUTH_SECRET

``sms.sender`` = (default optional)


2) through shell commands:

to configure the ``sms.provider`` key (smshosting for example): ::

 su - postgres -c "psql webtop5 -c \"insert into core.settings (\"service_id\",\"key\",\"value\") values ('com.sonicle.webtop.core','sms.provider','smshosting');\""
 
to configure the ``sms.provider.webrest.user`` key: ::

 su - postgres -c "psql webtop5 -c \"insert into core.settings (\"service_id\",\"key\",\"value\") values ('com.sonicle.webtop.core','sms.provider.webrest.user','API_AUTH_KEY');\""

to configure the ``sms.provider.webrest.password`` key: ::

 su - postgres -c "psql webtop5 -c \"insert into core.settings (\"service_id\",\"key\",\"value\") values ('com.sonicle.webtop.core','sms.provider.webrest.password','API AUTH_SECRET');\""
  
substituting the key obtained from the provider instead of 'API_AUTH_KEY' and 'API AUTH_SECRET'

The ``sms.sender`` key is optional and is used to specify the default sender when sending SMS.
It is possible to indicate a number (max 16 characters) or a text (max 11 characters).

to configure the ``sms.sender`` key: ::

 su - postgres -c "psql webtop5 -c \"insert into core.settings (\"service_id\",\"key\",\"value\") values ('com.sonicle.webtop.core','sms.sender','XXXXXXXXXX');\""
  
replacing 'XXXXXXXXXX' with the number or text of the default sender.

.. note::

   Each user always has the possibility to overwrite the sender by customizing it as desired through its settings panel: :guilabel:`WebTop` -> :guilabel:`Switchboard VOIP and SMS` -> :guilabel:`SMS Hosting service configured` -> :guilabel:`Default sender`
   
To send SMS from the addressbook, right-click on a contact that has the mobile field filled in -> :guilabel:`Send SMS`

Custom link buttons in launcher (Beta)
======================================

.. warning::
   This feature is currently released in Beta.
   When the final version will be released it is likely that the configurations previously made will be reset.

Configuration is currently only possible via the WebTop administration panel -> :guilabel:`Properties (system)` -> :guilabel:`Add` -> select :guilabel:`com.sonicle.webtop.core (WebTop)` and enter the data in the :guilabel:`Key` and :guilabel:`Value` fields according to the key to be configured:

``launcher.links`` : json array of link objects

In the "Value" field, enter the content in json format that shows the values of these variables:

``href`` : URL opened in a new browser tab

``text`` : descriptive text that appears with mouseover

``icon`` : icon image URL (to avoid scaling problems, use vector images)

For example: ::

 [
  {
    'href': 'https://www.google.it/',
    'text': 'Google',
    'icon': 'https://upload.wikimedia.org/wikipedia/commons/5/53/Google_%22G%22_Logo.svg'
  }, {
    'href': 'https://the/url/to/open',
    'text': 'The link text',
    'icon': 'https://the/icon/url'
  }
 ]

.. warning::
   The URL of the icon from which to retrieve the vector image must always be publicly reachable by the browser with which you connect.
   
If you can not retrieve an Internet link of the icon image, you can copy the image locally on the server in two different ways:

#. copying the file (for example ``icon.svg``) directly into the ``/var/www/html/`` directory of the server and using this type of URL for the 'icon' field of the Json file: ::

       'icon': 'https://<public_name_server>/<icon.svg>'
 
#. uploading the icon file to the public cloud of WebTop (where images are uploaded for mailcards) via the administration panel -> :guilabel:`Cloud` -> :guilabel:`Public Images`and insert a URL of this type for the 'icon' field of the Json file: ::

       'icon': 'https://<public_name_server>/webtop/resources/156c0407/images/<icon.svg>'

.. note::

   The configured custom link buttons will be shown to all users at the next login.


Browser notifications
=====================

With WebTop, the desktop notification mode integrated with the browser was introduced.

To activate it, simply access the general settings of your user:

.. image:: _static/webtop-desktop_notifications.png

It is possible to enable desktop notification in two modes:

- **Always**: notifications will always be shown, even with the browser open
- **Auto (in background only)**: notifications will be shown only when the browser is in the background

Once the mode is selected, a browser consent request will appear at the top left:

.. image:: _static/webtop-chrome_notifications.png

If you need to enable this consent later on a different browser just click on the appropriate button:

.. image:: _static/webtop-button_desktop_notifications.png


Mailcards of user and domain
============================

One of the main features of managing signatures on WebTop is the opportunity to integrate images or custom fields profiled per user.

To use the images you need to upload them to the public cloud through the WebTop admin user like this:

.. image:: _static/webtop-public_images.png

You can use the :guilabel:`Upload` button to load an image which is at the bottom or simply via a drag & drop.

.. note::

  Remember that the public images inserted in the signature are actually connected with a public link.
  To be visible to email recipients, the server must be reachable remotely on port 80 (http) and its FQDN name must be publicly resolvable.

To change your signature, each user can access the :menuselection:`Settings --> Mail --> Editing --> Edit User mailcard`:

.. image:: _static/webtop-edit_mailcard.png

The public image just uploaded will be able to recall it in the HTML editor of the mailcard with this button:

.. image:: _static/webtop-public_signature.png

.. note::

   The personal mailcard can be associated with the user or his email:
   by associating it by email it will also be possible to share the mailcard to other users with whom the identity is shared.

Through the :ref:`webtop5_impersonate-section` you can also set a general domain mailcard that will be automatically set for all users who have not configured their personal mailcard:

.. image:: _static/webtop-domain_mailcard.png

Furthermore, it will also be possible to modify personal information:

.. image:: _static/webtop-personal_information.png

that can be used within the parameterized fields within the domain mailcard editor:

.. image:: _static/webtop-domain_mailcard.png

In this way it is possible to create a single mailcard that will be automatically customized for every user who does not use his own mailcard.

Configure multiple mailcards for a single user
==============================================

It is possible to configure multiple mailcards (HTML signatures) for each individual user.

Access the :menuselection:`Settings --> Mail --> Identities` and create multiple identities:

.. image:: _static/webtop-sig_sig1.png

To edit every single signature select :menuselection:`Settings --> Mail --> Identities` then select each individual signature and click on the :guilabel:`edit mailcard` button

.. image:: _static/webtop-sig_sig2.png
.. image:: _static/webtop-sig_sig3.png

When finished, close the window and click YES:

.. image:: _static/webtop-sig_sig4.png

to use multiple mailcards, create a new email, and choose the signature:

.. image:: _static/webtop-sig_sig5.png


Manage identities
=================

In :menuselection:`settings --> mail --> identities` click :guilabel:`Add` and fill in the fields

.. image:: _static/webtop_manageident1.png

It is possible to associate the new identity with a folder in your account or of a shared account

**Local account:**

.. image:: _static/webtop_manageident2.png

**Shared account:**

.. image:: _static/webtop_manageident3.png

Otherwise the sent mails will always end up in the "Sent Items" folder of your personal account.

Subscribing remote resources
============================

WebTop supports subscription to remote calendars and contacts (directory) using cardDAV, calDav and iCal.

Remote calendars
----------------

An Internet Calendar can be added and synchronized.
To do so just click the right button on personal calendars, :guilabel:`Add Internet Calendar`.
Two types of remote calendars are supported: Webcal (ics format) and CalDAV.

.. note::

   Synchronization of Webcal calendars (ics) is always done by downloading every event on the remote resource every time, while only the differences are synchronized with the CalDAV mode
   
Example of Google Cal remote calendar (Webcal only - ICS)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

1) Take the public access ICS link from your Google calendar: :guilabel:`Calendar options -> Settings and sharing -> Secret address in iCal format`

2) On WebTop, add an Internet calendar of type Webcal and paste the copied URL without entering the authentication credentials in step 1 of the wizard.

3) The wizard will connect to the calendar, giving the possibility to change the name and color, and then perform the first synchronization.

.. note::

   The first synchronization may fail due to Google's security settings.
   If you receive a notification that warns you about accessing your resources you need to allow them to be used confirming that it is a legitimate attempt.

Remote contacts (directory)
---------------------------

Example of Google CardDAV remote address book
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

1) On Webtop, configure a new Internet address book, right-click on :guilabel:`Personal Categories -> Add Internet address book` and enter a URL of this type in step 1 of the wizard:
https://www.googleapis.com/carddav/v1/principals/XXXXXXXXXX@gmail.XXX/lists/default/
(replace the X your gmail account)

2) Enter the authentication credentials (as user name use the full address of gmail):

.. image:: _static/webtop-remote_phonebook.png

3) The wizard in the following steps will connect to the phonebook, giving the possibility to change the name and color, and then perform the first synchronization.

.. note::

    To be able to complete the synchronization it is necessary to enable on your account Google,
    in the security settings, the use of apps considered less secure (here a guide on how to do: https://support.google.com/accounts/answer/6010255?hl=it).

Synchronization of remote resources can be performed manually or automatically.

Automatic synchronization
^^^^^^^^^^^^^^^^^^^^^^^^^
To synchronize automatically you can choose between three time intervals: 15, 30 and 60 minutes.
The choice of the time interval can be made in the creation phase or later by changing the options.
To do this, right-click on the phonebook (or on the calendar), :guilabel:`Edit Category`, :guilabel:`Internet Addressbook` (or :guilabel:`Internet Calendar`):

.. image:: _static/webtop-sync_automatic.png

Manual synchronization
^^^^^^^^^^^^^^^^^^^^^^
To update a remote address book, for example, click on it with the right mouse button and then select the item "Synchronize":

.. image:: _static/webtop-sync_google.png

For CardDav address books, as well as for remote CalDAV calendars, you can select whether to perform a full synchronization or only for changes.
To do this, right-click on the phonebook (or on the calendar), :guilabel:`Edit Category`:

.. image:: _static/webtop-edit_sync_google.png

Select the desired mode next to the synchronization button:

.. image:: _static/webtop-edit_sync_google2.png

User settings management
========================
Most user settings can be directly managed by the user itself via the settings menu.
Locked settings require administration privileges.

The administrator can :index:`impersonate` users, to check the correctness and functionalities of the account, through a specific login:

* **User name**: admin!<username>
* **Password**: <WebTop admin password>

While impersonating you receive similar user privileges, allowing you to control exactly what the user can see.
Full administration of user settings is available directly in the administration interface, by right clicking on a user: the settings menu will open the full user settings panel, with all options unlocked.

It is also possible to make a massive change of the email domain of the selected users: select the users (Click + CTRL for multiple selection) to which you want to apply this change then right-click on :guilabel:`Bulk update email domain`.

SMTP setting
============

The default configuration for sending mail to the SMTP server is anonymous and without encryption on port 587.
It is possible to enable authenticated sending in this way: ::

  config setprop webtop SmtpAuth enabled
  
to enable encryption also: ::

  config setprop webtop SmtpStarttls enabled
  
To apply the new settings launch this event which will also restart the application: ::

  signal-event nethserver-webtop5-update

Changing the logo
=================

To modify and customize the initial logo that appears on the login page of WebTop,
you must upload the custom image file on the public images of the admin user and rename it with "login.png".

Proceed as follows:

1. log in with the WebTop user admin

2. select the cloud service and public images:

   .. image:: _static/webtop-public_images.png

3. upload the image (via the Upload button at the bottom left or simply dragging with a drag & drop)

4. rename the loaded image so that its name is **"login.png"** (use right click -> Rename):

   .. image:: _static/webtop-login_page.png

5. the next login will show the new logo on the login page

Change the public URL
=====================

By default, the public WebTop URL is configured with the FQDN name set in the server-manager.

If you want to change URL from this: ``http://server.domain.local/webtop`` to: ``http://mail.publicdomain.com/webtop``

execute these commands ::

  config setprop webtop PublicUrl http://mail.publicdomain.com/webtop
  signal-event nethserver-webtop5-update

Change default limit "Maximum file size"
========================================

There are hard-coded configured limits related to the maximum file size:

- Maximum file size for chat uploads (internal default = 10 MB)
- Maximum file size single message attachment (internal default = 10 MB)
- Maximum file size for cloud internal uploads (internal default = 500 MB)
- Maximum file size for cloud public uploads (internal default = 100 MB)

To change these default values for all users, the following keys can be added via the admin interface: :guilabel:`Properties (system) -> Add`

**Maximum file size for chat uploads**

  - Service: ``com.sonicle.webtop.core``
  - Key: ``im.upload.maxfilesize``

**Maximum file size for single message attachment**

  - Service: ``com.sonicle.webtop.mail``
  - Key: ``attachment.maxfilesize``

**Maximum file size for cloud internal uploads**

  - Service: ``com.sonicle.webtop.vfs``
  - Key: ``upload.private.maxfilesize``

**Maximum file size for cloud public uploads**

  - Service: ``com.sonicle.webtop.vfs``
  - Key: ``upload.public.maxfilesize``
   
.. note::

  The value must be expressed in Bytes (Example 10MB = 10485760)
   
Importing contacts and calendars
================================

WebTop supports importing contacts and calendars from various file formats.

Contacts
--------

Supported contacts format:

- CSV  - Comma Separated values (\*.txt, \*.csv)
- Excel (\.*xls, \*.xlsx)
- VCard (\*.vcf, \*.vcard)
- LDIF (\*.ldif)


To import contacts:

1. Right click on the target phone book, then select :guilabel:`Import contacts`

   .. image:: _static/webtop-import_contacts1.png

2. Select the import format and make sure that fields on the file match the ones available on WebTop

   .. image:: _static/webtop-import_contacts2.png

If you are importing a phone book exported from Outlook, make sure to set :guilabel:`Text qualifier` to ``"`` value.


.. image:: _static/webtop-import_contacts3.png

Calendars
---------

Supported calendar format: iCalendar (\*.ics, \*.ical, \*.icalendar)

To import events:

1. Right click on the target calendar, then select :guilabel:`Import events`

   .. image:: _static/webtop-import_calendars1.png

2. Select the import format
   
   .. image:: _static/webtop-import_calendars2.png

3. Then choose if you want to delete all existings events and import new ones, or just append imported data to existing calendar events

   .. image:: _static/webtop-import_calendars3.png



Importing from Outlook PST
==========================

You can import email, calendars and address books from an :index:`Outlook` :index:`PST` archive.

Before using the followings scripts, you will need to install the *libpst* package: ::

   yum install libpst -y

Also make sure the PHP timezone corresponds to the server timezone: ::

  config getprop php DateTimezone

PHP time zone can be updated using the following command: ::

  config setprop php DateTimezone Europe/Rome
  signal-event nethserver-php-update


Mail
----

Initial script to import mail messages: :file:`/usr/share/webtop/doc/pst2webtop.sh`

To start the import, run the script specifying the PST file and the system user: ::

   /usr/share/webtop/doc/pst2webtop.sh <filename.pst> <user>

Example: ::

  # /usr/share/webtop/doc/pst2webtop.sh data.pst goofy
  Do you wish to import email? [Y]es/[N]o:

All mail messages will be imported. Contacts and calendars will be saved inside a
temporary file and the script will output further commands to import contacts and calendars.

Example: ::

  Events Folder found: Outlook/Calendar/calendar
  pst2webtop_cal.php goody '/tmp/tmp.Szorhi5nUJ/Outlook/Calendar/calendar' <foldername>

  ...

  log created: /tmp/pst2webtop14271.log

All commands are saved also in the reported log.

Contacts
--------

Script for contacts import: :file:`/usr/share/webtop/doc/pst2webtop_card.php`.

The script will use files generated from mail import phase: ::

        /usr/share/webtop/doc/pst2webtop_card.php <user> <file_to_import> <phonebook_category>

**Example**

Let us assume that the pst2webtop.sh script has generated following output from mail import: ::

   Contacts Folder found: Personal folders/Contacts/contacts
    Import to webtop:
   ./pst2webtop_card.php foo '/tmp/tmp.0vPbWYf8Uo/Personal folders/Contacts/contacts' <foldername>

To import the default address book (WebTop) of *foo* user: ::

   /usr/share/webtop/doc/pst2webtop_card.php foo '/tmp/tmp.0vPbWYf8Uo/Personal folders/Contacts/contacts' WebTop

Calendars
---------

Script for calendars import: :file:`/usr/share/webtop/doc/pst2webtop_cal.php`

The script will use files generated from mail import phase: ::

        /usr/share/webtop/doc/pst2webtop_cal.php <user> <file_to_import> <foldername>

**Example**

Let us assume that the pst2webtop.sh script has generated following output from mail import: ::

   Events Folder found: Personal folders/Calendar/calendar
    Import to webtop:
   ./pst2webtop_cal.php foo '/tmp/tmp.0vPbWYf8Uo/Personal folders/Calendar/calendar' <foldername>

To import the default calendar (WebTop) of *foo* user: ::

        /usr/share/webtop/doc/pst2webtop_cal.php foo '/tmp/tmp.0vPbWYf8Uo/Personal folders/Calendar/calendar' WebTop

Known limitations:

* only the first occurrence of recurrent events will be imported
* Outlook reminders will be ignored

.. note::
   The script will import all events using the timezone selected by the user inside WebTop, if set.
   Otherwise system timezone will be used.

Troubleshooting
===============

After login a "mail account authentication error" is displayed
--------------------------------------------------------------

If an entire mail account is shared among different users, a Dovecot connection limit can be reached.
This is the displayed error:

.. image:: _static/webtop-dovecot_error.png

In ``/var/log/imap`` there are lines like the following: ::

  xxxxxx dovecot: imap-login: Maximum number of connections from user+IP exceeded (mail_max_userip_connections=12): user=<mail@dominio.com>, method=PLAIN, rip=127.0.0.1, lip=127.0.0.1, secured, session=<zz/8iz1M1AB/AAAB>

To list active IMAP connections per user, execute: ::

  doveadm who


To fix the problem, just raise the limit (eg. 50 connections for each user/IP): ::

  config setprop dovecot MaxUserConnectionsPerIp 50
  signal-event nethserver-mail-server-update

At the end, logout and login again in WebTop.


Blank page after login
----------------------

You can access WebTop using system admin user (|product| Administrator) using the full login name, eg: ``admin@nethserver.org``.

If the login fails, mostly when upgrading from WebTop 4, it means that the admin user doesn't have a mail address.

To fix the problem, execute the following command: ::

    curl -s https://git.io/vNuPf | bash -x

Synchronized events have different time
---------------------------------------

Sometimes calendar events created on mobile devices and synchronized via EAS, are shown with a wrong time, for example with a difference of 1 or 2 hours.

The problem is due to the PHP time zone which can be different from the system time zone.

With this command you can see the current time zone set for PHP: ::

  config getprop php DateTimezone

Output example: ::

  # config getprop php DateTimezone
  UTC


If the Time Zone is not the desired one, you can changed it using these commands: ::

  config setprop php DateTimezone "Europe/Rome"
  signal-event nethserver-php-update


To apply the changes, execute: ::

  signal-event nethserver-httpd-update
  signal-event nethserver-webtop5-update


List of PHP supported time zones: http://php.net/manual/it/timezones.php

Delete automatically suggested email addresses
----------------------------------------------

When compiling the recipient of a mail, some automatically saved email addresses are suggested.
If you need to delete someone because it is wrong, move with the arrow keys until you select the one you want to delete
(without clicking on it), then delete it with :guilabel:`Shift + Canc`

.. only:: nscom

  .. _webtop-vs-sogo:

  WebTop vs SOGo
  ==============

  WebTop and SOGo can be installed on the same machine, although it is discouraged to keep such setup on the long run.

  ActiveSync is enabled by default on SOGo and WebTop, but if both packages are
  installed, SOGo will take precedence.

  To disable ActiveSync on SOGo: ::

    config setprop sogod ActiveSync disabled
    signal-event nethserver-sogo-update

  To disable ActiveSync on WebTop: ::

    config setprop webtop ActiveSync disabled
    signal-event nethserver-webtop5-update


  All incoming mail filters configured within SOGo, must be manually recreated inside WebTop interface.
  This also applies if the user is switching from WebTop to SOGo.


  Google and Dropbox integration
  ==============================

  Users can add their own Google Drive and Dropbox accounts inside WebTop.
  Before proceeding, the administrator must create a pair of API access credentials.

  Google API
  ----------

  * Access https://console.developers.google.com/project and create a new project
  * Create new credentials by selecting "OAuth 2.0 clientID" type and remember to compile
    "OAuth consent screen" section
  * Insert new credentials (Client ID e Client Secret) inside WebTop configuration

  From the shell, access webtop database: ::

    su - postgres -c "psql webtop"

  Execute the queries, using the corresponding value in place of ``__value__`` variable: ::

    UPDATE core.settings SET value = '__value__' WHERE service_id = 'com.sonicle.webtop.core' AND key = 'googledrive.clientid';
    UPDATE core.settings SET value = '__value__' WHERE service_id = 'com.sonicle.webtop.core' AND key = 'googledrive.clientsecret';

  Dropbox API
  -----------

  * Access https://www.dropbox.com/developers/apps and create a new app
  * Insert the new credential key pair (App key e App secret) inside WebTop configuration

  From shell, access webtop database: ::

    su - postgres -c "psql webtop"

  Execute the queries, using the corresponding value in place of ``__value__`` variable: ::

    UPDATE core.settings SET value = '__value__' WHERE service_id = 'com.sonicle.webtop.core' AND key = 'dropbox.appkey';
    UPDATE core.settings SET value = '__value__' WHERE service_id = 'com.sonicle.webtop.core' AND key = 'dropbox.appsecret';


  If you need to raise the user limit, please read the official Dropbox documentation.

