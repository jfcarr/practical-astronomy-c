#include "pa_comet.h"
#include "../lib/pa_comet.h"
#include "../lib/pa_types.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

void test_position_of_elliptical_comet(
    double lct_hour, double lct_min, double lct_sec, bool is_daylight_saving,
    int zone_correction_hours, double local_date_day, int local_date_month,
    int local_date_year, char *comet_name, TCometPosition expected_result) {
  TCometPosition actual_result = position_of_elliptical_comet(
      lct_hour, lct_min, lct_sec, is_daylight_saving, zone_correction_hours,
      local_date_day, local_date_month, local_date_year, comet_name);

  printf("[Position of Elliptical Comet]\n");
  printf("\tExpected:\n");
  printf("\t\tRight Ascension is %0.0f h %0.0f m\n",
         expected_result.comet_ra_hour, expected_result.comet_ra_min);
  printf("\t\tDeclination is %0.0f d %0.0f m\n", expected_result.comet_dec_deg,
         expected_result.comet_dec_min);
  printf("\t\tDistance From Earth is %0.2f au\n",
         expected_result.comet_dist_earth);
  printf("\tActual:\n");
  printf("\t\tRight Ascension is %0.0f h %0.0f m\n",
         actual_result.comet_ra_hour, actual_result.comet_ra_min);
  printf("\t\tDeclination is %0.0f d %0.0f m\n", actual_result.comet_dec_deg,
         actual_result.comet_dec_min);
  printf("\t\tDistance From Earth is %0.2f au\n",
         actual_result.comet_dist_earth);

  assert(actual_result.comet_dec_deg == expected_result.comet_dec_deg);
  assert(actual_result.comet_dec_min == expected_result.comet_dec_min);
  assert(actual_result.comet_dist_earth == expected_result.comet_dist_earth);
  assert(actual_result.comet_ra_hour == expected_result.comet_ra_hour);
  assert(actual_result.comet_ra_min == expected_result.comet_ra_min);
}
