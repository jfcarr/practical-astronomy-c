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

/**
 * \brief Calculate rising and setting times for an object.
 *
 * @return TRiseSet <rs_status, ut_rise_hour, ut_rise_min, ut_set_hour,
 * ut_set_min, az_rise, az_set>
 */
TRiseSet rising_and_setting(double ra_hours, double ra_minutes,
                            double ra_seconds, double dec_deg, double dec_min,
                            double dec_sec, double gw_date_day,
                            int gw_date_month, int gw_date_year,
                            double geog_long_deg, double geog_lat_deg,
                            double vert_shift_deg) {
  double ra_hours1 = hms_dh(ra_hours, ra_minutes, ra_seconds);
  double dec_rad = degrees_to_radians(
      degrees_minutes_seconds_to_decimal_degrees(dec_deg, dec_min, dec_sec));
  double vertical_displ_radians = degrees_to_radians(vert_shift_deg);
  double geo_lat_radians = degrees_to_radians(geog_lat_deg);
  double cos_h =
      -(sin(vertical_displ_radians) + sin(geo_lat_radians) * sin(dec_rad)) /
      (cos(geo_lat_radians) * cos(dec_rad));
  double h_hours = decimal_degrees_to_degree_hours(w_to_degrees(acos(cos_h)));
  double lst_rise_hours =
      (ra_hours1 - h_hours) - 24 * floor((ra_hours1 - h_hours) / 24);
  double lst_set_hours =
      (ra_hours1 + h_hours) - 24 * floor((ra_hours1 + h_hours) / 24);
  double a_deg = w_to_degrees(
      acos((sin(dec_rad) + sin(vertical_displ_radians) * sin(geo_lat_radians)) /
           (cos(vertical_displ_radians) * cos(geo_lat_radians))));
  double az_rise_deg = a_deg - 360 * floor(a_deg / 360);
  double az_set_deg = (360 - a_deg) - 360 * floor((360 - a_deg) / 360);
  double ut_rise_hours1 = greenwich_sidereal_time_to_universal_time_macro(
      local_sidereal_time_to_greenwich_sidereal_time_macro(lst_rise_hours, 0, 0,
                                                           geog_long_deg),
      0, 0, gw_date_day, gw_date_month, gw_date_year);
  double ut_set_hours1 = greenwich_sidereal_time_to_universal_time_macro(
      local_sidereal_time_to_greenwich_sidereal_time_macro(lst_set_hours, 0, 0,
                                                           geog_long_deg),
      0, 0, gw_date_day, gw_date_month, gw_date_year);
  double ut_rise_adjusted_hours = ut_rise_hours1 + 0.008333;
  double ut_set_adjusted_hours = ut_set_hours1 + 0.008333;

  TRiseSetStatus rs_status = RiseSetStatus_Ok;
  if (cos_h > 1)
    rs_status = RiseSetStatus_NeverRises;
  if (cos_h < -1)
    rs_status = RiseSetStatus_Circumpolar;

  int ut_rise_hour = (rs_status == RiseSetStatus_Ok)
                         ? decimal_hours_hour(ut_rise_adjusted_hours)
                         : 0;
  int ut_rise_min = (rs_status == RiseSetStatus_Ok)
                        ? decimal_hours_minute(ut_rise_adjusted_hours)
                        : 0;
  int ut_set_hour = (rs_status == RiseSetStatus_Ok)
                        ? decimal_hours_hour(ut_set_adjusted_hours)
                        : 0;
  int ut_set_min = (rs_status == RiseSetStatus_Ok)
                       ? decimal_hours_minute(ut_set_adjusted_hours)
                       : 0;
  double az_rise = (rs_status == RiseSetStatus_Ok) ? dround(az_rise_deg, 2) : 0;
  double az_set = (rs_status == RiseSetStatus_Ok) ? dround(az_set_deg, 2) : 0;

  return (TRiseSet){rs_status,  ut_rise_hour, ut_rise_min, ut_set_hour,
                    ut_set_min, az_rise,      az_set};
}

