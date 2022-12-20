#include "pa_datetime.h"
#include "pa_macros.h"
#include "pa_types.h"
#include "pa_util.h"
#include <math.h>
#include <stdio.h>

/**
 * Convert Angle (degrees,minutes,seconds) to Decimal Degrees
 */
double angle_to_decimal_degrees(double degrees, double minutes,
                                double seconds) {
  double a = fabs(seconds) / 60;
  double b = (fabs(minutes) + a) / 60;
  double c = fabs(degrees) + b;
  double d = (degrees < 0 || minutes < 0 || seconds < 0) ? -c : c;

  return d;
}

/**
 * Convert Decimal Degrees to an Angle (degrees, minutes, and seconds)
 */
TAngle decimal_degrees_to_angle(double decimal_degrees) {
  double unsigned_decimal = fabs(decimal_degrees);
  double total_seconds = unsigned_decimal * 3600;
  double seconds2_dp = dround(fmod(total_seconds, 60), 2);
  double corrected_seconds = (seconds2_dp == 60) ? 0 : seconds2_dp;
  double corrected_remainder =
      (seconds2_dp == 60) ? total_seconds + 60 : total_seconds;
  double minutes = fmod(floor(corrected_remainder / 60), 60);
  double unsigned_degrees = floor(corrected_remainder / 3600);
  double signed_degrees =
      (decimal_degrees < 0) ? -1 * unsigned_degrees : unsigned_degrees;

  return (TAngle){signed_degrees, minutes, floor(corrected_seconds)};
}

/**
 * Convert Right Ascension to Hour Angle
 *
 * @return THourAngle <double hour_angle_hours, double hour_angle_minutes,
 * double hour_angle_seconds>
 */
THourAngle right_ascension_to_hour_angle(double ra_hours, double ra_minutes,
                                         double ra_seconds, double lct_hours,
                                         double lct_minutes, double lct_seconds,
                                         bool is_daylight_savings,
                                         int zone_correction, double local_day,
                                         int local_month, int local_year,
                                         double geographical_longitude) {
  int daylight_saving = (is_daylight_savings) ? 1 : 0;

  double hour_angle = right_ascension_to_hour_angle_macro(
      ra_hours, ra_minutes, ra_seconds, lct_hours, lct_minutes, lct_seconds,
      daylight_saving, zone_correction, local_day, local_month, local_year,
      geographical_longitude);

  int hour_angle_hours = decimal_hours_hour(hour_angle);
  int hour_angle_minutes = decimal_hours_minute(hour_angle);
  double hour_angle_seconds = decimal_hours_second(hour_angle);

  return (THourAngle){hour_angle_hours, hour_angle_minutes, hour_angle_seconds};
}

/**
 * \brief Convert Hour Angle to Right Ascension
 *
 * @return TRightAscension <double right_ascension_hours, double
 * right_ascension_minutes, double right_ascension_seconds>
 */
TRightAscension hour_angle_to_right_ascension(
    double hour_angle_hours, double hour_angle_minutes,
    double hour_angle_seconds, double lct_hours, double lct_minutes,
    double lct_seconds, bool is_daylight_savings, int zone_correction,
    double local_day, int local_month, int local_year,
    double geographical_longitude) {
  int daylight_saving = (is_daylight_savings) ? 1 : 0;

  double right_ascension = hour_angle_to_right_ascension_macro(
      hour_angle_hours, hour_angle_minutes, hour_angle_seconds, lct_hours,
      lct_minutes, lct_seconds, daylight_saving, zone_correction, local_day,
      local_month, local_year, geographical_longitude);

  int right_ascension_hours = decimal_hours_hour(right_ascension);
  int right_ascension_minutes = decimal_hours_minute(right_ascension);
  int right_ascension_seconds = decimal_hours_second(right_ascension);

  return (TRightAscension){right_ascension_hours, right_ascension_minutes,
                           right_ascension_seconds};
}

/**
 * Convert Equatorial Coordinates to Horizon Coordinates
 *
 * @return THorizonCoordinates <double azimuthDegrees, double azimuthMinutes,
 * double azimuthSeconds, double altitudeDegrees, double altitudeMinutes, double
 * altitudeSeconds>
 */
