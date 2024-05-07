#include "../lib/pa_sun.h"
#include <stdbool.h>

#ifndef _pa_test_sun
#define _pa_test_sun
void test_approximate_position_of_sun(double lct_hours, double lct_minutes,
                                      double lct_seconds, double local_day,
                                      int local_month, int local_year,
                                      bool is_daylight_saving,
                                      int zone_correction,
                                      TSunPosition expected_result);

void test_precise_position_of_sun(double lct_hours, double lct_minutes,
                                  double lct_seconds, double local_day,
                                  int local_month, int local_year,
                                  bool is_daylight_saving, int zone_correction,
                                  TSunPosition expected_result);

void test_sun_distance_and_angular_size(double lct_hours, double lct_minutes,
                                        double lct_seconds, double local_day,
                                        int local_month, int local_year,
                                        bool is_daylight_saving,
                                        int zone_correction,
                                        TSunDistanceSize expected_result);

test_sunrise_and_sunset(double local_day, int local_month, int local_year,
                        bool is_daylight_saving, int zone_correction,
                        double geographical_long_deg,
                        double geographical_lat_deg,
                        TSunriseSunsetInfo expected_result);
#endif