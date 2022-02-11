#include "pa_coordinates.h"
#include "../lib/pa_coordinates.h"
#include "../lib/pa_util.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>

void test_angle_to_decimal_degrees(double degrees, double minutes,
                                   double seconds, double expected_result) {
  double actual_result =
      dround(angle_to_decimal_degrees(degrees, minutes, seconds), 6);

  assert(actual_result == expected_result);

  printf("Decimal Degrees for Angle of %d degrees, %d minutes %d "
         "seconds:\n\tExpected: %f\n\tGot:      %f\n",
         (int)degrees, (int)minutes, (int)seconds, expected_result,
         actual_result);
}

void test_decimal_degrees_to_angle(double decimal_degrees,
                                   TAngle expected_result) {
  TAngle actual_result = decimal_degrees_to_angle(decimal_degrees);

  assert(actual_result.degrees = expected_result.degrees);
  assert(actual_result.minutes = expected_result.minutes);
  assert(actual_result.seconds == expected_result.seconds);

  printf("Angle for Decimal Degrees of %0.6f:\n\tExpected: %dd %dm %ds\n\tGot: "
         "     %dd %dm %ds\n",
         decimal_degrees, (int)expected_result.degrees,
         (int)expected_result.minutes, (int)expected_result.seconds,
         (int)actual_result.degrees, (int)actual_result.minutes,
         (int)actual_result.seconds);
}