THorizonCoordinates equatorial_coordinates_to_horizon_coordinates(
    double hour_angle_hours, double hour_angle_minutes,
    double hour_angle_seconds, double declination_degrees,
    double declination_minutes, double declination_seconds,
    double geographical_latitude) {
  double azimuth_in_decimal_degrees = equatorial_coordinates_to_azimuth(
      hour_angle_hours, hour_angle_minutes, hour_angle_seconds,
      declination_degrees, declination_minutes, declination_seconds,
      geographical_latitude);

  double altitude_in_decimal_degrees = equatorial_coordinates_to_altitude(
      hour_angle_hours, hour_angle_minutes, hour_angle_seconds,
      declination_degrees, declination_minutes, declination_seconds,
      geographical_latitude);

  double azimuth_degrees = decimal_degrees_degrees(azimuth_in_decimal_degrees);
  double azimuth_minutes = decimal_degrees_minutes(azimuth_in_decimal_degrees);
  double azimuth_seconds = decimal_degrees_seconds(azimuth_in_decimal_degrees);

  double altitude_degrees =
      decimal_degrees_degrees(altitude_in_decimal_degrees);
  double altitude_minutes =
      decimal_degrees_minutes(altitude_in_decimal_degrees);
  double altitude_seconds =
      decimal_degrees_seconds(altitude_in_decimal_degrees);

  return (THorizonCoordinates){azimuth_degrees,  azimuth_minutes,
                               azimuth_seconds,  altitude_degrees,
                               altitude_minutes, altitude_seconds};
}

/**
 * Convert Horizon Coordinates to Equatorial Coordinates
 *
 * @return TEquatorialCoordinates <double hour_angle_hours, double
 * hour_angle_minutes, double hour_angle_seconds, double declination_degrees,
 * double declination_minutes, double declination_seconds>
 */
TEquatorialCoordinates horizon_coordinates_to_equatorial_coordinates(
    double azimuth_degrees, double azimuth_minutes, double azimuth_seconds,
    double altitude_degrees, double altitude_minutes, double altitude_seconds,
    double geographical_latitude) {
  double hour_angle_in_decimal_degrees = horizon_coordinates_to_hour_angle(
      azimuth_degrees, azimuth_minutes, azimuth_seconds, altitude_degrees,
      altitude_minutes, altitude_seconds, geographical_latitude);

  double declination_in_decimal_degrees = horizon_coordinates_to_declination(
      azimuth_degrees, azimuth_minutes, azimuth_seconds, altitude_degrees,
      altitude_minutes, altitude_seconds, geographical_latitude);

  int hour_angle_hours = decimal_hours_hour(hour_angle_in_decimal_degrees);
  int hour_angle_minutes = decimal_hours_minute(hour_angle_in_decimal_degrees);
  double hour_angle_seconds =
      decimal_hours_second(hour_angle_in_decimal_degrees);

  double declination_degrees =
      decimal_degrees_degrees(declination_in_decimal_degrees);
  double declination_minutes =
      decimal_degrees_minutes(declination_in_decimal_degrees);
  double declination_seconds =
      decimal_degrees_seconds(declination_in_decimal_degrees);

  return (TEquatorialCoordinates){hour_angle_hours,    hour_angle_minutes,
                                  hour_angle_seconds,  declination_degrees,
                                  declination_minutes, declination_seconds};
}

/**
 * Calculate Mean Obliquity of the Ecliptic for a Greenwich Date
 *
 * @return double mean_obliquity
 */
double mean_obliquity_of_the_ecliptic(double greenwich_day, int greenwich_month,
                                      int greenwich_year) {
  double jd =
      civil_date_to_julian_date(greenwich_day, greenwich_month, greenwich_year);
  double mjd = jd - 2451545;
  double t = mjd / 36525;
  double de1 = t * (46.815 + t * (0.0006 - (t * 0.00181)));
  double de2 = de1 / 3600;

  return 23.439292 - de2;
}

/**
 * Convert Ecliptic Coordinates to Equatorial Coordinates
 *
 * @return TEquatorialCoordinates2 <double right_ascension_hours, double
 * right_ascension_minutes, double right_ascension_seconds, double
 * declination_degrees, double declination_minutes, double declination_seconds>
 */
