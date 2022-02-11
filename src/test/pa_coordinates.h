#include "../lib/pa_coordinates.h"
#include <math.h>
#include <stdio.h>

#ifndef _pa_test_coordinates
#define _pa_test_coordinates

void test_angle_to_decimal_degrees(double degrees, double minutes,
                                   double seconds, double expected_result);

void test_decimal_degrees_to_angle(double decimal_degrees,
                                   TAngle expected_result);
#endif