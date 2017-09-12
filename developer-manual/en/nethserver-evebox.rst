=================
nethserver-evebox
=================

EveBox configuration for NethServer:

- it requires nethserver-suricata
- it runs as ``suricata`` user, only if ``/var/log/suricata/eve.json`` file exists
- Suricata must be running and eve log must be enabled
- it uses SQLite
- no ElasticSearch support
- listens on port 5636, accessible only from localhost
- web interface served via reverse proxy: ``https://<host>:980/<alias>`` (see ``alias`` prop below)
- once a week internal GeoIP database is updated by a cron job

Database: ::

 evebox=service
    TCPPort=5636
    access=
    alias=be771675da40887ccf9eb98d05b88dc80559b6a6
    status=enabled

Links
=====

- Official site: https://evebox.org/
