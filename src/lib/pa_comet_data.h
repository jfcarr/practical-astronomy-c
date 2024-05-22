#include <stdlib.h>

#ifndef comet_data_inc
#define comet_data_inc

struct CometDataElliptical {
  char name[50];                        /** Name of comet */
  double epoch_EpochOfPerihelion;       /** Epoch of the perihelion */
  double peri_LongitudeOfPerihelion;    /** Longitude of the perihelion */
  double node_LongitudeOfAscendingNode; /** Longitude of the ascending node */
  double period_PeriodOfOrbit;          /** Period of the orbit */
  double axis_SemiMajorAxisOfOrbit;     /** Semi-major axis of the orbit */
  double ecc_EccentricityOfOrbit;       /** Eccentricity of the orbit */
  double incl_InclinationOfOrbit;       /** Inclination of the orbit */
};

struct CometDataParabolic {
  char name[50];         /** Name of the comet  */
  double epoch_peri_day; /** Epoch perihelion day */
  int epoch_peri_month;  /** Epoch perihelion month */
  int epoch_peri_year;   /** Epoch perihelion year */
  double arg_peri;       /** Arg perihelion */
  double node;           /** Comet's node */
  double peri_dist;      /** Distance at the perihelion */
  double incl;           /** Inclination */
};

struct CometDataElliptical populate_comet_data_elliptical(
    char *name, double epoch_EpochOfPerihelion,
    double peri_LongitudeOfPerihelion, double node_LongitudeOfAscendingNode,
    double period_PeriodOfOrbit, double axis_SemiMajorAxisOfOrbit,
    double ecc_EccentricityOfOrbit, double incl_InclinationOfOrbit);

struct CometDataParabolic
populate_comet_data_parabolic(char *name, double epoch_peri_day,
                              int epoch_peri_month, int epoch_peri_year,
                              double arg_peri, double node, double peri_dist,
                              double incl);

struct CometDataElliptical get_comet_data_elliptical(char *cometName);

struct CometDataParabolic get_comet_data_parabolic(char *cometName);
#endif