TEquatorialCoordinates2 ecliptic_coordinates_to_equatorial_coordinates(
    double ecliptic_longitude_degrees, double ecliptic_longitude_minutes,
    double ecliptic_longitude_seconds, double ecliptic_latitude_degrees,
    double ecliptic_latitude_minutes, double ecliptic_latitude_seconds,
    double greenwich_day, int greenwich_month, int greenwich_year) {
  double ec_lon_deg = degrees_minutes_seconds_to_decimal_degrees(
      ecliptic_longitude_degrees, ecliptic_longitude_minutes,
      ecliptic_longitude_seconds);
  double ec_lat_deg = degrees_minutes_seconds_to_decimal_degrees(
      ecliptic_latitude_degrees, ecliptic_latitude_minutes,
      ecliptic_latitude_seconds);
  double ec_lon_rad = degrees_to_radians(ec_lon_deg);
  double ec_lat_rad = degrees_to_radians(ec_lat_deg);
  double obliq_deg = obliq(greenwich_day, greenwich_month, greenwich_year);
  double obliq_rad = degrees_to_radians(obliq_deg);
  double sin_dec = sin(ec_lat_rad) * cos(obliq_rad) +
                   cos(ec_lat_rad) * sin(obliq_rad) * sin(ec_lon_rad);
  double dec_rad = asin(sin_dec);
  double dec_deg = w_to_degrees(dec_rad);
  double y =
      sin(ec_lon_rad) * cos(obliq_rad) - tan(ec_lat_rad) * sin(obliq_rad);
  double x = cos(ec_lon_rad);
  double ra_rad = atan2(y, x);
  double ra_deg1 = w_to_degrees(ra_rad);
  double ra_deg2 = ra_deg1 - 360 * floor(ra_deg1 / 360);
  double ra_hours = decimal_degrees_to_degree_hours(ra_deg2);

  int out_ra_hours = decimal_hours_hour(ra_hours);
  int out_ra_minutes = decimal_hours_minute(ra_hours);
  double out_ra_seconds = decimal_hours_second(ra_hours);
  double out_dec_degrees = decimal_degrees_degrees(dec_deg);
  double out_dec_minutes = decimal_degrees_minutes(dec_deg);
  double out_dec_seconds = decimal_degrees_seconds(dec_deg);

  return (TEquatorialCoordinates2){out_ra_hours,    out_ra_minutes,
                                   out_ra_seconds,  out_dec_degrees,
                                   out_dec_minutes, out_dec_seconds};
}

/**
 * Convert Equatorial Coordinates to Ecliptic Coordinates
 *
 * @return TEclipticCoordinates <double longitude_degrees, double
 * longitude_minutes, double longitude_seconds, double latitude_degrees, double
 * latitude_minutes, double latitude_seconds>
 */
TEclipticCoordinates equatorial_coordinate_to_ecliptic_coordinate(
    double ra_hours, double ra_minutes, double ra_seconds, double dec_degrees,
    double dec_minutes, double dec_seconds, double gw_day, int gw_month,
    int gw_year) {
  double ra_deg =
      degree_hours_to_decimal_degrees(hms_dh(ra_hours, ra_minutes, ra_seconds));
  double dec_deg = degrees_minutes_seconds_to_decimal_degrees(
      dec_degrees, dec_minutes, dec_seconds);
  double ra_rad = degrees_to_radians(ra_deg);
  double dec_rad = degrees_to_radians(dec_deg);
  double obliq_deg = obliq(gw_day, gw_month, gw_year);
  double obliq_rad = degrees_to_radians(obliq_deg);
  double sin_ecl_rad = sin(dec_rad) * cos(obliq_rad) -
                       cos(dec_rad) * sin(obliq_rad) * sin(ra_rad);
  double ecl_lat_rad = asin(sin_ecl_rad);
  double ecl_lat_deg = w_to_degrees(ecl_lat_rad);
  double y = sin(ra_rad) * cos(obliq_rad) + tan(dec_rad) * sin(obliq_rad);
  double x = cos(ra_rad);
  double ecl_long_rad = atan2(y, x);
  double ecl_long_deg1 = w_to_degrees(ecl_long_rad);
  double ecl_long_deg2 = ecl_long_deg1 - 360 * floor(ecl_long_deg1 / 360);

  double out_ecl_long_deg = decimal_degrees_degrees(ecl_long_deg2);
  double out_ecl_long_min = decimal_degrees_minutes(ecl_long_deg2);
  double out_ecl_long_sec = decimal_degrees_seconds(ecl_long_deg2);
  double out_ecl_lat_deg = decimal_degrees_degrees(ecl_lat_deg);
  double out_ecl_lat_min = decimal_degrees_minutes(ecl_lat_deg);
  double out_ecl_lat_sec = decimal_degrees_seconds(ecl_lat_deg);

  return (TEclipticCoordinates){out_ecl_long_deg, out_ecl_long_min,
                                out_ecl_long_sec, out_ecl_lat_deg,
                                out_ecl_lat_min,  out_ecl_lat_sec};
}

