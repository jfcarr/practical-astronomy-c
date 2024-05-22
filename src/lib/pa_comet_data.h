#include <stdlib.h>

#ifndef comet_data_inc
#define comet_data_inc

struct CometRecord {
  char name[50];                        /** Name of comet */
  double epoch_EpochOfPerihelion;       /** Epoch of the perihelion */
  double peri_LongitudeOfPerihelion;    /** Longitude of the perihelion */
  double node_LongitudeOfAscendingNode; /** Longitude of the ascending node */
  double period_PeriodOfOrbit;          /** Period of the orbit */
  double axis_SemiMajorAxisOfOrbit;     /** Semi-major axis of the orbit */
  double ecc_EccentricityOfOrbit;       /** Eccentricity of the orbit */
  double incl_InclinationOfOrbit;       /** Inclination of the orbit */
};

struct CometRecord populate_comet_data(
    char *name, double epoch_EpochOfPerihelion,
    double peri_LongitudeOfPerihelion, double node_LongitudeOfAscendingNode,
    double period_PeriodOfOrbit, double axis_SemiMajorAxisOfOrbit,
    double ecc_EccentricityOfOrbit, double incl_InclinationOfOrbit);

struct CometRecord get_comet_data(char *cometName);
#endif