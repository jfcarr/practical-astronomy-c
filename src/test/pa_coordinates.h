#include "../lib/pa_coordinates.h"
#include <math.h>
#include <stdio.h>

#ifndef _pa_test_coordinates
#define _pa_test_coordinates

void test_angle_to_decimal_degrees(double degrees, double minutes,
                                   double seconds, double expected_result);

void test_decimal_degrees_to_angle(double decimal_degrees,
                                   TAngle expected_result);

void test_right_ascension_to_hour_angle(
    double ra_hours, double ra_minutes, double ra_seconds, double lct_hours,
    double lct_minutes, double lct_seconds, bool is_daylight_savings,
    int zone_correction, double local_day, int local_month, int local_year,
    double geographical_longitude, THourAngle expected_result);

void test_hour_angle_to_right_ascension(
    double hour_angle_hours, double hour_angle_minutes,
    double hour_angle_seconds, double lct_hours, double lct_minutes,
    double lct_seconds, bool is_daylight_savings, int zone_correction,
    double local_day, int local_month, int local_year,
    double geographical_longitude, TRightAscension expected_result);
#endif