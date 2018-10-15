.. _rspamd-section:

======
Rspamd
======

Rspamd is the new anti-spam engine of |product|, it replaces SpamAssassin and
Amavisd-new.

The official documentation of Rspamd is available at https://rspamd.com

You need to install the :guilabel:`Email` module from the :guilabel:`Software
center` page. The menu where to activate it and modify its settings is on the
:guilabel:`Email > Filter` page. You can read more in the :ref:`Email filter
<email_filter>` section.


Rspamd Web Interface
====================

The anti-spam component is implemented by Rspamd which provides its
administrative web interface at ::

  https://<HOST_IP>:980/rspamd

The actual URL is listed under the :guilabel:`Applications` page. By default
access is granted to members of the ``domain admins`` group and to the ``admin``
user (see also :ref:`admin-account-section`). An additional special login
``rspamd`` can be used to access it. Its credentials are available from
:guilabel:`Email > Filter > Rspamd user interface (Web URL)`: just follow the
given link.

The Rspamd web UI:

* displays messages and actions counters,
* shows the server configuration,
* tracks the history of recent messages,
* allows training the Bayes filter by submitting a message from the web form.

Status
------

It is the landing menu, the global statistics are available on the Rspamd service.

Troughput
---------

The graphics are displayed in this menu to explain the activity of the anti-spam 
software. You can adjust the time scale (hourly, daily, weekly, montly) and modify 
some other settings to refine the graphics

Configuration
-------------

The :guilabel:`Configuration > Lists` menu is useful to edit lists of allowed IP/Domain/mime for the modules, you will find:

  * SURBL
  * mime list types
  * SPF_DKIM
  * DMARC
  * DKIM
  * SPF

When you want to create an exception list in a module, you could give the path 
:file:`/var/lib/rspamd/`, the list will be editable by the Rspamd web interface.


Symbols
-------

Rspamd use a concept of symbols which will increase or decrease the spam score 
when the rule has matched. The symbol weight is modifiable, negative score are 
for good email, positive are for spam. 

Find the matching symbols
^^^^^^^^^^^^^^^^^^^^^^^^^

The convenient way is to use the :guilabel:`History > History` menu.

Modify a symbol weight
^^^^^^^^^^^^^^^^^^^^^^

An easier way to change the symbol weight is to use the Rspamd WebUI: :guilabel:`Symbols > Symbols and rules`. 
A search box is available, you could use it to display the symbol and modify its weight.

* Symbol score for spam is in red (positive score)
* Symbol score for ham is in green (negative score)

If you want to remove the custom settings, you could edit the file 
:file:`/var/lib/rspamd/rspamd_dynamic` or remove them in the Rspamd Web Interface: 
:guilabel:`Configuration > Lists > rspamd_dynamic`

You could redefine manually the scores defined in :file:`/etc/rspamd/scores.d/*_group.conf`
where they are placed by a symbol’s group. Like for the modules, you could overwrite 
the setting in :file:`/etc/rspamd/local.d/*_group.conf` or :file:`/etc/rspamd/override.d/*_group.conf`.

Priority order ::

    scores.d/*_group.conf < local.d/*_group.conf < override.d/*_group.conf

Learning
--------

The purpose of the :guilabel:`Learning` Menu is to train the Bayes filter, you could use 
directly the source of the email in the relevant text area to make learn to rspamd if the email 
is a spam or a ham.

Scan
----

The :guilabel:`Scan` menu can be used to scan directly an email and check its score and the matching symbols.

History
-------

The Rspamd web Interface could be used to display the action done and the spam score against an email, 
see :guilabel:`History > History`

You could display a list of symbols by clicking on the email field, it will help you to understand the action done 
(reject, add_header, no_action, rewrite_subject, greylist) and gather useful informations like: 

* the sender
* the recipient
* the subject
* the full score


Modules
=======

Rspamd comes with a modular approach, all modules are not enabled by default and are 
customisable by the system administrator. The default settings are in the file 
:file:`/etc/rspamd/modules.d/MODULE_NAME.conf`, relevant to the module name.

For a particular need, you can look the documentation with the 
`list of modules <https://rspamd.com/doc/modules/>`_.

.. only:: nscom

    Disable a module
    ----------------

    You must disable a module only with a good reason. For example the ip_score module 
    could give a high spam score due to the IP of the email sender, if it is blacklisted.

    In that example we could disable the module but many modules (like ip_score) implement 
    a white list to do not check an ip or a domain against the spam filter.

    Create a file (relevant to the module name) :file:`/etc/rspamd/override.d/MODULE_NAME.conf` with ::

        enabled = false;


    Restart Rspamd ::

        systemctl restart rspamd


    Modify the settings of a module
    -------------------------------

    All the default settings of a module are in :file:`/etc/rspamd/modules.d/MODULE_NAME.conf`, 
    |product| uses :file:`/etc/rspamd/local.d/MODULE_NAME.conf` to modify these parameters. 
    Therefore the prefered way is to use :file:`/etc/rspamd/override.d/MODULE_NAME.conf` 
    to either change the Rspamd and |product| default settings. The override file uses the 
    new parameter with a high preference, all former settings are kept.

    Priority order::

        modules.d/MODULE_NAME.conf < local.d/MODULE_NAME.conf < override.d/MODULE_NAME.conf

    In that example we want to implement a list of IP to allow them in the ip_score module.

    Create a file :file:`/etc/rspamd/override.d/ip_score.conf` with ::

        whitelist = "file:///var/lib/rspamd/ip_score_whitelist";

    Restart rspamd ::

        systemctl restart rspamd

    The whitelist is editable in the rspamd UI at :guilabel:`Configuration > Lists > ip_score_whitelist`

    .. note::

       The folder :file:`/var/lib/rspamd` is owned by Rspamd, all files here are modifiable by the software


Frequently asked questions
==========================

The official Rspamd FAQ could have the answer to your questions. Please see
https://rspamd.com/doc/faq.html