/**
 * Calculate precession (corrected coordinates between two epochs)
 *
 * @return TCorrectedPrecession<double corrected_ra_hour, double
 * corrected_ra_minutes, double corrected_ra_seconds, double corrected_dec_deg,
 * double corrected_dec_minutes, double corrected_dec_seconds>
 */
TCorrectedPrecession
correct_for_precession(double ra_hour, double ra_minutes, double ra_seconds,
                       double dec_deg, double dec_minutes, double dec_seconds,
                       double epoch1_day, int epoch1_month, int epoch1_year,
                       double epoch2_day, int epoch2_month, int epoch2_year) {
  double ra1_rad = degrees_to_radians(
      degree_hours_to_decimal_degrees(hms_dh(ra_hour, ra_minutes, ra_seconds)));
  double dec1_rad =
      degrees_to_radians(degrees_minutes_seconds_to_decimal_degrees(
          dec_deg, dec_minutes, dec_seconds));
  double t_centuries =
      (civil_date_to_julian_date(epoch1_day, epoch1_month, epoch1_year) -
       2415020) /
      36525;
  double m_sec = 3.07234 + (0.00186 * t_centuries);
  double n_arcsec = 20.0468 - (0.0085 * t_centuries);
  double n_years =
      (civil_date_to_julian_date(epoch2_day, epoch2_month, epoch2_year) -
       civil_date_to_julian_date(epoch1_day, epoch1_month, epoch1_year)) /
      365.25;
  double s1_hours =
      ((m_sec + (n_arcsec * sin(ra1_rad) * tan(dec1_rad) / 15)) * n_years) /
      3600;
  double ra2_hours = hms_dh(ra_hour, ra_minutes, ra_seconds) + s1_hours;
  double s2_deg = (n_arcsec * cos(ra1_rad) * n_years) / 3600;
  double dec2_deg = degrees_minutes_seconds_to_decimal_degrees(
                        dec_deg, dec_minutes, dec_seconds) +
                    s2_deg;

  int corrected_ra_hour = decimal_hours_hour(ra2_hours);
  int corrected_ra_minutes = decimal_hours_minute(ra2_hours);
  double corrected_ra_seconds = decimal_hours_second(ra2_hours);
  double corrected_dec_deg = decimal_degrees_degrees(dec2_deg);
  double corrected_dec_minutes = decimal_degrees_minutes(dec2_deg);
  double corrected_dec_seconds = decimal_degrees_seconds(dec2_deg);

  return (TCorrectedPrecession){corrected_ra_hour,     corrected_ra_minutes,
                                corrected_ra_seconds,  corrected_dec_deg,
                                corrected_dec_minutes, corrected_dec_seconds};
}

/**
 * Calculate nutation for two values: ecliptic longitude and obliquity,
 * for a Greenwich date.
 *
 * @return TNutation<nutation in ecliptic longitude (degrees), nutation in
 * obliquity (degrees)>
 */
TNutation nutation_in_ecliptic_longitude_and_obliquity(double greenwich_day,
                                                       int greenwich_month,
                                                       int greenwich_year) {
  double jd_days =
      civil_date_to_julian_date(greenwich_day, greenwich_month, greenwich_year);
  double t_centuries = (jd_days - 2415020) / 36525;
  double a_deg = 100.0021358 * t_centuries;
  double l1_deg = 279.6967 + (0.000303 * t_centuries * t_centuries);
  double l_deg1 = l1_deg + 360 * (a_deg - floor(a_deg));
  double l_deg2 = l_deg1 - 360 * floor(l_deg1 / 360);
  double l_rad = degrees_to_radians(l_deg2);
  double b_deg = 5.372617 * t_centuries;
  double n_deg1 = 259.1833 - 360 * (b_deg - floor(b_deg));
  double n_deg2 = n_deg1 - 360 * (floor(n_deg1 / 360));
  double n_rad = degrees_to_radians(n_deg2);
  double nut_in_long_arcsec = -17.2 * sin(n_rad) - 1.3 * sin(2 * l_rad);
  double nut_in_obl_arcsec = 9.2 * cos(n_rad) + 0.5 * cos(2 * l_rad);

  double nut_in_long_deg = nut_in_long_arcsec / 3600;
  double nut_in_obl_deg = nut_in_obl_arcsec / 3600;

  return (TNutation){nut_in_long_deg, nut_in_obl_deg};
}

