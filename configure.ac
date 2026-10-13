#
# starter-configurable-service-extras - configure.ac
#
# Copyright (C) 2026 Christian Brunello <brncrs@gmail.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Process this file with autoconf to produce configure.

AC_INIT([starter-configurable-service-extras], [0.1.0], [startercontroller@gmail.com])
AC_CONFIG_SRCDIR([processes/sun-position.c])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIRS([m4])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])

AC_PROG_CC
AM_PROG_AR
LT_INIT

PKG_PROG_PKG_CONFIG
PKG_CHECK_MODULES([GLIB], [glib-2.0 >= 2.44])

AC_CHECK_LIB([m], [sin], [], [AC_MSG_ERROR([libm is required])])

AC_PATH_TOOL([MAKEINFO], [makeinfo], [:])
if test "$MAKEINFO" = ":" ; then
    AC_MSG_ERROR([makeinfo not found. Please install it and try again.])
fi

AC_CONFIG_FILES([
  Makefile
  processes/Makefile
  doc/Makefile
])
AC_OUTPUT
