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
#endif
