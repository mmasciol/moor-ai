#ifndef MOOR_AI_DOMAIN_H
#define MOOR_AI_DOMAIN_H

#include "def.h"
#include "err.h"

ERROR_CODE domain_initialize(Domain *d, char **msg);
ERROR_CODE domain_set_label(Domain *d, char *info, char **msg);
ERROR_CODE domain_free(Domain *d, char **msg);

#endif /* MOOR_AI_DOMAIN_H */
