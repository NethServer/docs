=========
Web proxy 
=========

Configure the web proxy with content filtering.

Proxy
=====

The Web Proxy works to reduce bandwidth usage by caching
the pages you visit. It's transparent to web browsers using
this server as their gateway.

Enabled
    Enable Proxy.

Parent proxy
    Enter the IP address and port of the parent proxy. The correct syntax is
    IP_Address:port .

Filter
======

The content filter is used to control web browsing and
site blocking using some variables such as keywords, ip
address, internal users, or evaluating the content of the web page,
or file extensions. With this tool it is possible for example to enable
access only on some desired sites (such as those of interest
company) while blocking all others.

Mode
    Enabling the Web Filter you can configure mode
    "Block All" and then allow the selected categories, or
    "Allow all" and then block the selected categories.

Block access to websites with IP
    If enabled, you can not access websites using one IP but only the host name.

Enable URL filtering with expressions of
    If enabled, the URLs are scanned for words that fall into the categories selected. 
    For example may be blocked urls that contain the word *sex*.

List of blocked file extensions
    Enter the extensions that you want to block, separated by commas

Banned sites and IP addresses
    The list of banned sites and the list of hosts on the LAN that can not browse the Internet.

Sites and IP permissions
    The list of sites and hosts on the LAN allowed to bypass the content filter.

Bypass transparent proxy
========================

Set up some IP to bypass the transparent proxy and access
Internet without being proxied.

Create
------

Create a new bypass rule.

IP Address
    IP address of the host that will not be filtered by the proxy.

Antivirus
=========

Enable / disable virus scanning of web pages.
