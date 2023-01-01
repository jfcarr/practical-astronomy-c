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
         "%f\n\tGot:      %f\n",
         (int)greenwich_month, (int)greenwich_day, (int)greenwich_year,
         expected_result, actual_result);
}

void test_ecliptic_coordinates_to_equatorial_coordinates(
    double ecliptic_longitude_degrees, double ecliptic_longitude_minutes,
    double ecliptic_longitude_seconds, double ecliptic_latitude_degrees,
    double ecliptic_latitude_minutes, double ecliptic_latitude_seconds,
    double greenwich_day, int greenwich_month, int greenwich_year,
    TEquatorialCoordinates2 expected_result) {
  TEquatorialCoordinates2 actual_result =
      ecliptic_coordinates_to_equatorial_coordinates(
          ecliptic_longitude_degrees, ecliptic_longitude_minutes,
          ecliptic_longitude_seconds, ecliptic_latitude_degrees,
          ecliptic_latitude_minutes, ecliptic_latitude_seconds, greenwich_day,
          greenwich_month, greenwich_year);

  assert(actual_result.right_ascension_hours ==
         expected_result.right_ascension_hours);
  assert(actual_result.right_ascension_minutes ==
         expected_result.right_ascension_minutes);
  assert(actual_result.right_ascension_seconds ==
         expected_result.right_ascension_seconds);
  assert(actual_result.declination_degrees ==
         expected_result.declination_degrees);
  assert(actual_result.declination_minutes ==
         expected_result.declination_minutes);
  assert(actual_result.declination_seconds ==
         expected_result.declination_seconds);

  printf(
      "Equatorial Coordinates for Ecliptic Coordinates of %0.0f degrees, %0.0f "
      "minutes, %0.0f seconds/%0.0f degrees, %0.0f minutes, %0.0f "
      "seconds:\n\tExpected: %dh %dm %ds/%dh %dm %ds\n\tGot:      %dh %dm "
      "%ds/%dh %dm %ds\n",
      ecliptic_longitude_degrees, ecliptic_longitude_minutes,
      ecliptic_longitude_seconds, ecliptic_latitude_degrees,
      ecliptic_latitude_minutes, ecliptic_latitude_seconds,
      (int)expected_result.right_ascension_hours,
      (int)expected_result.right_ascension_minutes,
      (int)expected_result.right_ascension_seconds,
      (int)expected_result.declination_degrees,
      (int)expected_result.declination_minutes,
      (int)expected_result.declination_seconds,
      (int)actual_result.right_ascension_hours,
      (int)actual_result.right_ascension_minutes,
      (int)actual_result.right_ascension_seconds,
      (int)actual_result.declination_degrees,
      (int)actual_result.declination_minutes,
      (int)actual_result.declination_seconds);
}

void test_equatorial_coordinate_to_ecliptic_coordinate(
    double ra_hours, double ra_minutes, double ra_seconds, double dec_degrees,
    double dec_minutes, double dec_seconds, double gw_day, int gw_month,
    int gw_year, TEclipticCoordinates expected_result) {
  TEclipticCoordinates actual_result =
      equatorial_coordinate_to_ecliptic_coordinate(
          ra_hours, ra_minutes, ra_seconds, dec_degrees, dec_minutes,
          dec_seconds, gw_day, gw_month, gw_year);

  assert(actual_result.latitude_degrees = expected_result.latitude_degrees);
  assert(actual_result.latitude_minutes = expected_result.latitude_minutes);
  assert(actual_result.latitude_seconds = expected_result.latitude_seconds);
  assert(actual_result.longitude_degrees = expected_result.longitude_degrees);
  assert(actual_result.longitude_minutes = expected_result.longitude_minutes);
  assert(actual_result.longitude_seconds = expected_result.longitude_seconds);

  printf(
      "Ecliptic Coordinates for Equatorial Coordinates of %0.0f hours, %0.0f "
      "minutes, %0.0f seconds/%0.0f degrees, %0.0f minutes, %0.0f "
      "seconds:\n\tExpected: %dd %dm %ds/%dd %dm %ds\n\tGot:      %dd %dm "
      "%ds/%dd %dm %ds\n",
      ra_hours, ra_minutes, ra_seconds, dec_degrees, dec_minutes, dec_seconds,
      (int)expected_result.latitude_degrees,
      (int)expected_result.latitude_minutes,
      (int)expected_result.latitude_seconds,
      (int)expected_result.longitude_degrees,
      (int)expected_result.longitude_minutes,
      (int)expected_result.longitude_seconds,
      (int)actual_result.latitude_degrees, (int)actual_result.latitude_minutes,
      (int)actual_result.latitude_seconds, (int)actual_result.longitude_degrees,
      (int)actual_result.longitude_minutes,
      (int)actual_result.longitude_seconds);
}