/**
 * Correct ecliptic coordinates for the effects of aberration.
 *
 * @return TCorrectedEclipticCoordinates<apparent ecliptic longitude (degrees,
 * minutes, seconds), apparent ecliptic latitude (degrees, minutes, seconds)>
 */
TCorrectedEclipticCoordinates
correct_for_aberration(double ut_hour, double ut_minutes, double ut_seconds,
                       double gw_day, int gw_month, int gw_year,
                       double true_ecl_long_deg, double true_ecl_long_min,
                       double true_ecl_long_sec, double true_ecl_lat_deg,
                       double true_ecl_lat_min, double true_ecl_lat_sec) {
  double true_long_deg = degrees_minutes_seconds_to_decimal_degrees(
      true_ecl_long_deg, true_ecl_long_min, true_ecl_long_sec);
  double true_lat_deg = degrees_minutes_seconds_to_decimal_degrees(
      true_ecl_lat_deg, true_ecl_lat_min, true_ecl_lat_sec);
  double sun_true_long_deg = sun_long(ut_hour, ut_minutes, ut_seconds, 0, 0,
                                      gw_day, gw_month, gw_year);
  double d_long_arcsec =
      -20.5 * cos(degrees_to_radians(sun_true_long_deg - true_long_deg)) /
      cos(degrees_to_radians(true_lat_deg));
  double d_lat_arcsec =
      -20.5 * sin(degrees_to_radians(sun_true_long_deg - true_long_deg)) *
      sin(degrees_to_radians(true_lat_deg));
  double apparent_long_deg = true_long_deg + (d_long_arcsec / 3600);
  double apparent_lat_deg = true_lat_deg + (d_lat_arcsec / 3600);

  double apparent_ecl_long_deg = decimal_degrees_degrees(apparent_long_deg);
  double apparent_ecl_long_min = decimal_degrees_minutes(apparent_long_deg);
  double apparent_ecl_long_sec = decimal_degrees_seconds(apparent_long_deg);
  double apparent_ecl_lat_deg = decimal_degrees_degrees(apparent_lat_deg);
  double apparent_ecl_lat_min = decimal_degrees_minutes(apparent_lat_deg);
  double apparent_ecl_lat_sec = decimal_degrees_seconds(apparent_lat_deg);

  return (TCorrectedEclipticCoordinates){
      apparent_ecl_long_deg, apparent_ecl_long_min, apparent_ecl_long_sec,
      apparent_ecl_lat_deg,  apparent_ecl_lat_min,  apparent_ecl_lat_sec};
}

/**
 * Calculate corrected RA/Dec, accounting for atmospheric refraction.
 *
 * NOTE: Valid values for coordinate_type are "TRUE" and "APPARENT".
 *
 * @return TCorrectedRefraction <corrected RA hours,minutes,seconds and
 * corrected Declination degrees,minutes,seconds>
 */
