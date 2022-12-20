#include "lib/pa_datetime.h"
#include "test/pa_coordinates.h"
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

  test_greenwich_sidereal_time_to_local_sidereal_time(4, 40, 5.23, -64,
                                                      (TFullTime){0, 24, 5.23});

  test_local_sidereal_time_to_greenwich_sidereal_time(0, 24, 5.23, -64,
                                                      (TFullTime){4, 40, 5.23});
}

void test_coordinates() {
  test_angle_to_decimal_degrees(182, 31, 27, 182.524167);

  test_decimal_degrees_to_angle(182.524167, (TAngle){182, 31, 27});

  test_right_ascension_to_hour_angle(18, 32, 21, 14, 36, 51.67, false, -4, 22,
                                     4, 1980, -64, (THourAngle){9, 52, 23.66});

  test_hour_angle_to_right_ascension(9, 52, 23.66, 14, 36, 51.67, false, -4, 22,
                                     4, 1980, -64,
                                     (TRightAscension){18, 32, 21});

  test_equatorial_coordinates_to_horizon_coordinates(
      5, 51, 44, 23, 13, 10, 52,
      (THorizonCoordinates){283, 16, 15.7, 19, 20, 3.64});

  test_horizon_coordinates_to_equatorial_coordinates(
      283, 16, 15.7, 19, 20, 3.64, 52,
      (TEquatorialCoordinates){5, 51, 44, 23, 13, 10});

  test_mean_obliquity_of_the_ecliptic(6, 7, 2009, 23.43805531);

  test_ecliptic_coordinates_to_equatorial_coordinates(
      139, 41, 10, 4, 52, 31, 6, 7, 2009,
      (TEquatorialCoordinates2){9, 34, 53.4, 19, 32, 8.52});

  test_equatorial_coordinate_to_ecliptic_coordinate(
      9, 34, 53.4, 19, 32, 8.52, 6, 7, 2009,
      (TEclipticCoordinates){139, 41, 9.97, 4, 52, 30.99});

  test_equatorial_coordinate_to_galactic_coordinate(
      10, 21, 0, 10, 3, 11,
      (TGalacticCoordinates){232, 14, 52.38, 51, 7, 20.16});

  test_galactic_coordinates_to_equatorial_coordinates(
      232, 14, 52.38, 51, 7, 20.16,
      (TEquatorialCoordinates2){10, 21, 0, 10, 3, 11});

  test_angle_between_two_objects(5, 13, 31.7, -8, 13, 30, 6, 44, 13.4, -16, 41,
                                 11, AngleMeasurement_Hours,
                                 (TAngle){23, 40, 25.86});
}

int main() {
  test_datetime();
  test_coordinates();

  return (0);
}
