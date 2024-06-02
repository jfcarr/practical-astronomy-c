#include "pa_eclipses.h"
#include "pa_macros.h"
#include "pa_types.h"
#include "pa_util.h"
#include <math.h>

/**
 * Determine if a lunar eclipse is likely to occur.
 */
TLunarEclipseOccurrence lunar_eclipse_occurrence(double local_date_day,
                                                 int local_date_month,
                                                 int local_date_year,
                                                 bool is_daylight_saving,
                                                 int zone_correction_hours) {
  int daylight_saving = is_daylight_saving ? 1 : 0;

  double julian_date_of_full_moon =
      ma_fullmoon(daylight_saving, zone_correction_hours, local_date_day,
                  local_date_month, local_date_year);

  double g_date_of_full_moon_day = ma_julian_date_day(julian_date_of_full_moon);
  double integer_day = floor(g_date_of_full_moon_day);
  int g_date_of_full_moon_month =
      ma_julian_date_month(julian_date_of_full_moon);
  int g_date_of_full_moon_year = ma_julian_date_year(julian_date_of_full_moon);
  double ut_of_full_moon_hours = g_date_of_full_moon_day - integer_day;

  double local_civil_date_day = ma_universal_time_local_civil_day(
      ut_of_full_moon_hours, 0.0, 0.0, daylight_saving, zone_correction_hours,
      integer_day, g_date_of_full_moon_month, g_date_of_full_moon_year);
  int local_civil_date_month = ma_universal_time_local_civil_month(
      ut_of_full_moon_hours, 0.0, 0.0, daylight_saving, zone_correction_hours,
      integer_day, g_date_of_full_moon_month, g_date_of_full_moon_year);
  int local_civil_date_year = ma_universal_time_local_civil_year(
      ut_of_full_moon_hours, 0.0, 0.0, daylight_saving, zone_correction_hours,
      integer_day, g_date_of_full_moon_month, g_date_of_full_moon_year);

  enum LunarEclipseStatus eclipse_occurrence = ma_lunar_eclipse_occurrence(
      daylight_saving, zone_correction_hours, local_date_day, local_date_month,
      local_date_year);

  enum LunarEclipseStatus status = eclipse_occurrence;
  double event_date_day = local_civil_date_day;
  int event_date_month = local_civil_date_month;
  int event_date_year = local_civil_date_year;

  return (TLunarEclipseOccurrence){status, event_date_day, event_date_month,
                                   event_date_year};
}

/**
 * Calculate the circumstances of a lunar eclipse.
 */