/**
 * Convert Equatorial Coordinates to Galactic Coordinates
 *
 * @return TGalacticCoordinates <double longitude_degrees, double
 * longitude_minutes, double longitude_seconds, double latitude_degrees, double
 * latitude_minutes, double latitude_seconds>
 */
TGalacticCoordinates equatorial_coordinate_to_galactic_coordinate(
    double ra_hours, double ra_minutes, double ra_seconds, double dec_degrees,
    double dec_minutes, double dec_seconds) {
  double ra_deg =
      degree_hours_to_decimal_degrees(hms_dh(ra_hours, ra_minutes, ra_seconds));
  double dec_deg = degrees_minutes_seconds_to_decimal_degrees(
      dec_degrees, dec_minutes, dec_seconds);
  double ra_rad = degrees_to_radians(ra_deg);
  double dec_rad = degrees_to_radians(dec_deg);
  double sin_b = cos(dec_rad) * cos(degrees_to_radians(27.4)) *
                     cos(ra_rad - degrees_to_radians(192.25)) +
                 sin(dec_rad) * sin(degrees_to_radians(27.4));
  double b_radians = asin(sin_b);
  double b_deg = w_to_degrees(b_radians);
  double y = sin(dec_rad) - sin_b * sin(degrees_to_radians(27.4));
  double x = cos(dec_rad) * sin(ra_rad - degrees_to_radians(192.25)) *
             cos(degrees_to_radians(27.4));
  double long_deg1 = w_to_degrees(atan2(y, x)) + 33;
  double long_deg2 = long_deg1 - 360 * floor(long_deg1 / 360);

  double gal_long_deg = decimal_degrees_degrees(long_deg2);
  double gal_long_min = decimal_degrees_minutes(long_deg2);
  double gal_long_sec = decimal_degrees_seconds(long_deg2);
  double gal_lat_deg = decimal_degrees_degrees(b_deg);
  double gal_lat_min = decimal_degrees_minutes(b_deg);
  double gal_lat_sec = decimal_degrees_seconds(b_deg);

  return (TGalacticCoordinates){gal_long_deg, gal_long_min, gal_long_sec,
                                gal_lat_deg,  gal_lat_min,  gal_lat_sec};
}

/**
 * Convert Galactic Coordinates to Equatorial Coordinates
 *
 * @return TEquatorialCoordinates2 <double right_ascension_hours, double
 * right_ascension_minutes, double right_ascension_seconds, double
 * declination_degrees, double declination_minutes, double declination_seconds>
 */
