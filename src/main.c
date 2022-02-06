#include "lib/pa_datetime.h"
#include "test/pa_datetime.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

void test_datetime() {
  test_date_of_easter(1914, (TFullDate){4, 12, 1914});
  test_date_of_easter(1950, (TFullDate){4, 9, 1950});
  test_date_of_easter(1980, (TFullDate){4, 6, 1980});
  test_date_of_easter(2003, (TFullDate){4, 20, 2003});

  test_civil_date_to_day_number(1, 1, 2000, 1);
  test_civil_date_to_day_number(3, 1, 2000, 61);
  test_civil_date_to_day_number(6, 1, 2003, 152);
  test_civil_date_to_day_number(11, 27, 2009, 331);

  test_civil_time_to_decimal_hours(18, 31, 27.0, 18.52416667);

  test_decimal_hours_to_civil_time(18.52416667, (TFullTime){18, 31, 27});

  test_local_civil_time_to_universal_time(
      3, 37, 0, true, 4, 1, 7, 2013, (TFullDateTime){6, 30, 2013, 22, 37, 0});

  test_universal_time_to_local_civil_time(
      22, 37, 0, true, 4, 30, 6, 2013, (TFullDateTime){7, 1, 2013, 3, 37, 0});

  test_universal_time_to_greenwich_sidereal_time(14, 36, 51.67, 22, 4, 1980,
                                                 (TFullTime){4, 40, 5.23});

  test_greenwich_sidereal_time_to_universal_time(
      4, 40, 5.23, 22, 4, 1980,
      (TFullTimeWarning){14, 36, 51.67, WarningFlag_OK});
}

int main() {
  test_datetime();

  return (0);
}
