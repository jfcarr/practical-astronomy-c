#ifndef planets_data_inc
#define planets_data_inc

struct PlanetRecord {
  char name[25];
  double tp_PeriodOrbit;
  double long_LongitudeEpoch;
  double peri_LongitudePerihelion;
  double ecc_EccentricityOrbit;
  double axis_AxisOrbit;
  double incl_OrbitalInclination;
  double node_LongitudeAscendingNode;
  double theta0_AngularDiameter;
  double v0_VisualMagnitude;
};

struct PlanetRecord populate_planet_data(
    char *name, double tp_PeriodOrbit, double long_LongitudeEpoch,
    double peri_LongitudePerihelion, double ecc_EccentricityOrbit,
    double axis_AxisOrbit, double incl_OrbitalInclination,
    double node_LongitudeAscendingNode, double theta0_AngularDiameter,
    double v0_VisualMagnitude);

struct PlanetRecord get_planet_data(char *planetName);

#endif