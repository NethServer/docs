=====
Redis
=====

Package: nethserver-redis

Start and stop Redis server.

This package is used by old release of nethserver-ntopng < 1.3.0.

Events:

* ``nethserver-redis-update``, standard event triggered on package installation/update.


Configuration DB ::

 redis=service
    TCPPort=6379
    access=private


Links: 

* Official site: http://redis.io/