TCorrectedRefraction atmospheric_refraction(
    double true_ra_hour, double true_ra_min, double true_ra_sec,
    double true_dec_deg, double true_dec_min, double true_dec_sec,
    TCoordinateType coordinate_type1, double geog_long_deg, double geog_lat_deg,
    int daylight_saving_hours, int timezone_hours, double lcd_day,
    int lcd_month, int lcd_year, double lct_hour, double lct_min,
    double lct_sec, double atmospheric_pressure_mbar,
    double atmospheric_temperature_celsius) {
  double ha_hour = right_ascension_to_hour_angle_macro(
      true_ra_hour, true_ra_min, true_ra_sec, lct_hour, lct_min, lct_sec,
      daylight_saving_hours, timezone_hours, lcd_day, lcd_month, lcd_year,
      geog_long_deg);
  double azimuth_deg = equatorial_coordinates_to_azimuth(
      ha_hour, 0, 0, true_dec_deg, true_dec_min, true_dec_sec, geog_lat_deg);
  double altitude_deg = equatorial_coordinates_to_altitude(
      ha_hour, 0, 0, true_dec_deg, true_dec_min, true_dec_sec, geog_lat_deg);
  double corrected_altitude_deg =
      refract(altitude_deg, coordinate_type1, atmospheric_pressure_mbar,
              atmospheric_temperature_celsius);

  double corrected_ha_hour = horizon_coordinates_to_hour_angle(
      azimuth_deg, 0, 0, corrected_altitude_deg, 0, 0, geog_lat_deg);
  double corrected_ra_hour1 = hour_angle_to_right_ascension_macro(
      corrected_ha_hour, 0, 0, lct_hour, lct_min, lct_sec,
      daylight_saving_hours, timezone_hours, lcd_day, lcd_month, lcd_year,
      geog_long_deg);
  double corrected_dec_deg1 = horizon_coordinates_to_declination(
      azimuth_deg, 0, 0, corrected_altitude_deg, 0, 0, geog_lat_deg);

  int corrected_ra_hour = decimal_hours_hour(corrected_ra_hour1);
  int corrected_ra_min = decimal_hours_minute(corrected_ra_hour1);
  double corrected_ra_sec = decimal_hours_second(corrected_ra_hour1);
  double corrected_dec_deg = decimal_degrees_degrees(corrected_dec_deg1);
  double corrected_dec_min = decimal_degrees_minutes(corrected_dec_deg1);
  double corrected_dec_sec = decimal_degrees_seconds(corrected_dec_deg1);

  return (TCorrectedRefraction){corrected_ra_hour, corrected_ra_min,
                                corrected_ra_sec,  corrected_dec_deg,
                                corrected_dec_min, corrected_dec_sec};
}

/**
 * \brief Calculate corrected RA/Dec, accounting for geocentric parallax.
 *
 * @return TCorrectedParallax<corrected RA hours,minutes,seconds and corrected
 * Declination degrees,minutes,seconds>
 */
TCorrectedParallax corrections_for_geocentric_parallax(
    double ra_hour, double ra_min, double ra_sec, double dec_deg,
    double dec_min, double dec_sec, TCoordinateType coordinate_type,
    double equatorial_hor_parallax_deg, double geog_long_deg,
    double geog_lat_deg, double height_m, int daylight_saving,
    int timezone_hours, double lcd_day, int lcd_month, int lcd_year,
    double lct_hour, double lct_min, double lct_sec) {
  double ha_hours = right_ascension_to_hour_angle_macro(
      ra_hour, ra_min, ra_sec, lct_hour, lct_min, lct_sec, daylight_saving,
      timezone_hours, lcd_day, lcd_month, lcd_year, geog_long_deg);

  double corrected_ha_hours =
      parallax_ha(ha_hours, 0, 0, dec_deg, dec_min, dec_sec, coordinate_type,
                  geog_lat_deg, height_m, equatorial_hor_parallax_deg);

  double corrected_ra_hours = hour_angle_to_right_ascension_macro(
      corrected_ha_hours, 0, 0, lct_hour, lct_min, lct_sec, daylight_saving,
      timezone_hours, lcd_day, lcd_month, lcd_year, geog_long_deg);

  double corrected_dec_deg1 =
      parallax_dec(ha_hours, 0, 0, dec_deg, dec_min, dec_sec, coordinate_type,
                   geog_lat_deg, height_m, equatorial_hor_parallax_deg);

  int c_ra_hour = decimal_hours_hour(corrected_ra_hours);
  int c_ra_min = decimal_hours_minute(corrected_ra_hours);
  double c_ra_sec = decimal_hours_second(corrected_ra_hours);
  double c_dec_deg = decimal_degrees_degrees(corrected_dec_deg1);
  double c_dec_min = decimal_degrees_minutes(corrected_dec_deg1);
  double c_dec_sec = decimal_degrees_seconds(corrected_dec_deg1);

  return (TCorrectedParallax){c_ra_hour, c_ra_min,  c_ra_sec,
                              c_dec_deg, c_dec_min, c_dec_sec};
}

