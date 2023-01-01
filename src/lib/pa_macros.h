#include "pa_datetime.h"

#ifndef _pa_lib_macros
#define _pa_lib_macros
double hms_dh(double hours, double minutes, double seconds);

int decimal_hours_hour(double decimal_hours);

int decimal_hours_minute(double decimal_hours);

double decimal_hours_second(double decimal_hours);

double civil_date_to_julian_date(double day, double month, double year);

double julian_date_day(double julian_date);

int julian_date_month(double julian_date);

int julian_date_year(double julian_date);

double right_ascension_to_hour_angle_macro(
    double ra_hours, double ra_minutes, double ra_seconds, double lct_hours,
    double lct_minutes, double lct_seconds, int daylight_saving,
    int zone_correction, double local_day, int local_month, int local_year,
    double geographical_longitude);

double local_civil_time_to_universal_time_macro(
    double lct_hours, double lct_minutes, double lct_seconds,
    int daylight_saving, int zone_correction, double local_day, int local_month,
    int local_year);

double local_civil_time_greenwich_day(double lct_hours, double lct_minutes,
                                      double lct_seconds, int daylight_saving,
                                      int zone_correction, double local_day,
                                      int local_month, int local_year);

double local_civil_time_greenwich_month(double lct_hours, double lct_minutes,
                                        double lct_seconds, int daylight_saving,
                                        int zone_correction, double local_day,
                                        int local_month, int local_year);

double local_civil_time_greenwich_year(double lct_hours, double lct_minutes,
                                       double lct_seconds, int daylight_saving,
                                       int zone_correction, double local_day,
                                       int local_month, int local_year);

double universal_time_to_greenwich_sidereal_time_macro(
    double u_hours, double u_minutes, double u_seconds, double greenwich_day,
    int greenwich_month, int greenwich_year);

double greenwich_sidereal_time_to_universal_time_macro(
    double greenwich_sidereal_hours, double greenwich_sidereal_minutes,
    double greenwich_sidereal_seconds, double greenwich_day,
    int greenwich_month, int greenwich_year);

double greenwich_sidereal_time_to_local_sidereal_time_macro(
    double greenwich_hours, double greenwich_minutes, double greenwich_seconds,
    double geographical_longitude);

double local_sidereal_time_to_greenwich_sidereal_time_macro(
    double local_hours, double local_minutes, double local_seconds,
    double longitude);

double hour_angle_to_right_ascension_macro(
    double hour_angle_hours, double hour_angle_minutes,
    double hour_angle_seconds, double lct_hours, double lct_minutes,
    double lct_seconds, int daylight_saving, int zone_correction,
    double local_day, int local_month, int local_year,
    double geographical_longitude);

double equatorial_coordinates_to_azimuth(double hour_angle_hours,
                                         double hour_angle_minutes,
                                         double hour_angle_seconds,
                                         double declination_degrees,
                                         double declination_minutes,
                                         double declination_seconds,
                                         double geographical_latitude);

double equatorial_coordinates_to_altitude(double hour_angle_hours,
                                          double hour_angle_minutes,
                                          double hour_angle_seconds,
                                          double declination_degrees,
                                          double declination_minutes,
                                          double declination_seconds,
                                          double geographical_latitude);

double degrees_minutes_seconds_to_decimal_degrees(double degrees,
                                                  double minutes,
                                                  double seconds);

double w_to_degrees(double w);

double decimal_degrees_degrees(double decimal_degrees);

double decimal_degrees_minutes(double decimal_degrees);

double decimal_degrees_seconds(double decimal_degrees);

double decimal_degrees_to_degree_hours(double decimal_degrees);

double degree_hours_to_decimal_degrees(double degree_hours);

double horizon_coordinates_to_declination(
    double azimuth_degrees, double azimuth_minutes, double azimuth_seconds,
    double altitude_degrees, double altitude_minutes, double altitude_seconds,
    double geographical_latitude);

double horizon_coordinates_to_hour_angle(
    double azimuth_degrees, double azimuth_minutes, double azimuth_seconds,
    double altitude_degrees, double altitude_minutes, double altitude_seconds,
    double geographical_latitude);

double obliq(double greenwich_day, int greenwich_month, int greenwich_year);

double nutat_long(double gd, int gm, int gy);

double nutat_obl(double greenwich_day, int greenwich_month, int greenwich_year);

double sun_long(double lch, double lcm, double lcs, int ds, int zc, double ld,
                int lm, int ly);

double true_anomaly(double am, double ec);

double eccentric_anomaly(double am, double ec);

double refract(double y2, TCoordinateType sw, double pr, double tr);

double refract_l3035(double pr, double tr, double y, double d);

double parallax_ha(double hh, double hm, double hs, double dd, double dm,
                   double ds, TCoordinateType sw, double gp, double ht,
                   double hp);

TParallaxHelper parallax_ha_l2870(double x, double y, double rc, double rp,
                                  double rs, double tp);

double parallax_dec(double hh, double hm, double hs, double dd, double dm,
                    double ds, TCoordinateType sw, double gp, double ht,
                    double hp);

TParallaxHelper parallax_dec_l2870(double x, double y, double rc, double rp,
                                   double rs, double tp);

double sun_dist(double lch, double lcm, double lcs, int ds, int zc, double ld,
                int lm, int ly);

double sun_dia(double lch, double lcm, double lcs, int ds, int zc, double ld,
               int lm, int ly);

double moon_longitude(double lh, double lm, double ls, int ds, int zc,
                      double dy, int mn, int yr);

double moon_latitude(double lh, double lm, double ls, int ds, int zc, double dy,
                     int mn, int yr);

double moon_horizontal_parallax(double lh, double lm, double ls, int ds, int zc,
                                double dy, int mn, int yr);

double unwind(double w);
#endif