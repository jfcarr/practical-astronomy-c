#include "pa_datetime.h"
#include "pa_macros.h"
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
int civil_date_to_day_number(TFullDate input_date) {
  if (input_date.month <= 2) {
    input_date.month = input_date.month - 1;
    input_date.month = (is_leap_year(input_date.year) == T)
                           ? input_date.month * 62
                           : input_date.month * 63;
    input_date.month = (int)floor((double)input_date.month / 2.0);
  } else {
    input_date.month = (int)floor(((double)input_date.month + 1.0) * 30.6);
    input_date.month = (is_leap_year(input_date.year) == T)
                           ? input_date.month - 62
                           : input_date.month - 63;
  }

  return input_date.month + input_date.day;
}

/**
 * Convert civil time (HH:MM:SS) to decimal hours (HH.########)
 */
double civil_time_to_decimal_hours(TFullTime civil_time) {
  return hms_dh(civil_time);
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