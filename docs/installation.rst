############
Installation
############

Build Requirements
==================

To compile Nginx with this module, you will need an enviornment that can compile :code:`C` applications. If using Ubuntu, you can issue the following commands to acheive such an enviornment.

.. code-block:: bash

   sudo apt-get update
   sudo apt-get install build-essential


If using a different Linux distribution, please use the required installation commands to include :code:`gcc`.

Compiling and Install Nginx
===========================

Once you have the required dependencies, you will be able to compile Nginx using the following command.

.. code-block:: bash

   cd path/to/Nginx
   patch -p1 < path/to/repo/patches/http_servats_nginx_x.x.x.patch
   ./configure --add-module=path/to/repo/module/
   make
   make install
