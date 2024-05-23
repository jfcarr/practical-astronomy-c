#include "pa_moon.h"
#include "../lib/pa_moon.h"
#include "../lib/pa_types.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

void test_approximate_position_of_moon(
    double lct_hour, double lct_min, double lct_sec, bool is_daylight_saving,
    int zone_correction_hours, double local_date_day, int local_date_month,
    int local_date_year, TMoonApproximatePosition expected_result) {
  TMoonApproximatePosition actual_result = approximate_position_of_moon(
      lct_hour, lct_min, lct_sec, is_daylight_saving, zone_correction_hours,
      local_date_day, local_date_month, local_date_year);

  printf("[Approximate Position of Moon]\n");
  printf("\tExpected:\n");
  printf("\t\tRight Ascension is %0.0f h %0.0f m %0.2f s\n",
         expected_result.moon_ra_hour, expected_result.moon_ra_min,
         expected_result.moon_ra_sec);
  printf("\t\tDeclination is %0.0f d %0.0f m %0.2f s\n",
         expected_result.moon_dec_deg, expected_result.moon_dec_min,
         expected_result.moon_dec_sec);
  printf("\tActual:\n");
  printf("\t\tRight Ascension is %0.0f h %0.0f m %0.2f s\n",
         actual_result.moon_ra_hour, actual_result.moon_ra_min,
         actual_result.moon_ra_sec);
  printf("\t\tDeclination is %0.0f d %0.0f m %0.2f s\n",
         actual_result.moon_dec_deg, actual_result.moon_dec_min,
         actual_result.moon_dec_sec);

  assert(actual_result.moon_dec_deg == expected_result.moon_dec_deg);
  assert(actual_result.moon_dec_min == expected_result.moon_dec_min);
  assert(actual_result.moon_dec_sec == expected_result.moon_dec_sec);
  assert(actual_result.moon_ra_hour == expected_result.moon_ra_hour);
  assert(actual_result.moon_ra_min == expected_result.moon_ra_min);
  assert(actual_result.moon_ra_sec == expected_result.moon_ra_sec);
}

void test_precise_position_of_moon(double lct_hour, double lct_min,
                                   double lct_sec, bool is_daylight_saving,
                                   int zone_correction_hours,
                                   double local_date_day, int local_date_month,
                                   int local_date_year,
                                   TMoonPrecisePosition expected_result) {

  TMoonPrecisePosition actual_result = precise_position_of_moon(
      lct_hour, lct_min, lct_sec, is_daylight_saving, zone_correction_hours,
      local_date_day, local_date_month, local_date_year);

  printf("[Precise Position of Moon]\n");
  printf("\tExpected:\n");
  printf("\t\tRight Ascension is %0.0f h %0.0f m %0.2f s\n",
         expected_result.moon_ra_hour, expected_result.moon_ra_min,
         expected_result.moon_ra_sec);
  printf("\t\tDeclination is %0.0f d %0.0f m %0.2f s\n",
         expected_result.moon_dec_deg, expected_result.moon_dec_min,
         expected_result.moon_dec_sec);
  printf("\t\tEarth-to-Moon Distance is %0.0f km\n",
         expected_result.earth_moon_dist_km);
  printf("\t\tMoon Horizontal Parallax is %f d\n",
         expected_result.moon_hor_parallax_deg);
  printf("\tActual:\n");
  printf("\t\tRight Ascension is %0.0f h %0.0f m %0.2f s\n",
         actual_result.moon_ra_hour, actual_result.moon_ra_min,
         actual_result.moon_ra_sec);
  printf("\t\tDeclination is %0.0f d %0.0f m %0.2f s\n",
         actual_result.moon_dec_deg, actual_result.moon_dec_min,
         actual_result.moon_dec_sec);
  printf("\t\tEarth-to-Moon Distance is %0.0f km\n",
         actual_result.earth_moon_dist_km);
  printf("\t\tMoon Horizontal Parallax is %f d\n",
         actual_result.moon_hor_parallax_deg);

  assert(actual_result.earth_moon_dist_km ==
         expected_result.earth_moon_dist_km);
  assert(actual_result.moon_dec_deg == expected_result.moon_dec_deg);
  assert(actual_result.moon_dec_min == expected_result.moon_dec_min);
  assert(actual_result.moon_dec_sec == expected_result.moon_dec_sec);
  assert(actual_result.moon_hor_parallax_deg ==
         expected_result.moon_hor_parallax_deg);
  assert(actual_result.moon_ra_hour == expected_result.moon_ra_hour);
  assert(actual_result.moon_ra_min == expected_result.moon_ra_min);
  assert(actual_result.moon_ra_sec == expected_result.moon_ra_sec);
}