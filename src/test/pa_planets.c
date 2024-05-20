#include "pa_planets.h"
#include "../lib/pa_planets.h"
#include "../lib/pa_types.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

void test_approximate_position_of_planet(
    double lct_hour, double lct_min, double lct_sec, bool is_daylight_saving,
    int zone_correction_hours, double local_date_day, int local_date_month,
    int local_date_year, char *planet_name, TPlanetPosition expected_result) {
  TPlanetPosition actual_result = approximate_position_of_planet(
      lct_hour, lct_min, lct_sec, is_daylight_saving, zone_correction_hours,
      local_date_day, local_date_month, local_date_year, planet_name);

  printf("[Approximate Position of Planet]\n");
  printf("\tExpected:\n");
  printf("\t\tRA is %0.0fh %0.0fm %0.2fs\n", expected_result.planet_ra_hour,
         expected_result.planet_ra_min, expected_result.planet_ra_sec);
  printf("\t\tDeclination is %0.0fd %0.0fm %0.2fs\n",
         expected_result.planet_dec_deg, expected_result.planet_dec_min,
         expected_result.planet_dec_sec);
  printf("\tActual:\n");
  printf("\t\tRA is %0.0fh %0.0fm %0.2fs\n", actual_result.planet_ra_hour,
         actual_result.planet_ra_min, actual_result.planet_ra_sec);
  printf("\t\tDeclination is %0.0fd %0.0fm %0.2fs\n",
         actual_result.planet_dec_deg, actual_result.planet_dec_min,
         actual_result.planet_dec_sec);

  assert(actual_result.planet_dec_deg == expected_result.planet_dec_deg);
  assert(actual_result.planet_dec_min == expected_result.planet_dec_min);
  assert(actual_result.planet_dec_sec == actual_result.planet_dec_sec);
  assert(actual_result.planet_ra_hour == expected_result.planet_ra_hour);
  assert(actual_result.planet_ra_min == expected_result.planet_ra_min);
  assert(actual_result.planet_ra_sec == expected_result.planet_ra_sec);
}

void test_precise_position_of_planet(
    double lct_hour, double lct_min, double lct_sec, bool is_daylight_saving,
    int zone_correction_hours, double local_date_day, int local_date_month,
    int local_date_year, char *planet_name, TPlanetPosition expected_result) {
  TPlanetPosition actual_result = precise_position_of_planet(
      lct_hour, lct_min, lct_sec, is_daylight_saving, zone_correction_hours,
      local_date_day, local_date_month, local_date_year, planet_name);

  printf("[Precise Position of Planet]\n");
  printf("\tExpected:\n");
  printf("\t\tRA is %0.0fh %0.0fm %0.2fs\n", expected_result.planet_ra_hour,
         expected_result.planet_ra_min, expected_result.planet_ra_sec);
  printf("\t\tDeclination is %0.0fd %0.0fm %0.2fs\n",
         expected_result.planet_dec_deg, expected_result.planet_dec_min,
         expected_result.planet_dec_sec);
  printf("\tActual:\n");
  printf("\t\tRA is %0.0fh %0.0fm %0.2fs\n", actual_result.planet_ra_hour,
         actual_result.planet_ra_min, actual_result.planet_ra_sec);
  printf("\t\tDeclination is %0.0fd %0.0fm %0.2fs\n",
         actual_result.planet_dec_deg, actual_result.planet_dec_min,
         actual_result.planet_dec_sec);

  assert(actual_result.planet_dec_deg == expected_result.planet_dec_deg);
  assert(actual_result.planet_dec_min == expected_result.planet_dec_min);
  assert(actual_result.planet_dec_sec == actual_result.planet_dec_sec);
  assert(actual_result.planet_ra_hour == expected_result.planet_ra_hour);
  assert(actual_result.planet_ra_min == expected_result.planet_ra_min);
  assert(actual_result.planet_ra_sec == expected_result.planet_ra_sec);
}