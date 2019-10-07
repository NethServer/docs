.. index::
   single: Server Manager
   single: web interface

.. _access-section:

============================
Accessing the Server Manager
============================

.. note:: A new Server Manager based on Cockpit is available. See :ref:`access2-section`.

|product| can be configured using the :dfn:`Server Manager` web interface. 
You need a web browser like Mozilla Firefox or Google Chrome to access the web interface using the address (URL) 
``https://a.b.c.d:980`` or ``https://server_name:980`` where *a.b.c.d* and *server_name* respectively are the server IP address and name 
configured during installation.

If the web server module is installed, you can also access the web interface using this address ``https://server_name/server-manager``.

The Server Manager uses self-signed SSL certificates.
You should explicitly accept them the first time you access the server.
The connection is safe and encrypted.

Login
=====

The login page allows selecting an alternative language among those already
installed on the system. After logging in, go to the
:ref:`software-center-section` page to install additional languages.

The login page will give you a trusted access to the web interface. Log in
as **root** and type the password chosen during |product| installation.

.. note:: 
    
    The *unattended* install procedure sets the root password to the default
    ``Nethesis,1234``.

.. _first-configuration-wizard-section:

First configuration wizard
==========================

The first time **root** logs in, the *First configuration wizard* procedure is
displayed.

If the root password is still at the default value, a password change is required.

It is possible to restore a **configuration backup**. Refer to
:ref:`disaster-recovery-section` for more information.

Otherwise the wizard procedure helps on setting up:

* Host name
* :ref:`Date and time zone <date-time-section>`
* SSH port
* :ref:`Smarthost configuration <smarthost-configuration>`
* :ref:`Usage statistics <phonehome-section>`

Change the current password
===========================

You can change the root password from the web interface by going to the
:guilabel:`root@host.domain.com` label on the upper right corner of the screen
and clicking on :guilabel:`Profile`.


Logout
======

Terminate the current Server Manager session by going to the
:guilabel:`root@host.domain.com` label on the upper right corner of the screen
and by clicking on :guilabel:`Logout`.

.. _session-timeouts-section:

Session timeouts
================

By default (starting from |product| 7.5.1804), a Server Manager session
terminates after **60 minutes of inactivity** (idle timeout) and **expires
8 hours after the login** (session life time).

The following shell command sets 2 hours of idle timeout, and 16 hours of
maximum session life time. Time is expressed in seconds: ::
    
    config setprop httpd-admin MaxSessionIdleTime 7200 MaxSessionLifeTime 57600

To disable the timeouts ::
    
    config setprop httpd-admin MaxSessionIdleTime '' MaxSessionLifeTime ''

The new timeout values will affect new sessions. They do not change any active
session.
