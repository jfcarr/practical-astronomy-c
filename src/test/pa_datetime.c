#include "pa_datetime.h"
#include "../lib/pa_datetime.h"
#include "../lib/pa_util.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>

void test_date_of_easter(int input_year, TFullDate expected_date) {
  TFullDate date_of_easter;

  date_of_easter = get_date_of_easter(input_year);

  printf("Date of Easter for %d: expected %d/%d/%d, got %d/%d/%d\n", input_year,
         expected_date.month, expected_date.day, expected_date.year,
         date_of_easter.month, date_of_easter.day, date_of_easter.year);

  assert(date_of_easter.month == expected_date.month);
  assert(date_of_easter.day == expected_date.day);
  assert(date_of_easter.year == expected_date.year);
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

  assert(actual_civil_time.hours == expected_civil_time.hours);
  assert(actual_civil_time.minutes == expected_civil_time.minutes);
  assert(actual_civil_time.seconds == expected_civil_time.seconds);

  printf("Civil time for decimal hours of %0.8f: expected %d:%d:%d, got "
         "%d:%d:%d\n",
         decimal_hours, expected_civil_time.hours, expected_civil_time.minutes,
         (int)expected_civil_time.seconds, actual_civil_time.hours,
         actual_civil_time.minutes, (int)actual_civil_time.seconds);
}

void test_local_civil_time_to_universal_time(
    double lct_hours, double lct_minutes, double lct_seconds,
    bool is_daylight_savings, int zone_correction, double local_day,
    int local_month, int local_year, TFullDateTime expected_result) {
  TFullDateTime actual_result = local_civil_time_to_universal_time(
      lct_hours, lct_minutes, lct_seconds, is_daylight_savings, zone_correction,
      local_day, local_month, local_year);

  assert(actual_result.day == expected_result.day);
  assert(actual_result.hours == expected_result.hours);
  assert(actual_result.minutes == expected_result.minutes);
  assert(actual_result.month == expected_result.month);
  assert(actual_result.seconds == actual_result.seconds);
  assert(actual_result.year == actual_result.year);

  printf("Universal time for civil time of %d:%d:%d:\n\tExpected: %d/%d/%d "
         "%d:%d:%d\n\tGot:      %d/%d/%d %d:%d:%d\n",
         (int)lct_hours, (int)lct_minutes, (int)lct_seconds,
         expected_result.month, expected_result.day, expected_result.year,
         expected_result.hours, expected_result.minutes,
         (int)expected_result.seconds, actual_result.month, actual_result.day,
         actual_result.year, actual_result.hours, actual_result.minutes,
         (int)actual_result.seconds);
}

void test_universal_time_to_local_civil_time(double ut_hours, double ut_minutes,
                                             double ut_seconds,
                                             bool is_daylight_savings,
                                             int zone_correction, int gw_day,
                                             int gw_month, int gw_year,
                                             TFullDateTime expected_result) {
  TFullDateTime actual_result = universal_time_to_local_civil_time(
      ut_hours, ut_minutes, ut_seconds, is_daylight_savings, zone_correction,
      gw_day, gw_month, gw_year);

  assert(actual_result.day == expected_result.day);
  assert(actual_result.hours == expected_result.hours);
  assert(actual_result.minutes == expected_result.minutes);
  assert(actual_result.month == expected_result.month);
  assert(actual_result.seconds == actual_result.seconds);
  assert(actual_result.year == actual_result.year);

  printf("Civil time for universal time of %d:%d:%d:\n\tExpected: %d/%d/%d "
         "%d:%d:%d\n\tGot:      %d/%d/%d %d:%d:%d\n",
         (int)ut_hours, (int)ut_minutes, (int)ut_seconds, expected_result.month,
         expected_result.day, expected_result.year, expected_result.hours,
         expected_result.minutes, (int)expected_result.seconds,
         actual_result.month, actual_result.day, actual_result.year,
         actual_result.hours, actual_result.minutes,
         (int)actual_result.seconds);
}