TLunarEclipseCircumstances
lunar_eclipse_circumstances(double local_date_day, int local_date_month,
                            int local_date_year, bool is_daylight_saving,
                            int zone_correction_hours) {
  int daylight_saving = is_daylight_saving ? 1 : 0;

  double julian_date_of_full_moon =
      ma_fullmoon(daylight_saving, zone_correction_hours, local_date_day,
                  local_date_month, local_date_year);
  double g_date_of_full_moon_day = ma_julian_date_day(julian_date_of_full_moon);
  double integer_day = floor(g_date_of_full_moon_day);
  int g_date_of_full_moon_month =
      ma_julian_date_month(julian_date_of_full_moon);
  int g_date_of_full_moon_year = ma_julian_date_year(julian_date_of_full_moon);
  double ut_of_full_moon_hours = g_date_of_full_moon_day - integer_day;

  double local_civil_date_day = ma_universal_time_local_civil_day(
      ut_of_full_moon_hours, 0.0, 0.0, daylight_saving, zone_correction_hours,
      integer_day, g_date_of_full_moon_month, g_date_of_full_moon_year);
  int local_civil_date_month = ma_universal_time_local_civil_month(
      ut_of_full_moon_hours, 0.0, 0.0, daylight_saving, zone_correction_hours,
      integer_day, g_date_of_full_moon_month, g_date_of_full_moon_year);
  int local_civil_date_year = ma_universal_time_local_civil_year(
      ut_of_full_moon_hours, 0.0, 0.0, daylight_saving, zone_correction_hours,
      integer_day, g_date_of_full_moon_month, g_date_of_full_moon_year);

  double ut_max_eclipse =
      ma_ut_max_lunar_eclipse(local_date_day, local_date_month, local_date_year,
                              daylight_saving, zone_correction_hours);
  double ut_first_contact = ma_ut_first_contact_lunar_eclipse(
      local_date_day, local_date_month, local_date_year, daylight_saving,
      zone_correction_hours);
  double ut_last_contact = ma_ut_last_contact_lunar_eclipse(
      local_date_day, local_date_month, local_date_year, daylight_saving,
      zone_correction_hours);
  double ut_start_umbral_phase = ma_ut_start_umbra_lunar_eclipse(
      local_date_day, local_date_month, local_date_year, daylight_saving,
      zone_correction_hours);
  double ut_end_umbral_phase = ma_ut_end_umbra_lunar_eclipse(
      local_date_day, local_date_month, local_date_year, daylight_saving,
      zone_correction_hours);
  double ut_start_total_phase = ma_ut_start_total_lunar_eclipse(
      local_date_day, local_date_month, local_date_year, daylight_saving,
      zone_correction_hours);
  double ut_end_total_phase = ma_ut_end_total_lunar_eclipse(
      local_date_day, local_date_month, local_date_year, daylight_saving,
      zone_correction_hours);

  double eclipse_magnitude1 =
      ma_mag_lunar_eclipse(local_date_day, local_date_month, local_date_year,
                           daylight_saving, zone_correction_hours);

  double lunar_eclipse_certain_date_day = local_civil_date_day;
  int lunar_eclipse_certain_date_month = local_civil_date_month;
  int lunar_eclipse_certain_date_year = local_civil_date_year;

  double ut_start_pen_phase_hour =
      (ut_first_contact == -99.0)
          ? -99.0
          : ma_decimal_hours_hour(ut_first_contact + 0.008333);
  double ut_start_pen_phase_minutes =
      (ut_first_contact == -99.0)
          ? -99.0
          : ma_decimal_hours_minute(ut_first_contact + 0.008333);

  double ut_start_umbral_phase_hour =
      (ut_start_umbral_phase == -99.0)
          ? -99.0
          : ma_decimal_hours_hour(ut_start_umbral_phase + 0.008333);
  double ut_start_umbral_phase_minutes =
      (ut_start_umbral_phase == -99.0)
          ? -99.0
          : ma_decimal_hours_minute(ut_start_umbral_phase + 0.008333);

  double ut_start_total_phase_hour =
      (ut_start_total_phase == -99.0)
          ? -99.0
          : ma_decimal_hours_hour(ut_start_total_phase + 0.008333);
  double ut_start_total_phase_minutes =
      (ut_start_total_phase == -99.0)
          ? -99.0
          : ma_decimal_hours_minute(ut_start_total_phase + 0.008333);

  double ut_mid_eclipse_hour =
      (ut_max_eclipse == -99.0)
          ? -99.0
          : ma_decimal_hours_hour(ut_max_eclipse + 0.008333);
  double ut_mid_eclipse_minutes =
      (ut_max_eclipse == -99.0)
          ? -99.0
          : ma_decimal_hours_minute(ut_max_eclipse + 0.008333);

  double ut_end_total_phase_hour =
      (ut_end_total_phase == -99.0)
          ? -99.0
          : ma_decimal_hours_hour(ut_end_total_phase + 0.008333);
  double ut_end_total_phase_minutes =
      (ut_end_total_phase == -99.0)
          ? -99.0
          : ma_decimal_hours_minute(ut_end_total_phase + 0.008333);

  double ut_end_umbral_phase_hour =
      (ut_end_umbral_phase == -99.0)
          ? -99.0
          : ma_decimal_hours_hour(ut_end_umbral_phase + 0.008333);
  double ut_end_umbral_phase_minutes =
      (ut_end_umbral_phase == -99.0)
          ? -99.0
          : ma_decimal_hours_minute(ut_end_umbral_phase + 0.008333);

  double ut_end_pen_phase_hour =
      (ut_last_contact == -99.0)
          ? -99.0
          : ma_decimal_hours_hour(ut_last_contact + 0.008333);
  double ut_end_pen_phase_minutes =
      (ut_last_contact == -99.0)
          ? -99.0
          : ma_decimal_hours_minute(ut_last_contact + 0.008333);

  double eclipse_magnitude =
      (eclipse_magnitude1 == -99.0) ? -99.0 : dround(eclipse_magnitude1, 2);

  return (TLunarEclipseCircumstances){
      lunar_eclipse_certain_date_day,  lunar_eclipse_certain_date_month,
      lunar_eclipse_certain_date_year, ut_start_pen_phase_hour,
      ut_start_pen_phase_minutes,      ut_start_umbral_phase_hour,
      ut_start_umbral_phase_minutes,   ut_start_total_phase_hour,
      ut_start_total_phase_minutes,    ut_mid_eclipse_hour,
      ut_mid_eclipse_minutes,          ut_end_total_phase_hour,
      ut_end_total_phase_minutes,      ut_end_umbral_phase_hour,
      ut_end_umbral_phase_minutes,     ut_end_pen_phase_hour,
      ut_end_pen_phase_minutes,        eclipse_magnitude};
}

