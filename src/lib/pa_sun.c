#include "pa_sun.h"
#include "pa_macros.h"
#include "pa_util.h"
#include <math.h>
#include <stdbool.h>

/**
 * Calculate approximate position of the sun for a local date and time.
 */
TSunPosition approximate_position_of_sun(double lct_hours, double lct_minutes,
                                         double lct_seconds, double local_day,
                                         int local_month, int local_year,
                                         bool is_daylight_saving,
                                         int zone_correction) {
  int daylight_saving = (is_daylight_saving == true) ? 1 : 0;

  double greenwich_date_day = ma_local_civil_time_greenwich_day(
      lct_hours, lct_minutes, lct_seconds, daylight_saving, zone_correction,
      local_day, local_month, local_year);
  int greenwich_date_month = ma_local_civil_time_greenwich_month(
      lct_hours, lct_minutes, lct_seconds, daylight_saving, zone_correction,
      local_day, local_month, local_year);
  int greenwich_date_year = ma_local_civil_time_greenwich_year(
      lct_hours, lct_minutes, lct_seconds, daylight_saving, zone_correction,
      local_day, local_month, local_year);
  double ut_hours = ma_local_civil_time_to_universal_time_macro(
      lct_hours, lct_minutes, lct_seconds, daylight_saving, zone_correction,
      local_day, local_month, local_year);
  double ut_days = ut_hours / 24;
  double jd_days =
      ma_civil_date_to_julian_date(greenwich_date_day, greenwich_date_month,
                                   greenwich_date_year) +
      ut_days;
  double d_days = jd_days - ma_civil_date_to_julian_date(0, 1, 2010);
  double n_deg = 360 * d_days / 365.242191;
  double m_deg1 = n_deg + ma_sun_e_long(0, 1, 2010) - ma_sun_peri(0, 1, 2010);
  double m_deg2 = m_deg1 - 360 * floor(m_deg1 / 360);
  double ec_deg =
      360 * ma_sun_ecc(0, 1, 2010) * sin(degrees_to_radians(m_deg2)) / M_PI;
  double ls_deg1 = n_deg + ec_deg + ma_sun_e_long(0, 1, 2010);
  double ls_deg2 = ls_deg1 - 360 * floor(ls_deg1 / 360);
  double ra_deg = ma_ec_ra(ls_deg2, 0, 0, 0, 0, 0, greenwich_date_day,
                           greenwich_date_month, greenwich_date_year);
  double ra_hours = ma_decimal_degrees_to_degree_hours(ra_deg);
  double dec_deg = ma_ec_dec(ls_deg2, 0, 0, 0, 0, 0, greenwich_date_day,
                             greenwich_date_month, greenwich_date_year);

  int sun_ra_hour = ma_decimal_hours_hour(ra_hours);
  int sun_ra_min = ma_decimal_hours_minute(ra_hours);
  double sun_ra_sec = ma_decimal_hours_second(ra_hours);
  double sun_dec_deg = ma_decimal_degrees_degrees(dec_deg);
  double sun_dec_min = ma_decimal_degrees_minutes(dec_deg);
  double sun_dec_sec = ma_decimal_degrees_seconds(dec_deg);

  return (TSunPosition){sun_ra_hour, sun_ra_min,  sun_ra_sec,
                        sun_dec_deg, sun_dec_min, sun_dec_sec};
}

/**
 * Calculate precise position of the sun for a local date and time.
 */
TSunPosition precise_position_of_sun(double lct_hours, double lct_minutes,
                                     double lct_seconds, double local_day,
                                     int local_month, int local_year,
                                     bool is_daylight_saving,
                                     int zone_correction) {
  int daylight_saving = (is_daylight_saving == true) ? 1 : 0;

  double g_day = ma_local_civil_time_greenwich_day(
      lct_hours, lct_minutes, lct_seconds, daylight_saving, zone_correction,
      local_day, local_month, local_year);
  int g_month = ma_local_civil_time_greenwich_month(
      lct_hours, lct_minutes, lct_seconds, daylight_saving, zone_correction,
      local_day, local_month, local_year);
  int g_year = ma_local_civil_time_greenwich_year(
      lct_hours, lct_minutes, lct_seconds, daylight_saving, zone_correction,
      local_day, local_month, local_year);
  double sun_ecliptic_longitude_deg =
      ma_sun_long(lct_hours, lct_minutes, lct_seconds, daylight_saving,
                  zone_correction, local_day, local_month, local_year);
  double ra_deg = ma_ec_ra(sun_ecliptic_longitude_deg, 0, 0, 0, 0, 0, g_day,
                           g_month, g_year);
  double ra_hours = ma_decimal_degrees_to_degree_hours(ra_deg);
  double dec_deg = ma_ec_dec(sun_ecliptic_longitude_deg, 0, 0, 0, 0, 0, g_day,
                             g_month, g_year);

  int sun_ra_hour = ma_decimal_hours_hour(ra_hours);
  int sun_ra_min = ma_decimal_hours_minute(ra_hours);
  double sun_ra_sec = ma_decimal_hours_second(ra_hours);
  double sun_dec_deg = ma_decimal_degrees_degrees(dec_deg);
  double sun_dec_min = ma_decimal_degrees_minutes(dec_deg);
  double sun_dec_sec = ma_decimal_degrees_seconds(dec_deg);

  return (TSunPosition){sun_ra_hour, sun_ra_min,  sun_ra_sec,
                        sun_dec_deg, sun_dec_min, sun_dec_sec};
}

