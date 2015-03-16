########################
Configuration Directives
########################

This module allows for a variety of configuration directives. If you simply want
to view the status of your Nginx server and have no interest in further customization,
the only requirement is to enable the module using the first directive, :code:`servats`.

servats
=======

This config directive turns the module on or off. By default, the module is disabled.

:Default:			:code:`off`
:Valid Entries:		:code:`off`, :code:`on`
:Contexts:			:code:`http`, :code:`server`, :code:`location`

Example usage:

.. code-block:: nginx

   location /status {
     servats on;
   }


Unlike other implementations of the "extended status" module, disabling this module within
inner location blocks is supported. For example, the following configuration would show
the server status when navigating to :code:`/status` but not :code:`/status/disabled`:

.. code-block:: nginx

   location /status {
     servats on;

     location /disabled {
       servats off;
     }
   }


servats_theme_href_css
======================

This directive can be optionally set to apply a custom CSS :code:`link` within the
HTML header. When set with :code:`servats_theme_both` enabled, the custom CSS will
be the *last CSS include*. When :code:`servats_theme_both` is disabled, the custom
CSS will be the *only CSS include*.

:Default:			:code:`""`
:Valid Entries:		:code:`""`, :code:`"/a/path/to/custom.css"`, :code:`[...]`
:Contexts:			:code:`http`, :code:`server`, :code:`location`

Example usage:

.. code-block:: nginx

   location /status {
     servats                on;
     servats_theme_both     on;
     servats_theme_href_css "/a/path/to/custom.css";
   }


servats_theme_href_script_lib
=============================

This directive can be optionally set to include a custom JavaScript :code:`script`
within the HTML header. It is intended to include an external, custom JavaScript library.
When set with :code:`servats_theme_both` enabled, the custom JS will be the
*last JS library* included in the header. When :code:`servats_theme_both` is disabled,
the custom JS include will be the *only JS include*.

:Default:			:code:`""`
:Valid Entries:		:code:`""`, :code:`"/a/path/to/custom/js/library.js"`, :code:`[...]`
:Contexts:			:code:`http`, :code:`server`, :code:`location`

Example usage:

.. code-block:: nginx

   location /status {
     servats                       on;
     servats_theme_both            on;
     servats_theme_href_css        "/a/path/to/custom.css";
     servats_theme_href_script_lib "/a/path/to/custom/js/library.js";
   }


servats_theme_href_script
=========================

This directive can be optionally set to include a custom JavaScript :code:`script`
at the end of the HTML body. It is intended to include an external, custom JavaScript
file that performs custom actions on the HTML. When set with :code:`servats_theme_both`
enabled, the custom JS will be the *last JS file* included at the end of the HTML body.
When :code:`servats_theme_both` is disabled, the custom JS will be the *only JS include*
at the end of the HTML body.

:Default:			:code:`""`
:Valid Entries:		:code:`""`, :code:`"/a/path/to/custom/js/main.js"`, :code:`[...]`
:Contexts:			:code:`http`, :code:`server`, :code:`location`

Example usage:

.. code-block:: nginx

   location /status {
     servats                       on;
     servats_theme_both            on;
     servats_theme_href_css        "/a/path/to/custom.css";
     servats_theme_href_script_lib "/a/path/to/custom/js/library.js";
     servats_theme_href_script     "/a/path/to/custom/js/main.js";
   }


servats_theme_both
==================

This configuration directive determines whether the internal CSS and JavaScript should
be applied *as well as* any user-defined CSS and JavaScript. By default, this directive
is enabled. This means that using any of the :code:`servats_theme_href_*` directives
will apply those *in addition to* the internal, default CSS and JavaScript. When this
directive is set to :code:`off`, only the user-defined CSS and JavaScript will be
included in the page.

:Default:			    :code:`on`
:Valid Entries:		:code:`off`, :code:`on`
:Contexts:			  :code:`http`, :code:`server`, :code:`location`

Example usage:

.. code-block:: nginx

   location /status {
     servats            on;
     servats_theme_both on;
   }
