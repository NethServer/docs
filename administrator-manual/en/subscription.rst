.. _subscription-section:

======================
|product| subscription
======================

A |product| installation can be registered to a public or private Dartagnan [#Dartagnan]_ instance,
getting access to monitoring portal and stable update repositories.

.. hint::

    The |product| Subscription by Nethesis [#Nethesis]_ enables access to a
    public ready-to-use Dartagnan instance, along with immediate professional
    support services for your |product| deployments. Detailed info available at
    https://my.nethserver.com


Activating a subscription will enable the stable YUM repositories, but will
disable any other repositories you may have added. You can re-enable any other
repositories by creating a "template-custom" for
:file:`/etc/nethserver/eorepo.conf`.

The subscription provider may not accept support requests for the contents of
custom repositories.


.. _register-an-installation:

Registering the system
======================

1. Access :guilabel:`Subscription` page from the old or new Server Manager
2. Click on :guilabel:`Subscribe`
3. Login or register to https://my.nethserver.com to obtain a registration code
4. Copy and paste the code inside the :guilabel:`Registration token` field
5. Click on :guilabel:`Register now` button

At the end, the subscription plan name and validity are reported inside the page.
Monitoring and access to stable repositories are automatically enabled.

.. [#Dartagnan] Dartagnan documentation: https://nethesis.github.io/dartagnan/
.. [#Nethesis] Nethesis official site: http://www.nethesis.it

Removing a subscription
=======================

When the subscription expires, or at the end of a trial period, use the following command to
revert any modification to repositories and access the community ones: ::

  config setprop subscription Secret '' SystemId ''
  signal-event nethserver-subscription-save

If you have installed the `new server manager` AKA `cockpit`, you can unsubscribe the machine in the `Subscription` page, clicking on **Unsubscribe** button.

Refer to :ref:`software-updates-section` for more information about the community updates origin.
