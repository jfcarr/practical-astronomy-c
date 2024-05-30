#ifndef _pa_lib_types
#define _pa_lib_types

#define PA_PI 3.14159265358979323846

/**
 * Warning flags for calculation results.
 */
enum WarningFlags {
  WarningFlag_OK,     /**< Calculation result is OK. */
  WarningFlag_Warning /**< Calculation result is invalid/inaccurate. */
};

enum RiseSetStatus {
  RiseSetStatus_OK,
  RiseSetStatus_NEVER_RISES,
  RiseSetStatus_CIRCUMPOLAR,
  RiseSetStatus_GST_TO_UT_CONVERSION_WARNING
};

enum TwilightStatus {
  TwilightStatus_OK,
  TwilightStatus_LASTS_ALL_NIGHT,
  TwilightStatus_SUN_TOO_FAR_BELOW_HORIZON,
  TwilightStatus_GST_TO_UT_CONVERSION_WARNING
};

enum TwilightType {
  TwilightType_CIVIL = 6,
  TwilightType_NAUTICAL = 12,
  TwilightType_ASTRONOMICAL = 18,
};

/**
 * Angle measurement units.
 */
enum AngleMeasurementType {
  AngleMeasurementType_DEGREES,
  AngleMeasurementType_HOURS
};

/**
 * Coordinate types
 */
enum CoordinateType {
  CoordinateType_ACTUAL,  /**< actual/real */
  CoordinateType_APPARENT /**< apparent (observer) */
};

enum AccuracyLevel { AccuracyLevel_APPROXIMATE, AccuracyLevel_PRECISE };

/**
 * Structure to hold a Date value:
 *
 * int month
 * int day
 * int year
 */
typedef struct pa_full_date {
  int month;
  int day;
  int year;
} TFullDate;

typedef struct pa_full_date_precise {
  int month;
  double day;
  int year;
} TFullDatePrecise;

/**
 * Structure to hold a Time value:
 *
 * int hours
 * int minutes
 * double seconds
 */
typedef struct pa_full_time {
  int hours;
  int minutes;
  double seconds;
} TFullTime;

/**
 * Structure to hold a Time value, along with a calculation warning:
 *
 * int hours
 * int minutes
 * double seconds
 * WarningFlags warning_flag
 */
typedef struct pa_full_time_warning {
  int hours;
  int minutes;
  double seconds;
  enum WarningFlags warning_flag;
} TFullTimeWarning;

/**
 * Structure to hold a DateTime value:
 *
 * int month
 * int day
 * int year
 * int hours
 * int minutes
 * double seconds
 */
typedef struct pa_full_datetime {
  int month;
  int day;
  int year;
  int hours;
  int minutes;
  double seconds;
} TFullDateTime;

/**
 * Structure to hold an Angle value:
 *
 * double degrees
 * double minutes
 * double seconds
 */
typedef struct pa_angle {
  double degrees;
  double minutes;
  double seconds;
} TAngle;

/**
 * Structure to hold an Hour Angle value:
 *
 * double hours
 * double minutes
 * double seconds
 */
typedef struct pa_hour_angle {
  double hours;
  double minutes;
  double seconds;
} THourAngle;

/**
 * Structure to hold a Right Ascension value:
 *
 * double hours
 * double minutes
 * double seconds
 */
typedef struct pa_right_ascension {
  double hours;
  double minutes;
  double seconds;
} TRightAscension;

/**
 * Structure to hold a Horizon Coordinate value:
 *
 * Azimuth: degrees, minutes, and seconds
 * Altitude: degrees, minutes, and seconds
 */
typedef struct pa_horizon_coordinates {
  double azimuth_degrees;
  double azimuth_minutes;
  double azimuth_seconds;
  double altitude_degrees;
  double altitude_minutes;
  double altitude_seconds;
} THorizonCoordinates;

/**
 * Structure to hold a Equatorial Coordinate value:
 *
 * Hour Angle: hours, minutes, and seconds
 * Declination: degrees, minutes, and seconds
 */
typedef struct pa_equatorial_coordinates {
  double hour_angle_hours;
  double hour_angle_minutes;
  double hour_angle_seconds;
  double declination_degrees;
  double declination_minutes;
  double declination_seconds;
} TEquatorialCoordinates;

/**
 * Structure to hold a Equatorial Coordinate value:
 *
 * Right Ascension: hours, minutes, and seconds
 * Declination: degrees, minutes, and seconds
 */