/**
 * Calculate heliographic coordinates for a given Greenwich date, with a given
 * heliographic position angle and heliographic displacement in arc minutes.
 *
 * @return THeliographicCoordinates <heliographic longitude and heliographic
 * latitude, in degrees>
 */
THeliographicCoordinates
heliographic_coordinates(double helio_position_angle_deg,
                         double helio_displacement_arcmin, double gwdate_day,
                         int gwdate_month, int gwdate_year) {
  double julian_date_days =
      civil_date_to_julian_date(gwdate_day, gwdate_month, gwdate_year);
  double t_centuries = (julian_date_days - 2415020) / 36525;
  double long_asc_node_deg =
      degrees_minutes_seconds_to_decimal_degrees(74, 22, 0) +
      (84 * t_centuries / 60);
  double sun_long_deg =
      sun_long(0, 0, 0, 0, 0, gwdate_day, gwdate_month, gwdate_year);
  double y = sin(degrees_to_radians(long_asc_node_deg - sun_long_deg)) *
             cos(degrees_to_radians(
                 degrees_minutes_seconds_to_decimal_degrees(7, 15, 0)));
  double x = -cos(degrees_to_radians(long_asc_node_deg - sun_long_deg));
  double a_deg = w_to_degrees(atan2(y, x));
  double m_deg1 = 360 - (360 * (julian_date_days - 2398220) / 25.38);
  double m_deg2 = m_deg1 - 360 * floor(m_deg1 / 360);
  double l0_deg1 = m_deg2 + a_deg;
  double b0_rad =
      asin(sin(degrees_to_radians(sun_long_deg - long_asc_node_deg)) *
           sin(degrees_to_radians(
               degrees_minutes_seconds_to_decimal_degrees(7, 15, 0))));
  double theta1_rad = atan(
      -cos(degrees_to_radians(sun_long_deg)) *
      tan(degrees_to_radians(obliq(gwdate_day, gwdate_month, gwdate_year))));
  double theta2_rad =
      atan(-cos(degrees_to_radians(long_asc_node_deg - sun_long_deg)) *
           tan(degrees_to_radians(
               degrees_minutes_seconds_to_decimal_degrees(7, 15, 0))));
  double p_deg = w_to_degrees(theta1_rad + theta2_rad);
  double rho1_deg = helio_displacement_arcmin / 60;
  double rho_rad =
      asin(2 * rho1_deg /
           sun_dia(0, 0, 0, 0, 0, gwdate_day, gwdate_month, gwdate_year)) -
      degrees_to_radians(rho1_deg);
  double b_rad =
      asin(sin(b0_rad) * cos(rho_rad) +
           cos(b0_rad) * sin(rho_rad) *
               cos(degrees_to_radians(p_deg - helio_position_angle_deg)));
  double b_deg = w_to_degrees(b_rad);
  double l_deg1 =
      w_to_degrees(
          asin(sin(rho_rad) *
               sin(degrees_to_radians(p_deg - helio_position_angle_deg)) /
               cos(b_rad))) +
      l0_deg1;
  double l_deg2 = l_deg1 - 360 * floor(l_deg1 / 360);

  double helio_long_deg = dround(l_deg2, 2);
  double helio_lat_deg = dround(b_deg, 2);

  return (THeliographicCoordinates){helio_long_deg, helio_lat_deg};
}

