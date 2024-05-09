#include "pa_types.h"
#include <stdbool.h>

#ifndef _pa_lib_sun
#define _pa_lib_sun

TSunPosition approximate_position_of_sun(double lct_hours, double lct_minutes,
                                         double lct_seconds, double local_day,
                                         int local_month, int local_year,
                                         bool is_daylight_saving,
                                         int zone_correction);

TSunPosition precise_position_of_sun(double lct_hours, double lct_minutes,
                                     double lct_seconds, double local_day,
                                     int local_month, int local_year,
                                     bool is_daylight_saving,
                                     int zone_correction);

TSunDistanceSize
sun_distance_and_angular_size(double lct_hours, double lct_minutes,
                              double lct_seconds, double local_day,
                              int local_month, int local_year,
                              bool is_daylight_saving, int zone_correction);

TSunriseSunsetInfo sunrise_and_sunset(double local_day, int local_month,
                                      int local_year, bool is_daylight_saving,
                                      int zone_correction,
                                      double geographical_long_deg,
                                      double geographical_lat_deg);

TTwilightInfo morning_and_evening_twilight(
    double local_day, int local_month, int local_year, bool is_daylight_saving,
    int zone_correction, double geographical_long_deg,
    double geographical_lat_deg, enum TwilightType twilight_type);

TEquationOfTime equation_of_time(double gw_date_day, int gw_date_month,
                                 int gw_date_year);

double solar_elongation(double ra_hour, double ra_min, double ra_sec,
                        double dec_deg, double dec_min, double dec_sec,
                        double gw_date_day, int gw_date_month,
                        int gw_date_year);
#endif