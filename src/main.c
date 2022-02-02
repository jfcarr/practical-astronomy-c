#include "lib/pa_datetime.h"
#include "test/pa_datetime.h"
#include <math.h>
#include <stdio.h>

void test_datetime() {
  test_date_of_easter(1914, (TFullDate){4, 12, 1914});
  test_date_of_easter(1950, (TFullDate){4, 9, 1950});
  test_date_of_easter(1980, (TFullDate){4, 6, 1980});
  test_date_of_easter(2003, (TFullDate){4, 20, 2003});

  test_civil_date_to_day_number((TFullDate){1, 1, 2000}, 1);
  test_civil_date_to_day_number((TFullDate){3, 1, 2000}, 61);
  test_civil_date_to_day_number((TFullDate){6, 1, 2003}, 152);
  test_civil_date_to_day_number((TFullDate){11, 27, 2009}, 331);

  test_civil_time_to_decimal_hours((TFullTime){18, 31, 27.0}, 18.52416667);

  test_decimal_hours_to_civil_time(18.52416667, (TFullTime){18, 31, 27});
}

int main() {
  test_datetime();

  return (0);
}