void test_universal_time_to_greenwich_sidereal_time(
    double ut_hours, double ut_minutes, double ut_seconds, double gw_day,
    int gw_month, int gw_year, TFullTime expected_result) {
  TFullTime actual_result = universal_time_to_greenwich_sidereal_time(
      ut_hours, ut_minutes, ut_seconds, gw_day, gw_month, gw_year);

  assert(actual_result.hours == expected_result.hours);
  assert(actual_result.minutes == expected_result.minutes);
  assert(actual_result.seconds == expected_result.seconds);

  printf("Greenwich Sidereal Time for Universal Time of %d/%d/%d "
         "%d:%d:%0.2f:\n\tExpected: %d:%d:%0.2f\n\tGot:      %d:%d:%0.2f\n",
         gw_month, (int)gw_day, gw_year, (int)ut_hours, (int)ut_minutes,
         ut_seconds, expected_result.hours, expected_result.minutes,
         expected_result.seconds, actual_result.hours, actual_result.minutes,
         actual_result.seconds);
}

void test_greenwich_sidereal_time_to_universal_time(
    double gst_hours, double gst_minutes, double gst_seconds, double gw_day,
    int gw_month, int gw_year, TFullTimeWarning expected_result) {
  TFullTimeWarning actual_result = greenwich_sidereal_time_to_universal_time(
      gst_hours, gst_minutes, gst_seconds, gw_day, gw_month, gw_year);

  assert(actual_result.hours == expected_result.hours);
  assert(actual_result.minutes == expected_result.minutes);
  assert(actual_result.seconds == expected_result.seconds);
  assert(actual_result.warning_flag == expected_result.warning_flag);

  printf("Universal Time for Greenwich Sidereal Time of %d/%d/%d "
         "%d:%d:%0.2f:\n\tExpected: %d:%d:%0.2f\n\tGot:      %d:%d:%0.2f\n",
         gw_month, (int)gw_day, gw_year, (int)gst_hours, (int)gst_minutes,
         gst_seconds, expected_result.hours, expected_result.minutes,
         expected_result.seconds, actual_result.hours, actual_result.minutes,
         actual_result.seconds);
}

void test_greenwich_sidereal_time_to_local_sidereal_time(
    double gst_hours, double gst_minutes, double gst_seconds,
    double geographical_longitude, TFullTime expected_result) {
  TFullTime actual_result = greenwich_sidereal_time_to_local_sidereal_time(
      gst_hours, gst_minutes, gst_seconds, geographical_longitude);

  assert(actual_result.hours == expected_result.hours);
  assert(actual_result.minutes == expected_result.minutes);
  assert(actual_result.seconds == expected_result.seconds);

  printf("Local Sidereal Time for Greenwich Sidereal Time of "
         "%d:%d:%0.2f:\n\tExpected: %d:%d:%0.2f\n\tGot:      %d:%d:%0.2f\n",
         (int)gst_hours, (int)gst_minutes, gst_seconds, expected_result.hours,
         expected_result.minutes, expected_result.seconds, actual_result.hours,
         actual_result.minutes, actual_result.seconds);
}

void test_local_sidereal_time_to_greenwich_sidereal_time(
    double lst_hours, double lst_minutes, double lst_seconds,
    double geographical_longitude, TFullTime expected_result) {
  TFullTime actual_result = local_sidereal_time_to_greenwich_sidereal_time(
      lst_hours, lst_minutes, lst_seconds, geographical_longitude);

  assert(actual_result.hours == expected_result.hours);
  assert(actual_result.minutes == expected_result.minutes);
  assert(actual_result.seconds == expected_result.seconds);

  printf("Greenwich Sidereal Time for Local Sidereal Time of "
         "%d:%d:%0.2f:\n\tExpected: %d:%d:%0.2f\n\tGot:      %d:%d:%0.2f\n",
         (int)lst_hours, (int)lst_minutes, lst_seconds, expected_result.hours,
         expected_result.minutes, expected_result.seconds, actual_result.hours,
         actual_result.minutes, actual_result.seconds);
}