TEquatorialCoordinates2 galactic_coordinates_to_equatorial_coordinates(
    double gal_long_deg, double gal_long_min, double gal_long_sec,
    double gal_lat_deg, double gal_lat_min, double gal_lat_sec) {
  double g_long_deg = degrees_minutes_seconds_to_decimal_degrees(
      gal_long_deg, gal_long_min, gal_long_sec);
  double g_lat_deg = degrees_minutes_seconds_to_decimal_degrees(
      gal_lat_deg, gal_lat_min, gal_lat_sec);
  double g_long_rad = degrees_to_radians(g_long_deg);
  double g_lat_rad = degrees_to_radians(g_lat_deg);
  double sin_dec = cos(g_lat_rad) * cos(degrees_to_radians(27.4)) *
                       sin(g_long_rad - degrees_to_radians(33.0)) +
                   sin(g_lat_rad) * sin(degrees_to_radians(27.4));
  double dec_radians = asin(sin_dec);
  double dec_deg = w_to_degrees(dec_radians);
  double y = cos(g_lat_rad) * cos(g_long_rad - degrees_to_radians(33.0));
  double x = sin(g_lat_rad) * cos(degrees_to_radians(27.4)) -
             cos(g_lat_rad) * sin(degrees_to_radians(27.4)) *
                 sin(g_long_rad - degrees_to_radians(33.0));

  double ra_deg1 = w_to_degrees(atan2(y, x)) + 192.25;
  double ra_deg2 = ra_deg1 - 360 * floor(ra_deg1 / 360);
  double ra_hours1 = decimal_degrees_to_degree_hours(ra_deg2);

  double ra_hours = decimal_hours_hour(ra_hours1);
  double ra_minutes = decimal_hours_minute(ra_hours1);
  double ra_seconds = decimal_hours_second(ra_hours1);
  double dec_degrees = decimal_degrees_degrees(dec_deg);
  double dec_minutes = decimal_degrees_minutes(dec_deg);
  double dec_seconds = decimal_degrees_seconds(dec_deg);

  return (TEquatorialCoordinates2){ra_hours,    ra_minutes,  ra_seconds,
                                   dec_degrees, dec_minutes, dec_seconds};
}

/**
 * Calculate the angle between two celestial objects
 *
 * @return TAngle <double degrees, double minutes, double seconds>
 */
TAngle angle_between_two_objects(double ra_long1_hour_deg, double ra_long1_min,
                                 double ra_long1_sec, double dec_lat1_deg,
                                 double dec_lat1_min, double dec_lat1_sec,
                                 double ra_long2_hour_deg, double ra_long2_min,
                                 double ra_long2_sec, double dec_lat2_deg,
                                 double dec_lat2_min, double dec_lat2_sec,
                                 TAngleMeasurementUnits hour_or_degree) {
  double ra_long1_decimal =
      (hour_or_degree == AngleMeasurement_Hours)
          ? hms_dh(ra_long1_hour_deg, ra_long1_min, ra_long1_sec)
          : degrees_minutes_seconds_to_decimal_degrees(
                ra_long1_hour_deg, ra_long1_min, ra_long1_sec);
  double ra_long1_deg = (hour_or_degree == AngleMeasurement_Hours)
                            ? degree_hours_to_decimal_degrees(ra_long1_decimal)
                            : ra_long1_decimal;

  double ra_long1_rad = degrees_to_radians(ra_long1_deg);
  double dec_lat1_deg1 = degrees_minutes_seconds_to_decimal_degrees(
      dec_lat1_deg, dec_lat1_min, dec_lat1_sec);
  double dec_lat1_rad = degrees_to_radians(dec_lat1_deg1);

  double ra_long2_decimal =
      (hour_or_degree == AngleMeasurement_Hours)
          ? hms_dh(ra_long2_hour_deg, ra_long2_min, ra_long2_sec)
          : degrees_minutes_seconds_to_decimal_degrees(
                ra_long2_hour_deg, ra_long2_min, ra_long2_sec);
  double ra_long2_deg = (hour_or_degree == AngleMeasurement_Hours)
                            ? degree_hours_to_decimal_degrees(ra_long2_decimal)
                            : ra_long2_decimal;
  double ra_long2_rad = degrees_to_radians(ra_long2_deg);
  double dec_lat2_deg1 = degrees_minutes_seconds_to_decimal_degrees(
      dec_lat2_deg, dec_lat2_min, dec_lat2_sec);
  double dec_lat2_rad = degrees_to_radians(dec_lat2_deg1);

  double cos_d =
      sin(dec_lat1_rad) * sin(dec_lat2_rad) +
      cos(dec_lat1_rad) * cos(dec_lat2_rad) * cos(ra_long1_rad - ra_long2_rad);
  double d_rad = acos(cos_d);
  double d_deg = w_to_degrees(d_rad);

  double angle_deg = decimal_degrees_degrees(d_deg);
  double angle_min = decimal_degrees_minutes(d_deg);
  double angle_sec = decimal_degrees_seconds(d_deg);

  return (TAngle){angle_deg, angle_min, angle_sec};
}
