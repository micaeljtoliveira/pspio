#!/bin/sh
#
# Copyright (C) 2011 J. Alberdi, M. Oliveira, Y. Pouillon, and M. Verstraete
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation; either version 3 of the License, or 
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
#
# $Id: wipeout.sh 144 2011-08-31 18:11:24Z pouillon $
#

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
  echo "test_buildsys_plain: Cowardly refusing to remove something from here!" >&2
  exit 1
fi

# stop at first error
set -e

# Set test parameters
test_name="buildsys-test-plain"
test_options=""

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
