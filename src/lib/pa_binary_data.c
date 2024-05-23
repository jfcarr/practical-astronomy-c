#include "pa_binary_data.h"
#include <string.h>

struct BinaryStarData populate_binary_star_data(char *name, double period,
                                                double epoch_peri,
                                                double long_peri, double ecc,
                                                double axis, double incl,
                                                double pa_node) {
  struct BinaryStarData return_data;

  strcpy(return_data.name, name);
  return_data.axis = axis;
  return_data.ecc = ecc;
  return_data.epoch_peri = epoch_peri;
  return_data.incl = incl;
  return_data.long_peri = long_peri;
  return_data.pa_node = pa_node;
  return_data.period = period;

  return return_data;
}

struct BinaryStarData get_binary_star_data(char *binary_star_name) {
  struct BinaryStarData binary_star_data[10];

  binary_star_data[0] = populate_binary_star_data(
      "eta-Cor", 41.623, 1934.008, 219.907, 0.2763, 0.907, 59.025, 23.717);

  binary_star_data[1] = populate_binary_star_data(
      "gamma-Vir", 171.37, 1836.433, 252.88, 0.8808, 3.746, 146.05, 31.78);

  binary_star_data[2] = populate_binary_star_data(
      "eta-Cas", 480.0, 1889.6, 268.59, 0.497, 11.9939, 34.76, 278.42);

  binary_star_data[3] = populate_binary_star_data(
      "zeta-Ori", 1508.6, 2070.6, 47.3, 0.07, 2.728, 72.0, 155.5);

  binary_star_data[4] = populate_binary_star_data(
      "alpha-CMa", 50.09, 1894.13, 147.27, 0.5923, 7.5, 136.53, 44.57);

  binary_star_data[5] = populate_binary_star_data(
      "delta-Gem", 1200.0, 1437.0, 57.19, 0.11, 6.9753, 63.28, 18.38);

  binary_star_data[6] = populate_binary_star_data(
      "alpha-Gem", 420.07, 1965.3, 261.43, 0.33, 6.295, 115.94, 40.47);

  binary_star_data[7] = populate_binary_star_data(
      "aplah-CMi", 40.65, 1927.6, 269.8, 0.4, 4.548, 35.7, 284.3);

  binary_star_data[8] = populate_binary_star_data(
      "alpha-Cen", 79.92, 1955.56, 231.56, 0.516, 17.583, 79.24, 204.868);

  binary_star_data[9] = populate_binary_star_data("alpha Sco", 900.0, 1889.0,
                                                  0.0, 0.0, 3.21, 86.3, 273.0);

  struct BinaryStarData return_data;

  for (int i = 0; i < sizeof(binary_star_data) / sizeof(binary_star_data[0]);
       i++) {
    if (strcmp(binary_star_data[i].name, binary_star_name) == 0) {
      return_data = binary_star_data[i];

      return return_data;
    }
  }

  strcpy(return_data.name, "NOTFOUND");
  return_data.axis = -99;
  return_data.ecc = -99;
  return_data.epoch_peri = -99;
  return_data.incl = -99;
  return_data.long_peri = -99;
  return_data.pa_node = -99;
  return_data.period = -99;

  return return_data;
}