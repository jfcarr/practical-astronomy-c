#include <math.h>
#include <stdio.h>

#ifndef _pa_lib_util
#define _pa_lib_util
typedef enum { F, T } boolean;

boolean is_leap_year(int input_year);
double dround(double input, int places);
#endif
