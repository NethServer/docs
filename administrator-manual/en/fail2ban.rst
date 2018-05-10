========
Fail2ban
========

Fail2ban scans log files (e.g. /var/log/apache/error_log) and bans IPs that show the malicious signs – too many password failures, seeking for exploits, etc. Generally Fail2Ban is then used to update firewall rules to reject the IP addresses for a specified amount of time, although any arbitrary other action (e.g. sending an email) could also be configured. Out of the box Fail2Ban comes with filters for various services (apache, courier, ssh, etc).

Fail2Ban is able to reduce the rate of incorrect authentications attempts however it cannot eliminate the risk that weak authentication presents. Configure services to use only two factors or public/private authentication mechanisms if you really want to protect services.

Installation
============

Install from the Software Center or use the command line: ::

  yum install nethserver-fail2ban


Settings
========

Fail2ban is configurable in the security category of the server-manager. Most of settings can be changed in the ``Configuration`` tab, only really advanced settings must be configured by the terminal. The ``Ban status`` tab displays the statistic and the banned IPs.

You can also activate changes and restart the fail2ban service by: ::

  signal-event nethserver-fail2ban-save

Jails
-----

A jail is enabled and start to protect a service when you install a new module, the relevant jail (if existing) is automatically activated by the event 'runlevel-adjust' which is launched at the end of the yum process.


All jails can be disabled individually in the Jails settings.

Number of attempts
    Number of matches (i.e. value of the counter) which triggers ban action on the IP.

Time span
    The counter is set to zero if no match is found within "findtime" seconds.

Ban Time
    Duration for IP to be banned for.

Recidive jail is perpetual
    When an IP goes several time in jail, the recidive jail bans it for a much longer time. If enabled, it is perpetual.

Network
-------

Allow bans on the LAN
    By default the failed attempts from your Local Network are ignored, except when you enabled the option.


IP Whitelisting
    Ip listed in the text area will be never banned by fail2ban (one IP per line).

Email
-----

Send email notifications
    Enable to send administrative emails.

Administrators emails
    List of email addresses of administrators (one address per line).

Notify jail start/stop events
    Send email notifications when a jail is started or stopped.


E-smith Database
================

You can set custom values for the MaxRetry property of each jail, once removed you go back to the default MaxRetry value. ::

    config show fail2ban |grep -i '_maxretry'

    Apache_MaxRetry=
    Dovecot_MaxRetry=
    Ejabber_MaxRetry=
    HttpdAdmin_MaxRetry=
    Mysqld_MaxRetry=
    Nextcloud_MaxRetry=
    Nginx_MaxRetry=
    OpenVpn_MaxRetry=
    Owncloud_MaxRetry=
    PamGeneric_MaxRetry=
    Postfix_MaxRetry=
    Recidive_MaxRetry=
    Roundcube_MaxRetry=
    Sieve_MaxRetry=
    Sogo_MaxRetry=
    Sshd_MaxRetry=
    Urbackup_MaxRetry=
    Vsftpd_MaxRetry=

Only available by a db command, to set it: ::

  config setprop fail2ban Recidive_MaxRetry 6
  signal-event nethserver-fail2ban-save

If you delete the property you go back to the default MaxRetry value: ::

  config setprop fail2ban Recidive_MaxRetry ''
  signal-event nethserver-fail2ban-save

Tools
=====

Fail2ban-client
---------------

Fail2ban-client is part of the fail2ban rpm, it gives the state of fail2ban and all available jails: ::

  fail2ban-client status

To see a specific jail : ::

  fail2ban-client status sshd

To see which logfiles are monitored for a jail: ::

  fail2ban-client get nginx-http-auth logpath

Fail2ban-listban
----------------

Fail2ban-listban counts the IPs currently and totally banned in all activated jails, at the end it shows you the IPs which are still banned by shorewall. ::

  fail2ban-listban

Fail2ban-regex
--------------

Fail2ban-regex is a tool which is used to test the regex on you logs, it is a part of fail2ban software. Only one filter is allowed per jail, but it is possible to specify several actions, on separate lines.

The documentation is `readable at the fail2ban project <http://fail2ban.readthedocs.io/en/latest/filters.html>`_. 

::

  fail2ban-regex /var/log/YOUR_LOG /etc/fail2ban/filter.d/YOUR_JAIL.conf --print-all-matched

You can also test custom regex directly: ::

  fail2ban-regex /var/log/secure '^%(__prefix_line)s(?:error: PAM: )?[aA]uthentication (?:failure|error) for .* from <HOST>( via \S+)?\s*$'

Fail2ban-unban
--------------

Fail2ban-unban is used to unban an IP when the ban must be removed manually. ::

  fail2ban-unban <IP>

You can use also the built-in command with fail2ban-client: ::

  fail2ban-client set <JAIL> unbanip <IP>

Whois
=====

If you desire to query the IP ``whois`` database and obtain the origin of the banned IP by email, you could  Install the ``whois`` rpm.

