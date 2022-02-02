#include "pa_macros.h"
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
