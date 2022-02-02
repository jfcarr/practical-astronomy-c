#include <math.h>
#include <stdio.h>

#ifndef _pa_lib_datetime
#define _pa_lib_datetime
typedef struct pa_full_date {
  int month;
  int day;
  int year;
} TFullDate;

typedef struct pa_full_time {
  int hours;
  int minutes;
  double seconds;
} TFullTime;

TFullDate get_date_of_easter(int input_year);

int civil_date_to_day_number(int month, int day, int year);

double civil_time_to_decimal_hours(double hours, double minutes,
                                   double seconds);

TFullTime decimal_hours_to_civil_time(double decimal_hours);
#endif
