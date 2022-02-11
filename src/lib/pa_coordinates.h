#include "pa_types.h"

#ifndef _pa_lib_coordinates
#define _pa_lib_coordinates

double angle_to_decimal_degrees(double degrees, double minutes, double seconds);

TAngle decimal_degrees_to_angle(double decimal_degrees);
#endif
