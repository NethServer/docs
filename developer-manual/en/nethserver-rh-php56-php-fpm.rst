===========================
nethserver-rh-php56-php-fpm
===========================

Configure default installation of PHP 5.6 running on FPM.
The default configuration of FPM is from upstream and can freely change 
(no template): ``/etc/opt/rh/rh-php56/php-fpm.d/www.conf``.

Adding new configuration
========================

If you need a new configuration, simply drop a file inside ``/etc/opt/rh/rh-php56/php-fpm.d/``
directory and execute: ::

    signal-event nethserver-rh-php56-php-fpm-update
