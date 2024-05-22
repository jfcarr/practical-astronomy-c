#include "pa_comet_data.h"
#include <string.h>

struct CometRecord populate_comet_data(
    char *name, double epoch_EpochOfPerihelion,
    double peri_LongitudeOfPerihelion, double node_LongitudeOfAscendingNode,
    double period_PeriodOfOrbit, double axis_SemiMajorAxisOfOrbit,
    double ecc_EccentricityOfOrbit, double incl_InclinationOfOrbit) {
  struct CometRecord return_data;

  strcpy(return_data.name, name);
  return_data.epoch_EpochOfPerihelion = epoch_EpochOfPerihelion;
  return_data.peri_LongitudeOfPerihelion = peri_LongitudeOfPerihelion;
  return_data.node_LongitudeOfAscendingNode = node_LongitudeOfAscendingNode;
  return_data.period_PeriodOfOrbit = period_PeriodOfOrbit;
  return_data.axis_SemiMajorAxisOfOrbit = axis_SemiMajorAxisOfOrbit;
  return_data.ecc_EccentricityOfOrbit = ecc_EccentricityOfOrbit;
  return_data.incl_InclinationOfOrbit = incl_InclinationOfOrbit;

  return return_data;
}

struct CometRecord get_comet_data(char *cometName) {
  struct CometRecord comet_data[15];

  comet_data[0] = populate_comet_data("Encke", 1974.32, 160.1, 334.2, 3.3, 2.21,
                                      0.85, 12.0);

  comet_data[1] = populate_comet_data("Temple 2", 1972.87, 310.2, 119.3, 5.26,
                                      3.02, 0.55, 12.5);

  comet_data[2] = populate_comet_data("Haneda-Campos", 1978.77, 12.02, 131.7,
                                      5.37, 3.07, 0.64, 5.81);

  comet_data[3] = populate_comet_data("Schwassmann-Wachmann 2", 1974.7, 123.3,
                                      126.0, 6.51, 3.49, 0.39, 3.7);

  comet_data[4] = populate_comet_data("Borrelly", 1974.36, 67.8, 75.1, 6.76,
                                      3.58, 0.63, 30.2);

  comet_data[5] = populate_comet_data("Whipple", 1970.77, 18.2, 188.4, 7.47,
                                      3.82, 0.35, 10.2);

  comet_data[6] = populate_comet_data("Oterma", 1958.44, 150.0, 155.1, 7.88,
                                      3.96, 0.14, 4.0);

  comet_data[7] = populate_comet_data("Schaumasse", 1960.29, 138.1, 86.2, 8.18,
                                      4.05, 0.71, 12.0);

  comet_data[8] = populate_comet_data("Comas Sola", 1969.83, 102.9, 62.8, 8.55,
                                      4.18, 0.58, 13.4);

  comet_data[9] = populate_comet_data("Schwassmann-Wachmann 1", 1974.12, 334.1,
                                      319.6, 15.03, 6.09, 0.11, 9.7);

  comet_data[10] = populate_comet_data("Neujmin 1", 1966.94, 334.0, 347.2,
                                       17.93, 6.86, 0.78, 15.0);

  comet_data[11] = populate_comet_data("Crommelin", 1956.82, 86.4, 250.4, 27.89,
                                       9.17, 0.92, 28.9);

  comet_data[12] = populate_comet_data("Olbers", 1956.46, 150.0, 85.4, 69.47,
                                       16.84, 0.93, 44.6);

  comet_data[13] = populate_comet_data("Pons-Brooks", 1954.39, 94.2, 255.2,
                                       70.98, 17.2, 0.96, 74.2);

  comet_data[14] = populate_comet_data("Halley", 1986.112, 170.011, 58.154,
                                       76.0081, 17.9435, 0.9673, 162.2384);

  struct CometRecord return_data;

  for (int i = 0; i < sizeof(comet_data) / sizeof(comet_data[0]); i++) {
    if (strcmp(comet_data[i].name, cometName) == 0) {
      return_data = comet_data[i];

      return return_data;
    }
  }

  strcpy(return_data.name, "NOTFOUND");
  return_data.epoch_EpochOfPerihelion = -99;
  return_data.peri_LongitudeOfPerihelion = -99;
  return_data.node_LongitudeOfAscendingNode = -99;
  return_data.period_PeriodOfOrbit = -99;
  return_data.axis_SemiMajorAxisOfOrbit = -99;
  return_data.ecc_EccentricityOfOrbit = -99;
  return_data.incl_InclinationOfOrbit = -99;

  return return_data;
}