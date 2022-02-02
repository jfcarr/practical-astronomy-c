#include "pa_datetime.h"

#ifndef _pa_lib_macros
#define _pa_lib_macros
double hms_dh(TFullTime civil_time);
int decimal_hours_hour(double decimal_hours);
int decimal_hours_minute(double decimal_hours);
double decimal_hours_second(double decimal_hours);
#endif