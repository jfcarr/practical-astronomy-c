#include <stdlib.h>

#ifndef planets_data_inc
#define planets_data_inc

struct PlanetRecord {
  char name[25];                      /** Name of planet. */
  double tp_PeriodOrbit;              /** Period of orbit. */
  double long_LongitudeEpoch;         /** Longitude at the epoch. */
  double peri_LongitudePerihelion;    /** Longitude of the perihelion. */
  double ecc_EccentricityOrbit;       /** Eccentricity of the orbit. */
  double axis_AxisOrbit;              /** Semi-major axis of the orbit. */
  double incl_OrbitalInclination;     /** Orbital inclination. */
  double node_LongitudeAscendingNode; /** Longitude of the ascending node. */
  double theta0_AngularDiameter;      /** Angular diameter at 1 AU. */
  double v0_VisualMagnitude;          /** Visual magnitude at 1 AU. */
};

typedef struct {
  char name[25];   /** Name of planet */
  double value1;   /** Working value 1 */
  double value2;   /** Working value 2 */
  double value3;   /** Working value 3 */
  double value4;   /** Working value 4 */
  double value5;   /** Working value 5 */
  double value6;   /** Working value 6 */
  double value7;   /** Working value 7 */
  double value8;   /** Working value 8 */
  double value9;   /** Working value 9 */
  double ap_value; /** Working AP value */
} PlanetDataPrecise;

struct PlanetRecord populate_planet_data(
    char *name, double tp_PeriodOrbit, double long_LongitudeEpoch,
    double peri_LongitudePerihelion, double ecc_EccentricityOrbit,
    double axis_AxisOrbit, double incl_OrbitalInclination,
    double node_LongitudeAscendingNode, double theta0_AngularDiameter,
    double v0_VisualMagnitude);

PlanetDataPrecise populate_precise_planet_data(char *name, double value1,
                                               double value2, double value3,
                                               double value4, double value5,
                                               double value6, double value7,
                                               double value8, double value9,
                                               double ap_value);

struct PlanetRecord get_planet_data(char *planetName);

PlanetDataPrecise
get_precise_planet_data(char *planet_name,
                        PlanetDataPrecise precise_planet_data[],
                        size_t precise_planet_data_size);
#endif