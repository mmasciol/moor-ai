#ifndef MOOR_AI_DEF_H
#define MOOR_AI_DEF_H

#include "sys.h"

typedef struct LinePropertiesT {
  char *label;
  int nlabel;
  ufloat_t od;
  ufloat_t in;
  ufloat_t k;
  ufloat_t c;
  ufloat_t m;
} LineProperties;

typedef struct DomainT {
  char *label;
  LineProperties *line_props;
  int nline_props;
} Domain;

#endif /* MOOR_AI_DEF_H */
