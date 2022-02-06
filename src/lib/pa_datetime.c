#include "pa_datetime.h"
#include "pa_macros.h"
#include "pa_types.h"
#include "pa_util.h"
#include <math.h>
#include <stdio.h>

/**
 * Determine the date of Easter for a given year.
 */
TFullDate get_date_of_easter(int input_year) {
  double year = (double)input_year;

  double a = (int)year % 19;
  double b = floor(year / 100.0);
  double c = (int)year % 100;
  double d = floor(b / 4.0);
  double e = (int)b % 4;
  double f = floor((b + 8.0) / 25.0);
  double g = floor((b - f + 1.0) / 3.0);
  double h = (int)((19.0 * a) + b - d - g + 15.0) % 30;
  double i = floor(c / 4.0);
  double k = (int)c % 4;
  double l = (int)(32.0 + 2.0 * (e + i) - h - k) % 7;
  double m = floor((a + (11.0 * h) + (22.0 * l)) / 451.0);
  double n = floor((h + l - (7.0 * m) + 114.0) / 31.0);
  double p = (int)(h + l - (7.0 * m) + 114.0) % 31;

  double day = p + 1.0;
  double month = n;

  TFullDate return_value = {(int)month, (int)day, (int)year};

  return return_value;
}

/**
 * Convert a civil date (month, day, and year) to a day number (the number of
 * days from the beginning of the year upon which the civil date falls)
 */
int civil_date_to_day_number(int month, int day, int year) {
  if (month <= 2) {
    month = month - 1;
    month = (is_leap_year(year)) ? month * 62 : month * 63;
    month = (int)floor((double)month / 2.0);
  } else {
    month = (int)floor(((double)month + 1.0) * 30.6);
    month = (is_leap_year(year)) ? month - 62 : month - 63;
  }

  return month + day;
}

/**
 * Convert civil time (HH:MM:SS) to decimal hours (HH.########)
 */
double civil_time_to_decimal_hours(double hours, double minutes,
                                   double seconds) {
  return hms_dh(hours, minutes, seconds);
}

/**
 * Convert decimal hours (HH.########) to civil time (HH:MM:SS)
 */
TFullTime decimal_hours_to_civil_time(double decimal_hours) {
  int hours = decimal_hours_hour(decimal_hours);
  int minutes = decimal_hours_minute(decimal_hours);
  double seconds = decimal_hours_second(decimal_hours);

  TFullTime return_value = {hours, minutes, seconds};

  return return_value;
}

/**
 * Convert local civil time to universal time.
 */
TFullDateTime
local_civil_time_to_universal_time(double lct_hours, double lct_minutes,
                                   double lct_seconds, bool is_daylight_savings,
                                   int zone_correction, double local_day,
                                   int local_month, int local_year) {
  double lct = civil_time_to_decimal_hours(lct_hours, lct_minutes, lct_seconds);

  int daylight_savings_offset = (is_daylight_savings) ? 1 : 0;

  double ut_interim = lct - daylight_savings_offset - zone_correction;
  double g_day_interim = local_day + (ut_interim / 24);

  double jd = civil_date_to_julian_date(g_day_interim, local_month, local_year);

  double g_day = julian_date_day(jd);
  int g_month = julian_date_month(jd);
  int g_year = julian_date_year(jd);

  double ut = 24 * (g_day - floor(g_day));

  return (TFullDateTime){g_month,
                         (int)floor(g_day),
                         g_year,
                         decimal_hours_hour(ut),
                         decimal_hours_minute(ut),
                         (int)decimal_hours_second(ut)};
}

/**
 * Convert universal time to local civil time.
 */
TFullDateTime
universal_time_to_local_civil_time(double ut_hours, double ut_minutes,
                                   double ut_seconds, bool is_daylight_savings,
                                   int zone_correction, int gw_day,
                                   int gw_month, int gw_year) {
  int dst_value = (is_daylight_savings) ? 1 : 0;
  double ut = hms_dh(ut_hours, ut_minutes, ut_seconds);
  double zone_time = ut + zone_correction;
  double local_time = zone_time + dst_value;
  double local_jd_plus_local_time =
      civil_date_to_julian_date(gw_day, gw_month, gw_year) + (local_time / 24);
  double local_day = julian_date_day(local_jd_plus_local_time);
  double integer_day = floor(local_day);
  int local_month = julian_date_month(local_jd_plus_local_time);
  int local_year = julian_date_year(local_jd_plus_local_time);

  double lct = 24 * (local_day - integer_day);

  return (TFullDateTime){local_month,
                         (int)integer_day,
                         local_year,
                         decimal_hours_hour(lct),
                         decimal_hours_minute(lct),
                         decimal_hours_second(lct)};
}

/**
 * Convert Universal Time to Greenwich Sidereal Time
 */
TFullTime universal_time_to_greenwich_sidereal_time(double ut_hours,
                                                    double ut_minutes,
                                                    double ut_seconds,
                                                    double gw_day, int gw_month,
                                                    int gw_year) {
  double jd = civil_date_to_julian_date(gw_day, gw_month, gw_year);
  double s = jd - 2451545.0;
  double t = s / 36525.0;
  double t01 = 6.697374558 + (2400.051336 * t) + (0.000025862 * t * t);
  double t02 = t01 - (24.0 * floor(t01 / 24.0));
  double ut = hms_dh(ut_hours, ut_minutes, ut_seconds);
  double a = ut * 1.002737909;
  double gst1 = t02 + a;
  double gst2 = gst1 - (24.0 * floor(gst1 / 24.0));

  int gst_hours = decimal_hours_hour(gst2);
  int gst_minutes = decimal_hours_minute(gst2);
  double gst_seconds = decimal_hours_second(gst2);

  return (TFullTime){gst_hours, gst_minutes, gst_seconds};
}

/**
 * Convert Greenwich Sidereal Time to Universal Time
 */
TFullTimeWarning
greenwich_sidereal_time_to_universal_time(double gst_hours, double gst_minutes,
                                          double gst_seconds, double gw_day,
                                          int gw_month, int gw_year) {
  double jd = civil_date_to_julian_date(gw_day, gw_month, gw_year);
  double s = jd - 2451545;
  double t = s / 36525;
  double t01 = 6.697374558 + (2400.051336 * t) + (0.000025862 * t * t);
  double t02 = t01 - (24 * floor(t01 / 24));
  double gst_hours1 = hms_dh(gst_hours, gst_minutes, gst_seconds);

  double a = gst_hours1 - t02;
  double b = a - (24 * floor(a / 24));
  double ut = b * 0.9972695663;
  int ut_hours = decimal_hours_hour(ut);
  int ut_minutes = decimal_hours_minute(ut);
  double ut_seconds = decimal_hours_second(ut);

  enum WarningFlags warning_flag =
      (ut < 0.065574) ? WarningFlag_Warning : WarningFlag_OK;

  return (TFullTimeWarning){ut_hours, ut_minutes, ut_seconds, warning_flag};
}