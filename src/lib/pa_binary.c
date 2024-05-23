#include "pa_binary.h"
#include "pa_binary_data.h"
#include "pa_macros.h"
#include "pa_util.h"
#include <math.h>
#include <stdbool.h>

/**
 * Calculate orbital data for binary star.
 */
TBinaryStarOrbitalData binary_star_orbit(double greenwich_date_day,
                                         int greenwich_date_month,
                                         int greenwich_date_year,
                                         char *binary_name) {
  struct BinaryStarData binary_info = get_binary_star_data(binary_name);

  double y_years =
      greenwich_date_year +
      (ma_civil_date_to_julian_date(greenwich_date_day, greenwich_date_month,
                                    greenwich_date_year) -
       ma_civil_date_to_julian_date(0, 1, greenwich_date_year)) /
          365.242191 -
      binary_info.epoch_peri;
  double m_deg = 360 * y_years / binary_info.period;
  double m_rad = degrees_to_radians(m_deg - 360 * floor(m_deg / 360));
  double eccentricity = binary_info.ecc;
  double true_anomaly_rad = ma_true_anomaly(m_rad, eccentricity);
  double r_arcsec =
      (1 - eccentricity * cos(ma_eccentric_anomaly(m_rad, eccentricity))) *
      binary_info.axis;
  double ta_peri_rad =
      true_anomaly_rad + degrees_to_radians(binary_info.long_peri);

  double y = sin(ta_peri_rad) * cos(degrees_to_radians(binary_info.incl));
  double x = cos(ta_peri_rad);
  double a_deg = ma_degrees(atan2(y, x));
  double theta_deg1 = a_deg + binary_info.pa_node;
  double theta_deg2 = theta_deg1 - 360 * floor(theta_deg1 / 360);
  double rho_arcsec =
      r_arcsec * cos(ta_peri_rad) /
      cos(degrees_to_radians((theta_deg2 - binary_info.pa_node)));

  double position_angle_deg = dround(theta_deg2, 1);
  double separation_arcsec = dround(rho_arcsec, 2);

  return (TBinaryStarOrbitalData){position_angle_deg, separation_arcsec};
}
