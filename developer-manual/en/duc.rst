===================
Disk analyzer (Duc)
===================

Official site: https://github.com/zevv/duc

This tool is used to visualize disk usage in a simply and nice graph.

Features:
* Indexing filesystem very fast
* Interact with graph with click and double click to navigate in the directories tree.

Overview
========
This tool is composed by two parts: **duc indexer** and **duc viewer**. The first one is launched every day and it indexes the ``/`` directory and it creates a file that is loaded by **duc viewer** to show graph.

In the graph are showed only directories over certain size, in particularly this size is *10MB* as you can see in file ``/etc/e-smith/events/actions/nethserver-duc-index``.
