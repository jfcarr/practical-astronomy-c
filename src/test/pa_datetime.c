#include "pa_datetime.h"
#include "../lib/pa_datetime.h"
#include "../lib/pa_util.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>

void test_date_of_easter(int input_year, int expected_month, int expected_day,
                         int expected_year) {
  TFullDate date_of_easter;

  date_of_easter = get_date_of_easter(input_year);

  printf("Date of Easter for %d: expected %d/%d/%d, got %d/%d/%d\n", input_year,
         expected_month, expected_day, expected_year, date_of_easter.month,
         date_of_easter.day, date_of_easter.year);

  assert(date_of_easter.month == expected_month);
  assert(date_of_easter.day == expected_day);
  assert(date_of_easter.year == expected_year);
}

void test_civil_date_to_day_number(int month, int day, int year,
                                   int expected_day_number) {
  int day_number = civil_date_to_day_number(month, day, year);

  printf("Day number for %d/%d/%d: expected %d, got %d\n", month, day, year,
         expected_day_number, day_number);

  assert(day_number == expected_day_number);
}

void test_civil_time_to_decimal_hours(double hours, double minutes,
                                      double seconds,
                                      double expected_decimal_hours) {
  double decimal_hours = civil_time_to_decimal_hours(hours, minutes, seconds);

  printf(
      "Decimal hours for civil time of %d:%d:%d: expected %0.8f, got %0.8f\n",
      (int)hours, (int)minutes, (int)seconds, expected_decimal_hours,
      decimal_hours);

  assert(dround(decimal_hours, 8) == expected_decimal_hours);
}

void test_decimal_hours_to_civil_time(double decimal_hours,
                                      TFullTime expected_civil_time) {
  TFullTime actual_civil_time = decimal_hours_to_civil_time(decimal_hours);

  assert(actual_civil_time.hours = expected_civil_time.hours);
  assert(actual_civil_time.minutes = expected_civil_time.minutes);
  assert(actual_civil_time.seconds = expected_civil_time.seconds);

  printf("Civil time for decimal hours of %0.8f: expected %d:%d:%d, got "
         "%d:%d:%d\n",
         decimal_hours, expected_civil_time.hours, expected_civil_time.minutes,
         (int)expected_civil_time.seconds, actual_civil_time.hours,
         actual_civil_time.minutes, (int)actual_civil_time.seconds);
}