/**
 * Determine if a solar eclipse is likely to occur.
 */
TSolarEclipseOccurrence solar_eclipse_occurrence(double local_date_day,
                                                 int local_date_month,
                                                 int local_date_year,
                                                 bool is_daylight_saving,
                                                 int zone_correction_hours) {
  int daylight_saving = is_daylight_saving ? 1 : 0;

  double julian_date_of_new_moon =
      ma_newmoon(daylight_saving, zone_correction_hours, local_date_day,
                 local_date_month, local_date_year);
  double g_date_of_new_moon_day = ma_julian_date_day(julian_date_of_new_moon);
  double integer_day = floor(g_date_of_new_moon_day);
  int g_date_of_new_moon_month = ma_julian_date_month(julian_date_of_new_moon);
  int g_date_of_new_moon_year = ma_julian_date_year(julian_date_of_new_moon);
  double ut_of_new_moon_hours = g_date_of_new_moon_day - integer_day;

  double local_civil_date_day = ma_universal_time_local_civil_day(
      ut_of_new_moon_hours, 0.0, 0.0, daylight_saving, zone_correction_hours,
      integer_day, g_date_of_new_moon_month, g_date_of_new_moon_year);
  int local_civil_date_month = ma_universal_time_local_civil_month(
      ut_of_new_moon_hours, 0.0, 0.0, daylight_saving, zone_correction_hours,
      integer_day, g_date_of_new_moon_month, g_date_of_new_moon_year);
  int local_civil_date_year = ma_universal_time_local_civil_year(
      ut_of_new_moon_hours, 0.0, 0.0, daylight_saving, zone_correction_hours,
      integer_day, g_date_of_new_moon_month, g_date_of_new_moon_year);

  enum SolarEclipseStatus eclipse_occurrence = ma_solar_eclipse_occurrence(
      daylight_saving, zone_correction_hours, local_date_day, local_date_month,
      local_date_year);

  enum SolarEclipseStatus status = eclipse_occurrence;
  double event_date_day = local_civil_date_day;
  int event_date_month = local_civil_date_month;
  int event_date_year = local_civil_date_year;

  return (TSolarEclipseOccurrence){status, event_date_day, event_date_month,
                                   event_date_year};
}

/**
 * Calculate the circumstances of a solar eclipse.
 */
