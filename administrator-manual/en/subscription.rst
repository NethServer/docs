======================
|product| subscription
======================

A |product| installation can be registerd to a public or private Dartagnan [#Dartagnan]_ instance,
getting access to monitoring portal and stable update repositories.

The |product| Subscription by Nethesis [#Nethesis]_ enables access to a public ready-to-use Dartagnan instance,
along with immediate professional support services for your |product| deployments.

Detailed info available: https://my.nethserver.com

Register an installation
========================

1. Access :guilabel:`Subscription` page from the Server Manager
2. Click on :guilabel:`Subscribe`
3. Login or register to https://my.nethserver.com to obtain a registration code
4. Copy and paste the code inside the :guilabel:`Registration token` field
5. Click on :guilabel:`Register now` button

At the end, the subscription plan name and validity are reported inside the page.
Monitoring and access to stable repositories are automatically enabeld.

.. [#Dartagnan] Dartagnan documentation: https://nethesis.github.io/dartagnan/
.. [#Nethesis] Nethesis official site: http://www.nethesis.it

Removing a subscription
=======================

When the subscription expires, or at the end of a trial period, use the following command to
revert any modification to repositories and access the community ones: ::

  config setprop Secret '' SystemId ''
  eorepo base centos-sclo-rh centos-sclo-sclo epel extras nethforge nethserver-base nethserver-updates updates
