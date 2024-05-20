#include "../lib/pa_planets.h"
#include <stdbool.h>

#ifndef _pa_test_planets
#define _pa_test_planets
void test_approximate_position_of_planet(
    double lct_hour, double lct_min, double lct_sec, bool is_daylight_saving,
    int zone_correction_hours, double local_date_day, int local_date_month,
    int local_date_year, char *planet_name, TPlanetPosition expected_result);

void test_precise_position_of_planet(
    double lct_hour, double lct_min, double lct_sec, bool is_daylight_saving,
    int zone_correction_hours, double local_date_day, int local_date_month,
    int local_date_year, char *planet_name, TPlanetPosition expected_result);
#endif