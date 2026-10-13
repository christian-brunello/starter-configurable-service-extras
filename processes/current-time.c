#include <stdio.h>
#include <stdlib.h>

#include <glib.h>

static unsigned
calculate_day_minutes(GDateTime *p)
{
  int hour;
  int minute;

  hour = g_date_time_get_hour(p);
  minute = g_date_time_get_minute(p);

  return (unsigned) (hour * 60 + minute);
}

static unsigned
calculate_day_seconds(GDateTime *p)
{
  unsigned minutes;
  int seconds;

  minutes = calculate_day_minutes(p);
  seconds = (int) g_date_time_get_seconds(p);

  return minutes * 60 + (unsigned) seconds;
}

int
main(int argc, char *argv[])
{
  g_autoptr(GDateTime) now = NULL;

  (void) argc;
  (void) argv;

  now = g_date_time_new_now_local();

  printf("{"
	 "\"year\": %u, "
	 "\"month\": %u, "
	 "\"day\": %u, "
	 "\"hour\": %u, "
	 "\"minute\": %u, "
	 "\"second\": %u, "
	 "\"dayMinutes\": %u, "
	 "\"daySeconds\": %u, "
	 "\"unix\": %ld, "
	 "\"UTCOffset\": %lu, "
	 "\"timezone\": \"%s\""
	 "}",
	 (unsigned) g_date_time_get_year(now),
	 (unsigned) g_date_time_get_month(now),
	 (unsigned) g_date_time_get_day_of_month(now),
	 (unsigned) g_date_time_get_hour(now),
	 (unsigned) g_date_time_get_minute(now),
	 (unsigned) g_date_time_get_seconds(now),
	 calculate_day_minutes(now),
	 calculate_day_seconds(now),
	 (long) g_date_time_to_unix(now),
	 (long) g_date_time_get_utc_offset(now),
	 g_date_time_get_timezone_abbreviation(now));

  return EXIT_SUCCESS;
}
