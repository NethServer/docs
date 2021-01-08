.. _fail2ban-section:

========
Fail2ban
========

Fail2ban scans log files (e.g. :file:`/var/log/apache/error_log`) and bans IPs that show the malicious signs – too many password failures, seeking for exploits, etc. Generally Fail2ban is then used to update firewall rules to reject the IP addresses for a specified amount of time, although any arbitrary other action (e.g. sending an email) could also be configured. Out of the box Fail2ban comes with filters for various services (Apache, Dovecot, Ssh, Postfix, etc).

Fail2ban is able to reduce the rate of incorrect authentications attempts however, it cannot eliminate the risk that weak authentication presents. To improve the security, open the access to service only for secure networks using the firewall or :ref:`services-section`.

Configuration
=============

Access the *Applications* and click on the :guilabel:`Settings` button of **Fail2ban** application.
The configuration is split into two pages:

- :guilabel:`Settings`: general configuration options
- :guilabel:`Jails`: manage available jails

A jail is enabled and start to protect a service when you install a new module, the relevant jail (if existing) is automatically activated after the package installation.
All jails can be disabled individually in the Jails settings.

Available settings are:

* :guilabel:`IP Whitelist`: IPs listed in the text area will be never banned by fail2ban (one IP per line).

* :guilabel:`Recidive ban`: extend the ban of persistent abusers. Recidive ban can have 2 different behaviors:

    * *Static ban time*: ban recidive hosts for 2 weeks, like brute force attack bots. The rule applies when an IP address has been already banned multiple times.
    * *Incremental ban time*: increase the ban time after each failure found in log. When enabled, if you set a short ban time, a valid user can be banned for a a little while but a brute force attacker will be banned for a very long time.

* :guilabel:`Allow bans on the LAN`: by default the failed attempts from your Local Network are ignored, except when you enabled the option.
  :ref:`trusted_networks-section` are considered part of the LAN.

* :guilabel:`Logging Level`: increase or decrease the log level

* :guilabel:`Number of attempts`: number of matches (i.e. value of the counter) which triggers ban action on the IP.

* :guilabel:`Time span`: the counter is set to zero if no match is found within "findtime" seconds.

* :guilabel:`Ban time`: duration for IP to be banned for.



.. rubric:: Mail notifications

Mail notification are disabled by default.
To enable them, click on the :guilabel:`Email notifications` button, then add
one ore more mail address using the :guilabel:`Add an email` button and filling the :guilabel:`Notify to` field.
Existing mail addresses can be removed by clicking on the :guilabel:`-` button.

To receive also notification when a jail is enabled or disabled, check the :guilabel:`Notify jail start/stop events` option.

Unban IP
========

IPs are banned when they are found several times in log, during a specific find time.
They are stored in a database to be banned again each time the server is restarted.
List of current bans is available inside the :guilabel:`Unban` page.
To unban an IP just click on the corresponding :guilabel:`Unban` button.

Command line tools
==================

.. rubric:: fail2ban-client

``fail2ban-client`` gives the state of fail2ban and all available jails: ::

  fail2ban-client status

To see a specific jail : ::

  fail2ban-client status sshd

To see which log files are monitored for a jail: ::

  fail2ban-client get nginx-http-auth logpath

.. rubric:: fail2ban-listban

``fail2ban-listban`` counts the IPs currently and totally banned in all activated jails, at the end it shows the IPs which are still banned by shorewall. ::

  fail2ban-listban

.. rubric:: fail2ban-regex

``fail2ban-regex`` is a tool which is used to test the regex on you logs, it is a part of fail2ban software. Only one filter is allowed per jail, but it is possible to specify several actions, on separate lines.

The documentation is `available at the fail2ban project <http://fail2ban.readthedocs.io/en/latest/filters.html>`_. 

::

  fail2ban-regex /var/log/YOUR_LOG /etc/fail2ban/filter.d/YOUR_JAIL.conf --print-all-matched

You can also test custom regex directly: ::

  fail2ban-regex /var/log/secure '^%(__prefix_line)s(?:error: PAM: )?[aA]uthentication (?:failure|error) for .* from <HOST>( via \S+)?\s*$'

.. rubric:: fail2ban-unban

``fail2ban-unban`` is used to unban an IP when the ban must be removed manually. ::

  fail2ban-unban <IP>

You can use also the built-in command with fail2ban-client: ::

  fail2ban-client set <JAIL> unbanip <IP>

.. rubric:: Whois

If you desire to query the IP ``whois`` database and obtain the origin of the banned IP by email, you could  Install the ``whois`` rpm.
