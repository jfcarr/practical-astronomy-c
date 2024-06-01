#include "pa_eclipses.h"
#include "../lib/pa_eclipses.h"
#include "../lib/pa_util.h"
#include <assert.h>
#include <math.h>

void test_lunar_eclipse_occurrence(double local_date_day, int local_date_month,
                                   int local_date_year, bool is_daylight_saving,
                                   int zone_correction_hours,
                                   TLunarEclipseOccurrence expected_result) {
  TLunarEclipseOccurrence actual_result = lunar_eclipse_occurrence(
      local_date_day, local_date_month, local_date_year, is_daylight_saving,
      zone_correction_hours);

  printf("[Lunar Eclipse Occurrence]\n");
  printf("\tExpected:\n");
  printf("\t\tDate is %d/%0.0f/%d\n", expected_result.event_date_month,
         expected_result.event_date_day, expected_result.event_date_year);
  printf("\t\tStatus is %d\n", expected_result.status);
  printf("\tActual:\n");
  printf("\t\tDate is %d/%0.0f/%d\n", actual_result.event_date_month,
         actual_result.event_date_day, actual_result.event_date_year);
  printf("\t\tStatus is %d\n", actual_result.status);

  assert(actual_result.event_date_day == expected_result.event_date_day);
  assert(actual_result.event_date_month == expected_result.event_date_month);
  assert(actual_result.event_date_year == expected_result.event_date_year);
  assert(actual_result.status == expected_result.status);
}

void test_lunar_eclipse_circumstances(
    double local_date_day, int local_date_month, int local_date_year,
    bool is_daylight_saving, int zone_correction_hours,
    TLunarEclipseCircumstances expected_result) {
  TLunarEclipseCircumstances actual_result = lunar_eclipse_circumstances(
      local_date_day, local_date_month, local_date_year, is_daylight_saving,
      zone_correction_hours);

  printf("[Lunar Eclipse Circumstances]\n");
  printf("\tExpected:\n");
  printf("\t\tCertain Date is %0.0f/%0.0f/%0.0f\n",
         expected_result.lunar_eclipse_certain_datemonth,
         expected_result.lunar_eclipse_certain_dateday,
         expected_result.lunar_eclipse_certain_dateyear);
  printf("\t\tStart of Penumbral Phase is %0.0f h %0.0f m\n",
         expected_result.ut_start_pen_phase_hour,
         expected_result.ut_start_pen_phase_minutes);
  printf("\t\tStart of Umbral Phase is %0.0f h %0.0f m\n",
         expected_result.ut_start_umbral_phase_hour,
         expected_result.ut_start_umbral_phase_minutes);
  printf("\t\tStart of Total Phase is %0.0f h %0.0f m\n",
         expected_result.ut_start_total_phase_hour,
         expected_result.ut_start_total_phase_minutes);
  printf("\t\tMiddle of eclipse at %0.0f h %0.0f m\n",
         expected_result.ut_mid_eclipse_hour,
         expected_result.ut_mid_eclipse_minutes);
  printf("\t\tEnd of Total Phase is %0.0f h %0.0f m\n",
         expected_result.ut_end_total_phase_hour,
         expected_result.ut_end_total_phase_minutes);
  printf("\t\tEnd of Umbral Phase is %0.0f h %0.0f m\n",
         expected_result.ut_end_umbral_phase_hour,
         expected_result.ut_end_umbral_phase_minutes);
  printf("\t\tEnd of Penumbral Phase is %0.0f h %0.0f m\n",
         expected_result.ut_end_pen_phase_hour,
         expected_result.ut_end_pen_phase_minutes);
  printf("\t\tMagnitude is %0.2f\n", expected_result.eclipse_magnitude);
  printf("\tActual:\n");
  printf("\t\tCertain Date is %0.0f/%0.0f/%0.0f\n",
         actual_result.lunar_eclipse_certain_datemonth,
         actual_result.lunar_eclipse_certain_dateday,
         actual_result.lunar_eclipse_certain_dateyear);
  printf("\t\tStart of Penumbral Phase is %0.0f h %0.0f m\n",
         actual_result.ut_start_pen_phase_hour,
         actual_result.ut_start_pen_phase_minutes);
  printf("\t\tStart of Umbral Phase is %0.0f h %0.0f m\n",
         actual_result.ut_start_umbral_phase_hour,
         actual_result.ut_start_umbral_phase_minutes);
  printf("\t\tStart of Total Phase is %0.0f h %0.0f m\n",
         actual_result.ut_start_total_phase_hour,
         actual_result.ut_start_total_phase_minutes);
  printf("\t\tMiddle of eclipse at %0.0f h %0.0f m\n",
         actual_result.ut_mid_eclipse_hour,
         actual_result.ut_mid_eclipse_minutes);
  printf("\t\tEnd of Total Phase is %0.0f h %0.0f m\n",
         actual_result.ut_end_total_phase_hour,
         actual_result.ut_end_total_phase_minutes);
  printf("\t\tEnd of Umbral Phase is %0.0f h %0.0f m\n",
         actual_result.ut_end_umbral_phase_hour,
         actual_result.ut_end_umbral_phase_minutes);
  printf("\t\tEnd of Penumbral Phase is %0.0f h %0.0f m\n",
         actual_result.ut_end_pen_phase_hour,
         actual_result.ut_end_pen_phase_minutes);
  printf("\t\tMagnitude is %0.2f\n", actual_result.eclipse_magnitude);

  assert(actual_result.eclipse_magnitude == expected_result.eclipse_magnitude);
  assert(actual_result.lunar_eclipse_certain_dateday ==
         expected_result.lunar_eclipse_certain_dateday);
  assert(actual_result.lunar_eclipse_certain_datemonth ==
         expected_result.lunar_eclipse_certain_datemonth);
  assert(actual_result.lunar_eclipse_certain_dateyear ==
         expected_result.lunar_eclipse_certain_dateyear);
  assert(actual_result.ut_end_pen_phase_hour ==
         expected_result.ut_end_pen_phase_hour);
  assert(actual_result.ut_end_pen_phase_minutes ==
         expected_result.ut_end_pen_phase_minutes);
  assert(actual_result.ut_end_total_phase_hour ==
         expected_result.ut_end_total_phase_hour);
  assert(actual_result.ut_end_total_phase_minutes ==
         expected_result.ut_end_total_phase_minutes);
  assert(actual_result.ut_end_umbral_phase_hour ==
         expected_result.ut_end_umbral_phase_hour);
  assert(actual_result.ut_end_umbral_phase_minutes ==
         expected_result.ut_end_umbral_phase_minutes);
  assert(actual_result.ut_mid_eclipse_hour ==
         expected_result.ut_mid_eclipse_hour);
  assert(actual_result.ut_mid_eclipse_minutes ==
         expected_result.ut_mid_eclipse_minutes);
  assert(actual_result.ut_start_pen_phase_hour ==
         expected_result.ut_start_pen_phase_hour);
  assert(actual_result.ut_start_pen_phase_minutes ==
         expected_result.ut_start_pen_phase_minutes);
  assert(actual_result.ut_start_total_phase_hour ==
         expected_result.ut_start_total_phase_hour);
  assert(actual_result.ut_start_total_phase_minutes ==
         expected_result.ut_start_total_phase_minutes);
  assert(actual_result.ut_start_umbral_phase_hour ==
         expected_result.ut_start_umbral_phase_hour);
  assert(actual_result.ut_start_umbral_phase_minutes ==
         expected_result.ut_start_umbral_phase_minutes);
}