#include "pa_types.h"
#include <stdbool.h>

#ifndef _pa_lib_binary
#define _pa_lib_binary
TBinaryStarOrbitalData binary_star_orbit(double greenwich_date_day,
                                         int greenwich_date_month,
                                         int greenwich_date_year,
                                         char *binary_name);
#endif