.. _antivirus-section:

=========
Antivirus
=========

.. note::

  The configuration page of this module is available only in the new Server Manager.

ClamAV is the open source antivirus engine of |product|. The server runs two different ClamAV instances:
one for scanning received mail (see :ref:`email-section`) and the other one for analyzing HTTP web traffic (see :ref:`web_content_filter-section`).

The antivirus engine can be configured from the new Server Manager.
Since virus signatures are downloaded about once per hour, changes to the configuration will take effect
on next automatic signatures download.

Available options:

- :guilabel:`ClamAV official signatures`: enable or disable official signatures.
  These signatures detect many old threats but are not very effective against the latest malware.
  Usage of official signatures is discouraged on machines with less than 4GB of RAM.

- :guilabel:`Third-party signatures rating`: choose the rating of unofficial signatures downloaded from multiple verified sources like `SaneSecurity <https://sanesecurity.com>`_.
  Higher rating means more blocked threats but also a higher probability of false positives. Recommended ratings are ``Low`` and ``Medium``.

