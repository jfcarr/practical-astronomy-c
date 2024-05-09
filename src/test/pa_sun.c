#include "pa_sun.h"
#include "../lib/pa_sun.h"
#include "../lib/pa_types.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

void test_approximate_position_of_sun(double lct_hours, double lct_minutes,
                                      double lct_seconds, double local_day,
                                      int local_month, int local_year,
                                      bool is_daylight_saving,
                                      int zone_correction,
                                      TSunPosition expected_result) {
  TSunPosition actual_result = approximate_position_of_sun(
      lct_hours, lct_minutes, lct_seconds, local_day, local_month, local_year,
      is_daylight_saving, zone_correction);

  printf("[Approximate Position of Sun]\n");
  printf("\tExpected:\n");
  printf("\t\tRA is %0.0fh %0.0fm %0.2fs\n", expected_result.sun_ra_hour,
         expected_result.sun_ra_min, expected_result.sun_ra_sec);
  printf("\t\tDeclination is %0.0fd %0.0fm %0.2fs\n",
         expected_result.sun_dec_deg, expected_result.sun_dec_min,
         expected_result.sun_dec_sec);
  printf("\tActual:\n");
  printf("\t\tRA is %0.0fh %0.0fm %0.2fs\n", actual_result.sun_ra_hour,
         actual_result.sun_ra_min, actual_result.sun_ra_sec);
  printf("\t\tDeclination is %0.0fd %0.0fm %0.2fs\n", actual_result.sun_dec_deg,
         actual_result.sun_dec_min, actual_result.sun_dec_sec);

  assert(actual_result.sun_dec_deg == expected_result.sun_dec_deg);
  assert(actual_result.sun_dec_min == expected_result.sun_dec_min);
  assert(actual_result.sun_dec_sec == expected_result.sun_dec_sec);
  assert(actual_result.sun_ra_hour == expected_result.sun_ra_hour);
  assert(actual_result.sun_ra_min == expected_result.sun_ra_min);
  assert(actual_result.sun_ra_sec == expected_result.sun_ra_sec);
}

void test_precise_position_of_sun(double lct_hours, double lct_minutes,
                                  double lct_seconds, double local_day,
                                  int local_month, int local_year,
                                  bool is_daylight_saving, int zone_correction,
                                  TSunPosition expected_result) {
  TSunPosition actual_result = precise_position_of_sun(
      lct_hours, lct_minutes, lct_seconds, local_day, local_month, local_year,
      is_daylight_saving, zone_correction);

  printf("[Precise Position of Sun]\n");
  printf("\tExpected:\n");
  printf("\t\tRA is %0.0fh %0.0fm %0.2fs\n", expected_result.sun_ra_hour,
         expected_result.sun_ra_min, expected_result.sun_ra_sec);
  printf("\t\tDeclination is %0.0fd %0.0fm %0.2fs\n",
         expected_result.sun_dec_deg, expected_result.sun_dec_min,
         expected_result.sun_dec_sec);
  printf("\tActual:\n");
  printf("\t\tRA is %0.0fh %0.0fm %0.2fs\n", actual_result.sun_ra_hour,
         actual_result.sun_ra_min, actual_result.sun_ra_sec);
  printf("\t\tDeclination is %0.0fd %0.0fm %0.2fs\n", actual_result.sun_dec_deg,
         actual_result.sun_dec_min, actual_result.sun_dec_sec);

  assert(actual_result.sun_dec_deg == expected_result.sun_dec_deg);
  assert(actual_result.sun_dec_min == expected_result.sun_dec_min);
  assert(actual_result.sun_dec_sec == expected_result.sun_dec_sec);
  assert(actual_result.sun_ra_hour == expected_result.sun_ra_hour);
  assert(actual_result.sun_ra_min == expected_result.sun_ra_min);
  assert(actual_result.sun_ra_sec == expected_result.sun_ra_sec);
}

void test_sun_distance_and_angular_size(double lct_hours, double lct_minutes,
                                        double lct_seconds, double local_day,
                                        int local_month, int local_year,
                                        bool is_daylight_saving,
                                        int zone_correction,
                                        TSunDistanceSize expected_result) {
  TSunDistanceSize actual_result = sun_distance_and_angular_size(
      lct_hours, lct_minutes, lct_seconds, local_day, local_month, local_year,
      is_daylight_saving, zone_correction);

  printf("[Sun Distance and Angular Size]\n");
  printf("\tExpected:\n");
  printf("\t\tAngular Size is %0.0fd %0.0fm %0.0fs\n",
         expected_result.sun_ang_size_deg, expected_result.sun_ang_size_min,
         expected_result.sun_ang_size_sec);
  printf("\t\tDistance is %0.0f km\n", expected_result.sun_dist_km);
  printf("\tActual:\n");
  printf("\t\tAngular Size is %0.0fd %0.0fm %0.0fs\n",
         actual_result.sun_ang_size_deg, actual_result.sun_ang_size_min,
         actual_result.sun_ang_size_sec);
  printf("\t\tDistance is %0.0f km\n", actual_result.sun_dist_km);

  assert(actual_result.sun_ang_size_deg == expected_result.sun_ang_size_deg);
  assert(actual_result.sun_ang_size_min == expected_result.sun_ang_size_min);
  assert(actual_result.sun_ang_size_sec == expected_result.sun_ang_size_sec);
  assert(actual_result.sun_dist_km == expected_result.sun_dist_km);
}

