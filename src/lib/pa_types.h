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
#endif