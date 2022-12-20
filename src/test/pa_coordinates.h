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
#endif