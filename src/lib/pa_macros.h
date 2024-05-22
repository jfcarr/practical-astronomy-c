#include "pa_datetime.h"
#include "pa_planets_data.h"

#ifndef _pa_lib_macros
#define _pa_lib_macros
double ma_hms_dh(double hours, double minutes, double seconds);

int ma_decimal_hours_hour(double decimal_hours);

int ma_decimal_hours_minute(double decimal_hours);

double ma_decimal_hours_second(double decimal_hours);

double ma_civil_date_to_julian_date(double day, double month, double year);

double ma_julian_date_day(double julian_date);

int ma_julian_date_month(double julian_date);

int ma_julian_date_year(double julian_date);

double ma_right_ascension_to_hour_angle(double ra_hours, double ra_minutes,
                                        double ra_seconds, double lct_hours,
                                        double lct_minutes, double lct_seconds,
                                        int daylight_saving,
                                        int zone_correction, double local_day,
                                        int local_month, int local_year,
                                        double geographical_longitude);

double
ma_local_civil_time_to_universal_time(double lct_hours, double lct_minutes,
                                      double lct_seconds, int daylight_saving,
                                      int zone_correction, double local_day,
                                      int local_month, int local_year);

double
ma_universal_time_to_local_civil_time(double uHours, double uMinutes,
                                      double uSeconds, int daylightSaving,
                                      int zoneCorrection, double greenwichDay,
                                      int greenwichMonth, int greenwichYear);

double ma_local_civil_time_greenwich_day(double lct_hours, double lct_minutes,
                                         double lct_seconds,
                                         int daylight_saving,
                                         int zone_correction, double local_day,
                                         int local_month, int local_year);

double ma_local_civil_time_greenwich_month(double lct_hours, double lct_minutes,
                                           double lct_seconds,
                                           int daylight_saving,
                                           int zone_correction,
                                           double local_day, int local_month,
                                           int local_year);

double ma_local_civil_time_greenwich_year(double lct_hours, double lct_minutes,
                                          double lct_seconds,
                                          int daylight_saving,
                                          int zone_correction, double local_day,
                                          int local_month, int local_year);

double ma_universal_time_to_greenwich_sidereal_time(
    double u_hours, double u_minutes, double u_seconds, double greenwich_day,
    int greenwich_month, int greenwich_year);

double ma_greenwich_sidereal_time_to_universal_time(
    double greenwich_sidereal_hours, double greenwich_sidereal_minutes,
    double greenwich_sidereal_seconds, double greenwich_day,
    int greenwich_month, int greenwich_year);

double ma_greenwich_sidereal_time_to_local_sidereal_time(
    double greenwich_hours, double greenwich_minutes, double greenwich_seconds,
    double geographical_longitude);

double ma_local_sidereal_time_to_greenwich_sidereal_time(double local_hours,
                                                         double local_minutes,
                                                         double local_seconds,
                                                         double longitude);

double ma_hour_angle_to_right_ascension(double hour_angle_hours,
                                        double hour_angle_minutes,
                                        double hour_angle_seconds,
                                        double lct_hours, double lct_minutes,
                                        double lct_seconds, int daylight_saving,
                                        int zone_correction, double local_day,
                                        int local_month, int local_year,
                                        double geographical_longitude);

double ma_equatorial_coordinates_to_azimuth(double hour_angle_hours,
                                            double hour_angle_minutes,
                                            double hour_angle_seconds,
                                            double declination_degrees,
                                            double declination_minutes,
                                            double declination_seconds,
                                            double geographical_latitude);

double ma_equatorial_coordinates_to_altitude(double hour_angle_hours,
                                             double hour_angle_minutes,
                                             double hour_angle_seconds,
                                             double declination_degrees,
                                             double declination_minutes,
                                             double declination_seconds,
                                             double geographical_latitude);

double ma_degrees_minutes_seconds_to_decimal_degrees(double degrees,
                                                     double minutes,
                                                     double seconds);

double ma_degrees(double w);

double ma_decimal_degrees_degrees(double decimal_degrees);

double ma_decimal_degrees_minutes(double decimal_degrees);

double ma_decimal_degrees_seconds(double decimal_degrees);

double ma_decimal_degrees_to_degree_hours(double decimal_degrees);

double ma_degree_hours_to_decimal_degrees(double degree_hours);

double ma_horizon_coordinates_to_declination(
    double azimuth_degrees, double azimuth_minutes, double azimuth_seconds,
    double altitude_degrees, double altitude_minutes, double altitude_seconds,
    double geographical_latitude);

double ma_horizon_coordinates_to_hour_angle(
    double azimuth_degrees, double azimuth_minutes, double azimuth_seconds,
    double altitude_degrees, double altitude_minutes, double altitude_seconds,
    double geographical_latitude);

double ma_obliq(double greenwich_day, int greenwich_month, int greenwich_year);

double ma_nutat_long(double gd, int gm, int gy);

double ma_nutat_obl(double greenwich_day, int greenwich_month,
                    int greenwich_year);

double ma_sun_long(double lch, double lcm, double lcs, int ds, int zc,
                   double ld, int lm, int ly);

double ma_true_anomaly(double am, double ec);

double ma_eccentric_anomaly(double am, double ec);

double ma_refract(double y2, enum CoordinateType sw, double pr, double tr);

double ma_refract_l3035(double pr, double tr, double y, double d);

double ma_parallax_ha(double hh, double hm, double hs, double dd, double dm,
                      double ds, enum CoordinateType sw, double gp, double ht,
                      double hp);

TParallaxHelper ma_parallax_ha_l2870(double x, double y, double rc, double rp,
                                     double rs, double tp);

