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

void test_visual_aspects_of_a_planet(double lct_hour, double lct_min,
                                     double lct_sec, bool is_daylight_saving,
                                     int zone_correction_hours,
                                     double local_date_day,
                                     int local_date_month, int local_date_year,
                                     char *planet_name,
                                     TPlanetVisualAspects expected_result) {
  TPlanetVisualAspects actual_result = visual_aspects_of_a_planet(
      lct_hour, lct_min, lct_sec, is_daylight_saving, zone_correction_hours,
      local_date_day, local_date_month, local_date_year, planet_name);

  printf("[Visual Aspects of a Planet]\n");
  printf("\tExpected:\n");
  printf("\t\tDistance is %f au\n", expected_result.distance_au);
  printf("\t\tAngular Diameter is %0.2f arcsec\n",
         expected_result.ang_dia_arcsec);
  printf("\t\tPhase is %0.2f\n", expected_result.phase);
  printf("\t\tLight Time is %0.0f h %0.0f m %0.2f s\n",
         expected_result.light_time_hour, expected_result.light_time_minutes,
         expected_result.light_time_seconds);
  printf("\t\tPosition Angle of the Bright Limb is %0.2f d\n",
         expected_result.pos_angle_bright_limb_deg);
  printf("\t\tApproximate Magnitude is %0.2f\n",
         expected_result.approximate_magnitude);
  printf("\tActual:\n");
  printf("\t\tDistance is %f au\n", actual_result.distance_au);
  printf("\t\tAngular Diameter is %0.2f arcsec\n",
         actual_result.ang_dia_arcsec);
  printf("\t\tPhase is %0.2f\n", actual_result.phase);
  printf("\t\tLight Time is %0.0f h %0.0f m %0.2f s\n",
         actual_result.light_time_hour, actual_result.light_time_minutes,
         actual_result.light_time_seconds);
  printf("\t\tPosition Angle of the Bright Limb is %0.2f d\n",
         actual_result.pos_angle_bright_limb_deg);
  printf("\t\tApproximate Magnitude is %0.2f\n",
         actual_result.approximate_magnitude);

  assert(actual_result.ang_dia_arcsec == expected_result.ang_dia_arcsec);
  assert(actual_result.approximate_magnitude ==
         expected_result.approximate_magnitude);
  assert(actual_result.distance_au == expected_result.distance_au);
  assert(actual_result.light_time_hour == expected_result.light_time_hour);
  assert(actual_result.light_time_minutes ==
         expected_result.light_time_minutes);
  assert(actual_result.light_time_seconds ==
         expected_result.light_time_seconds);
  assert(actual_result.phase == expected_result.phase);
  assert(actual_result.pos_angle_bright_limb_deg ==
         expected_result.pos_angle_bright_limb_deg);
}
