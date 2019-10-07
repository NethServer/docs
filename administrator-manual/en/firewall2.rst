.. _firewall_new-section:

==========================
Firewall and gateway (new)
==========================

.. note::

   This chapter describes changes introduces by the *Firewall* application in the new Server Manager.
   Basic firewall behavior is unchanged and describe inside :ref:`firewall-section`.
   
   Please note that some changes made in the new Server Manager may not be reflected in the old one. 


General
=======

Main differences from the old Server Manager:

* the rules panel has been split into 3 different pages: 

  * :ref:`firewall_rules_new-section`
  * :ref:`local_rules-section`
  * :ref:`traffic_shaping-section`

* all pages use :ref:`apply_revert-section` behavior
* smart search: on most panels the full text search can be used to quickly find existing rules or objects
* advanced properties: when creating new rules, only the most common fields are shown. To show other less common parameters click the :guilabel:`Advanced` label
* raw address support: the user can use raw IP addresses (or CIDR) whenever creating a rule. Such raw addresses can be later converted to firewall objects
  using the :guilabel:`Create Host` and :guilabel:`Create CIDR subnet` actions which will appear next to the IP address
* real-time charts: many pages has real-time charts displaying data from ``netdata``. 
  Since netdata is not installed by default, you can install it from :ref:`software-center-section`.
* list of active :ref:`firewall_connections-section`

.. _apply_revert-section:

Apply and revert
----------------

Every time the configuration has been changed, modifications are not applied immediately but saved in a temporary store.
For the changes to take effect, click on the :guilabel:`Apply` button at the top right corner of the page.

As long as the new rules created have not been applied, you can revert all changes clicking the :guilabel:`Revert` button at the top right corner of the page.

Dashboard
=========

The dashboard displays the local firewall network topology along with the number of established connection,
the count of configured objects and the list of active services.

WAN
===

All red interfaces are listed on the top of the page, just below bandwidth usage charts.
Download and upload bandwidth can be automatically calculated using :guilabel:`Speedtest` button.
Each red network interface can be also enabled and disabled directly from the list.

To change WAN mode and link monitoring options click on :guilabel:`Configure` button.

Rules can be created under the :guilabel:`Rules` section on the same page.
After creating or editing rules, make sure to :ref:`apply <apply_revert-section>` the changes.

.. _traffic_shaping-section:

Traffic shaping
===============

Traffic shaping classes are used to commit bandwidth for specific network traffic.
For each class the bandwidth can be specified using the percentage of available network bandwidth or
with absolutes values expressed in kbps.

As default, a traffic shaping class is applied to all red network interfaces.
Such behavior can be changed by selecting an existing red interfaces under the :guilabel:`Bind to` menu
inside the :guilabel:`Advanced` section.
Bound classes and bandwidth expressed in kbps are not usable inside the old Server Manager.

Rules can be created under the :guilabel:`Rules` section on the same page.
After creating or editing rules, make sure to :ref:`apply <apply_revert-section>` the changes.

SNAT
====

SNAT is available only if there is at least one IP alias configured on red network interfaces.
See also :ref:`snat-section`.

Objects
=======

Firewall objects page offer the same features as the :ref:`old Server Manager <firewall_objects-section>`.

Port forward
============

Port forwards are grouped by destination host and support raw IP addresses along with firewall objects.

The following protocols are supported only in the new Server Manager:

* AH
* ESP
* GRE

For more info on port forward see the :ref:`old Server Manager <port_forward-section>`.

.. _firewall_rules_new-section:

Rules
=====

This page allows the management of rules applied only to the network traffic traversing the firewall.
To create rules for the traffic from/to the firewall itself, see the :ref:`local_rules-section`.

A rule consists of five main parts:

* Source 
* Destination
* Service (optional)
* Action
* Time condition (optional)

Available actions are:

* :dfn:`ACCEPT`: accept the network traffic
* :dfn:`REJECT`: block the traffic and notify the sender host 
* :dfn:`DROP`: block the traffic, packets are dropped and no notification is sent to the sender host

Rules support raw IP addresses and two extra zones:

* ivpn: all traffic from IPSec VPNs
* ovpn: all traffic from OpenVPN VPNs

Both zones are available only if VPN application is installed.
Rules using such zones, can't be modified from the :ref:`old Server Manager <firewall-rules-section>`.

.. _policies-section:

Policies
--------

To display active policies click on the :guilabel:`Policies` button.
Policies are affected by changes on the :ref:`firewall_settings-section` page.

.. _local_rules-section:

Local rules
===========

This page allows the management of rules applied only to the network traffic generated from the firewall,
or directed to the firewall itself.
The configuration is the same as :ref:`firewall_rules_new-section` page.

.. _firewall_connections-section:

Connections
===========

This page keeps track of all active connections.
Connections can be filter by :guilabel:`Protocol` and :guilabel:`State`.
The list of connections is not refreshed in real time. To list new connections click the :guilabel:`Refresh` button.

The administrator can delete a single connection or flush the whole connection tracking table using :guilabel:`Delete all connections` button.


.. _firewall_settings-section:

Settings
========

Global settings which affect the whole firewall behavior, like MAC validation.
When the :guilabel:`Traffic to Internet (red interface)` option is changed, modifications are
reflected inside the :ref:`policies-section` section.
