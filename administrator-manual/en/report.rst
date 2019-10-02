.. _report-section:

======
Report
======

.. note::

  The configuration page of this module is available only in the new Server Manager.

ntopng
This module manages the configuration of `Dante
<https://github.com/nethesis/dante/>`_.

Dante collects data from logs, databases and services, aggregates and displays them on a report structured as a customizable dashboard.
The report can be sent via e-mail, with configurable scheduling and recipients.

Dashboard
=========

The *Dashboard* page is composed by a set of widgets, each showing a piece of information on the system.
The user can customize the layout of the dashboard by adding, removing, resizing and drag & dropping widgets.

The types of widgets currently supported are:

* **Chart**: pie, bar, line or area charts
* **Counter**: a card that displays an aggregated numerical value and a trend on a time interval
* **Table**: a table with optional row and column headers
* **Ranking**: a list of the top N items, ordered by their value
* **Label**: a text showing a piece of information
* **Title**: a simple text typed by the user to organize the layout of the dashboard

Settings
========

The *Settings* page manages the configuration of the module.

Host configuration
------------------

* **Public host**: this is the hostname where the report is hosted. It must be a name that can be resolved from the internet
* **Final url**: this field displays the public URL where the report is hosted

Report configuration
--------------------

* **Theme**: the themes available for the dashboard are *light* and *dark*
* **Palette**: there are 9 color palettes to choose from
* **Interval**: time interval on which the data are aggregated. It can be *Week*, *Month* or *Six-months*
* **Language**: language used to display the report
* **Anonymization**: boolean flag that controls the anonymization of sensible data in the report
* **Max Entries**: maximum number of items to display on ranking widgets
* **Addresses**: configuration of report e-mail recipients and scheduling of e-mail dispatch

Test mail
---------

* **Address**: e-mail recipient of the test e-mail containing the report
* **Include configured addresses**: boolean flag to control whether the test e-mail should be sent to the addresses configured in *Report configuration* in addition to *Address*










