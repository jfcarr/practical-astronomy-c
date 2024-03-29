#include "../lib/pa_coordinates.h"
#include <math.h>
#include <stdio.h>

#ifndef _pa_test_coordinates
#define _pa_test_coordinates

void test_angle_to_decimal_degrees(double degrees, double minutes,
                                   double seconds, double expected_result);

void test_decimal_degrees_to_angle(double decimal_degrees,
                                   TAngle expected_result);

void test_right_ascension_to_hour_angle(
    double ra_hours, double ra_minutes, double ra_seconds, double lct_hours,
    double lct_minutes, double lct_seconds, bool is_daylight_savings,
    int zone_correction, double local_day, int local_month, int local_year,
    double geographical_longitude, THourAngle expected_result);

void test_hour_angle_to_right_ascension(
    double hour_angle_hours, double hour_angle_minutes,
    double hour_angle_seconds, double lct_hours, double lct_minutes,
    double lct_seconds, bool is_daylight_savings, int zone_correction,
    double local_day, int local_month, int local_year,
    double geographical_longitude, TRightAscension expected_result);

void test_equatorial_coordinates_to_horizon_coordinates(
    double hour_angle_hours, double hour_angle_minutes,
    double hour_angle_seconds, double declination_degrees,
    double declination_minutes, double declination_seconds,
    double geographical_latitude, THorizonCoordinates expected_result);

void test_horizon_coordinates_to_equatorial_coordinates(
    double azimuth_degrees, double azimuth_minutes, double azimuth_seconds,
    double altitude_degrees, double altitude_minutes, double altitude_seconds,
    double geographical_latitude, TEquatorialCoordinates expected_result);

void test_mean_obliquity_of_the_ecliptic(double greenwich_day,
                                         int greenwich_month,
                                         int greenwich_year,
                                         double expected_result);

void test_ecliptic_coordinates_to_equatorial_coordinates(
    double ecliptic_longitude_degrees, double ecliptic_longitude_minutes,
    double ecliptic_longitude_seconds, double ecliptic_latitude_degrees,
    double ecliptic_latitude_minutes, double ecliptic_latitude_seconds,
    double greenwich_day, int greenwich_month, int greenwich_year,
    TEquatorialCoordinates2 expected_result);

void test_equatorial_coordinate_to_ecliptic_coordinate(
    double ra_hours, double ra_minutes, double ra_seconds, double dec_degrees,
    double dec_minutes, double dec_seconds, double gw_day, int gw_month,
    int gw_year, TEclipticCoordinates expected_result);

void test_equatorial_coordinate_to_galactic_coordinate(
    double ra_hours, double ra_minutes, double ra_seconds, double dec_degrees,
    double dec_minutes, double dec_seconds,
    TGalacticCoordinates expected_result);

void test_galactic_coordinates_to_equatorial_coordinates(
    double gal_long_deg, double gal_long_min, double gal_long_sec,
    double gal_lat_deg, double gal_lat_min, double gal_lat_sec,
    TEquatorialCoordinates2 expected_result);

void test_angle_between_two_objects(
    double ra_long1_hour_deg, double ra_long1_min, double ra_long1_sec,
    double dec_lat1_deg, double dec_lat1_min, double dec_lat1_sec,
    double ra_long2_hour_deg, double ra_long2_min, double ra_long2_sec,
    double dec_lat2_deg, double dec_lat2_min, double dec_lat2_sec,
    TAngleMeasurementUnits hour_or_degree, TAngle expected_result);

void test_rising_and_setting(double ra_hours, double ra_minutes,
                             double ra_seconds, double dec_deg, double dec_min,
                             double dec_sec, double gw_date_day,
                             int gw_date_month, int gw_date_year,
                             double geog_long_deg, double geog_lat_deg,
                             double vert_shift_deg, TRiseSet expected_result);

void test_correct_for_precession(double ra_hour, double ra_minutes,
                                 double ra_seconds, double dec_deg,
                                 double dec_minutes, double dec_seconds,
                                 double epoch1_day, int epoch1_month,
                                 int epoch1_year, double epoch2_day,
                                 int epoch2_month, int epoch2_year,
                                 TCorrectedPrecession expected_result);

void test_nutation_in_ecliptic_longitude_and_obliquity(
    double greenwich_day, int greenwich_month, int greenwich_year,
    TNutation expected_result);

void test_correct_for_aberration(
    double ut_hour, double ut_minutes, double ut_seconds, double gw_day,
    int gw_month, int gw_year, double true_ecl_long_deg,
    double true_ecl_long_min, double true_ecl_long_sec, double true_ecl_lat_deg,
    double true_ecl_lat_min, double true_ecl_lat_sec,
    TCorrectedEclipticCoordinates expected_result);

void test_atmospheric_refraction(
    double true_ra_hour, double true_ra_min, double true_ra_sec,
    double true_dec_deg, double true_dec_min, double true_dec_sec,
    TCoordinateType coordinate_type1, double geog_long_deg, double geog_lat_deg,
    int daylight_saving_hours, int timezone_hours, double lcd_day,
    int lcd_month, int lcd_year, double lct_hour, double lct_min,
    double lct_sec, double atmospheric_pressure_mbar,
    double atmospheric_temperature_celsius,
    TCorrectedRefraction expected_result);

void test_corrections_for_geocentric_parallax(
    double ra_hour, double ra_min, double ra_sec, double dec_deg,
    double dec_min, double dec_sec, TCoordinateType coordinate_type,
    double equatorial_hor_parallax_deg, double geog_long_deg,
    double geog_lat_deg, double height_m, int daylight_saving,
    int timezone_hours, double lcd_day, int lcd_month, int lcd_year,
    double lct_hour, double lct_min, double lct_sec,
    TCorrectedParallax expected_result);

void test_heliographic_coordinates(double helio_position_angle_deg,
                                   double helio_displacement_arcmin,
                                   double gwdate_day, int gwdate_month,
                                   int gwdate_year,
                                   THeliographicCoordinates expected_result);

void test_carrington_rotation_number(double gwdate_day, int gwdate_month,
                                     int gwdate_year, int expected_value);

void test_selenographic_coordinates1(
    double gwdate_day, int gwdate_month, int gwdate_year,
    TSelenographicSubEarthCoordinates expected_result);

void test_selenographic_coordinates2(
    double gwdate_day, int gwdate_month, int gwdate_year,
    TSelenographicSubSolarCoordinates expected_result);
#endif