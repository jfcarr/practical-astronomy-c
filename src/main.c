#include "lib/pa_datetime.h"
#include "test/pa_coordinates.h"
#include "test/pa_datetime.h"
#include "test/pa_sun.h"
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
                                 11, AngleMeasurementType_HOURS,
                                 (TAngle){23, 40, 25.86});

  test_rising_and_setting(
      23, 39, 20, 21, 42, 0, 24, 8, 2010, 64, 30, 0.5667,
      (TRiseSet){RiseSetStatus_OK, 14, 16, 4, 10, 64.36, 295.64});

  test_correct_for_precession(
      9, 10, 43, 14, 23, 25, 0.923, 1, 1950, 1, 6, 1979,
      (TCorrectedPrecession){9, 12, 20.18, 14, 16, 9.12});

  test_nutation_in_ecliptic_longitude_and_obliquity(
      1, 9, 1988, (TNutation){.001525808, .0025671});

  test_correct_for_aberration(
      0, 0, 0, 8, 9, 1988, 352, 37, 10.1, -1, 32, 56.4,
      (TCorrectedEclipticCoordinates){352, 37, 30.45, -1, 32, 56.33});

  test_atmospheric_refraction(
      23, 14, 0, 40, 10, 0, CoordinateType_ACTUAL, 0.17, 51.2036110, 0, 0, 23,
      3, 1987, 1, 1, 24, 1012, 21.7,
      (TCorrectedRefraction){23, 13, 44.74, 40, 19, 45.76});

  test_corrections_for_geocentric_parallax(
      22, 35, 19, -7, 41, 13, CoordinateType_ACTUAL, 1.019167, -100, 50, 60, 0,
      -6, 26, 2, 1979, 10, 45, 0,
      (TCorrectedParallax){22, 36, 43.22, -8, 32, 17.4});

  test_heliographic_coordinates(220, 10.5, 1, 5, 1988,
                                (THeliographicCoordinates){142.59, -19.94});

  test_carrington_rotation_number(27, 1, 1975, 1624);

  test_selenographic_coordinates1(
      1, 5, 1988, (TSelenographicSubEarthCoordinates){-4.88, 4.04, 19.78});

  test_selenographic_coordinates2(
      1, 5, 1988, (TSelenographicSubSolarCoordinates){6.81, 83.19, 1.19});
}

void test_sun() {
  test_approximate_position_of_sun(0, 0, 0, 27, 7, 2003, false, 0,
                                   (TSunPosition){8, 23, 33.73, 19, 21, 14.33});

  test_precise_position_of_sun(0, 0, 0, 27, 7, 1988, false, 0,
                               (TSunPosition){8, 26, 3.83, 19, 12, 49.72});

  test_sun_distance_and_angular_size(
      0, 0, 0, 27, 7, 1988, false, 0,
      (TSunDistanceSize){151920130, 0, 31, 29.93});

  test_sunrise_and_sunset(
      10, 3, 1986, false, -5, -71.05, 42.37,
      (TSunriseSunsetInfo){6, 5, 17, 45, 94.83, 265.43, RiseSetStatus_OK});

  test_morning_and_evening_twilight(
      7, 9, 1979, false, 0, 0, 52, TwilightType_ASTRONOMICAL,
      (TTwilightInfo){3, 17, 20, 37, TwilightStatus_OK});

  test_equation_of_time(27, 7, 2010, (TEquationOfTime){6, 31.52});

  test_solar_elongation(10, 6, 45, 11, 57, 27, 27.8333333, 7, 2010, 24.78);
}

int main() {
  test_datetime();
  test_coordinates();
  test_sun();

  return (0);
}
