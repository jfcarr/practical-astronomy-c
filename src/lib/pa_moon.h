#include "pa_types.h"
#include <stdbool.h>

#ifndef _pa_lib_moon
#define _pa_lib_moon
TMoonApproximatePosition
approximate_position_of_moon(double lct_hour, double lct_min, double lct_sec,
                             bool is_daylight_saving, int zone_correction_hours,
                             double local_date_day, int local_date_month,
                             int local_date_year);
#endif