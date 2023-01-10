#include <stdio.h>
#include <stdlib.h>

#include "domain.h"
#include "sys.h"

ERROR_CODE domain_initialize(Domain *d, char **msg)
{
  ERROR_CODE ierr = SAFE;
  EMITERRQ(STACK, __func__);

  d->label = NULL;
  d->line_props = NULL;
  d->nline_props = 0;

  return ierr;
CLEAN_UP:
  return FATAL;
}

ERROR_CODE domain_set_label(Domain *d, char *info, char **msg)
{
  ERROR_CODE ierr = SAFE;
  EMITERRQ(STACK, __func__);

  return ierr;
CLEAN_UP:
  return FATAL;
}

ERROR_CODE domain_free(Domain *d, char **msg)
{
  ERROR_CODE ierr = SAFE;
  EMITERRQ(STACK, __func__);

  if (d->label) {
    checkpoint();
    free(d->label);
  }

  if (d->label) {
    checkpoint();
    free(d->line_props);
  }

  return ierr;
CLEAN_UP:
  return FATAL;
}
