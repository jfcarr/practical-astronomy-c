#include "pa_planets.h"
#include "pa_macros.h"
#include "pa_planets_data.h"
#include "pa_util.h"
#include <math.h>
#include <stdbool.h>

/**
 * Calculate approximate position of a planet.
 */
TPlanetPosition approximate_position_of_planet(
    double lct_hour, double lct_min, double lct_sec, bool is_daylight_saving,
    int zone_correction_hours, double local_date_day, int local_date_month,
    int local_date_year, char *planet_name) {
  int daylight_saving = is_daylight_saving ? 1 : 0;

  struct PlanetRecord planet_info = get_planet_data(planet_name);

  double g_date_day = ma_local_civil_time_greenwich_day(
      lct_hour, lct_min, lct_sec, daylight_saving, zone_correction_hours,
      local_date_day, local_date_month, local_date_year);
  int g_date_month = ma_local_civil_time_greenwich_month(
      lct_hour, lct_min, lct_sec, daylight_saving, zone_correction_hours,
      local_date_day, local_date_month, local_date_year);
  int g_date_year = ma_local_civil_time_greenwich_year(
      lct_hour, lct_min, lct_sec, daylight_saving, zone_correction_hours,
      local_date_day, local_date_month, local_date_year);

  double ut_hours = ma_local_civil_time_to_universal_time_macro(
      lct_hour, lct_min, lct_sec, daylight_saving, zone_correction_hours,
      local_date_day, local_date_month, local_date_year);
  double g_days = ma_civil_date_to_julian_date(g_date_day + (ut_hours / 24),
                                               g_date_month, g_date_year) -
                  ma_civil_date_to_julian_date(0, 1, 2010);
  double np_deg1 = 360 * g_days / (365.242191 * planet_info.tp_PeriodOrbit);
  double np_deg2 = np_deg1 - 360 * floor(np_deg1 / 360);
  double mp_deg = np_deg2 + planet_info.long_LongitudeEpoch -
                  planet_info.peri_LongitudePerihelion;
  double lp_deg1 = np_deg2 +
                   (360 * planet_info.ecc_EccentricityOrbit *
                    sin(degrees_to_radians(mp_deg)) / PA_PI) +
                   planet_info.long_LongitudeEpoch;
  double lp_deg2 = lp_deg1 - 360 * floor(lp_deg1 / 360);
  double planet_true_anomaly_deg =
      lp_deg2 - planet_info.peri_LongitudePerihelion;
  double r_au = planet_info.axis_AxisOrbit *
                (1 - pow(planet_info.ecc_EccentricityOrbit, 2)) /
                (1 + planet_info.ecc_EccentricityOrbit *
                         cos(degrees_to_radians(planet_true_anomaly_deg)));

  struct PlanetRecord earth_info = get_planet_data("Earth");

  double ne_deg1 = 360 * g_days / (365.242191 * earth_info.tp_PeriodOrbit);
  double ne_deg2 = ne_deg1 - 360 * floor(ne_deg1 / 360);
  double me_deg = ne_deg2 + earth_info.long_LongitudeEpoch -
                  earth_info.peri_LongitudePerihelion;
  double le_deg1 = ne_deg2 + earth_info.long_LongitudeEpoch +
                   360 * earth_info.ecc_EccentricityOrbit *
                       sin(degrees_to_radians(me_deg)) / PA_PI;
  double le_deg2 = le_deg1 - 360 * floor(le_deg1 / 360);
  double earth_true_anomaly_deg = le_deg2 - earth_info.peri_LongitudePerihelion;
  double r_au2 = earth_info.axis_AxisOrbit *
                 (1 - pow(earth_info.ecc_EccentricityOrbit, 2)) /
                 (1 + earth_info.ecc_EccentricityOrbit *
                          cos(degrees_to_radians(earth_true_anomaly_deg)));
  double lp_node_rad =
      degrees_to_radians(lp_deg2 - planet_info.node_LongitudeAscendingNode);
  double psi_rad =
      asin(sin(lp_node_rad) *
           sin(degrees_to_radians(planet_info.incl_OrbitalInclination)));
  double y = sin(lp_node_rad) *
             cos(degrees_to_radians(planet_info.incl_OrbitalInclination));
  double x = cos(lp_node_rad);
  double ld_deg =
      ma_degrees(atan2(y, x)) + planet_info.node_LongitudeAscendingNode;
  double rd_au = r_au * cos(psi_rad);
  double le_ld_rad = degrees_to_radians(le_deg2 - ld_deg);
  double atan2_type1 =
      atan2((rd_au * sin(le_ld_rad)), (r_au2 - rd_au * cos(le_ld_rad)));
  double atan2_type2 =
      atan2((r_au2 * sin(-le_ld_rad)), (rd_au - r_au2 * cos(le_ld_rad)));
  double a_rad = (rd_au < 1) ? atan2_type1 : atan2_type2;
  double lamda_deg1 = (rd_au < 1) ? 180 + le_deg2 + ma_degrees(a_rad)
                                  : ma_degrees(a_rad) + ld_deg;
  double lamda_deg2 = lamda_deg1 - 360 * floor(lamda_deg1 / 360);
  double beta_deg = ma_degrees(
      atan(rd_au * tan(psi_rad) * sin(degrees_to_radians(lamda_deg2 - ld_deg)) /
           (r_au2 * sin(-le_ld_rad))));
  double ra_hours = ma_decimal_degrees_to_degree_hours(ma_ec_ra(
      lamda_deg2, 0, 0, beta_deg, 0, 0, g_date_day, g_date_month, g_date_year));
  double dec_deg = ma_ec_dec(lamda_deg2, 0, 0, beta_deg, 0, 0, g_date_day,
                             g_date_month, g_date_year);

  int planet_ra_hour = ma_decimal_hours_hour(ra_hours);
  int planet_ra_min = ma_decimal_hours_minute(ra_hours);
  double planet_ra_sec = ma_decimal_hours_second(ra_hours);
  double planet_dec_deg = ma_decimal_degrees_degrees(dec_deg);
  double planet_dec_min = ma_decimal_degrees_minutes(dec_deg);
  double planet_dec_sec = ma_decimal_degrees_seconds(dec_deg);

  return (TPlanetPosition){planet_ra_hour, planet_ra_min,  planet_ra_sec,
                           planet_dec_deg, planet_dec_min, planet_dec_sec};
}

