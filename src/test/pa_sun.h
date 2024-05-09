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

void test_sunrise_and_sunset(double local_day, int local_month, int local_year,
                             bool is_daylight_saving, int zone_correction,
                             double geographical_long_deg,
                             double geographical_lat_deg,
                             TSunriseSunsetInfo expected_result);

void test_morning_and_evening_twilight(double local_day, int local_month,
                                       int local_year, bool is_daylight_saving,
                                       int zone_correction,
                                       double geographical_long_deg,
                                       double geographical_lat_deg,
                                       enum TwilightType twilight_type,
                                       TTwilightInfo expected_result);

void test_equation_of_time(double gw_date_day, int gw_date_month,
                           int gw_date_year, TEquationOfTime expected_result);

void test_solar_elongation(double ra_hour, double ra_min, double ra_sec,
                           double dec_deg, double dec_min, double dec_sec,
                           double gw_date_day, int gw_date_month,
                           int gw_date_year, double expected_result);
#endif