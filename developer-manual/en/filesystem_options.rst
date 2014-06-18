===================
Filesystems options
===================

Some programs may need special filesystem options to work correctly. 
For example, Samba needs *acl* and *user_xattr* to enable fully compatibility with Windows systems.

NethServer add a special ``fstab`` key inside the ``configuration`` e-smith db.
Each prop of ``fstab`` is in the form ``mountpoint=options``.

For example: ::

 fstab=configuration
   /=defaults,acl
   /boot=defaults

The entries are not mandatory, if a filesystem hasn't an associated property, no modification will be done.

After each modification to ``fstab`` properties, the *fstab-update* event must be fired.
The *fstab-update* event will expand the :file:`/etc/fstab` file and then remount all filesystems except for types: swap proc sysfs devpts.

Example: ::

 config setprop fstab / defaults,acl
 signal-event fstab-update
