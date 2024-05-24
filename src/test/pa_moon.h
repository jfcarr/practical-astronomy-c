#include "../lib/pa_moon.h"
#include <stdbool.h>

#ifndef _pa_test_moon
#define _pa_test_moon
void test_approximate_position_of_moon(
    double lct_hour, double lct_min, double lct_sec, bool is_daylight_saving,
    int zone_correction_hours, double local_date_day, int local_date_month,
    int local_date_year, TMoonApproximatePosition expected_result);

void test_precise_position_of_moon(double lct_hour, double lct_min,
                                   double lct_sec, bool is_daylight_saving,
                                   int zone_correction_hours,
                                   double local_date_day, int local_date_month,
                                   int local_date_year,
                                   TMoonPrecisePosition expected_result);

void test_moon_phase(double lct_hour, double lct_min, double lct_sec,
                     bool is_daylight_saving, int zone_correction_hours,
                     double local_date_day, int local_date_month,
                     int local_date_year, enum AccuracyLevel accuracy_level,
                     TMoonPhase expected_result);
#endif