/**
 * Calculate precise position of a planet.
 */
TPlanetPosition
precise_position_of_planet(double lct_hour, double lct_min, double lct_sec,
                           bool is_daylight_saving, int zone_correction_hours,
                           double local_date_day, int local_date_month,
                           int local_date_year, char *planet_name) {
  int daylight_saving = is_daylight_saving ? 1 : 0;

  TPlanetCoordinates coordinate_results = ma_planet_coordinates(
      lct_hour, lct_min, lct_sec, daylight_saving, zone_correction_hours,
      local_date_day, local_date_month, local_date_year, planet_name);

  double planet_ra_hours = ma_decimal_degrees_to_degree_hours(
      ma_ec_ra(coordinate_results.planet_longitude, 0, 0,
               coordinate_results.planet_latitude, 0, 0, local_date_day,
               local_date_month, local_date_year));
  double planet_dec_deg1 =
      ma_ec_dec(coordinate_results.planet_longitude, 0, 0,
                coordinate_results.planet_latitude, 0, 0, local_date_day,
                local_date_month, local_date_year);

  int planet_ra_hour = ma_decimal_hours_hour(planet_ra_hours);
  int planet_ra_min = ma_decimal_hours_minute(planet_ra_hours);
  double planet_ra_sec = ma_decimal_hours_second(planet_ra_hours);
  double planet_dec_deg = ma_decimal_degrees_degrees(planet_dec_deg1);
  double planet_dec_min = ma_decimal_degrees_minutes(planet_dec_deg1);
  double planet_dec_sec = ma_decimal_degrees_seconds(planet_dec_deg1);

  return (TPlanetPosition){planet_ra_hour, planet_ra_min,  planet_ra_sec,
                           planet_dec_deg, planet_dec_min, planet_dec_sec};
}

