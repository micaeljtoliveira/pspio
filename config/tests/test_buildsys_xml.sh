#!/bin/sh
#
# Copyright (C) 2011-2016 Yann Pouillon <devops@materialsevolution.es>
#
# This file is part of Libpspio.
#
# This Source Code Form is subject to the terms of the Mozilla Public License,
# version 2.0. If a copy of the MPL was not distributed with this file, You can
# obtain one at https://mozilla.org/MPL/2.0/.
#
# Libpspio is distributed in the hope that it will be useful, but WITHOUT ANY
# WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
# A PARTICULAR PURPOSE. See the Mozilla Public License version 2.0 for more
# details.

#
# IMPORTANT NOTE:
#
#   For maintainer use only!
#
#   PLEASE DO NOT EDIT THIS FILE, AS IT COULD CAUSE A SERIOUS LOSS OF DATA.
#   *** YOU HAVE BEEN WARNED! ***
#

# Check that we are in the right directory
if test ! -s "./configure.ac" -o ! -d "psp_references"; then
  echo "test_buildsys_xml: Cowardly refusing to remove something from here!" >&2
  exit 1
fi

# stop at first error
set -e

# Set test parameters
test_name="buildsys-test-plain"
test_options="--enable-xml"

# Prepare the build
./wipeout.sh
./autogen.sh
mkdir "tmp-${test_name}"
cd "tmp-${test_name}"

# Check configuration
../configure ${test_options}
make distcheck
make install DESTDIR="${PWD}/install"

# Clean-up the mess
cd ..
rm -rf "tmp-${test_name}"
./wipeout.sh
