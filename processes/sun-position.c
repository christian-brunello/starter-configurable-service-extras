#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <glib.h>

#define PI 3.14159265358979323846

#define INV_LAT 100.0
#define INV_LON 200.0

typedef struct {
    double azimuth;   // 0° = Nord, 180° = Sud
    double elevation; // Gradi sopra l'orizzonte
} SolarPosition;


static SolarPosition calculate_current_solar_position(double lat, double lon) 
{
  SolarPosition pos;
  g_autoptr(GDateTime) dt_local;

  dt_local = g_date_time_new_now_local();

  // 1. Convertiamo sempre in UTC per eliminare fusi orari e ora legale
  g_autoptr(GDateTime) dt = g_date_time_to_utc(dt_local);

  int day_of_year = g_date_time_get_day_of_year(dt);

  // Ora decimale in UTC
  double hour_utc = g_date_time_get_hour(dt) + 
    (g_date_time_get_minute(dt) / 60.0) + 
    (g_date_time_get_second(dt) / 3600.0);

  // 2. Declinazione solare (invariata)
  double declination = 23.45 * sin(2.0 * PI * (284 + day_of_year) / 365.0 * (PI / 180.0));

  // 3. Equazione del tempo (invariata)
  double b = 2.0 * PI * (day_of_year - 81) / 364.0;
  double eq_time = 9.87 * sin(2.0 * b) - 7.53 * cos(b) - 1.5 * sin(b);

  // 4. Calcolo dell'Ora Solare Vera (LST - Local Solar Time)
  // Invece di usare un meridiano di riferimento, usiamo direttamente la longitudine.
  // Ogni grado di longitudine Est aggiunge 4 minuti rispetto a Greenwich (UTC).
  // Ogni grado Ovest li sottrae.
  double solar_time_fix = eq_time + (4.0 * lon); 
  double solar_hour = hour_utc + (solar_time_fix / 60.0);

  // 5. Angolo orario (H)
  // Ora 12.0 è il mezzogiorno solare a Greenwich
  double hour_angle = 15.0 * (solar_hour - 12.0);

  // ... (il resto dei calcoli trigonometrici rimane identico) ...

  // Riassunto delle conversioni e calcolo finale
  double lat_rad = lat * (PI / 180.0);
  double decl_rad = declination * (PI / 180.0);
  double h_rad = hour_angle * (PI / 180.0);

  double sin_elev = sin(lat_rad) * sin(decl_rad) + cos(lat_rad) * cos(decl_rad) * cos(h_rad);
  if (sin_elev > 1.0) sin_elev = 1.0; else if (sin_elev < -1.0) sin_elev = -1.0;
  pos.elevation = asin(sin_elev) * (180.0 / PI);

  double cos_az = (sin(decl_rad) - sin(lat_rad) * sin_elev) / (cos(lat_rad) * cos(asin(sin_elev)));
  if (cos_az > 1.0) cos_az = 1.0; else if (cos_az < -1.0) cos_az = -1.0;
  pos.azimuth = acos(cos_az) * (180.0 / PI);

  if (solar_hour > 12.0 || hour_angle > 0) {
      pos.azimuth = 360.0 - pos.azimuth;
  }

  return pos;
}

int main(int argc, char *argv[])
{
  time_t timestamp;
  // double latitude = 45.223072502092485;
  // double longitude = 11.999837862115918;
  double latitude = INV_LAT;
  double longitude = INV_LON;
  SolarPosition pos;
  g_autoptr(GOptionContext) context = NULL;
  g_autoptr(GDateTime) now = NULL;
  GError *error = NULL;
  GOptionEntry entries[] = {
    { "latitude", 'a', 0, G_OPTION_ARG_DOUBLE, &latitude, "Reference latitude", "LAT" },
    { "longitude", 'o', 0, G_OPTION_ARG_DOUBLE, &longitude, "Reference longitude", "LON" },
    G_OPTION_ENTRY_NULL
  };

  context = g_option_context_new ("- sun position");
    
  g_option_context_add_main_entries (context, entries, NULL);
    
  if(!g_option_context_parse (context, &argc, &argv, &error)) {
    fprintf(stderr, "Command line parsing failed: %s\n", error ? error->message : "unknown error");
    g_error_free (error);

    exit(EXIT_FAILURE);
  }
  
  if(latitude == INV_LAT && longitude == INV_LON) {
    fprintf(stderr, "latitude and longitude arguments are mandatory!\n");

    exit(EXIT_FAILURE);
  }
    
  pos = calculate_current_solar_position(latitude, longitude);
  
  now = g_date_time_new_now_local();
  
  timestamp = g_date_time_to_unix(now);
  
  printf("{\"timestamp\": %lu, \"latitude\": %lf, \"longitude\": %lf, \"azimuth\": %lf, \"elevation\": %lf}",
         timestamp, latitude, longitude, pos.azimuth, pos.elevation);


  return EXIT_SUCCESS;
}

