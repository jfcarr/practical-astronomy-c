#include "pa_util.h"

/**
 * Determine if the specified year is a leap year.
 */
boolean is_leap_year(int input_year) {
  double year = (double)input_year;

  if ((int)year % 4 == 0) {
    if ((int)year % 100 == 0) {
      return ((int)year % 400 == 0) ? T : F;
    } else {
      return T;
    }
  } else {
    return F;
  }
}

/**
 * Round the double value to specified number of decimal places.
 */
double dround(double input, int places) {
  boolean isNegative = (input < 0) ? T : F;

  long double multiplier = pow(10, places);

  if (isNegative) {
    input = fabs(input);
  };

  long double a = input * multiplier;
  a = (a >= 0) ? a + 0.5 : a - 0.5;

  double returnValue = floor(a) / multiplier;

  return (isNegative) ? -(returnValue) : returnValue;
}
