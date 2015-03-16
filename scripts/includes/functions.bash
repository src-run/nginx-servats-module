#!/usr/bin/env bash

##
 # scripts/includes/functions.bash
 #
 # This file is part of the HTTP Servats Module.
 #
 # For the full copyright and license information, please view the LICENSE.md
 # file that was distributed with this source code.
 #
 ##

#
# Output status message to user
#
out_line()
{
	local caller=${NGX_MAKE_CALLER:-"make.bash"}
	local notice=${1:-"Undefined message."}

	echo -e "[${caller}] ${notice}"
}

#
# Output step status message to user
#
out_step()
{
	local notice=${1:-"Undefined message."}

	out_line "Step     : ${notice}"
}

#
# Output error message and exit
#
out_error()
{
	echo -e ${1:-"Error"}
	exit -5
}

#
# Output usage text and exit
#
out_usage()
{
	local caller=./$(basename ${NGX_MAKE_CALLER:-"make.bash"})

	out_error "\nUsage: ${caller} [clean|bootstrap|make|install|all]\n"
}

#
# Clean our installation completly
#
dir_clean()
{
	out_step "Removing binary and source directories."

	rm -fr "${DIR_VENDOR}"
	rm -fr "${DIR_BUILD}"
}

#
# Setup the required directory structure
#
dir_setup()
{
	out_step "Bootstrapping required directories."

	mkdir -p ${DIR_BUILD}
	mkdir -p ${DIR_VENDOR}
}

#
# Download Nginx source and unarchive
#
ngx_download()
{
	if [ ! -d ${DIR_VENDOR} ] || [ ! "$(ls -A ${DIR_VENDOR} 2>/dev/null)" ];
	then
		local ngx_dl_version=${NGX_VERSION}

		cd ${DIR_VENDOR}

		out_step "Downloading Nginx (${ngx_dl_version})."
		curl -s -L -O http://nginx.org/download/nginx-${NGX_VERSION}.tar.gz >/dev/null || \
			out_error "Could not download the requested Nginx version ${ngx_dl_version}."

		out_step "Un-archiving source files."
		tar --strip-components=1 -zxf nginx-${ngx_dl_version}.tar.gz >/dev/null || \
			out_error "Invalid archive resulted from download."

		rm nginx-${ngx_dl_version}.tar.gz

		ngx_patch
	fi
}

#
# Patch Nginx source
#
ngx_patch()
{
	if [ -f ${NGX_PATCH} ];
	then
		local ngx_patch_filepath=${NGX_PATCH}
		local ngx_patch_basename=$(basename ${NGX_PATCH})

		cd ${DIR_VENDOR}

		out_step "Patching Nginx source code using ${ngx_patch_basename}"
		cp ${ngx_patch_filepath} ${ngx_patch_basename}
		patch -p1 < ${ngx_patch_basename} >/dev/null || out_error "Could not patch Nginx source."

		rm ${ngx_patch_basename}
	else
		out_error "Could not locate patch file ${NGX_PATCH}"
	fi
}

#
# Configure Nginx with debug and no compiler optomizations
#
ngx_cfg_dbg()
{
	out_step "Configuring with debug enabled." && sleep 1

	cd ${DIR_VENDOR}

	make clean 2>/dev/null || true

	CFLAGS="-g -O0" \
	./configure \
		--with-debug \
		--prefix=${DIR_BUILD} \
		--conf-path=conf/nginx.conf \
		--error-log-path=logs/error.log \
		--http-log-path=logs/access.log \
		--add-module=../module/ \
		>/dev/null
}

#
# Configure Nginx with no debug and allow compiler optomizations
#
ngx_cfg_no_dbg()
{
	out_step "Conifiguring with debug disabled."

	cd ${DIR_VENDOR}

	make clean 2>/dev/null || true

	./configure \
		--prefix=${DIR_BUILD} \
		--conf-path=conf/nginx.conf \
		--error-log-path=logs/error.log \
		--http-log-path=logs/access.log \
		--add-module=../module/ \
		>/dev/null
}

#
# Configure Nginx with/without debug based on
#
ngx_cfg()
{
	local no_debug=${NGX_NO_DEBUG:-0}

	if [ ${no_debug} -eq 1 ];
	then
		ngx_cfg_no_dbg
	else
		ngx_cfg_dbg
	fi
}

#
# Compile Nginx (make)
#
ngx_compile()
{
	out_step "Running source compilation."

	cd ${DIR_VENDOR}

	make build >/dev/null || out_error "Error during compilation!"
}

#
# Install Nginx (make install)
#
ngx_install()
{
	out_step "Running compiled binary installation."

	cd ${DIR_VENDOR}

	make install >/dev/null || out_error "Error during installation!"

	out_step "Symlinking test config into build conf directory."
	cd ${DIR_BUILD}/conf/ && rm nginx.conf
	ln -s ${NGX_CONFIG} nginx.conf || out_error "Couldn't symlink the Nginx test configuration."
}

#
# The action chooser
#
ngx_action()
{
	if [ -z "${1:-}" ] || [ -z "${2:-}" ];
	then
		out_usage "${1}" && echo -5
	fi

	local caller=$(basename ${1})
	local action=${2:-}

	export NGX_MAKE_CALLER=${caller}

	out_line "Beginning: Action \"${action:-"Unknown"}\""

	case "${action}" in
		clean)
				dir_clean
				;;
        bootstrap)
        		dir_setup
        		ngx_download
                ;;
        make)
                dir_setup
                ngx_download
                ngx_cfg
                ngx_compile
                ;;
        install)
        		ngx_install
        		;;
        all)
        		dir_clean
        		dir_setup
        		ngx_download
                ngx_cfg
        		ngx_compile
        		ngx_install
                ;;
        *)
                out_usage ${0:-}
	esac

	out_line "Completed: Action \"${action}\""
}

# EOF
