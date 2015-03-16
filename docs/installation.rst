############
Installation
############

Build Requirements
==================

To compile Nginx with this module, you will need an environment that can compile
:code:`C` applications. If using Ubuntu, you can issue the following commands to
achieve such an environment.

.. code-block:: bash

   sudo apt-get update
   sudo apt-get install build-essential


If using a different Linux distribution, please use the required installation
commands to include :code:`gcc`.

Build Procedure
===============

*Note: For the remainder of these instructions, I will assume you intend to work with
Nginx* :code:`1.7.10`. *Feel free to substitute another version per your requirements.*

Download and Prepare Nginx
--------------------------

Installation of this module requires applying a patch to the Nginx core source-
source. As this source-code changes with each release, there are *specific patch
files* provided for various versions of Nginx.

To download this module and Nginx, you can simply call the following commands.

.. code-block::  bash

   git clone https://github.com/scribenet/nginx-servats-module.git
   cd nginx-servats-module && mkdir vendor && cd vendor
   wget curl -s -L -O http://nginx.org/download/nginx-1.7.10.tar.gz
   tar --strip-components=1 -zxf nginx-1.7.10.tar.gz
   patch -p1 < ../patches/http_servats_nginx_1.7.10.patch


Compile and Install Nginx
-------------------------

After executing the command from the previous section, you will have a copy of
this module, as well a patched Nginx source within the vendor directory of the
module. To compile Nginx, simply execute the following commands from within the
root of the module's git repository path on your local machine.

.. code-block:: bash

   cd vendor
   ./configure --add-module=../module
   make install


Patching Unsupported Nginx Versions
===================================

If you are attempting to use this module with a version of Nginx that does not
have a pre-made `patch` file, it is suggest you proceed as follows.

*Note: It is highly recommended you configure you environment to use the integrated
test suite. Documentation on doing so can be found on the*
`Test Suite <test_suite.html>`_ *page.*

- Determine the closest matching patch file available (for example, if you
  wanted to compile this module against Nginx 1.7.6, you would choose the
  :code:`1.7.8` patch file).
- Attempt to apply the patch per the above instructions.
- If the patch operation *does not succeed* and outputs errors about being
  unable to apply specific blocks of the patch file:

  - Create a copy of the patch file you started with (named appropriately for
    the version of Nginx you are trying to compile).
  - Review the source code and patch file to determine the required changes.
  - Update the patch file and re-attempt to apply it once you believe you have
    satisfied any errors.

- Otherwise, if the patch operation *succeeds without error*:

  - It is possible the patch is valid against your version of Nginx.
  - It is recommended you verify the results of the patch by looking over the
    resulting Nginx source code.

- Perform the installation as described below and verify Nginx both *compiles*
  and *runs*, and that the *module behaves as expected*.

*Please: If you take the time to do this, please either submit an issue stating
that a specific patch properly worked with a version of Nginx not listed or
submit a pull request with the new patch file so others can benefit from your
effort.*
