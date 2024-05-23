#include "pa_moon.h"
#include "pa_macros.h"
#include "pa_util.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

/**
 * Calculate approximate position of the Moon.
 */
TMoonApproximatePosition
approximate_position_of_moon(double lct_hour, double lct_min, double lct_sec,
                             bool is_daylight_saving, int zone_correction_hours,
                             double local_date_day, int local_date_month,
                             int local_date_year) {
  int daylight_saving = is_daylight_saving ? 1 : 0;

  double l0 = 91.9293359879052;
  double p0 = 130.143076320618;
  double n0 = 291.682546643194;
  double i = 5.145396;

  double gdate_day = ma_local_civil_time_greenwich_day(
      lct_hour, lct_min, lct_sec, daylight_saving, zone_correction_hours,
      local_date_day, local_date_month, local_date_year);
  int gdate_month = ma_local_civil_time_greenwich_month(
      lct_hour, lct_min, lct_sec, daylight_saving, zone_correction_hours,
      local_date_day, local_date_month, local_date_year);
  int gdate_year = ma_local_civil_time_greenwich_year(
      lct_hour, lct_min, lct_sec, daylight_saving, zone_correction_hours,
      local_date_day, local_date_month, local_date_year);

  double ut_hours = ma_local_civil_time_to_universal_time(
      lct_hour, lct_min, lct_sec, daylight_saving, zone_correction_hours,
      local_date_day, local_date_month, local_date_year);
  double d_days =
      ma_civil_date_to_julian_date(gdate_day, gdate_month, gdate_year) -
      ma_civil_date_to_julian_date(0.0, 1, 2010) + ut_hours / 24;
  double sun_long_deg = ma_sun_long(lct_hour, lct_min, lct_sec, daylight_saving,
                                    zone_correction_hours, local_date_day,
                                    local_date_month, local_date_year);
  double sun_mean_anomaly_rad = ma_sun_mean_anomaly(
      lct_hour, lct_min, lct_sec, daylight_saving, zone_correction_hours,
      local_date_day, local_date_month, local_date_year);
  double lm_deg = ma_unwind_deg(13.1763966 * d_days + l0);
  double mm_deg = ma_unwind_deg(lm_deg - 0.1114041 * d_days - p0);
  double n_deg = ma_unwind_deg(n0 - (0.0529539 * d_days));
  double ev_deg =
      1.2739 * sin(degrees_to_radians(2.0 * (lm_deg - sun_long_deg) - mm_deg));
  double ae_deg = 0.1858 * sin(sun_mean_anomaly_rad);
  double a3_deg = 0.37 * sin(sun_mean_anomaly_rad);
  double mmd_deg = mm_deg + ev_deg - ae_deg - a3_deg;
  double ec_deg = 6.2886 * sin(degrees_to_radians(mmd_deg));
  double a4_deg = 0.214 * sin(2.0 * degrees_to_radians(mmd_deg));
  double ld_deg = lm_deg + ev_deg + ec_deg - ae_deg + a4_deg;
  double v_deg = 0.6583 * sin(2.0 * degrees_to_radians(ld_deg - sun_long_deg));
  double ldd_deg = ld_deg + v_deg;
  double nd_deg = n_deg - 0.16 * sin(sun_mean_anomaly_rad);
  double y =
      sin(degrees_to_radians(ldd_deg - nd_deg)) * cos(degrees_to_radians(i));
  double x = cos(degrees_to_radians(ldd_deg - nd_deg));

  double moon_long_deg = ma_unwind_deg(ma_degrees(atan2(y, x)) + nd_deg);
  double moon_lat_deg = ma_degrees(asin(
      sin(degrees_to_radians(ldd_deg - nd_deg)) * sin(degrees_to_radians(i))));
  double moon_ra_hours1 = ma_decimal_degrees_to_degree_hours(
      ma_ec_ra(moon_long_deg, 0, 0, moon_lat_deg, 0, 0, gdate_day, gdate_month,
               gdate_year));
  double moon_dec_deg1 = ma_ec_dec(moon_long_deg, 0, 0, moon_lat_deg, 0, 0,
                                   gdate_day, gdate_month, gdate_year);

  int moon_ra_hour = ma_decimal_hours_hour(moon_ra_hours1);
  int moon_ra_min = ma_decimal_hours_minute(moon_ra_hours1);
  double moon_ra_sec = ma_decimal_hours_second(moon_ra_hours1);
  double moon_dec_deg = ma_decimal_degrees_degrees(moon_dec_deg1);
  double moon_dec_min = ma_decimal_degrees_minutes(moon_dec_deg1);
  double moon_dec_sec = ma_decimal_degrees_seconds(moon_dec_deg1);

  return (TMoonApproximatePosition){moon_ra_hour, moon_ra_min,  moon_ra_sec,
                                    moon_dec_deg, moon_dec_min, moon_dec_sec};
}
