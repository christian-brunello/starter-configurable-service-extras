#
# starter-configurable-service-extras - Makefile.am
#
# Copyright (C) 2026 Christian Brunello <brncrs@gmail.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

ACLOCAL_AMFLAGS = -I m4

SUBDIRS = processes doc

EXTRA_DIST = README AUTHORS NEWS ChangeLog plugins/README.md \
	starter-configurable-service-extras.pc.in

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = starter-configurable-service-extras.pc

.PHONY: doc
doc:
	$(MAKE) $(AM_MAKEFLAGS) -C doc pdf