void test_equatorial_coordinate_to_galactic_coordinate(
    double ra_hours, double ra_minutes, double ra_seconds, double dec_degrees,
    double dec_minutes, double dec_seconds,
    TGalacticCoordinates expected_result) {

  TGalacticCoordinates actual_result =
      equatorial_coordinate_to_galactic_coordinate(ra_hours, ra_minutes,
                                                   ra_seconds, dec_degrees,
                                                   dec_minutes, dec_seconds);

  assert(actual_result.latitude_degrees == expected_result.latitude_degrees);
  assert(actual_result.latitude_minutes == expected_result.latitude_minutes);
  assert(actual_result.latitude_seconds == expected_result.latitude_seconds);
  assert(actual_result.longitude_degrees == expected_result.longitude_degrees);
  assert(actual_result.longitude_minutes == expected_result.longitude_minutes);
  assert(actual_result.longitude_seconds == expected_result.longitude_seconds);

  printf(
      "Galactic Coordinates for Equatorial Coordinates of %0.0f hours, %0.0f "
      "minutes, %0.0f seconds/%0.0f degrees, %0.0f minutes, %0.0f "
      "seconds:\n\tExpected: %dd %dm %ds/%dd %dm %ds\n\tGot:      %dd %dm "
      "%ds/%dd %dm %ds\n",
      ra_hours, ra_minutes, ra_seconds, dec_degrees, dec_minutes, dec_seconds,
      (int)expected_result.latitude_degrees,
      (int)expected_result.latitude_minutes,
      (int)expected_result.latitude_seconds,
      (int)expected_result.longitude_degrees,
      (int)expected_result.longitude_minutes,
      (int)expected_result.longitude_seconds,
      (int)actual_result.latitude_degrees, (int)actual_result.latitude_minutes,
      (int)actual_result.latitude_seconds, (int)actual_result.longitude_degrees,
      (int)actual_result.longitude_minutes,
      (int)actual_result.longitude_seconds);
}

void test_galactic_coordinates_to_equatorial_coordinates(
    double gal_long_deg, double gal_long_min, double gal_long_sec,
    double gal_lat_deg, double gal_lat_min, double gal_lat_sec,
    TEquatorialCoordinates2 expected_result) {
  TEquatorialCoordinates2 actual_result =
      galactic_coordinates_to_equatorial_coordinates(gal_long_deg, gal_long_min,
                                                     gal_long_sec, gal_lat_deg,
                                                     gal_lat_min, gal_lat_sec);

  assert(actual_result.declination_degrees ==
         expected_result.declination_degrees);
  assert(actual_result.declination_minutes ==
         expected_result.declination_minutes);
  assert(actual_result.declination_seconds ==
         expected_result.declination_seconds);
  assert(actual_result.right_ascension_hours ==
         expected_result.right_ascension_hours);
  assert(actual_result.right_ascension_minutes ==
         expected_result.right_ascension_minutes);
  assert(actual_result.right_ascension_seconds ==
         expected_result.right_ascension_seconds);

  printf(
      "Equatorial Coordinates for Galactic Coordinates of %0.0f degrees, %0.0f "
      "minutes, %0.0f seconds/%0.0f degrees, %0.0f minutes, %0.0f "
      "seconds:\n\tExpected: %dh %dm %ds/%dh %dm %ds\n\tGot:      %dh %dm "
      "%ds/%dh %dm %ds\n",
      gal_long_deg, gal_long_min, gal_long_sec, gal_lat_deg, gal_lat_min,
      gal_lat_sec, (int)expected_result.right_ascension_hours,
      (int)expected_result.right_ascension_minutes,
      (int)expected_result.right_ascension_seconds,
      (int)expected_result.declination_degrees,
      (int)expected_result.declination_minutes,
      (int)expected_result.declination_seconds,
      (int)actual_result.right_ascension_hours,
      (int)actual_result.right_ascension_minutes,
      (int)actual_result.right_ascension_seconds,
      (int)actual_result.declination_degrees,
      (int)actual_result.declination_minutes,
      (int)actual_result.declination_seconds);
}

