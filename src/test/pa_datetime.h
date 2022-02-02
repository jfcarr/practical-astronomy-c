#include "../lib/pa_datetime.h"
#include <math.h>
#include <stdio.h>

void test_date_of_easter(int input_year, int expected_month, int expected_day,
                         int expected_year);

void test_civil_date_to_day_number(int month, int day, int year,
                                   int expected_day_number);

void test_civil_time_to_decimal_hours(double hours, double minutes,
                                      double seconds,
                                      double expected_decimal_hours);

void test_decimal_hours_to_civil_time(double decimal_hours,
                                      TFullTime expected_civil_time);