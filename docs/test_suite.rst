##############
The Test Suite
##############

Environment Setup
=================

To run the test suite, you must have a sane Ruby environment setup. I would
highly suggest utilizing a Ruby version management utility such as
`RVM <https://rvm.io/>`_, `Chruby <https://github.com/postmodern/chruby>`_,
or one of the `many alternatives <ruby version manager>`_.  **This tutorial will
be using** `RVM <https://rvm.io/>`_ **and assume you are running a modern version
of** `Ubuntu Linux <http://www.ubuntu.com/>`_ **or a Debian-compatible system**.

*Note: For a detailed rundown of available options, as well as additional
information on installation using alternate operating systems, I suggest reading
Mischa Taylor's guide to setting up a*
`Sane Ruby Environment <http://misheska.com/blog/2013/12/26/set-up-a-sane-ruby-cookbook-authoring-environment-for-chef/#linux>`_
*from the Chef series.*

System Requirements
-------------------

In order to build Ruby, you will need some Ubuntu packages. The minimal requirements
include a compiler (and other build tools, which you will need to build Nginx
anyway), as well as some header files for :code:`libxml2`, :code:`libxslt`, and
:code:`libssl`.

.. code-block:: bash

   sudo apt-get update
   sudo apt-get install -y build-essential libxml2-dev libxslt-dev libssl-dev


RVM
---

To install RVM as well as Ruby :code:`2.2.1`, execute the following commands.

.. code-block:: bash

   \curl -sSL https://get.rvm.io | bash
   source $HOME/.rvm/scripts/rvm
   rvm install ruby-2.2.1


After completing the above, executing :code:`rvm list` should show the following
output.

.. code-block:: text

   rvm rubies

   =* ruby-2.2.1 [ x86_64 ]

   # => - current
   # =* - current && default
   #  * - default

You can confirm Ruby :code:`2.2.1` is being properly called by issuing
:code:`ruby --version`. *Note: your exact version string and build date will
not be exactly the same as the output provided here.*

.. code-block:: text

   ruby 2.2.1p85 (2015-02-26 revision 49769) [x86_64-linux]


Gem Dependencies
----------------

If you haven't cloned the *Nginx Servats Module* repository yet, do so now. If
you already have, enter the directory now.

.. code-block:: bash

   git clone https://github.com/scribenet/nginx-servats-module.git
   cd nginx-servats-module


The Gem dependencies are handled via the GemFile, which :code:`bundle` uses to
install the requested gems. Issue the bundle command now.

.. code-block:: bash

   bundle


You will receive output similar to the following.

.. code-block:: text

   Fetching gem metadata from https://rubygems.org/.........
   Fetching version metadata from https://rubygems.org/..
   Resolving dependencies...
   Using rake 10.4.2
   Installing curb 0.8.6
   Installing diff-lcs 1.2.5
   Installing rspec-support 3.2.2
   Installing rspec-core 3.2.2
   Installing rspec-expectations 3.2.0
   Installing rspec-mocks 3.2.1
   Installing rspec 3.2.0
   Using bundler 1.8.4
   Bundle complete! 3 Gemfile dependencies, 9 gems now installed.
   Use `bundle show [gemname]` to see where a bundled gem is installed.


You are now ready to utilize the integrated build task manager and test suite!


Compiling and Testing
=====================

The :code:`rake` command is used to handle dispatching the tasks required to
download, patch, and compile Nginx, as well as run the provided test suite.

Give it a try (by default it will use Nginx :code:`1.7.10`).

.. code-block:: bash

   rake nginx:compile
   rake test


Be patient during the compilation step; depending on your system this could take
some time. Once Nginx is compiled, running :code:`rake text` will run the tests.
Assuming everything went well, you should see a collection of green assertions
with the block ending in :code:`12 examples, 0 failures`. The number of examples
will change over time as more tests are added, the important part to note is that
:code:`0 failures` occurred.

You can now start up Nginx yourself if you'd like to view the page manually.

.. code-block:: bash

   rake nginx:start
   google-chrome http://localhost:8888/servats


The above command assumes you have `Google Chrome <https://www.google.com/chrome>`_
installed. If you do not, simply open the URL in your browser of choice. Once
you've finished taking a look, call :code:`rake nginx:stop` to stop the Nginx
test server.

To compile the module using a different version of Nginx, simply set the
:code:`NGX_VERSION_ENV` variable prior to calling :code:`rake nginx:compile`.
For example, to compile Nginx :code:`1.4.2` and run the tests:

.. code-block:: bash

   NGX_VERSION_ENV=1.4.2 rake nginx:compile
   rake test


If you are attempting to compile an Nginx version not supported by default, be
sure to provide a patch file within the :code:`patches/` folder in the repository
root.
