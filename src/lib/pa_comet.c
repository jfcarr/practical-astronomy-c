#include "pa_comet.h"
#include "pa_comet_data.h"
#include "pa_macros.h"
#include "pa_util.h"
#include <math.h>
#include <stdbool.h>

/**
 * Calculate position of an elliptical comet.
 */
TCometPosition
position_of_elliptical_comet(double lct_hour, double lct_min, double lct_sec,
                             bool is_daylight_saving, int zone_correction_hours,
                             double local_date_day, int local_date_month,
                             int local_date_year, char *comet_name) {
  int daylight_saving = is_daylight_saving ? 1 : 0;

  double greenwich_date_day = ma_local_civil_time_greenwich_day(
      lct_hour, lct_min, lct_sec, daylight_saving, zone_correction_hours,
      local_date_day, local_date_month, local_date_year);
  int greenwich_date_month = ma_local_civil_time_greenwich_month(
      lct_hour, lct_min, lct_sec, daylight_saving, zone_correction_hours,
      local_date_day, local_date_month, local_date_year);
  int greenwich_date_year = ma_local_civil_time_greenwich_year(
      lct_hour, lct_min, lct_sec, daylight_saving, zone_correction_hours,
      local_date_day, local_date_month, local_date_year);

  struct CometRecord comet_info = get_comet_data(comet_name);

  double time_since_epoch_years =
      (ma_civil_date_to_julian_date(greenwich_date_day, greenwich_date_month,
                                    greenwich_date_year) -
       ma_civil_date_to_julian_date(0.0, 1, greenwich_date_year)) /
          365.242191 +
      greenwich_date_year - comet_info.epoch_EpochOfPerihelion;
  double mc_deg =
      360 * time_since_epoch_years / comet_info.period_PeriodOfOrbit;
  double mc_rad = degrees_to_radians(mc_deg - 360 * floor(mc_deg / 360));
  double eccentricity = comet_info.ecc_EccentricityOfOrbit;
  double true_anomaly_deg = ma_degrees(ma_true_anomaly(mc_rad, eccentricity));
  double lc_deg = true_anomaly_deg + comet_info.peri_LongitudeOfPerihelion;
  double r_au = comet_info.axis_SemiMajorAxisOfOrbit *
                (1 - eccentricity * eccentricity) /
                (1 + eccentricity * cos(degrees_to_radians(true_anomaly_deg)));
  double lc_node_rad =
      degrees_to_radians(lc_deg - comet_info.node_LongitudeOfAscendingNode);
  double psi_rad =
      asin(sin(lc_node_rad) *
           sin(degrees_to_radians(comet_info.incl_InclinationOfOrbit)));

  double y = sin(lc_node_rad) *
             cos(degrees_to_radians(comet_info.incl_InclinationOfOrbit));
  double x = cos(lc_node_rad);

  double ld_deg =
      ma_degrees(atan2(y, x)) + comet_info.node_LongitudeOfAscendingNode;
  double rd_au = r_au * cos(psi_rad);

  double earth_longitude_le_deg =
      ma_sun_long(lct_hour, lct_min, lct_sec, daylight_saving,
                  zone_correction_hours, local_date_day, local_date_month,
                  local_date_year) +
      180.0;
  double earth_radius_vector_au = ma_sun_dist(
      lct_hour, lct_min, lct_sec, daylight_saving, zone_correction_hours,
      local_date_day, local_date_month, local_date_year);

  double le_ld_rad = degrees_to_radians(earth_longitude_le_deg - ld_deg);
  double a_rad = (rd_au < earth_radius_vector_au)
                     ? atan2((rd_au * sin(le_ld_rad)),
                             (earth_radius_vector_au - rd_au * cos(le_ld_rad)))
                     : atan2((earth_radius_vector_au * sin(-le_ld_rad)),
                             (rd_au - earth_radius_vector_au * cos(le_ld_rad)));

  double comet_long_deg1 =
      (rd_au < earth_radius_vector_au)
          ? 180.0 + earth_longitude_le_deg + ma_degrees(a_rad)
          : ma_degrees(a_rad) + ld_deg;
  double comet_long_deg = comet_long_deg1 - 360 * floor(comet_long_deg1 / 360);
  double comet_lat_deg =
      ma_degrees(atan(rd_au * tan(psi_rad) *
                      sin(degrees_to_radians((comet_long_deg1 - ld_deg))) /
                      (earth_radius_vector_au * sin(-le_ld_rad))));
  double comet_ra_hours1 = ma_decimal_degrees_to_degree_hours(
      ma_ec_ra(comet_long_deg, 0, 0, comet_lat_deg, 0, 0, greenwich_date_day,
               greenwich_date_month, greenwich_date_year));
  double comet_dec_deg1 =
      ma_ec_dec(comet_long_deg, 0, 0, comet_lat_deg, 0, 0, greenwich_date_day,
                greenwich_date_month, greenwich_date_year);
  double comet_distance_au =
      sqrt(pow(earth_radius_vector_au, 2) + pow(r_au, 2) -
           2.0 * earth_radius_vector_au * r_au *
               cos(degrees_to_radians((lc_deg - earth_longitude_le_deg))) *
               cos(psi_rad));

  int comet_ra_hour = ma_decimal_hours_hour(comet_ra_hours1 + 0.008333);
  int comet_ra_min = ma_decimal_hours_minute(comet_ra_hours1 + 0.008333);
  double comet_dec_deg = ma_decimal_degrees_degrees(comet_dec_deg1 + 0.008333);
  double comet_dec_min = ma_decimal_degrees_minutes(comet_dec_deg1 + 0.008333);
  double comet_dist_earth = dround(comet_distance_au, 2);

  return (TCometPosition){comet_ra_hour, comet_ra_min, comet_dec_deg,
                          comet_dec_min, comet_dist_earth};
}