/**
 * Calculate carrington rotation number for a Greenwich date
 *
 * @return carrington rotation number
 */
int carrington_rotation_number(double gwdate_day, int gwdate_month,
                               int gwdate_year) {
  double julian_date_days =
      civil_date_to_julian_date(gwdate_day, gwdate_month, gwdate_year);

  int crn = 1690 + (int)dround((julian_date_days - 2444235.34) / 27.2753, 0);

  return crn;
}

/**
 * Calculate selenographic (lunar) coordinates (sub-Earth)
 *
 * @return TSelenographicSubEarthCoordinates <sub-earth longitude, sub-earth
 * latitude, and position angle of pole>
 */
TSelenographicSubEarthCoordinates selenographic_coordinates1(double gwdate_day,
                                                             int gwdate_month,
                                                             int gwdate_year) {
  double julian_date_days =
      civil_date_to_julian_date(gwdate_day, gwdate_month, gwdate_year);
  double t_centuries = (julian_date_days - 2451545) / 36525;
  double long_asc_node_deg = 125.044522 - 1934.136261 * t_centuries;
  double f1 = 93.27191 + 483202.0175 * t_centuries;
  double f2 = f1 - 360 * floor(f1 / 360);
  double geocentric_moon_long_deg =
      moon_longitude(0, 0, 0, 0, 0, gwdate_day, gwdate_month, gwdate_year);
  double geocentric_moon_lat_rad = degrees_to_radians(
      moon_latitude(0, 0, 0, 0, 0, gwdate_day, gwdate_month, gwdate_year));
  double inclination_rad = degrees_to_radians(
      degrees_minutes_seconds_to_decimal_degrees(1, 32, 32.7));
  double node_long_rad =
      degrees_to_radians(long_asc_node_deg - geocentric_moon_long_deg);
  double sin_be =
      -cos(inclination_rad) * sin(geocentric_moon_lat_rad) +
      sin(inclination_rad) * cos(geocentric_moon_lat_rad) * sin(node_long_rad);
  double sub_earth_lat_deg = w_to_degrees(asin(sin_be));
  double a_rad = atan2(-sin(geocentric_moon_lat_rad) * sin(inclination_rad) -
                           cos(geocentric_moon_lat_rad) * cos(inclination_rad) *
                               sin(node_long_rad),
                       cos(geocentric_moon_lat_rad) * cos(node_long_rad));
  double a_deg = w_to_degrees(a_rad);
  double sub_earth_long_deg1 = a_deg - f2;
  double sub_earth_long_deg2 =
      sub_earth_long_deg1 - 360 * floor(sub_earth_long_deg1 / 360);
  double sub_earth_long_deg3 = (sub_earth_long_deg2 > 180)
                                   ? (sub_earth_long_deg2 - 360)
                                   : sub_earth_long_deg2;
  double c1_rad = atan(cos(node_long_rad) * sin(inclination_rad) /
                       (cos(geocentric_moon_lat_rad) * cos(inclination_rad) +
                        sin(geocentric_moon_lat_rad) * sin(inclination_rad) *
                            sin(node_long_rad)));
  double obliquity_rad =
      degrees_to_radians(obliq(gwdate_day, gwdate_month, gwdate_year));
  double c2_rad = atan(sin(obliquity_rad) *
                       cos(degrees_to_radians(geocentric_moon_long_deg)) /
                       (sin(obliquity_rad) * sin(geocentric_moon_lat_rad) *
                            sin(degrees_to_radians(geocentric_moon_long_deg)) -
                        cos(obliquity_rad) * cos(geocentric_moon_lat_rad)));
  double c_deg = w_to_degrees(c1_rad + c2_rad);

  double sub_earth_longitude = dround(sub_earth_long_deg3, 2);
  double sub_earth_latitude = dround(sub_earth_lat_deg, 2);
  double position_angle_of_pole = dround(c_deg, 2);

  return (TSelenographicSubEarthCoordinates){
      sub_earth_longitude, sub_earth_latitude, position_angle_of_pole};
}

