#include "../lib/pa_comet.h"
#include <stdbool.h>

#ifndef _pa_test_comet
#define _pa_test_comet
void test_position_of_elliptical_comet(
    double lct_hour, double lct_min, double lct_sec, bool is_daylight_saving,
    int zone_correction_hours, double local_date_day, int local_date_month,
    int local_date_year, char *comet_name, TCometPosition expected_result);

void test_position_of_parabolic_comet(
    double lct_hour, double lct_min, double lct_sec, bool is_daylight_saving,
    int zone_correction_hours, double local_date_day, int local_date_month,
    int local_date_year, char *comet_name, TCometPosition expected_result);
#endif