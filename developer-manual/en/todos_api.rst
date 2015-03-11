.. index::
   pair: TODO; API

========
TODO API
========

The *TODO API* is specific for the Server Manager web application. It
is designed to execute a list of checks and possibly report the
outcome to the admin user.

An RPM can install one or more executable scripts under
:file:`/etc/nethserver/todos.d/`.

* The script must print the results formatted according to JSON
  [#JSON]_ and the following schema: ::

    {
        "text": "free text",
	"icon": "info-circle",
	"action": {
	    "url": "/User",
	    "label": "Link label"
	}
    }

  ``icon`` and ``action`` keys are optional. The only required key is
  ``text``.  The ``url`` value is actually an absolute path to the
  Server Manager module.  Future versions may support real URLs.

* If the script exit code is non-zero, or if the output is not
  correctly JSON-encoded, an error message is sent to the system log.

* The script must be aware of locale settings, as its output is
  displayed on the user's browser [#Gettext]_.

The executable helper :file:`/usr/libexec/nethserver/admin-todos` is
responsible for the invocation of scripts, validation of output and
error reporting.  It is executed by the :file:`AdminTodo` UI module.  

The :file:`AdminTodo` known callers are:

* :guilabel:`Dashboard`
* :guilabel:`Software center`

Translations
============

Steps to setup translation for a new todo:

1. Be sure gettext is installed in your system

2. Add the todo script to the git repository

3. Create locale directory inside the git repository root: ::

     mkdir -p locale

4. Extract the strings:  ::

     xgettext --msgid-bugs-address "nethserver@googlegroups.com" --package-version "$(git describe)"  --package-name "$(basename `pwd`)" --foreign-user -d "$(basename `pwd`)" -o "locale/$(basename `pwd`).pot" -L Python root/etc/nethserver/todos.d/*

5. Create the language file from template: ::

     mkdir -p locale/en/LC_MESSAGES
     cp locale/<pkgname>.pot  locale/en/LC_MESSAGES/<pkgname>.po

6. Substitute following fields in po file:

  * DESCRIPTIVE
  * LANGUAGE <LL@li.org>
  * CHARSET (must be UTF-8)
  * FIRST AUTHOR <EMAIL@ADDRESS>, YEAR.

7. Add translations. You can try poedit editor

8. Repeat for all languages

9. Inside the spec file, add this dependency: ::

     BuildRequires: gettext

9. In the %build section of the spec file, add following snippet: ::

     for D in locale/*/LC_MESSAGES; do
       [ -d "$D" ] && msgfmt -v $D/%{name}.po -o $D/%{name}.mo
     done

10. In the \%install section of the spec file, add following snippet: ::

      for F in locale/*/LC_MESSAGES/%{name}.mo; do
        install -D $F $RPM_BUILD_ROOT/%{_datadir}/$F
      done
      %{find_lang} %{name}

11. Change %file line to this: ::

      %files -f %{name}-%{version}-%{release}-filelist -f %{name}.lang

.. rubric:: References

.. [#JSON] JSON (JavaScript Object Notation) is a lightweight
           data-interchange format. http://json.org/
.. [#Gettext] GNU gettext utilities http://www.gnu.org/software/gettext/
	  
	