void test_sunrise_and_sunset(double local_day, int local_month, int local_year,
                             bool is_daylight_saving, int zone_correction,
                             double geographical_long_deg,
                             double geographical_lat_deg,
                             TSunriseSunsetInfo expected_result) {
  TSunriseSunsetInfo actual_result = sunrise_and_sunset(
      local_day, local_month, local_year, is_daylight_saving, zone_correction,
      geographical_long_deg, geographical_lat_deg);

  printf("[Sunrise and Sunset]\n");
  printf("\tExpected:\n");
  printf("\t\tAzimuth of sunrise/sunset: %0.2fd/%0.2fd\n",
         expected_result.azimuth_of_sunrise_deg,
         expected_result.azimuth_of_sunset_deg);
  printf("\t\tLocal sunrise: %0.0fh %0.0fm\n",
         expected_result.local_sunrise_hour,
         expected_result.local_sunrise_minute);
  printf("\t\tLocal sunset: %0.0fh %0.0fm\n", expected_result.local_sunset_hour,
         expected_result.local_sunset_minute);
  printf("\t\tStatus: %d\n", expected_result.status);
  printf("\tActual:\n");
  printf("\t\tAzimuth of sunrise/sunset: %0.2fd/%0.2fd\n",
         actual_result.azimuth_of_sunrise_deg,
         actual_result.azimuth_of_sunset_deg);
  printf("\t\tLocal sunrise: %0.0fh %0.0fm\n", actual_result.local_sunrise_hour,
         actual_result.local_sunrise_minute);
  printf("\t\tLocal sunset: %0.0fh %0.0fm\n", actual_result.local_sunset_hour,
         actual_result.local_sunset_minute);
  printf("\t\tStatus: %d\n", actual_result.status);

  assert(actual_result.azimuth_of_sunrise_deg ==
         expected_result.azimuth_of_sunrise_deg);
  assert(actual_result.azimuth_of_sunset_deg ==
         expected_result.azimuth_of_sunset_deg);
  assert(actual_result.local_sunrise_hour ==
         expected_result.local_sunrise_hour);
  assert(actual_result.local_sunrise_minute ==
         expected_result.local_sunrise_minute);
  assert(actual_result.local_sunset_hour == expected_result.local_sunset_hour);
  assert(actual_result.local_sunset_minute ==
         expected_result.local_sunset_minute);
  assert(actual_result.status == expected_result.status);
}

void test_morning_and_evening_twilight(double local_day, int local_month,
                                       int local_year, bool is_daylight_saving,
                                       int zone_correction,
                                       double geographical_long_deg,
                                       double geographical_lat_deg,
                                       enum TwilightType twilight_type,
                                       TTwilightInfo expected_result) {

  TTwilightInfo actual_result = morning_and_evening_twilight(
      local_day, local_month, local_year, is_daylight_saving, zone_correction,
      geographical_long_deg, geographical_lat_deg, twilight_type);

  printf("[Morning and Evening Twilight]\n");
  printf("\tExpected:\n");
  printf("\t\tAM twilight begins: %0.0fh %0.0fm\n",
         expected_result.am_twilight_begins_hour,
         expected_result.am_twilight_begins_min);
  printf("\t\tPM twilight ends: %0.0fh %0.0fm\n",
         expected_result.pm_twilight_ends_hour,
         expected_result.pm_twilight_ends_min);
  printf("\t\tStatus: %d\n", expected_result.status);
  printf("\tActual:\n");
  printf("\t\tAM twilight begins: %0.0fh %0.0fm\n",
         actual_result.am_twilight_begins_hour,
         actual_result.am_twilight_begins_min);
  printf("\t\tPM twilight ends: %0.0fh %0.0fm\n",
         actual_result.pm_twilight_ends_hour,
         actual_result.pm_twilight_ends_min);
  printf("\t\tStatus: %d\n", actual_result.status);

  assert(actual_result.am_twilight_begins_hour ==
         expected_result.am_twilight_begins_hour);
  assert(actual_result.am_twilight_begins_min ==
         expected_result.am_twilight_begins_min);
  assert(actual_result.pm_twilight_ends_hour ==
         expected_result.pm_twilight_ends_hour);
  assert(actual_result.pm_twilight_ends_min ==
         expected_result.pm_twilight_ends_min);
  assert(actual_result.status == expected_result.status);
}