# Nginx Module: servats

[![Travis branch](https://img.shields.io/travis/scribenet/nginx-servats-module/master.svg?style=flat-square)](https://nginx-servats-module.docs.scribe.tools/ci)
[![Gittag](https://img.shields.io/github/tag/scribenet/nginx-servats-module.svg?style=flat-square)](https://github.com/scribenet/nginx-servats-module/releases)
[![Documentation](https://readthedocs.org/projects/nginx-servats-module/badge/?version=latest&style=flat-square)](https://nginx-servats-module.docs.scribe.tools/docs)
[![License](https://img.shields.io/badge/license-MIT-008ac6.svg?style=flat-square)](https://nginx-servats-module.docs.scribe.tools/license)

*Scribe / Nginx Servats Module* is an Nginx module that provides server status information. For beutifully formatted documentation, visit our [Read the Docs page](https://nginx-servats-module.docs.scribe.tools/docs).

# Contents

1. [Installation](#installation)
  - [Patching the Nginx source](#patching-the-nginx-source)
  - [Compilation](#compilation)
  - [Patching unsupported versions](#patching-unsupported-versions)
2. [Configuration](#configuration)
  - [Definition](#definition)
  - [Working example](#working-example)
3. [Authors and Contributors](#authors-and-contributors)
4. [License](#license)

# Installation

Installation of this module requires applying a patch to the Nginx core source-
source. As this source-code changes with each release, there are *specific patch
files* provided for various versions of Nginx.

- [`0.8.54` and `0.8.55`](patches/http_servats_nginx_0.8.54.patch)
- [`1.0.11`](patches/http_servats_nginx_1.0.11.patch)
- [`1.4.2`](patches/http_servats_nginx_1.4.2.patch)
- [`1.6.2`](patches/http_servats_nginx_1.6.2.patch)
- [`1.7.8`](patches/http_servats_nginx_1.7.8.patch)
- [`1.7.10`](patches/http_servats_nginx_1.7.10.patch)

### Patching the Nginx source

To ready the Nginx source-code, choose the `*.patch` file that corresponds with
the version of Nginx you are trying to compile. Next, run the following patch
command (replacing `x.x.x` with the correct version string):

```
patch -p1 < extended_status-x.x.x.patch
```

As an example, to patch Nginx `0.8.54`/`0.8.55`, `1.0.11`, or `1.7.10`, you
would run one of the following commands, respectively:

```
patch -p1 < extended_status-0.8.54.patch
patch -p1 < extended_status-1.0.11.patch
patch -p1 < extended_status-1.7.10.patch
```

Be sure to review the output of the `patch` command and verify it was successful.
Generally, if it encounters an error it will inform you by providing the specific
block(s) within the patch it could not successfully apply.

### Compilation

*Before proceeding with this step, be sure you applied the appropriate patch per
the above instructions. If you are attempting to compile an unsupported version
of Nginx, see the below guide creating a new patch.*

To compile Nginx, run the following set of commands. You must replace the
directory path in the `./configure` line, after `--add-module=`, to point to the
location of this source code. Running `make` performs the actual compilation and
running `make install` installs the compiled files to your system.

```
./configure --add-module=dir/path/to/git-source/module
make
make install
```

*Note: It is likely you will want to configure additional aspects of Nginx.
Running `./configure --help` will provide you with a list of available options
to further customize the build process.*

### Patching unsupported versions

If you are attempting to use this module with a version of Nginx that does not
have a pre-made `patch` file, it is suggest you proceed as follows.

- Determine the closest matching patch file available (for example, if you
  wanted to compile this module against Nginx 1.7.6, you would choose the
  [1.7.8](patches/http_servats_nginx_1.7.8.patch) patch file).
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

## Configuration

This module allows for a few Nginx configuration directive, the most important one
allowing for you to enable or disable the module: `servats`. It can be set to
either *on* or *off*, defaulting to *off*. It is valid in the *http*, *server*,
and *location* Nginx configuration contexts.

### Definitions

- *Syntax*: `servats on|off;`
  - *Default state*: `off`
  - *Valid contexts*: `http`, `server`, `location`
  - *Description*: Enables or disable the module.
- *Syntax*: `servats_theme_both on|off;`
  - *Default state*: `on`
  - *Valid contexts*: `http`, `server`, `location`
  - *Description*: Should the internal JS/CSS be applied in conjunction with any user-supplied JS/CSS or should the internal JS/CSS be disabled when user-supplied JS/CSS is configured.
- *Syntax*: `servats_theme_href_css "/a/path/to/custom.css";`
  - *Default state*: `<empty>`
  - *Valid contexts*: `http`, `server`, `location`
  - *Description*: Absolute or relative path to a custom CSS file to include in the status page.
- *Syntax*: `servats_theme_href_script_lib "/a/path/to/lib.js";`
  - *Default state*: `<empty>`
  - *Valid contexts*: `http`, `server`, `location`
  - *Description*: Absolute or relative path to a custom JS library to include in the status page.
- *Syntax*: `servats_theme_href_script "/a/path/to/main.js";`
  - *Default state*: `<empty>`
  - *Valid contexts*: `http`, `server`, `location`
  - *Description*: Absolute or relative path to a custom JS file to include in the status page.

### Working example

```
location = /status {
  servats on;
}
```

## License

This Nginx module is released under *The MIT License (MIT)* unless otherwise
explicitly stated. See the [LICENSE.md](LICENSE.md) file distributed with this
source code for additional licensing information.