void test_angle_between_two_objects(
    double ra_long1_hour_deg, double ra_long1_min, double ra_long1_sec,
    double dec_lat1_deg, double dec_lat1_min, double dec_lat1_sec,
    double ra_long2_hour_deg, double ra_long2_min, double ra_long2_sec,
    double dec_lat2_deg, double dec_lat2_min, double dec_lat2_sec,
    TAngleMeasurementUnits hour_or_degree, TAngle expected_result) {
  TAngle actual_result = angle_between_two_objects(
      ra_long1_hour_deg, ra_long1_min, ra_long1_sec, dec_lat1_deg, dec_lat1_min,
      dec_lat1_sec, ra_long2_hour_deg, ra_long2_min, ra_long2_sec, dec_lat2_deg,
      dec_lat2_min, dec_lat2_sec, hour_or_degree);

  assert(actual_result.degrees == expected_result.degrees);
  assert(actual_result.minutes == expected_result.minutes);
  assert(actual_result.seconds == expected_result.seconds);

  printf("Angle between:\n\tObject 1, with RA %0.0f %0.0fm %0.0fs Dec %0.0fd "
         "%0.0fm %0.0fs\n\tObject 2, with RA %0.0f %0.0fm %0.0fs Dec %0.0fd "
         "%0.0fm %0.0fs\n\t\tExpected: %0.0fd %0.0fm %0.0fs\n\t\tGot:      "
         "%0.0fd %0.0fm %0.0fs\n",
         ra_long1_hour_deg, ra_long1_min, ra_long1_sec, dec_lat1_deg,
         dec_lat1_min, dec_lat1_sec, ra_long2_hour_deg, ra_long2_min,
         ra_long2_sec, dec_lat2_deg, dec_lat2_min, dec_lat2_sec,
         expected_result.degrees, expected_result.minutes,
         expected_result.seconds, actual_result.degrees, actual_result.minutes,
         actual_result.seconds);
}

void test_rising_and_setting(double ra_hours, double ra_minutes,
                             double ra_seconds, double dec_deg, double dec_min,
                             double dec_sec, double gw_date_day,
                             int gw_date_month, int gw_date_year,
                             double geog_long_deg, double geog_lat_deg,
                             double vert_shift_deg, TRiseSet expected_result) {
  TRiseSet actual_result = rising_and_setting(
      ra_hours, ra_minutes, ra_seconds, dec_deg, dec_min, dec_sec, gw_date_day,
      gw_date_month, gw_date_year, geog_long_deg, geog_lat_deg, vert_shift_deg);

  assert(actual_result.az_rise == expected_result.az_rise);
  assert(actual_result.az_set == expected_result.az_set);
  assert(actual_result.rise_set_status == expected_result.rise_set_status);
  assert(actual_result.ut_rise_hour == expected_result.ut_rise_hour);
  assert(actual_result.ut_rise_minute == expected_result.ut_rise_minute);
  assert(actual_result.ut_set_hour == expected_result.ut_set_hour);
  assert(actual_result.ut_set_minute == expected_result.ut_set_minute);

  printf("(Rising and Setting) WHEN\n");
  printf("\tRight Ascension is %0.0fh %0.0fm %0.0fs AND\n", ra_hours,
         ra_minutes, ra_seconds);
  printf("\tDeclination is %0.0fd %0.0fm %0.0fs AND\n", dec_deg, dec_min,
         dec_sec);
  printf("\tGreenwich Date is %d/%0.0f/%d AND\n", gw_date_month, gw_date_day,
         gw_date_year);
  printf("\tGeographical Long/Lat is %0.1f/%0.1f\n", geog_long_deg,
         geog_lat_deg);
  printf("\tTHEN\n");
  printf("\t\tExpected:\n");
  printf("\t\t\trise/set status is %d AND\n", expected_result.rise_set_status);
  printf("\t\t\trise time is %0.0f:%0.0f AND\n", expected_result.ut_rise_hour,
         expected_result.ut_rise_minute);
  printf("\t\t\tset time is %0.0f:%0.0f AND\n", expected_result.ut_set_hour,
         expected_result.ut_set_minute);
  printf("\t\t\tazimuth rise/set is %0.2f/%0.2f\n", expected_result.az_rise,
         expected_result.az_set);
  printf("\t\tActual:\n");
  printf("\t\t\trise/set status is %d AND\n", actual_result.rise_set_status);
  printf("\t\t\trise time is %0.0f:%0.0f AND\n", actual_result.ut_rise_hour,
         actual_result.ut_rise_minute);
  printf("\t\t\tset time is %0.0f:%0.0f AND\n", actual_result.ut_set_hour,
         actual_result.ut_set_minute);
  printf("\t\t\tazimuth rise/set is %0.2f/%0.2f\n", actual_result.az_rise,
         actual_result.az_set);
}

