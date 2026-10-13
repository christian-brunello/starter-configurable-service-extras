#!/bin/bash
set -e

echo "Initializing Autotools for starter-configurable-service-extras..."

if [ -d "m4" ]; then
    aclocal -I m4
else
    aclocal
fi

autoconf
autoheader
libtoolize --copy --force
automake --add-missing --copy

echo "Done. Now run: ./configure && make"
