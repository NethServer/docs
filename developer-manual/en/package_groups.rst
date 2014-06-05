==============
Package groups
==============

The composition of package groups is documented on http://dev.nethserver.org/nethserver/comps.html, an automatically generated document in XHTML format. 
 
Generate comps file
===================

Checkout the **comps** git repository, enter the directory and execute:: 

  $ make comps-ns<version>.xml

For instance, see how :file:`nethserver-groups.xml` is generated from :file:`nethserver-groups.xml.in`.


For further information on how to modify :file:`*.xml.in` files, see  Fedora Project Wiki: https://fedoraproject.org/wiki/How_to_use_and_edit_comps.xml_for_package_groups .