void test_correct_for_precession(double ra_hour, double ra_minutes,
                                 double ra_seconds, double dec_deg,
                                 double dec_minutes, double dec_seconds,
                                 double epoch1_day, int epoch1_month,
                                 int epoch1_year, double epoch2_day,
                                 int epoch2_month, int epoch2_year,
                                 TCorrectedPrecession expected_result) {
  TCorrectedPrecession actual_result = correct_for_precession(
      ra_hour, ra_minutes, ra_seconds, dec_deg, dec_minutes, dec_seconds,
      epoch1_day, epoch1_month, epoch1_year, epoch2_day, epoch2_month,
      epoch2_year);

  assert(actual_result.declination_degrees ==
         expected_result.declination_degrees);
  assert(actual_result.declination_minutes ==
         expected_result.declination_minutes);
  assert(actual_result.declination_seconds ==
         expected_result.declination_seconds);
  assert(actual_result.right_ascension_hours ==
         expected_result.right_ascension_hours);
  assert(actual_result.right_ascension_minutes ==
         expected_result.right_ascension_minutes);
  assert(actual_result.right_ascension_seconds ==
         expected_result.right_ascension_seconds);

  printf("(Corrected for Precession) WHEN\n");
  printf("\tRight Ascension is %0.0fh %0.0fm %0.0fs AND\n", ra_hour, ra_minutes,
         ra_seconds);
  printf("\tDeclination is %0.0fd %0.0fm %0.0fs AND\n", dec_deg, dec_minutes,
         dec_seconds);
  printf("\tEpoch 1 date is %d/%0.3f/%d AND\n", epoch1_month, epoch1_day,
         epoch1_year);
  printf("\tEpoch 2 date is %d/%0.3f/%d\n", epoch2_month, epoch2_day,
         epoch2_year);
  printf("\tTHEN\n");
  printf("\t\tExpected:\n");
  printf("\t\t\tRight Ascension is %0.0fh %0.0fm %0.0fs AND\n",
         expected_result.right_ascension_hours,
         expected_result.right_ascension_minutes,
         expected_result.right_ascension_seconds);
  printf("\t\t\tDeclination is %0.0fd %0.0fm %0.0fs\n",
         expected_result.declination_degrees,
         expected_result.declination_minutes,
         expected_result.declination_seconds);
  printf("\t\tActual:\n");
  printf("\t\t\tRight Ascension is %0.0fh %0.0fm %0.0fs AND\n",
         actual_result.right_ascension_hours,
         actual_result.right_ascension_minutes,
         actual_result.right_ascension_seconds);
  printf("\t\t\tDeclination is %0.0fd %0.0fm %0.0fs\n",
         actual_result.declination_degrees, actual_result.declination_minutes,
         actual_result.declination_seconds);
}

void test_nutation_in_ecliptic_longitude_and_obliquity(
    double greenwich_day, int greenwich_month, int greenwich_year,
    TNutation expected_result) {
  TNutation actual_result = nutation_in_ecliptic_longitude_and_obliquity(
      greenwich_day, greenwich_month, greenwich_year);

  assert(dround(actual_result.nutation_in_ecliption_longitude, 9) ==
         expected_result.nutation_in_ecliption_longitude);
  assert(dround(actual_result.nutation_in_obliquity, 7) ==
         expected_result.nutation_in_obliquity);

  printf("(Nutation) WHEN\n");
  printf("\tGreenwich Date is %d/%0.0f/%d\n", greenwich_month, greenwich_day,
         greenwich_year);
  printf("\tTHEN\n");
  printf("\t\tExpected:\n");
  printf("\t\t\tNutation in Ecliptic Longitude is %0.9f AND\n",
         expected_result.nutation_in_ecliption_longitude);
  printf("\t\t\tNutation in Obliquity is %0.7f\n",
         expected_result.nutation_in_obliquity);
  printf("\t\tActual:\n");
  printf("\t\t\tNutation in Ecliptic Longitude is %0.9f AND\n",
         actual_result.nutation_in_ecliption_longitude);
  printf("\t\t\tNutation in Obliquity is %0.7f\n",
         actual_result.nutation_in_obliquity);
}