typedef struct pa_equatorial_coordinates_2 {
  double right_ascension_hours;
  double right_ascension_minutes;
  double right_ascension_seconds;
  double declination_degrees;
  double declination_minutes;
  double declination_seconds;
} TEquatorialCoordinates2, TCorrectedPrecession, TCorrectedRefraction,
    TCorrectedParallax;

typedef struct pa_ecliptic_galactic_coordinates {
  double longitude_degrees;
  double longitude_minutes;
  double longitude_seconds;
  double latitude_degrees;
  double latitude_minutes;
  double latitude_seconds;
} TEclipticCoordinates, TCorrectedEclipticCoordinates, TGalacticCoordinates;

typedef struct pa_rise_set {
  enum RiseSetStatus rise_set_status;
  double ut_rise_hour;
  double ut_rise_minute;
  double ut_set_hour;
  double ut_set_minute;
  double az_rise;
  double az_set;
} TRiseSet;

typedef struct pa_nutation {
  double nutation_in_ecliption_longitude;
  double nutation_in_obliquity;
} TNutation;

typedef struct pa_parallax_helper {
  double p;
  double q;
} TParallaxHelper;

typedef struct pa_heliographic_coordinates {
  double longitude_degrees;
  double latitude_degrees;
} THeliographicCoordinates;

typedef struct pa_selenographic_subearth_coordinates {
  double longitude;
  double latitude;
  double position_angle_of_pole;
} TSelenographicSubEarthCoordinates;

typedef struct pa_selenographic_subsolar_coordinates {
  double longitude;
  double co_longitude;
  double latitude;
} TSelenographicSubSolarCoordinates;

typedef struct pa_sun_position {
  double sun_ra_hour;
  double sun_ra_min;
  double sun_ra_sec;
  double sun_dec_deg;
  double sun_dec_min;
  double sun_dec_sec;
} TSunPosition;

typedef struct pa_sun_distance_size {
  double sun_dist_km;
  double sun_ang_size_deg;
  double sun_ang_size_min;
  double sun_ang_size_sec;
} TSunDistanceSize;

typedef struct pa_sunrise_sunset_info {
  double local_sunrise_hour;
  double local_sunrise_minute;
  double local_sunset_hour;
  double local_sunset_minute;
  double azimuth_of_sunrise_deg;
  double azimuth_of_sunset_deg;
  enum RiseSetStatus status;
} TSunriseSunsetInfo;

typedef struct pa_sunrise_lct_helper {
  double a;
  double x;
  double y;
  double la;
  enum RiseSetStatus s;
} TSunriseLctHelper;

typedef struct pa_twilight_info {
  double am_twilight_begins_hour;
  double am_twilight_begins_min;
  double pm_twilight_ends_hour;
  double pm_twilight_ends_min;
  enum TwilightStatus status;
} TTwilightInfo;

typedef struct pa_twilight_lct_helper {
  double a;
  double x;
  double y;
  double la;
  enum RiseSetStatus s;
} TTwilightLctHelper;

typedef struct pa_twilight_lct_helper2 {
  double a;
  double x;
  double y;
  double la;
  enum TwilightStatus s;
} TTwilightLctHelper2;

typedef struct pa_equation_of_time {
  double equation_of_time_min;
  double equation_of_time_sec;
} TEquationOfTime;

typedef struct pa_planet_position {
  double planet_ra_hour;
  double planet_ra_min;
  double planet_ra_sec;
  double planet_dec_deg;
  double planet_dec_min;
  double planet_dec_sec;
} TPlanetPosition;

typedef struct pa_planet_coordinates {
  double planet_longitude;
  double planet_latitude;
  double planet_distance_au;
  double planet_h_long1;
  double planet_h_long2;
  double planet_h_lat;
  double planet_r_vect;
} TPlanetCoordinates;

typedef struct pa_planet_longlat_l4685 {
  double qa;
  double qb;
} TPlanetLongLatL4685;

typedef struct pa_planet_longlat_l4735 {
  double qa;
  double qb;
  double qc;
  double qe;
} TPlanetLongLatL4735;

typedef struct pa_planet_longlat_l4810 {
  double a;
  double sa;
  double ca;
  double qc;
  double qe;
  double qa;
  double qb;
} TPlanetLongLatL4810;

typedef struct pa_planet_longlat_l4945 {
  double qa;
  double qb;
  double qc;
  double qd;
  double qe;
  double qf;
  double qg;
} TPlanetLongLatL4945;

