#include "pa_types.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#ifndef _pa_lib_datetime
#define _pa_lib_datetime
TFullDate get_date_of_easter(int input_year);

int civil_date_to_day_number(int month, int day, int year);

double civil_time_to_decimal_hours(double hours, double minutes,
                                   double seconds);

TFullTime decimal_hours_to_civil_time(double decimal_hours);

TFullDateTime
local_civil_time_to_universal_time(double lct_hours, double lct_minutes,
                                   double lct_seconds, bool is_daylight_savings,
                                   int zone_correction, double local_day,
                                   int local_month, int local_year);

TFullDateTime
universal_time_to_local_civil_time(double ut_hours, double ut_minutes,
                                   double ut_seconds, bool is_daylight_savings,
                                   int zone_correction, int gw_day,
                                   int gw_month, int gw_year);

TFullTime universal_time_to_greenwich_sidereal_time(double ut_hours,
                                                    double ut_minutes,
                                                    double ut_seconds,
                                                    double gw_day, int gw_month,
                                                    int gw_year);

TFullTimeWarning
greenwich_sidereal_time_to_universal_time(double gst_hours, double gst_minutes,
                                          double gst_seconds, double gw_day,
                                          int gw_month, int gw_year);
#endif