void test_correct_for_aberration(
    double ut_hour, double ut_minutes, double ut_seconds, double gw_day,
    int gw_month, int gw_year, double true_ecl_long_deg,
    double true_ecl_long_min, double true_ecl_long_sec, double true_ecl_lat_deg,
    double true_ecl_lat_min, double true_ecl_lat_sec,
    TCorrectedEclipticCoordinates expected_result) {

  TCorrectedEclipticCoordinates actual_result = correct_for_aberration(
      ut_hour, ut_minutes, ut_seconds, gw_day, gw_month, gw_year,
      true_ecl_long_deg, true_ecl_long_min, true_ecl_long_sec, true_ecl_lat_deg,
      true_ecl_lat_min, true_ecl_lat_sec);

  assert(actual_result.latitude_degrees = expected_result.latitude_degrees);
  assert(actual_result.latitude_minutes = expected_result.latitude_minutes);
  assert(actual_result.latitude_seconds = expected_result.latitude_seconds);
  assert(actual_result.longitude_degrees = expected_result.longitude_degrees);
  assert(actual_result.longitude_minutes = expected_result.longitude_minutes);
  assert(actual_result.longitude_seconds = expected_result.longitude_seconds);

  printf("(Corrected For Aberration) WHEN\n");
  printf("\tUniversal Time is %0.0f:%0.0f:%0.0f AND\n", ut_hour, ut_minutes,
         ut_seconds);
  printf("\tGreenwich Date is %d/%0.0f/%d AND\n", gw_month, gw_day, gw_year);
  printf("\tTrue Ecliptic Longitude is %0.0fd %0.0fm %0.2fs AND\n",
         true_ecl_long_deg, true_ecl_long_min, true_ecl_long_sec);
  printf("\tTrue Ecliptic Latitude is %0.0fd %0.0fm %0.2fs\n", true_ecl_lat_deg,
         true_ecl_lat_min, true_ecl_lat_sec);
  printf("\tTHEN\n");
  printf("\t\tExpected:\n");
  printf("\t\t\tCorrected Ecliptic Longitude is %0.0fd %0.0fm %0.2fs AND\n",
         expected_result.longitude_degrees, expected_result.longitude_minutes,
         expected_result.longitude_seconds);
  printf("\t\t\tCorrected Ecliptic Latitude is %0.0fd %0.0fm %0.2fs\n",
         expected_result.latitude_degrees, expected_result.latitude_minutes,
         expected_result.latitude_seconds);
  printf("\t\tActual:\n");
  printf("\t\t\tCorrected Ecliptic Longitude is %0.0fd %0.0fm %0.2fs AND\n",
         actual_result.longitude_degrees, actual_result.longitude_minutes,
         actual_result.longitude_seconds);
  printf("\t\t\tCorrected Ecliptic Latitude is %0.0fd %0.0fm %0.2fs\n",
         actual_result.latitude_degrees, actual_result.latitude_minutes,
         actual_result.latitude_seconds);
}

