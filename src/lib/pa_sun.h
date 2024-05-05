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
#endif