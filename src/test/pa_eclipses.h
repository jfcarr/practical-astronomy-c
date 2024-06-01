#include "../lib/pa_eclipses.h"
#include <math.h>
#include <stdio.h>

#ifndef _pa_test_eclipses
#define _pa_test_eclipses
void test_lunar_eclipse_occurrence(double local_date_day, int local_date_month,
                                   int local_date_year, bool is_daylight_saving,
                                   int zone_correction_hours,
                                   TLunarEclipseOccurrence expected_result);

void test_lunar_eclipse_circumstances(
    double local_date_day, int local_date_month, int local_date_year,
    bool is_daylight_saving, int zone_correction_hours,
    TLunarEclipseCircumstances expected_result);
#endif