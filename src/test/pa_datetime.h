#include "../lib/pa_datetime.h"
#include <math.h>
#include <stdio.h>

#ifndef _pa_test_datetime
#define _pa_test_datetime
void test_date_of_easter(int input_year, TFullDate expected_date);

void test_civil_date_to_day_number(TFullDate input_date,
                                   int expected_day_number);

void test_civil_time_to_decimal_hours(TFullTime civil_time,
                                      double expected_decimal_hours);

void test_decimal_hours_to_civil_time(double decimal_hours,
                                      TFullTime expected_civil_time);
#endif