/**
 * Calculate selenographic (lunar) coordinates (sub-Solar)
 *
 * @return TSelenographicSubSolarCoordinates <sub-solar longitude, sub-solar
 * colongitude, and sub-solar latitude>
 */
TSelenographicSubSolarCoordinates selenographic_coordinates2(double gwdate_day,
                                                             int gwdate_month,
                                                             int gwdate_year) {
  double julian_date_days =
      civil_date_to_julian_date(gwdate_day, gwdate_month, gwdate_year);
  double t_centuries = (julian_date_days - 2451545) / 36525;
  double long_asc_node_deg = 125.044522 - 1934.136261 * t_centuries;
  double f1 = 93.27191 + 483202.0175 * t_centuries;
  double f2 = f1 - 360 * floor(f1 / 360);
  double sun_geocentric_long_deg =
      sun_long(0, 0, 0, 0, 0, gwdate_day, gwdate_month, gwdate_year);
  double moon_equ_hor_parallax_arc_min =
      moon_horizontal_parallax(0, 0, 0, 0, 0, gwdate_day, gwdate_month,
                               gwdate_year) *
      60;
  double sun_earth_dist_au =
      sun_dist(0, 0, 0, 0, 0, gwdate_day, gwdate_month, gwdate_year);
  double geocentric_moon_lat_rad = degrees_to_radians(
      moon_latitude(0, 0, 0, 0, 0, gwdate_day, gwdate_month, gwdate_year));
  double geocentric_moon_long_deg =
      moon_longitude(0, 0, 0, 0, 0, gwdate_day, gwdate_month, gwdate_year);
  double adjusted_moon_long_deg =
      sun_geocentric_long_deg + 180 +
      (26.4 * cos(geocentric_moon_lat_rad) *
       sin(degrees_to_radians(sun_geocentric_long_deg -
                              geocentric_moon_long_deg)) /
       (moon_equ_hor_parallax_arc_min * sun_earth_dist_au));
  double adjusted_moon_lat_rad =
      0.14666 * geocentric_moon_lat_rad /
      (moon_equ_hor_parallax_arc_min * sun_earth_dist_au);
  double inclination_rad = degrees_to_radians(
      degrees_minutes_seconds_to_decimal_degrees(1, 32, 32.7));
  double node_long_rad =
      degrees_to_radians(long_asc_node_deg - adjusted_moon_long_deg);
  double sin_bs =
      -cos(inclination_rad) * sin(adjusted_moon_lat_rad) +
      sin(inclination_rad) * cos(adjusted_moon_lat_rad) * sin(node_long_rad);
  double sub_solar_lat_deg = w_to_degrees(asin(sin_bs));
  double a_rad = atan2(-sin(adjusted_moon_lat_rad) * sin(inclination_rad) -
                           cos(adjusted_moon_lat_rad) * cos(inclination_rad) *
                               sin(node_long_rad),
                       cos(adjusted_moon_lat_rad) * cos(node_long_rad));
  double a_deg = w_to_degrees(a_rad);
  double sub_solar_long_deg1 = a_deg - f2;
  double sub_solar_long_deg2 =
      sub_solar_long_deg1 - 360 * floor(sub_solar_long_deg1 / 360);
  double sub_solar_long_deg3 = (sub_solar_long_deg2 > 180)
                                   ? sub_solar_long_deg2 - 360
                                   : sub_solar_long_deg2;
  double sub_solar_colong_deg = 90 - sub_solar_long_deg3;

  double sub_solar_longitude = dround(sub_solar_long_deg3, 2);
  double sub_solar_colongitude = dround(sub_solar_colong_deg, 2);
  double sub_solar_latitude = dround(sub_solar_lat_deg, 2);

  return (TSelenographicSubSolarCoordinates){
      sub_solar_longitude, sub_solar_colongitude, sub_solar_latitude};
}