void test_atmospheric_refraction(
    double true_ra_hour, double true_ra_min, double true_ra_sec,
    double true_dec_deg, double true_dec_min, double true_dec_sec,
    TCoordinateType coordinate_type1, double geog_long_deg, double geog_lat_deg,
    int daylight_saving_hours, int timezone_hours, double lcd_day,
    int lcd_month, int lcd_year, double lct_hour, double lct_min,
    double lct_sec, double atmospheric_pressure_mbar,
    double atmospheric_temperature_celsius,
    TCorrectedRefraction expected_result) {
  TCorrectedRefraction actual_result = atmospheric_refraction(
      true_ra_hour, true_ra_min, true_ra_sec, true_dec_deg, true_dec_min,
      true_dec_sec, coordinate_type1, geog_long_deg, geog_lat_deg,
      daylight_saving_hours, timezone_hours, lcd_day, lcd_month, lcd_year,
      lct_hour, lct_min, lct_sec, atmospheric_pressure_mbar,
      atmospheric_temperature_celsius);

  assert(actual_result.declination_degrees ==
         expected_result.declination_degrees);
  assert(actual_result.declination_minutes ==
         expected_result.declination_minutes);
  assert(actual_result.declination_seconds ==
         expected_result.declination_seconds);
  assert(actual_result.right_ascension_hours ==
         expected_result.right_ascension_hours);
  assert(actual_result.right_ascension_minutes ==
         expected_result.right_ascension_minutes);
  assert(actual_result.right_ascension_seconds ==
         expected_result.right_ascension_seconds);

  printf("(Corrected For Refraction) WHEN\n");
  printf("\tRight Ascension is %0.0fh %0.0fm %0.0fs AND\n", true_ra_hour,
         true_ra_min, true_ra_sec);
  printf("\tDeclination is %0.0fd %0.0fm %0.0fs AND\n", true_dec_deg,
         true_dec_min, true_dec_sec);
  printf("\tCoordinate Type is %d AND\n", coordinate_type1);
  printf("\tGeographical Long/Lat is %0.2f/%0.6f AND\n", geog_long_deg,
         geog_lat_deg);
  printf("\tDaylight Saving Hours is %d AND\n", daylight_saving_hours);
  printf("\tTimezone Hours is %d AND\n", timezone_hours);
  printf("\tLocal Civil Date is %d/%0.0f/%d AND\n", lcd_month, lcd_day,
         lcd_year);
  printf("\tLocal Civil Time is %0.0f:%0.0f:%0.0f AND\n", lct_hour, lct_min,
         lct_sec);
  printf("\tAtmospheric Pressure is %0.0f mbar AND\n",
         atmospheric_pressure_mbar);
  printf("\tAtmospheric Temperature is %0.1f celsius\n",
         atmospheric_temperature_celsius);
  printf("\tTHEN\n");
  printf("\t\tExpected:\n");
  printf("\t\t\tCorrected Right Ascension is %0.0fh %0.0fm %0.2fs AND\n",
         expected_result.right_ascension_hours,
         expected_result.right_ascension_minutes,
         expected_result.right_ascension_seconds);
  printf("\t\t\tCorrected Declination is %0.0fd %0.0fm %0.2fs\n",
         expected_result.declination_degrees,
         expected_result.declination_minutes,
         expected_result.declination_seconds);
  printf("\t\tActual:\n");
  printf("\t\t\tCorrected Right Ascension is %0.0fh %0.0fm %0.2fs AND\n",
         actual_result.right_ascension_hours,
         actual_result.right_ascension_minutes,
         actual_result.right_ascension_seconds);
  printf("\t\t\tCorrected Declination is %0.0fd %0.0fm %0.2fs\n",
         actual_result.declination_degrees, actual_result.declination_minutes,
         actual_result.declination_seconds);
}

