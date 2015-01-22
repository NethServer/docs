=============
Release notes
=============

* After system installation, the server-manager shows the *First
  Configuration wizard*, where the admin can set the password, change
  the host name and so on.

* The :guilabel:`Remote access` page has been removed. Access to the
  *server-manager* is now controlled from :guilabel:`Network services`
  page, service :guilabel:`httpd-admin`.

* Secure Shell (SSH) access is configured from the new :guilabel:`SSH`
  page.
  
* The :guilabel:`Package manager` page has been renamed
  :guilabel:`Software center`, and moved to the *Administration*
  category.  To enhance the page usability, now two separate tabs show
  respectively *Available* and *Installed* modules.  It is now possible
  to update the installed packages, and read the updates changelog.
  
* The new page, :guilabel:`Server certificate` shows the self-signed
  SSL certificate and allows generating a new one, customizing also
  the *alternative names* of the server.  As consequence, changing the
  host name from the :guilabel:`Server name` page does not generate a
  new SSL certificate any more.  The same applies for the
  :guilabel:`Organization contacts`.

