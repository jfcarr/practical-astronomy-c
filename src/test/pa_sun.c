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