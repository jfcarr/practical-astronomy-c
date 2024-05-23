#include <stdlib.h>

#ifndef binary_data_inc
#define binary_data_inc

struct BinaryStarData {
  char name[50];     /** Name of binary system.  */
  double period;     /** Period of the orbit. */
  double epoch_peri; /** Epoch of the perihelion. */
  double long_peri;  /** Longitude of the perihelion. */
  double ecc;        /** Eccentricity of the orbit. */
  double axis;       /** Semi-major axis of the orbit. */
  double incl;       /** Orbital inclination. */
  double pa_node;    /** Position angle of the ascending node. */
};

struct BinaryStarData populate_binary_star_data(char *name, double period,
                                                double epoch_peri,
                                                double long_peri, double ecc,
                                                double axis, double incl,
                                                double pa_node);

struct BinaryStarData get_binary_star_data(char *binary_star_name);

#endif