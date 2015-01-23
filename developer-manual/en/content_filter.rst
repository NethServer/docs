==================
Web content filter
==================

The nethserver-squidguard package configures the web content filter based on SquidGuard url-rewriter.

The configuration is based on profiles.
Each profile is composed by:

* a user, group of users, host or group of hosts accessing the web page
* a filter which includes allowed and denied sites
* a time frame within the filter is active

The system comes with a default profile which is applied to any host/user who doesn't fit on a specific profile.

Blacklists
==========

Blacklists are updated every night using the script: :file:`/etc/cron.daily/update-squidguard-blacklists`
The script will download and merge all blacklists listed in :file:`/etc/squid/blacklists`. This actions can take several minutes.

Databases
=========

The package uses the ``squidguard`` key inside the ``configuration`` database, also it creates a new ``contentfilter`` database
for profiles and filters configuration.

Common configuration
--------------------

Properties for ``squidguard`` key:

* *BlockedFileTypes*: comma separated list of blocked file extensions
* *CustomListURL*: URL to download a custom blacklist. The blacklist must follow SquidGuard standard
* *DomainBlacklist*: comma separated domain list, this domains are always blocked 
* *DomainWhitelist*: comma separated domain list, this domains are always allowed
* *Expressions*: if enabled, allow regular expression on blacklists categories. Can be ``enabled`` or ``disabled``, default is ``disabled``
* *IdleChildren*: minimum number of idle processes. Default is 5
* *Lists*: comma separated list of blacklist names. Possible values are: ``shalla``, ``toulouse``, ``urlblacklist`` and ``custom``.
  If set to ``custom``, make sure ``CustomListURL`` is set.
* *MaxChildren*: maximum number of processes. Default is 20
* *RedirectUrl*: custom URL for block page. See :ref:`squidguard-blockpage-section`
* *StartupChildren*: minimum number of process children on startup. Default is 5
* *UrlBlacklist*: comma separated URL list, this URLs are always blocked 
* *UrlWhitelist*: comma separated URL list, this URLs are always allowed


.. note:: Modifying following parameters can greatly affect memory usage: IdleChildren, MaxChildren, StartupChildren

Example: ::

 squidguard=configuration
    BlockedFileTypes=
    CustomListURL=
    DomainBlacklist=microsoft.com
    DomainWhitelist=nethserver.org,nethesis.it
    Expressions=disabled
    IdleChildren=5
    Lists=shalla
    MaxChildren=20
    RedirectUrl=
    StartupChildren=5
    UrlBlacklist=
    UrlWhitelist=
    status=enabled

Contentfilter database
----------------------

The ``contentfilter`` database can contain three kind of records:

* category: a custom categorized list of domain blocked or allowed. Custom categories can be added to a filter
* filter: an object describing which categories must be blocked or allowed
* time: when the filter must be applied, it contains week days and time
* profile: a relation between above objects describing WHO (host or user), WHAT (filter) and WHEN (time)

Categories
^^^^^^^^^^

Properties:

* *Domains*: comma separated list of domains 
* *Description*: optional description

Category example: ::

 mycategory=category
    Description=My Category
    Domains=nethesis.it,nethserver.org

Filters
^^^^^^^

Properties:

* *BlackList*: enable or disable the global blacklist (``DomainBlacklist`` and ``UrlBlacklist``). Can be ``enabled`` or ``disabled``
* *BlockAll*: can be ``enabled`` or ``disabled``. If disabled, all listed categories in ``Categories`` are blocked and all other sites are allowed.
  If enabled, all listed categories in ``Categories`` are allowed and all other sites are blocked
* *BlockFileTypes*: enable or disable the global file extension list (``BlockedFileTypes``). Can be ``enabled`` or ``disabled`` 
* *BlockIpAccess*: if enabled, sites can be accessed only using a domain name (not an IP address). Can be ``enabled`` or ``disabled``
* *Categories*: comma separated list of categories blocked or allowed. If a category is not present inside the SquidGuard db (:file:`/var/squidGuard/Blacklists`), the category will be excluded from configuration file to avoid SquidGuard panic-mode
* *Description*: optional description
* *WhiteList*: enable or disable the global whitelist (``DomainWhitelist`` and ``UrlWhitelist``). Can be ``enabled`` or ``disabled``
* *Removable*: can be ``yes`` or ``no``. If set to ``no`` the record can't be removed from web interface 

Filter example: ::

 myfilter=filter
    BlackList=enabled
    BlockAll=disabled
    BlockFileTypes=disabled
    BlockIpAccess=disabled
    Categories=aggressive,alcohol,weapons,warez
    Description=Default filter
    WhiteList=enabled

Times
^^^^^

Properties:

* *Days*: comma separated list of week days. Valid values are:

  * *m*: Monday
  * *t*: Tuesday
  * *w*: Wednesday
  * *h*: Thursday
  * *f*: Friday
  * *a*: Saturday
  * *s*: Sunday 
* *Description*: optional description
* *EndTime*: hour of the day in 24h format or empty
* *StartTime*: our of the day in 24h format or empty

Time example: ::

 worktime=time
    Days=m,t,w,h,f
    Description=Work time
    EndTime=18:30
    StartTime=08:30


Profiles
^^^^^^^^

Properties:

* *Filter*: a filter object
* *Src*: it can be an object of type user, user group, host or host group. Otherwise, if it is a string, the system will
  assume the profile is associated with an user from Active Directory; the system must be joined to a domain
* *Time*: a time object (optional)
* *Description*: optional description
* *Removable*: can be ``yes`` or ``no``. If set to ``no`` the record can't be removed from web interface 


Profile example: ::

 myprofile=profile
    Description=My profile
    Filter=filter;badboys
    Src=host;demo
    Time=time;worktime


.. _squidguard-blockpage-section:

Block page
==========

The block page is a CGI used to inform the user about the block reason.
It's a single page which can handle requests from SquidGuard and SquidClamav (:ref:`squidclamav-section`).

The page is localized depending on browser language.

This configuration can be overwritten using ``RedirectUrl`` property.


Log files
=========

Blocked page logs:

* SquidGuard: :file:`/var/log/squidGuard/urlfilter.log`