typedef struct pa_planet_visual_aspects {
  double distance_au;
  double ang_dia_arcsec;
  double phase;
  double light_time_hour;
  double light_time_minutes;
  double light_time_seconds;
  double pos_angle_bright_limb_deg;
  double approximate_magnitude;
} TPlanetVisualAspects;

typedef struct pa_comet_position {
  double comet_ra_hour;
  double comet_ra_min;
  double comet_ra_sec;
  double comet_dec_deg;
  double comet_dec_min;
  double comet_dec_sec;
  double comet_dist_earth;
} TCometPosition;

typedef struct pa_comet_long_lat_dist {
  double comet_long_deg;
  double comet_lat_deg;
  double comet_dist_au;
} TCometLongLatDist;

typedef struct pa_binary_star_orbital_data {
  double position_angle_deg;
  double separation_arcsec;
} TBinaryStarOrbitalData;

typedef struct pa_moon_approximate_position {
  double moon_ra_hour;
  double moon_ra_min;
  double moon_ra_sec;
  double moon_dec_deg;
  double moon_dec_min;
  double moon_dec_sec;
} TMoonApproximatePosition;

typedef struct pa_moon_precise_position {
  double moon_ra_hour;
  double moon_ra_min;
  double moon_ra_sec;
  double moon_dec_deg;
  double moon_dec_min;
  double moon_dec_sec;
  double earth_moon_dist_km;
  double moon_hor_parallax_deg;
} TMoonPrecisePosition;

typedef struct pa_moon_long_lat_hp {
  double moon_long_deg;
  double moon_lat_deg;
  double moon_hor_para;
} TMoonLongLatHP;

typedef struct pa_moon_phase {
  double moon_phase;
  double bright_limb_deg;
} TMoonPhase;

typedef struct pa_moon_new_full {
  double nm_local_time_hour;
  double nm_local_time_min;
  double nm_local_date_day;
  int nm_local_date_month;
  int nm_local_date_year;
  double fm_local_time_hour;
  double fm_local_time_min;
  double fm_local_date_day;
  int fm_local_date_month;
  int fm_local_date_year;
} TMoonNewFull;

typedef struct pa_new_moon_full_moon_l6855 {
  double a;
  double b;
  double f;
} TNewMoonFullMoonL6855;

typedef struct pa_moon_dist_diameter_hp {
  double earth_moon_dist;
  double ang_diameter_deg;
  double ang_diameter_min;
  double hor_parallax_deg;
  double hor_parallax_min;
  double hor_parallax_sec;
} TMoonDistDiameterHP;

typedef struct pa_moon_rise_set {
  double mr_local_time_hour;
  double mr_local_time_min;
  double mr_local_date_day;
  int mr_local_date_month;
  int mr_local_date_year;
  double mr_azimuth_deg;
  double ms_local_time_hour;
  double ms_local_time_min;
  double ms_local_date_day;
  int ms_local_date_month;
  int ms_local_date_year;
  double ms_azimuth_deg;
} TMoonRiseSet;

typedef struct pa_moon_rise_lct_l6680 {
  double ut;
  double lct;
  double dy1;
  int mn1;
  int yr1;
  double gdy;
  int gmn;
  int gyr;
} TMoonRiseLCTL6680, TMoonSetLCTL6680;

typedef struct pa_moon_rise_lct_l6700 {
  double mm;
  double bm;
  double pm;
  double dp;
  double th;
  double di;
  double p;
  double q;
  double lu;
  double lct;
} TMoonRiseLCTL6700, TMoonSetLCTL6700;

typedef struct pa_moon_rise_lc_dmy_l6680 {
  double ut;
  double lct;
  double dy1;
  int mn1;
  int yr1;
  double gdy;
  int gmn;
  int gyr;
} TMoonRiseLcDMYL6680, TMoonSetLcDMYL6680;

typedef struct pa_moon_rise_lc_dmy_l6700 {
  double mm;
  double bm;
  double pm;
  double dp;
  double th;
  double di;
  double p;
  double q;
  double lu;
  double lct;
} TMoonRiseLcDMYL6700, TMoonSetLcDMYL6700;

typedef struct pa_moon_rise_az_l6680 {
  double ut;
  double lct;
  double dy1;
  int mn1;
  int yr1;
  double gdy;
  int gmn;
  int gyr;
} TMoonRiseAzL6680, TMoonSetAzL6680;

typedef struct pa_moon_rise_az_l6700 {
  double mm;
  double bm;
  double pm;
  double dp;
  double th;
  double di;
  double p;
  double q;
  double lu;
  double lct;
  double au;
} TMoonRiseAzL6700, TMoonSetAzL6700;
#endif
