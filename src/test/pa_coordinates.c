#include "pa_coordinates.h"
#include "../lib/pa_coordinates.h"
#include "../lib/pa_util.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>

void test_angle_to_decimal_degrees(double degrees, double minutes,
                                   double seconds, double expected_result) {
  double actual_result =
      dround(angle_to_decimal_degrees(degrees, minutes, seconds), 6);

  assert(actual_result == expected_result);

  printf("Decimal Degrees for Angle of %d degrees, %d minutes %d "
         "seconds:\n\tExpected: %f\n\tGot:      %f\n",
         (int)degrees, (int)minutes, (int)seconds, expected_result,
         actual_result);
}

void test_decimal_degrees_to_angle(double decimal_degrees,
                                   TAngle expected_result) {
  TAngle actual_result = decimal_degrees_to_angle(decimal_degrees);

  assert(actual_result.degrees == expected_result.degrees);
  assert(actual_result.minutes == expected_result.minutes);
  assert(actual_result.seconds == expected_result.seconds);

  printf("Angle for Decimal Degrees of %0.6f:\n\tExpected: %dd %dm %ds\n\tGot: "
         "     %dd %dm %ds\n",
         decimal_degrees, (int)expected_result.degrees,
         (int)expected_result.minutes, (int)expected_result.seconds,
         (int)actual_result.degrees, (int)actual_result.minutes,
         (int)actual_result.seconds);
}

void test_right_ascension_to_hour_angle(
    double ra_hours, double ra_minutes, double ra_seconds, double lct_hours,
    double lct_minutes, double lct_seconds, bool is_daylight_savings,
    int zone_correction, double local_day, int local_month, int local_year,
    double geographical_longitude, THourAngle expected_result) {
  THourAngle actual_result = right_ascension_to_hour_angle(
      ra_hours, ra_minutes, ra_seconds, lct_hours, lct_minutes, lct_seconds,
      is_daylight_savings, zone_correction, local_day, local_month, local_year,
      geographical_longitude);

  assert(actual_result.hours == expected_result.hours);
  assert(actual_result.minutes == expected_result.minutes);
  assert(actual_result.seconds == expected_result.seconds);

  printf("Hour Angle for Right Ascension of %0.2f hours, %0.2f minutes, %0.2f "
         "seconds:\n\tExpected: %dh %dm %ds\n\tGot:      %dh %dm %ds\n",
         ra_hours, ra_minutes, ra_seconds, (int)expected_result.hours,
         (int)expected_result.minutes, (int)expected_result.seconds,
         (int)actual_result.hours, (int)actual_result.minutes,
         (int)actual_result.seconds);
}

void test_hour_angle_to_right_ascension(
    double hour_angle_hours, double hour_angle_minutes,
    double hour_angle_seconds, double lct_hours, double lct_minutes,
    double lct_seconds, bool is_daylight_savings, int zone_correction,
    double local_day, int local_month, int local_year,
    double geographical_longitude, TRightAscension expected_result) {
  TRightAscension actual_result = hour_angle_to_right_ascension(
      hour_angle_hours, hour_angle_minutes, hour_angle_seconds, lct_hours,
      lct_minutes, lct_seconds, is_daylight_savings, zone_correction, local_day,
      local_month, local_year, geographical_longitude);

  assert(actual_result.hours == expected_result.hours);
  assert(actual_result.minutes == expected_result.minutes);
  assert(actual_result.seconds == expected_result.seconds);

  printf("Right Ascension for Hour Angle of %0.2f hours, %0.2f minutes, %0.2f "
         "seconds:\n\tExpected: %dh %dm %ds\n\tGot:      %dh %dm %ds\n",
         hour_angle_hours, hour_angle_minutes, hour_angle_seconds,
         (int)expected_result.hours, (int)expected_result.minutes,
         (int)expected_result.seconds, (int)actual_result.hours,
         (int)actual_result.minutes, (int)actual_result.seconds);
}