/**
 * Calculate distance to the Sun (in km), and angular size.
 */
TSunDistanceSize
sun_distance_and_angular_size(double lct_hours, double lct_minutes,
                              double lct_seconds, double local_day,
                              int local_month, int local_year,
                              bool is_daylight_saving, int zone_correction) {
  int daylight_saving = is_daylight_saving ? 1 : 0;

  double g_day = ma_local_civil_time_greenwich_day(
      lct_hours, lct_minutes, lct_seconds, daylight_saving, zone_correction,
      local_day, local_month, local_year);
  int g_month = ma_local_civil_time_greenwich_month(
      lct_hours, lct_minutes, lct_seconds, daylight_saving, zone_correction,
      local_day, local_month, local_year);
  int g_year = ma_local_civil_time_greenwich_year(
      lct_hours, lct_minutes, lct_seconds, daylight_saving, zone_correction,
      local_day, local_month, local_year);
  double true_anomaly_deg =
      ma_sun_true_anomaly(lct_hours, lct_minutes, lct_seconds, daylight_saving,
                          zone_correction, local_day, local_month, local_year);
  double true_anomaly_rad = degrees_to_radians(true_anomaly_deg);
  double eccentricity = ma_sun_ecc(g_day, g_month, g_year);
  double f = (1 + eccentricity * cos(true_anomaly_rad)) /
             (1 - eccentricity * eccentricity);
  double r_km = 149598500 / f;
  double theta_deg = f * 0.533128;

  double sun_dist_km = dround(r_km, 0);
  double sun_ang_size_deg = ma_decimal_degrees_degrees(theta_deg);
  double sun_ang_size_min = ma_decimal_degrees_minutes(theta_deg);
  double sun_ang_size_sec = ma_decimal_degrees_seconds(theta_deg);

  return (TSunDistanceSize){sun_dist_km, sun_ang_size_deg, sun_ang_size_min,
                            sun_ang_size_sec};
}

/**
 * Calculate local sunrise and sunset.
 */
TSunriseSunsetInfo sunrise_and_sunset(double local_day, int local_month,
                                      int local_year, bool is_daylight_saving,
                                      int zone_correction,
                                      double geographical_long_deg,
                                      double geographical_lat_deg) {
  int daylight_saving = is_daylight_saving ? 1 : 0;

  double local_sunrise_hours = ma_sunrise_lct(
      local_day, local_month, local_year, daylight_saving, zone_correction,
      geographical_long_deg, geographical_lat_deg);
  double local_sunset_hours = ma_sunset_lct(
      local_day, local_month, local_year, daylight_saving, zone_correction,
      geographical_long_deg, geographical_lat_deg);

  enum RiseSetStatus sun_rise_set_status =
      ma_e_sun_rs(local_day, local_month, local_year, daylight_saving,
                  zone_correction, geographical_long_deg, geographical_lat_deg);

  double adjusted_sunrise_hours = local_sunrise_hours + 0.008333;
  double adjusted_sunset_hours = local_sunset_hours + 0.008333;

  double azimuth_of_sunrise_deg1 = ma_sunrise_az(
      local_day, local_month, local_year, daylight_saving, zone_correction,
      geographical_long_deg, geographical_lat_deg);
  double azimuth_of_sunset_deg1 = ma_sunset_az(
      local_day, local_month, local_year, daylight_saving, zone_correction,
      geographical_long_deg, geographical_lat_deg);

  int local_sunrise_hour = sun_rise_set_status == RiseSetStatus_OK
                               ? ma_decimal_hours_hour(adjusted_sunrise_hours)
                               : 0;
  int local_sunrise_minute =
      sun_rise_set_status == RiseSetStatus_Ok
          ? ma_decimal_hours_minute(adjusted_sunrise_hours)
          : 0;

  int local_sunset_hour = sun_rise_set_status == RiseSetStatus_Ok
                              ? ma_decimal_hours_hour(adjusted_sunset_hours)
                              : 0;
  int local_sunset_minute = sun_rise_set_status == RiseSetStatus_Ok
                                ? ma_decimal_hours_minute(adjusted_sunset_hours)
                                : 0;

  double azimuth_of_sunrise_deg = sun_rise_set_status == RiseSetStatus_Ok
                                      ? dround(azimuth_of_sunrise_deg1, 2)
                                      : 0;
  double azimuth_of_sunset_deg = sun_rise_set_status == RiseSetStatus_Ok
                                     ? dround(azimuth_of_sunset_deg1, 2)
                                     : 0;

  enum RiseSetStatus status = sun_rise_set_status;

  return (TSunriseSunsetInfo){local_sunrise_hour,
                              local_sunrise_minute,
                              local_sunset_hour,
                              local_sunset_minute,
                              azimuth_of_sunrise_deg,
                              azimuth_of_sunset_deg,
                              status};
}