TSolarEclipseCircumstances solar_eclipse_circumstances(
    double local_date_day, int local_date_month, int local_date_year,
    bool is_daylight_saving, int zone_correction_hours,
    double geog_longitude_deg, double geog_latitude_deg) {
  int daylight_saving = is_daylight_saving ? 1 : 0;

  double julian_date_of_new_moon =
      ma_newmoon(daylight_saving, zone_correction_hours, local_date_day,
                 local_date_month, local_date_year);
  double g_date_of_new_moon_day = ma_julian_date_day(julian_date_of_new_moon);
  double integer_day = floor(g_date_of_new_moon_day);
  int g_date_of_new_moon_month = ma_julian_date_month(julian_date_of_new_moon);
  int g_date_of_new_moon_year = ma_julian_date_year(julian_date_of_new_moon);
  double ut_of_new_moon_hours = g_date_of_new_moon_day - integer_day;
  double local_civil_date_day = ma_universal_time_local_civil_day(
      ut_of_new_moon_hours, 0.0, 0.0, daylight_saving, zone_correction_hours,
      integer_day, g_date_of_new_moon_month, g_date_of_new_moon_year);
  int local_civil_date_month = ma_universal_time_local_civil_month(
      ut_of_new_moon_hours, 0.0, 0.0, daylight_saving, zone_correction_hours,
      integer_day, g_date_of_new_moon_month, g_date_of_new_moon_year);
  int local_civil_date_year = ma_universal_time_local_civil_year(
      ut_of_new_moon_hours, 0.0, 0.0, daylight_saving, zone_correction_hours,
      integer_day, g_date_of_new_moon_month, g_date_of_new_moon_year);

  double ut_max_eclipse = ma_ut_max_solar_eclipse(
      local_date_day, local_date_month, local_date_year, daylight_saving,
      zone_correction_hours, geog_longitude_deg, geog_latitude_deg);
  double ut_first_contact = ma_ut_first_contact_solar_eclipse(
      local_date_day, local_date_month, local_date_year, daylight_saving,
      zone_correction_hours, geog_longitude_deg, geog_latitude_deg);
  double ut_last_contact = ma_ut_last_contact_solar_eclipse(
      local_date_day, local_date_month, local_date_year, daylight_saving,
      zone_correction_hours, geog_longitude_deg, geog_latitude_deg);
  double magnitude = ma_mag_solar_eclipse(
      local_date_day, local_date_month, local_date_year, daylight_saving,
      zone_correction_hours, geog_longitude_deg, geog_latitude_deg);

  double solar_eclipse_certain_date_day = local_civil_date_day;
  int solar_eclipse_certain_date_month = local_civil_date_month;
  int solar_eclipse_certain_date_year = local_civil_date_year;

  double ut_first_contact_hour =
      (ut_first_contact == -99.0)
          ? -99.0
          : ma_decimal_hours_hour(ut_first_contact + 0.008333);
  double ut_first_contact_minutes =
      (ut_first_contact == -99.0)
          ? -99.0
          : ma_decimal_hours_minute(ut_first_contact + 0.008333);

  double ut_mid_eclipse_hour =
      (ut_max_eclipse == -99.0)
          ? -99.0
          : ma_decimal_hours_hour(ut_max_eclipse + 0.008333);
  double ut_mid_eclipse_minutes =
      (ut_max_eclipse == -99.0)
          ? -99.0
          : ma_decimal_hours_minute(ut_max_eclipse + 0.008333);

  double ut_last_contact_hour =
      (ut_last_contact == -99.0)
          ? -99.0
          : ma_decimal_hours_hour(ut_last_contact + 0.008333);
  double ut_last_contact_minutes =
      (ut_last_contact == -99.0)
          ? -99.0
          : ma_decimal_hours_minute(ut_last_contact + 0.008333);

  double eclipse_magnitude =
      (magnitude == -99.0) ? -99.0 : dround(magnitude, 3);

  return (TSolarEclipseCircumstances){
      solar_eclipse_certain_date_day,  solar_eclipse_certain_date_month,
      solar_eclipse_certain_date_year, ut_first_contact_hour,
      ut_first_contact_minutes,        ut_mid_eclipse_hour,
      ut_mid_eclipse_minutes,          ut_last_contact_hour,
      ut_last_contact_minutes,         eclipse_magnitude};
}
