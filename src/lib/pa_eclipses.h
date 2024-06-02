#include "pa_types.h"
#include <stdbool.h>

#ifndef _pa_lib_eclipses
#define _pa_lib_eclipses
TLunarEclipseOccurrence lunar_eclipse_occurrence(double local_date_day,
                                                 int local_date_month,
                                                 int local_date_year,
                                                 bool is_daylight_saving,
                                                 int zone_correction_hours);

TLunarEclipseCircumstances
lunar_eclipse_circumstances(double local_date_day, int local_date_month,
                            int local_date_year, bool is_daylight_saving,
                            int zone_correction_hours);

TSolarEclipseOccurrence solar_eclipse_occurrence(double local_date_day,
                                                 int local_date_month,
                                                 int local_date_year,
                                                 bool is_daylight_saving,
                                                 int zone_correction_hours);

TSolarEclipseCircumstances solar_eclipse_circumstances(
    double local_date_day, int local_date_month, int local_date_year,
    bool is_daylight_saving, int zone_correction_hours,
    double geog_longitude_deg, double geog_latitude_deg);
#endif