double ma_parallax_dec(double hh, double hm, double hs, double dd, double dm,
                       double ds, enum CoordinateType sw, double gp, double ht,
                       double hp);

TParallaxHelper ma_parallax_dec_l2870(double x, double y, double rc, double rp,
                                      double rs, double tp);

double ma_sun_dist(double lch, double lcm, double lcs, int ds, int zc,
                   double ld, int lm, int ly);

double ma_sun_dia(double lch, double lcm, double lcs, int ds, int zc, double ld,
                  int lm, int ly);

double ma_moon_longitude(double lh, double lm, double ls, int ds, int zc,
                         double dy, int mn, int yr);

double ma_moon_latitude(double lh, double lm, double ls, int ds, int zc,
                        double dy, int mn, int yr);

double ma_moon_horizontal_parallax(double lh, double lm, double ls, int ds,
                                   int zc, double dy, int mn, int yr);

double ma_unwind(double w);

double ma_sun_e_long(double gd, int gm, int gy);

double ma_sun_peri(double gd, int gm, int gy);

double ma_sun_ecc(double gd, int gm, int gy);

double ma_ec_dec(double eld, double elm, double els, double bd, double bm,
                 double bs, double gd, int gm, int gy);

double ma_ec_ra(double eld, double elm, double els, double bd, double bm,
                double bs, double gd, int gm, int gy);

double ma_sun_true_anomaly(double lch, double lcm, double lcs, int ds, int zc,
                           double ld, int lm, int ly);

double ma_sun_mean_anomaly(double lch, double lcm, double lcs, int ds, int zc,
                           double ld, int lm, int ly);

double ma_sunrise_lct(double ld, int lm, int ly, int ds, int zc, double gl,
                      double gp);

TSunriseLctHelper ma_sunrise_lct_3710(double gd, int gm, int gy, double sr,
                                      double di, double gp);

double ma_sunset_lct(double ld, int lm, int ly, int ds, int zc, double gl,
                     double gp);

TSunriseLctHelper ma_sunset_lct_l3710(double gd, int gm, int gy, double sr,
                                      double di, double gp);

enum WarningFlags ma_eg_st_ut(double gsh, double gsm, double gss, double gd,
                              int gm, int gy);

double ma_rise_set_local_sidereal_time_rise(double rah, double ram, double ras,
                                            double dd, double dm, double ds,
                                            double vd, double g);

double ma_rise_set_local_sidereal_time_set(double rah, double ram, double ras,
                                           double dd, double dm, double ds,
                                           double vd, double g);

double ma_rise_set_azimuth_rise(double rah, double ram, double ras, double dd,
                                double dm, double ds, double vd, double g);

double ma_rise_set_azimuth_set(double rah, double ram, double ras, double dd,
                               double dm, double ds, double vd, double g);

enum RiseSetStatus ma_ers(double rah, double ram, double ras, double dd,
                          double dm, double ds, double vd, double g);

enum RiseSetStatus ma_e_sun_rs(double ld, int lm, int ly, int ds, int zc,
                               double gl, double gp);

TSunriseLctHelper ma_e_sun_rs_l3710(double gd, int gm, int gy, double sr,
                                    double di, double gp);

double ma_sunrise_az(double ld, int lm, int ly, int ds, int zc, double gl,
                     double gp);

TSunriseLctHelper ma_sunrise_az_l3710(double gd, int gm, int gy, double sr,
                                      double di, double gp);

double ma_sunset_az(double ld, int lm, int ly, int ds, int zc, double gl,
                    double gp);

TSunriseLctHelper ma_sunset_az_l3710(double gd, int gm, int gy, double sr,
                                     double di, double gp);

double ma_twilight_am_lct(double ld, int lm, int ly, int ds, int zc, double gl,
                          double gp, enum TwilightType tt);

TTwilightLctHelper ma_twilight_am_lct_l3710(double gd, int gm, int gy,
                                            double sr, double di, double gp);

double ma_twilight_pm_lct(double ld, int lm, int ly, int ds, int zc, double gl,
                          double gp, enum TwilightType tt);

TTwilightLctHelper ma_twilight_pm_lct_l3710(double gd, int gm, int gy,
                                            double sr, double di, double gp);

enum TwilightStatus ma_e_twilight(double ld, int lm, int ly, int ds, int zc,
                                  double gl, double gp, enum TwilightType tt);

TTwilightLctHelper2 ma_e_twilight_l3710(double gd, int gm, int gy, double sr,
                                        double di, double gp);

double ma_angle(double xx1, double xm1, double xs1, double dd1, double dm1,
                double ds1, double xx2, double xm2, double xs2, double dd2,
                double dm2, double ds2, enum AngleMeasurementType s);

TPlanetCoordinates ma_planet_coordinates(double lh, double lm, double ls,
                                         int ds, int zc, double dy, int mn,
                                         int yr, char *s);

TPlanetLongLatL4685 ma_planet_long_l4685(PlanetDataPrecise pl[]);

TPlanetLongLatL4735 ma_planet_long_l4735(PlanetDataPrecise pl[], double ms,
                                         double t);

TPlanetLongLatL4810 ma_planet_long_l4810(PlanetDataPrecise pl[], double ms);

TPlanetLongLatL4945 ma_planet_long_l4945(double t, PlanetDataPrecise planet);

TCometLongLatDist ma_p_comet_long_lat_dist(double lh, double lm, double ls,
                                           int ds, int zc, double dy, int mn,
                                           int yr, double td, int tm, int ty,
                                           double q, double i, double p,
                                           double n);

double ma_solve_cubic(double w);
#endif