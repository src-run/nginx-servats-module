#!/usr/bin/env bash

##
 # scripts/make.bash
 #
 # This file is part of the HTTP Servats Module.
 #
 # For the full copyright and license information, please view the LICENSE.md
 # file that was distributed with this source code.
 #
 ##

set -o nounset
set -o errexit

# Include the common variables file
if [ -f "scripts/includes/variables.bash" ];
then
    source scripts/includes/variables.bash

elif [ -f "includes/variables.bash" ];
then
    source includes/variables.bash

else
    echo "Could not find variables.bash" && exit -1
fi

# Include the common variables file
if [ -f "scripts/includes/functions.bash" ];
then
    source scripts/includes/functions.bash

elif [ -f "includes/functions.bash" ];
then
    source includes/functions.bash

else
    echo "Could not find functions.bash" && exit -1
fi

# Call the requested action
ngx_action ${0} ${1:-}

# EOF