/**
 * Calculate several visual aspects of a planet.
 */
TPlanetVisualAspects
visual_aspects_of_a_planet(double lct_hour, double lct_min, double lct_sec,
                           bool is_daylight_saving, int zone_correction_hours,
                           double local_date_day, int local_date_month,
                           int local_date_year, char *planet_name) {
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

  TPlanetCoordinates planet_coord_info = ma_planet_coordinates(
      lct_hour, lct_min, lct_sec, daylight_saving, zone_correction_hours,
      local_date_day, local_date_month, local_date_year, planet_name);

  double planet_ra_rad = degrees_to_radians(
      ma_ec_ra(planet_coord_info.planet_longitude, 0, 0,
               planet_coord_info.planet_latitude, 0, 0, local_date_day,
               local_date_month, local_date_year));
  double planet_dec_rad = degrees_to_radians(
      ma_ec_dec(planet_coord_info.planet_longitude, 0, 0,
                planet_coord_info.planet_latitude, 0, 0, local_date_day,
                local_date_month, local_date_year));

  double light_travel_time_hours =
      planet_coord_info.planet_distance_au * 0.1386;

  struct PlanetRecord planet_info = get_planet_data(planet_name);
  double angular_diameter_arcsec =
      planet_info.theta0_AngularDiameter / planet_coord_info.planet_distance_au;
  double phase1 =
      0.5 * (1.0 + cos(degrees_to_radians(planet_coord_info.planet_longitude -
                                          planet_coord_info.planet_h_long1)));

  double sun_ecl_long_deg = ma_sun_long(
      lct_hour, lct_min, lct_sec, daylight_saving, zone_correction_hours,
      local_date_day, local_date_month, local_date_year);
  double sun_ra_rad = degrees_to_radians(
      ma_ec_ra(sun_ecl_long_deg, 0, 0, 0, 0, 0, greenwich_date_day,
               greenwich_date_month, greenwich_date_year));
  double sun_dec_rad = degrees_to_radians(
      ma_ec_dec(sun_ecl_long_deg, 0, 0, 0, 0, 0, greenwich_date_day,
                greenwich_date_month, greenwich_date_year));

  double y = cos(sun_dec_rad) * sin(sun_ra_rad - planet_ra_rad);
  double x =
      cos(planet_dec_rad) * sin(sun_dec_rad) -
      sin(planet_dec_rad) * cos(sun_dec_rad) * cos(sun_ra_rad - planet_ra_rad);

  double chi_deg = ma_degrees(atan2(y, x));
  double radius_vector_au = planet_coord_info.planet_r_vect;
  double approximate_magnitude1 =
      5.0 * log10(radius_vector_au * planet_coord_info.planet_distance_au /
                  sqrt(phase1)) +
      planet_info.v0_VisualMagnitude;

  double distance_au = dround(planet_coord_info.planet_distance_au, 5);
  double ang_dia_arcsec = dround(angular_diameter_arcsec, 1);
  double phase = dround(phase1, 2);
  int light_time_hour = ma_decimal_hours_hour(light_travel_time_hours);
  int light_time_minutes = ma_decimal_hours_minute(light_travel_time_hours);
  double light_time_seconds = ma_decimal_hours_second(light_travel_time_hours);
  double pos_angle_bright_limb_deg = dround(chi_deg, 1);
  double approximate_magnitude = dround(approximate_magnitude1, 1);

  return (TPlanetVisualAspects){distance_au,
                                ang_dia_arcsec,
                                phase,
                                light_time_hour,
                                light_time_minutes,
                                light_time_seconds,
                                pos_angle_bright_limb_deg,
                                approximate_magnitude};
}
