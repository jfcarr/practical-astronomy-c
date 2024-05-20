#include "pa_planets_data.h"
#include <string.h>

struct PlanetRecord populate_planet_data(
    char *name, double tp_PeriodOrbit, double long_LongitudeEpoch,
    double peri_LongitudePerihelion, double ecc_EccentricityOrbit,
    double axis_AxisOrbit, double incl_OrbitalInclination,
    double node_LongitudeAscendingNode, double theta0_AngularDiameter,
    double v0_VisualMagnitude) {
  struct PlanetRecord return_data;

  strcpy(return_data.name, name);
  return_data.tp_PeriodOrbit = tp_PeriodOrbit;
  return_data.long_LongitudeEpoch = long_LongitudeEpoch;
  return_data.peri_LongitudePerihelion = peri_LongitudePerihelion;
  return_data.ecc_EccentricityOrbit = ecc_EccentricityOrbit;
  return_data.axis_AxisOrbit = axis_AxisOrbit;
  return_data.incl_OrbitalInclination = incl_OrbitalInclination;
  return_data.node_LongitudeAscendingNode = node_LongitudeAscendingNode;
  return_data.theta0_AngularDiameter = theta0_AngularDiameter;
  return_data.v0_VisualMagnitude = v0_VisualMagnitude;

  return return_data;
}

PlanetDataPrecise populate_precise_planet_data(char *name, double value1,
                                               double value2, double value3,
                                               double value4, double value5,
                                               double value6, double value7,
                                               double value8, double value9,
                                               double ap_value) {
  PlanetDataPrecise return_data;

  strcpy(return_data.name, name);
  return_data.value1 = value1;
  return_data.value2 = value2;
  return_data.value3 = value3;
  return_data.value4 = value4;
  return_data.value5 = value5;
  return_data.value6 = value6;
  return_data.value7 = value7;
  return_data.value8 = value8;
  return_data.value9 = value9;
  return_data.ap_value = ap_value;

  return return_data;
}

struct PlanetRecord get_planet_data(char *planetName) {
  struct PlanetRecord planet_data[9];

  planet_data[0] =
      populate_planet_data("Mercury", 0.24085, 75.5671, 77.612, 0.205627,
                           0.387098, 7.0051, 48.449, 6.74, -0.42);
  planet_data[1] =
      populate_planet_data("Venus", 0.615207, 272.30044, 131.54, 0.006812,
                           0.723329, 3.3947, 76.769, 16.92, -4.4);
  planet_data[2] =
      populate_planet_data("Earth", 0.999996, 99.556772, 103.2055, 0.016671,
                           0.999985, -99.0, -99.0, -99.0, -99.0);
  planet_data[3] =
      populate_planet_data("Mars", 1.880765, 109.09646, 336.217, 0.093348,
                           1.523689, 1.8497, 49.632, 9.36, -1.52);
  planet_data[4] =
      populate_planet_data("Jupiter", 11.857911, 337.917132, 14.6633, 0.048907,
                           5.20278, 1.3035, 100.595, 196.74, -9.4);
  planet_data[5] =
      populate_planet_data("Saturn", 29.310579, 172.398316, 89.567, 0.053853,
                           9.51134, 2.4873, 113.752, 165.6, -8.88);
  planet_data[6] = populate_planet_data("Uranus", 84.039492, 356.135400,
                                        172.884833, 0.046321, 19.21814,
                                        0.773059, 73.926961, 65.8, -7.19);
  planet_data[7] =
      populate_planet_data("Neptune", 165.845392, 326.895127, 23.07, 0.010483,
                           30.1985, 1.7673, 131.879, 62.2, -6.87);

  struct PlanetRecord return_data;

  for (int i = 0; i < sizeof(planet_data) / sizeof(planet_data[0]); i++) {
    if (strcmp(planet_data[i].name, planetName) == 0) {
      return_data = planet_data[i];

      return return_data;
    }
  }

  strcpy(return_data.name, "NOTFOUND");
  return_data.tp_PeriodOrbit = -99;
  return_data.long_LongitudeEpoch = -99;
  return_data.peri_LongitudePerihelion = -99;
  return_data.ecc_EccentricityOrbit = -99;
  return_data.axis_AxisOrbit = -99;
  return_data.incl_OrbitalInclination = -99;
  return_data.node_LongitudeAscendingNode = -99;
  return_data.theta0_AngularDiameter = -99;
  return_data.v0_VisualMagnitude = -99;

  return return_data;
}

PlanetDataPrecise
get_precise_planet_data(char *planet_name,
                        PlanetDataPrecise precise_planet_data[],
                        size_t precise_planet_data_size) {
  PlanetDataPrecise return_data;

  for (int i = 0; i < precise_planet_data_size / sizeof(precise_planet_data[0]);
       i++) {
    if (strcmp(precise_planet_data[i].name, planet_name) == 0) {
      return_data = precise_planet_data[i];

      return return_data;
    }
  }

  strcpy(return_data.name, "NOTFOUND");
  return_data.value1 = -99;
  return_data.value2 = -99;
  return_data.value3 = -99;
  return_data.value4 = -99;
  return_data.value5 = -99;
  return_data.value6 = -99;
  return_data.value7 = -99;
  return_data.value8 = -99;
  return_data.value9 = -99;
  return_data.ap_value = -99;

  return return_data;
}