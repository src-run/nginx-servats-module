#!/usr/bin/env bash

##
 # scripts/includes/variables.bash
 #
 # This file is part of the HTTP Servats Module.
 #
 # For the full copyright and license information, please view the LICENSE.md
 # file that was distributed with this source code.
 #
 ##

# Path to self (this script)
readonly DIR_SELF="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Path to project root
readonly DIR_ROOT=${DIR_SELF}/../../

# Vendor directory (Nginx source)
readonly DIR_VENDOR=${DIR_ROOT}vendor

# Build directory (Nginx compiled)
readonly DIR_BUILD=${DIR_ROOT}build

# Path to the Nginx configuration file
NGX_CONFIG=${DIR_ROOT}scripts/fixtures/nginx.conf

# Version of Nginx to build against
NGX_VERSION=${NGX_VERSION_ENV:-"1.7.10"}

# Path to the Nginx patche file
NGX_PATCH=${DIR_ROOT}patches/http_servats_nginx_${NGX_VERSION}.patch

# EOF
