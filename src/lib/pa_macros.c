#include "pa_macros.h"
#include "pa_datetime.h"
#include "pa_util.h"
#include <math.h>
#include <stdlib.h>

/**
 * Convert a Civil Time (hours,minutes,seconds) to Decimal Hours.  Original
 * macro name: HMSDH
 *
 * @param[in]  hours  Hour part of time.
 * @param[in]  minutes  Minutes part of time.
 * @param[in]  seconds  Seconds part of time.
 *
 * \return Decimal representation of time.
 */
double hms_dh(double hours, double minutes, double seconds) {
  double f_hours = hours;
  double f_minutes = minutes;
  double f_seconds = seconds;

  double a = fabs(f_seconds) / 60.0;
  double b = (fabs(f_minutes) + a) / 60.0;
  double c = fabs(f_hours) + b;

  return (f_hours < 0 || f_minutes < 0 || f_seconds < 0) ? -c : c;
}

/**
 * Extract hour part of decimal hours.
 */
int decimal_hours_hour(double decimal_hours) {
  double a = fabs(decimal_hours);
  double b = a * 3600;
  double c = dround(b - 60 * floor(b / 60), 2);
  double e = (c == 60) ? b + 60 : b;

  return (decimal_hours < 0) ? (int)-(floor(e / 3600)) : (int)floor(e / 3600);
}

/**
 * Extract minutes part of decimal hours.
 */
int decimal_hours_minute(double decimal_hours) {
  double a = fabs(decimal_hours);
  double b = a * 3600;
  double c = dround(b - 60 * floor(b / 60), 2);
  double e = (c == 60) ? b + 60 : b;

  return (int)floor(e / 60) % 60;
}

/**
 * Extract seconds part of decimal hours.
 */
double decimal_hours_second(double decimal_hours) {
  double a = fabs(decimal_hours);
  double b = a * 3600;
  double c = dround(b - 60 * floor(b / 60), 2);
  double d = (c == 60) ? 0 : c;

  return d;
}

/**
 * Convert a Greenwich Date/Civil Date (day,month,year) to Julian Date
 *
 * Original macro name: CDJD
 */
double civil_date_to_julian_date(double day, double month, double year) {
  double f_day = (double)day;
  double f_month = (double)month;
  double f_year = (double)year;

  double y = (f_month < 3) ? f_year - 1 : f_year;
  double m = (f_month < 3) ? f_month + 12 : f_month;

  double b;

  if (f_year > 1582) {
    double a = floor(y / 100);
    b = 2 - a + floor(a / 4);
  } else {
    if (f_year == 1582 && f_month > 10) {
      double a = floor(y / 100);
      b = 2 - a + floor(a / 4);
    } else {
      if (f_year == 1582 && f_month == 10 && f_day >= 15) {
        double a = floor(y / 100);
        b = 2 - a + floor(a / 4);
      } else
        b = 0;
    }
  }

  double c = (y < 0) ? floor(((365.25 * y) - 0.75)) : floor(365.25 * y);
  double d = floor(30.6001 * (m + 1.0));

  return b + c + d + f_day + 1720994.5;
}

/**
 * Returns the day part of a Julian Date
 *
 * Original macro name: JDCDay
 */
double julian_date_day(double julian_date) {
  double i = floor(julian_date + 0.5);
  double f = julian_date + 0.5 - i;
  double a = floor((i - 1867216.25) / 36524.25);
  double b = (i > 2299160) ? i + 1 + a - floor(a / 4) : i;
  double c = b + 1524;
  double d = floor((c - 122.1) / 365.25);
  double e = floor(365.25 * d);
  double g = floor((c - e) / 30.6001);

  return c - e + f - floor(30.6001 * g);
}

/**
 * Returns the month part of a Julian Date
 *
 * Original macro name: JDCMonth
 */
int julian_date_month(double julian_date) {
  double i = floor(julian_date + 0.5);
  double a = floor((i - 1867216.25) / 36524.25);
  double b = (i > 2299160) ? i + 1 + a - floor(a / 4) : i;
  double c = b + 1524;
  double d = floor((c - 122.1) / 365.25);
  double e = floor(365.25 * d);
  double g = floor((c - e) / 30.6001);

  double returnValue = (g < 13.5) ? g - 1 : g - 13;

  return (int)returnValue;
}

/**
 * Returns the year part of a Julian Date
 *
 * Original macro name: JDCYear
 */
int julian_date_year(double julian_date) {
  double i = floor(julian_date + 0.5);
  double a = floor((i - 1867216.25) / 36524.25);
  double b = (i > 2299160) ? i + 1.0 + a - floor(a / 4.0) : i;
  double c = b + 1524;
  double d = floor((c - 122.1) / 365.25);
  double e = floor(365.25 * d);
  double g = floor((c - e) / 30.6001);
  double h = (g < 13.5) ? g - 1 : g - 13;

  double returnValue = (h > 2.5) ? d - 4716 : d - 4715;

  return (int)returnValue;
}