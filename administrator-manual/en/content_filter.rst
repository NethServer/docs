.. _web_content_filter-section:

==================
Web content filter
==================

The :index:`content filter` analyzes all web traffic and blocks selected websites or sites containing viruses.
Forbidden sites are selected from a list of categories, which in turn must be downloaded from external sources and stored on the system.

Web content filter is included inside the "Web Proxy & Filter" application of the new Server Manager.

The system allows to create an infinite number of profiles.
A profile is composed by three parts:

* **Who**: the client associated with the profile.
  Can be a user, a group of users, a host, a group of hosts, a zone or an interface role (like green, blue, etc).

* **What**: which sites can be browsed by the profiled client.
  It's a filter created inside the :guilabel:`Filters` section.

* **When**: the filter can always be enabled or valid only during certain period of times.
  Time frames can be created inside the :guilabel:`Times` section.


This is the recommended order for content filter configuration:

1. Select a list of categories from :guilabel:`Blacklists` page and start the download
2. Create one or more time conditions (optional)
3. Create custom categories (optional)
4. Create a new filter or modify the default one
5. Create a new profile associated to a user or host, then select
   a filter and a time frame (if enabled)

If no profile matches, the system provides a default profile that is applied to all clients.

Filters
=======

A filter can:

* block access to categories of sites
* block access to sites accessed using IP address (recommended)
* filter URLs with regular expressions
* block files with specific extensions
* enable global blacklist and whitelist

A filter can operate in two different modes:

* Allow all: allow access to all sites, except those explicitly blocked
* Block all: blocks access to all sites, except those explicitly permitted

.. note:: The category list will be displayed only after the download of list selected from :guilabel`Blacklist` page.

Blocking Google Translate
-------------------------

Online translation services, like :index:`Google Translate`, can be used to bypass
the content filter because pages visited trough the translator always refer to a Google's domain
despite having content from external servers.

It's possible to block all requests to Google translate, creating a blocked URL inside the :guilabel:`General` page.
The content of the blocked URL must be: ``translate.google``.

Antivirus
=========

Web browsing can be checked for malicious content, but only for clear text HTTP protocol.
If the proxy is configured in SSL transparent mode (:ref:`proxy_ssl-section`), content downloaded via HTTPS **will not** be scanned.
See :ref:`antivirus-section` for more info.


Troubleshooting
===============

If a bad page is not blocked, please verify:

* the client is surfing using the proxy
* the client doesn't have a configured bypass inside :guilabel:`Hosts without proxy` section
* the client is not browsing a site with a configured bypass inside :guilabel:`Sites without proxy` section
* the client is really associated with a profile not allowed to visit the page
* the client is surfing within a time frame when the filter is permissive