void test_equatorial_coordinates_to_horizon_coordinates(
    double hour_angle_hours, double hour_angle_minutes,
    double hour_angle_seconds, double declination_degrees,
    double declination_minutes, double declination_seconds,
    double geographical_latitude, THorizonCoordinates expected_result) {
  THorizonCoordinates actual_result =
      equatorial_coordinates_to_horizon_coordinates(
          hour_angle_hours, hour_angle_minutes, hour_angle_seconds,
          declination_degrees, declination_minutes, declination_seconds,
          geographical_latitude);

  assert(actual_result.azimuth_degrees == expected_result.azimuth_degrees);
  assert(actual_result.azimuth_minutes == expected_result.azimuth_minutes);
  assert(actual_result.azimuth_seconds == expected_result.azimuth_seconds);
  assert(actual_result.altitude_degrees == expected_result.altitude_degrees);
  assert(actual_result.altitude_minutes == expected_result.altitude_minutes);
  assert(actual_result.altitude_seconds == expected_result.altitude_seconds);

  printf(
      "Horizon Coordinates for Equatorial Coordinates of %0.0f hours, %0.0f "
      "minutes, %0.0f seconds/%0.0f degrees, %0.0f minutes, %0.0f "
      "seconds:\n\tExpected: %dd %dm %ds/%dd %dm %ds\n\tGot:      %dd %dm "
      "%ds/%dd %dm %ds\n",
      hour_angle_hours, hour_angle_minutes, hour_angle_seconds,
      declination_degrees, declination_minutes, declination_seconds,
      (int)expected_result.azimuth_degrees,
      (int)expected_result.azimuth_minutes,
      (int)expected_result.azimuth_seconds,
      (int)expected_result.altitude_degrees,
      (int)expected_result.altitude_minutes,
      (int)expected_result.altitude_seconds, (int)actual_result.azimuth_degrees,
      (int)actual_result.azimuth_minutes, (int)actual_result.azimuth_seconds,
      (int)actual_result.altitude_degrees, (int)actual_result.altitude_minutes,
      (int)actual_result.altitude_seconds);
}

void test_horizon_coordinates_to_equatorial_coordinates(
    double azimuth_degrees, double azimuth_minutes, double azimuth_seconds,
    double altitude_degrees, double altitude_minutes, double altitude_seconds,
    double geographical_latitude, TEquatorialCoordinates expected_result) {
  TEquatorialCoordinates actual_result =
      horizon_coordinates_to_equatorial_coordinates(
          azimuth_degrees, azimuth_minutes, azimuth_seconds, altitude_degrees,
          altitude_minutes, altitude_seconds, geographical_latitude);

  assert(actual_result.hour_angle_hours == expected_result.hour_angle_hours);
  assert(actual_result.hour_angle_minutes ==
         expected_result.hour_angle_minutes);
  assert(actual_result.hour_angle_seconds ==
         expected_result.hour_angle_seconds);
  assert(actual_result.declination_degrees ==
         expected_result.declination_degrees);
  assert(actual_result.declination_minutes ==
         expected_result.declination_minutes);
  assert(actual_result.declination_seconds ==
         expected_result.declination_seconds);

  printf(
      "Equatorial Coordinates for Horizon Coordinates of %0.0f degrees, %0.0f "
      "minutes, %0.0f seconds/%0.0f degrees, %0.0f minutes, %0.0f "
      "seconds:\n\tExpected: %dh %dm %ds/%dh %dm %ds\n\tGot:      %dh %dm "
      "%ds/%dh %dm %ds\n",
      azimuth_degrees, azimuth_minutes, azimuth_seconds, altitude_degrees,
      altitude_minutes, altitude_seconds, (int)expected_result.hour_angle_hours,
      (int)expected_result.hour_angle_minutes,
      (int)expected_result.hour_angle_seconds,
      (int)expected_result.declination_degrees,
      (int)expected_result.declination_minutes,
      (int)expected_result.declination_seconds,
      (int)actual_result.hour_angle_hours,
      (int)actual_result.hour_angle_minutes,
      (int)actual_result.hour_angle_seconds,
      (int)actual_result.declination_degrees,
      (int)actual_result.declination_minutes,
      (int)actual_result.declination_seconds);
}

void test_mean_obliquity_of_the_ecliptic(double greenwich_day,
                                         int greenwich_month,
                                         int greenwich_year,
                                         double expected_result) {
  double actual_result = mean_obliquity_of_the_ecliptic(
      greenwich_day, greenwich_month, greenwich_year);

  assert(actual_result = expected_result);

  printf("Mean Obliquity for Greenwich Date of %d/%d/%d:\n\tExpected: "
         "%f\n\tGot: %f\n",
         (int)greenwich_month, (int)greenwich_day, (int)greenwich_year,
         expected_result, actual_result);
}