/**
 * Calculate position of a parabolic comet.
 */
TCometPosition
position_of_parabolic_comet(double lct_hour, double lct_min, double lct_sec,
                            bool is_daylight_saving, int zone_correction_hours,
                            double local_date_day, int local_date_month,
                            int local_date_year, char *comet_name) {
  int daylight_saving = is_daylight_saving ? 1 : 0;

  double greenwich_date_day = ma_local_civil_time_greenwich_day(
      lct_hour, lct_min, lct_sec, daylight_saving, zone_correction_hours,
      local_date_day, local_date_month, local_date_year);
  int greenwich_date_month = ma_local_civil_time_greenwich_month(
      lct_hour, lct_min, lct_sec, daylight_saving, zone_correction_hours,
      local_date_day, local_date_month, local_date_year);
  int greenwich_date_year = ma_local_civil_time_greenwich_year(
      lct_hour, lct_min, lct_sec, daylight_saving, zone_correction_hours,
      local_date_day, local_date_month, local_date_year);

  struct CometDataParabolic comet_info = get_comet_data_parabolic(comet_name);

  double perihelion_epoch_day = comet_info.epoch_peri_day;
  int perihelion_epoch_month = comet_info.epoch_peri_month;
  int perihelion_epoch_year = comet_info.epoch_peri_year;
  double q_au = comet_info.peri_dist;
  double inclination_deg = comet_info.incl;
  double perihelion_deg = comet_info.arg_peri;
  double node_deg = comet_info.node;

  TCometLongLatDist comet_long_lat_dist = ma_p_comet_long_lat_dist(
      lct_hour, lct_min, lct_sec, daylight_saving, zone_correction_hours,
      local_date_day, local_date_month, local_date_year, perihelion_epoch_day,
      perihelion_epoch_month, perihelion_epoch_year, q_au, inclination_deg,
      perihelion_deg, node_deg);

  double comet_ra_hours = ma_decimal_degrees_to_degree_hours(
      ma_ec_ra(comet_long_lat_dist.comet_long_deg, 0, 0,
               comet_long_lat_dist.comet_lat_deg, 0, 0, greenwich_date_day,
               greenwich_date_month, greenwich_date_year));
  double comet_dec_deg1 =
      ma_ec_dec(comet_long_lat_dist.comet_long_deg, 0, 0,
                comet_long_lat_dist.comet_lat_deg, 0, 0, greenwich_date_day,
                greenwich_date_month, greenwich_date_year);

  int comet_ra_hour = ma_decimal_hours_hour(comet_ra_hours);
  int comet_ra_min = ma_decimal_hours_minute(comet_ra_hours);
  double comet_ra_sec = ma_decimal_hours_second(comet_ra_hours);
  double comet_dec_deg = ma_decimal_degrees_degrees(comet_dec_deg1);
  double comet_dec_min = ma_decimal_degrees_minutes(comet_dec_deg1);
  double comet_dec_sec = ma_decimal_degrees_seconds(comet_dec_deg1);
  double comet_dist_earth = dround(comet_long_lat_dist.comet_dist_au, 2);

  return (TCometPosition){comet_ra_hour,   comet_ra_min,  comet_ra_sec,
                          comet_dec_deg,   comet_dec_min, comet_dec_sec,
                          comet_dist_earth};
}