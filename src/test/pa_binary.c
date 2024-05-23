#include "pa_binary.h"
#include "../lib/pa_binary.h"
#include "../lib/pa_types.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

void test_binary_star_orbit(double greenwich_date_day, int greenwich_date_month,
                            int greenwich_date_year, char *binary_name,
                            TBinaryStarOrbitalData expected_result) {
  TBinaryStarOrbitalData actual_result =
      binary_star_orbit(greenwich_date_day, greenwich_date_month,
                        greenwich_date_year, binary_name);

  printf("[Binary Star Orbital Data]\n");
  printf("\tExpected:\n");
  printf("\t\tPosition Angle is %0.2f d\n", expected_result.position_angle_deg);
  printf("\t\tSeparation is %0.2f arcsec\n", expected_result.separation_arcsec);
  printf("\tActual:\n");
  printf("\t\tPosition Angle is %0.2f d\n", actual_result.position_angle_deg);
  printf("\t\tSeparation is %0.2f arcsec\n", actual_result.separation_arcsec);

  assert(actual_result.position_angle_deg ==
         expected_result.position_angle_deg);
  assert(actual_result.separation_arcsec == expected_result.separation_arcsec);
}
