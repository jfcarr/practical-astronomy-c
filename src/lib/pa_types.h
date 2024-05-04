#ifndef _pa_lib_types
#define _pa_lib_types
/**
 * Warning flags for calculation results.
 */
enum WarningFlags {
  WarningFlag_OK,     /**< Calculation result is OK. */
  WarningFlag_Warning /**< Calculation result is invalid/inaccurate. */
};

/**
 * Angle measurement units.
 */
typedef enum pa_angle_measurement_units {
  AngleMeasurement_Hours,
  AngleMeasurement_Degrees
} TAngleMeasurementUnits;

typedef enum pa_rise_set_status {
  RiseSetStatus_Ok,          /**< Object rises and sets */
  RiseSetStatus_NeverRises,  /**< Object is never visible above the horizon. */
  RiseSetStatus_Circumpolar, /**< Object never sets. */
  RiseSetStatus_GstToUtConversionWarning /**< Error in conversion. */
} TRiseSetStatus;

/**
 * Coordinate types
 */
typedef enum pa_coordinate_type {
  CoordinateType_Actual,  /**< actual/real */
  CoordinateType_Apparent /**< apparent (observer) */
} TCoordinateType;

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
  TRiseSetStatus rise_set_status;
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
#endif
