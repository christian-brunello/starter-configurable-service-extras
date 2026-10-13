#
# starter-configurable-service-extras — process helpers
#
# Copyright (C) 2026 Christian Brunello <brncrs@gmail.com>
#
# Binaries invoked by starter-configurable-service process-transport.

bin_PROGRAMS = current-time sun-position

current_time_SOURCES = current-time.c
current_time_CPPFLAGS = $(AM_CPPFLAGS) $(GLIB_CFLAGS)
current_time_LDADD = $(GLIB_LIBS)

sun_position_SOURCES = sun-position.c
sun_position_CPPFLAGS = $(AM_CPPFLAGS) $(GLIB_CFLAGS)
sun_position_LDADD = $(GLIB_LIBS) -lm