void test_corrections_for_geocentric_parallax(
    double ra_hour, double ra_min, double ra_sec, double dec_deg,
    double dec_min, double dec_sec, TCoordinateType coordinate_type,
    double equatorial_hor_parallax_deg, double geog_long_deg,
    double geog_lat_deg, double height_m, int daylight_saving,
    int timezone_hours, double lcd_day, int lcd_month, int lcd_year,
    double lct_hour, double lct_min, double lct_sec,
    TCorrectedParallax expected_result) {
  TCorrectedParallax actual_result = corrections_for_geocentric_parallax(
      ra_hour, ra_min, ra_sec, dec_deg, dec_min, dec_sec, coordinate_type,
      equatorial_hor_parallax_deg, geog_long_deg, geog_lat_deg, height_m,
      daylight_saving, timezone_hours, lcd_day, lcd_month, lcd_year, lct_hour,
      lct_min, lct_sec);

  assert(actual_result.declination_degrees ==
         expected_result.declination_degrees);
  assert(actual_result.declination_minutes ==
         expected_result.declination_minutes);
  assert(actual_result.declination_seconds ==
         expected_result.declination_seconds);
  assert(actual_result.right_ascension_hours ==
         expected_result.right_ascension_hours);
  assert(actual_result.right_ascension_minutes ==
         expected_result.right_ascension_minutes);
  assert(actual_result.right_ascension_seconds ==
         expected_result.right_ascension_seconds);

  printf("(Corrected For Parallax) WHEN\n");
  printf("\tRight Ascension is %0.0fh %0.0fm %0.0fs AND\n", ra_hour, ra_min,
         ra_sec);
  printf("\tDeclination is %0.0fd %0.0fm %0.0fs AND\n", dec_deg, dec_min,
         dec_sec);
  printf("\tCoordinate Type is %d AND\n", coordinate_type);
  printf("\tEquatorial Horizon Parallax is %0.6fd AND\n",
         equatorial_hor_parallax_deg);
  printf("\tGeographical Long/Lat is %0.0f/%0.0f AND\n", geog_long_deg,
         geog_lat_deg);
  printf("\tHeight is %0.0f meters AND\n", height_m);
  printf("\tDaylight Saving Hours is %d AND\n", daylight_saving);
  printf("\tTimezone Hours is %d AND\n", timezone_hours);
  printf("\tLocal Civil Date is %d/%0.0f/%d AND\n", lcd_month, lcd_day,
         lcd_year);
  printf("\tLocal Civil Time is %0.0f:%0.0f:%0.0f AND\n", lct_hour, lct_min,
         lct_sec);
  printf("\tTHEN\n");
  printf("\t\tExpected:\n");
  printf("\t\t\tCorrected Right Ascension is %0.0fh %0.0fm %0.2fs AND\n",
         expected_result.right_ascension_hours,
         expected_result.right_ascension_minutes,
         expected_result.right_ascension_seconds);
  printf("\t\t\tCorrected Declination is %0.0fd %0.0fm %0.2fs\n",
         expected_result.declination_degrees,
         expected_result.declination_minutes,
         expected_result.declination_seconds);
  printf("\t\tActual:\n");
  printf("\t\t\tCorrected Right Ascension is %0.0fh %0.0fm %0.2fs AND\n",
         actual_result.right_ascension_hours,
         actual_result.right_ascension_minutes,
         actual_result.right_ascension_seconds);
  printf("\t\t\tCorrected Declination is %0.0fd %0.0fm %0.2fs\n",
         actual_result.declination_degrees, actual_result.declination_minutes,
         actual_result.declination_seconds);
}

void test_heliographic_coordinates(double helio_position_angle_deg,
                                   double helio_displacement_arcmin,
                                   double gwdate_day, int gwdate_month,
                                   int gwdate_year,
                                   THeliographicCoordinates expected_result) {
  THeliographicCoordinates actual_result = heliographic_coordinates(
      helio_position_angle_deg, helio_displacement_arcmin, gwdate_day,
      gwdate_month, gwdate_year);

  assert(actual_result.latitude_degrees == expected_result.latitude_degrees);
  assert(actual_result.longitude_degrees == expected_result.longitude_degrees);

  printf("(Heliographic Coordinates) WHEN\n");
  printf("\tHeliographic Position Angle is %0.0f degrees AND\n",
         helio_position_angle_deg);
  printf("\tHeliographic Displacement is %0.1f arc minutes AND\n",
         helio_displacement_arcmin);
  printf("\tGreenwich Date is %d/%0.0f/%d\n", gwdate_month, gwdate_day,
         gwdate_year);
  printf("\tTHEN\n");
  printf("\t\tExpected:\n");
  printf("\t\t\tHeliographic Longitude is %0.2f degrees AND\n",
         expected_result.longitude_degrees);
  printf("\t\t\tHeliographic Latitude is %0.2f degrees\n",
         expected_result.latitude_degrees);
  printf("\t\tActual:\n");
  printf("\t\t\tHeliographic Longitude is %0.2f degrees AND\n",
         actual_result.longitude_degrees);
  printf("\t\t\tHeliographic Latitude is %0.2f degrees\n",
         actual_result.latitude_degrees);
}

void test_carrington_rotation_number(double gwdate_day, int gwdate_month,
                                     int gwdate_year, int expected_value) {
  int actual_value =
      carrington_rotation_number(gwdate_day, gwdate_month, gwdate_year);

  assert(actual_value == expected_value);

  printf("(Carrington Rotation Number) WHEN\n");
  printf("\tGreenwich Date is %d/%0.0f/%d\n", gwdate_month, gwdate_day,
         gwdate_year);
  printf("\tTHEN\n");
  printf("\t\tExpected:\n");
  printf("\t\t\tCarrington Rotation Number is %d\n", expected_value);
  printf("\t\tActual:\n");
  printf("\t\t\tCarrington Rotation Number is %d\n", actual_value);
}